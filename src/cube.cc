#include "cube.hh"

void Cube::render(const Renderer& renderer) {
    renderer.draw(this->m_vao, this->m_ibo, this->m_program, this->m_wireframe);
}