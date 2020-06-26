
#include "CVE.h"

// функции запроса аналоговых параметров класса
double CVE::GetAltitude(void)
{
   return cve_reg.GetAltitude() * StepAlt;
}

double CVE::GetAttenuation(void)
{
   return cve_reg.GetAttenuation() * StepAtt;
}

double CVE::GetAuxAtten(void)
{
   return cve_reg.GetAuxAtten() * StepAuxAtt;
}

// функции установки аналоговых параметров класса
void CVE::SetAltitude(double Alt)
{
	cve_reg.SetAltitude( (int) (Alt/StepAlt));
}

void CVE::SetAttenuation(double Att)
{
	cve_reg.SetAttenuation( (int) (Att/StepAtt) );
}

void CVE::SetAuxAtten(double AuxAtt)
{
	cve_reg.SetAuxAtten( (int) (AuxAtt/StepAuxAtt) );
}

void CVE::SetEnabelCal(bool Enabel)
{
	cve_reg.SetEnabelCal(Enabel);
}

CVE::CVE(void){ }

// функции, реализующие старый функционал (целочисленные значения параметров)
int CVE::GetAltitudeInt(){return cve_reg.GetAltitude();}
int CVE::GetAttenuationInt(){return cve_reg.GetAttenuation();}
int CVE::GetAuxAttenInt(){return cve_reg.GetAuxAtten();}
int CVE::GetDoplerInt(){return cve_reg.GetDopler();}
void CVE::DecAlt(){cve_reg.DecAlt();}
void CVE::IncAlt(){cve_reg.IncAlt();}
void CVE::DecAtt(){cve_reg.DecAtt();}
void CVE::IncAtt(){cve_reg.IncAtt();}
