attribute vec2 aPosition;
attribute vec2 aUV;

uniform mat4 uMVP;

varying vec2 vUV;

void main() {
	vUV = aUV;
	gl_Position = uMVP * vec4(aPosition, 0.0, 1.0);
}