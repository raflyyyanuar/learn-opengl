#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstdio>

// A callback function that gets called whenever the window is resized
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow* window);

int main() {
	glfwInit();

	// Initialize GLFW window (https://www.glfw.org/docs/latest/window.html#window_hints)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // MacOS only

	GLFWwindow* window = glfwCreateWindow(800, 600, "Learn OpenGL", NULL, NULL);
	if (window == NULL) {
		printf("Failed to create GLFW window\n");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	// Initialize GLAD to manage function pointers for OpenGL
	// before calling any OpenGL function
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		glfwTerminate();
		printf("Failed to initialize GLAD\n");
		return -1;
	}

	// Setup Viewport
	glViewport(0, 0, 800, 600);

	// Register callback functions AFTER the window is created and BEFORE the render loop is initiated
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Clear the screen with a color of our choice
	glClearColor(1.0, 0.0, 0.0, 0.0);
	
	// This is the render loop
	while (!glfwWindowShouldClose(window)) {
		// input
		processInput(window);

		// rendering
		glClear(GL_COLOR_BUFFER_BIT);


		// check and call events and swap the buffers
		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	printf("Window got resized!\n");
	glViewport(0, 0, width, height);
}


void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

