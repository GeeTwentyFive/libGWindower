#include <GWindower.hpp>

#include <GLFW/glfw3.h>
#ifdef _WIN32
#define GLFW_EXPOSE_NATIVE_WIN32
#else
#define GLFW_EXPOSE_NATIVE_WAYLAND
#endif
#include <GLFW/glfw3native.h>

#include <stdexcept>
#include <string>
#include <string.h>


#define ERROR(msg) throw std::runtime_error(std::string("[ERROR] ") + __FILE__ + "@" + std::to_string(__LINE__) + " (" + __func__ + "): " + (msg))


inline int GWindower::GetScreenWidth() {
        const GLFWvidmode* video_mode = glfwGetVideoMode(glfwGetPrimaryMonitor()); if (video_mode == NULL) ERROR("Failed to get primary monitor's video mode");
        return video_mode->width;
}
inline int GWindower::GetScreenHeight() {
        const GLFWvidmode* video_mode = glfwGetVideoMode(glfwGetPrimaryMonitor()); if (video_mode == NULL) ERROR("Failed to get primary monitor's video mode");
        return video_mode->height;
}
inline int GWindower::GetScreenRefreshRate() {
        const GLFWvidmode* video_mode = glfwGetVideoMode(glfwGetPrimaryMonitor()); if (video_mode == NULL) ERROR("Failed to get primary monitor's video mode");
        return video_mode->refreshRate;
}


GWindower::GWindower(
        int window_width, int window_height,
        int opengl_context_major, int opengl_context_minor
) {
        fullscreen = (window_width == 0);
        opengl = (opengl_context_major != 0);

        if (!glfwInit()) ERROR("Failed to initialize GLFW");

        GLFWmonitor* monitor = glfwGetPrimaryMonitor(); if (monitor == NULL) ERROR("Failed to get primary monitor");

        const GLFWvidmode* video_mode = glfwGetVideoMode(monitor); if (video_mode == NULL) ERROR("Failed to get primary monitor's video mode");

        glfwWindowHint(GLFW_RED_BITS, video_mode->redBits); glfwWindowHint(GLFW_GREEN_BITS, video_mode->greenBits); glfwWindowHint(GLFW_BLUE_BITS, video_mode->blueBits); glfwWindowHint(GLFW_REFRESH_RATE, video_mode->refreshRate);
        if (opengl) { glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API); glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, opengl_context_major); glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, opengl_context_minor); glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE); glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); }
        else { glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); }
        if (fullscreen) { _glfwWindow = glfwCreateWindow(video_mode->width, video_mode->height, "", monitor, NULL); }
        else { _glfwWindow = glfwCreateWindow(window_width, window_height, "", NULL, NULL); }
        if (_glfwWindow == NULL) ERROR(std::string("Failed to create window") + " (GLFW error code: " + std::to_string(glfwGetError(NULL)) + ")");

        // TODO
}

bool GWindower::Update(
        bool vsync,
        bool sleep_until_input, double sleep_until_input_timeout
) noexcept {
        // TODO
}

GWindower::~GWindower() {} // TODO