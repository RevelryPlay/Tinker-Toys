
#include "Window.hpp"

Window::Window() {
    createGLFWWindow();
}

Window::Window(const char *title) {
    windowTitle = title;

    createGLFWWindow();
}

Window::Window(const char *title, const int width, const int height) {
    windowTitle = title;
    windowWidth = width;
    windowHeight = height;

    createGLFWWindow();
}

Window::~Window() {
    if (&window != nullptr) {
        glfwDestroyWindow(window);
    }

    glfwTerminate();
}

void Window::update() {
    if (glfwWindowShouldClose(window)) {
        windowShouldClose = true;
        return;
    }

    constexpr GLfloat color[] = {0.2f, 0.3f, 0.3f, 1.0f};
    glClearColor(color[0], color[1], color[2], color[3]);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Window::processInput(GLFWwindow *window, int key, int scancode, int action, int mods) {
    const auto windowPtr = static_cast<Window *>(glfwGetWindowUserPointer(window));
    windowPtr->handleKeyboardInput(key, scancode, action, mods);
}

void Window::handleKeyboardInput(int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        switch (key) {
            case GLFW_KEY_W:
                // Move camera forward
                break;
            case GLFW_KEY_S:
                // Move camera backward
                break;
            case GLFW_KEY_A:
                // Move camera left
                break;
            case GLFW_KEY_D:
                // Move camera right
                break;
            case GLFW_KEY_Q:
                // Move camera up
                break;
            case GLFW_KEY_E:
                // Move camera down
                break;
            case GLFW_KEY_ESCAPE:
                windowShouldClose = true;
                break;
            default:
                break;
        }
    }
}

void Window::handleMouseInput(int button, int action, int mods) {
}

void Window::handleMouseMovement(double xpos, double ypos) {
}

void Window::handleMouseScroll(double xoffset, double yoffset) {
}

void Window::handleFramebufferResize(int width, int height) {
    glViewport(0, 0, width, height);
}

void Window::handleWindowResize(GLFWwindow * /*window*/, int width, int height) {
    glViewport(0, 0, width, height);
}

void Window::handleWindowClose() {
    windowShouldClose = true;
}

void Window::setWindowShouldClose(bool shouldClose) {
    windowShouldClose = shouldClose;
}

void Window::setWindowWidth(int width) {
    glfwSetWindowSize(window, width, windowHeight);
}

void Window::setWindowHeight(int height) {
    glfwSetWindowSize(window, windowWidth, height);
}

void Window::setWindowTitle(const char *title) {
    glfwSetWindowTitle(window, title);
}

int Window::createGLFWWindow() {
    if (glfwInit() == 0) {
        throw std::runtime_error("Failed to initialize GLFW");
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window = glfwCreateWindow(
        windowWidth,
        windowHeight,
        windowTitle,
        nullptr,
        nullptr
    );

    glfwMakeContextCurrent(window);

    if (gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)) == 0) {
        throw std::runtime_error("Failed to initialize GLAD");
        return -1;
    }

    if (window == nullptr) {
        throw std::runtime_error("Failed to create GLFW window");
        glfwTerminate();
        return -1;
    }

    // glfwSetFramebufferSizeCallback(window, handleFramebufferResize);
    // glfwSetWindowSizeCallback(window, handleWindowResize);
    // glfwSetWindowCloseCallback(window, handleWindowClose);
    glfwSetKeyCallback(window, processInput);
    // glfwSetMouseButtonCallback(window, handleMouseInput);
    // glfwSetCursorPosCallback(window, handleMouseMovement);
    // glfwSetScrollCallback(window, handleMouseScroll);

    glfwSetWindowUserPointer(window, this);
    return 0;
}
