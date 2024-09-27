#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstdio>
#include <cmath>

// A callback function that gets called whenever the window is resized
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char* vertexShaderSource =
"#version 330 core\n"
"layout (location = 0) in vec3 pos;\n"
"void main() {\n"
"gl_Position = vec4(pos, 1.0);\n"
"}\0"
;

const char* fragmentShaderSource =
"#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 ourColor;"
"void main() {\n"
"FragColor = ourColor;\n"
"}\0"
;

int main() {
	glfwInit();

	// Initialize GLFW window (https://www.glfw.org/docs/latest/window.html#window_hints)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Learn OpenGL", NULL, NULL);
	if (window == NULL) {
		printf("Failed to create GLFW window\n");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	// Register callback functions AFTER the window is created and BEFORE the render loop is initiated
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Initialize GLAD to manage function pointers for OpenGL
	// before calling any OpenGL function
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		glfwTerminate();
		printf("Failed to initialize GLAD\n");
		return -1;
	}


	// build and compile vertex shader
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// check for compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED:\n%s\n", infoLog);
		return -1;
	}

	// build and compile fragment shader
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// check for compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED:\n%s\n", infoLog);
		return -1;
	}

	// Link vertex and fragment shaders
	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glLinkProgram(shaderProgram);

	// check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		printf("ERROR::SHADER::PROGRAM::LINKING_FAILD:\n%s\n", infoLog);
		return -1;
	}

	// delete shaders as they are not used anymore
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Setup vertex data
	float vertices[] = {
		-0.5f, -0.5f, 0.0f, // left
		 0.5f, -0.5f, 0.0f, // right
		 0.0f,  0.5f, 0.0f, // top
	};

	// setup buffers
	unsigned int VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// bind VAO first
	glBindVertexArray(VAO);

	// then bind VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// GL_STATIC_DRAW = vertices set once, used many times

	// setup vertex attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// 0 is the layout location defined in vertexShaderSource

	// unbind VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// unbind VAO
	glBindVertexArray(0);

	// Set screen clear color to the color of our choice
	glClearColor(1.0, 1.0, 1.0, 1.0);

	// uncomment this call to draw in wireframe polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// This is the render loop
	while (!glfwWindowShouldClose(window)) {
		// input
		processInput(window);

		// rendering
		glClear(GL_COLOR_BUFFER_BIT);

		// Modify the uniform ourColor variable in the fragment shader
		float timeValue = glfwGetTime();
		float redValue = roundf((sin(5.0f * timeValue) / 2.0f) + 0.5f);
		int ourColorLocation = glGetUniformLocation(shaderProgram, "ourColor");

		// draw our first triangle
		glUseProgram(shaderProgram);
		glUniform4f(ourColorLocation, redValue, 0.0, 0.0, 1.0);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);


		// check and call events and swap the buffers
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	// delete all used resources
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	//printf("Window got resized!\n");
	glViewport(0, 0, width, height);
}


void processInput(GLFWwindow* window) {
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}
