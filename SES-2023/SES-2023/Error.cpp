#include"stdafx.h"
#include"Error.h"
namespace Error
{
	//0-99 ñèñòåìíûå îøèáêè
	//100-109 îøèáêè ïàğàìåòğîâ
	//110-119îøèáêè îòêğûòèÿ è ÷òåíèÿ ôàéëîâ
	ERROR errors[ERROR_MAX_ENTRY] = {
		ERROR_ENTRY(0,"Íåäîïóñòèìûé êîä îøèáêè"),
		ERROR_ENTRY(1,"Ñèñòåìíûé ñáîé"),
		ERROR_ENTRY(2,"Îøèáî÷íîå âûğàæíèå"),
		ERROR_ENTRY(3,"Íåèçâåñòíàÿ áèáëèîòåêà"),
		ERROR_ENTRY_NODEF(4), ERROR_ENTRY_NODEF(5),
		ERROR_ENTRY_NODEF(6), ERROR_ENTRY_NODEF(7), ERROR_ENTRY_NODEF(8), ERROR_ENTRY_NODEF(9),
		ERROR_ENTRY_NODEF10(10), ERROR_ENTRY_NODEF10(20), ERROR_ENTRY_NODEF10(30), ERROR_ENTRY_NODEF10(40),
		ERROR_ENTRY_NODEF10(50), ERROR_ENTRY_NODEF10(60), ERROR_ENTRY_NODEF10(70), ERROR_ENTRY_NODEF10(80),ERROR_ENTRY_NODEF10(90),
		ERROR_ENTRY(100,"Ïàğàìåòğ -in äîëæåí áûòü çàäàí"),
		ERROR_ENTRY_NODEF(101), ERROR_ENTRY_NODEF(102),ERROR_ENTRY_NODEF(103),
		ERROR_ENTRY(104,"Ïğåâûøåíà äëèíà âõîäíîãî ïàğàìåòğà"),	
		ERROR_ENTRY(105,"Îøèáêà ïğè ñîçäàíèè âûõîäíîãî ôàéëà ñ ğàñøèğåíèåì .out"),//113
		ERROR_ENTRY(106,"Íåäîïóñòèìûé ğàçìåğ òàáëèöû ëåêñåì"),//114
		ERROR_ENTRY(107,"Ïğåâûøåí ğàçìåğ òàáëèöû ëåêñåì"),//115
		ERROR_ENTRY_NODEF(108),ERROR_ENTRY_NODEF(109),
		ERROR_ENTRY(110,"Îøèáêà ïğè îòêğûòèè ôàéëà ñ èñõîäíûì êîäîì (-in)"),
		ERROR_ENTRY(111,"Íåäîïóñòèìûé ñèìâîë â èñõîäíîì ôàéëå (-in)"),
		ERROR_ENTRY(112,"Îøèáêà ïğè ñîçäàíèè ôàéëà ñ ïğîòîêîëîì (-log)"),
		ERROR_ENTRY(113,"Íåäîïóñòèìûé èäåíòèôèêàòîğ"),
		ERROR_ENTRY(114,"Äóáëèğîâàíèå èäåíòèôèêàòîğà"),//105
		ERROR_ENTRY(115,"Èäåíòèôèêàòîğ íå îïğåäåë¸í"),//106
		ERROR_ENTRY(116,"Íåêîğğåêòíîå èñïîëüçîâàíèå èíäåêñà"),//107
		ERROR_ENTRY(117,"Íåäîïóñòèìûé ğàçìåğ òàáëèöû èäåíòèôèêàòîğîâ"),//íàğóøåíà íóìåğàöèÿ îøèáîê
		ERROR_ENTRY(118,"Ïğåâûøåí ğàçìåğ òàáëèöû èäåíòèôèêàòîğîâ"),
		ERROR_ENTRY(119,"Ïğåâûøåíà äëèíà ëåêñåìû"),
		ERROR_ENTRY(120,"Ïğåâûøåíî ìàêñèìàëüíîå äîïóñòèìîå êîëè÷åñòâî ïàğàìåòğîâ ó ôóíêöèè"),//íå èñïîëüçóåòñÿ
		ERROR_ENTRY_NODEF(121) ,
		ERROR_ENTRY(122, "Âûğàæåíèå äîëæíî èìåòü òèï  bool"),
		ERROR_ENTRY(123, "Âûøåïåğå÷èñëåííûå ïåğåìåííûå íå ïğîèöèíèöèëèçèğîâàíû"),
		ERROR_ENTRY(124,"Âûõîä çà ïğåäåëû ìàññèâà"),
		ERROR_ENTRY(125,"Íåñîîòâåòñòâèå òèïà âîçâğàùàåìîãî çíà÷åíèÿ"),
		ERROR_ENTRY(126, "Íåêîğğåêòíûé áëîê êîäà"),
		ERROR_ENTRY(127,"Ïğèñâîèòü ìîæíî çíà÷åíèå ìîæíî òîëüêî ïåğåìåííîé"),
		ERROR_ENTRY(128,"×òåíèå äîñòóïíî òîëüêî äëÿ ïåğåìåííîé"),//ïåğåìåñòèòü
		ERROR_ENTRY(129,"Ìàêñèìàëüíûé ğàçìåğ ñòğîêè/ìàññèâà 128(íå ìåíüøå íóëÿ)"),
		ERROR_ENTRY_NODEF10(130),ERROR_ENTRY_NODEF10(140),ERROR_ENTRY_NODEF10(150),ERROR_ENTRY_NODEF10(160),
		ERROR_ENTRY_NODEF10(170),ERROR_ENTRY_NODEF10(180),ERROR_ENTRY_NODEF10(190),ERROR_ENTRY_NODEF100(200),ERROR_ENTRY_NODEF100(300),
		ERROR_ENTRY_NODEF100(400),ERROR_ENTRY_NODEF100(500),
		ERROR_ENTRY(600,"Íåâåğíàÿ ñòğóêòóğà ïğîãğàììû"),
		ERROR_ENTRY(601,"Îøèáî÷íûé îïåğàòîğ"),
		ERROR_ENTRY(602,"Îøèáêà â âûğàæåíèè"),
		ERROR_ENTRY(603,"Îøèáêà â ïàğàìåòğàõ ôóíêöèè"),
		ERROR_ENTRY(604,"Îøèáêà â ïàğàìåòğàõ îáüúÿâëÿåìîé ôóíêöèè"),
		ERROR_ENTRY(605,"Ñèíòàêñè÷åñêè àíàëèç çàâåğø¸í äîñğî÷íî"),
		ERROR_ENTRY_NODEF(606),ERROR_ENTRY_NODEF(607),ERROR_ENTRY_NODEF(608),ERROR_ENTRY_NODEF(609),ERROR_ENTRY_NODEF10(610),
		ERROR_ENTRY_NODEF10(620),ERROR_ENTRY_NODEF10(630),ERROR_ENTRY_NODEF10(640),ERROR_ENTRY_NODEF10(650),ERROR_ENTRY_NODEF10(660),ERROR_ENTRY_NODEF10(670),
		ERROR_ENTRY_NODEF10(680),ERROR_ENTRY_NODEF10(690),
		ERROR_ENTRY_NODEF100(700),ERROR_ENTRY_NODEF100(800),
		ERROR_ENTRY_NODEF100(900)
	};
	ERROR geterror(int id)
	{
		if (id > 0 && id < ERROR_MAX_ENTRY)
		{
			return errors[id];
		}
		else
		{
			return errors[0];
		}
	}
	ERROR geterrorin(int id, int line = -1, int col = -1)
	{
		if (id > 0 && id < ERROR_MAX_ENTRY)	
		{
			errors[id].inext.col = col;
			errors[id].inext.line = line;
			return errors[id];
		}
		else
		{
			return errors[0];
		}
	}
};