// fragment, light and camera position
varying vec4 fragPos, lightPos; 

// normal on the fragment, fragment to light, fragment to camera
varying vec3 N, L, C;

//ambient color, diffuse color, specular color
uniform vec3 Ka, Kd, Ks;

// specular coefficient, opacity
uniform float Ns, d;

// Textures
uniform bool activeTextures[6];
varying vec2 texCoord;
uniform sampler2D map_Ka, map_Kd, map_Ks, map_Ns, map_d, map_bump;
vec4 frag_Ka, frag_Kd, frag_Ks, frag_Ns, frag_d, frag_bump;

void main(void)
{
	vec3 nn;
	vec4 diffusion, specular, diffusionFactor;


	vec3 lightColor = vec3(1.0, 1.0, 1.0);
	vec2 aaa = vec2(texCoord.x, 1.0 - texCoord.y);

	vec3 camPos = vec3(gl_ModelViewMatrixInverse[3]);
	vec3 L = lightPos.xyz - fragPos.xyz;
	vec3 C = camPos - fragPos.xyz;
	
	frag_Ks   = texture2D(map_Ks, aaa);
	frag_Ns   = texture2D(map_Ns, aaa);
	frag_d    = texture2D(map_d,  aaa);
	
	// normal
	if (activeTextures[5]) { // map_bump
		frag_bump = texture2D(map_bump, aaa);
		frag_bump = texture2D(map_bump, aaa);
		nn = (frag_bump.xyz - 0.5) * 2.0;
	} else {
		nn = N;
	}
		
	// diffusion and ambient
	diffusionFactor = vec4(lightColor * max(dot(normalize(L), normalize(nn)), 0.0), 1.0);
	if (activeTextures[0]) { // map_Ka
		frag_Ka   = texture2D(map_Ka, aaa);
		diffusionFactor += frag_Ka;
	} else {
		diffusionFactor = diffusionFactor + vec4(Ka, 1.0);
	}
	
	if (activeTextures[1]) {
		frag_Kd   = texture2D(map_Kd, aaa);
		diffusion = vec4(Kd, 1.0) * frag_Kd * diffusionFactor;
	} else {
		diffusion = vec4(Kd, 1.0) * diffusionFactor;
	}
		
	// specular
	if (activeTextures[2]) { // map_Ks
		frag_Ks = texture2D(map_Ks, aaa);
		if (activeTextures[3]) {
			frag_Ns = texture2D(map_Ns, aaa);
			specular  = vec4(Ks, 1.0) * frag_Ks * pow(dot(nn, normalize(normalize(C) + normalize(L))), frag_Ns.x);
		} else {
			specular  = vec4(Ks, 1.0) * frag_Ks * pow(dot(nn, normalize(normalize(C) + normalize(L))), Ns);
		}
	} else {
		if (activeTextures[3]) { // map_Ns
			frag_Ns = texture2D(map_Ns, aaa);
			specular  = vec4(Ks * pow(dot(nn, normalize(normalize(C) + normalize(L))), frag_Ns.x), 1.0);
		} else {
			specular  = vec4(Ks * pow(dot(nn, normalize(normalize(C) + normalize(L))), Ns), 1.0);
		}
	}
	
	gl_FragColor = diffusion + specular;
}
