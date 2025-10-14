#include "CheckerBoard.h"
#include "RenderBoardConsole.h"
#include "RenderBoardGL.h"
#include "PlayerInput.h"
#include <iostream>
#include <conio.h>
using namespace std;

int main() {

	CCheckerBoard board;
	//CRenderBoardConsole render;
	CRenderBoardGL render;
	CPlayerInput playerWhite;
	CPlayerInput playerBlack;

	if (!render.InitializeRender())
	{
		return -1;
	}

	if (!render.CreateWindow())
	{
		return -1;
	}

	bool whiteTurn = true;

	board.ResetBoard();

	bool bWindowClosed = false;

	while (!bWindowClosed)
	{
		render.RenderCheckerBoard(&board);

		//cout << (whiteTurn ? "White Turn!" : "Black Turn!") << endl;

		//SNextMove nextMove = whiteTurn ? playerWhite.ProcessPlayerInput(&board) : playerBlack.ProcessPlayerInput(&board);

		//nextMove.checkerType = whiteTurn ? ECheckerType::white : ECheckerType::black;

		//if (board.ValidateMove(nextMove))
		//{
		//	board.MoveChecker(nextMove);

		//	whiteTurn = !whiteTurn;
		//}
		//else
		//{
		//	//player chose invalid tile
		//	cout << "Invalid Move, Try Again!, Press Any Key" << endl;
		//	_getch();
		//}

		bWindowClosed = render.IsWindowClosed();
	}

	render.DeinitializeWindow();

	return 0;
}

//#include <GLFW/glfw3.h>
//
//int main(void)
//{
//    GLFWwindow* window;
//
//    /* Initialize the library */
//    if (!glfwInit())
//        return -1;
//
//    /* Create a windowed mode window and its OpenGL context */
//    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
//    if (!window)
//    {
//        glfwTerminate();
//        return -1;
//    }
//
//    /* Make the window's context current */
//    glfwMakeContextCurrent(window);
//
//    /* Loop until the user closes the window */
//    while (!glfwWindowShouldClose(window))
//    {
//        /* Render here */
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        /* Swap front and back buffers */
//        glfwSwapBuffers(window);
//
//        /* Poll for and process events */
//        glfwPollEvents();
//    }
//
//    glfwTerminate();
//    return 0;
//}
//
