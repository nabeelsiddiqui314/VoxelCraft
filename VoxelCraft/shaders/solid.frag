#version 330 core

out vec4 color;
in vec2 v_texCoords;
in lowp vec4 v_lighting;

uniform sampler2D u_texture;

void main() {
	color = texture(u_texture, v_texCoords) * v_lighting;
}