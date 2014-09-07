varying vec4 localFragPos;
varying vec3 normal;

void main(void)
{
	localFragPos = gl_Vertex;
	normal = gl_Normal;
	
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}