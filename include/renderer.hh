#ifndef RENDERER_HH_
#define RENDERER_HH_

#include "vao.hh"
#include "ibo.hh"
#include "program.hh"

class Renderer {
public:
    void draw(const VAO&, const IBO&, const Program&, bool = false) const;
    void clear() const;
    void clear_color(float, float, float, float) const;
};

#endif