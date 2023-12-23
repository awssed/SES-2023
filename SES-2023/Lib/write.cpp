#include <iostream>
#include <Windows.h>
#include<string>


#pragma warning(disable: 4996)
extern "C"
{
	void waitPause()
	{
		system("pause");
	}
  void writeString(char* type, char* str)
  {

	  setlocale(LC_ALL, "rus");
	  if(*type == 1) 
	  {
		  int value = static_cast<int>(*str); // Приводим значение первого байта к типу int
		  std::cout << value ;
	  }
	  if (*type == 2)
	  {		  int32_t value = 0;
			  value = *reinterpret_cast<int*>(str);
			  std::cout<< value ;
	  }
	  if (*type == 3)
	  {
		  if (*str == 1)
			  std::cout << "true";
		  if (*str == 0)
			  std::cout << "false";
	  }
	  if (*type == 7)
		  std::cout << *str;
  }
  void writeLineString(char* type, char* str)
  {
	  setlocale(LC_ALL, "rus");
	  if (*type == 1)
	  {
		  int value = static_cast<int>(*str); // Приводим значение первого байта к типу int
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
			  std::cout << *str;
	  std::cout << std::endl;
  }
  void readCon(char* num,char*type,char* value)
  {
	  LPCSTR message = "Произошла ошибка!\nНекорректное значение введено\nСтрока: ";
	  LPCSTR caption = "Ошибка при исполнении программы";

	  char errorMessage[256];
	  int messageLength = strlen(message);

	  strcpy(errorMessage, message);
	  for (int i = 0; i < strlen(num); i++)
	  {
		  errorMessage[messageLength] = *(num + i);
		  messageLength++;
	  }
	  errorMessage[messageLength] = '\0';
	  std::int64_t val;
	  char str[128];
	  if (*type == 1)
	  {
		  std::cin >> val;
		  if ((val >= (-128)) && (val <= 127))
		  {
			  *(int*)value = val;
			  return;
		  }
		  MessageBoxA(NULL, errorMessage, caption, MB_OK | MB_ICONERROR | MB_SETFOREGROUND);
	  }
	  if (*type == 2)
	  {
		  std::cin >> val;
		  
			  if ((val >= -2147483648) && (val <= 2147483648))
			  {
				  *(int*)value = val;
				  return;
			  }
			  MessageBoxA(NULL, errorMessage, caption, MB_OK | MB_ICONERROR | MB_SETFOREGROUND);
	  }
	  if (*type == 3)
	  {
			  std::cin.getline(str,128);
				  if (!std::strcmp(str, "true"))
				  {
					  *value = 1;
					  return;
				  }
				  if (!std::strcmp(str, "false"))
				  {
					  *value = 0;
					  return;
				  }

			  MessageBoxA(NULL, errorMessage, caption, MB_OK | MB_ICONERROR | MB_SETFOREGROUND);
			  return;
	  }
	  if (*type == 7)
	  {
		  std::cin.getline(str, 128);
		  for (int i = 0; i < strlen(value); i++)
		  {
			  value[i] = str[i];
		  }
		  return;
	  }
  }
  
}