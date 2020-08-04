#version 150

in vec4 vertexPosition;
out vec4 colour;

uniform mat4 ModelView, Projection;

void main() {
    gl_Position = Projection * ModelView * vertexPosition;
    fragmentColour = vec4(1,1,1,1);
}