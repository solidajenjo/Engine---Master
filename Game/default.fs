#version 330 core
out vec4 color;

in vec4 colorV;
void main()
{
	color = vec4(colorV.x, colorV.y, colorV.z, 1.0);
	
}