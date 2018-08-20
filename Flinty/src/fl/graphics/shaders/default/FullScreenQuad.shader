R"(
#shader vertex
#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 uv;

out DATA
{
	vec2 uv;
} vs_out;

void main()
{
	gl_Position = position;
	vs_out.uv = uv;
};

#shader fragment
#version 330 core

layout (location = 0) out vec4 color;

uniform sampler2D u_Texture;

in DATA
{
	vec2 uv;
} fs_in;

void main()
{
	color = texture(u_Texture, fs_in.uv);
};
)"