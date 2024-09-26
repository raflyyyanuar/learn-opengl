#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstdio>

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

const char* fragmentShaderSource1 =
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main() {\n"
"FragColor = vec4(0.3359375, 0.4375, 0.515625, 1.0);\n"
"}\0"
;

const char* fragmentShaderSource2 =
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main() {\n"
"FragColor = vec4(0.671875, 0.74609375, 0.75, 1.0);\n"
"}\0"
;

int main() {
	glfwInit();

	// Initialize GLFW window (https://www.glfw.org/docs/latest/window.html#window_hints)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Learn OpenGL", NULL, NULL);
	if (window == NULL) {
		printf("Failed to create GLFW window\n");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		glfwTerminate();
		printf("Failed to initialize GLAD\n");
		return -1;
	}

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED:\n%s\n", infoLog);
		return -1;
	}

	unsigned int fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader1, 1, &fragmentShaderSource1, NULL);
	glCompileShader(fragmentShader1);

	glGetShaderiv(fragmentShader1, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader1, 512, NULL, infoLog);
		printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED:\n%s\n", infoLog);
		return -1;
	}

	unsigned int fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, NULL);
	glCompileShader(fragmentShader2);

	glGetShaderiv(fragmentShader2, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader2, 512, NULL, infoLog);
		printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED:\n%s\n", infoLog);
		return -1;
	}

	unsigned int redShaderProgram = glCreateProgram();
	glAttachShader(redShaderProgram, vertexShader);
	glAttachShader(redShaderProgram, fragmentShader1);
	glLinkProgram(redShaderProgram);

	glGetProgramiv(redShaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(redShaderProgram, 512, NULL, infoLog);
		printf("ERROR::SHADER::PROGRAM::LINKING_FAILD:\n%s\n", infoLog);
		return -1;
	}

	unsigned int greenShaderProgram = glCreateProgram();
	glAttachShader(greenShaderProgram, vertexShader);
	glAttachShader(greenShaderProgram, fragmentShader2);
	glLinkProgram(greenShaderProgram);

	glGetProgramiv(greenShaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(greenShaderProgram, 512, NULL, infoLog);
		printf("ERROR::SHADER::PROGRAM::LINKING_FAILD:\n%s\n", infoLog);
		return -1;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader1);
	glDeleteShader(fragmentShader2);

	float triangle1[] = {
		// top triangle
		-0.5f,  0.1f, 0.0f, // left
		 0.5f,  0.1f, 0.0f, // right
		 0.0f,  0.85f, 0.0f, // top
	};

	float triangle2[] = {
		// bottom triangle
		-0.5f, -0.1f, 0.0f, // left
		 0.5f, -0.1f, 0.0f, // right
		 0.0f, -0.85f, 0.0f, // top
	};

	unsigned int VAO[2], VBO[2];
	
	glGenVertexArrays(2, VAO);
	glGenBuffers(2, VBO);

	glBindVertexArray(VAO[0]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle1), triangle1, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(VAO[1]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle2), triangle2, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		glClearColor(0.7890625, 0.5390625, 0.2890625, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(redShaderProgram);
		glBindVertexArray(VAO[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glUseProgram(greenShaderProgram);
		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(2, VAO);
	glDeleteBuffers(2, VBO);
	glDeleteProgram(redShaderProgram);
	glDeleteProgram(greenShaderProgram);
	
	glfwTerminate();

	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

