#include "Renderer.h"
#include <iostream>

void GLClearError(){
    while (glGetError()!= GL_NO_ERROR);
}
bool GLLogCall(const char* function, const char* file, int line){
    while ( GLenum error = glGetError()){
        std::cout << "OpenGL error (" << error << " )" << function << " " << file << " : " << line << std::endl;
        return false;
    }
    return true;
}

void Renderer::Clear() const
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Draw(const VertexArray &va, const IndexBuffer& ib, const Shader &shader) const
{
    shader.Bind();
    ib.Bind();
    va.Bind();
    //glDrawArrays(GL_TRIANGLES, 0, 3);
    //glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
    glDrawElementsInstanced(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr, 10 * 10);
}