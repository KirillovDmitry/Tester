
#include "ProxyTester.h"

// при отладки переопределяем функцию чтения/записи usb-порта
int ProxyTester::UpdateTesterState(void)
{
	#ifndef  DEBUG
		RT.UpdateTesterState();
	#else
					// прибор не подключен, никакие данные в порт не посылаем
		Sleep(3);   // имитируем задержку реакции на команду

		return 0;   // возвращаем безошибочное состояние USB-порта
	
	#endif
}

void ProxyTester::SetAltitude(double alt){
	#ifndef  DEBUG
		RT.SetAltitude(alt);
	#else
		Tester::cve.SetAltitude(alt);
		// прибор не подключен, никакие данные в порт не посылаем
		// имитируем выдачу команды на заданной высоте и ослаблении
		if ( (RT.GetAltitude() >= 12) & (RT.GetAltitude() <= 15) & (RT.GetAttenuation() <= 100) )
			RT.SetVK(TRUE);
	#endif
}

void ProxyTester::SetAttenuation(double att){
	#ifndef  DEBUG
		RT.SetAttenuation(att);
	#else
		Tester::cve.SetAttenuation(att);
		// прибор не подключен, никакие данные в порт не посылаем
		// имитируем выдачу команды на заданной высоте и ослаблении
		if ( (RT.GetAltitude() >= 12) & (RT.GetAltitude() <= 15) & (RT.GetAttenuation() <= 100) )
			RT.SetVK(TRUE);
	#endif

}

int ProxyTester::GetError(void){
	#ifndef  DEBUG
		RT.GetError(att);
	#else
		// имитируем отсутсвие ошибок
		return 0;
	#endif
}

bool ProxyTester::GetVK(void){
	#ifndef  DEBUG
		RT.GetVK();
	#else
		// читаем команду непосредстенно с объекта экземпляра RD
		return Tester::rd.GetVK();
	#endif
}

ProxyTester::ProxyTester(void)
{
}

ProxyTester::~ProxyTester(void)
{
}
