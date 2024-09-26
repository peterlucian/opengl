
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <GLFW/glfw3.h>

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Renderer.h"
#include "Texture.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 640;
const unsigned int SCR_HEIGHT = 640;

const unsigned int GRID_SIZE_X = 10;
const unsigned int GRID_SIZE_Y = 10;
const float cellWidth = 50.0f;
const float cellHeight = 50.0f;


int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    
    {

        
        // set up vertex data (and buffer(s)) and configure vertex attributes
        // ------------------------------------------------------------------
        // float vertices[] = {
        //     -2.5f, -2.5f,   0.0f, 0.0f, // left  
        //      -1.5f, -2.5f,   1.0f, 0.0f, // right 
        //      -1.5f,  -1.5f,   1.0f, 1.0f, // top  
        //     -2.5f,  -1.5f,   0.0f, 1.0f
        // };

          float vertices[] = {
            -250.0f,  -250.0f,   0.0f, 0.0f, // left  
            -200.0f,  -250.0f,   1.0f, 0.0f, // right 
            -200.0f,  -200.0f,   1.0f, 1.0f, // top  
            -250.0f,  -200.0f,   0.0f, 1.0f
        };
        
        //  float vertices[] = {
        //     -0.5f, -0.5f, // left  
        //     0.5f, -0.5f,   // right 
        //     0.5f,  0.5f,   // top  
        //     -0.5f,  0.5f
        // }; 


        unsigned int indices[]= {
            0, 1, 2,
            2, 3, 0
        };

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        //Create the vertex Array and vertex Buffer
        VertexArray va;
        VertexBuffer vb (vertices, 4 * 4 * sizeof(float));
        //VertexBuffer vb (vertices, 4 * 2 * sizeof(float));

        
        // Create the vertex array layout and bind the buffer and the layout
        VertexBufferLayout layout;
        //layout.push(2, VALUETYPE::FLOAT);
        //layout.push(2, VALUETYPE::FLOAT);
        layout.Push<float>(2);
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);

        IndexBuffer ibo(indices, 6);

       
        //glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f);
        glm::mat4 proj = glm::ortho(-320.0f, 320.0f, -320.0f, 320.0f, -1.0f, 1.0f);

        Shader shader("basic.shader");
        //shader.SetUniform4f("u_Color", 1.0f, 0.5f, 0.2f, 1.0f);
        

        Texture texture("pngegg.png");
        texture.Bind();
        shader.SetUniform1i("u_Texture", 0);


        glm::vec2 offsets[GRID_SIZE_X * GRID_SIZE_Y];
        
        for (int y = 0; y < GRID_SIZE_Y; y++) {
            for (int x = 0; x < GRID_SIZE_X; x++) {
                offsets[y * GRID_SIZE_X + x] = glm::vec2(x * cellWidth, y * cellHeight);  // Position each cell in the grid
            }
        }

        VertexBuffer instancedVBO ( offsets, GRID_SIZE_X * GRID_SIZE_Y * 2 * sizeof(float) );
        // Now, bind it to the quad VAO
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        glVertexAttribDivisor(2, 1); // Tell OpenGL this is an instanced attribute
        glBindVertexArray(0);

        shader.Bind();
        shader.SetUniformMat4f("u_MVP", proj);
        // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
        // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
        // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
        // va.Unbind();
        // vb.Unbind();
        // shader.Unbind();
        Renderer renderer;
        // uncomment this call to draw in wireframe polygons.
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        float r = 0.0f;
        float increment = 0.05f;
        // render loop
        // -----------
        while (!glfwWindowShouldClose(window))
        {
            // input
            // -----
            //processInput(window);

            // render
            // ------
            renderer.Clear();

            //shader.SetUniform4f("u_Color", r, 0.5f, 0.2f, 1.0f);
            // draw our first triangle
            
            renderer.Draw(va, ibo, shader);

            // if (r > 1.0f)
            //     increment = -0.05f;
            // else if (r < 0.0f)
            //     increment = 0.05f;

            // r += increment;
            // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
            // -------------------------------------------------------------------------------
            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        // optional: de-allocate all resources once they've outlived their purpose:
        // ------------------------------------------------------------------------
        // glfw: terminate, clearing all previously allocated GLFW resources.
        // ------------------------------------------------------------------
    }
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
// void processInput(GLFWwindow *window)
// {
//     if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//         glfwSetWindowShouldClose(window, true);
// }

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

