#include <iostream>
#include <Windows.h>
#include <ctime>
#pragma warning(disable: 4996)
extern "C"
{
	void ErrorType(char* str)
	{
		LPCSTR message = "��������� ������!\n������������� ����� ���������\ ����������\n������: ";
		LPCSTR caption = "������ ��� ���������� ���������";

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
		LPCSTR message = "��������� ������!\n���� ����\n������: ";
		LPCSTR caption = "������ ��� ���������� ���������";

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
		LPCSTR message = "��������� ������!\n���� ����������\n������: ";
		LPCSTR caption = "������ ��� ���������� ���������";

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
		LPCSTR message = "��������� ������!\n����� �� ������� �������/������\n������: ";
		LPCSTR caption = "������ ��� ���������� ���������";

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