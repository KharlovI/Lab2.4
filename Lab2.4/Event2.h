#pragma once
class Event2
{
private:
	double	probabylity;
	int		value;
public:
	Event2();
	Event2(double p, int v);

	double GetProbabylity();
	int GetValue();

	void SetProbabylity(double p);
	void SetValue(int v);
};