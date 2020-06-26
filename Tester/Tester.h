// фасад для управления USB-портом, КПА и прибором.
// Проверка прибора осуществляется с помощью КПА через USB-порт. Классы прибора, порта и КПА взаимодействуют между собой,
// имеют нетривиальный интерфейс; для инициализации и работы с ними необходимо иметь класс-оболочку, скрывающюю
// взаимодействие классов от внешнего кода. В данном классе также реализован прокол обмена с прибором через USB-порт.

#ifndef TESTER_H
#define TESTER_H

#include <ctime>
#include "CVE.h"
#include "RD.h"
#include "USB.h"

class Tester
{
protected:
	virtual int UpdateTesterState();
	CVE& cve;				 // экземпляр КПА
	RD& rd;					 // экземпляр прибора

private:
	USB& usb;				 // экземпляр usb-порта
//	bool VK;				 // наличие выходной команды
	int Error;				 // состояние тестера, индетификатор ошибки

public:
	Tester(void);
	~Tester(void);
	virtual int GetError(void);
	virtual bool GetVK(void);
	virtual void SetVK(bool);
	virtual double GetAltitude(void);
	virtual double GetAttenuation(void);
	virtual void SetAltitude(double);
	virtual void SetAttenuation(double);
	virtual void SetAuxAttenuation(double);
	virtual void SetEnableCal(bool);
	virtual int GetUSBOpened(void);
	virtual unsigned long GetUSBStatus(void);

	virtual void DecAlt(void);		// уменьшение значения высоты на единицу
	virtual void IncAlt(void);		// увеличение значения высоты на единицу

	virtual void DecAtt(void);		// уменьшение значения ослабления на единицу
	virtual void IncAtt(void);		// увеличение значения ослабления на единицу

};

#endif
