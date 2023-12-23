#include <iostream>
#include <Windows.h>
#include <ctime>
#pragma warning(disable: 4996)
extern "C"
{
	uint8_t* length_fun(char* type, char* str)
	{
		int result;
		static uint8_t bytes[5];
		bytes[0] = 2;
		if (*type == 7)
		{
			result = strlen(str);
		}
		uint8_t* resultBytes = reinterpret_cast<uint8_t*>(&result);
		for (int i = 0; i < 4; i++) {
			bytes[i + 1] = resultBytes[i];
		}
		return bytes;
	}
	uint8_t* compS_fun(char* type1, char* str1, char* type2, char* str2)
	{
		static uint8_t bytes[2];
		bytes[0] = 3;
		if (*type1 == 7 && *type2 == 7)
		{
			if (*str1==*str2)
			{
				bytes[1] = 1;
				return bytes;
			}
			else
			{
				bytes[1] = 0;
				return bytes;
			}
		}
		else
		{
			bytes[1] = 0;
			return bytes;
		}
		bytes[1] = 0;
		return bytes;
	}
	uint8_t* compare_fun(char* type1, char* str1, char* type2, char* str2)
	{
		static uint8_t bytes[2];
		bytes[0] = 3;
		if (*type1 == 7 && *type2 == 7)
		{
			if (strlen(str1) == strlen(str2))
			{
				for (int i = 0; i < strlen(str1); i++)
				{
					if (str1[i] != str2[i])
					{
						bytes[1] = 0;
						return bytes;
					}
				}
			}
			else
			{
				bytes[1] = 0;
				return bytes;
			}
		}
		else
		{
			bytes[1] = 0;
			return bytes;
		}
		bytes[1] = 1;
		return bytes;
	}
	void print_fun(char* type, char* str)
	{
		setlocale(LC_ALL, "rus");
		if (*type == 1)
		{
			int value = static_cast<int>(*str); // ѕриводим значение первого байта к типу int
			std::cout << value;
		}
		if (*type == 2)
		{
			int32_t value = 0;
			value = *reinterpret_cast<int*>(str);
			std::cout << value;
		}
		if (*type == 3)
		{
			if (*str == 1)
				std::cout << "true";
			if (*str == 0)
				std::cout << "false";
		}
		if (*type == 7)
			for (int i = 0; i < strlen(str); i++)
			{
				std::cout << str[i];
			}
		std::cout << std::endl;
	}
}
