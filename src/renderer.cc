#include "renderer.hh"

void Renderer::draw(const VAO& vao, const IBO& ibo, const Program& program, bool wireframe) const {
    vao.bind();
    ibo.bind();
    program.bind();
    if(wireframe) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawElements(GL_TRIANGLES, ibo.get_count(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::clear() const {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void Renderer::clear_color(float r, float g, float b, float a) const {
    glClearColor(r, g, b, a);
}