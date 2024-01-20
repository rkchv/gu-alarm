#include "usb3000.h"
#include "imit_kt.h"

// Конструктор объекта модуля USB3000 *OK

usb3000_t::usb3000_t():
           type(0),
           noise(100),
           amplitude(600.00),
           lower(0),
           x(0.01)
{
	// Обнуление структур
	
	// данных информации о драйвере
	memset(&data_dac, 	 0, sizeof(RTUSB3000::OUTPUT_PARS)); 
	// данных для работы с ППЗУ
	memset(&data_flash,  0, sizeof(RTUSB3000::FLASH));    
	// данных работы с ЦАП
	memset(&data_driver, 0, sizeof(RTUSB3000::DSP_INFO));
	
	data_dac.OutputRate = 100.0; 
	// максимальный размер FIFO буфера ЦАП в DSP модуля
	data_dac.OutputFifoLength = 0xF80;
}

 
////////// Проверка корректности работы подключенного модуля ///////  *OK

bool usb3000_t::checking(void)
{

	// Экспорт библиотеки Rtusbapi
	usb3000_library.setFileName("Rtusbapi");
	
	// Если не удалось загрузить
	if (!usb3000_library.load())
	{	
		return 0;
	}
	
	typedef void*   (_stdcall *Exp_ci)(char *);
	
	// Вызов функции из библиотеки Rtusbapi для получения указателя на модуль USB3000
	Exp_ci CreateInstance = (Exp_ci)(usb3000_library.resolve("RtCreateInstance"));
	
	// Получить указатель на интерфейс модуля
	usb3000_module = static_cast<IRTUSB3000 *>(CreateInstance("usb3000"));
	if (usb3000_module==NULL)
	{
		return 0;
	}
	
	short slot=0;
	// Поиск модуля USB в первых 127 слотах
	for(slot = 0; slot<127; slot++) 
		if (usb3000_module->OpenDevice(slot)) 
			break;
	
	// Если дошли до последнего слота, то модуль не обнаружен
	if (slot == 127)
	{
		return 0;
	}
		
	// Получим версию загруженного драйвера DSP из библиотеки Rtusbapi	
	if (!usb3000_module->LOAD_DSP())
	{
		return 0;
	}
	
	// Проинициализируем поле size структуры RTUSB3000::FLASH
	data_flash.size = sizeof(RTUSB3000::FLASH);
	
	// Получим информацию из ППЗУ модуля
	if (!usb3000_module->GET_FLASH(&data_flash))
	{
		return 0;
	}
	
	// Проверим, есть ли на модуле ЦАП
	if (!data_flash.IsDacPresented)
	{
		return 0;
	}
		
	// Проинициализируем поле size структуры RTUSB3000::OUTPUT_PARS
	data_dac.size = sizeof(RTUSB3000::OUTPUT_PARS);
	// Получим текущие параметры работы ЦАП
	if (!usb3000_module->GET_OUTPUT_PARS(&data_dac))
	{
		return 0;
	}
	
	return 1;
};

// Генерация сигнала и вывод на ЦАП

void usb3000_t::sl_output_data(void)
{	
	double frequency = 5;

	switch(type)
	{
		// Имитация шума с заданным уровнем 
		case 0:
            dac = (rand()%(noise*2)-noise)*2/5;
			
		// Имитация синусоидального сигнала
		case 1:
            double noise_level = rand()%(noise*2)-noise;
            if (lower == 1)
            { 
               // Затухающая синусоида
               dac = (SHORT)(((amplitude*sin(2.*M_PI*frequency*x) + noise_level)/x)*2/5);
            }
            else
            {   
               // Незатухающая синусоида
               dac = (SHORT)((amplitude*sin(2.*M_PI*frequency*x) + noise_level)*2/5);
            }
	}
   
   // вывод сигнала на 1 канал
	usb3000_module->WRITE_SAMPLE(WORD(0), &dac);
   Sleep(50);
   // вывод сигнала на 2 канал
	dac *= (SHORT)-1;
	usb3000_module->WRITE_SAMPLE(WORD(1), &dac);
   // инкрементируем временной коэффициент
	x += 1/data_dac.OutputRate;
};

void usb3000_t::sl_establish_type(int type_accept)
{
   type = type_accept;
   x = 0.01;
};

void usb3000_t::sl_establish_noise(int noise_accept)
{
   noise = noise_accept;
   x = 0.01;
};

void usb3000_t::sl_establish_amplitude(double amplitude_accept)
{
   amplitude = amplitude_accept;
   x = 0.01;
};

void usb3000_t::sl_establish_lower(int lower_accept)
{
   lower = lower_accept;
   x = 0.01;
};

////////////////////////////////////////////////////////////

// Освобождение доступа к модулю USB3000
// 1. Освобождаем интерфейс модуля.
// 2. Обнуляем указатель на модуль.
// 3. Выход из приложения

void usb3000_t::sl_exit(void)
{
	usb3000_module->ReleaseDevice();
	usb3000_module = NULL;
	QCoreApplication::exit(0);
}