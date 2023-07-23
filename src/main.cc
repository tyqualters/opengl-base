/**
 * @file main.cc
 * @author 
 * @brief Entry point of your application
 * @version 0.1
 * @date 2023-07-23
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <iostream>
#include <format> // C++20
#include <cstdlib>
#include <stdexcept>
#include <vector>

#include "glad/glad.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "cube.hh"

// This example wrapper for Window is based on SDL2
class Window {
public:
    Window() {
        // Initialize SDL2
        if(SDL_WasInit(SDL_INIT_EVERYTHING) != SDL_INIT_EVERYTHING) {
            if(SDL_Init(SDL_INIT_EVERYTHING) < 0) throw std::runtime_error("Failed to initialize SDL."); 
        }

        // Create the Window
        const char* title = "Untitled window";
        
        int x = SDL_WINDOWPOS_CENTERED,
            y = SDL_WINDOWPOS_CENTERED;
        
        int w = 800, h = 600;

        Uint32 flags = SDL_WINDOW_OPENGL;

        auto& window = this->m_window;

        window = SDL_CreateWindow(title, x, y, w, h, flags);

        if(window == nullptr) throw std::runtime_error("Failed to create a window.");

        // Hardware acceleration
        if(SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1) < 0) throw std::runtime_error("Failed to set GL attribute.");
        // OpenGL 3.3 (forward compatible)
        if(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3) < 0) throw std::runtime_error("Failed to set GL attribute.");
        if(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3) < 0) throw std::runtime_error("Failed to set GL attribute.");
        if(SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE) < 0) throw std::runtime_error("Failed to set GL attribute.");
        if(SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG) < 0) throw std::runtime_error("Failed to set GL attribute.");
    
        // Load SDL's GL library
        if(SDL_GL_LoadLibrary(NULL) < 0) throw std::runtime_error("Failed to load the OpenGL library.");

        // Create the OpenGL context
        // Note: The underlying type of an SDL_GLContext is void*
        auto& context = this->m_context;

        if((context = SDL_GL_CreateContext(window)) == nullptr) throw std::runtime_error("Failed to initialize an OpenGL context.");

        // Bind GLAD to SDL/GL (will be different with GLEW)
        if(gladLoadGLLoader(SDL_GL_GetProcAddress) == 0) throw std::runtime_error("Failed to bind GLAD.");

        SDL_GL_MakeCurrent(window, context);

        // Debugging
        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(Window::_gl_message_callback, 0);
    }

    ~Window() {
        SDL_GL_DeleteContext(this->m_context);
        SDL_DestroyWindow(this->m_window);
        SDL_Quit();
    }

    static void GLAPIENTRY _gl_message_callback([[maybe_unused]] GLenum source, GLenum type, [[maybe_unused]] GLuint id, GLenum severity, [[maybe_unused]] GLsizei length, const GLchar* message, [[maybe_unused]] const void* userParam) {
        std::cerr << std::format("GL CALLBACK: {} type = 0x{}, severity = 0x{}, message = {}\n", (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""), type, severity, message);
    }

    const std::vector<SDL_Event>& poll() {
        this->m_events.clear();

        // Populate the events vector for future access until next poll
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) this->m_shouldClose = true;
            this->m_events.push_back(event);
        }

        // Go ahead and update the GL viewport
        int width, height;
        SDL_GetWindowSizeInPixels(this->m_window, &width, &height);
        glViewport(0, 0, width, height);

        return this->m_events;
    }

    inline bool should_close() {
        return this->m_shouldClose;
    }

    inline void swap() {
        SDL_GL_SwapWindow(this->m_window);
    }

private:
    SDL_Window* m_window = nullptr;
    SDL_GLContext m_context;
    bool m_shouldClose = false;
    std::vector<SDL_Event> m_events{};
};

int main(void) {
    Window window;
    Renderer renderer;

    Cube cube;

    cube.set_color_rgba(1.f, 0.f, 0.f); // set color

    cube.translate(-1.f, 1.f, -1.5f); // translate cube

    cube.get_wireframe_opt() = true; // turn on wireframe

    while(!window.should_close()) {
        window.poll();

        renderer.clear(); // clears buffer bit
        renderer.clear_color(0.f, 0.f, 0.f, 1.f); // background color

        cube.render(renderer);

        window.swap();
    }
    
    return EXIT_SUCCESS;
}