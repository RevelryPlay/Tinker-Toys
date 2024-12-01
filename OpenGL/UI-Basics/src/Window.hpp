#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

constexpr int DEFAULT_WINDOW_WIDTH = 1024;
constexpr int DEFAULT_WINDOW_HEIGHT = 1024;
const auto DEFAULT_WINDOW_TITLE = "New Window";

class Window {
public:
    Window();

    explicit Window(const char *title);

    Window(const char *title, int width, int height);

    ~Window();

    void update();

    static void processInput(GLFWwindow *window, int key, int scancode, int action, int mods);

    void handleKeyboardInput(int key, int scancode, int action, int mods);

    void handleMouseInput(int button, int action, int mods);

    void handleMouseMovement(double xpos, double ypos);

    void handleMouseScroll(double xoffset, double yoffset);

    void handleFramebufferResize(int width, int height);

    void handleWindowResize(GLFWwindow *, int width, int height);

    void handleWindowClose();

    void setWindowShouldClose(bool shouldClose);

    void setWindowWidth(int width);

    void setWindowHeight(int height);

    void setWindowTitle(const char *title);

    [[nodiscard]] bool shouldClose() const { return windowShouldClose; }

private:
    GLFWwindow *window{nullptr};

    int windowWidth = DEFAULT_WINDOW_WIDTH;
    int windowHeight = DEFAULT_WINDOW_HEIGHT;
    const char *windowTitle = DEFAULT_WINDOW_TITLE;

    bool windowShouldClose = false;

    void glfwSetFramebufferSizeCallback(GLFWwindow *window, GLFWframebuffersizefun callback);

    int createGLFWWindow();
};
