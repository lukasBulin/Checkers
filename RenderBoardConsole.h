#pragma once
#include "RenderBoard.h"

class CCheckerBoard;

class CRenderBoardConsole: public CRenderBoard
{
public:

	virtual bool InitializeRender() override { return true; };
	virtual void DeinitializeWindow() override {};

	virtual bool CreateWindow() override { return true; };

	virtual void RenderCheckerBoard(const CCheckerBoard* board) override;

	virtual bool IsWindowClosed() const override { return false; };

private:

};