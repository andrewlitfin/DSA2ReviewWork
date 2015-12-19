#version 420

in vec2 fragUV;
in vec3 L;
in vec3 E;
in vec3 H;
in vec3 N;
out vec4 fragColor;

uniform sampler2D uniformTex;

const float ambient = 0.9;
const float Kd = 0.8;
const float Ks = 0.8;
const float shininess = 16;

void main()
{
	float diffuse = Kd * dot(L, N);
	float specular = Ks * pow(dot(H, N), shininess);
	float brightness = ambient + diffuse + specular;
	vec4 color = texture(uniformTex, fragUV);
	fragColor = vec4(color.rgb * brightness, 1);
}