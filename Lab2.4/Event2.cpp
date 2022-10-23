#include"Event2.h"


Event2::Event2()
{
	this->probabylity = 0;
	this->value = 0;
}

Event2::Event2(double p, int v)
{
	this->probabylity = p;
	this->value = v;
}

double Event2::GetProbabylity()
{
	return this->probabylity;
}

int Event2::GetValue()
{
	return this->value;
}

void Event2::SetProbabylity(double p)
{
	this->probabylity = p;
}

void Event2::SetValue(int v)
{
	this->value = v;
}
