#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include "glad/glad.h"

class VertexBuffer
{
    private:
        /* data */
        unsigned int m_RendererID;
    public:
        VertexBuffer(const void* data, unsigned int size);
        ~VertexBuffer();

        void Bind() const;
        void Unbind() const;
};

#endif