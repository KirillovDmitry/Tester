Программа на языке С++ для управления контрольно-проверочной аппаратурой (КПА). К КПА подключается тестируемый прибор. С помощью разработанного программного обеспечения через КПА на прибор подается серия команд, в результате выполнения которых подтверждается работоспособность подключенного прибора.

В main.cpp реализовано оконное приложение с использованием WinAPI. Здесь создаются стандартные элементы для управления КПА и прибором.

Программа включает в себя следующие основные классы, интерфейс которых реализован в одноименных .h-файлах:
- класс USB содержит интерфейс и реализацию методов для работы с usb-портом (инициализация, открытие и закрытие порта, посылка и считывание данных из порта); 
- класс RD абстрагирует состояние подключенного к КПА прибора, одиночка;
- класс CVE_reg (ControlAndVerificationEquipment) содержит параметры, соответствующие состоянию КПА в определенный момент времени; параметры задаются в двоичном виде и предназначены для посылки в usb-порт без последующих преобразований;
- класс CVE адаптирует интерфейс базового класса CVE_reg с целью возможности задания параметров КПА  в аналоговом виде;
- класс Tester представляет фасад для управления USB-портом, КПА и тестируемым прибором;
- класс ProxyTester контролирует доступ к классу Tester и позволяет в случае отсутствия КПА и прибора проводить корректную отладку программы.

В главной программе создается глобальная переменная типа ProxyTester, абстрагирующая работу аппаратного комплекса. К объекту этой переменной отправляются запросы в соответствии с состояниями элементов управления главной формы, и выполнится заданные тесты прибора.