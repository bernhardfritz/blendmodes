#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "linmath.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

static const struct {
	float x, y;
	float u, v;
} vertices[] = {
	{ -1.f,  1.f, 0.f, 1.f },
	{ -1.f, -1.f, 0.f, 0.f },
	{  1.f,  1.f, 1.f, 1.f },
	{  1.f, -1.f, 1.f, 0.f }
};

static const unsigned short indices[] = {
	0, 1, 2,
	2, 1, 3
};

static void error_callback(int error, const char* description) {
	fprintf(stderr, "Error: %s\n", description);
}

char* readFile(const char* filename) {
	char* s = NULL;
	FILE* file = fopen(filename, "r");
	if (file) {
		fseek(file, 0, SEEK_END);
		size_t length = ftell(file);
		rewind(file);
		s = (char*) malloc(sizeof(char) * (length + 1));
		s[length] = '\0';
		if (length != fread(s, sizeof(char), length, file)) {
			free(s);
			s = NULL;
		}
		fclose(file);
	}
	return s;
}

void validateShader(GLuint shader) {
	GLint compile_status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_status);
	if (compile_status == GL_FALSE) {
		GLint log_length = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);
		char* log_buffer = (char*) malloc(log_length * sizeof(char));
		glGetShaderInfoLog(shader, log_length * sizeof(char), &log_length, log_buffer);
		fprintf(stderr, "%s", log_buffer);
		free(log_buffer);
		exit(EXIT_FAILURE);
	}
}

GLuint loadTexture(const char* filename, int* width, int* height) {
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	stbi_set_flip_vertically_on_load(1);
	unsigned char* data = stbi_load(filename, width, height, NULL, 4);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, *width, *height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	stbi_image_free(data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	return texture;
}

const char *get_filename_ext(const char *filename) {
    const char *dot = strrchr(filename, '.');
    if(!dot || dot == filename) return "";
    return dot + 1;
}

#define max(a,b) \
({ __typeof__ (a) _a = (a); \
__typeof__ (b) _b = (b); \
_a > _b ? _a : _b; })

int main(int argc, char* argv[]) {
	if (argc < 6) {
		fprintf(stderr, "Usage: %s backgroundFilename foregroundFilename outputFilename blendMode blendOpacity\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	char* backgroundFilename = argv[1];
	if (access(backgroundFilename, F_OK) == -1) {
		fprintf(stderr, "%s cannot be found\n", backgroundFilename);
		exit(EXIT_FAILURE);
	}
	char* foregroundFilename = argv[2];
	if (access(foregroundFilename, F_OK) == -1) {
		fprintf(stderr, "%s cannot be found\n", foregroundFilename);
		exit(EXIT_FAILURE);
	}
	char* outputFilename = argv[3];
	const char* outputFileExtension = get_filename_ext(outputFilename);
	int blendMode;
	if (sscanf(argv[4], "%d", &blendMode) == 0 || blendMode < 0 || blendMode > 24) {
		fprintf(stderr, "blendMode is required to be an integer between 0 and 24\n");
		exit(EXIT_FAILURE);
	}
	float blendOpacity;
	if (sscanf(argv[5], "%f", &blendOpacity) == 0 || blendOpacity < 0.f || blendOpacity > 1.f) {
		fprintf(stderr, "blendOpacity is required to be a float between 0 and 1\n");
		exit(EXIT_FAILURE);
	}

	glfwSetErrorCallback(error_callback);

	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_VISIBLE, 0);

	GLFWwindow* window = glfwCreateWindow(640, 480, "blendmodes", NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	GLuint ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	int backgroundWidth, backgroundHeight, foregroundWidth, foregroundHeight;
	GLuint texture0 = loadTexture(backgroundFilename, &backgroundWidth, &backgroundHeight);
	GLuint texture1 = loadTexture(foregroundFilename, &foregroundWidth, &foregroundHeight);

	glfwSetWindowSize(window, max(backgroundWidth, foregroundWidth), max(backgroundHeight, foregroundHeight));

	GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	const char* vs = readFile("vs.glsl");
	glShaderSource(vertex_shader, 1, &vs, NULL);
	free((char*) vs);
	glCompileShader(vertex_shader);
	validateShader(vertex_shader);

	GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	const char* fs = readFile("fs.glsl");
	glShaderSource(fragment_shader, 1, &fs, NULL);
	free((char*) fs);
	glCompileShader(fragment_shader);
	validateShader(fragment_shader);

	GLuint program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program);

	GLint aPosition_location = glGetAttribLocation(program, "aPosition");
	GLint aUV_location = glGetAttribLocation(program, "aUV");
	GLint uMVP_location = glGetUniformLocation(program, "uMVP");
	GLint uTexture0_location = glGetUniformLocation(program, "uTexture0");
	GLint uTexture1_location = glGetUniformLocation(program, "uTexture1");
	GLint uBlendMode = glGetUniformLocation(program, "uBlendMode");
	GLfloat uBlendOpacity = glGetUniformLocation(program, "uBlendOpacity");

	glEnableVertexAttribArray(aPosition_location);
	glVertexAttribPointer(
		aPosition_location,
		2,
		GL_FLOAT,
		GL_FALSE,
		sizeof(float) * 4,
		(void*) 0
	);

	glEnableVertexAttribArray(aUV_location);
	glVertexAttribPointer(
		aUV_location,
		2,
		GL_FLOAT,
		GL_FALSE,
		sizeof(float) * 4,
		(void*) (sizeof(float) * 2)
	);

	float ratio;
	int width, height;
	mat4x4 m, p, mvp;

	glfwGetFramebufferSize(window, &width, &height);
	ratio = width / (float) height;

	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT);

	mat4x4_identity(m);
	mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
	mat4x4_mul(mvp, p, m);

	glUseProgram(program);
	glUniformMatrix4fv(uMVP_location, 1, GL_FALSE, (const GLfloat*) mvp);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture0);
	glUniform1i(uTexture0_location, 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glUniform1i(uTexture1_location, 1);
	glUniform1i(uBlendMode, blendMode);
	glUniform1f(uBlendOpacity, blendOpacity);
	
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, (void*) 0);

	char pixels[width * height * 4];
	glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
	stbi__vertical_flip(pixels, width, height, 4);
	int success = 0;
	if (strcmp(outputFileExtension, "png") == 0) {
		success = stbi_write_png(outputFilename, width, height, 4, pixels, 0);
	} else if (strcmp(outputFileExtension, "bmp") == 0) {
		success = stbi_write_bmp(outputFilename, width, height, 4, pixels);
	} else if (strcmp(outputFileExtension, "tga") == 0) {
		success = stbi_write_tga(outputFilename, width, height, 4, pixels);
	} else if (strcmp(outputFileExtension, "jpg") == 0) {
		success = stbi_write_jpg(outputFilename, width, height, 4, pixels, 100);
	} else {
		fprintf(stderr, "The file extension \"%s\" is not supported. Please use one of the following instead: png, bmp, tga, jpg\n", outputFileExtension);
	}
	if (!success) {
		fprintf(stderr, "Unable to write %s\n", outputFilename);
	}

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}