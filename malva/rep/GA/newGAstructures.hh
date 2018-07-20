#ifndef INC_newGA_mallba_hh
#define INC_newGA_mallba_hh


#include <iostream>
#include <fstream>
#include <math.h>
#include <limits.h>
#include <float.h>
#include "../../src/Rlist.h"
#include "../../src/Rarray.h"
#include "../../src/Messages.h"
#include "../../src/mallba.hh"
#include "../../src/States.hh"
#include "../../src/random.hh"
#include "../../src/time.hh"
#include "../../src/netstream.hh"
#include <assert.h>

using namespace std;

#ifndef _INDIVIDUAL_
#define _INDIVIDUAL_

struct individual // index of a individual in the population and its fitness
{
	int    index;
	double fitness;
	double sel_parameter;
	bool   change;
};

/*int lessF(const struct individual &i1,const  struct individual &i2)
{
	return i1.fitness < i2.fitness;
}

int lessS(const struct individual &i1,const  struct individual &i2)
{
	return i1.sel_parameter < i2.sel_parameter;
}

int greaterF(const struct individual &i1,const  struct individual &i2)
{
	return i1.fitness > i2.fitness;
}

int greaterS(const struct individual &i1,const  struct individual &i2)
{
	return i1.sel_parameter > i2.sel_parameter;
}*/
#endif
#endif
