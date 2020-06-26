#ifndef CVE_REG_H
#define CVE_REG_H
// ControlAndVerificationEquipment
// класс содержит параметры, соответствующие состоянию тестера в определенный момент времени.
// параметры задаются в двоичном виде и предназначены для посылки в usb-порт без последующих преобразований.

#include "cve_constants.h"
class CVE_reg
{
protected:
	int  Dopler;		// значение доплеровского сдвига
	int  Altitude;		// значение высоты
	int  Attenuation;	// значение ослабления основного аттенюатора
	int  AuxAtten;		// значение ослабления дополнительного аттенюатора
	bool EnabelCal;		// установка программной калибровки
	bool TesterOK;		// состояние тестера

public:
	// функции установки параметров
	void SetDopler(int);
	void SetAltitude(int);
	void SetAttenuation(int);
	void SetAuxAtten(int);
	void SetTesterStatus(bool);
	void SetEnabelCal(bool);

	// функции запроса параметров
	int  GetDopler(void);
	int  GetAltitude(void);
	int  GetAttenuation(void);
	int  GetAuxAtten(void);
	bool GetTesterStatus(void);
	bool GetEnabelCal(void);

	void DecAlt(void);		// уменьшение значения высоты на единицу
	void IncAlt(void);		// увеличение значения высоты на единицу

	void DecAtt(void);		// уменьшение значения ослабления на единицу
	void IncAtt(void);		// увеличение значения ослабления на единицу

	CVE_reg(void);

public:
	
	static CVE_reg& getInstance(void) {
		static CVE_reg instance;
		return instance;
	}
	~CVE_reg(void);
};

#endif

