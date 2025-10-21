#pragma once
#include "RenderBoard.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class CCheckerBoard;
struct GLFWwindow;

class CRenderBoardGL : public CRenderBoard
{
public:

	virtual void DeinitializeWindow() override;

	virtual bool CreateWindow() override;

	virtual void RenderCheckerBoard(const CCheckerBoard* board) override;

	virtual bool IsWindowClosed() const override;
	
private:
	
	bool CompileShader(GLuint& shader, GLenum type, const char* source);
	bool InitializeShaders();
	void SetupBoardGeometry();
	virtual bool InitializeRender() override;
	GLuint LoadTexture(const char* filepath);

	GLFWwindow* window = nullptr;

	GLuint shaderProgram;
	GLuint boardVAO, boardVBO, boardEBO;

	GLuint boardTexture = 0;
	GLuint redPieceTexture = 0;
	GLuint blackPieceTexture = 0;
};