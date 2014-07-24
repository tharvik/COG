uniform vec3 Ka, Kd, Ks;
uniform float Ns, d;

varying vec4 localPosition;
 
void main()
{
	

	if (localPosition.z > -0.05 && localPosition.z < 0.05) {
		gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
	} else if (localPosition.z < -10000.0) {
		vec3 a = Ka + Kd + Ks + vec3(d, Ns, 0);
		gl_FragColor = vec4(a, 1.0);
	} else {
		gl_FragColor = vec4(Ka + Kd + Ks, 1.0);
	}
}