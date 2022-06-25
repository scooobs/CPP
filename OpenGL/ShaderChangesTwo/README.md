# Shader Changes Two (better)

### What?
This program will render two triangles with different colours for each vertex. This is done by including RGB data into the Vertex Buffer Objects (now each vertex is 6 floats, being the co-ords + RGB). We also now read in our GLSL files from disk and create an abstraction over our shaders using the Shader class.
### How to Compile

`g++ -o shaderchanges2 shaderchanges2.cpp ../glad/glad.c -lglfw -ldl -std=c++17`

### How to Run

`./shaderchanges2`

