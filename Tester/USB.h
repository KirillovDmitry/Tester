
#ifndef USB_H
#define USB_H

#include "FTD2XX.h"
#include "debug.h"
#include "Bufer.h"
#include <string>

// интерфейс юсб-порта
class USB
{
    public:
      int USBSemaphore;
      int USBOpened;
      int DeviceIndex;
      int DeviceFound;
      int USBError;

      FT_HANDLE USBHandle;
      FT_STATUS USBStatus;

      std::string USBDeviceName;

	  // функции для работы с usb-устройством
      void OpenUSBPort(void);				// открытие порта
      void USBPortSearch(void);				// поиск usb-устройств
      void USBPortInit(void);				// инициализация usb-порта
      void USBClearBufs(void);				// очистка буфера usb-порта
      void CloseUSBPort(void);				// закрытие usb-порта
      void WriteToUSB(DWORD);				// запись данных в usb-порт
      int  ReadFromUSB(DWORD, int);			// чтение данных из usb-порта

	  char** BufPtrs;				 		// массив описания найденных устройств
	  int  NumDev;							// размер массива описания найденных устройств
	  Bufer* Buf;							// приемо-передающий буфер

	  ~USB();

	  static USB& getInstance(void)
		{
			static USB instance;
			return instance;
		}
	private:
		USB();
};

#endif
