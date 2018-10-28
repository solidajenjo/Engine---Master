#version 330
layout(location = 0) in vec3 vertex_position;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;
uniform vec3 color;

out vec4 colorV;

void main()
{
	vec4 vertex = proj*view*model*vec4(vertex_position, 1.0);
	colorV = vec4(color, 1.0);
 	gl_Position = vertex;
}