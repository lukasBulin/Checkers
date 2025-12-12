#pragma once
#include "RenderBoard.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class CCheckerBoard;
struct GLFWwindow;
class CGameState;

class CRenderBoardGL : public CRenderBoard
{
public:

	virtual void DeinitializeWindow() override;

	virtual bool CreateWindow(CGameState* inGameState) override;

	virtual void RenderCheckerBoard(const CCheckerBoard* board) override;

	virtual bool IsWindowClosed() const override;

private:

	static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

	void RenderAllCheckers(const CCheckerBoard* board);
	void RenderChecker(float x, float y, GLuint texture, bool isSelected);
	void RenderHintDot(float x, float y, GLuint texture);
	
	bool CompileShader(GLuint& shader, GLenum type, const char* source);
	bool InitializeShaders();

	void SetupBoardGeometry();
	void SetupCheckerGeometry();
	void SetupHintDotGeometry();

	virtual bool InitializeRender() override;
	GLuint LoadTexture(const char* filepath);

	CGameState* gameState = nullptr;
	GLFWwindow* window = nullptr;

	GLuint shaderProgram = 0;
	
	//board VAOs
	GLuint boardVAO = 0;
	GLuint boardVBO = 0;
	GLuint boardEBO = 0;

	//Checker VAOs
	GLuint CheckerVAO = 0;
	GLuint CheckerVBO = 0;
	GLuint CheckerEBO = 0;

	//HintDot VAOs
	GLuint hintVAO = 0;
	GLuint hintVBO = 0;
	GLuint hintEBO = 0;

	GLuint boardTexture = 0;
	GLuint redCheckerTexture = 0;
	GLuint blackCheckerTexture = 0;
	GLuint hintDotTexture = 0;
	GLuint redQueenCheckerTexture = 0;
	GLuint blackQueenCheckerTexture = 0;

	int windowWidth = 800;
	int windowHeight = 800;
};