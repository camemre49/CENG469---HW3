#version 330 core

in float fsAge;
out vec4 FragColor;

void main() {
	FragColor = mix(
		vec4(0.1, 0.0, 0.0, 0.1),   // dark red
		vec4(1.0, 0.2, 0.0, 1.0),   // bright orange
		pow(fsAge, 2.0)
	);
}
