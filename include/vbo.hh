#ifndef VBO_HH_
#define VBO_HH_

#include <cstddef>
#include <cstdint>

#include "glad/glad.h"

class VBO {

public:
    VBO(const void* data, const size_t size) : m_size(size) {
        glGenBuffers(1, &this->m_bufId);
        glBindBuffer(GL_ARRAY_BUFFER, this->m_bufId);
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
    }

    ~VBO() {
        glDeleteBuffers(1, &this->m_bufId);
    }

    void bind() const;
    void unbind() const;

    inline size_t get_size() const { 
        return this->m_size;
    }

private:
    uint32_t m_bufId;
    size_t m_size;
};

#endif