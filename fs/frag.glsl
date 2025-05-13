#version 330 core

in float fsAge;
out vec4 FragColor;

void main() {
	FragColor = vec4(0.3, 0.75, 0.75, 1.0) * fsAge;
}
