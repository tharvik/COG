uniform vec3 Ka;

varying vec4 localPosition;

void main()
{
	localPosition = gl_Vertex; 

	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}