#pragma once
#include "RenderBoard.h"

class CCheckerBoard;
class CGameState;

class CRenderBoardConsole: public CRenderBoard
{
public:

	virtual bool InitializeRender() override { return true; };
	virtual void DeinitializeWindow() override {};

	virtual bool CreateWindow(CGameState* inGameState) override { return true; };

	virtual void RenderCheckerBoard(const CCheckerBoard* board) override;

	virtual bool IsWindowClosed() const override { return false; };

private:

};