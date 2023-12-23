#include"stdafx.h"
#include"Parm.h"
#include"Error.h"

namespace Parm
{
	PARM getparm(int argc, wchar_t* argv[])
	{
		PARM parm;
		bool in_find = 0, out_find = 0, log_find = 0;
		for (int i = 0; i < argc; i++)
		{
			if (wcslen(argv[i]) > PARM_MAX_SIZE)
			{
				throw ERROR_THROW(104);
			}
			if (wcsstr(argv[i], PARM_IN))
			{
				wcscpy_s(parm.in, argv[i] + wcslen(PARM_IN));
				in_find = 1;
			}
			if (wcsstr(argv[i], PARM_OUT))
			{
				wcscpy_s(parm.out, argv[i] + wcslen(PARM_OUT));
				out_find = 1;
			}
			if (wcsstr(argv[i], PARM_LOG))
			{
				wcscpy_s(parm.log, argv[i] + wcslen(PARM_LOG));
				log_find = 1;
			}
		}
			if (!in_find)
			{
				throw ERROR_THROW(100);
			}
			if (!out_find)
			{
				wcscpy_s(parm.out, parm.in);
				wcscat(parm.out, PARM_OUT_DEFAULT_EXT);
			}
			if (!log_find)
			{
				wcscpy(parm.log, parm.in);
				wcscat(parm.log, PARM_LOG_DEFAULT_EXT);
			}
		return parm;
	}
}