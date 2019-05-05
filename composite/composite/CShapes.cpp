#include "stdafx.h"
#include "CShapes.h"

size_t CShapes::GetShapesCount() const
{
	return m_shapes.size();
}

void CShapes::InsertShape(const std::shared_ptr<IShape>& shape, size_t position)
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

std::shared_ptr<IShape> CShapes::GetShapeAtIndex(size_t index) const
{
	return m_shapes.at(index);
}

void CShapes::RemoveShapeAtIndex(size_t index)
{
	if (index >= m_shapes.size())
	{
		throw std::out_of_range("There is no shape with this index.");
	}

	m_shapes.erase(m_shapes.begin() + index);
}
