#version 130
uniform mat4 KeyBindMatrix;
in vec3 a_pos;
in vec3 a_color;
out vec3 color;

void main() {
	gl_Position = KeyBindMatrix * vec4(a_pos-vec3(7,15,0), 1.0);
	color = a_color;
}

