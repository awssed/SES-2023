#include <iostream>
#include <Windows.h>
#include <ctime>
#pragma warning(disable: 4996)
extern "C"
{
  void writeString(char* type, char* str)
  {
	  if (*type == 1)
		  std::cout << int(str);
	  if(*type==7)
		for (int i = 0; i < strlen(str); i++)
		  std::cout << str[i];
  }

}