#version 420

layout (location = 0) in vec3 vertPos;
layout (location = 1) in vec2 vertTexUV;
layout (location = 2) in vec3 vertNorm;
out vec2 fragUV;
out vec3 L;
out vec3 E;
out vec3 H;
out vec3 N;

uniform mat4 worldMatrix;
uniform mat4 cameraMatrix;
uniform vec3 eye;
uniform vec3 light;

void main()
{
	fragUV = vertTexUV;

	vec4 worldPos = worldMatrix * vec4(vertPos, 1);
	vec3 point = worldPos.xyz;
	vec3 normal = (worldMatrix * vec4(vertNorm, 0)).xyz;
	L = normalize(light - point);
	E = normalize(eye - point);
	H = normalize(L + E);
	N = normalize(normal);

	gl_Position = cameraMatrix * worldPos;
}