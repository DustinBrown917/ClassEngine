#version 450 core

in vec3 Colour;

out vec4 fColour;

void main(){
	fColour = vec4(Colour, 1);
}