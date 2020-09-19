#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 norm;
layout(location = 2) in vec4 color;
layout(location = 3) in vec2 texCoord;
layout(location = 4) in float texID;

out vec4 v_Color;
out vec2 v_TexCoord;
out float v_TexIndex;
out vec4 Normal;
out vec4 fragPos;

uniform mat4 u_MVP;
uniform mat4 model;

void main()
{
	gl_Position = u_MVP * model * position;
	v_TexCoord = texCoord;
	v_Color = color;
	v_TexIndex = texID;
	Normal = norm;
	fragPos = vec4(model * position);
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec4 v_Color;
in vec2 v_TexCoord;
flat in float v_TexIndex;
in vec4 Normal;
in vec4 fragPos;

uniform vec3 lightColor;
uniform sampler2D u_Texture;
uniform vec4 lightPos;

void main()
{
	vec4 norm = normalize(Normal);
	vec4 lightDir = normalize(lightPos - fragPos);

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	vec3 ambient = 0.5 * lightColor;
	
	vec3 final = ambient + diffuse;
	color = vec4(final, 1.0) * v_Color;
};