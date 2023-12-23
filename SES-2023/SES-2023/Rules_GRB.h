#pragma once
#include "GRB.h"
#include"Error.h"
#define GRB_ERROR_SERIES 600
#define NS(n) GRB::Rule::Chain::N(n)
#define TS(n) GRB::Rule::Chain::T(n)
#define ISNS(n)	GRB::Rule::Chain::isN(n)

namespace GRB
{
	Greibach greibach(NS('S'), TS('!'),				//стартовый символ, дно стека
		6,											//количество правил
		Rule(NS('S'), GRB_ERROR_SERIES + 0,			//Неверная структура программы
			5, //S->m{ N } | fti(W) { Nir}S|fati(W) { Nir}S|tiS
			Rule::Chain(4, TS('m'), TS('{'), NS('N'), TS('}')),
			Rule::Chain(12, TS('f'), TS('t'), TS('i'), TS('('), NS('W'), TS(')'), TS('{'), NS('N'), TS('i'), TS('q'), TS('}'), NS('S')),
			Rule::Chain(11, TS('f'), TS('t'), TS('i'), TS('('), NS('W'), TS(')'), TS('{'), TS('i'), TS('q'), TS('}'), NS('S')),
			Rule::Chain(12, TS('f'), TS('t'), TS('i'), TS('('), NS('W'), TS(')'), TS('{'), NS('N'), TS('l'), TS('q'), TS('}'), NS('S')),
			Rule::Chain(11, TS('f'), TS('t'), TS('i'), TS('('), NS('W'), TS(')'), TS('{'), TS('l'), TS('q'), TS('}'), NS('S'))
		),
		Rule(NS('N'), GRB_ERROR_SERIES + 1,			//Операторы программы
			66,		//N	->i|iN|L|LN|ti|tiN|ati|atiN|z(N){N}|z(N){N}N|h(N){N}|h(N){N}N|i$|i$N|ii@$|ii@$N|iL@$|iL@$N|w|wN|x|xN|h|hN|d|dN|r|rN|s|sN|o|oN|t|tN|e|eN|c|cN|p|pN|l|lN|+|+N|-|-N|*|*N|/|/N|ii@|ii@N|iL@|iLN@
			Rule::Chain(1, TS('i')),//
			Rule::Chain(2, TS('i'), NS('N')),//
			Rule::Chain(1, TS('l')),//
			Rule::Chain(2, TS('l'), NS('N')),//
			Rule::Chain(2, TS('t'), TS('i')),//
			Rule::Chain(3, TS('t'), TS('i'), NS('N')),//
			Rule::Chain(5, TS('a'), TS('t'), TS('i'), TS('l'), TS('@')),//тут дыл добавлен количесвто индексов
			Rule::Chain(6, TS('a'), TS('t'), TS('i'), TS('l'), TS('@'), NS('N')),//atiL@
			Rule::Chain(4, TS('t'), TS('i'), TS('l'), TS('@')),//тут дыл добавлен количесвто индексов
			Rule::Chain(5, TS('t'), TS('i'), TS('l'), TS('@'), NS('N')),//atiL@
			Rule::Chain(8, TS('z'), TS('('), NS('N'), TS(')'), TS('{'), NS('N'), TS('}'), NS('N')),//
			Rule::Chain(7, TS('z'), TS('('), NS('N'), TS(')'), TS('{'), NS('N'), TS('}')),//
			Rule::Chain(7, TS('h'), TS('('), NS('N'), TS(')'), TS('{'), NS('N'), TS('}')),//
			Rule::Chain(8, TS('h'), TS('('), NS('N'), TS(')'), TS('{'), NS('N'), TS('}'), NS('N')),//
			Rule::Chain(2, TS('i'), TS('$')),//
			Rule::Chain(3, TS('i'), TS('$'), NS('N')),//
			Rule::Chain(4, TS('i'), TS('i'), TS('@'), TS('$')),//
			Rule::Chain(5, TS('i'), TS('i'), TS('@'), TS('$'), NS('N')),//
			Rule::Chain(4, TS('i'), TS('l'), TS('@'), TS('$')),//
			Rule::Chain(5, TS('i'), TS('l'), TS('@'), TS('$'), NS('N')),//
			Rule::Chain(1, TS('w')),//
			Rule::Chain(2, TS('w'), NS('N')),//
			Rule::Chain(1, TS('x')),//
			Rule::Chain(2, TS('x'), NS('N')),//
			Rule::Chain(1, TS('d')),//
			Rule::Chain(2, TS('d'), NS('N')),//
			Rule::Chain(1, TS('r')),//
			Rule::Chain(2, TS('r'), NS('N')),//
			Rule::Chain(1, TS('s')),//
			Rule::Chain(2, TS('s'), NS('N')),//
			Rule::Chain(1, TS('o')),//
			Rule::Chain(2, TS('o'), NS('N')),//
			Rule::Chain(2,TS('i'),TS('n')),
			Rule::Chain(3, TS('i'), TS('n'),NS('N')),
			/*Rule::Chain(1, TS('t')),
			Rule::Chain(2, TS('t'), NS('N')),*/
			Rule::Chain(1, TS('e')),//
			Rule::Chain(2, TS('e'), NS('N')),//
			Rule::Chain(1, TS('c')),
			Rule::Chain(2, TS('c'), NS('N')),
			Rule::Chain(1, TS('+')),
			Rule::Chain(2, TS('+'), NS('N')),
			Rule::Chain(1, TS('-')),
			Rule::Chain(2, TS('-'), NS('N')),
			Rule::Chain(1, TS('*')),
			Rule::Chain(2, TS('*'), NS('N')),
			Rule::Chain(1, TS('/')),
			Rule::Chain(2, TS('/'), NS('N')),
			Rule::Chain(1, TS('=')),
			Rule::Chain(2, TS('='), NS('N')),
			Rule::Chain(1, TS('>')),//добавить в записку
			Rule::Chain(2, TS('>'), NS('N')),
			Rule::Chain(1, TS('<')),
			Rule::Chain(2, TS('<'), NS('N')),
			Rule::Chain(1, TS('p')),
			Rule::Chain(2, TS('p'), NS('N')),
			Rule::Chain(1, TS('k')),
			Rule::Chain(2, TS('k'), NS('N')),
			Rule::Chain(1, TS('j')),
			Rule::Chain(2, TS('j'), NS('N')),
			Rule::Chain(3, TS('i'), TS('i'), TS('@')),
			Rule::Chain(4, TS('i'), TS('i'), TS('@'), NS('N')),
			Rule::Chain(3, TS('i'), TS('l'), TS('@')),
			Rule::Chain(4, TS('i'), TS('l'), TS('@'), NS('N')),
			Rule::Chain(2, TS('i'), TS('q')),//добавить в записку
			Rule::Chain(3, TS('i'), TS('q'), NS('N')),
			Rule::Chain(2, TS('l'), TS('q')),
			Rule::Chain(2, TS('l'), TS('q'), NS('N'))
		),
		Rule(NS('W'), GRB_ERROR_SERIES + 3,			//параметры функции
			2,		//W->ti|ti,W|ati|ati,W
			Rule::Chain(2, TS('t'), TS('i')),
			Rule::Chain(4, TS('t'), TS('i'), TS(','), NS('W'))
		)
	);
}
