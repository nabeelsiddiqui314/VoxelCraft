#version 330 core

out vec4 color;
in vec2 v_texCoords;
in lowp vec3 v_lighting;
in float v_visibility;

uniform sampler2D u_texture;
uniform vec3 u_skyColor;
uniform float u_gamma;

void main() {
	color = texture(u_texture, v_texCoords) * vec4(v_lighting, 1.0);
	color.xyz = pow(color.xyz, vec3(u_gamma));
	//color = mix(vec4(u_skyColor, 1.0), color, v_visibility);
}