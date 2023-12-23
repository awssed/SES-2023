#include <iostream>
#include <Windows.h>
#include <ctime>
#pragma warning(disable: 4996)
extern "C"
{
	uint8_t* factor_fun(char* type, char* value)
	{
		static uint8_t bytes[5];
		bytes[0] = 2;
		int result=1;
		if (*type == 1)
		{
			int val = 0;
			val = static_cast<int>(*value);
			for (int i = 1; i <= val; i++)
			{
				result *= i;
			}
		}
		if (*type == 2)
		{
			int32_t val = 0;
			val = *reinterpret_cast<int*>(value);
			for (int i = 1; i <= val; i++)
			{
				result *= i;
			}
		}
		uint8_t* resultBytes = reinterpret_cast<uint8_t*>(&result);
		for (int i = 0; i < 4; i++) {
			bytes[i + 1] = resultBytes[i];
		}
		return bytes;

	}
	uint8_t* power_fun(char* type1, char* val1, char* type2, char* val2)
	{
		int result;
		static uint8_t bytes[5];
		bytes[0] = 2;
		int32_t value= 0;
		int32_t exp = 0;
		if (*type1 == 1)
		{
			value = static_cast<int>(*val1);
		}
		if (*type1 == 2)
			value = *reinterpret_cast<int*>(val1);
		if (*type2 == 1)
		{
			exp = static_cast<int>(*val2);
		}
		if (*type2 == 2)	
			exp = *reinterpret_cast<int*>(val2);
		result = pow(value, exp);
		uint8_t* resultBytes = reinterpret_cast<uint8_t*>(&result);
		for (int i = 0; i < 4; i++) {
			bytes[i + 1] = resultBytes[i];
		}
		return bytes;
	}

}