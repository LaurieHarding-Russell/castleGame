#version 130


in vec3 vectorIn;
out vec4 fragmentColour;

uniform vec4 position;
uniform mat4 projection;
uniform vec4 colour;

void main() {
    gl_Position = projection * (position + vec4(vectorIn, 1.0));
    fragmentColour = colour;
}
