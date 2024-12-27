#version 450
#pragma shader_stage(fragment)

layout(location = 0) in vec3 o_VertexColor;
layout(location = 0) out vec4 o_ScreenColor;

void main(void)
{
    o_ScreenColor = vec4(o_VertexColor, 1.0);
}
