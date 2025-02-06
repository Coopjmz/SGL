#version 460 core

in vec2 v_TexCoord;

uniform sampler2D u_Texture;

out vec4 o_Color;

void main()
{
	o_Color = texture(u_Texture, v_TexCoord);
};