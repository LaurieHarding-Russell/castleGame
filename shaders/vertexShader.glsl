#version 130

in vec2 textureCoordinate;
in vec4 vertexPosition;
out vec4 colour;

out vec4 fragmentColour;


uniform mat4 ModelView, Projection;

void main() {
    gl_Position = Projection * ModelView * vertexPosition;
    fragmentColour = vec4(1,1,1,1);
}
