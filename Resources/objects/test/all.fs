uniform vec3 Ka, Kd, Ks;
uniform float Ns, d;

varying vec4 localPosition;
 
void main()
{
	

	if (localPosition.z > -0.05 && localPosition.z < 0.05) {
		gl_FragColor = vec4(Kd, 1.0);
	} else if (localPosition.z < -10000.0) {
		gl_FragColor = vec4(Ka, 1.0);
	} else {
		gl_FragColor = vec4(Ks, 1.0);
	}
}