varying vec4 pixelPos;

void main(void)
{
	gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
	pixelPos[0] = gl_Vertex[0] / 10.0;
	pixelPos[1] = gl_Vertex[1] / 10.0;
	pixelPos[2] = gl_Vertex[2] / 10.0;
	pixelPos[3] = gl_Vertex[3] / 10.0;
    gl_Position = ftransform();
}