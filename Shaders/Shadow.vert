#version 450

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec4 inTangent;
layout(location = 3) in vec2 inTexCoord;

layout(push_constant) uniform Matrices
{
    mat4 model;
    mat4 viewProj;
} matrices;

void main()
{
    gl_Position = matrices.viewProj * matrices.model * vec4(inPosition, 1.0);
}