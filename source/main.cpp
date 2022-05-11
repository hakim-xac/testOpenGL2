#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>


GLfloat point[]{
    0.0f, 0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
};
GLfloat color[]{
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f,
};








void glfwWindowSizeCallback(GLFWwindow* pWindow, int width, int height) {
    glViewport(0, 0, width, height);
}


void processInput(GLFWwindow* pWindow) {
    if (glfwGetKey(pWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(pWindow, true);
    }
}

int main(void)
{

    /* Initialize the library */
    if (!glfwInit()) {
        std::cout << "glfwInit() == false";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* pWindow{ glfwCreateWindow(640, 480, "TEST OPENGL", nullptr, nullptr) };

    if (!pWindow)
    {
        std::cout << "pWindow == nullptr";
        glfwTerminate();
        return -1;
    }

    glfwSetWindowSizeCallback(pWindow, glfwWindowSizeCallback);

    /* Make the window's context current */
    glfwMakeContextCurrent(pWindow);
	
	if(!gladLoadGL()){
		std::cout << "Can't load GLAD!" << std::endl;
		return -1;
	}
	
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "OpenGl version: " << glGetString(GL_VERSION) << std::endl;

	glClearColor(0.3f, 0.3f, 0.5f, 1);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(pWindow))
    {
        processInput(pWindow);
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(pWindow);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}