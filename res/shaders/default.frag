#version 330 core

in vec4 Color;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D theTexture;

void main()
{
    // FragColor = vec4(1.0, 1.0, 1.0, 1.0);

    
    if (TexCoord.x == -1 || TexCoord.y == -1) {
        FragColor = Color;
    } else {
        FragColor = texture(theTexture, TexCoord) * Color;
    }
}
