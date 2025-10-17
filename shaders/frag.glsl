#version 330 core
out vec4 FragColor;

in vec3 position;

void main()
{
    FragColor = vec4(abs(position.x)*10, abs(position.y), abs(position.z), 1.0f);
} 