
#include "RD.h"

RD::RD(void)
{
	SetUST0(FALSE);
	SetUST1(FALSE);
	SetDev_Num(0);
	SetVK_DO(FALSE);
	SetVK_ChO(FALSE);
	SetVK(FALSE);
}

// запрос внутренних переменных класса (состояния прибора)
bool RD::GetUST0(void)
{
	return UST0;
}

bool RD::GetUST1(void)
{
	return UST1;
}

bool RD::GetVK_DO(void)
{
	return VK_DO;
}

bool RD::GetVK_ChO(void)
{
	return VK_ChO;
}

bool RD::GetVK(void)
{
	return VK;
}

int RD::GetDev_Num(void)
{
	return Dev_Num;
}


// установка внутренних переменных класса (состояния прибора)
void RD::SetUST0(bool U0)
{
	UST0 = U0;
}

void RD::SetUST1(bool U1)
{
	UST1 = U1;
}

void RD::SetVK(bool v)
{
	VK = v;
}

void RD::SetVK_DO(bool v)
{
	VK_DO = v;
}

void RD::SetVK_ChO(bool v)
{
	VK_ChO = v;
}

void RD::SetDev_Num(int dev)
{
	Dev_Num = dev;
}
