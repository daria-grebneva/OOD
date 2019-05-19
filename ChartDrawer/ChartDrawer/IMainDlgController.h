#pragma once

class IMainDlgController
{
public:
	virtual void SetAmplitude(int index, double a) = 0;
	virtual void SetFrequence(int index, double b) = 0;
	virtual void SetPhase(int index, double c) = 0;
	virtual ~IMainDlgController() = default;
};
