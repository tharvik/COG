varying vec4 pixelPos;

void main(void)
{
	gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
	pixelPos = ftransform();
    gl_Position = ftransform();
}