#ifndef SHADER_HH_
#define SHADER_HH_

#include <iostream>
#include <string>
#include <sstream>
#include <optional>
#include <expected>
#include <fstream>
#include <filesystem>
#include <vector>

#include "glad/glad.h"

class Shader {
public:
    Shader(uint32_t vertexShader, uint32_t fragmentShader) {
        this->m_vertexId = vertexShader;
        this->m_fragmentId = fragmentShader;
    }

    inline GLuint vertex() const {
        return (GLuint)this->m_vertexId;
    }

    inline GLuint fragment() const {
        return (GLuint)this->m_fragmentId;
    }

    ~Shader() {
        glDeleteShader(this->m_vertexId);
        glDeleteShader(this->m_fragmentId);
    }

    static std::expected<GLuint, std::string> compile(std::string&& shader, GLenum type) {
        GLuint id = glCreateShader(type);
        const char* shader_cstr = shader.c_str();
        glShaderSource(id, 1, (GLchar* const*)&shader_cstr, NULL);
        glCompileShader(id);
        
        GLint success;
        glGetShaderiv(id, GL_COMPILE_STATUS, &success);

        if(!success)
        {
            int32_t len;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, (GLint*)&len);
            std::vector<char> infoLog(len);
            glGetShaderInfoLog(id, len, NULL, infoLog.data());
            glDeleteShader(id);
            return std::unexpected(std::string(infoLog.data()));
        }

        return id;
    }

    static std::optional<Shader*> from_files(std::string vertexLocation, std::string fragmentLocation) {
        std::ifstream vertexFile, fragmentFile;
        
        vertexFile.open(vertexLocation, std::ios::binary);
        fragmentFile.open(fragmentLocation, std::ios::binary);

        std::string vertexShaderContents, fragmentShaderContents;
        if(!vertexFile.is_open() || !fragmentFile.is_open()) {
            
            if(!vertexFile.is_open()) {
                std::filesystem::path path{vertexLocation};
                if(std::filesystem::exists(path)) {
                    std::cerr << "Failed to open vertex shader file @ " << std::filesystem::canonical(path).string() << std::endl;
                } else {
                    std::filesystem::path path{"."};
                    path = std::filesystem::canonical(path);
                    path = path / vertexLocation;
                    std::cerr << "Vertex shader file does not exist @ " << path.string() << std::endl;
                }
            }

            if(!fragmentFile.is_open()) {
                std::filesystem::path path{fragmentLocation};
                if(std::filesystem::exists(path)) {
                    std::cerr << "Failed to open fragment shader file @ " << std::filesystem::canonical(path).string() << std::endl;
                } else {
                    std::filesystem::path path{"."};
                    path = std::filesystem::canonical(path);
                    path = path / fragmentLocation;
                    std::cerr << "Fragment shader file does not exist @ " << path.string() << std::endl;
                }
            }

            return std::nullopt;
        }

        std::string buf;
        std::stringstream ss;

        // Read the vertex file
        while(std::getline(vertexFile, buf, '\n')) {
            ss << buf << '\n';
        }
        vertexShaderContents = ss.str();
        buf.erase();
        buf.clear();
        ss.str(std::string());
        ss.clear();

        // Read the fragment file
        while(std::getline(fragmentFile, buf, '\n')) {
            ss << buf << '\n';
        }
        fragmentShaderContents = ss.str();
        buf.erase();
        buf.clear();
        ss.str(std::string());
        ss.clear();

        auto vertexShaderResult = Shader::compile(std::move(vertexShaderContents), GL_VERTEX_SHADER);
        auto fragmentShaderResult = Shader::compile(std::move(fragmentShaderContents), GL_FRAGMENT_SHADER);

        // std::cout << fragmentShaderContents << std::endl;

        if(vertexShaderResult.has_value() && fragmentShaderResult.has_value()) {
            // std::cout << "Vertex: " << vertexShaderContents << "\n\n\tID: " << vertexShaderResult.value() << std::endl;
            // std::cout << "Fragment: " << fragmentShaderContents << "\n\n\tID: " << fragmentShaderResult.value() << std::endl;
            // std::cout << "-------------------------" << std::endl;
            return new Shader(vertexShaderResult.value(), fragmentShaderResult.value());
        } else {
            if(vertexShaderResult.has_value()) {
                glDeleteShader(vertexShaderResult.value());
            } else std::cerr << "Vertex shader failed to compile." << '\n' << vertexShaderResult.error() << std::endl;
            
            if(fragmentShaderResult.has_value()) {
                glDeleteShader(fragmentShaderResult.value());
            } else std::cerr << "Fragment shader failed to compile." << '\n' << fragmentShaderResult.error() << std::endl;

            return std::nullopt;
        }
    }

protected:
    uint32_t m_vertexId, m_fragmentId;
};

#endif