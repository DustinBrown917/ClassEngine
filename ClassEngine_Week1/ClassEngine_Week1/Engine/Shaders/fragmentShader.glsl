#version 450 core

in vec3 Normal;
in vec2 TexCoords;
in vec3 Colour;
in vec3 FragPosition;

out vec4 fColour;

struct Light{
	vec3 position;
	float ambient;
	float diffuse;
	vec3 colour;
};

struct Material{
	sampler2D diffuseMap;
	float shininess; //ns*
	float transparency; //d*

	vec3 ambient; //ka*
	vec3 diffuse; //kd*
	vec3 specular; //ks*
};

//uniform sampler2D inputTexture;
uniform Material material;
uniform vec3 cameraPos;
uniform Light light;


void main(){
	//ambient
	vec3 ambient = light.ambient * material.ambient * texture(material.diffuseMap, TexCoords).rgb *
	light.colour;
	//diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPosition);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = (diff * material.diffuse) * texture(material.diffuseMap, TexCoords).rgb * light.colour;
	//specular
	vec3 viewDir = normalize(cameraPos-FragPosition);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = (spec * material.specular) * light.colour;
	vec3 result = ambient + diffuse + specular;
	fColour = vec4(result, material.transparency);
}