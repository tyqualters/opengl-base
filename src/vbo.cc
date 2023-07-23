#include "vbo.hh"

void VBO::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, this->m_bufId);
}

void VBO::unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}