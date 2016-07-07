/*		mpa.h		MPA : include file 			*/
/*				Multiple-Precision Arithmetic	*/
#ifndef		_MPA

#define		_MPA

#ifdef _DEBUG
#define EXT_STR "_d.lib"
#else
#define EXT_STR ".lib"
#endif

#pragma comment(lib, "MPA" EXT_STR)

#include "mpa_d.h"
#include "mpa_p.h"
#include "mpa_v.h"

#endif
