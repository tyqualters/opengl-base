#ifndef TEXTURE_HH_
#define TEXTURE_HH_

#include <cstdint>
#include <string>
#include <filesystem>
#include <format>

#include "stb_image.h"

#include "renderer.hh"

class Texture {
public:
    Texture(std::string&& filePath) : m_filePath(filePath) {
        glGenTextures(1, &this->m_textureId);
        glBindTexture(GL_TEXTURE_2D, this->m_textureId);

        // Specific to PNGs
        stbi_set_flip_vertically_on_load(1);

        if(!std::filesystem::exists(std::filesystem::path{this->m_filePath})) {
            throw std::runtime_error(std::format("Texture @ %s does not exist", this->m_filePath));
        }

        // Load the picture into the buffer (also, the 4 is for RGBA)
        this->m_localBuf = stbi_load(this->m_filePath.c_str(), &this->m_width, &this->m_height, &this->m_bpp, 4);

        // Downscaling
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        // Upscaling
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // Wrap (horizontal)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        // Wrap (vertical)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        // Send to GPU
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, this->m_width, this->m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->m_localBuf);
        // Unbind texture
        glBindTexture(GL_TEXTURE_2D, 0);

        // Free the stbi image
        if(this->m_localBuf)
            stbi_image_free(this->m_localBuf);
    }

    ~Texture() {
        glDeleteTextures(1, &this->m_textureId);
    }

    inline uint32_t get_width() const {
        return this->m_width;
    }

    inline uint32_t get_height() const {
        return this->m_height;
    }

    void bind(uint32_t slot = 0U) const;
    void unbind() const;

private:
    uint32_t m_textureId = 0U;
    std::string m_filePath;
    uint8_t* m_localBuf = nullptr;
    int32_t m_width = 0U, m_height = 0U, m_bpp = 0U;
};

#endif