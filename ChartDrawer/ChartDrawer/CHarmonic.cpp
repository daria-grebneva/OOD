#include "stdafx.h"
#include "CHarmonic.h"

CHarmonic::CHarmonic(double amplitude, double frequency, double phase, HarmonicType type)
	: m_amplitude(amplitude)
	, m_frequency(frequency)
	, m_phase(phase)
	, m_harmonicType(type)
{
}

double CHarmonic::CalculateValue(double x) const
{
	auto functionType = (m_harmonicType == HarmonicType::Sin) ? std::sinl : std::cosl;

	return (m_amplitude * functionType(m_frequency * x + m_phase));
}

sig::connection CHarmonic::DoOnHarmonicChange(const HarmonicChangeSignal::slot_type& handler)
{
	return m_harmonicChanged.connect(handler);
}

double CHarmonic::GetAmplitude() const
{
	return m_amplitude;
}

void CHarmonic::SetAmplitude(double amplitude)
{
	if (m_amplitude != amplitude)
	{
		m_amplitude = amplitude;
		m_harmonicChanged();
	}
}

double CHarmonic::GetFrequency() const
{
	return m_frequency;
}

void CHarmonic::SetFrequency(double frequency)
{
	if (m_frequency != frequency)
	{
		m_frequency = frequency;
		m_harmonicChanged();
	}
}

double CHarmonic::GetPhase() const
{
	return m_phase;
}

void CHarmonic::SetPhase(double phase)
{
	if (m_phase != phase)
	{
		m_phase = phase;
		m_harmonicChanged();
	}
}

HarmonicType CHarmonic::GetHarmonicType() const
{
	return m_harmonicType;
}

void CHarmonic::SetHarmonicType(HarmonicType type)
{
	if (m_harmonicType != type)
	{
		m_harmonicType = type;
		m_harmonicChanged();
	}
}
