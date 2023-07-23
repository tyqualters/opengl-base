#ifndef VAO_HH_
#define VAO_HH_

#include <cstdint>

#include "glad/glad.h"

#include "vbo.hh"
#include "buffer_layout.hh"

class VAO {
public:
    VAO() {
        glGenVertexArrays(1, &this->m_arrId);
        glBindVertexArray(this->m_arrId);
    }

    ~VAO() {
        glDeleteVertexArrays(1, &this->m_arrId);
    }

    void bind() const;
    void unbind() const;

    void add_buf(const VBO&, const BufferLayout&) const;

private:
    uint32_t m_arrId;
};

#endif