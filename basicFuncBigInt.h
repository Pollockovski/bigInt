#pragma once
#include"bigInt.h"


bigInt abs(bigInt a)
{
	a.value[0] = true;
	return a;
}

bigInt opp(bigInt a)
{
	a.value[0] = !a.value[0];
	return a;
}