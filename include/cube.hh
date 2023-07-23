#ifndef OBJ_CUBE_HH_
#define OBJ_CUBE_HH_

// Note: This is just an example for demonstrative purposes!

#include <cstdint>
#include <stdexcept>

#include "graphics.hh"
#include <glm/gtc/matrix_transform.hpp>

class Cube {
public:
    Cube(float aspect_ratio = 800.f / 600.f) : m_vbo(vertices, sizeof(vertices)), m_ibo(indices, sizeof(indices)) {
        auto shaderRes = Shader::from_files("shaders/cube.vert", "shaders/cube.frag");

        if(!shaderRes.has_value()) throw std::runtime_error("Could not load cube shaders.");

        std::unique_ptr<Shader> shader(shaderRes.value());

        this->m_program.import(*shader);

        BufferLayout layout;

        layout.add<float>(3); // This corresponds to the # of floats to be stored in location 0 (refer to cube.vert)

        this->m_vao.add_buf(this->m_vbo, layout);

        this->set_color_rgba(1.f, 1.f, 1.f);

        glm::mat4 projection = glm::perspective(45.0f, aspect_ratio, 1.0f, 150.0f); // aspect ratio, perspective

        glm::mat4 view = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, 0.f)); // position / orientation of camera

        this->m_view_proj = projection * view;

        glm::mat4 model = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, -3.f)); // position, rotation, scale of model

        model = glm::scale(model, glm::vec3(0.5f));

        glm::mat4 mvp = this->m_view_proj * model;

        this->m_program.set_uniform<glm::mat4>("u_MVP", &mvp);
    }

    inline void set_color_rgba(float r, float g, float b, float a = 1.f) {
        this->m_program.set_uniform<glm::vec4>("u_Color", {r, g, b, a});
    }

    void render(const Renderer&);

    inline bool& get_wireframe_opt() {
        return this->m_wireframe;
    }

    inline void translate(float x, float y, float z) {
        if(this->m_offset_x == x && this->m_offset_y == y && this->m_offset_z == z) return;
        
        this->m_offset_x = x;
        this->m_offset_y = y;
        this->m_offset_z = z;

        glm::mat4 model = glm::translate(glm::mat4(1.f), glm::vec3(x, y, z - 3.f)); // position, rotation, scale of model

        model = glm::scale(model, glm::vec3(0.5f));

        glm::mat4 mvp = this->m_view_proj * model;

        this->m_program.set_uniform<glm::mat4>("u_MVP", &mvp);
    }

private:
    Program m_program;
    VAO m_vao;
    VBO m_vbo;
    IBO m_ibo;

    glm::mat4 m_view_proj;

    float m_offset_x = 0.f, m_offset_y = 0.f, m_offset_z = 0.f;

    bool m_wireframe = false;

    // Continue off from here: https://www.youtube.com/watch?v=MXNMC1YAxVQ&list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2&index=9

    static constexpr float vertices[] = {
        -1.0f,-1.0f,-1.0f, //0
        -1.0f,-1.0f, 1.0f, //1
        -1.0f, 1.0f, 1.0f, //2
        1.0f, 1.0f,-1.0f, //3
        -1.0f,-1.0f,-1.0f, //4
        -1.0f, 1.0f,-1.0f, //5
        1.0f,-1.0f, 1.0f, //6
        -1.0f,-1.0f,-1.0f, //7
        1.0f,-1.0f,-1.0f, //8
        1.0f, 1.0f,-1.0f, //9
        1.0f,-1.0f,-1.0f, //10
        -1.0f,-1.0f,-1.0f, //11
        -1.0f,-1.0f,-1.0f, //12
        -1.0f, 1.0f, 1.0f, //13
        -1.0f, 1.0f,-1.0f, //14
        1.0f,-1.0f, 1.0f, //15
        -1.0f,-1.0f, 1.0f, //16
        -1.0f,-1.0f,-1.0f, //17
        -1.0f, 1.0f, 1.0f, //18
        -1.0f,-1.0f, 1.0f, //19
        1.0f,-1.0f, 1.0f, //20
        1.0f, 1.0f, 1.0f, //21
        1.0f,-1.0f,-1.0f, //22
        1.0f, 1.0f,-1.0f, //23
        1.0f,-1.0f,-1.0f, //24
        1.0f, 1.0f, 1.0f, //25
        1.0f,-1.0f, 1.0f, //26
        1.0f, 1.0f, 1.0f, //27
        1.0f, 1.0f,-1.0f, //28
        -1.0f, 1.0f,-1.0f, //29
        1.0f, 1.0f, 1.0f, //30
        -1.0f, 1.0f,-1.0f, //31
        -1.0f, 1.0f, 1.0f, //32
        1.0f, 1.0f, 1.0f, //33
        -1.0f, 1.0f, 1.0f, //34
        1.0f,-1.0f, 1.0f //35
    };

    static constexpr uint32_t indices[] = {
        0, 1, 2,
        3, 4, 5,
        6, 7, 8,
        9, 10, 11,
        12, 13, 14,
        15, 16, 17,
        18, 19, 20,
        21, 22, 23,
        24, 25, 26,
        27, 28, 29,
        30, 31, 32,
        33, 34, 35
    };
};

#endif