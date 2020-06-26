
#ifndef CVE_H
#define CVE_H

// ControlAndVerificationEquipment
// данный класс адаптирует интерфейс класса CVE_reg с целью возможности задания параметров тестера (высоты и
// ослабления в аналоговом виде. для этого в функциях установки и задания высоты/ослабления происходит
// пересчет значений задаваемых аналоговых параметров в занчения регистров класса CVE_reg

#include "cve_reg.h"

class CVE
{
public:
	// переопределение функции запроса/установки высоты и ослабления
	void SetAltitude(double);
	void SetAttenuation(double);
	void SetAuxAtten(double);

	double  GetAltitude(void);
	double  GetAttenuation(void);
	double  GetAuxAtten(void);

	void DecAlt(void);		// уменьшение значения высоты на единицу
	void IncAlt(void);		// увеличение значения высоты на единицу
	void DecAtt(void);		// уменьшение значения ослабления на единицу
	void IncAtt(void);		// увеличение значения ослабления на единицу
	void SetEnabelCal(bool);

	// непереопределенные функции запроса/установки высоты и ослабления
	int	GetAltitudeInt(void);
	int	GetDoplerInt(void);
	int	GetAttenuationInt(void);
	int	GetAuxAttenInt(void);

	static CVE& getInstance(void) {
		static CVE instance; 
		return instance;
	}
private:
	CVE_reg cve_reg;
	CVE(void);
};

#endif

