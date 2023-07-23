#include "program.hh"

#include <glm/glm.hpp>

template<>
void Program::set_uniform<int32_t>(const char* name, int32_t value) {
    this->bind();
    int32_t uniformId = this->find_uniform_id(name);
    if(uniformId == -1) return;
    glUniform1i(uniformId, value);
}

template<>
void Program::set_uniform<float>(const char* name, float value) {
    this->bind();
    int32_t uniformId = this->find_uniform_id(name);
    if(uniformId == -1) return;
    glUniform1f(uniformId, value);
}

template<>
void Program::set_uniform<glm::vec4>(const char* name, glm::vec4 value) {
    this->bind();
    int32_t uniformId = this->find_uniform_id(name);
    if(uniformId == -1) return;
    glUniform4f(uniformId, value.x, value.y, value.z, value.w);
}

template<>
void Program::set_uniform<glm::vec3>(const char* name, glm::vec3 value) {
    this->bind();
    int32_t uniformId = this->find_uniform_id(name);
    if(uniformId == -1) return;
    glUniform3f(uniformId, value.x, value.y, value.z);
}

template<>
void Program::set_uniform<glm::mat4>(const char* name, const glm::mat4* value) {
    assert(value != nullptr);
    this->bind();
    int32_t uniformId = this->find_uniform_id(name);
    if(uniformId == -1) return;
    glUniformMatrix4fv(uniformId, 1, 0U, &(*value)[0][0]);
}