#define MAP(f, a, b) vec3(f(a.r, b.r), f(a.g, b.g), f(a.b, b.b))

uniform sampler2D uTexture0;
uniform sampler2D uTexture1;
uniform int uBlendMode;
uniform float uBlendOpacity;

varying vec2 vUV;

float add(float a, float b) {
	return min(a + b, 1.0);
}

vec3 add(vec3 a, vec3 b) {
	return min(a + b, vec3(1.0));
}

vec3 average(vec3 a, vec3 b) {
	return (a + b) / 2.0;
}

float colorBurn(float a, float b) {
	return (b == 0.0) ? b : max((1.0 - ((1.0 - a) / b)), 0.0);
}

vec3 colorBurn(vec3 a, vec3 b) {
	return MAP(colorBurn, a, b);
}

float colorDodge(float a, float b) {
	return (b == 1.0) ? b : min(a / (1.0 - b), 1.0);
}

vec3 colorDodge(vec3 a, vec3 b) {
	return MAP(colorDodge, a, b);
}

float darken(float a, float b) {
	return min(b, a);
}

vec3 darken(vec3 a, vec3 b) {
	return MAP(darken, a, b);
}

vec3 difference(vec3 a, vec3 b) {
	return abs(a - b);
}

vec3 exclusion(vec3 a, vec3 b) {
	return a + b - 2.0 * a * b;
}

float reflect(float a, float b) {
	return (b == 1.0) ? b : min(a * a / (1.0 - b), 1.0);
}

vec3 reflect(vec3 a, vec3 b) {
	return MAP(reflect, a, b);
}

vec3 glow(vec3 a, vec3 b) {
	return reflect(b, a);
}

float overlay(float a, float b) {
	return a < 0.5 ? (2.0 * a * b) : (1.0 - 2.0 * (1.0 - a) * (1.0 - b));
}

vec3 overlay(vec3 a, vec3 b) {
	return MAP(overlay, a, b);
}

vec3 hardLight(vec3 a, vec3 b) {
	return overlay(b, a);
}

float vividLight(float a, float b) {
	return (b < 0.5) ? colorBurn(a, (2.0 * b)) : colorDodge(a, (2.0 * (b - 0.5)));
}

vec3 vividLight(vec3 a, vec3 b) {
	return MAP(vividLight, a, b);
}

float hardMix(float a, float b) {
	return (vividLight(a, b) < 0.5) ? 0.0 : 1.0;
}

vec3 hardMix(vec3 a, vec3 b) {
	return MAP(hardMix, a, b);
}

float lighten(float a, float b) {
	return max(b, a);
}

vec3 lighten(vec3 a, vec3 b) {
	return MAP(lighten, a, b);
}

float linearBurn(float a, float b) {
	return max(a + b - 1.0, 0.0);
}

vec3 linearBurn(vec3 a, vec3 b) {
	return max(a + b - vec3(1.0), vec3(0.0));
}

float linearDodge(float a, float b) {
	return min(a + b, 1.0);
}

vec3 linearDodge(vec3 a, vec3 b) {
	return min(a + b, vec3(1.0));
}

float linearLight(float a, float b) {
	return b < 0.5 ? linearBurn(a, (2.0 * b)) : linearDodge(a, (2.0 * (b - 0.5)));
}

vec3 linearLight(vec3 a, vec3 b) {
	return MAP(linearLight, a, b);
}

vec3 multiply(vec3 a, vec3 b) {
	return a * b;
}

vec3 negation(vec3 a, vec3 b) {
	return vec3(1.0) - abs(vec3(1.0) - a - b);
}

vec3 normal(vec3 a, vec3 b) {
	return b;
}

vec3 phoenix(vec3 a, vec3 b) {
	return min(a, b) - max(a, b) + vec3(1.0);
}

float pinLight(float a, float b) {
	return (b < 0.5) ? darken(a, (2.0 * b)) : lighten(a , (2.0 * (b - 0.5)));
}

vec3 pinLight(vec3 a, vec3 b) {
	return MAP(pinLight, a, b);
}

float screen(float a, float b) {
	return 1.0 - ((1.0 - a) * (1.0 - b));
}

vec3 screen(vec3 a, vec3 b) {
	return MAP(screen, a, b);
}

float softLight(float a, float b) {
	return (b < 0.5) ? (2.0 * a * b + a * a * (1.0 - 2.0 * b)) : (sqrt(a) * (2.0 * b - 1.0) + 2.0 * a * (1.0 - b));
}

vec3 softLight(vec3 a, vec3 b) {
	return MAP(softLight, a, b);
}

float subtract(float a, float b) {
	return max(a + b - 1.0, 0.0);
}

vec3 subtract(vec3 a, vec3 b) {
	return max(a + b - vec3(1.0), vec3(0.0));
}

vec3 blend(int mode, vec3 a, vec3 b, float opacity) {
	vec3 color = vec3(0.0);
	if (mode == 0) {
		color = add(a, b);
	} else if (mode == 1) {
		color = average(a, b);
	} else if (mode == 2) {
		color = colorBurn(a, b);
	} else if (mode == 3) {
		color = colorDodge(a, b);
	} else if (mode == 4) {
		color = darken(a, b);
	} else if (mode == 5) {
		color = difference(a, b);
	} else if (mode == 6) {
		color = exclusion(a, b);
	} else if (mode == 7) {
		color = glow(a, b);
	} else if (mode == 8) {
		color = hardLight(a, b);
	} else if (mode == 9) {
		color = hardMix(a, b);
	} else if (mode == 10) {
		color = lighten(a, b);
	} else if (mode == 11) {
		color = linearBurn(a, b);
	} else if (mode == 12) {
		color = linearDodge(a, b);
	} else if (mode == 13) {
		color = linearLight(a, b);
	} else if (mode == 14) {
		color = multiply(a, b);
	} else if (mode == 15) {
		color = negation(a, b);
	} else if (mode == 16) {
		color = normal(a, b);
	} else if (mode == 17) {
		color = overlay(a, b);
	} else if (mode == 18) {
		color = phoenix(a, b);
	} else if (mode == 19) {
		color = pinLight(a, b);
	} else if (mode == 20) {
		color = reflect(a, b);
	} else if (mode == 21) {
		color = screen(a, b);
	} else if (mode == 22) {
		color = softLight(a, b);
	} else if (mode == 23) {
		color = subtract(a, b);
	} else if (mode == 24) {
		color = vividLight(a, b);
	}
	return mix(a, color, opacity);
}

void main() {
	vec4 color0 = texture2D(uTexture0, vUV);
	vec4 color1 = texture2D(uTexture1, vUV);
	gl_FragColor = vec4(blend(uBlendMode, color0.rgb, color1.rgb, uBlendOpacity), 1.0);
}