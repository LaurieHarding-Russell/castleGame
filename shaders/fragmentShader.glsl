#version 130

in vec4 fragmentColour;
out vec4 fColor;
out vec3 fragmentLocation;

const vec3 sunPosition = vec3(1.0, 10.0, 1.0);

void main(){
	vec3 lightDir = sunPosition - fragmentLocation;
  	float distance = length(lightDir);

	fColor = distance * fragmentColour ;
}