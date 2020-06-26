
#include "CVE_reg.h"

CVE_reg::CVE_reg(void)
{
	// по умолчанию устанавливаем максимальные значения высоты и ослабления
	Dopler      = 0;
	Altitude    = 255; 
	Attenuation = 127;
	AuxAtten    = 15;
	TesterOK    = true;
	EnabelCal	= true;
}


CVE_reg::~CVE_reg(void)
{
}

// функции запроса параметров класса
int CVE_reg::GetDopler(void)
{
   return Dopler;
}

int CVE_reg::GetAltitude(void)
{
   return Altitude;
}

int CVE_reg::GetAttenuation(void)
{
   return Attenuation;
}

int CVE_reg::GetAuxAtten(void)
{
   return AuxAtten;
}

bool CVE_reg::GetTesterStatus(void)
{
   return TesterOK;
}

bool CVE_reg::GetEnabelCal(void)
{
   return EnabelCal;
}

// функции установки параметров класса
void CVE_reg::SetDopler(int Dop)
{
   Dopler = Dop;
}

void CVE_reg::SetAltitude(int Alt)
{
   Altitude = Alt;
}

void CVE_reg::SetAttenuation(int Att)
{
   Attenuation = Att;
}

void CVE_reg::SetAuxAtten(int AuxAtt)
{
   AuxAtten = AuxAtt;
}

void CVE_reg::SetTesterStatus(bool T_OK)
{
   TesterOK = T_OK;
}

void CVE_reg::SetEnabelCal(bool Enabel)
{
	EnabelCal = Enabel;
}

// уменьшение значения высоты на единицу
void CVE_reg::DecAlt(void){
	if (Altitude > bMinAlt)
		Altitude--;
}

// увеличение значения высоты на единицу
void CVE_reg::IncAlt(void){
	if (Altitude < bMaxAlt)
		Altitude++;
}

// уменьшение значения ослабления на единицу
void CVE_reg::DecAtt(void){
	if (Attenuation > bMinAtt)
		Attenuation--;
}

// увеличение значения ослабления на единицу
void CVE_reg::IncAtt(void){
	if (Attenuation < bMaxAtt)
		Attenuation++;
}
