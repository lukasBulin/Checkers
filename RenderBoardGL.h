#pragma once
#include "RenderBoard.h"

class CCheckerBoard;
struct GLFWwindow;

class CRenderBoardGL : public CRenderBoard
{
public:

	virtual bool InitializeRender() override;
	virtual void DeinitializeWindow() override;

	virtual bool CreateWindow() override;

	virtual void RenderCheckerBoard(const CCheckerBoard* board) override;

	virtual bool IsWindowClosed() const override;

private:

	GLFWwindow* window;

};