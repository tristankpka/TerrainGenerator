#version 120

in vec3 normal0;

uniform sampler2D diffuse;
uniform vec3 lightDirection;

void main()
{
	gl_FragColor = texture2D(diffuse, texCoord0) 
		* clamp(dot(-lightDirection, normal0), 0.0, 1.0);
}


