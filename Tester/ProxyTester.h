#ifndef PROXY_TESTER_H
#define PROXY_TESTER_H
// Данный класс представляет заместителя класса Tester.
// В процессе работы и отладки программы оборудование может быть не подключено, что
// приведет к выдачи ошибок подключения прибора. Класс ProxyTester позволяет отлаживать
// программу без необходимости подключения оборудавания, а также эмулировать работу
// прибора (выдачу команд на заданных уставках).

#include "Tester.h"
#include "debug.h"

// наследуем класс реального тестера
class RealTester: public Tester
{

};

class ProxyTester: public Tester
{
public:
	RealTester RT;				
	void SetAltitude(double);
	void SetAttenuation(double);
	int GetError(void);
	bool GetVK(void);
	ProxyTester(void);
	~ProxyTester(void);
protected:
	int UpdateTesterState();

};

#endif

