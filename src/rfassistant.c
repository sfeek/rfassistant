#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define PI 3.14159265

/*Safe function to get values from the user*/
void sgets( char *line , size_t size )
{
	size_t i;
	
	fflush( stdin );
		
	for ( i = 0 ; i < size-1 ; ++i )
	{
		int ch = fgetc( stdin );
		if (  ch == '\n' || ch == EOF )
		{
			break;
		}
		line[i] = ch;
	}

	line[i] = '\0';
}


/*Used with FOR loops to properly handle fractional step values*/
int floatlessthan( double f1 , double f2 , double step )
{
	if ( (f2 + step)-f1 > 1e-4)
		return 1;
	else
		return 0;
}


/* Wait for the user to Press ENTER */
void PauseForEnterKey( void )
{
	char ch;

	printf(  "\n*** Press [ENTER] For Main Menu ***\n" );

	while (1)
	{
		ch=fgetc( stdin );
		if ( ch == '\n') break;
	}

	return;
}


void TurnsToInductanceToroid( void )
{
	char buffer[80];
	double al , l;
	int turns , i;
	
	printf(  "Enter Al Value (uH/100 Turns): " );
	sgets( buffer , sizeof buffer );
	al = atof( buffer );
	
	printf(  "Enter Number of Turns: " );
	sgets( buffer , sizeof buffer );
	turns = atoi( buffer );
	
	if ( al < 0) 
	{
		printf(  "\nAl Cannot Be Negative!\n" );
		return;
	}
	
	if ( turns < 1)
	{
		printf(  "\nNumber of Turns must be > 0!\n" );
		return;
	}
	
	printf(  "\n" );

	for ( i = 1 ; i < turns + 1 ; i++ ) 
	{
		l = (al * i * i) / 10000.0;
		
		printf(  "%d -> %3.3f uH\n" , i  , l );
	}
}

void IndToAlToroid( void )
{
	char buffer[80];
	double al , l;
	int turns;
	
	printf(  "Enter Toroid Inductance (uH): " );
	sgets( buffer , sizeof buffer );
	l = atof( buffer );
	
	printf(  "Enter Number of Turns: " );
	sgets( buffer , sizeof buffer );
	turns = atoi( buffer );
	
	if (  l < 0 ) 
	{
		printf ( "\nInductance Cannot Be Negative!\n" );
		return;
	}
	
	if (  turns < 1 )
	{
		printf(  "\nNumber of Turns must be > 0!\n" );
		return;
	}
	
	printf(  "\n" );
	al = (l * 10000.0) / (turns * turns);
		
	printf(  " Al = %3.1f uH/100\n" , al );
}


void TurnsToInductanceAirCore( void )
{
	char buffer[80];
	int turns , i;
	double cd , ww , l;
	
	printf(  "Enter Coil Diameter (mm): " );
	sgets( buffer , sizeof buffer );
	cd = atof( buffer );
	
	printf(  "Enter Wire Width (mm): " );
	sgets( buffer , sizeof buffer );
	ww = atof( buffer );
	
	printf(  "Enter Number of Turns: " );
	sgets( buffer , sizeof buffer );
	turns = atoi( buffer );
	
	if (  cd <= 0.0 || cd < (ww * 2) )
	{
		printf(  "\nCoil Diameter must be > 2x Wire Width!\n" );
		return;
	}
	
	if (  turns < 2 )
	{                 
		printf(  "\nNumber of Turns must be > 2!\n" );
		return;
	}
	
	if (  ww <=0.0 )
	{
		printf(  "\nWire Width must be > 0!\n" );
		return;
	}
	
	printf(  "\n" );

	for ( i=1 ; i < turns+1 ; i++ )
	{
		l = (0.2 * pow(cd/25.4 , 2) * pow(i , 2)) / (3 * (cd/25.4) + 9 * ((i*ww)/25.4));
		
		printf(  "%d -> %3.3f uH   Coil Length = %3.1f mm\n" , i , l , i*ww);
	}
}


void CapacitanceFrequency( void )
{
	char buffer[80];
	double ind , scap , ecap , icap , c , f;
	
	printf(  "Enter Inductance (uH): " );
	sgets( buffer , sizeof buffer );
	ind = atof( buffer );
	
	printf(  "Enter Start Capacitance (pF): " );
	sgets( buffer , sizeof buffer );
	scap = atof( buffer );
	
	printf(  "Enter End Capacitance (pF): " );
	sgets( buffer , sizeof buffer );
	ecap = atof( buffer );
	
	printf(  "Enter Capacitance Step (pF): " );
	sgets( buffer , sizeof buffer );
	icap = atof( buffer );
	
	if (  ind < 0.0 )
	{
		printf(  "\nInductance must be Non-Zero!\n" );
		return;
	}
	
	if (  icap == 0 || ecap < scap )
	{
		icap = 1;
		ecap = scap;
	}
	
	if (  scap < 0 || scap > ecap )
	{
		printf(  "\nStart Value must be Non-Zero and smaller than End Value!\n" );
		return;
	}
	
	if (  ecap < 0 || ecap < scap )
	{
		printf(  "\nEnd Value must be Non-Zero and larger than Start Value!\n" );
		return;
	}
	
	if (  icap < 0 ) 
	{
		printf(  "\nStep Value must be Non-Zero!\n" );
		return;
	}
	
	printf(  "\n" );

	for ( c = scap ; floatlessthan( c , ecap , icap ); c += icap )
	{
		f = (1 / ( 2 * PI * (sqrt(ind * 1e-6 * c * 1e-12)))) / 1e6;

		printf(  "%3.2f pF -> %3.3f MHz\n" , c , f );
	}
}


void InductanceFrequency( void )
{
	char buffer[80];
	double cap , sind , eind , iind , i , f;
	
	printf(  "Enter Capacitance (pF): " );
	sgets( buffer , sizeof buffer );
	cap = atof( buffer );
	
	printf(  "Enter Start Inductance (uH): " );
	sgets( buffer , sizeof buffer );
	sind = atof( buffer );
	
	printf(  "Enter End Inductance (uH): " );
	sgets( buffer , sizeof buffer );
	eind = atof( buffer );
	
	printf(  "Enter Inductance Step (uH): " );
	sgets( buffer , sizeof buffer );
	iind = atof( buffer );
	
	if (  cap < 0.0 )
	{
		printf(  "\nCapacitance must be Non-Zero!\n" );
		return;
	}
	
	if (  iind == 0 || eind < sind )
	{
		iind = 1;
		eind = sind;
	}
	
	if (  sind < 0 || sind > eind )
	{
		printf(  "\nStart Value must be Non-Zero and smaller than End Value!\n" );
		return;
	}
	
	if (  eind < 0 || eind < sind )
	{
		printf(  "\nEnd Value must be Non-Zero and larger than Start Value!\n" );
		return;
	}
	
	if (  iind < 0 ) 
	{
		printf(  "\nStep Value must be Non-Zero!\n" );
		return;
	}
	
	printf(  "\n" );

	for (i = sind ; floatlessthan( i , eind , iind ); i += iind )
	{
		f = (1 / ( 2 * PI * (sqrt(i * 1e-6 * cap * 1e-12)))) / 1e6;

		printf(  "%3.3f uH -> %3.3f MHz\n" , i , f );
	}
}


void ReactanceCapacitance( void )
{
	char buffer[80];
	double r , scap , ecap , icap , i , f;
	
	printf( "Enter Frequency (MHz): " );
	sgets( buffer , sizeof buffer );
	f = atof( buffer );
	
	printf( "Enter Start Capacitance (pF): " );
	sgets( buffer , sizeof buffer );
	scap = atof( buffer );
	
	printf( "Enter End Capacitance (pF): " );
	sgets( buffer , sizeof buffer );
	ecap = atof( buffer );
	
	printf( "Enter Capacitance Step (pF): " );
	sgets( buffer , sizeof buffer );
	icap = atof( buffer );
	
	if ( f < 0.0 )
	{
		printf( "\nFrequency must be Non-Zero!\n" );
		return;
	}
	
	if ( icap == 0 || ecap < scap )
	{
		icap = 1;
		ecap = scap;
	}
	
	if ( scap < 0 || scap > ecap )
	{
		printf( "\nStart Value must be Non-Zero and smaller than End Value!\n" );
		return;
	}
	
	if ( ecap < 0 || ecap < scap )
	{
		printf( "\nEnd Value must be Non-Zero and larger than Start Value!\n" );
		return;
	}
	
	if ( icap < 0 ) 
	{
		printf( "\nStep Value must be Non-Zero!\n" );
		return;
	}
	
	printf( "\n" );

	for ( i = scap ; floatlessthan(i , ecap , icap) ; i += icap )
	{
		r = 1 / (2 * PI * (f * 1e6) * (i * 1e-12));

		printf( "%3.2f pF -> %3.1f Ohms\n" , i , r );
	}
}


void ReactanceInductance( void )
{
	char buffer[80];
	double r , sind , eind , iind , l , f;
	
	printf( "Enter Frequency (MHz): " );
	sgets( buffer , sizeof buffer );
	f = atof( buffer );
	
	printf( "Enter Start Inductance (uH): " );
	sgets( buffer , sizeof buffer );
	sind = atof( buffer );
	
	printf( "Enter End Inductance (uH): " );
	sgets( buffer , sizeof buffer );
	eind = atof( buffer );
	
	printf( "Enter Inductance Step (uH): " );
	sgets( buffer , sizeof buffer );
	iind = atof( buffer );
	
	if ( f < 0.0 )
	{
		printf( "\nFrequency must be Non-Zero!\n" );
		return;
	}
	
	if ( iind == 0 || eind < sind )
	{
		iind = 1;
		eind = sind;
	}
	
	if ( sind < 0 || sind > eind )
	{
		printf( "\nStart Value must be Non-Zero and smaller than End Value!\n" );
		return;
	}
	
	if ( eind < 0 || eind < sind )
	{
		printf( "\nEnd Value must be Non-Zero and larger than Start Value!\n" );
		return;
	}
	
	if ( iind < 0 ) 
	{
		printf( "\nStep Value must be Non-Zero!\n" );
		return;
	}
	
	printf( "\n" );
	for (l = sind ; floatlessthan( l , eind , iind ) ; l += iind )
	{
		r = 2 * PI * (f * 1e6) * (l * 1e-6);

		printf( "%3.3f uH -> %3.1f Ohms\n" , l , r );
	}
}


void SWRioZ( void )
{
	char buffer[80];
	double z0 , z1 , SWR , t;
	
	printf( "Enter Input Z (Ohms): " );
	sgets( buffer , sizeof buffer );
	z0 = atof( buffer );
	
	printf( "Enter Output Z (Ohms): " );
	sgets( buffer , sizeof buffer );
	z1 = atof( buffer );
	
	if ( z0 <= 0 )
	{
		printf( "\nInput Z must be > 0!\n" );
		return;
	}
	
	if ( z1 <= 0 )
	{
		printf( "\nOutput Z must be > 0!\n" );
		return;
	}
	
	if ( z1 < z0 ) 
	{
		t = z1;
		z1 = z0;
		z0 = t;
	}

	SWR = (1 + (z1 - z0) / (z1 + z0)) / (1 - (z1 - z0) / (z1 + z0));

	printf( "\nSWR -> %3.1f\n" , SWR );
	
	return;
}


void SWRf( void )
{
	char buffer[80];
	double SWR , tx , pr;
	
	printf( "Enter TX Power (W): " );
	sgets( buffer , sizeof buffer );
	tx = atof( buffer );
	
	printf( "Enter SWR: " );
	sgets( buffer , sizeof buffer );
	SWR = atof( buffer );
	
	if ( tx <=0 )
	{
		printf( "\nTX Power must be >0!\n" );
		return;
	}
	
	if ( SWR < 1 )
	{
		printf( "\nSWR must be >= 1!\n" );
		return;
	}
	
	pr = tx * pow(SWR-1 , 2) / pow(SWR+1 , 2);
	
	printf( "\nPower Radiated -> %3.2f W" , tx-pr );
	printf( "\nPower Reflected -> %3.2f W" , pr ); 
	printf( "\nPower Lost -> %3.1f %%\n" , pr / tx * 100.0 );
	
	return;
}


void SWRfr( void )
{
	char buffer[80];
	double SWR , pf , pr;
	
	printf( "Enter Forward Power (W): " );
	sgets( buffer , sizeof buffer );
	pf = atof( buffer );
	
	printf( "Enter Reflected Power (W): " );
	sgets( buffer , sizeof buffer );
	pr = atof( buffer );
	
	if ( pf <=0 ) 
	{
		printf( "\nForward Power must be >0!\n" );
		return;
	}
	
	if ( pr <=0 ) 
	{
		printf( "\nReflected Power must be >0!\n" );
		return;
	}
	
	if ( pr > pf )
	{
		printf( "\nReflected Power must be less than Forward Power!" );
		return;
	}
	
	SWR = (sqrt(pf) + sqrt(pr)) / (sqrt(pf) - sqrt(pr));
	
	printf( "\nSWR -> %3.2f\n" , SWR );
}


void VarCapScaling( void )
{
	char buffer[80];
	double I , X , Y , A , B;
	
	printf( "Enter Start Capacitance (pF): " );
	sgets( buffer , sizeof buffer );
	A = atof( buffer );
	
	printf( "Enter End Capacitance (pF): " );
	sgets( buffer , sizeof buffer );
	B = atof( buffer );
	
	printf( "Enter Variable Capacitor Start (pF): " );
	sgets( buffer , sizeof buffer );
	X = atof( buffer );
	
	printf( "Enter Variable Capacitor End (pF): " );
	sgets( buffer , sizeof buffer );
	Y = atof( buffer );
	
	if ( A >= B)
	{
		printf( "\nStart Capacitance must be less than End Capacitance!\n" );
		return;
	}
	
	if ( Y <= X + A)
	{
		printf( "\nVariable Capacitor End Too Small!\n" );
		return;
	}
	
	if ( X >= (1.0 / (1.0 / Y + 1.0 / B)))
	{
		printf( "\nVariable Capacitor Start Too Large!\n" );
		return;
	}
	
	if ( X >= Y)
	{
		printf( "\nVariable Capacitor Start must be less than Variable Capacitor End!\n" );
		return;
	}
	
	if ( A <= 0)
	{
		printf( "\nStart Capacitance must be >0!\n" );
		return;
	}
	
	if ( B <= 0)
	{
		printf( "\nEnd Capacitance must be >0!\n" );
		return;
	}
	
	if ( X <= 0)
	{
		printf( "\nVariable Capacitor Start must be >0!\n" );
		return;
	}
	
	if ( Y <= 0)
	{
		printf( "\nVariable Capacitor End must be >0!\n" );
		return;
	}
	
	if ( (Y - X) <= (B - A))
	{
		printf( "\nVariable Capacitor Capacitance Span too small!\n" );
		return;
	}
	
	I = -0.5 * ((-B * Y - B * X + A * Y + A * X - sqrt((-Y + X) * (X * B * B + X * A * A - 2 * X * A * B - 4 * B * Y * X + 4 * A * Y * X - B * B * Y + 2 * B * Y * A - A * A * Y))) / (-B + A + Y - X));	
	
	
	printf( "\nSeries Capacitor -> %3.2f pF\n" , I);
	printf( "\nParallel Capacitor -> %3.2f pF\n" , fabs(A - (X * I) / (X + I)));
}


void CoaxStub( void )
{
	char buffer[80];
	double f , vf , o;
	
	printf( "Enter Frequency (MHz): " );
	sgets( buffer , sizeof buffer );
	f = atof( buffer );
	
	printf( "Enter Velocity Factor : " );
	sgets( buffer , sizeof buffer );
	vf = atof( buffer );
	
	if ( f <= 0 )
	{
		printf( "\nFrequency must be >0!\n" );
		return;
	}
	
	if ( vf <= 0 || vf >= 1 )
	{
		printf( "\nVelocity Factor must be >0 and <1!\n" );
		return;
	}
	
	o = (74.9481 * vf / f) * 100;
	
	printf( "\nOpen End Stub = Notch Filter - Shorted Stub = Pass Filter\n" );
	printf( "\nCoax Stub Length -> %3.1f cm\n" , o);
}


void TXOutputMatch( void )
{
	char buffer[80];
	double DTOR , P , V , R1 , R2 , F , RA , Z1 , ZC1 , Z2 , ZC2 , Z3 , ZL1 , r , Qn , BW , Qn1 , Eff , Pd , QCoil;
	
	printf( "Enter TX Output Power (W): " );
	sgets( buffer , sizeof buffer );
	P = atof( buffer );
	
	printf( "Enter Collector or Plate Voltage Swing (V): " );
	sgets( buffer , sizeof buffer );
	V = atof( buffer );
	
	printf( "Enter TX Output Resistance (Ohms): " );
	sgets( buffer , sizeof buffer );
	R2 = atof( buffer );
	
	printf( "Enter TX Center Frequency (MHz): " );
	sgets( buffer , sizeof buffer );
	F = atof( buffer );
	
	printf( "Enter Unloaded Q of Coil : " );
	sgets( buffer , sizeof buffer );
	QCoil = atof( buffer );
	
	printf( "Enter Phase Shift Angle (Deg): " );
	sgets( buffer , sizeof buffer );
	r = atof( buffer );
	
	if ( P <= 0 )
	{
		printf( "\nTX Output Power must be >0!\n" );
		return;
	}
	
	if ( V <= 0 )
	{
		printf( "\nTX Collector or Plate Voltage Swing must be >0!\n" );
		return;
	}
	
	if ( R2 <= 0 )
	{
		printf( "\nTX Output Resistance must be >0!\n" );
		return;
	}
	
	if ( F < 0.1 || F > 2500 )
	{
		printf( "\nTX Center Frequency must be >0.1 and <2500!\n" );
		return;
	}
	
	if ( QCoil < 0.1 )
	{
		printf( "\nUnloaded Q of Coil must be >0.1!\n" );
		return;
	}
	
	if ( r < 90 || r > 180 )
	{
		printf( "\nPhase Shift Angle must be >=90 and <=180!\n" );
		return;
	}
	
	DTOR = PI / 180;

	R1 = pow(V , 2) / (2 * P);
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
	
	printf( "\nLoad Resistance -> %3.2f Ohms\n" , R2 );
	printf( "\nSource Resistance -> %3.2f Ohms\n" , R1 );
	printf( "\nSource Side Parallel Capacitor -> %3.1f pF\n" , ZC1 );
	printf( "\nLoad Side Parallel Capacitor -> %3.1f pF\n" , ZC2 );
	printf( "\nSeries Inductor -> %3.3f uH\n" , ZL1 );
	printf( "\nLoaded Q of Coil -> %3.1f\n" , Qn1 );
	printf( "\nCircuit Efficiency -> %3.1f %%\n" , Eff );
	printf( "\nSource Side Parallel Capacitor Reactance -> %3.1f Ohms\n" , Z1 );
	printf( "\nLoad Side Parallel Capacitor Reactance -> %3.1f Ohms\n" , Z2 );
	printf( "\nSeries Inductor Reactance -> %3.1f Ohms\n" , Z3 );
	printf( "\nBandwidth -> %3.1f MHz\n" , BW );
	printf( "\nPower Lost in Inductor -> %3.1f W\n" , Pd );
}


void ImpedanceMatch( void )
{
	char buffer[80];
	double DTOR , R1 , R2 , F , RA , Z1 , ZC1 , Z2 , ZC2 , Z3 , ZL1 , r , Qn , BW , Qn1 , Eff , QCoil;
	
	printf( "Source Resistance (Ohms): " );
	sgets( buffer , sizeof buffer );
	R1 = atof( buffer );
	
	printf( "Load Resistance (Ohms): " );
	sgets( buffer , sizeof buffer );
	R2 = atof( buffer );
	
	printf( "Enter TX Center Frequency (MHz): " );
	sgets( buffer , sizeof buffer );
	F = atof( buffer );
	
	printf( "Enter Unloaded Q of Coil : " );
	sgets( buffer , sizeof buffer );
	QCoil = atof( buffer );
	
	printf( "Enter Phase Shift Angle (90 - 180 Deg): " );
	sgets( buffer , sizeof buffer );
	r = atof( buffer );
	
	if ( R1 <= 0 )
	{
		printf( "\nSource Resistance must be >0!\n" );
		return;
	}
	
	if ( R2 <= 0 )
	{
		printf( "\nLoad Resistance must be >0!\n" );
		return;
	}
	
	if ( F < 0.1 || F > 2500 )
	{
		printf( "\nCenter Frequency must be >0.1 and <2500!\n" );
		return;
	}
	
	if ( QCoil < 0.1 )
	{
		printf( "\nUnloaded Q of Coil must be >0.1!\n" );
		return;
	}
	
	if ( r < 90 || r > 180 )
	{
		printf( "\nPhase Shift Angle must be >=90 and <=180!\n" );
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
	
	printf( "\nLoad Resistance -> %3.2f Ohms\n" , R2 );
	printf( "\nSource Resistance -> %3.2f Ohms\n" , R1 );
	printf( "\nSource Side Parallel Capacitor -> %3.1f pF\n" , ZC1 );
	printf( "\nLoad Side Parallel Capacitor -> %3.1f pF\n" , ZC2 );
	printf( "\nSeries Inductor -> %3.3f uH\n" , ZL1 );
	printf( "\nLoaded Q of Coil -> %3.1f\n" , Qn1 );
	printf( "\nCircuit Efficiency -> %3.1f %%\n" , Eff );
	printf( "\nSource Side Parallel Capacitor Reactance -> %3.1f Ohms\n" , Z1 );
	printf( "\nLoad Side Parallel Capacitor Reactance -> %3.1f Ohms\n" , Z2 );
	printf( "\nSeries Inductor Reactance -> %3.1f Ohms\n" , Z3 );
	printf( "\nBandwidth -> %3.1f MHz\n" , BW );
}


void V1V2( void )
{
	char buffer[80];
	double v1 , v2 , o;
	
	printf( "Enter Voltage 1 (V): " );
	sgets( buffer , sizeof buffer );
	v1 = atof( buffer );
	
	printf( "Enter Voltage 2 (V): " );
	sgets( buffer , sizeof buffer );
	v2 = atof( buffer );
	
	if ( v1 <= 0 )
	{
		printf( "\nVoltage 1 must be >0!\n" );
		return;
	}
	
	if ( v2 <= 0 )
	{
		printf( "\nVoltage 2 must be >0!\n" );
		return;
	}
	
	o = 20.0 * log10(v2/v1);
	
	printf( "\nDecibels -> %3.3f dB\n" , o );
	
}


void P1P2( void )
{

	char buffer[80];
	double p1 , p2 , o;
	
	printf( "Enter Power 1 : " );
	sgets( buffer , sizeof buffer );
	p1 = atof( buffer );
	
	printf( "Enter Power 2 : " );
	sgets( buffer , sizeof buffer );
	p2 = atof( buffer );
	
	if ( p1 <= 0 )
	{
		printf( "\nPower 1 must be >0!\n" );
		return;
	}
	
	if ( p2 <= 0 )
	{
		printf( "\nPower 2 must be >0!\n" );
		return;
	}
	
	o = 10.0 * log10(p2/p1);
	
	printf( "\nDecibels -> %3.3f dB\n" , o );
}


void dBmP( void )
{
	char buffer[80];
	double dBm , o;
	
	printf( "Enter dBm : " );
	sgets( buffer , sizeof buffer );
	dBm = atof( buffer );
	
	o = pow( 10.0 , dBm/10 );
	
	if ( o < 0.01 )
	{
		printf( "\nPower -> %.3e mW\n" , o );
	}
	else
	{	
		printf( "\nPower -> %3.3f mW\n" , o );
	}
}


void PdBm( void )
{
	char buffer[80];
	double pwr , o;
	
	printf( "Enter Power (mW) : " );
	sgets( buffer , sizeof buffer );
	pwr = atof( buffer );
	
	if ( pwr <= 0)
	{
		printf( "\nPower must be >0!\n" );
		return;
	}
		
	o = 10 * log10( pwr );
	
	if ( o < 0.01)
	{
		printf( "\nDecibels -> %.3edBm\n" , o);
	}
	else
	{	
		printf( "\nDecibels -> %3.3fdBm\n" , o);
	}
}


void dBmuV( void )
{
	char buffer[80];
	double v1 , v2 , o;
	
	printf( "Enter dBm : " );
	sgets( buffer , sizeof buffer );
	v1 = atof( buffer );
	
	printf( "Enter Impedance (Ohms): " );
	sgets( buffer , sizeof buffer );
	v2 = atof( buffer );
	
	if ( v2 <= 0 )
	{
		printf( "\nImpedance must be >0!\n" );
		return;
	}
	
	o = sqrt((pow(10 , (v1 + 30) / 10) * 1000000) * v2);
	
	printf( "\nVoltage -> %3.3f uV\n" , o );
}


void uVdBm( void )
{
	char buffer[80];
	double v1 , v2 , o;
	
	printf( "Enter Voltage (uV): " );
	sgets( buffer , sizeof buffer );
	v1 = atof( buffer );
	
	printf( "Enter Impedance (Ohms): " );
	sgets( buffer , sizeof buffer );
	v2 = atof( buffer );
	
	if ( v1 <= 0 )
	{
		printf( "\nVoltage must be >0!\n" );
		return;
	}
	
	if ( v2 <= 0 )
	{
		printf( "\nImpedance must be >0!\n" );
		return;
	}
	
	o = 10 * log10(pow(v1 * 0.000001 , 2) / v2) + 30;
	
	printf( "\nDecibels -> %3.3f dBm\n" , o );
}


void PdB( void )
{
	char buffer[80];
	double v1 , v2 , o;
	
	printf( "Enter Power : " );
	sgets( buffer , sizeof buffer );
	v1 = atof( buffer );
	
	printf( "Enter Decibels : " );
	sgets( buffer , sizeof buffer );
	v2 = atof( buffer );
	
	if ( v1 <= 0 )
	{
		printf( "\nPower must be >0!\n" );
		return;
	}
	
	o = v1 * (pow(10 , (v2 / 10)));
	
	printf( "\nPower -> %3.3f\n" , o );
}


void VdB( void )
{
	char buffer[80];
	double v1 , v2 , o;
	
	printf( "Enter Voltage : " );
	sgets( buffer , sizeof buffer );
	v1 = atof( buffer );
	
	printf( "Enter Decibels : " );
	sgets( buffer , sizeof buffer );
	v2 = atof( buffer );
	
	if ( v1 <= 0 )
	{
		printf( "\nVoltage must be >0!\n" );
		return;
	}
		
	o = v1 * (pow(10 , (v2 / 20)));
	
	printf( "\nVoltage -> %3.3f\n" , o );
}


void DecibelConversions( void )
{
	char buffer[3];
	int selection , done;
	done = 0;
	
	while (1)
	{
		printf( "\n\n   **** Decibel Conversion Menu ****\n\n" );
		printf( " 1. Voltage 1 -> Voltage 2\n" );
		printf( " 2. Power 1 -> Power 2\n" );
		printf( " 3. dBm -> Power\n" );
		printf( " 4. Power -> dBm\n" );
		printf( " 5. dBm -> Voltage uV\n" );
		printf( " 6. Voltage uV -> dBm\n" );
		printf( " 7. Power +/- dB\n" );
		printf( " 8. Voltage +/- dB\n" );
		
		printf( "\n 99. Exit\n\n" );
		printf( "Enter Selection: " );
		
		sgets( buffer , sizeof buffer );
		selection = atoi( buffer );
		
		printf( "\n\n" );
		
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
				printf( "Invalid Entry\n" );
				break;
		}
		if ( done == 1) break;
	}
}


void Resistors( void )
{
	double tresistance , nresistance;
	char buffer[80] , buffer1[80];
	
	printf( "Enter Initial Resistor : " );
	sgets( buffer , sizeof buffer );
	tresistance = atof( buffer );
	
	while(1)
	{
		printf( "Enter [S]eries , [P]arallel or [D]one: " );
		sgets(buffer1 , sizeof buffer1);
		
		if ( tolower( buffer1[0] ) == 'd' )
		{
			printf( "\nTotal Resistance = %3.3f\n" , tresistance);
			break;
		}

		printf( "Enter Next Resistor : " );
		sgets( buffer , sizeof buffer );
		nresistance = atof( buffer );

		if ( tolower( buffer1[0] ) == 's' )
		{
			tresistance += nresistance;
		}	

		if ( tolower( buffer1[0] ) == 'p' )
		{
			if ( nresistance > 0 ) tresistance = 1.0 / (1.0 / tresistance + 1.0 / nresistance);
		}
	}
}


void Inductors( void )
{
	double tinductance , ninductance;
	char buffer[80] , buffer1[80];
	
	printf( "Enter Initial Inductor : " );
	sgets( buffer , sizeof buffer );
	tinductance = atof( buffer );
	
	while(1)
	{
		printf( "Enter [S]eries , [P]arallel or [D]one: " );
		sgets(buffer1 , sizeof buffer1);
		
		if ( tolower( buffer1[0] ) == 'd')
		{
			printf( "\nTotal Inductance = %3.3f\n" , tinductance );
			break;
		}

		printf( "Enter Next Inductor : " );
		sgets( buffer , sizeof buffer );
		ninductance = atof( buffer );

		if ( tolower( buffer1[0] ) == 's')
		{
			tinductance += ninductance;
		}	

		if ( tolower( buffer1[0] ) == 'p')
		{
			if ( ninductance > 0 ) tinductance = 1.0 / (1.0 / tinductance + 1.0 / ninductance );
		}
	}
}


void Capacitors( void )
{
	double tcapacitance , ncapacitance;
	char buffer[80] , buffer1[80];
	
	printf( "Enter Initial Capacitor : " );
	sgets( buffer , sizeof buffer );
	tcapacitance = atof( buffer );
	
	while(1)
	{
		printf( "Enter [S]eries , [P]arallel or [D]one: " );
		sgets(buffer1 , sizeof buffer1 );
		
		if ( tolower( buffer1[0] ) == 'd')
		{
			printf( "\nTotal Capacitance = %3.3f\n" , tcapacitance );
			break;
		}

		printf( "Enter Next Capacitor : " );
		sgets( buffer , sizeof buffer );
		ncapacitance = atof( buffer );

		if ( tolower( buffer1[0] ) == 'p' )
		{
			tcapacitance += ncapacitance;
		}	

		if ( tolower( buffer1[0] ) == 's' )
		{
			if ( ncapacitance > 0) tcapacitance = 1.0 / (1.0 / tcapacitance + 1.0 / ncapacitance);
		}
	}
}


void RCI( void )
{
	char buffer[3];
	int selection , done;
	done = 0;
	
	while (1)
	{
		printf( "\n\n   **** Resistors , Inductors , Capacitors Menu ****\n\n" );
		printf( " 1. Resistors\n" );
		printf( " 2. Inductors\n" );
		printf( " 3. Capacitors\n" );
				
		printf( "\n 99. Exit\n\n" );
		printf( "Enter Selection: " );
		
		sgets( buffer , sizeof buffer );
		selection = atoi( buffer );
		
		printf( "\n\n" );
		
		switch ( selection )
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
				printf( "Invalid Entry\n" );
				break;
		}

		if ( done == 1 ) break;
	}
}

void ChebyshevFilter( void )
{
	char buffer[80] , inputtype , indcap[2] = { 'C' , 'L' };
	int filterorder , filtertype ,x , component , n;
	double fcl=0.0 , fch=0.0 , filterrippledb , c , l , r , b , *nelements = NULL , *aelements = NULL, *belements = NULL;

	printf( "Enter Filter Type (1 = Low Pass , 2 = High Pass , 3 = Band Pass , 4 = Band Stop) : " );
	sgets( buffer , sizeof buffer );
	filtertype = atoi( buffer );
	
	if ( filtertype < 1 || filtertype > 4 )
	{
		printf( "\nFilter Type must be 1 , 2 , 3 or 4\n" );
		return;
	}

	switch ( filtertype )
	{
		case 1:
			printf( "Enter Lowpass Cut-off Frequency (MHz): " );
			sgets( buffer , sizeof buffer );
			fcl = atof( buffer );
			break;

		case 2:
			printf( "Enter Highpass Cut-off Frequency (MHz): " );
			sgets( buffer , sizeof buffer );
			fch = atof( buffer );
			break;

		case 3:
			printf( "Enter Bandpass Lower Cut-off Frequency (MHz): " );
			sgets( buffer , sizeof buffer );
			fcl = atof( buffer );
			printf( "Enter Bandpass Upper Cut-off Frequency (MHz): " );
			sgets( buffer , sizeof buffer );
			fch = atof( buffer );
			if ( fch <= fcl )
			{
				printf( "\nHigher Cut-off frequency must be larger than Lower Cut-off frequency\n" );
				return;
			}
			break;

		case 4:
			printf( "Enter Bandstop Lower Cut-off Frequency (MHz): " );
			sgets( buffer , sizeof buffer );
			fcl = atof( buffer );
			printf( "Enter Bandstop Upper Cut-off Frequency (MHz): " );
			sgets( buffer , sizeof buffer );
			fch = atof( buffer );
			if ( fch <= fcl )
			{
				printf( "\nHigher Cut-off frequency must be larger than Lower Cut-off frequency\n" );
				return;
			}
			break;
	}

	fcl *= 1e6;
	fch *= 1e6;
	
	printf( "Enter Filter Order (Number of elements) : " );
	sgets( buffer , sizeof buffer );
	filterorder = atoi( buffer );
	
	if ( filterorder < 1 )
	{
		printf( "\nFilter Order must be > 1\n" );
		return;
	}

	nelements = malloc ( (filterorder + 1) * sizeof ( double ) );
	aelements = malloc ( (filterorder + 1) * sizeof ( double ) );
	belements = malloc ( (filterorder + 1) * sizeof ( double ) );

	if ( nelements == NULL || aelements == NULL || belements == NULL)
	{
		printf( "\nCould not allocate memory\n" );
		return;
	}

	printf( "Enter Input Type [T]ee or [P]i : " );
	sgets( buffer , sizeof buffer );
	
	inputtype = tolower( buffer[0] );
	if ( inputtype != 't' && inputtype != 'p' ) 
	{
		printf( "\nFilter Input Type must be Tee or Pi\n" );
		return;
	}

	printf( "Enter Filter Ripple dB : " );
	sgets( buffer , sizeof buffer );
	filterrippledb = atof( buffer );

	if ( filterrippledb < 0.01 )
	{
		printf( "\nFilter Ripple db must be > 0.01\n" );
		return;
	}

	printf( "Enter Filter Impedance : " );
	sgets( buffer , sizeof buffer );
	r = atof( buffer );

	if ( r < 0.01 )
	{
		printf( "\nFilter Impedance must be > 0.01\n" );
		return;
	}

	b = log(1/tanh(filterrippledb/17.37));

	for ( n = 1 ; n <= filterorder ; n++ )
	{
		aelements[n] = sin((2*n-1)*PI/2/filterorder);
	}

	for ( n = 0 ; n <= filterorder ; n++ )
	{	
		if ( n == 0 )
		{
				belements[n] = sinh(b/2/filterorder);
		}
		else
		{
				belements[n] = pow(belements[0],2)+pow(sin(n*PI/filterorder),2);
		} 
	}

	for ( n = 1 ; n <= filterorder + 1 ; n++ )
	{
		if ( n == filterorder + 1)
		{
				if ( filterorder % 2 == 0 )
				{
					if (inputtype == 't')
					{
						nelements[n] = pow (tanh(b/4),2);
					}
					else
					{
						nelements[n] = 1 / pow (tanh(b/4),2);
					}
				} 
				else
				{
						nelements[n] = 1.0;
				}
				break;
		}

		if ( n == 1 )
		{
			nelements[n] = 2 * aelements[n] / belements[n-1];
		}
		else
		{
			nelements[n] = 4 * aelements[n-1] * aelements[n] / belements[n-1] / nelements[n-1];
		}
	}

	switch( filtertype )
	{
		case 1:
			printf( "\nR(input) -> %3.1f\n" , r );

			if ( inputtype == 'p' ) x = 0; else x = 1;

			for ( component = 1 ; component <= filterorder ; component++ )
			{
				if ( indcap[x] == 'C' )
				{
					c = nelements[component];
					printf( "\nC -> %3.1f pF" , (c / ( 2 * PI * fcl * r)) * 1e12 );
				}

				if ( indcap[x] == 'L' )
				{
					l = nelements[component];
					printf( "\nL -> %3.3f uH" , ((l * r)/(2 * PI * fcl)) * 1e6 );
				}

				if ( inputtype == 'p' ) 
				{
					if ( x == 0 ) printf ( " Shunt\n" ); else printf ( " Series \n" );
				}

				if ( inputtype == 't' ) 
				{
					if ( x == 0 ) printf ( " Shunt\n" ); else printf ( " Series \n" );
				}

				x = 1 - x;
			}

			printf( "\nR(output) -> %3.1f\n" , r / nelements[component] );

			break;
		
		case 2:
			printf( "\nR(input) -> %3.1f\n" , r );

			if ( inputtype == 't' ) x = 0; else x = 1;

			for ( component = 1 ; component <= filterorder ; component++ )
			{
				if ( indcap[x] == 'C' )
				{
					l = nelements[component];
					printf( "\nC -> %3.1f pF" , (1 / (2 * PI * fch * r * l)) * 1e12 );
				}

				if ( indcap[x] == 'L' )
				{
					c = nelements[component];
					printf( "\nL -> %3.3f uH" , (r / (2 * PI * fch * c)) * 1e6 );
				}

				if ( inputtype == 'p' ) 
				{
					if ( x == 1 ) printf ( " Shunt\n" ); else printf ( " Series \n" );
				}

				if ( inputtype == 't' ) 
				{
					if ( x == 1 ) printf ( " Shunt\n" ); else printf ( " Series \n" );
				}

				x = 1 - x;
			}

			printf( "\nR(output) -> %3.1f\n" , r / nelements[component] );

			break;	

		case 3:
			printf( "\nR(input) -> %3.1f\n" , r );

			if ( inputtype == 't' ) x = 0; else x = 1;

			for ( component = 1 ; component <= filterorder ; component++ )
			{
				if ( indcap[x] == 'C' )
				{
					l = nelements[component];
					c = nelements[component];
					printf( "\n%c -> %3.3f uH" , indcap[1-x] , ((r * l) / (2 * PI * (fch - fcl))) * 1e6 );
					printf( "\n%c -> %3.1f pF" , indcap[x] , ((fch - fcl)/(2 * PI * fch * fcl * r * l)) * 1e12 );
				}

				if ( indcap[x] == 'L' )
				{
					c = nelements[component];
					l = nelements[component];
					printf( "\n%c -> %3.1f pF" , indcap[1-x] , (c/(2 * PI * (fch -fcl) * r )) * 1e12 );
					printf( "\n%c -> %3.3f uH" , indcap[x] , (((fch - fcl) * r)/(2 * PI * fch * fcl * c)) * 1e6 );
					
				}

				if ( inputtype == 'p' ) 
				{
					if ( x == 1 ) printf ( "\n Components Shunt\n" ); else printf ( "\n Components Series \n" );
				}

				if ( inputtype == 't' ) 
				{
					if ( x == 1 ) printf ( "\n Components Shunt\n" ); else printf ( "\n Components Series \n" );
				}

				x = 1 - x;
			}

			printf( "\nR(output) -> %3.1f\n" , r / nelements[component] );

			break;	

		case 4:
			printf( "\nR(input) -> %3.1f\n" , r );

			if ( inputtype == 't' ) x = 0; else x = 1;

			for ( component = 1 ; component <= filterorder ; component++ )
			{
				if ( indcap[x] == 'C' )
				{
					l = nelements[component];
					c = nelements[component];
					printf( "\n%c -> %3.3f uH" , indcap[1-x] , (((fch - fcl) * r * l)/(2 * PI * fch * fcl)) * 1e6 );
					printf( "\n%c -> %3.1f pF" , indcap[x] , (1/(2 * PI * (fch - fcl) * r * l)) * 1e12 );
				}

				if ( indcap[x] == 'L' )
				{
					c = nelements[component];
					l = nelements[component];
					printf( "\n%c -> %3.1f pF" , indcap[1-x] , (((fch - fcl) * c) / (2 * PI * fch * fcl * r)) * 1e12 );
					printf( "\n%c -> %3.3f uH" , indcap[x] , (r/(2 * PI * (fch - fcl) * c)) * 1e6 );
				}

				if ( inputtype == 'p' ) 
				{
					if ( x == 1 ) printf ( "\n Components in Series - Shunt\n" ); else printf ( "\n Components in Parallel - Series \n" );
				}

				if ( inputtype == 't' ) 
				{
					if ( x == 1 ) printf ( "\n Components in Series - Shunt\n" ); else printf ( "\n Components in Parallel - Series \n" );
				}

				x = 1 - x;
			}

			printf( "\nR(output) -> %3.1f\n" , r / nelements[component] );

			break;	
	}

	if ( nelements != NULL) free( nelements );
	if ( aelements != NULL) free( aelements );
	if ( belements != NULL) free( belements );

	return;
}

void ButterworthFilter( void )
{
	char buffer[80] , inputtype , indcap[2] = { 'C' , 'L' };
	int filterorder , filtertype ,x , component , n;
	double fcl=0.0 , fch=0.0 , c , l , r , *nelements = NULL;

	printf( "Enter Filter Type (1 = Low Pass , 2 = High Pass , 3 = Band Pass , 4 = Band Stop) : " );
	sgets( buffer , sizeof buffer );
	filtertype = atoi( buffer );
	
	if ( filtertype < 1 || filtertype > 4 )
	{
		printf( "\nFilter Type must be 1 , 2 , 3 or 4\n" );
		return;
	}

	switch ( filtertype )
	{
		case 1:
			printf( "Enter Lowpass Cut-off Frequency (MHz): " );
			sgets( buffer , sizeof buffer );
			fcl = atof( buffer );
			break;

		case 2:
			printf( "Enter Highpass Cut-off Frequency (MHz): " );
			sgets( buffer , sizeof buffer );
			fch = atof( buffer );
			break;

		case 3:
			printf( "Enter Bandpass Lower Cut-off Frequency (MHz): " );
			sgets( buffer , sizeof buffer );
			fcl = atof( buffer );
			printf( "Enter Bandpass Upper Cut-off Frequency (MHz): " );
			sgets( buffer , sizeof buffer );
			fch = atof( buffer );
			if ( fch <= fcl )
			{
				printf( "\nHigher Cut-off frequency must be larger than Lower Cut-off frequency\n" );
				return;
			}
			break;

		case 4:
			printf( "Enter Bandstop Lower Cut-off Frequency (MHz): " );
			sgets( buffer , sizeof buffer );
			fcl = atof( buffer );
			printf( "Enter Bandstop Upper Cut-off Frequency (MHz): " );
			sgets( buffer , sizeof buffer );
			fch = atof( buffer );
			if ( fch <= fcl )
			{
				printf( "\nHigher Cut-off frequency must be larger than Lower Cut-off frequency\n" );
				return;
			}
			break;
	}

	fcl *= 1e6;
	fch *= 1e6;
	
	printf( "Enter Filter Order (Number of elements) : " );
	sgets( buffer , sizeof buffer );
	filterorder = atoi( buffer );
	
	if ( filterorder < 1 )
	{
		printf( "\nFilter Order must be > 1\n" );
		return;
	}

	nelements = malloc ( (filterorder + 2) * sizeof ( double ) );
	
	if ( nelements == NULL )
	{
		printf( "\nCould not allocate memory\n" );
		return;
	}

	printf( "Enter Input Type [T]ee or [P]i : " );
	sgets( buffer , sizeof buffer );
	
	inputtype = tolower( buffer[0] );
	if ( inputtype != 't' && inputtype != 'p' ) 
	{
		printf( "\nFilter Input Type must be Tee or Pi\n" );
		return;
	}

	printf( "Enter Filter Impedance : " );
	sgets( buffer , sizeof buffer );
	r = atof( buffer );

	if ( r < 0.01 )
	{
		printf( "\nFilter Impedance must be > 0.01\n" );
		return;
	}

	for ( n = 1 ; n <= filterorder ; n++ )
	{
		nelements[n] = 2 * sin((2*n-1)*PI/2/filterorder);
	}
	nelements[n] = 1.0;

	switch( filtertype )
	{
		case 1:
			printf( "\nR(input) -> %3.1f\n" , r );

			if ( inputtype == 'p' ) x = 0; else x = 1;

			for ( component = 1 ; component <= filterorder ; component++ )
			{
				if ( indcap[x] == 'C' )
				{
					c = nelements[component];
					printf( "\nC-> %3.1f pF" , (c / ( 2 * PI * fcl * r)) * 1e12 );
				}

				if ( indcap[x] == 'L' )
				{
					l = nelements[component];
					printf( "\nL -> %3.3f uH" , ((l * r)/(2 * PI * fcl)) * 1e6 );
				}

				if ( inputtype == 'p' ) 
				{
					if ( x == 0 ) printf ( " Shunt\n" ); else printf ( " Series \n" );
				}

				if ( inputtype == 't' ) 
				{
					if ( x == 0 ) printf ( " Shunt\n" ); else printf ( " Series \n" );
				}

				x = 1 - x;
			}

			printf( "\nR(output) -> %3.1f\n" , r / nelements[component] );

			break;
		
		case 2:
			printf( "\nR(input) -> %3.1f\n" , r );

			if ( inputtype == 't' ) x = 0; else x = 1;

			for ( component = 1 ; component <= filterorder ; component++ )
			{
				if ( indcap[x] == 'C' )
				{
					l = nelements[component];
					printf( "\nC -> %3.1f pF" , (1 / (2 * PI * fch * r * l)) * 1e12 );
				}

				if ( indcap[x] == 'L' )
				{
					c = nelements[component];
					printf( "\nC -> %3.3f uH" , (r / (2 * PI * fch * c)) * 1e6 );
				}

				if ( inputtype == 'p' ) 
				{
					if ( x == 1 ) printf ( " Shunt\n" ); else printf ( " Series \n" );
				}

				if ( inputtype == 't' ) 
				{
					if ( x == 1 ) printf ( " Shunt\n" ); else printf ( " Series \n" );
				}

				x = 1 - x;
			}

			printf( "\nR(output) -> %3.1f\n" , r / nelements[component] );

			break;	

		case 3:
			printf( "\nR(input) -> %3.1f\n" , r );

			if ( inputtype == 't' ) x = 0; else x = 1;

			for ( component = 1 ; component <= filterorder ; component++ )
			{
				if ( indcap[x] == 'C' )
				{
					l = nelements[component];
					c = nelements[component];
					printf( "\n%c -> %3.3f uH" , indcap[1-x] , ((r * l) / (2 * PI * (fch - fcl))) * 1e6 );
					printf( "\n%c -> %3.1f pF" , indcap[x] , ((fch - fcl)/(2 * PI * fch * fcl * r * l)) * 1e12 );
				}

				if ( indcap[x] == 'L' )
				{
					c = nelements[component];
					l = nelements[component];
					printf( "\n%c%d -> %3.1f pF" , indcap[1-x] , component , (c/(2 * PI * (fch -fcl) * r )) * 1e12 );
					printf( "\n%c%d -> %3.3f uH" , indcap[x] , component , (((fch - fcl) * r)/(2 * PI * fch * fcl * c)) * 1e6 );
					
				}

				if ( inputtype == 'p' ) 
				{
					if ( x == 1 ) printf ( "\n Components Shunt\n" ); else printf ( "\n Components Series \n" );
				}

				if ( inputtype == 't' ) 
				{
					if ( x == 1 ) printf ( "\n Components Shunt\n" ); else printf ( "\n Components Series \n" );
				}

				x = 1 - x;
			}

			printf( "\nR(output) -> %3.1f\n" , r / nelements[component] );

			break;	

		case 4:
			printf( "\nR(input) -> %3.1f\n" , r );

			if ( inputtype == 't' ) x = 0; else x = 1;

			for ( component = 1 ; component <= filterorder ; component++ )
			{
				if ( indcap[x] == 'C' )
				{
					l = nelements[component];
					c = nelements[component];
					printf( "\n%c -> %3.3f uH" , indcap[1-x] , (((fch - fcl) * r * l)/(2 * PI * fch * fcl)) * 1e6 );
					printf( "\n%c -> %3.1f pF" , indcap[x] , (1/(2 * PI * (fch - fcl) * r * l)) * 1e12 );
				}

				if ( indcap[x] == 'L' )
				{
					c = nelements[component];
					l = nelements[component];
					printf( "\n%c -> %3.1f pF" , indcap[1-x] , (((fch - fcl) * c) / (2 * PI * fch * fcl * r)) * 1e12 );
					printf( "\n%c -> %3.3f uH" , indcap[x] , (r/(2 * PI * (fch - fcl) * c)) * 1e6 );
				}

				if ( inputtype == 'p' ) 
				{
					if ( x == 1 ) printf ( "\n Components in Series - Shunt\n" ); else printf ( "\n Components in Parallel - Series \n" );
				}

				if ( inputtype == 't' ) 
				{
					if ( x == 1 ) printf ( "\n Components in Series - Shunt\n" ); else printf ( "\n Components in Parallel - Series \n" );
				}

				x = 1 - x;
			}

			printf( "\nR(output) -> %3.1f\n" , r / nelements[component] );

			break;	
	}

	if ( nelements != NULL) free( nelements );

	return;
}

void Powers10( void )
{
	double number, number1;
	char buffer[80];
	char unitlabels[][6] = {"yotta","zetta","exa","peta","tera","giga","mega","kilo","unit","milli","micro","nano","pico","femto","atto","zepto","yotto"};
	double unitvalues[] = {1e24,1e21,1e18,1e15,1e12,1e9,1e6,1e3,1,1e-3,1e-6,1e-9,1e-12,1e-15,1e-18,1e-21,1e-24};
	int x , unit , s , e;

	printf( "\nEnter value : " );
	sgets( buffer , sizeof buffer );
	number = atof( buffer );
	number1 = number;
	
	for ( x=1 ; x <= 17 ; x++ )
	{
		printf( "%d. %s\n" , x , unitlabels[x-1]);
	}

	printf ( "\nChoose Unit : \n" );
	sgets( buffer , sizeof buffer );
	unit = atoi( buffer );	

	if ( unit < 1 || unit > 17 )
	{
		printf( "\nUnit must be 1-17\n" );
		return;
	}

	number = number * unitvalues[unit - 1];	

	s = unit - 3;
	e = unit + 3;

	if ( s < 1 ) s = 1;
	if ( e > 17 ) e = 17;

	printf( "\n%9.9g %s = \n" , number1 , unitlabels[unit-1] );

	for ( x=s ; x <= e ; x++)
	{
		printf( "\n   %9.9g %s" , number / unitvalues[x-1] , unitlabels[x-1] );
	}

	printf( "\n" );
}

void LineOfSight(void)
{
	char units , buffer[80] , ustringi[10] , ustringo[12];
	double ah1 , ah2 , d1 , d2 , dr1 , dr2 , ag1 , ag2 , fspl , f , td;

	printf( "\nEnter [M]etric or [E]nglish Units : " );
	sgets( buffer , sizeof buffer );

	units = tolower( buffer[0] );
	if ( units != 'm' && units != 'e' ) 
	{
		printf( "\nUnits must be [M]etric or [E]nglish\n" );
		return;
	}

	if ( units == 'm' ) 
	{
		strcpy( ustringi , "meters" );
		strcpy( ustringo , "kilometers" );
	}
	else
	{
		strcpy( ustringi , "feet" );
		strcpy( ustringo , "miles" );
	}

	printf( "\nEnter Antenna 1 Height (%s) : " , ustringi );
	sgets( buffer , sizeof buffer );
	ah1 = atof( buffer );
	if ( ah1 <= 0 )
	{
		printf ( "\nHeight must be greater than 0\n" );
		return;
	}

	printf( "\nEnter Antenna 1 Gain (db) : " );
	sgets( buffer , sizeof buffer );
	ag1 = atof( buffer );

	if ( ag1 < 0 )
	{
		printf ( "\nGain must be >= 0\n" );
		return;
	}

	printf( "\nEnter Antenna 2 Height (%s) : " , ustringi );
	sgets( buffer , sizeof buffer );
	ah2 = atof( buffer );
	if ( ah2 <= 0 )
	{
		printf ( "\nHeight must be greater than 0\n" );
		return;
	}

	printf( "\nEnter Antenna 2 Gain (db) : " );
	sgets( buffer , sizeof buffer );
	ag2 = atof( buffer );
	if ( ag2 <= 0 )
	{
		printf ( "\nGain must be >= 0\n" );
		return;
	}

	printf( "\nEnter Frequency (MHz) : " );
	sgets( buffer , sizeof buffer );
	f = atof( buffer );

	if ( units == 'm' )
	{
		d1 = 3.57 * sqrt(ah1);
		d2 = 3.57 * sqrt(ah2);
		dr1 = 4.12 * sqrt(ah1);
		dr2 = 4.12 * sqrt(ah2);
		td = ((d1 + d2) + (dr1 + dr2))/2;
		fspl = 20*log10(td) + 20*log10(f) + 32.45 - ag2 - ag1;
	} 
	else
	{
		d1 = 1.23 * sqrt(ah1);
		d2 = 1.23 * sqrt(ah2);
		dr1 = 1.41 * sqrt(ah1);
		dr2 = 1.41 * sqrt(ah2);
		td = ((d1 + d2) + (dr1 + dr2))/2;
		fspl = 20*log10(td/0.621371) + 20*log10(f) + 32.45 - ag2 - ag1;
	}

	printf ( "\n\nDistance to physical horizon for Antenna 1 : %3.1f %s\n" , d1 , ustringo );
	printf ( "Distance to physical horizon for Antenna 2 : %3.1f %s\n" , d2 , ustringo );
	printf ( "\nDistance to radio horizon for Antenna 1 : %3.1f %s\n" , dr1 , ustringo);
	printf ( "Distance to radio horizon for Antenna 2 : %3.1f %s\n" , dr2 , ustringo);
	printf ( "\nTypical communication distance  : %3.1f %s\n" , td , ustringo);
	printf ( "\nFree Space Path Loss %3.1f dB\n" , fspl);
}

void ResistorAttenuator( void )
{
	char buffer[80], type;
	double attn , z , r1 , r2;

	printf( "\nEnter Attenuation (dB) : " );
	sgets( buffer , sizeof buffer );
	attn = atof( buffer );

	if ( attn <= 0 )
	{
		printf ( "\nAttenuation must be greater than 0\n" );
		return;
	}

	printf( "\nEnter Impedance (Ohms) : " );
	sgets( buffer , sizeof buffer );
	z = atof( buffer );

	if ( z <= 0 )
	{
		printf ( "\nImpedance must be greater than 0\n" );
		return;
	}

	printf( "\nEnter [P]i or [T]ee : " );
	sgets( buffer , sizeof buffer );

	type = tolower( buffer[0] );
	if ( type != 'p' && type != 't' ) 
	{
		printf( "\nUnits must be [P]i or [T]ee\n" );
		return;
	}

	if ( type == 'p' )
	{
		r1 = z*((pow(10,attn/20)+1)/(pow(10,attn/20)-1));
		r2 = (z/2)*((pow(10,attn/10)-1)/pow(10,attn/20));
	}
	else
	{
		r1 = z*((pow(10,attn/20)-1)/(pow(10,attn/20)+1));
		r2 = 2*z*((pow(10,attn/20)/(pow(10,attn/10)-1)));
	}

	printf ( "\nR1 -> %3.2f\n", r1 );
	printf ( "\nR2 -> %3.2f\n", r2 );
}

void CoaxLoss( void )
{
	double k1[] = {0.26293,0.16925,0.12050,0.26904,0.11287,0.16925,0.34190,0.35364,0.38823,0.45322,0.29629,0.32074,0.26247,0.37381,0.76172,0.18993,0.14044,0.70501,0.32062,0.24271,0.12013,0.07563,0.05190,0.12102,0.14044,0.41009,0.45876,0.13757,0.31217,0.36305,0.28692,0.06432,0.03482,0.02397,0.04960,0.05100,0.06210,0.04140,0.05654,0.05557,0.07291,0.03083,0.10181,0.02713,0.01897,0.00000,0.00000};
	double k2[] = {0.00159,0.00204,0.00066,0.00572,0.00160,0.00313,0.00377,0.00526,0.00566,0.00836,0.00147,0.00174,0.00039,0.00159,0.00955,0.00216,0.00032,0.00183,0.00034,0.00032,0.00031,0.00026,0.00015,0.00066,0.00032,0.00360,0.00837,0.00366,0.00313,0.00438,0.00060,0.00019,0.00015,0.00014,0.00120,
	0.00100,0.00090,0.00170,0.07176,0.06182,0.05510,0.07756,0.00068,0.00024,0.00010,0.00000,0.00000};

	char types[][30] = {"Belden 8215 (RG-6A)","Belden 8237 (RG-8)","Belden 9913 (RG-8)","Belden 9258 (RG-8X)","Belden 8213 (RG-11)","Belden 8261 (RG-11A)","Belden 8240 (RG-58)","Belden 9201 (RG-58)","Belden 8219 (RG-58A)","Belden 8259 (RG-58C)","Belden 8212 (RG-59)","Belden 8263 (RG-59B)","Belden 9269 (RG-62A)","Belden 83241 (RG-141A)","Belden 8216 (RG-174)","Belden 8267 (RG-213)","Davis RF Bury-Flex","TMS LMR-100A","TMS LMR-200","TMS LMR-240","TMS LMR-400","TMS LMR-600","TMS LMR-900","Wireman CQ102 (RG-8)","Wireman CQ106 (RG-8)","Wireman CQ125 (RG-58)","Wireman CQ127 (RG-58C)","Wireman CQ110 (RG-213)","Tandy Cable RG-8X","Tandy Cable RG-58","Tandy Cable RG-59","Andrew Heliax LDF4-50A","Andrew Heliax LDF5-50A","Andrew Heliax LDF6-50A","Wireman 551 Ladder Line","Wireman 552 Ladder Line","Wireman 553 Ladder Line","Wireman 554 Ladder Line","Wireman 551 (wet)","Wireman 552 (wet)","Wireman 553 (wet)","Wireman 554 (wet)","Generic 300 ohm Tubular","Generic 450 ohm Window","Generic 600 ohm Open","Ideal (lossless) 50 ohm","Ideal (lossless) 75 ohm"};

	int x , i , c;
	double freq , swr , len , pwrin , mldb , rho , alpha , totdb , swrdb , pwrout;
	char buffer[80] , units;

	printf( "\n" );
	c = sizeof (types) / 30;

	for ( x=0 ; x < c ; x++)
	{
		printf( "\n%d. %s" , x + 1 ,types[x]);
	}

	printf( "\n\nEnter Coax Selection : " );
	sgets( buffer , sizeof buffer );
	i = atoi( buffer ) - 1;

	if ( i < 0 || i > c )
	{
		printf( "\nSelection must be 1-%d\n" , c);
		return;
	}

	printf( "\nEnter [M]etric or [E]nglish : " );
	sgets( buffer , sizeof buffer );

	units = tolower( buffer[0] );
	if ( units != 'm' && units != 'e' ) 
	{
		printf( "\nUnits must be [M]etric or [E]nglish\n" );
		return;
	}

	if ( units == 'm' ) 
	{
		printf( "\nEnter Line Length (Meters) : " );
	}
	else
	{
		printf( "\nEnter Line Length (Feet) : " );
	}

	sgets( buffer , sizeof buffer );
	len = atof( buffer );

	if ( len < 0 )
	{
		printf( "\nLength must be > 0\n" );
		return;
	}

	printf( "\nEnter Frequency (MHz) : " );
	sgets( buffer , sizeof buffer );
	freq = atof( buffer );

	if ( freq < 0 )
	{
		printf( "\nFrequency must be > 0\n" );
		return;
	}

	printf( "\nEnter SWR (x:1) : " );
	sgets( buffer , sizeof buffer );
	swr = atof( buffer );

	if ( swr < 1 )
	{
		printf( "\nSWR must be >= 1\n" );
		return;
	}

	printf( "\nEnter Power Input (W) : " );
	sgets( buffer , sizeof buffer );
	pwrin = atof( buffer );

	if ( pwrin <= 0 )
	{
		printf( "\nPower Input must be > 0\n" );
		return;
	}

	mldb = (k1[i] * sqrt(freq) + k2[i] * freq) / 100 * len;
	if ( units == 'm' ) mldb = mldb / 0.3048;

	rho = (swr - 1) / (swr + 1);
	alpha = pow(10,mldb / 10);
	totdb = 10 * (log((pow(alpha,2) - pow(rho,2)) / (alpha * (1 - pow(rho,2)))) / 2.302585092994046);
	swrdb  = totdb - mldb;
	pwrout = pwrin * pow(10,(-totdb / 10));

	printf ( "\n\nMatched Loss %3.2f dB\n" , mldb );
	printf ( "\nSWR Loss %3.2f dB\n" , swrdb );
	printf ( "\nTotal Loss %3.2f dB\n" , totdb);
	printf ( "\nPower Output %3.1f W\n" , pwrout);
}

void WireAntennaLength( void )
{
	char buffer[80] , units;
	double f;

	printf( "\nEnter [M]etric or [E]nglish : " );
	sgets( buffer , sizeof buffer );

	units = tolower( buffer[0] );
	if ( units != 'm' && units != 'e' ) 
	{
		printf( "\nUnits must be [M]etric or [E]nglish\n" );
		return;
	}

	printf( "\nEnter Frequency (MHz) : " );
	sgets( buffer , sizeof buffer );
	f = atof( buffer );

	if ( units == 'm' )
	{
		printf ( "\nHalf Wave %3.2f Meters" , (468/f) * 0.3048 );
		printf ( "\nHalf Wave %3.2f Centimeters\n", (468/f) * 30.48 );
		printf ( "\nQuarter Wave %3.2f Meters" , (468/f) * 0.3048 / 2 );
		printf ( "\nQuarter Wave %3.2f Centimeters\n" , (468/f) * 30.48 / 2 );
	}
	else
	{
		printf ( "\nHalf Wave %3.2f Feet" , 468/f );
		printf ( "\nHalf Wave %3.2f Inches\n", (468/f) * 12 );
		printf ( "\nQuarter Wave %3.2f Feet" , (468/f) / 2 );
		printf ( "\nQuarter Wave %3.2f Inches\n" , (468/f) / 2 * 12 );
	}
}

void ImageFrequency( void )
{
	char buffer[80];
	double rf, intf, im1,im2,lo1,lo2;
	
	printf ( "\nEnter Reception Frequency : " );
	sgets( buffer , sizeof buffer );
	rf = atof ( buffer );

	printf ( "\nEnter Intermediate Frequency : " );
	sgets( buffer , sizeof buffer );
	intf = atof ( buffer );

	im1 = fabs(intf * 2 - rf);
	im2 = fabs(intf * 2 + rf);
	lo1 = fabs(intf - rf);
	lo2 = fabs(intf + rf);

	printf ( "\nImage Frequencies: %3.3f & %3.3f", im1, im2);
	printf ( "\nLocal Oscillator Frequencies: %3.3f & %3.3f\n", lo1, lo2);
}

int main ( void )
{
	char buffer[4];
	int selection , done;
	done = 0;
	
	while (1)
	{
		printf( "\n\n   **** RF Calculator Main Menu ****\n\n" );
		printf( " 1. Turns to Inductance for Toroid Coil\n" );
		printf( " 2. Turns to Inductance for Air Core Coil\n" );
		printf( " 3. Capacitance vs Frequency for Tank Circuit\n" );
		printf( " 4. Inductance vs Frequency for Tank Circuit\n" );
		printf( " 5. Capacitive Reactance @ Frequency\n" );
		printf( " 6. Inductive Reactance @ Frequency\n" );
		printf( " 7. SWR for Input Z vs Output Z\n" );
		printf( " 8. Power Radiated and Lost for SWR @ TX Power\n" );
		printf( " 9. SWR for Power Forward vs Power Reflected\n" );
		printf( "10. Variable Capacitor Scaling\n" );
		printf( "11. Coax Stub Notch & Pass\n" );
		printf( "12. Transmitter Output Matching PI Network\n" );
		printf( "13. Impedance Matching PI Network\n" );
		printf( "14. Decibel Conversions\n" );
		printf( "15. Resistors , Inductors , Capacitors - Series & Parallel\n" );
		printf( "16. Torroid Al Value from Inductance and Turns\n" );
		printf( "17. Chebyshev Filters\n" );
		printf( "18. Butterworth Filters\n" );
		printf( "19. Nearby Powers of 10 Conversion\n" );
		printf( "20. Line of Sight Distance / Free Space Path Loss\n" );
		printf( "21. Resistor Attenuators\n" );
		printf( "22. Coax Loss\n" );
		printf( "23. Wire Antenna Length\n" );
		printf( "24. Image Frequency and Local Oscillator\n" );
		printf( "\n 99. Exit\n\n" );
		printf( "Enter Selection: " );
		
		sgets( buffer , sizeof buffer );
		selection = atoi( buffer );
		
		printf( "\n\n" );
		
		switch ( selection )
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

			case 17:
				ChebyshevFilter();
				PauseForEnterKey();
				break;

			case 18:
				ButterworthFilter();
				PauseForEnterKey();
				break;

			case 19:
				Powers10();
				PauseForEnterKey();
				break;

			case 20:
				LineOfSight();
				PauseForEnterKey();
				break;

			case 21:
				ResistorAttenuator();
				PauseForEnterKey();
				break;

			case 22:
				CoaxLoss();
				PauseForEnterKey();
				break;

			case 23:
				WireAntennaLength();
				PauseForEnterKey();
				break;

			case 24:
				ImageFrequency();
				PauseForEnterKey();
				break;

			case 99:
				done = 1;
				break;

			default:
				printf( "Invalid Entry\n" );
				break;
		}

		if ( done == 1) break;
	}

	return 0;
}



