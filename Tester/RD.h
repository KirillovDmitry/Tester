// класс состояния испытываемого прибора, одиночка.
// значения уставок UST0, UST1, а также номер прибора можно считывать и устанавливать.
// контроль наличия выходных команд доступен для внешнего кода только в режиме чтения.

#ifndef RD_h
#define RD_h

class RD
{
private:
	bool UST0;   // значение уставки
	bool UST1;   // значение уставки
	bool VK_DO;  // наличие команды динамического блока обработки
	bool VK_ChO; // наличие команды частотного блока обработки
	bool VK;     // наличие выходной команды
	int Dev_Num; // номер прибора
	RD(void);    // закрытый конструктор
	
public:
	// инициализация объекта класса
	static RD& getInstance(void) {
		static RD instance;
		return instance;
	}

	// функиции запроса и установки состояния прибора
	bool GetUST0(void);
	bool GetUST1(void);
	bool GetVK_DO(void);
	bool GetVK_ChO(void);
	bool GetVK(void);
	int  GetDev_Num(void);
	void SetUST0(bool);
	void SetUST1(bool);

	// функиции установки выходных команд и номера устройства
	void SetVK_DO(bool);
	void SetVK_ChO(bool);
	void SetVK(bool);
	void SetDev_Num(int);
};

#endif

