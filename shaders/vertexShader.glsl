#version 130


in vec3 vectorIn;
out vec4 fragmentColour;

void main() {
    gl_Position = vec4(vectorIn, 1.0);
    fragmentColour = vec4(1,1,1,1);
}
