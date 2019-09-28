#version 330 core

out vec4 color;
in vec2 v_texCoords;

uniform sampler2D u_texture;
uniform lowp vec4 u_alphaMultiplier;

void main() {
	color = texture(u_texture, v_texCoords) * u_alphaMultiplier;
}