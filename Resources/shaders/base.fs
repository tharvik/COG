// fragment, light and camera position
varying vec4 fragPos, lightPos; 

// normal on the fragment, fragment to light, fragment to camera
varying vec3 N, L, C;

//ambient color, diffuse color, specular color
uniform vec3 Ka, Kd, Ks;

// specular coefficient
uniform float Ns, d;

void main(void)
{
	vec3 lightColor = vec3(1.0, 1.0, 1.0);

	vec3 camPos = vec3(gl_ModelViewMatrixInverse[3]);

	vec3 L = lightPos.xyz - fragPos.xyz;
	vec3 C = camPos - fragPos.xyz;

	vec3 diffusion = Kd * max(dot(normalize(L), normalize(N)), 0.0);
	vec3 specular  = Ks * pow(dot(N, normalize(normalize(C) + normalize(L))), Ns);

	gl_FragColor = vec4(diffusion + specular, 1);
//	gl_FragColor = vec4(lightPos);
}
