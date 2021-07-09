#version 430 core

out vec4 FragColog;

in vec4 world_vertex;
in vec4 world_normal;

// Light
uniform vec3 eye;

void main()
{
	vec3 normalized_normal = normalize(world_normal).xyz;
	vec3 light_position = vec3(0, 0, 10);
	vec3 light_direction = normalize(light_position - world_vertex.xyz);
	float lambert = clamp(dot(normalized_normal, light_direction), 0, 1);
	
	FragColog = vec4(vec3(1, 1, 1) * lambert, 1) ;
}