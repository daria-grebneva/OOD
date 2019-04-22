#include "stdafx.h"
#include "CGroupShape.h"
#include <algorithm>
#include <functional>

CGroupShape::CGroupShape()
{
	FillGroup fillStyleGroup = [this](std::function<void(IStyle&)> func) {
		for (auto&& shape : m_shapes)
		{
			func(*shape->GetFillStyle());
		}
	};

	m_groupFillStyle = std::make_shared<CGroupFillStyle>(fillStyleGroup);

	LineGroup lineStyleGroup = [this](std::function<void(ILineStyle&)> func) {
		for (auto&& shape : m_shapes)
		{
			func(*shape->GetLineStyle());
		}
	};

	m_groupLineStyle = std::make_shared<CGroupLineStyle>(lineStyleGroup);
}

RectD CGroupShape::GetFrame()
{
	if (m_shapes.empty())
	{
		return RectD{ 0, 0, 0, 0 };
	}

	auto frame = m_shapes.front()->GetFrame();
	double minX = frame.left;
	double minY = frame.top;
	double maxX = frame.left + frame.width;
	double maxY = frame.top + frame.height;

	for (size_t i = 1; i < GetShapesCount(); ++i)
	{
		auto frame = m_shapes[i]->GetFrame();
		minX = std::min(minX, frame.left);
		minY = std::min(minX, frame.top);

		maxX = std::max(maxX, frame.left + frame.width);
		maxY = std::max(maxY, frame.top + frame.height);
	}

	return RectD{ minX, minY, maxX - minX, maxY - minY };
}

void CGroupShape::SetFrame(const RectD& rect)
{
	auto oldFrame = GetFrame();

	for (auto& shape : m_shapes)
	{
		auto oldShapeFrame = shape->GetFrame();
		shape->SetFrame({ GetNewLeftCoord(rect, oldShapeFrame, oldFrame),
			GetNewTopCoord(rect, oldShapeFrame, oldFrame),
			GetNewWidth(rect, oldShapeFrame, oldFrame),
			GetNewHeight(rect, oldShapeFrame, oldFrame) });
	}
}

double CGroupShape::GetNewLeftCoord(const RectD& rect, const RectD& oldShapeFrame, const RectD& oldFrame)
{
	return (rect.left + ((oldShapeFrame.left - oldFrame.left) / oldFrame.width) * rect.width);
}

double CGroupShape::GetNewTopCoord(const RectD& rect, const RectD& oldShapeFrame, const RectD& oldFrame)
{
	return (rect.top + ((oldShapeFrame.top - oldFrame.top) / oldFrame.height) * rect.height);
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
	return std::make_shared<CGroupShape>(*this);
}

std::shared_ptr<const IGroupShape> CGroupShape::GetGroup() const
{
	return std::make_shared<CGroupShape>(*this);
}

size_t CGroupShape::GetShapesCount() const
{
	return m_shapes.size();
}

void CGroupShape::InsertShape(const std::shared_ptr<IShape>& shape, size_t position)
{
	if (position >= GetShapesCount())
	{
		m_shapes.push_back(shape);
	}
	else
	{
		m_shapes.insert(m_shapes.begin() + position, shape);
	}
}

std::shared_ptr<IShape> CGroupShape::GetShapeAtIndex(size_t index)
{
	if (index >= GetShapesCount())
	{
		throw std::out_of_range("shape out of range");
	}
	return m_shapes[index];
}

void CGroupShape::RemoveShapeAtIndex(size_t index)
{
	if (index >= GetShapesCount())
	{
		throw std::out_of_range("shape out of range");
	}

	m_shapes.erase(m_shapes.begin() + index);
}

void CGroupShape::Draw(ICanvas& canvas) const
{
	for (auto const& shape : m_shapes)
	{
		shape->Draw(canvas);
	}
}
