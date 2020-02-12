#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoords;
layout (location = 2) in float naturalLight;
layout (location = 3) in float skyExposure;

out vec2 v_texCoords;
out lowp vec3 v_lighting;
out float v_visibility;

uniform mat4 u_view;
uniform mat4 u_projection;

uniform float u_time;
uniform lowp float u_amplitude;
uniform lowp float u_frequency;

uniform float u_density;
uniform float u_gradient;

uniform float u_worldTime;

void main() {
	gl_Position = u_projection * u_view * vec4(position.x, position.y + u_amplitude * sin(u_frequency * (u_time + position.x + position.x)), position.z, 1.0);
	v_texCoords = texCoords;

	float lightIntensity = max(u_worldTime, 0.02f);
	v_lighting = vec3((naturalLight / 32.0) + ((skyExposure / 32.0)) * lightIntensity);

	vec4 posRelativeToCam = u_view * vec4(position, 1.0);
	float distance = length(posRelativeToCam.xyz);
	v_visibility = exp(-pow((distance * u_density), u_gradient));
	v_visibility = clamp(v_visibility, 0.0, 1.0);
}