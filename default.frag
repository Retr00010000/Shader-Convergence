#version 460 core

// Outputs colors in RGBA
out vec4 FragColor;


// Inputs the color from the Vertex Shader
in vec3 color;

void main()
{
// Outputs the color of the pixel 
FragColor = vec4(color, 1.0f);
}
