#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <errno.h>

#define FALSE 0 /* False */
#define TRUE 1 /* True */
#define SUCCESS 0 /* Great success! */
#define FAIL 1 /* General Fail */
#define FAIL_MEMORY 2 /* Failed memory allocation */
#define FAIL_NUMBER 3 /* Invalid number */
#define FAIL_PARAMETER 4 /* Invalid value in a parameter */

#define PI 3.14159265358979323846
#define E 2.71828182845904523536

#define free_malloc(p) (free(p),p=NULL)

typedef struct Fraction {
    int n;
    int d;
} fraction;

int append_string (char **, char *);
int copy_string (char **, char *);
int sprintf_string (char **, char *fmt, ... );
int truncate_string (char **, size_t);
int replace_string (char **, const char *, const char *);
int wrap_string (char **, size_t);
size_t get_string (char**, const char *);
size_t len_string(char **);
int string_to_double (const char *, double *);
int string_to_int (const char *, int *);
size_t int_to_string (char**, int);
size_t double_to_string (char**, double, int);
int sub_string(char**, size_t, size_t);
int left_string(char** str, size_t s);
int right_string(char** str, size_t s);

int csv_parse(char ***,char *, size_t *);
void cleanup_csv_strings(char **,size_t);

void pause_for_enter (const char *);

int float_less_than (double, double, double);
double get_double (const char *);
int get_int (const char *);
double deg_to_rad(double);
double rad_to_deg(double);

fraction decimal_to_fraction(double, double);
double fraction_to_decimal(fraction);

void d_swap(double *, double *);
int d_partition(double[], int, int);
void d_sort(double [], int, int);
int array_sort_double(double[], int);

void i_swap(int *, int *);
int i_partition(int [], int, int);
void i_sort(int [], int, int);
int array_sort_int(int [], int);
