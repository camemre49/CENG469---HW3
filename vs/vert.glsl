#version 330 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec2 velocity;
layout(location = 2) in float age;

out float fsAge;
void main() {
	fsAge = age;
	gl_Position = vec4(position.xy, 0.0, 1.0);
}
