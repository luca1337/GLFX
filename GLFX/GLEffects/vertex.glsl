#version 430 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;

// MVP
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec4 world_vertex;
out vec4 world_normal;

void main()
{
	vec4 world_position		= model * vec4(vertex, 1.0);
	world_position			= view * world_position;
	world_position			= projection * world_position;

	world_vertex			= world_position;
	world_normal			= model * vec4(normal, 1.0);

	gl_Position				= world_position;
}