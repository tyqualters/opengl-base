#ifndef PROGRAM_HH_
#define PROGRAM_HH_

#include <cstdint>
#include <vector>
#include <cassert>
#include <unordered_map>

#include "glad/glad.h"

#include "shader.hh"

class Program {
public:

    Program() {
        this->m_programId = glCreateProgram();
    }
    
    // Set uniforms

    inline int32_t find_uniform_id(const char* name) {
        if(this->m_uniforms.find(name) != this->m_uniforms.end())
            return this->m_uniforms[name];
        else {
            int32_t uniformId = glGetUniformLocation(this->m_programId, (const GLchar*)name);
            if(uniformId == -1) return uniformId;
            this->m_uniforms[name] = uniformId;
            return uniformId;
        }
    }

    template<class T>
    void set_uniform(const char*, T);

    template<class T>
    void set_uniform(const char*, const T*);

    // ---------------------------------------------

    inline GLuint get_program_id() const {
        return (GLuint)this->m_programId;
    }

    inline bool import(const Shader& shader) {

        GLuint vertex = shader.vertex(), fragment = shader.fragment(), &programId = this->m_programId;

        glAttachShader(programId, vertex);
        glAttachShader(programId, fragment);
        this->m_shaders.push_back(vertex);
        this->m_shaders.push_back(fragment);

        glLinkProgram(programId);
        glValidateProgram(programId);

        GLint programLinkStatus;
        glGetProgramiv(programId, GL_LINK_STATUS, &programLinkStatus);
        if(!programLinkStatus) {
            int32_t len;
            glGetProgramiv(programId, GL_INFO_LOG_LENGTH, (GLint*)&len);
            std::vector<char> infoLog = {0};
            infoLog.resize(len);
            glGetProgramInfoLog(programId, len, NULL, infoLog.data());
            std::cerr << "Program link failed: " << std::string(infoLog.data()) << std::endl;
            return false;
        }

        return true;
    }

    inline void bind() const { 
        glUseProgram(this->m_programId);
    }

    inline void unbind() const {
        glUseProgram(0);
    }

    ~Program() {
        for(const auto& shader : this->m_shaders)
            glDetachShader(this->m_programId, shader);

        glLinkProgram(this->m_programId);

        glDeleteProgram(this->m_programId);
    }

private:
    std::vector<uint32_t> m_shaders{};
    uint32_t m_programId;
    std::unordered_map<const char*, int32_t> m_uniforms;
};

#endif