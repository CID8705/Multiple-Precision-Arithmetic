/*		m_set.c		double --> MPA	*/
#include "mpa.h"

MPA m_set(double a)
{
	MPA m;
	int i;
	UINT *p;
	double t;

	m = _M0;
	if(a == 0.)	return m;
	m.zero = 0;
	if(a < 0.)
	{
		m.sign = 0;
		a = - a;
	}
	while(a >= (double)RADIX)
	{
		m.exp++;
		a /= (double)RADIX;
	}
	while(a < 1.)
	{
		m.exp--;
		a *= (double)RADIX;
	}
	p = m.num;
	i = 0;
	do
	{
		*p = (UINT)a;
		a -= (double)*p++;
		a *= (double)RADIX;
	} while(a != 0. && ++i <= NMPA);
	for(i++; i <= NMPA; i++)	*p++ = 0;
	return m;
}

/*		m_set_a			"xxx" --> MPA	*/

MPA m_set_a(char *s)
{
	MPA a, t;
	char *p;
	int c, exp, i, pflag, sign, zflag;
	UINT *q;

	p = s;
	sign = 1;
	if(*p == '-')
	{
		sign = 0;
		p++;
	}else if(*p == '+')	p++;
	a = t = _M0;
	t.zero = 0;
	exp = 0;
	pflag = zflag = 0;
	for(; *p != '\0'; p++)
	{
		if(*p == '.')
		{
			if(pflag)
			{
				fprintf(stderr, "Error : Illegal parameter in m_set_a()\n");
				return _M0;
			}
			pflag = 1;
		}
		else if(*p == 'E' || *p == 'e')
		{
			p++;
			exp -= atoi(p);
			break;
		}
		else if(*p == '+' || *p == '-')
		{
			exp -= atoi(p);
			break;
		}
		else if(*p != ' ' && (*p < '0' || *p > '9'))
		{
			fprintf(stderr, "Error : Illegal parameter  in m_set_a()\n");
			return _M0;
		}
		else
		{
			c = *p - '0';
			if(c != 0 || pflag != 0)	zflag = -1;
			else
			{
				if(zflag == 0)	zflag = 1;
				else if(zflag == 1)
				{
					fprintf(stderr, "Error : Illegal parameter  in m_set_a()\n");
					return _M0;
				}
			}
			m_mul1_s(&a, 10);
			if(c)
			{
				t.num[0] = c;
				a = m_add(a, t);
/*
				a = m_add_a(a, t);
*/
			}
			if(pflag == 1)	exp++;
		}
	}
	if(exp > MAXEXP)
	{
		fprintf(stderr, "Error : Overflow  in m_set_a()\n");
		return _MMAX;
	}
	if(exp < MINEXP)
	{
		fprintf(stderr, "Error : Underflow  in m_set_a()\n");
		return _M0;
	}
	a.sign = sign;
	if(exp > 0)	while(--exp >= 0)	m_div1_s(&a, 10);
	else		while(++exp <= 0)	m_mul1_s(&a, 10);
	m_z_chk(&a);
	return a;
}

/*		m_set_l.c		MPA <-- long	*/

MPA m_set_l(long n)
{
	MPA a;
	UINT *p, *q, w;

	a = _M0;
	if(n == 0L)	return a;
	a.zero = 0;
	if(n < 0L)
	{
		a.sign = 0;
		n = - n;
	}
	p = q = a.num;
	while(n != 0)
	{
		*p++ = n % RADIX;
		n /= RADIX;
		a.exp++;
	}
	a.exp--;
	p--;
	while(q < p)
	{
		w = *p;
		*p-- = *q;
		*q++ = w;
	}
	return a;
}

/*		m_int		integer MPA --> MPA		*/

MPA m_int(MPA a)
{
	int i;

	if(a.zero || a.exp < 0)	return _M0;
	if(a.exp >= NMPA)	return a;
	for(i = a.exp + 1; i <= NMPA; i++)	a.num[i] = 0;
	return a;
}

/*		m_frac			MPA - integer MPA --> MPA	*/

MPA m_frac(MPA a)
{
	MPA b;
	UINT *p, *q;
	int i;

	if(a.zero || a.exp >= NMPA)	return _M0;
	if(a.exp < 0)	return a;
	b.zero = 0;
	b.sign = a.sign;
	b.exp = -1;
	for(i = a.exp + 1, p = a.num + i, q = b.num; i <= NMPA; i++)
		*q++ = *p++;
	for(i = 0; i <= a.exp; i++)	*q++ = 0;
	return	b;
}

/*		m_round			round(MPA, n) --> MPA	*/

MPA m_round(MPA a, int n)
{
	MPA t;
	char s[15];

	sprintf_s(s, _countof(s), "+1.0e%d\0", n);
	t = m_set_a(s);
	return m_mul(m_int(m_add(m_div(a, t), m_set_a("0.5"))), t);
}
