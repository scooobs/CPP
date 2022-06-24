# Shader Changes (still bad)

### What?
This program will render two Triangles to the screen of different colours using seperate Fragment Shaders, VBOs (Vertex Buffer Objects) and VAOs (Vertex Array Objects). It then uses a uniform value in the Fragment Shader GLSL to update the colour of the bottom triangle each frame. This is still bad as we want to be able to allow every vertex be a different colour, but $\vert\text{V}\vert = \vert\text{U}\vert$ is inefficient. Here $\text{V}$ denotes the set of Vertices and $\text{U}$ the set of Uniforms. We can fix this by adding extra attributes to the input vertex data. See the next [Shader Change](https://github.com/scooobs/CPP/OpenGL/ShaderChangesTwo) for this.
### How to Compile

`g++ -o shaderchanges shaderchanges.cpp ../glad/glad.c -lglfw -ldl -std=c++17`

### How to Run

`./shaderchanges`

