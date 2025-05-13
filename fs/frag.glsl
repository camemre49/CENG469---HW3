#version 330 core

in float fsAge;
out vec4 FragColor;

void main() {
	FragColor = mix(
		vec4(0.0, 0.2, 1.0, 1.0),
		vec4(0.2, 0.05, 0.3, 1.0),
		fsAge
	);
}
