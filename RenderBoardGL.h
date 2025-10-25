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
	
	void RenderAllCheckers(const CCheckerBoard* board);

	void RenderChecker(float x, float y, GLuint texture);
	
	bool CompileShader(GLuint& shader, GLenum type, const char* source);
	bool InitializeShaders();

	void SetupBoardGeometry();
	void SetupRedCheckerGeometry();

	virtual bool InitializeRender() override;
	GLuint LoadTexture(const char* filepath);

	GLFWwindow* window = nullptr;

	GLuint shaderProgram = 0;
	
	//board VAOs
	GLuint boardVAO = 0;
	GLuint boardVBO = 0;
	GLuint boardEBO = 0;

	//redChecker VAOs
	GLuint CheckerVAO = 0;
	GLuint CheckerVBO = 0;
	GLuint CheckerEBO = 0;

	GLuint boardTexture = 0;
	GLuint redCheckerTexture = 0;
	GLuint blackCheckerTexture = 0;
};