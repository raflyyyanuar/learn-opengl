#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstdio>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

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

		// check and call events and swap the buffers
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	//printf("Window got resized!\n");
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
		printf("Right mouse button was clicked!\n");
		glfwSetWindowShouldClose(window, true);
	}
}
