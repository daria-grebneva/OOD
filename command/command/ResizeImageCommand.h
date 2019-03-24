#pragma once
#include "AbstractCommand.h"

class CResizeImageCommand : public CAbstractCommand
{
public:
	CResizeImageCommand(int& currentWidth, int width, int& currentHeight, int height);

private:
	void DoExecute() override;
	void DoUnexecute() override;

	int& m_currentWidth;
	int m_width;
	int& m_currentHeight;
	int m_height;
};
