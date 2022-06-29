#version 330 core

in vec4 Color;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D theTexture;
uniform bool isTextured;

void main()
{
    if (isTextured) {
        // TODO: Get textures working
        // FragColor = texture(theTexture, TexCoord) * Color;
    } else {
        FragColor = Color;
    }
}
