#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoords;
layout (location = 2) in float lighting;

out vec2 v_texCoords;
out lowp vec4 v_lighting;
out float v_visibility;

uniform mat4 u_view;
uniform mat4 u_projection;

uniform float u_density;
uniform float u_gradient;
uniform float u_time;
uniform float u_frequency;
uniform float u_amplitude;

vec3 getPos() {
	return position + vec3( u_amplitude * sin((position.x * position.y + u_time) * u_frequency), 0, 
	                        u_amplitude * sin((position.z * position.y + u_time) * u_frequency) );
}

void main() {
	gl_Position = u_projection * u_view * vec4(getPos(), 1.0);
	v_texCoords = texCoords;
	v_lighting = vec4(lighting, lighting, lighting, 1.0);

	vec4 posRelativeToCam = u_view * vec4(position, 1.0);
	float distance = length(posRelativeToCam.xyz);
	v_visibility = exp(-pow((distance * u_density), u_gradient));
	v_visibility = clamp(v_visibility, 0.0, 1.0);
}