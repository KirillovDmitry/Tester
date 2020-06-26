
#include "Bufer.h"

Bufer::Bufer(int i = 8): BufLen(i)
{
	buf = new char [BufLen];
	for (int i = 0; i<BufLen; i++)
		buf[i] = '\0';
}


Bufer::~Bufer(void)
{
	delete [] buf;
}


void Bufer::ClearBufer(void)
{
    for (int i = 0; i<BufLen; i++)
		buf[i] = '\0';
}


// функция записи одного байта в i-ый элемент буфера
int Bufer::SendToBufer(char data, int i)
{
	if( (i<=BufLen) & (i>=0) )
	  {
		buf[i] = data;
        return 0;
	  }
    else
        return 1; 
}


// функция записи в буфер N байт данных
int Bufer::SendToBufer(char* data, int N)
{
    for (int i = 0; ((i<BufLen) & (i<N)); i++)
        buf[i] = data[i];
	
	if (N <= BufLen)
        return 0;
    else
        return 1; 
}


// чтение байта данных из i-ого элемента буфера
char Bufer::ReadFromBufer(int i)
{
	if ( (i<=BufLen) & (i>=0) )
		return buf[i];
	else
		return 'E';
}


// чтение N байт из буфера по указателю *data
int Bufer::ReadFromBufer(int N, char* data)
{
    for (int i = 0; ((i<N) & (i<BufLen)); i++)
        data[i] = buf[i];
	
	if (N <= BufLen)
        return 0;
    else
        return 1;
}
