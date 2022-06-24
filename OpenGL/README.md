# OpenGL
This part of the [C++](https://github.com/scooobs/CPP) repo is going to contain all my progress as I work through [LearnOpenGL](https://learnopengl.com). The goal of this was to get better at C++ and also learn about rendering. Maybe at the end I will have enough knowledge to create some rudimentary game engine.

## Things I Ran Into

##### Installing GLFW and GLAD... fine but where do I put them?
I used `brew` to install GLFW and used the [webservice](https://glad.dav1d.de/) to install GLAD. On my machine I put these files to be put inside `/usr/local/` this is because Homebrew decided this is where it will be storing GLFW.
##### GLFW/GLAD/(...insert others here) headers not found.
I am using nvim and clangd, so I needed to be sure I got my nice autocompletions. To do so, make sure within your `.zshrc` (or perhaps your bash profile you set your `CPATH` and `LIBRARY_PATH`. For example if like me you are not _currently_ on an M1 processor. Then you can set them to the following:

```sh
export CPATH="/usr/local/include/"
export LIBRARY_PATH="/usr/local/lib"
```
From here test compilation and if it still doesn't work, good luck scouring StackOverflow for solutions.
