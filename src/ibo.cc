#include "ibo.hh"

void IBO::bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_bufId);
}

void IBO::unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}