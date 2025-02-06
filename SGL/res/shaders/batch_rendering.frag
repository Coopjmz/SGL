#version 460 core

in vec4 v_Color;
in vec2 v_TexCoords;
in float v_TexIndex;

uniform sampler2D u_Textures[32];

out vec4 o_Color;

void main()
{
	if (v_TexIndex >= 0)
		o_Color = texture(u_Textures[int(v_TexIndex)], v_TexCoords);
	else
		o_Color = v_Color;
};