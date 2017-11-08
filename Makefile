all:
	gcc -o bm main.c -IGL/include GL/src/glad.c -lglfw -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo