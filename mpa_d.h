/*		mpa_d.h		*/
#ifdef		_MPA
#define _USE_MATH_DEFINES
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <float.h>
#include <math.h>
/*
		NMPA1 = NMPA + 1
		NMPA2 = NMPA1 * 2
		MMPA  = NMPA1 * log10(RADIX) / 4
*/
#define		NMPA		100
#define		NMPA1		101
#define		NMPA2		202
#define		MMPA		114

#define		RADIXBITS	15
#define		RADIX		0x8000			/* = 2 ^ RADIXBITS */
#define		RADIX1		0x7fff			/* = RADIX - 1 */
#define		RADIX_2		16384			/* = RADIX / 2 */
#define		RADIX2		1073741824L		/* = RADIX ^ 2 */
#define		MAXEXP		16383
#define		MINEXP		-16384
#define		MAX_LONG	0x7FFFFFFFL
#define		MIN_LONG	0x80000000L
#define		MAX_K		180				/* < (sqrt(4 * RADIX + 1) - 1) * 0.5 */

typedef		unsigned int		UINT;
typedef		unsigned long		ULONG;
typedef		struct
			{
				int sign;
				int exp;
				int zero;
				UINT num[NMPA1];
			}							MPA;

#endif
