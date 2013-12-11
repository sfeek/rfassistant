#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265

/*Safe function to get values from the user*/
void sgets(char *line,size_t size)
{
	size_t i;
	
	fflush(stdin);
		
	for ( i = 0; i < size - 1; ++i )
	{
		int ch = fgetc(stdin);
		if ( ch == '\n' || ch == EOF )
		{
			break;
		}
		line[i] = ch;
	}
	line[i] = '\0';
}


/*Used with FOR loops to properly handle fractional step values*/
int floatlessthan(double f1,double f2,double step)
{
	if ((f2 + step)-f1 > 1e-4)
		return 1;
	else
		return 0;
}


/* Wait for the user to Press ENTER */
void PauseForEnterKey(void)
{
	char ch;
	printf("\n*** Press [ENTER] For Main Menu ***\n");
	while (1)
	{
		ch=fgetc(stdin);
		if (ch == '\n') break;
	}
	return;
}


void TurnsToInductanceToroid(void)
{
	char buffer[80];
	double al,l;
	int turns,i;
	
	printf("Enter Al Value (uH/100 Turns): ");
	sgets(buffer,sizeof buffer);
	al = atof(buffer);
	
	printf("Enter Number of Turns: ");
	sgets(buffer,sizeof buffer);
	turns = atoi(buffer);
	
	if (al < 0) 
	{
		printf("\nAl Cannot Be Negative!\n");
		return;
	}
	
	if (turns < 1)
	{
		printf("\nNumber of Turns must be > 0!\n");
		return;
	}
	
	printf("\n");
	for (i = 1; i < turns + 1; i++) 
	{
		l = (al * i * i) / 10000.0;
		
		printf("%d -> %3.3f uH\n",i,l);
	}
}

void IndToAlToroid(void)
{
	char buffer[80];
	double al,l;
	int turns,i;
	
	printf("Enter Toroid Inductance (uH): ");
	sgets(buffer,sizeof buffer);
	l = atof(buffer);
	
	printf("Enter Number of Turns: ");
	sgets(buffer,sizeof buffer);
	turns = atoi(buffer);
	
	if (l < 0) 
	{
		printf("\nInductance Cannot Be Negative!\n");
		return;
	}
	
	if (turns < 1)
	{
		printf("\nNumber of Turns must be > 0!\n");
		return;
	}
	
	printf("\n");
	al = (l * 10000.0) / (turns * turns);
		
	printf(" Al = %3.1f uH/100\n",al);
}


void TurnsToInductanceAirCore(void)
{
	char buffer[80];
	int turns,i;
	double cd,ww,l;
	
	printf("Enter Coil Diameter (mm): ");
	sgets(buffer,sizeof buffer);
	cd = atof(buffer);
	
	printf("Enter Wire Width (mm): ");
	sgets(buffer,sizeof buffer);
	ww = atof(buffer);
	
	printf("Enter Number of Turns: ");
	sgets(buffer,sizeof buffer);
	turns = atoi(buffer);
	
	if (cd <= 0.0 || cd < (ww * 2))
	{
		printf("\nCoil Diameter must be > 2x Wire Width!\n");
		return;
	}
	
	if (turns < 2)
	{                 
		printf("\nNumber of Turns must be > 2!\n");
		return;
	}
	
	if (ww <=0.0 )
	{
		printf("\nWire Width must be > 0!\n");
		return;
	}
	
	printf("\n");
	for (i=1;i<turns+1;i++)
	{
		l = (0.2 * pow(cd/25.4, 2) * pow(i, 2)) / (3 * (cd/25.4) + 9 * ((i*ww)/25.4));
		
		printf("%d -> %3.3f uH   Coil Length = %3.1f mm\n",i,l,i*ww);
        }
}


void CapacitanceFrequency(void)
{
	char buffer[80];
	double ind,scap,ecap,icap,c,f;
	
	printf("Enter Inductance (uH): ");
	sgets(buffer,sizeof buffer);
	ind = atof(buffer);
	
	printf("Enter Start Capacitance (pF): ");
	sgets(buffer,sizeof buffer);
	scap = atof(buffer);
	
	printf("Enter End Capacitance (pF): ");
	sgets(buffer,sizeof buffer);
	ecap = atof(buffer);
	
	printf("Enter Capacitance Step (pF): ");
	sgets(buffer,sizeof buffer);
	icap = atof(buffer);
	
	if (ind < 0.0)
	{
		printf("\nInductance must be Non-Zero!\n");
		return;
	}
	
	if (icap == 0 || ecap < scap)
        {
            icap = 1;
            ecap = scap;
        }
	
	if (scap < 0 || scap > ecap)
	{
		printf("\nStart Value must be Non-Zero and smaller than End Value!\n");
		return;
	}
	
	if (ecap < 0 || ecap < scap)
	{
		printf("\nEnd Value must be Non-Zero and larger than Start Value!\n");
		return;
	}
	
	if (icap < 0) 
	{
		printf("\nStep Value must be Non-Zero!\n");
		return;
	}
	
	printf("\n");
	for (c = scap; floatlessthan(c,ecap,icap); c += icap)
        {
            f = (1 / ( 2 * PI * (sqrt(ind * 1e-6 * c * 1e-12)))) / 1e6;
            
            printf("%3.2f pF -> %3.3f MHz\n",c,f);
        }
}


void InductanceFrequency(void)
{
	char buffer[80];
	double cap,sind,eind,iind,i,f;
	
	printf("Enter Capacitance (pF): ");
	sgets(buffer,sizeof buffer);
	cap = atof(buffer);
	
	printf("Enter Start Inductance (uH): ");
	sgets(buffer,sizeof buffer);
	sind = atof(buffer);
	
	printf("Enter End Inductance (uH): ");
	sgets(buffer,sizeof buffer);
	eind = atof(buffer);
	
	printf("Enter Inductance Step (uH): ");
	sgets(buffer,sizeof buffer);
	iind = atof(buffer);
	
	if (cap < 0.0)
	{
		printf("\nCapacitance must be Non-Zero!\n");
		return;
	}
	
	if (iind == 0 || eind < sind)
        {
            iind = 1;
            eind = sind;
        }
	
	if (sind < 0 || sind > eind)
	{
		printf("\nStart Value must be Non-Zero and smaller than End Value!\n");
		return;
	}
	
	if (eind < 0 || eind < sind)
	{
		printf("\nEnd Value must be Non-Zero and larger than Start Value!\n");
		return;
	}
	
	if (iind < 0) 
	{
		printf("\nStep Value must be Non-Zero!\n");
		return;
	}
	
	printf("\n");
	for (i = sind; floatlessthan(i,eind,iind); i += iind)
        {
            f = (1 / ( 2 * PI * (sqrt(i * 1e-6 * cap * 1e-12)))) / 1e6;
            
            printf("%3.3f uH -> %3.3f MHz\n",i,f);
        }
}


void ReactanceCapacitance(void)
{
	char buffer[80];
	double r,scap,ecap,icap,i,f;
	
	printf("Enter Frequency (MHz): ");
	sgets(buffer,sizeof buffer);
	f = atof(buffer);
	
	printf("Enter Start Capacitance (pF): ");
	sgets(buffer,sizeof buffer);
	scap = atof(buffer);
	
	printf("Enter End Capacitance (pF): ");
	sgets(buffer,sizeof buffer);
	ecap = atof(buffer);
	
	printf("Enter Capacitance Step (pF): ");
	sgets(buffer,sizeof buffer);
	icap = atof(buffer);
	
	if (f < 0.0)
	{
		printf("\nFrequency must be Non-Zero!\n");
		return;
	}
	
	if (icap == 0 || ecap < scap)
        {
            icap = 1;
            ecap = scap;
        }
	
	if (scap < 0 || scap > ecap)
	{
		printf("\nStart Value must be Non-Zero and smaller than End Value!\n");
		return;
	}
	
	if (ecap < 0 || ecap < scap)
	{
		printf("\nEnd Value must be Non-Zero and larger than Start Value!\n");
		return;
	}
	
	if (icap < 0) 
	{
		printf("\nStep Value must be Non-Zero!\n");
		return;
	}
	
	printf("\n");
	for (i = scap; floatlessthan(i,ecap,icap); i += icap)
        {
            r = 1 / (2 * PI * (f * 1e6) * (i * 1e-12));
            
            printf("%3.2f pF -> %3.1f Ohms\n",i,r);
        }
}


void ReactanceInductance(void)
{
	char buffer[80];
	double r,sind,eind,iind,l,f;
	
	printf("Enter Frequency (MHz): ");
	sgets(buffer,sizeof buffer);
	f = atof(buffer);
	
	printf("Enter Start Inductance (uH): ");
	sgets(buffer,sizeof buffer);
	sind = atof(buffer);
	
	printf("Enter End Inductance (uH): ");
	sgets(buffer,sizeof buffer);
	eind = atof(buffer);
	
	printf("Enter Inductance Step (uH): ");
	sgets(buffer,sizeof buffer);
	iind = atof(buffer);
	
	if (f < 0.0)
	{
		printf("\nFrequency must be Non-Zero!\n");
		return;
	}
	
	if (iind == 0 || eind < sind)
        {
            iind = 1;
            eind = sind;
        }
	
	if (sind < 0 || sind > eind)
	{
		printf("\nStart Value must be Non-Zero and smaller than End Value!\n");
		return;
	}
	
	if (eind < 0 || eind < sind)
	{
		printf("\nEnd Value must be Non-Zero and larger than Start Value!\n");
		return;
	}
	
	if (iind < 0) 
	{
		printf("\nStep Value must be Non-Zero!\n");
		return;
	}
	
	printf("\n");
	for (l = sind; floatlessthan(l,eind,iind); l += iind)
        {
            r = 2 * PI * (f * 1e6) * (l * 1e-6);
            
            printf("%3.3f uH -> %3.1f Ohms\n",l,r);
        }
}


void SWRioZ(void)
{
	char buffer[80];
	double z0,z1,SWR,t;
	
	printf("Enter Input Z (Ohms): ");
	sgets(buffer,sizeof buffer);
	z0 = atof(buffer);
	
	printf("Enter Output Z (Ohms): ");
	sgets(buffer,sizeof buffer);
	z1 = atof(buffer);
	
	if (z0 <= 0)
	{
		printf("\nInput Z must be > 0!\n");
		return;
	}
	
	if (z1 <= 0)
	{
		printf("\nOutput Z must be > 0!\n");
		return;
	}
	
	if (z1 < z0) 
	{
            t = z1;
            z1 = z0;
            z0 = t;
        }
        
        SWR = (1 + (z1 - z0) / (z1 + z0)) / (1 - (z1 - z0) / (z1 + z0));
        
        printf("\nSWR -> %3.1f\n",SWR);
	
	return;
}


void SWRf(void)
{
	char buffer[80];
	double SWR,tx,pr;
	
	printf("Enter TX Power (W): ");
	sgets(buffer,sizeof buffer);
	tx = atof(buffer);
	
	printf("Enter SWR: ");
	sgets(buffer,sizeof buffer);
	SWR = atof(buffer);
	
	if (tx <=0)
	{
		printf("\nTX Power must be >0!\n");
		return;
	}
	
	if (SWR < 1)
	{
		printf("\nSWR must be >= 1!\n");
		return;
	}
	
	pr = tx * pow(SWR-1,2) / pow(SWR+1,2);
	
	printf("\nPower Radiated -> %3.2f W", tx-pr);
	printf("\nPower Reflected -> %3.2f W", pr); 
	printf("\nPower Lost -> %3.1f %%\n", pr / tx * 100.0);
	
	return;
}


void SWRfr(void)
{
	char buffer[80];
	double SWR,pf,pr;
	
	printf("Enter Forward Power (W): ");
	sgets(buffer,sizeof buffer);
	pf = atof(buffer);
	
	printf("Enter Reflected Power (W): ");
	sgets(buffer,sizeof buffer);
	pr = atof(buffer);
	
	if (pf <=0) 
	{
		printf("\nForward Power must be >0!\n");
		return;
	}
	
	if (pr <=0) 
	{
		printf("\nReflected Power must be >0!\n");
		return;
	}
	
	if (pr > pf)
	{
		printf("\nReflected Power must be less than Forward Power!");
		return;
	}
	
	SWR = (sqrt(pf) + sqrt(pr)) / (sqrt(pf) - sqrt(pr));
	
	printf("\nSWR -> %3.2f\n",SWR);
}


void VarCapScaling(void)
{
	char buffer[80];
	double I,X,Y,A,B;
	
	printf("Enter Start Capacitance (pF): ");
	sgets(buffer,sizeof buffer);
	A = atof(buffer);
	
	printf("Enter End Capacitance (pF): ");
	sgets(buffer,sizeof buffer);
	B = atof(buffer);
	
	printf("Enter Variable Capacitor Start (pF): ");
	sgets(buffer,sizeof buffer);
	X = atof(buffer);
	
	printf("Enter Variable Capacitor End (pF): ");
	sgets(buffer,sizeof buffer);
	Y = atof(buffer);
	
	if (A >= B)
	{
		printf("\nStart Capacitance must be less than End Capacitance!\n");
		return;
	}
	
	if (Y <= X + A)
	{
		printf("\nVariable Capacitor End Too Small!\n");
		return;
	}
	
	if (X >= (1.0 / (1.0 / Y + 1.0 / B)))
	{
		printf("\nVariable Capacitor Start Too Large!\n");
		return;
	}
	
	if (X >= Y)
	{
		printf("\nVariable Capacitor Start must be less than Variable Capacitor End!\n");
		return;
	}
	
	if (A <= 0)
	{
		printf("\nStart Capacitance must be >0!\n");
		return;
	}
	
	if (B <= 0)
	{
		printf("\nEnd Capacitance must be >0!\n");
		return;
	}
	
	if (X <= 0)
	{
		printf("\nVariable Capacitor Start must be >0!\n");
		return;
	}
	
	if (Y <= 0)
	{
		printf("\nVariable Capacitor End must be >0!\n");
		return;
	}
	
	if ((Y - X) <= (B - A))
	{
		printf("\nVariable Capacitor Capacitance Span too small!\n");
		return;
	}
	
	I = -0.5 * ((-B * Y - B * X + A * Y + A * X - sqrt((-Y + X) * (X * B * B + X * A * A - 2 * X * A * B - 4 * B * Y * X + 4 * A * Y * X - B * B * Y + 2 * B * Y * A - A * A * Y))) / (-B + A + Y - X));	
	
	
	printf("\nSeries Capacitor -> %3.2f pF\n",I);
	printf("\nParallel Capacitor -> %3.2f pF\n",fabs(A - (X * I) / (X + I)));
}


void CoaxStub(void)
{
	char buffer[80];
	double f,vf,o;
	
	printf("Enter Frequency (MHz): ");
	sgets(buffer,sizeof buffer);
	f = atof(buffer);
	
	printf("Enter Velocity Factor : ");
	sgets(buffer,sizeof buffer);
	vf = atof(buffer);
	
	if (f <= 0)
	{
		printf("\nFrequency must be >0!\n");
		return;
	}
	
	if (vf <= 0 || vf >= 1)
	{
		printf("\nVelocity Factor must be >0 and <1!\n");
		return;
	}
	
	o = (74.9481 * vf / f) * 100;
	
	printf("\nOpen End Stub = Notch Filter - Shorted Stub = Pass Filter\n");
	printf("\nCoax Stub Length -> %3.1f cm\n",o);
}


void TXOutputMatch(void)
{
	char buffer[80];
	double DTOR,P,V,R1,R2,F,RA,Z1,ZC1,Z2,ZC2,Z3,ZL1,r,Qn,BW,Qn1,Eff,Pd,QCoil;
	
	printf("Enter TX Output Power (W): ");
	sgets(buffer,sizeof buffer);
	P = atof(buffer);
	
	printf("Enter Collector or Plate Voltage Swing (V): ");
	sgets(buffer,sizeof buffer);
	V = atof(buffer);
	
	printf("Enter TX Output Resistance (Ohms): ");
	sgets(buffer,sizeof buffer);
	R2 = atof(buffer);
	
	printf("Enter TX Center Frequency (MHz): ");
	sgets(buffer,sizeof buffer);
	F = atof(buffer);
	
	printf("Enter Unloaded Q of Coil : ");
	sgets(buffer,sizeof buffer);
	QCoil = atof(buffer);
	
	printf("Enter Phase Shift Angle (Deg): ");
	sgets(buffer,sizeof buffer);
	r = atof(buffer);
	
	if (P <= 0)
	{
		printf("\nTX Output Power must be >0!\n");
		return;
	}
	
	if (V <= 0)
	{
		printf("\nTX Collector or Plate Voltage Swing must be >0!\n");
		return;
	}
	
	if (R2 <= 0)
	{
		printf("\nTX Output Resistance must be >0!\n");
		return;
	}
	
	if (F < 0.1 || F > 2500)
	{
		printf("\nTX Center Frequency must be >0.1 and <2500!\n");
		return;
	}
	
	if (QCoil < 0.1)
	{
		printf("\nUnloaded Q of Coil must be >0.1!\n");
		return;
	}
	
	if (r < 90 || r > 180)
	{
		printf("\nPhase Shift Angle must be >=90 and <=180!\n");
		return;
	}
	
	DTOR = PI / 180;

	R1 = pow(V,2) / (2 * P);
	RA = r * DTOR;

	Z1 = (R1 * R2 * sin(RA)) / (R2 * cos(RA) - sqrt(R1 * R2));
	ZC1 = fabs(1000000 / (2 * PI * F * Z1));

	Z2 = (R1 * R2 * sin(RA)) / (R1 * cos(RA) - sqrt(R1 * R2));
	ZC2 = fabs(1000000 / (2 * PI * F * Z2));

	Z3 = sqrt(R1 * R2) * sin(RA);
	ZL1 = Z3 / (2 * PI * F);

	Qn = fabs(R1 / Z1 + R2 / Z2);
	Qn1 = (Qn * QCoil) / (Qn + QCoil);

	BW = F / Qn;
	Eff = (Z3 / Qn) / (Z3 / Qn1) * 100;
	Pd = P - P * (Eff / 100);
	
	printf("\nLoad Resistance -> %3.2f Ohms\n",R2);
	printf("\nSource Resistance -> %3.2f Ohms\n",R1);
	printf("\nSource Side Parallel Capacitor -> %3.1f pF\n",ZC1);
	printf("\nLoad Side Parallel Capacitor -> %3.1f pF\n",ZC2);
	printf("\nSeries Inductor -> %3.3f uH\n",ZL1);
	printf("\nLoaded Q of Coil -> %3.1f\n",Qn1);
	printf("\nCircuit Efficiency -> %3.1f %%\n",Eff);
	printf("\nSource Side Parallel Capacitor Reactance -> %3.1f Ohms\n",Z1);
	printf("\nLoad Side Parallel Capacitor Reactance -> %3.1f Ohms\n",Z2);
	printf("\nSeries Inductor Reactance -> %3.1f Ohms\n",Z3);
	printf("\nBandwidth -> %3.1f MHz\n",BW);
	printf("\nPower Lost in Inductor -> %3.1f W\n",Pd);
}


void ImpedanceMatch(void)
{
	char buffer[80];
	double DTOR,R1,R2,F,RA,Z1,ZC1,Z2,ZC2,Z3,ZL1,r,Qn,BW,Qn1,Eff,QCoil;
	
	printf("Source Resistance (Ohms): ");
	sgets(buffer,sizeof buffer);
	R1 = atof(buffer);
	
	printf("Load Resistance (Ohms): ");
	sgets(buffer,sizeof buffer);
	R2 = atof(buffer);
	
	printf("Enter TX Center Frequency (MHz): ");
	sgets(buffer,sizeof buffer);
	F = atof(buffer);
	
	printf("Enter Unloaded Q of Coil : ");
	sgets(buffer,sizeof buffer);
	QCoil = atof(buffer);
	
	printf("Enter Phase Shift Angle (Deg): ");
	sgets(buffer,sizeof buffer);
	r = atof(buffer);
	
	if (R1 <= 0)
	{
		printf("\nSource Resistance must be >0!\n");
		return;
	}
	
	if (R2 <= 0)
	{
		printf("\nLoad Resistance must be >0!\n");
		return;
	}
	
	if (F < 0.1 || F > 2500)
	{
		printf("\nCenter Frequency must be >0.1 and <2500!\n");
		return;
	}
	
	if (QCoil < 0.1)
	{
		printf("\nUnloaded Q of Coil must be >0.1!\n");
		return;
	}
	
	if (r < 90 || r > 180)
	{
		printf("\nPhase Shift Angle must be >=90 and <=180!\n");
		return;
	}
	
	DTOR = PI / 180;

	RA = r * DTOR;

	Z1 = (R1 * R2 * sin(RA)) / (R2 * cos(RA) - sqrt(R1 * R2));
	ZC1 = fabs(1000000 / (2 * PI * F * Z1));

	Z2 = (R1 * R2 * sin(RA)) / (R1 * cos(RA) - sqrt(R1 * R2));
	ZC2 = fabs(1000000 / (2 * PI * F * Z2));

	Z3 = sqrt(R1 * R2) * sin(RA);
	ZL1 = Z3 / (2 * PI * F);

	Qn = fabs(R1 / Z1 + R2 / Z2);
	Qn1 = (Qn * QCoil) / (Qn + QCoil);

	BW = F / Qn;
	Eff = (Z3 / Qn) / (Z3 / Qn1) * 100;
	
	printf("\nLoad Resistance -> %3.2f Ohms\n",R2);
	printf("\nSource Resistance -> %3.2f Ohms\n",R1);
	printf("\nSource Side Parallel Capacitor -> %3.1f pF\n",ZC1);
	printf("\nLoad Side Parallel Capacitor -> %3.1f pF\n",ZC2);
	printf("\nSeries Inductor -> %3.3f uH\n",ZL1);
	printf("\nLoaded Q of Coil -> %3.1f\n",Qn1);
	printf("\nCircuit Efficiency -> %3.1f %%\n",Eff);
	printf("\nSource Side Parallel Capacitor Reactance -> %3.1f Ohms\n",Z1);
	printf("\nLoad Side Parallel Capacitor Reactance -> %3.1f Ohms\n",Z2);
	printf("\nSeries Inductor Reactance -> %3.1f Ohms\n",Z3);
	printf("\nBandwidth -> %3.1f MHz\n",BW);
}


void V1V2(void)
{
	char buffer[80];
	double v1,v2,o;
	
	printf("Enter Voltage 1 (V): ");
	sgets(buffer,sizeof buffer);
	v1 = atof(buffer);
	
	printf("Enter Voltage 2 (V): ");
	sgets(buffer,sizeof buffer);
	v2 = atof(buffer);
	
	if (v1 <= 0)
	{
		printf("\nVoltage 1 must be >0!\n");
		return;
	}
	
	if (v2 <= 0)
	{
		printf("\nVoltage 2 must be >0!\n");
		return;
	}
	
	o = 20.0 * log10(v2/v1);
	
	printf("\nDecibels -> %3.3f dB\n",o);
	
}


void P1P2(void)
{

	char buffer[80];
	double p1,p2,o;
	
	printf("Enter Power 1 : ");
	sgets(buffer,sizeof buffer);
	p1 = atof(buffer);
	
	printf("Enter Power 2 : ");
	sgets(buffer,sizeof buffer);
	p2 = atof(buffer);
	
	if (p1 <= 0)
	{
		printf("\nPower 1 must be >0!\n");
		return;
	}
	
	if (p2 <= 0)
	{
		printf("\nPower 2 must be >0!\n");
		return;
	}
	
	o = 10.0 * log10(p2/p1);
	
	printf("\nDecibels -> %3.3f dB\n",o);
}


void dBmP(void)
{
	char buffer[80];
	double dBm,o;
	
	printf("Enter dBm : ");
	sgets(buffer,sizeof buffer);
	dBm = atof(buffer);
	
	o = pow(10.0, dBm/10);
	
	if (o < 0.01)
	{
		printf("\nPower -> %.3e mW\n",o);
	}
	else
	{	
		printf("\nPower -> %3.3f mW\n",o);
	}
}


void PdBm(void)
{
	char buffer[80];
	double pwr,o;
	
	printf("Enter Power (mW) : ");
	sgets(buffer,sizeof buffer);
	pwr = atof(buffer);
	
	if (pwr <= 0)
	{
		printf("\nPower must be >0!\n");
		return;
	}
		
	o = 10 * log10(pwr);
	
	if (o < 0.01)
	{
		printf("\nDecibels -> %.3edBm\n",o);
	}
	else
	{	
		printf("\nDecibels -> %3.3fdBm\n",o);
	}
}


void dBmuV(void)
{
	char buffer[80];
	double v1,v2,o;
	
	printf("Enter dBm : ");
	sgets(buffer,sizeof buffer);
	v1 = atof(buffer);
	
	printf("Enter Impedance (Ohms): ");
	sgets(buffer,sizeof buffer);
	v2 = atof(buffer);
	
	if (v2 <= 0)
	{
		printf("\nImpedance must be >0!\n");
		return;
	}
	
	o = sqrt((pow(10,(v1 + 30) / 10) * 1000000) * v2);
	
	printf("\nVoltage -> %3.3f uV\n",o);
}


void uVdBm(void)
{
	char buffer[80];
	double v1,v2,o;
	
	printf("Enter Voltage (uV): ");
	sgets(buffer,sizeof buffer);
	v1 = atof(buffer);
	
	printf("Enter Impedance (Ohms): ");
	sgets(buffer,sizeof buffer);
	v2 = atof(buffer);
	
	if (v1 <= 0)
	{
		printf("\nVoltage must be >0!\n");
		return;
	}
	
	if (v2 <= 0)
	{
		printf("\nImpedance must be >0!\n");
		return;
	}
	
	o = 10 * log10(pow(v1 * 0.000001,2) / v2) + 30;
	
	printf("\nDecibels -> %3.3f dBm\n",o);
}


void PdB(void)
{
	char buffer[80];
	double v1,v2,o;
	
	printf("Enter Power : ");
	sgets(buffer,sizeof buffer);
	v1 = atof(buffer);
	
	printf("Enter Decibels : ");
	sgets(buffer,sizeof buffer);
	v2 = atof(buffer);
	
	if (v1 <= 0)
	{
		printf("\nPower must be >0!\n");
		return;
	}
	
	o = v1 * (pow(10,(v2 / 10)));
	
	printf("\nPower -> %3.3f\n",o);
}


void VdB(void)
{
	char buffer[80];
	double v1,v2,o;
	
	printf("Enter Voltage : ");
	sgets(buffer,sizeof buffer);
	v1 = atof(buffer);
	
	printf("Enter Decibels : ");
	sgets(buffer,sizeof buffer);
	v2 = atof(buffer);
	
	if (v1 <= 0)
	{
		printf("\nVoltage must be >0!\n");
		return;
	}
		
	o = v1 * (pow(10,(v2 / 20)));
	
	printf("\nVoltage -> %3.3f\n",o);
}


void DecibelConversions(void)
{
	char buffer[3];
	int selection,done;
	done = 0;
	
	while (1)
	{
		printf("\n\n   **** Decibel Conversion Menu ****\n\n");
		printf(" 1. Voltage 1 -> Voltage 2\n");
		printf(" 2. Power 1 -> Power 2\n");
		printf(" 3. dBm -> Power\n");
		printf(" 4. Power -> dBm\n");
		printf(" 5. dBm -> Voltage uV\n");
		printf(" 6. Voltage uV -> dBm\n");
		printf(" 7. Power +/- dB\n");
		printf(" 8. Voltage +/- dB\n");
		
		printf("\n 99. Exit\n\n");
		printf("Enter Selection: ");
		
		sgets(buffer,sizeof buffer);
		selection = atoi(buffer);
		
		printf("\n\n");
		
		switch (selection)
		{
			case 1:
				V1V2();
				PauseForEnterKey();
				done = 1;
				break;
				
			case 2:
				P1P2();
				PauseForEnterKey();
				done = 1;
				break;
				
			case 3:
				dBmP();
				PauseForEnterKey();
				done = 1;
				break;
				
			case 4:
				PdBm();
				PauseForEnterKey();
				done = 1;
				break;	
				
			case 5:
				dBmuV();
				PauseForEnterKey();
				done = 1;
				break;
				
			case 6:
				uVdBm();
				PauseForEnterKey();
				done = 1;
				break;
				
			case 7:
				PdB();
				PauseForEnterKey();
				done = 1;
				break;
			
			case 8:
				VdB();
				PauseForEnterKey();
				done = 1;
				break;
				
			case 99:
				done = 1;
				break;
				
			default:
				printf("Invalid Entry\n");
				break;
		}
		if (done == 1) break;
	}
}


void Resistors(void)
{
	double tresistance,nresistance;
	char buffer[80],buffer1[80];
	
	printf("Enter Initial Resistor : ");
	sgets(buffer,sizeof buffer);
	tresistance = atof(buffer);
	
	while(1)
	{
		printf("Enter [S]eries, [P]arallel or [E]xit: ");
		sgets(buffer1,sizeof buffer1);
		
		if (buffer1[0] == 'E' || buffer1[0] == 'e')
		{
			printf("\nTotal Resistance = %3.3f\n",tresistance);
			break;
		}

		printf("Enter Next Resistor : ");
		sgets(buffer,sizeof buffer);
		nresistance = atof(buffer);

		if (buffer1[0] == 'S' || buffer1[0] == 's')
		{
			tresistance += nresistance;
		}	

		if (buffer1[0] == 'P' || buffer1[0] == 'p')
		{
			if (nresistance > 0) tresistance = 1.0 / (1.0 / tresistance + 1.0 / nresistance);
		}
	}
}


void Inductors(void)
{
	double tinductance,ninductance;
	char buffer[80],buffer1[80];
	
	printf("Enter Initial Inductor : ");
	sgets(buffer,sizeof buffer);
	tinductance = atof(buffer);
	
	while(1)
	{
		printf("Enter [S]eries, [P]arallel or [E]xit: ");
		sgets(buffer1,sizeof buffer1);
		
		if (buffer1[0] == 'E' || buffer1[0] == 'e')
		{
			printf("\nTotal Inductance = %3.3f\n",tinductance);
			break;
		}

		printf("Enter Next Inductor : ");
		sgets(buffer,sizeof buffer);
		ninductance = atof(buffer);

		if (buffer1[0] == 'S' || buffer1[0] == 's')
		{
			tinductance += ninductance;
		}	

		if (buffer1[0] == 'P' || buffer1[0] == 'p')
		{
			if (ninductance > 0) tinductance = 1.0 / (1.0 / tinductance + 1.0 / ninductance);
		}
	}
}


void Capacitors(void)
{
	double tcapacitance,ncapacitance;
	char buffer[80],buffer1[80];
	
	printf("Enter Initial Capacitor : ");
	sgets(buffer,sizeof buffer);
	tcapacitance = atof(buffer);
	
	while(1)
	{
		printf("Enter [S]eries, [P]arallel or [E]xit: ");
		sgets(buffer1,sizeof buffer1);
		
		if (buffer1[0] == 'E' || buffer1[0] == 'e')
		{
			printf("\nTotal Capacitance = %3.3f\n",tcapacitance);
			break;
		}

		printf("Enter Next Capacitor : ");
		sgets(buffer,sizeof buffer);
		ncapacitance = atof(buffer);

		if (buffer1[0] == 'P' || buffer1[0] == 'p')
		{
			tcapacitance += ncapacitance;
		}	

		if (buffer1[0] == 'S' || buffer1[0] == 's')
		{
			if (ncapacitance > 0) tcapacitance = 1.0 / (1.0 / tcapacitance + 1.0 / ncapacitance);
		}
	}
}


void RCI(void)
{
	char buffer[3];
	int selection,done;
	done = 0;
	
	while (1)
	{
		printf("\n\n   **** Resistors, Inductors, Capacitors Menu ****\n\n");
		printf(" 1. Resistors\n");
		printf(" 2. Inductors\n");
		printf(" 3. Capacitors\n");
				
		printf("\n 99. Exit\n\n");
		printf("Enter Selection: ");
		
		sgets(buffer,sizeof buffer);
		selection = atoi(buffer);
		
		printf("\n\n");
		
		switch (selection)
		{
			case 1:
				Resistors();
				PauseForEnterKey();
				done = 1;
				break;
				
			case 2:
				Inductors();
				PauseForEnterKey();
				done = 1;
				break;
				
			case 3:
				Capacitors();
				PauseForEnterKey();
				done = 1;
				break;
			
			case 99:
				done = 1;
				break;
				
			default:
				printf("Invalid Entry\n");
				break;
		}
		if (done == 1) break;
	}
}


int main (void)
{
	char buffer[4];
	int selection,done;
	done = 0;
	
	while (1)
	{
		printf("\n\n   **** RF Calculator Main Menu ****\n\n");
		printf(" 1. Turns to Inductance for Toroid Coil\n");
		printf(" 2. Turns to Inductance for Air Core Coil\n");
		printf(" 3. Capacitance vs Frequency for Tank Circuit\n");
		printf(" 4. Inductance vs Frequency for Tank Circuit\n");
		printf(" 5. Capacitive Reactance @ Frequency\n");
		printf(" 6. Inductive Reactance @ Frequency\n");
		printf(" 7. SWR for Input Z vs Output Z\n");
		printf(" 8. Power Radiated and Lost for SWR @ TX Power\n");
		printf(" 9. SWR for Power Forward vs Power Reflected\n");
		printf("10. Variable Capacitor Scaling\n");
		printf("11. Coax Stub Notch & Pass\n");
		printf("12. Transmitter Output Matching PI Network\n");
		printf("13. Impedance Matching PI Network\n");
		printf("14. Decibel Conversions\n");
		printf("15. Resistors, Inductors, Capacitors - Series & Parallel\n");
		printf("16. Torroid Al Value from Inductance and Turns\n");
		printf("\n 99. Exit\n\n");
		printf("Enter Selection: ");
		
		sgets(buffer,sizeof buffer);
		selection = atoi(buffer);
		
		printf("\n\n");
		
		switch (selection)
		{
			case 1:
				TurnsToInductanceToroid();
				PauseForEnterKey();
				break;
				
			case 2:
				TurnsToInductanceAirCore();
				PauseForEnterKey();
				break;
				
			case 3:
				CapacitanceFrequency();
				PauseForEnterKey();
				break;
				
			case 4:
				InductanceFrequency();
				PauseForEnterKey();
				break;	
				
			case 5:
				ReactanceCapacitance();
				PauseForEnterKey();
				break;
				
			case 6:
				ReactanceInductance();
				PauseForEnterKey();
				break;
				
			case 7:
				SWRioZ();
				PauseForEnterKey();
				break;
			
			case 8:
				SWRf();
				PauseForEnterKey();
				break;
				
			case 9:
				SWRfr();
				PauseForEnterKey();
				break;
				
			case 10:
				VarCapScaling();
				PauseForEnterKey();
				break;
				
			case 11:
				CoaxStub();
				PauseForEnterKey();
				break;
				
			case 12:
				TXOutputMatch();
				PauseForEnterKey();
				break;
				
			case 13:
				ImpedanceMatch();
				PauseForEnterKey();
				break;
				
			case 14:
				DecibelConversions();
				break;

			case 15:
				RCI();
				break;
				
			case 16:
				IndToAlToroid();
				PauseForEnterKey();
				break;
								
			case 99:
				done = 1;
				break;
				
			default:
				printf("Invalid Entry\n");
				break;
		}
		if (done == 1) break;
	}
	return 0;
}



