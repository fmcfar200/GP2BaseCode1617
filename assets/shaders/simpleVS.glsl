#version 410

layout(location=0) in vec3 vertexPosition;
layout(location=1) in vec4 vertexColours;
layout(location=2) in vec3 vertextTextureCoords;

out vec2 vertexTextureCoordsOut;
out vec4 vertexColoursOut;

uniform mat4 MVP;

void main()
{
		gl_Position = MVP * vec4(vertexPosition, 1.0);
		vertexTextureCoordsOut = vertexTextureCoords;
}
