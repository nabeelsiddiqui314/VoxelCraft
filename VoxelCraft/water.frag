#version 330 core

out vec4 color;
in vec2 v_texCoords;
in lowp vec4 v_lighting;

uniform sampler2D u_texture;
uniform lowp vec4 u_alphaMultiplier;

void main() {
	color = texture(u_texture, v_texCoords) * u_alphaMultiplier * v_lighting;
}