#version 430 core

in vec3 myPosition;
in vec4 myColor;
in vec3 myNormal;

layout(location = 0) out vec4 FragColor;

layout (location = 20) uniform mat4 viewMatrix;

vec3 light_position_world  = vec3(0.0, 10.0, 0.0);
vec3 Ls = vec3(1.0, 1.0, 1.0); // white specular colour
vec3 Ld = vec3(0.7, 0.7, 0.7); // dull white diffuse light colour
vec3 La = vec3(0.4, 0.4, 0.4); // grey ambient colour

// surface reflectance
vec3 Ks = vec3(1.0, 1.0, 1.0); // fully reflect specular light

vec3 Ka = vec3(1.0, 1.0, 1.0); // fully reflect ambient light
float specular_exponent = 100.0; // specular 'power'



void main()
{
	vec3 Ia = La * Ka;
	vec3 color3 = vec3(myColor);
	// diffuse intensity
	// raise light position to eye space
	vec3 light_position_eye = vec3(viewMatrix * vec4(light_position_world, 1.0));
	vec3 distance_to_light_eye = light_position_eye - myPosition;
	vec3 direction_to_light_eye = normalize(distance_to_light_eye);
	float dot_prod = dot(direction_to_light_eye, myNormal);
	dot_prod = max(dot_prod, 0.0);
	vec3 Id = Ld * color3 * dot_prod; // final diffuse intensity

	// specular intensity
	vec3 surface_to_viewer_eye = normalize(-myPosition);

	//vec3 reflection_eye = reflect (-direction_to_light_eye, normal_eye);
	//float dot_prod_specular = dot (reflection_eye, surface_to_viewer_eye);
	//dot_prod_specular = max (dot_prod_specular, 0.0);
	//float specular_factor = pow (dot_prod_specular, specular_exponent);

	// blinn
	vec3 half_way_eye = normalize(surface_to_viewer_eye + direction_to_light_eye);
	float dot_prod_specular = max(dot(half_way_eye, myNormal), 0.0);
	float specular_factor = pow(dot_prod_specular, specular_exponent);

	vec3 Is = Ls * Ks * specular_factor; 

	FragColor = vec4(Is + Id + Ia, 1.0);
}