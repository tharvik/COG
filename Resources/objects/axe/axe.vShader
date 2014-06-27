uniform vec3 camPos;

varying vec4 fragPos;

void main(void)
{
	gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
	fragPos = gl_Vertex;
//	pixelPos[0] = gl_Vertex[0] / 10.0;
//	pixelPos[1] = gl_Vertex[1] / 10.0;
//	pixelPos[2] = gl_Vertex[2] / 10.0;
//	pixelPos[3] = gl_Vertex[3] / 10.0;

	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}