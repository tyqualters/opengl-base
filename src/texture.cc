#include "texture.hh"

void Texture::bind(uint32_t slot) const {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, this->m_textureId);
}

void Texture::unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}