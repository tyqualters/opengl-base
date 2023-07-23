#ifndef BUF_LAYOUT_HH_
#define BUF_LAYOUT_HH_

#include <cstdint>
#include <vector>
#include <array>

struct BufferElement {
    uint32_t count;
    size_t size;
    uint32_t gl_type;
    bool normalized;
};

class BufferLayout {
public:
    BufferLayout() = default;

    inline const std::vector<BufferElement>& get_elements() const {
        return this->m_elements;
    }

    inline uint32_t get_stride() const {
        return this->m_stride;
    }

    template<typename T>
    void add(uint32_t);

private:
    std::vector<BufferElement> m_elements{};
    uint32_t m_stride = 0;
};

#endif