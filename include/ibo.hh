#ifndef IBO_HH_
#define IBO_HH_

#include <cstddef>
#include <cstdint>

#include "glad/glad.h"

class IBO {

public:
    
    IBO(const uint32_t* data, const uint32_t capacity) : m_capacity(capacity) {
        glGenBuffers(1, &this->m_bufId);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_bufId);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, capacity * sizeof(uint32_t), data, GL_STATIC_DRAW);
    }

    ~IBO() {
        glDeleteBuffers(1, &this->m_bufId);
    }

    void bind() const;
    void unbind() const;

    inline uint32_t get_count() const {
        return this->m_capacity;
    }

    inline size_t get_size() const { 
        return this->m_capacity * sizeof(uint32_t);
    }

private:
    uint32_t m_bufId;
    uint32_t m_capacity;
};

#endif