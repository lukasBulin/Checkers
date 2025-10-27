#pragma once

class CCheckerBoard;
class CGameState;

class CRenderBoard
{
public:

	virtual bool InitializeRender() = 0;
	virtual void DeinitializeWindow() = 0;

	virtual bool CreateWindow(CGameState* inGameState) = 0;

	virtual void RenderCheckerBoard(const CCheckerBoard* board) = 0;

	virtual bool IsWindowClosed() const = 0;

private:

};