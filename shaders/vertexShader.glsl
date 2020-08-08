#version 130


in vec3 vectorIn;
uniform mat4 position;
out vec4 fragmentColour;

void main() {
    gl_Position = position * vec4(vectorIn, 1.0);
    fragmentColour = vec4(1,1,1,1);
}
