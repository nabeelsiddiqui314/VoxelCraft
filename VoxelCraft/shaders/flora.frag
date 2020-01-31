#version 330 core

out vec4 color;
in vec2 v_texCoords;
in lowp vec3 v_lighting;
in float v_visibility;

uniform sampler2D u_texture;
uniform vec3 u_skyColor;

void main() {
	color = texture(u_texture, v_texCoords) * vec4(v_lighting + 0.2, 1.0);
	//color = mix(vec4(u_skyColor, 1.0), color, v_visibility);
}