#include "RenderBoardGL.h"
#include "CheckerBoard.h"
#include <GLFW/glfw3.h>

bool CRenderBoardGL::InitializeRender()
{
    if (!glfwInit())
    {
        return false;
    }
    return true;
}

void CRenderBoardGL::DeinitializeWindow()
{
    glfwTerminate();
}

bool CRenderBoardGL::CreateWindow()
{
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return false;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    return true;
}

void CRenderBoardGL::RenderCheckerBoard(const CCheckerBoard* board)
{
	/* Render here */
    glClear(GL_COLOR_BUFFER_BIT);

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
}

bool CRenderBoardGL::IsWindowClosed() const
{
    return glfwWindowShouldClose(window);
}