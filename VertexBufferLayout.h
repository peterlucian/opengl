#ifndef VERTEX_BUFFER_LAYOUT_H
#define VERTEX_BUFFER_LAYOUT_H

#include "glad/glad.h"
#include <stdexcept>
#include <vector>



struct VertexBufferElement{
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    static unsigned int GetSizeOfType (unsigned int type){
        switch (type)
        {
            case GL_FLOAT: return 4;
            case GL_UNSIGNED_INT: return 4;
            case GL_UNSIGNED_BYTE: return 1; 
        }

        return 0;
    }
};

enum class VALUETYPE
{
    FLOAT = 0,UNSIGNED_INT=1,UNSIGNED_CHAR=2 //Create outside VertexBufferLayout class
};

class VertexBufferLayout
{
private:
    std::vector<VertexBufferElement> m_Elements;
    unsigned int m_Stride;
public:
    VertexBufferLayout()
        :m_Stride(0) { }


    // void Push(unsigned int type, unsigned int count)
    // {
    //     m_Elements.push_back({ type, count, GL_FALSE });
    //     m_Stride += count * VertexBufferElement::GetSizeOfType(type);
    // }

    // void push(unsigned int count,VALUETYPE value)
    // {
    //     switch(value)
    //     {
    //     case VALUETYPE::FLOAT:
    //         m_Elements.push_back({GL_FLOAT,count,GL_FALSE});
    //         m_Stride += VertexBufferElement::GetSizeOfType(GL_FLOAT) * count;
    //         break;
    //     case VALUETYPE::UNSIGNED_INT:
    //         m_Elements.push_back({GL_UNSIGNED_INT,count,GL_FALSE});
    //         m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT) * count;
    //         break;
    //     case VALUETYPE::UNSIGNED_CHAR:
    //         m_Elements.push_back({GL_UNSIGNED_BYTE,count,GL_TRUE});
    //         m_Stride +=VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE) * count;
    //         break;
    //     }
    // }

    // template<typename T>
    // void Push(unsigned int count){
    //     std::runtime_error("Trying to template wrong type");
    // };

    template<typename T> void Push(unsigned int count);

    inline const std::vector<VertexBufferElement> GetElements() const& {return m_Elements; };
    inline unsigned int GetStride() const& { return m_Stride; };
};

// template<>
// void VertexBufferLayout::Push<float>(unsigned int count ){
//     m_Elements.push_back({GL_FLOAT, count, GL_FALSE});
//     m_Stride += VertexBufferElement::GetSizeOfType(GL_FLOAT) * count;
// }
// template<>
// void VertexBufferLayout::Push<unsigned int>(unsigned int count ){
//     m_Elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
//     m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT) * count;
// }
// template<>
// void VertexBufferLayout::Push<unsigned char>(unsigned int count ){
//     m_Elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
//     m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE) * count;
// }

#endif

