#include "buffer_layout.hh"

#include "glad/glad.h"

template<>
void BufferLayout::add<float>(uint32_t count) {
    size_t size = count * sizeof(float);
    this->m_elements.push_back({count, size, GL_FLOAT, false});
    this->m_stride += size;
}

template<>
void BufferLayout::add<uint32_t>(uint32_t count) {
    size_t size = count * sizeof(uint32_t);
    this->m_elements.push_back({count, size, GL_UNSIGNED_INT, false});
    this->m_stride += size;
}

template<>
void BufferLayout::add<uint8_t>(uint32_t count) {
    size_t size = count * sizeof(uint8_t);
    this->m_elements.push_back({count, size, GL_UNSIGNED_BYTE, true});
    this->m_stride += size;
}