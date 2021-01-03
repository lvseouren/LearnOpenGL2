#version 330 core
out vec4 fragColor;
in vec4 ourColor;
in vec2 texCoord;

uniform sampler2D ourTexture;

void main()
{
    fragColor = texture(ourTexture, texCoord);
}