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


int GWindower::GetScreenWidth() {
        const GLFWvidmode* video_mode = glfwGetVideoMode(glfwGetPrimaryMonitor()); if (video_mode == NULL) ERROR("Failed to get primary monitor's video mode");
        return video_mode->width;
}
int GWindower::GetScreenHeight() {
        const GLFWvidmode* video_mode = glfwGetVideoMode(glfwGetPrimaryMonitor()); if (video_mode == NULL) ERROR("Failed to get primary monitor's video mode");
        return video_mode->height;
}
int GWindower::GetScreenRefreshRate() {
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

        glfwSetWindowUserPointer((GLFWwindow*)_glfwWindow, this);

        #ifdef _WIN32
                this->native_window_handle = (void*)glfwGetWin32Window((GLFWwindow*)_glfwWindow); if (this->native_window_handle == NULL) ERROR("Failed to get native window handle (Win32 HWND)");
        #else
                this->native_window_handle = (void*)glfwGetWaylandWindow((GLFWwindow*)_glfwWindow); if (this->native_window_handle == NULL) ERROR("Failed to get native window handle (Wayland wl_surface*)");
                this->native_wayland_display = (void*)glfwGetWaylandDisplay(); if (this->native_wayland_display == NULL) ERROR("Failed to get native wl_display*");
        #endif

        if (opengl) { glfwMakeContextCurrent((GLFWwindow*)_glfwWindow); }

        memset(key_states, false, (sizeof(key_states) / sizeof(key_states[0])));
        mouse_x = 0; mouse_y = 0;
        memset(mouse_button_states, false, (sizeof(mouse_button_states) / sizeof(mouse_button_states[0])));
        mouse_scroll_delta = 0.0;
        memset(gamepad_button_states, false, (sizeof(gamepad_button_states) / sizeof(gamepad_button_states[0])));
        memset(gamepad_axes, 0.0, (sizeof(gamepad_axes) / sizeof(gamepad_axes[0])));

        if (fullscreen) locked_mouse = true;
        else locked_mouse = false;
        _last_mouse_lock_state = locked_mouse;

        glfwSetKeyCallback((GLFWwindow*)_glfwWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods){
                ((GWindower*)glfwGetWindowUserPointer(window))->key_states[key] = (action != GLFW_RELEASE);
        });

        glfwSetMouseButtonCallback((GLFWwindow*)_glfwWindow, [](GLFWwindow* window, int button, int action, int mods){
                ((GWindower*)glfwGetWindowUserPointer(window))->mouse_button_states[button] = (action != GLFW_RELEASE);
        });

        glfwSetScrollCallback((GLFWwindow*)_glfwWindow, [](GLFWwindow* window, double xoffset, double yoffset){
                ((GWindower*)glfwGetWindowUserPointer(window))->mouse_scroll_delta = yoffset;
                ((GWindower*)glfwGetWindowUserPointer(window))->_scrolled = true;
        });
}

bool GWindower::Update(
        bool sleep_until_input, double sleep_until_input_timeout,
        bool opengl_vsync
) noexcept {
        glfwGetFramebufferSize((GLFWwindow*)_glfwWindow, &window_width, &window_height);

        if (opengl) { glfwSwapInterval(opengl_vsync); glfwSwapBuffers((GLFWwindow*)_glfwWindow); }

        if (_scrolled) { _scrolled = false; mouse_scroll_delta = 0.0; }  // prevent scroll data from "sticking"

        if (_last_mouse_lock_state != locked_mouse) { _last_mouse_lock_state = locked_mouse;
                if (locked_mouse) {
                        glfwSetCursorPos((GLFWwindow*)_glfwWindow, 0.0, this->window_height/2.0);  // (to prevent jerking/snapping)
                        glfwSetInputMode((GLFWwindow*)_glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED); if (glfwRawMouseMotionSupported()) glfwSetInputMode((GLFWwindow*)_glfwWindow, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
                        glfwSetCursorPos((GLFWwindow*)_glfwWindow, 0.0, this->window_height/2.0);  // (to prevent jerking/snapping)
                }
                else { glfwSetInputMode((GLFWwindow*)_glfwWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL); }
        }

        if (sleep_until_input) {
                if (sleep_until_input_timeout != 0.0) { glfwWaitEventsTimeout(sleep_until_input_timeout); }
                else { glfwWaitEvents(); }
        }
        else { glfwPollEvents(); }

        double xpos = 0, ypos = 0;
        glfwGetCursorPos((GLFWwindow*)_glfwWindow, &xpos, &ypos);
        this->mouse_x = (int)xpos; this->mouse_y = (int)ypos;
        if (locked_mouse) { glfwSetCursorPos((GLFWwindow*)_glfwWindow, 0.0, 0.0); }  // so there is zero precision loss going from doubles to ints

        for (int j = 0; j < GLFW_JOYSTICK_LAST; j++) {
                if (!glfwJoystickIsGamepad(j)) continue;
                GLFWgamepadstate gamepad_state;
                if (!glfwGetGamepadState(j, &gamepad_state)) continue;
                for (int b = 0; b < GLFW_GAMEPAD_BUTTON_LAST; b++) { gamepad_button_states[b] = (gamepad_state.buttons[b] != GLFW_RELEASE); }
                for (int a = 0; a < GLFW_GAMEPAD_AXIS_LAST; a++) { gamepad_axes[a] = gamepad_state.axes[a]; }
                break;
        }

        return !glfwWindowShouldClose((GLFWwindow*)_glfwWindow);
}

GWindower::~GWindower() { glfwTerminate(); }