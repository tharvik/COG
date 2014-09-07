varying vec4 fragPos, lightPos;
varying vec3 faceNormal;

varying vec3 T;
varying vec3 B; 
varying vec3 N;

varying vec2 texCoord;

uniform sampler2D map_Kd, map_Ks;



void main(void)
{
	texCoord = gl_MultiTexCoord0.xy;

	lightPos = vec4(10.0, 10.0, 30.0, 1.0);

	N = gl_Normal;
	fragPos = gl_Vertex;
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}