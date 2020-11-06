#version 450 core


layout (location = 0) in vec3 positionl;
layout (location = 1) in vec3 colourl;

out vec3 Colour;

uniform float size;
uniform mat4 view;
uniform mat4 proj;
uniform vec3 position;
uniform vec3 colour;

void main(){

	gl_Position = proj * view * vec4(position, 1.0f);
	float attenuation = inversesqrt(0.1f * length(gl_Position.xyz));
	gl_PointSize = attenuation * size;

	Colour = colour;
}