#include "stdafx.h"
#include "CHarmonicCollection.h"
#include "CHarmonic.h"

double CHarmonicCollection::CalculateValue(double x) const
{
	double sum = 0;

	for (auto & harmonic : m_collection)
	{
		sum += harmonic->CalculateValue(x);
	}

	return sum;
}

sig::connection CHarmonicCollection::DoOnSolutionChange(const HarmonicChangeSignal::slot_type& handler)
{
	for (auto & harmonic : m_collection)
	{
		harmonic->DoOnSolutionChange(handler);
	}

	return m_harmonicsUpdateSignal.connect(handler);
}

IHarmonicCollectionPointer CHarmonicCollection::GetHarmonic(size_t index) const
{
	if (index >= m_collection.size())
	{
		throw std::out_of_range("Your index of harmonic is out of range");
	}
	else
	{
		return m_collection[index];
	}
}

size_t CHarmonicCollection::GetHarmonicsCount() const
{
	return m_collection.size();
}

void CHarmonicCollection::AddHarmonic(double amplitude, double frequency, double phase, CHarmonicType type)
{
	auto harmonic = std::make_shared<CHarmonic>(amplitude, frequency, phase, type);
	m_collection.push_back(harmonic);
	m_harmonicsUpdateSignal();
}

void CHarmonicCollection::DeleteHarmonic(size_t index)
{
	if (index >= m_collection.size())
	{
		throw std::out_of_range("Your index of harmonic is out of range");
	}

	m_collection.erase(m_collection.begin() + index);
	m_harmonicsUpdateSignal();
}

