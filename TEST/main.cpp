#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback([[maybe_unused]] GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}


int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Example", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // Kolor tła (ciemny turkus)
        glClear(GL_COLOR_BUFFER_BIT);

        // Rysowanie prostokąta
        glBegin(GL_QUADS); // Rozpoczynamy rysowanie czworokąta
        glColor3f(1.0f, 0.0f, 0.0f); // Czerwony kolor
        glVertex2f(-0.5f, -0.5f);    // Dolny lewy wierzchołek
        glVertex2f(0.5f, -0.5f);     // Dolny prawy wierzchołek
        glVertex2f(0.5f, 0.5f);      // Górny prawy wierzchołek
        glVertex2f(-0.5f, 0.5f);     // Górny lewy wierzchołek
        glEnd(); // Zakończenie rysowania

        glfwSwapBuffers(window);    // Wyświetlenie narysowanego obrazu
        glfwPollEvents();           // Przetwarzanie zdarzeń
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
