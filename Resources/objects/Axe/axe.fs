varying vec4 localFragPos;
varying vec3 normal;

void main(void)
{
	vec3 lightPos = vec3(1.0);
	vec3 color = vec3(0.0);

	if (localFragPos.x > 0.05) {
		color += vec3(1.0, 0.0, 0.0);
	}
	
	if (localFragPos.y > 0.05) {
		color += vec3(0.0, 1.0, 0.0);
	}
	
	if (localFragPos.z > 0.05) {
		color += vec3(0.0, 0.0, 1.0);
	}
	
	float diffusion = max(dot(normal, lightPos), 0.3);
	
	gl_FragColor = vec4(diffusion * color, 1.0);
}