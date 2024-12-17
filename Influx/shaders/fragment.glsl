#version 450
#pragma shader_stage(fragment)

layout(location = 0) in vec3 o_FragColor;

layout(location = 0) out vec4 o_ScreenColor;

void main() {
    o_ScreenColor = vec4(o_FragColor, 1.0);
}