#include "stdafx.h"
#include "ResizeImageCommand.h"

CResizeImageCommand::CResizeImageCommand(int& currentWidth, int& width, int& currentHeight, int& height)
	: m_currentHeight(currentHeight)
	, m_currentWidth(currentWidth)
	, m_height(height)
	, m_width(width)
{
}

void CResizeImageCommand::DoExecute()
{
	std::swap(m_currentHeight, m_height);
	std::swap(m_currentWidth, m_width);
}

void CResizeImageCommand::DoUnexecute()
{
	DoExecute();
}
