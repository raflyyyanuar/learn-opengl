# A Template for A Simple Hello Rectangle

This readme contains things that I think I should do in order to code a simple program that renders a rectangle.

In the global scope:
1. Include **GLAD** and **GLFW**
2. Create two function prototypes:
    1. A `framebuffer_size_callback` function that gets called whenever the window is resized
    2. A `processInput` function to check and use inputs from user
3. Define screen width and height constants
4. Define vertex and fragment shader sources

In the `main` function:
1. Call `glfwInit`
2. Set window hints:
    1. Context version (major and minor)
    2. OpenGL profile
3. Create a window and make it current
4. Register the `framebuffer_size_callback` function
5. Initialize **GLAD**
6. Build and compile vertex and fragment shaders
7. Link the shaders and make a shader program
8. Delete used shaders
9. Define vertices and indices arrays
10. Setup buffers:
    1. Generate VAO, VBO, and EBO
    2. Bind VAO, VBO, and EBO
    3. Setup vertex attribute
    4. Unbind VBO and VAO
11. Set clear color
12. Create a render loop:
    1. Call `processInput`
    2. Call `glClear`
    3. Use the built shader program
    4. Bind VAO
    5. Draw elements
    6. Poll events and swap buffers
13. Upon closing, delete buffers and the shader program
14. Call `glfwTerminate`

