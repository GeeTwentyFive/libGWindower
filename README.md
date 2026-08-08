See `include/GWindower.hpp` for documentation


# Usage

```c++
GWindower gw{WIDTH, HEIGHT, GL_MAJOR, GL_MINOR};
while (gw.Update()) {  // If using OpenGL: `glViewport(0, 0, gw.window_width, gw.window_height); glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);`
        // ...
}
```
