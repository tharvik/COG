uniform vec3 camPos;

varying vec4 fragPos;
varying vec3 faceNormal;

varying vec3 T;
varying vec3 B; 
varying vec3 N;

void main(void)
{
	N = gl_Normal;
	fragPos = gl_Vertex;
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}