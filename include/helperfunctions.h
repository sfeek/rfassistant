#include <complex.h>

double getfrequency (const char *display);
double getcapacitance (const char *display);
double getinductance (const char *display);
double getresistance (const char *display);
double getpower (const char *display);
double getdistance (const char *display);
double getvoltage (const char *display);
double getamperage (const char *display);
void showfrequency (double);
void showcapacitance (double);
void showinductance (double);
void showpower (double);
void showdistance (double);
void showresistance (double);
void showvoltage (double);
void showamperage (double);

#ifdef __linux__
    double complex getimpedance (const char *display);
#endif

#ifdef _WIN32
    _Dcomplex getimpedance (const char *display);
    _Dcomplex add_complex (_Dcomplex, _Dcomplex);
    _Dcomplex sub_complex (_Dcomplex, _Dcomplex);
    _Dcomplex div_complex (_Dcomplex, _Dcomplex);
    _Dcomplex mult_complex (_Dcomplex, _Dcomplex);
#endif