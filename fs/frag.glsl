#version 330 core

in float fsAge;
out vec4 FragColor;

void main() {
	/* blue to green
	FragColor = mix(
		vec4(0.3, 0.7, 0.0, 1.0),
		vec4(0.0, 0.0, 1.0, 1.0),
		pow(fsAge, 2.0)
	);
	*/

	//* orange to red
	FragColor = mix(
	vec4(0.1, 0.0, 0.0, 0.1),   // dark red
	vec4(1.0, 0.2, 0.0, 1.0),   // bright orange
		pow(fsAge, 2.0)
	);
	//*/

	/* blue
	FragColor = mix(
		vec4(0.0, 0.2, 1.0, 0.1),
		vec4(0.2, 0.05, 0.0, 1.0),
		pow(fsAge, 2.0)
	);
	*/
}
