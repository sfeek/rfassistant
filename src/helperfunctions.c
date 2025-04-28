#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <complex.h>
#include "../include/helperfunctions.h"
#include "../include/ghcommon.h"

/* Show frequency */
void showfrequency(double v)
{
	double a = fabs(v);

	if (a >= 1e9)
	{
		printf("%3.3f GHz", v / 1e9);
		return;
	}

	if (a >= 1e6)
	{
		printf("%3.3f MHz", v / 1e6);
		return;
	}

	if (a >= 1e3)
	{
		printf("%3.3f KHz", v / 1e3);
		return;
	}

	printf("%3.3f Hz", v);
	return;
}

/* Show Capacitance */
void showcapacitance(double v)
{
	double a = fabs(v);

	if (a >= 1e0)
	{
		printf("%3.3f F", v);
		return;
	}

	if (a >= 1e-3)
	{
		printf("%3.3f mF", v / 1e-3);
		return;
	}

	if (a >= 1e-6)
	{
		printf("%3.3f μF", v / 1e-6);
		return;
	}

	if (a >= 1e-9)
	{
		printf("%3.3f nF", v / 1e-9);
		return;
	}

	if (a >= 1e-12)
	{
		printf("%3.3f pF", v / 1e-12);
		return;
	}

	printf("%e F", v);
	return;
}

/* Show Inductance */
void showinductance(double v)
{
	double a = fabs(v);

	if (a >= 1e0)
	{
		printf("%3.3f H", v);
		return;
	}

	if (a >= 1e-3)
	{
		printf("%3.3f mH", v / 1e-3);
		return;
	}

	if (a >= 1e-6)
	{
		printf("%3.3f μH", v / 1e-6);
		return;
	}

	if (a >= 1e-9)
	{
		printf("%3.3f nH", v / 1e-9);
		return;
	}

	if (a >= 1e-12)
	{
		printf("%3.3f pH", v / 1e-12);
		return;
	}

	printf("%e H", v);
	return;
}

/* Show Resistance */
void showresistance(double v)
{
	double a = fabs(v);

	if (a >= 1e9)
	{
		printf("%3.3f GΩ", v / 1e9);
		return;
	}

	if (a >= 1e6)
	{
		printf("%3.3f MΩ", v / 1e6);
		return;
	}

	if (a >= 1e3)
	{
		printf("%3.3f KΩ", v / 1e3);
		return;
	}

	if (a >= 1e0)
	{
		printf("%3.3f Ω ", v);
		return;
	}

	if (a >= 1e-3)
	{
		printf("%3.3f mΩ", v / 1e-3);
		return;
	}

	if (a >= 1e-6)
	{
		printf("%3.3f μΩ", v / 1e-6);
		return;
	}

	printf("%e Ω", v);
	return;
}

/* Show Power */
void showpower(double v)
{
	double a = fabs(v);

	if (a >= 1e9)
	{
		printf("%3.3f GW", v / 1e9);
		return;
	}

	if (a >= 1e6)
	{
		printf("%3.3f MW", v / 1e6);
		return;
	}

	if (a >= 1e3)
	{
		printf("%3.3f KW", v / 1e3);
		return;
	}

	if (a >= 1e0)
	{
		printf("%3.3f W", v);
		return;
	}

	if (a >= 1e-3)
	{
		printf("%3.3f mW", v / 1e-3);
		return;
	}

	if (a >= 1e-6)
	{
		printf("%3.3f μW", v / 1e-6);
		return;
	}

	if (a >= 1e-9)
	{
		printf("%3.3f nW", v / 1e-9);
		return;
	}

	if (a >= 1e-12)
	{
		printf("%3.3f pW", v / 1e-12);
		return;
	}

	printf("%e W", v);
	return;
}

/* Show Voltage */
void showvoltage(double v)
{
	double a = fabs(v);

	if (a >= 1e6)
	{
		printf("%3.3f MV", v / 1e6);
		return;
	}

	if (a >= 1e3)
	{
		printf("%3.3f KV", v / 1e3);
		return;
	}

	if (a >= 1e0)
	{
		printf("%3.3f V", v);
		return;
	}

	if (a >= 1e-3)
	{
		printf("%3.3f mV", v / 1e-3);
		return;
	}

	if (a >= 1e-6)
	{
		printf("%3.3f μV", v / 1e-6);
		return;
	}

	if (a >= 1e-9)
	{
		printf("%3.3f nV", v / 1e-9);
		return;
	}

	printf("%e V", v);
	return;
}

/* Show Amperage */
void showamperage(double v)
{
	double a = fabs(v);

	if (a >= 1e3)
	{
		printf("%3.3f KA", v / 1e3);
		return;
	}

	if (a >= 1e0)
	{
		printf("%3.3f A", v);
		return;
	}

	if (a >= 1e-3)
	{
		printf("%3.3f mA", v / 1e-3);
		return;
	}

	if (a >= 1e-6)
	{
		printf("%3.3f μA", v / 1e-6);
		return;
	}

	if (a >= 1e-9)
	{
		printf("%3.3f nA", v / 1e-9);
		return;
	}

	printf("%e A", v);
	return;
}

/* Get frequency in Hz*/
double getfrequency(const char *display)
{
	double v;
	int i;

	while (1)
	{
		v = get_double(display);
		i = get_int("\n1)Hz  2)KHz  3)MHz  4)GHz : ");

		switch (i)
		{
		case 1:
			return v;

		case 2:
			return v * 1e3;

		case 3:
			return v * 1e6;

		case 4:
			return v * 1e9;
		}
	}
}

/* Get capacitance in F */
double getcapacitance(const char *display)
{
	double v;
	int i;

	while (1)
	{
		v = get_double(display);
		i = get_int("\n1)F  2)mF  3)μF  4)nF  5)pF : ");

		switch (i)
		{
		case 1:
			return v;

		case 2:
			return v * 1e-3;

		case 3:
			return v * 1e-6;

		case 4:
			return v * 1e-9;

		case 5:
			return v * 1e-12;
		}
	}
}

/* Get inductance in H */
double getinductance(const char *display)
{
	double v;
	int i;

	while (1)
	{
		v = get_double(display);
		i = get_int("\n1)H  2)mH  3)μH  4)nH  5)pH : ");

		switch (i)
		{
		case 1:
			return v;

		case 2:
			return v * 1e-3;

		case 3:
			return v * 1e-6;

		case 4:
			return v * 1e-9;

		case 5:
			return v * 1e-12;
		}
	}
}

/* Get resistance in Ω */
double getresistance(const char *display)
{
	double v;
	int i;

	while (1)
	{
		v = get_double(display);
		i = get_int("\n1)MΩ  2)KΩ  3)Ω  4)mΩ : ");

		switch (i)
		{
		case 1:
			return v * 1e6;

		case 2:
			return v * 1e3;

		case 3:
			return v;

		case 4:
			return v * 1e-3;
		}
	}
}

/* Get power in W */
double getpower(const char *display)
{
	double v;
	int i;

	while (1)
	{
		v = get_double(display);
		i = get_int("\n1)MW  2)KW  3)W  4)mW  5)μW : ");

		switch (i)
		{
		case 1:
			return v * 1e6;

		case 2:
			return v * 1e3;

		case 3:
			return v;

		case 4:
			return v * 1e-3;

		case 5:
			return v * 1e-6;
		}
	}
}

/* Get voltage in V */
double getvoltage(const char *display)
{
	double v;
	int i;

	while (1)
	{
		v = get_double(display);
		i = get_int("\n1)MV  2)KV  3)V  4)mV  5)μV  6)nV: ");

		switch (i)
		{
		case 1:
			return v * 1e6;

		case 2:
			return v * 1e3;

		case 3:
			return v;

		case 4:
			return v * 1e-3;

		case 5:
			return v * 1e-6;

		case 6:
			return v * 1e-9;
		}
	}
}

/* Get amperage in A */
double getamperage(const char *display)
{
	double v;
	int i;

	while (1)
	{
		v = get_double(display);
		i = get_int("\n1)KA  2)A  3)mA  4)μA  5)nA: ");

		switch (i)
		{
		case 1:
			return v * 1e3;

		case 2:
			return v;

		case 3:
			return v * 1e-3;

		case 4:
			return v * 1e-6;

		case 5:
			return v * 1e-9;
		}
	}
}

#ifdef __linux__
/* Get impedance r + jx */
double complex getimpedance(const char *display)
{
	double complex v;
	double r;
	double x;
	char *rs = NULL;
	char *rx = NULL;

	sprintf_string(&rs, "%s - r : ", display);
	sprintf_string(&rx, "%s - jx : ", display);

	r = get_double(rs);
	x = get_double(rx);
	v = r + x * I;

	if (rs)
		free(rs);

	if (rx)
		free(rx);

	return v;
}
#endif

#ifdef _WIN32
/* Get impedance r + jx */
_Dcomplex getimpedance(const char *display)
{
	_Dcomplex v;
	double r;
	double x;
	char *rs = NULL;
	char *rx = NULL;

	sprintf_string(&rs, "%s - r : ", display);
	sprintf_string(&rx, "%s - jx : ", display);

	v._Val[0] = get_double(rs);
	v._Val[1] = get_double(rx);

	if (rs)
		free(rs);

	if (rx)
		free(rx);

	return v;
}
#endif