#pragma once

class GWindower { private: bool fullscreen; bool opengl; public: ~GWindower(); void* _glfwWindow;  // for interoperability (e.g. Dear ImGui's GLFW backend)
        static inline int GetScreenWidth(); static inline int GetScreenHeight();
        static inline int GetScreenRefreshRate();

        void* native_window_handle; // Win32 HWND / Wayland wl_surface*
        void* native_wayland_display = nullptr;  // NULL on Windows
        GWindower(
                int window_width = 0, int window_height = 0,  // leave both at 0 for fullscreen
                int opengl_context_major = 0, int opengl_context_minor = 0  // leave both at 0 for no OpenGL context
        );

        bool key_states[349];  // GWindower::Key - `true` = pressed
        int mouse_x, mouse_y;  // delta in fullscreen, absolute in windowed
        bool mouse_button_states[8];  // GWindower::MouseButton - `true` = pressed
        bool gamepad_button_states[15];  // GWindower::GamepadButton - `true` = pressed
        float gamepad_axes[6];  // GWindower::GamepadAxis
        int window_width, window_height;  // size of window's non-decorated drawing/framebuffer area
        bool Update(  // returns `false` if window should close
                bool sleep_until_input = false, double sleep_until_input_timeout = 0.0,
                bool opengl_vsync = false
        ) noexcept;


        // Inputs

        enum class Key {
                SPACE = 32,
                APOSTROPHE = 39,  /* ' */
                COMMA = 44,  /* , */
                MINUS = 45,  /* - */
                PERIOD = 46,  /* . */
                SLASH = 47,  /* / */
                ZERO = 48,
                ONE = 49,
                TWO = 50,
                THREE = 51,
                FOUR = 52,
                FIVE = 53,
                SIX = 54,
                SEVEN = 55,
                EIGHT = 56,
                NINE = 57,
                SEMICOLON = 59,  /* ; */
                EQUAL = 61,  /* = */
                A = 65,
                B = 66,
                C = 67,
                D = 68,
                E = 69,
                F = 70,
                G = 71,
                H = 72,
                I = 73,
                J = 74,
                K = 75,
                L = 76,
                M = 77,
                N = 78,
                O = 79,
                P = 80,
                Q = 81,
                R = 82,
                S = 83,
                T = 84,
                U = 85,
                V = 86,
                W = 87,
                X = 88,
                Y = 89,
                Z = 90,
                LEFT_BRACKET = 91,  /* [ */
                BACKSLASH = 92,  /* \ */
                RIGHT_BRACKET = 93,  /* ] */
                GRAVE_ACCENT = 96,  /* ` */
                WORLD_1 = 161,  /* non-US #1 */
                WORLD_2 = 162,  /* non-US #2 */
                ESCAPE = 256,
                ENTER = 257,
                TAB = 258,
                BACKSPACE = 259,
                INSERT = 260,
                DELETE = 261,
                RIGHT = 262,
                LEFT = 263,
                DOWN = 264,
                UP = 265,
                PAGE_UP = 266,
                PAGE_DOWN = 267,
                HOME = 268,
                END = 269,
                CAPS_LOCK = 280,
                SCROLL_LOCK = 281,
                NUM_LOCK = 282,
                PRINT_SCREEN = 283,
                PAUSE = 284,
                F1 = 290,
                F2 = 291,
                F3 = 292,
                F4 = 293,
                F5 = 294,
                F6 = 295,
                F7 = 296,
                F8 = 297,
                F9 = 298,
                F10 = 299,
                F11 = 300,
                F12 = 301,
                F13 = 302,
                F14 = 303,
                F15 = 304,
                F16 = 305,
                F17 = 306,
                F18 = 307,
                F19 = 308,
                F20 = 309,
                F21 = 310,
                F22 = 311,
                F23 = 312,
                F24 = 313,
                F25 = 314,
                KP_0 = 320,
                KP_1 = 321,
                KP_2 = 322,
                KP_3 = 323,
                KP_4 = 324,
                KP_5 = 325,
                KP_6 = 326,
                KP_7 = 327,
                KP_8 = 328,
                KP_9 = 329,
                KP_DECIMAL = 330,
                KP_DIVIDE = 331,
                KP_MULTIPLY = 332,
                KP_SUBTRACT = 333,
                KP_ADD = 334,
                KP_ENTER = 335,
                KP_EQUAL = 336,
                LEFT_SHIFT = 340,
                LEFT_CONTROL = 341,
                LEFT_ALT = 342,
                LEFT_SUPER = 343,
                RIGHT_SHIFT = 344,
                RIGHT_CONTROL = 345,
                RIGHT_ALT = 346,
                RIGHT_SUPER = 347,
                MENU = 348,
                LAST = MENU  //
        };

        enum class MouseButton {
                LEFT = 0,
                RIGHT = 1,
                MIDDLE = 2,
                FOUR = 3,
                FIVE = 4,
                SIX = 5,
                SEVEN = 6,
                EIGHT = 7,
                LAST = EIGHT  //
        };

        enum class GamepadButton {
                A = 0,
                B = 1,
                X = 2,
                Y = 3,
                LEFT_BUMPER = 4,
                RIGHT_BUMPER = 5,
                BACK = 6,
                START = 7,
                GUIDE = 8,
                LEFT_THUMB = 9,
                RIGHT_THUMB = 10,
                DPAD_UP = 11,
                DPAD_RIGHT = 12,
                DPAD_DOWN = 13,
                DPAD_LEFT = 14,
                LAST = DPAD_LEFT,  //

                CROSS = A,
                CIRCLE = B,
                SQUARE = X,
                TRIANGLE = Y
        };
        enum class GamepadAxis {
                LEFT_X,
                LEFT_Y,
                RIGHT_X,
                RIGHT_Y,
                LEFT_TRIGGER,
                RIGHT_TRIGGER,
                LAST = RIGHT_TRIGGER  //
        };
};