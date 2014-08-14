varying vec4 fragPos, lightPos;
varying vec3 faceNormal;

varying vec3 T;
varying vec3 B; 
varying vec3 N;

void main(void)
{

	lightPos = vec4(2.0, 2.0, 2.0, 1.0);

	N = gl_Normal;
	fragPos = gl_Vertex;
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}