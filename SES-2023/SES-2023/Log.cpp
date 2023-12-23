#include<iostream>
#include<ctime>
#include"Log.h"

namespace Log
{
	LOG getlog(wchar_t logfile[])
	{
		LOG temp;
		temp.stream = new std::ofstream;
		temp.stream->open(logfile);
		if (!temp.stream->is_open())
		{
			ERROR_THROW(112);
		}
		wcscpy_s(temp.logfile , logfile);
		return temp;
	}

	void WriteLine(LOG log, char* c, ...)
	{
		char** ptr	 = &c;
		int i = 0;
		while (*ptr != "") {
			*log.stream << *ptr;
			*ptr++;
		}
		*log.stream << std::endl;
	}

	void WriteLine(LOG log, wchar_t* c, ...)
	{
		wchar_t** ptr = &c;
		char l[1024] = "";
		char f[1024] = "";
		while (*ptr != L"")
		{
			wcstombs_s(0, l, *ptr, IN_MAX_LEN_TEXT);
			strcat_s(f, l);
			ptr++;
		}
		*log.stream << f;
	}

	void WriteLog(LOG log)
	{
		char date[100];
		tm local;
		time_t currentTime;
		currentTime = time(NULL);
		localtime_s(&local, &currentTime);
		strftime(date, 100, "%d.%m.%Y %H:%M:%S", &local);
		*log.stream << "----Протокол----" << date<<std::endl;
	}

	void WriteParm(LOG log, Parm::PARM parm)
	{
		char buff[PARM_MAX_SIZE];
		size_t tsize = 0;
		*log.stream << "----Параметры----" << std::endl;
		wcstombs_s(&tsize, buff, parm.log, PARM_MAX_SIZE);
		*log.stream << "-log:" << buff << std::endl;
		wcstombs_s(&tsize, buff, parm.out, PARM_MAX_SIZE);
		*log.stream << "-out: " << buff << std::endl;
		wcstombs_s(&tsize, buff, parm.in, PARM_MAX_SIZE);
		*log.stream << "-in: " << buff << std::endl;
	}

	void WriteIn(LOG log, In::IN in)
	{
		*log.stream << "----Исходные данные----" << std::endl;
		*log.stream << "Количество символов: " << in.size <<std::endl;
		*log.stream << "Проигнорировано: " << in.ignore << std::endl;
		*log.stream << "Количество строк: " << in.lines << std::endl;
	}

	void WriteError(LOG log, Error::ERROR error)
	{
		*log.stream << "Ошибка: " << error.id << ":" << error.message << std:: endl;
		if (error.inext.line != -1)
		{
			*log.stream << "Строка: " << error.inext.line << " Позиция: " << error.inext.col << std::endl;
		}
	}

	void Close(LOG log)
	{
		log.stream->close();
		delete log.stream;
	}
}