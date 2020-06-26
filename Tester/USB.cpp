
#include "USB.h"

//extern const int DEBUG;

USB::USB()
{
	// инициализация членов класса
	USBSemaphore  = 0;
	USBOpened     = 0;
	DeviceIndex   = 0;
	DeviceFound   = 0;
	USBError      = 0;
	USBDeviceName = "Altimeters Tester";

	NumDev = 8;								// количество подключнных устройств не должно превышать размер буфера
	BufPtrs = new char* [NumDev];			// указатель на массив usb-устройств
	for(int i = 0; i<NumDev; i++)
		BufPtrs[i] = new char [64];			// инициализация каждого буфера usb-устройства массивом

	Buf = new Bufer(8);				// инициализация приемо-передающего буфера

	// инициализация usb-буфера, поиск аппаратуры
	// в случае режима отладки считаем, что порт правильно открыт
	#ifndef  DEBUG
		if(USBOpened != 1)
			{
				USBPortSearch();
				OpenUSBPort();
				if(USBStatus != FT_OK)
                	MessageBox(NULL, "Не удалось открыть порт", "Ошибка ввода-вывода", MB_OK);
				USBPortInit();
			}
	#else	
		USBOpened	= 1;
		USBStatus	= FT_OK;
		USBHandle	= 0;
		DeviceIndex = 1;
		DeviceFound = 1;
		USBError    = 0;
	#endif

}

USB::~USB()
{	
	// по окончании работы с портом закрываем его
	USBClearBufs();				// очистка буфера usb-порта
    CloseUSBPort();				// закрытие usb-порта

	// высвобождаем память из-под массива usb-устройств
	for(int i = 0; i<NumDev; i++)
		delete [] BufPtrs[i];
	   
	delete [] BufPtrs;

	delete Buf;

}


// сканирование usb-устройств, подключенных к компьютеру
void USB::USBPortSearch()
{
	DWORD numDev;
	DWORD devIndex;
	int DeviceFound(0);
	
	// осуществляем поиск всех usb-устройств; их описатели сохраняем в буфере.
	// индекс искомого прибора сохраняется в переменных класса.
	USBStatus = FT_ListDevices(BufPtrs, &numDev, FT_LIST_ALL | FT_OPEN_BY_DESCRIPTION);
	if(USBStatus == FT_OK)
	  {
		for(unsigned int i = 0; i < numDev; i++)
		{
			if(std::string(BufPtrs[i]) == USBDeviceName)
			 {
				DeviceIndex = devIndex = i;
				DeviceFound = 1;
				break;
			 }
		}
	  }
	else
	  {
		DeviceFound = 0;
	  }
	/*
	// поиск прибора по имени
	char SerNumBuf[64]; 
	if(numDev > 0 && DeviceFound == 1)
	   {
		  USBStatus = FT_ListDevices((PVOID)devIndex, SerNumBuf, FT_LIST_BY_INDEX | FT_OPEN_BY_SERIAL_NUMBER);
	   }
	*/
}


// открытие юсб-порта, к которому подключен тестер;
// сохранение хэндела в члене класса
void USB::OpenUSBPort()
{
	FT_HANDLE ftHandle;
	USBStatus = FT_Open(DeviceIndex, &ftHandle);

	if(USBStatus == FT_OK)
	  {
		USBOpened = 1;
		USBHandle = ftHandle;
	  }
	else
	  {
	
		#ifndef DEBUG  // в рабочем режиме в выводим на экран сообщение об ошибке подключения к аппаратуре
		  MessageBox(NULL, "Не удалось открыть порт", "Ошибка ввода-вывода", MB_OK);
		#endif
		USB::USBOpened = 0;
	  }
}


// инициализация открытого порта, задание скорости работы и других параметров
void USB::USBPortInit()
{
    if(USBOpened == 1)
      {
		USBStatus = FT_ResetDevice(USBHandle);
		USBStatus = FT_Purge(USBHandle, FT_PURGE_RX | FT_PURGE_TX);  
		USBStatus = FT_SetBaudRate(USBHandle, FT_BAUD_19200);		 
		USBStatus = FT_SetDataCharacteristics(USBHandle, FT_BITS_8, FT_STOP_BITS_2, FT_PARITY_NONE);
		USBStatus = FT_SetFlowControl(USBHandle, FT_FLOW_NONE, NULL, NULL);
      }
}

// очистка usb-буфера
void USB::USBClearBufs()
{
	USBStatus = FT_Purge(USBHandle, FT_PURGE_RX | FT_PURGE_TX);
}

// закрытие usb-буфера
void USB::CloseUSBPort()
{
    if(USBOpened == 1)
      {
		USBStatus = FT_Close(USBHandle);
		if( USBStatus != FT_OK)
		  {
			if(USBError == 0)
				#ifndef DEBUG  //
					MessageBox(NULL, "Не удалось закрыть порт", "Ошибка ввода-вывода", MB_OK);
				#endif
			USBError = 30;
		  }
		USBSemaphore  = 0;
		USBOpened     = 0;
		DeviceIndex   = 0;
		DeviceFound   = 0;
      }
}


// запись BytesToWrite байт из буффера Buf в usb-порт
void USB::WriteToUSB(DWORD BytesToWrite)
{
	DWORD BytesWritten(0);
	char* WriteBuf = new char[BytesToWrite];

		if(USBOpened == 1)
		  {
			Buf->ReadFromBufer(Buf->BufLen, WriteBuf);
			USBStatus = FT_Write(USBHandle, WriteBuf, BytesToWrite, &BytesWritten);
			if(USBStatus != FT_OK)
 			  {
				if(USBError == 0)
					#ifndef DEBUG  //
						MessageBox(NULL, "Не удалось записать данные в порт", "Ошибка ввода-вывода", MB_OK);
					#endif
				USBError = 20;
			  }
		  }
	delete [] WriteBuf;  
}

// чтение из usb-порта
int USB::ReadFromUSB(DWORD BytesToRead, int Timeout)
{
    DWORD BytesWritten;
    char* ReadBuf = new char[BytesToRead];
    FT_SetTimeouts(USBHandle, Timeout, 0);
    FT_Read(USBHandle, ReadBuf, BytesToRead, &BytesWritten);
    Buf->SendToBufer(ReadBuf, BytesToRead);

    delete [] ReadBuf;
    if(BytesToRead != BytesWritten)
        return 0;
    else
        return 1;
}
