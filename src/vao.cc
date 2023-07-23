#include "vao.hh"

void VAO::bind() const {
    glBindVertexArray(this->m_arrId);
}

void VAO::unbind() const {
    glBindVertexArray(0);
}

void VAO::add_buf(const VBO& vbo, const BufferLayout& layout) const {
    this->bind();

    vbo.bind();

    const auto& elements = layout.get_elements();

    uint32_t index = 0; // location = 0
    uintptr_t offset = 0; // this will be converted into a ptr
    for(auto it = elements.begin(); it != elements.end(); ++it, ++index) {
        glVertexAttribPointer(index, it->count, it->gl_type, static_cast<uint8_t>(it->normalized), layout.get_stride(), (const void*)offset);
        glEnableVertexAttribArray(index);
        offset += it->size;
    }

}