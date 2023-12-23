#include <iostream>
#include <Windows.h>
#include <ctime>
#pragma warning(disable: 4996)
extern "C"
{
	void ErrorType(char* str)
	{
		LPCSTR message = "Произошла ошибка!\nНесоответсвие типов операндов\ параметров\nСтрока: ";
		LPCSTR caption = "Ошибка при исполнении программы";

		char errorMessage[256];
		int messageLength = strlen(message);

		strcpy(errorMessage, message);
		for (int i = 0; i < strlen(str); i++)
		{
			errorMessage[messageLength] = *(str+i);
			messageLength++;
		}
		errorMessage[messageLength] = '\0';

		MessageBoxA(NULL, errorMessage, caption, MB_OK | MB_ICONERROR | MB_SETFOREGROUND);
	}
	void ErrorStackEmpty(char* str)
	{
		LPCSTR message = "Произошла ошибка!\nСтек пуст\nСтрока: ";
		LPCSTR caption = "Ошибка при исполнении программы";

		char errorMessage[256];
		int messageLength = strlen(message);

		strcpy(errorMessage, message);
		for (int i = 0; i < strlen(str); i++)
		{
			errorMessage[messageLength] = *(str + i);
			messageLength++;
		}
		errorMessage[messageLength] = '\0';

		MessageBoxA(NULL, errorMessage, caption, MB_OK | MB_ICONERROR | MB_SETFOREGROUND);
	}
	void ErrorStackOverflow(char* str)
	{
		LPCSTR message = "Произошла ошибка!\nСтек переполнен\nСтрока: ";
		LPCSTR caption = "Ошибка при исполнении программы";

		char errorMessage[256];
		int messageLength = strlen(message);

		strcpy(errorMessage, message);
		for (int i = 0; i < strlen(str); i++)
		{
			errorMessage[messageLength] = *(str + i);
			messageLength++;
		}
		errorMessage[messageLength] = '\0';

		MessageBoxA(NULL, errorMessage, caption, MB_OK | MB_ICONERROR | MB_SETFOREGROUND);
	}
	void ErrorIncorInd(char* str)
	{
		LPCSTR message = "Произошла ошибка!\nВыход за пределы массива/строки\nСтрока: ";
		LPCSTR caption = "Ошибка при исполнении программы";

		char errorMessage[256];
		int messageLength = strlen(message);

		strcpy(errorMessage, message);
		for (int i = 0; i < strlen(str); i++)
		{
			errorMessage[messageLength] = *(str + i);
			messageLength++;
		}
		errorMessage[messageLength] = '\0';

		MessageBoxA(NULL, errorMessage, caption, MB_OK | MB_ICONERROR | MB_SETFOREGROUND);
	}

}