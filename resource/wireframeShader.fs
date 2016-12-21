#version 120

varying vec3 normal0;
uniform vec3 lightDirection;

void main()
{
	gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0)
		* clamp(dot(-lightDirection, normal0), 0.0, 1.0);
}


