// приемо-передающий буфер

#ifndef BUF
#define BUF

class Bufer
{
    public:
	  int  BufLen;						// размер приемо-передающего буфера
      void ClearBufer(void);			// очистка приемо-передающего буфера
      int  SendToBufer(char, int);		// запись одного байта в i-й элемент приемо-передающего буфера
      int  SendToBufer(char*, int);		// запись N байт в приемо-передающего буфер
      char ReadFromBufer(int);			// чтение из буфера i-го элемента
      int  ReadFromBufer(int, char*);	// чтение из буфера N байт в приемник по переданному указателю
      ~Bufer();
      Bufer(int);

    private:
      char* buf;						// приемо-передающий буфер
};

#endif
