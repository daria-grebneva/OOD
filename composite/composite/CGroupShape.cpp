#include "stdafx.h"
#include "CGroupShape.h"
#include <algorithm>
#include <functional>

CGroupShape::CGroupShape()
{
	m_shapes = std::make_shared<CShapes>();

	m_groupLineStyle = std::make_shared<CGroupLineStyle>(m_shapes);
	m_groupFillStyle = std::make_shared<CGroupFillStyle>(m_shapes);
}

RectD CGroupShape::GetFrame()
{
	auto rect = RectD{ 0, 0, 0, 0 };
	if (m_shapes->GetShapesCount() != 0)
	{
		auto firstFrame = m_shapes->GetShapeAtIndex(0)->GetFrame();

		double minX = firstFrame.left;
		double minY = firstFrame.top;
		double maxX = firstFrame.left + firstFrame.width;
		double maxY = firstFrame.top + firstFrame.height;

		for (size_t i = 1; i < GetShapesCount(); ++i)
		{
			auto frame = m_shapes->GetShapeAtIndex(i)->GetFrame();
			if (!IsNullFrame(frame))
			{
				minX = (IsNullFrame(firstFrame)) ? frame.left : std::min(minX, frame.left);
				minY = (IsNullFrame(firstFrame)) ? frame.top : std::min(minX, frame.top);

				maxX = std::max(maxX, frame.left + frame.width);
				maxY = std::max(maxY, frame.top + frame.height);
			}
		}

		rect = RectD{ minX, minY, maxX - minX, maxY - minY };
	}

	return rect;
}

bool CGroupShape::IsNullFrame(const RectD& frame)
{
	return ((frame.height == 0) && (frame.width == 0) && (frame.top == 0) && (frame.left == 0));
}

void CGroupShape::SetFrame(const RectD& rect)
{
	auto oldFrame = GetFrame();

	for (size_t i = 0; i < m_shapes->GetShapesCount(); i++)
	{
		auto shape = m_shapes->GetShapeAtIndex(i);
		auto oldShapeFrame = shape->GetFrame();
		shape->SetFrame({ GetNewLeftCoord(rect, oldShapeFrame, oldFrame),
			GetNewTopCoord(rect, oldShapeFrame, oldFrame),
			GetNewWidth(rect, oldShapeFrame, oldFrame),
			GetNewHeight(rect, oldShapeFrame, oldFrame) });
	}
}

double CGroupShape::GetNewLeftCoord(const RectD& rect, const RectD& oldShapeFrame, const RectD& oldFrame)
{
	return (rect.left + ((oldShapeFrame.left - oldFrame.left) * (rect.width / oldFrame.width)));
}

double CGroupShape::GetNewTopCoord(const RectD& rect, const RectD& oldShapeFrame, const RectD& oldFrame)
{
	return (rect.top + ((oldShapeFrame.top - oldFrame.top) * (rect.height / oldFrame.height)));
}

double CGroupShape::GetNewWidth(const RectD& rect, const RectD& oldShapeFrame, const RectD& oldFrame)
{
	return (oldShapeFrame.width * rect.width / oldFrame.width);
}

double CGroupShape::GetNewHeight(const RectD& rect, const RectD& oldShapeFrame, const RectD& oldFrame)
{
	return (oldShapeFrame.height * rect.height / oldFrame.height);
}

std::shared_ptr<ILineStyle> CGroupShape::GetLineStyle()
{
	return m_groupLineStyle;
}

std::shared_ptr<const ILineStyle> CGroupShape::GetLineStyle() const
{
	return m_groupLineStyle;
}

std::shared_ptr<IStyle> CGroupShape::GetFillStyle()
{
	return m_groupFillStyle;
}

std::shared_ptr<const IStyle> CGroupShape::GetFillStyle() const
{
	return m_groupFillStyle;
}

std::shared_ptr<IGroupShape> CGroupShape::GetGroup()
{
	return shared_from_this();
}

std::shared_ptr<const IGroupShape> CGroupShape::GetGroup() const
{
	return shared_from_this();
}

size_t CGroupShape::GetShapesCount() const
{
	return m_shapes->GetShapesCount();
}

void CGroupShape::InsertShape(const std::shared_ptr<IShape>& shape, size_t position)
{
	m_shapes->InsertShape(shape, position);
}

std::shared_ptr<IShape> CGroupShape::GetShapeAtIndex(size_t index) const
{
	return m_shapes->GetShapeAtIndex(index);
}

void CGroupShape::RemoveShapeAtIndex(size_t index)
{
	m_shapes->RemoveShapeAtIndex(index);
}

void CGroupShape::Draw(ICanvas& canvas) const
{
	for (size_t i = 0; i < m_shapes->GetShapesCount(); i++)
	{
		auto shape = m_shapes->GetShapeAtIndex(i);
		shape->Draw(canvas);
	}
}
