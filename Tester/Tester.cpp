#include "Tester.h"

Tester::Tester(void) : cve(CVE::getInstance()), rd(RD::getInstance()), usb(USB::getInstance())
{
	//VK    = FALSE;			
	Error = (int)usb.USBStatus;
}


Tester::~Tester(void)
{
}

void Tester::SetAltitude(double alt) {
	cve.SetAltitude(alt);	// установили значение высоты в переменную класса
	UpdateTesterState();	// и отправили ее значение в порт
							// здесь же читает значение VK
}

void Tester::SetAttenuation(double att) {
	cve.SetAttenuation(att); // установили значение ослабления в переменную класса
	UpdateTesterState();	 // и отправили ее значение в порт
							 // здесь же читает значение VK
}

void Tester::SetAuxAttenuation(double att) {
	cve.SetAuxAtten(att);    // установили значение ослабления в переменную класса
	UpdateTesterState();	 // и отправили ее значение в порт
							 // здесь же читает значение VK
}

void Tester::SetEnableCal(bool enable){
	cve.SetEnabelCal(enable);
}

void Tester::SetVK(bool comand){
	rd.SetVK(comand);
}

int Tester::GetUSBOpened(void){
	return usb.USBOpened;
}

unsigned long Tester::GetUSBStatus(void){
	return usb.USBStatus;
}

double Tester::GetAltitude(void){
	return cve.GetAltitude();
}

double Tester::GetAttenuation(void){
	return cve.GetAttenuation();
}

int Tester::GetError(void){
	return Error;
}
bool Tester::GetVK(void){
	return rd.GetVK();
}

// протокол обмена. посылаются в порт шесть байт установки заданных значений высоты/ослабления.
// чтение из порта данных о состоянии выходной команды.
int Tester::UpdateTesterState()
{
	int NumByte = 0;
	unsigned char DataByte;
	usb.USBClearBufs();

	//First Byte
	DataByte = ((0x00 << 3) & 0x08);
	DataByte = DataByte | (0x04 & 0x07);
	usb.Buf->SendToBufer(DataByte, NumByte);
	usb.WriteToUSB(1);
	
	//Second Byte
	usb.Buf->SendToBufer('\x50', ++NumByte);
	usb.WriteToUSB(1);
	
	//Third Byte
	char AltLow;
	char AltHigh;
	AltLow =  ( cve.GetAltitudeInt() ) & 0x7F;
	AltHigh = ( cve.GetAttenuationInt()  >> 7) & 0x01;
	DataByte = AltHigh;
	DataByte = DataByte | ( int(cve.GetDoplerInt()) << 5);
	DataByte = DataByte | (0x01 & 0x01) << 1;
	usb.Buf->SendToBufer(DataByte, ++NumByte);
	usb.WriteToUSB(1);

	//Fourth Byte
	DataByte = AltLow;
	usb.Buf->SendToBufer(DataByte, ++NumByte);
	usb.WriteToUSB(1);

    //Fiths Byte
	DataByte = 0x7F - int(cve.GetAltitudeInt());
	usb.Buf->SendToBufer(DataByte, ++NumByte);
	usb.WriteToUSB(1);

	//Six Byte
	DataByte = int(cve.GetAuxAttenInt());
	usb.Buf->SendToBufer(DataByte, ++NumByte);
	usb.WriteToUSB(1);
	usb.USBClearBufs();

	Sleep(50);                      // задержка на время переключения ЛЗ и аттенюатора

	// чтение выходной команды из порта
	usb.ReadFromUSB(1, 200);
	rd.SetVK( (usb.Buf->ReadFromBufer(0)) & 0x01);

	return (int)usb.USBError;       // возвращаем состояние USB-порта
}

	// уменьшение значения высоты на единицу
	void Tester::DecAlt(void)		
	{
		cve.DecAlt();				// уменьшили значение высоты на единицу
		UpdateTesterState();		// и обновили состояние порта
	}

	// увеличение значения высоты на единицу
	void Tester::IncAlt(void)		
	{
		cve.IncAlt();				// увеличили значение высоты на единицу
		UpdateTesterState();		// и обновили состояние порта
	}

	// уменьшение значения ослабления на единицу
	void Tester::DecAtt(void)		
	{
		cve.DecAtt();				// уменьшили значение ослабления на единицу
		UpdateTesterState();		// и обновили состояние порта
	}

	// увеличение значения ослабления на единицу
	void Tester::IncAtt(void)		
	{
		cve.IncAtt();				// уменьшили значение ослабления на единицу
		UpdateTesterState();		// и обновили состояние порта
	}
