#ifndef _LIBGWINDOWER_H
#define _LIBGWINDOWER_H

class GWindower { private: bool opengl; bool _scrolled = false; bool _last_mouse_lock_state = false; public: ~GWindower(); void* _glfwWindow;  // for interoperability (e.g. Dear ImGui's GLFW backend)
        static int GetScreenWidth(); static int GetScreenHeight(); static int GetScreenRefreshRate();

        void* native_window_handle; // Win32 HWND / Wayland wl_surface*
        void* native_wayland_display = nullptr;  // NULL on Windows
        GWindower(
                int window_width = 0, int window_height = 0,  // leave both at 0 for fullscreen
                int opengl_context_major = 0, int opengl_context_minor = 0  // leave both at 0 for no OpenGL context
        );

        bool input_states[372]; bool last_input_states[372];
        int cursor_x, cursor_y;
        int mouse_x_delta, mouse_y_delta;
        double mouse_scroll_delta;
        float gamepad_axes[6];  // GAMEPADAXIS_*
        int window_width, window_height;  // size of window's (non-decorated) drawing/framebuffer area
        bool Update(  // returns `false` if window should close
                bool locked_mouse = false,  // lock/unlock mouse/cursor to window (+ sets raw input on locked)
                bool sleep_until_input = false, double sleep_until_input_timeout = 0.0,
                bool opengl_vsync = false
        ) noexcept;

        enum { // Inputs
                // Keyboard
                KEY_SPACE = 32,
                KEY_APOSTROPHE = 39,  /* ' */
                KEY_COMMA = 44,  /* , */
                KEY_MINUS = 45,  /* - */
                KEY_PERIOD = 46,  /* . */
                KEY_SLASH = 47,  /* / */
                KEY_ZERO = 48,
                KEY_ONE = 49,
                KEY_TWO = 50,
                KEY_THREE = 51,
                KEY_FOUR = 52,
                KEY_FIVE = 53,
                KEY_SIX = 54,
                KEY_SEVEN = 55,
                KEY_EIGHT = 56,
                KEY_NINE = 57,
                KEY_SEMICOLON = 59,  /* ; */
                KEY_EQUAL = 61,  /* = */
                KEY_A = 65,
                KEY_B = 66,
                KEY_C = 67,
                KEY_D = 68,
                KEY_E = 69,
                KEY_F = 70,
                KEY_G = 71,
                KEY_H = 72,
                KEY_I = 73,
                KEY_J = 74,
                KEY_K = 75,
                KEY_L = 76,
                KEY_M = 77,
                KEY_N = 78,
                KEY_O = 79,
                KEY_P = 80,
                KEY_Q = 81,
                KEY_R = 82,
                KEY_S = 83,
                KEY_T = 84,
                KEY_U = 85,
                KEY_V = 86,
                KEY_W = 87,
                KEY_X = 88,
                KEY_Y = 89,
                KEY_Z = 90,
                KEY_LEFT_BRACKET = 91,  /* [ */
                KEY_BACKSLASH = 92,  /* \ */
                KEY_RIGHT_BRACKET = 93,  /* ] */
                KEY_GRAVE_ACCENT = 96,  /* ` */
                KEY_WORLD_1 = 161,  /* non-US #1 */
                KEY_WORLD_2 = 162,  /* non-US #2 */
                KEY_ESCAPE = 256,
                KEY_ENTER = 257,
                KEY_TAB = 258,
                KEY_BACKSPACE = 259,
                KEY_INSERT = 260,
                KEY_DELETE = 261,
                KEY_RIGHT = 262,
                KEY_LEFT = 263,
                KEY_DOWN = 264,
                KEY_UP = 265,
                KEY_PAGE_UP = 266,
                KEY_PAGE_DOWN = 267,
                KEY_HOME = 268,
                KEY_END = 269,
                KEY_CAPS_LOCK = 280,
                KEY_SCROLL_LOCK = 281,
                KEY_NUM_LOCK = 282,
                KEY_PRINT_SCREEN = 283,
                KEY_PAUSE = 284,
                KEY_F1 = 290,
                KEY_F2 = 291,
                KEY_F3 = 292,
                KEY_F4 = 293,
                KEY_F5 = 294,
                KEY_F6 = 295,
                KEY_F7 = 296,
                KEY_F8 = 297,
                KEY_F9 = 298,
                KEY_F10 = 299,
                KEY_F11 = 300,
                KEY_F12 = 301,
                KEY_F13 = 302,
                KEY_F14 = 303,
                KEY_F15 = 304,
                KEY_F16 = 305,
                KEY_F17 = 306,
                KEY_F18 = 307,
                KEY_F19 = 308,
                KEY_F20 = 309,
                KEY_F21 = 310,
                KEY_F22 = 311,
                KEY_F23 = 312,
                KEY_F24 = 313,
                KEY_F25 = 314,
                KEY_KP_0 = 320,
                KEY_KP_1 = 321,
                KEY_KP_2 = 322,
                KEY_KP_3 = 323,
                KEY_KP_4 = 324,
                KEY_KP_5 = 325,
                KEY_KP_6 = 326,
                KEY_KP_7 = 327,
                KEY_KP_8 = 328,
                KEY_KP_9 = 329,
                KEY_KP_DECIMAL = 330,
                KEY_KP_DIVIDE = 331,
                KEY_KP_MULTIPLY = 332,
                KEY_KP_SUBTRACT = 333,
                KEY_KP_ADD = 334,
                KEY_KP_ENTER = 335,
                KEY_KP_EQUAL = 336,
                KEY_LEFT_SHIFT = 340,
                KEY_LEFT_CONTROL = 341,
                KEY_LEFT_ALT = 342,
                KEY_LEFT_SUPER = 343,
                KEY_RIGHT_SHIFT = 344,
                KEY_RIGHT_CONTROL = 345,
                KEY_RIGHT_ALT = 346,
                KEY_RIGHT_SUPER = 347,
                KEY_MENU = 348,

                // Mouse
                MOUSEBUTTON_LEFT,
                MOUSEBUTTON_RIGHT,
                MOUSEBUTTON_MIDDLE,
                MOUSEBUTTON_FOUR,
                MOUSEBUTTON_FIVE,
                MOUSEBUTTON_SIX,
                MOUSEBUTTON_SEVEN,
                MOUSEBUTTON_EIGHT,

                // Gamepad buttons
                GAMEPADBUTTON_A,
                GAMEPADBUTTON_B,
                GAMEPADBUTTON_X,
                GAMEPADBUTTON_Y,
                GAMEPADBUTTON_LEFT_BUMPER,
                GAMEPADBUTTON_RIGHT_BUMPER,
                GAMEPADBUTTON_BACK,
                GAMEPADBUTTON_START,
                GAMEPADBUTTON_GUIDE,
                GAMEPADBUTTON_LEFT_THUMB,
                GAMEPADBUTTON_RIGHT_THUMB,
                GAMEPADBUTTON_DPAD_UP,
                GAMEPADBUTTON_DPAD_RIGHT,
                GAMEPADBUTTON_DPAD_DOWN,
                GAMEPADBUTTON_DPAD_LEFT,

                _input_last,

                // Aliases

                GAMEPADBUTTON_CROSS = GAMEPADBUTTON_A,
                GAMEPADBUTTON_CIRCLE = GAMEPADBUTTON_B,
                GAMEPADBUTTON_SQUARE = GAMEPADBUTTON_X,
                GAMEPADBUTTON_TRIANGLE = GAMEPADBUTTON_Y,
        };
        enum { // Gamepad axes
                GAMEPADAXIS_LEFT_X,
                GAMEPADAXIS_LEFT_Y,
                GAMEPADAXIS_RIGHT_X,
                GAMEPADAXIS_RIGHT_Y,
                GAMEPADAXIS_LEFT_TRIGGER,
                GAMEPADAXIS_RIGHT_TRIGGER
        };
};

#endif // _LIBGWINDOWER_H