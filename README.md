# OpenGL-Base

A simple base for OpenGL projects.

Note: The following files are thirdparty. Please see their file contents for licensing.

    - cmake/FindGLM.cmake
    - cmake/FindSDL2.cmake
    - include/stb_image.h
    - include/KHR/khrplatform.h
    - include/glad/glad.h
    - src/glad.c

This base was based off of The Cherno's OpenGL series.

---

When developing with this base, keep in mind that you may want to modify shaders.hh to allow for more shaders than only 1 vertex and 1 fragment shader. You may also want the ability to parse shaders in a single file.

These files were pulled from another project of mine, and reflect as such. No additional modifications were made other than what was necessary to work in this environment.

The "Cube" class is meant to be an example. You probably should make your own objects a bit more dynamic and modular.

This project excluding all thirdparty additions is hereby released to the public domain.
