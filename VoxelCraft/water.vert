#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoords;

out vec2 v_texCoords;

uniform mat4 u_view;
uniform mat4 u_projection;

uniform float u_time;
uniform lowp float u_amplitude;
uniform lowp float u_frequency;

void main() {
	gl_Position = u_projection * u_view * vec4(position.x, position.y + u_amplitude * sin(u_frequency * (u_time + position.x + position.x)), position.z, 1.0);
	v_texCoords = texCoords;
}