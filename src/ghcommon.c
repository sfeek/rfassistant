#include "../include/ghcommon.h"

#ifdef _WIN32
	#include <complex.h>
	#include <math.h>
#endif

int append_string(char **s1, char *s2)
{
	char *t;
	size_t len_s1, len_s2;

	if (s2 == NULL)
		return SUCCESS;

	if ((len_s2 = strlen(s2)) == 0)
		return SUCCESS;

	if (*s1 == NULL)
	{
		len_s1 = 0;
		if (!(*s1 = calloc(len_s1 + len_s2 + 1, sizeof(char))))
			return FAIL_MEMORY;
	}
	else
	{
		len_s1 = strlen(*s1);
		if (!(t = realloc(*s1, (len_s1 + len_s2 + 1) * sizeof(char))))
		{
			if (*s1)
				free(*s1);
			*s1 = NULL;
			return FAIL_MEMORY;
		}
		else
			*s1 = t;
	}

	strcat(*s1, s2);

	return SUCCESS;
}

size_t len_string(char **s)
{
	return strlen(*s);
}

size_t get_string(char **s, const char *display)
{
	char c;
	char cs[2];
	size_t count = 0;

	if (display)
		printf("%s", display);

	while ((c = fgetc(stdin)) != '\n')
	{
		cs[0] = c;
		cs[1] = 0;
		if (append_string(s, cs))
			return 0;

		count++;
	}

	return count;
}

int copy_string(char **s, char *s1)
{
	char *t;
	size_t len;

	if (s1 == NULL)
		return SUCCESS;

	if (strlen(s1) == 0)
		return SUCCESS;

	len = strlen(s1);

	if (*s == NULL)
	{
		if (!(*s = calloc(len + 1, sizeof(char))))
			return FAIL_MEMORY;
	}
	else
	{
		if (!(t = realloc(*s, (len + 1) * sizeof(char))))
		{
			if (*s)
				free(*s);
			*s = NULL;
			return FAIL_MEMORY;
		}
		else
			*s = t;
	}

	strcpy(*s, s1);

	return SUCCESS;
}

int truncate_string(char **s, size_t len)
{
	char *t;

	if (*s == NULL)
		return SUCCESS;

	if (len >= strlen(*s))
		return FAIL_PARAMETER;

	if (!(t = realloc(*s, (len + 2) * sizeof(char))))
	{
		if (*s)
			free(*s);
		*s = NULL;
		return FAIL_MEMORY;
	}
	else
		t[len + 1] = '\0';

	*s = t;

	return SUCCESS;
}

int sprintf_string(char **s, char *fmt, ...)
{
	char *t;
	size_t len;
	va_list args;

	va_start(args, fmt);
	len = vsnprintf(NULL, 0, fmt, args);
	va_end(args);

	if (*s == NULL)
	{
		if (!(*s = malloc((len + 1) * sizeof(char))))
			return FAIL_MEMORY;
	}
	else
	{
		if (!(t = realloc(*s, (len + 1) * sizeof(char))))
		{
			if (*s)
				free(*s);
			*s = NULL;
			return FAIL_MEMORY;
		}
		else
			*s = t;
	}

	va_start(args, fmt);
	vsprintf(*s, fmt, args);
	va_end(args);

	return SUCCESS;
}

int replace_string(char **s, const char *oldW, const char *newW)
{
	char *str;
	size_t i, j, l, cnt = 0;
	char *r;
	size_t newWlen = strlen(newW);
	size_t oldWlen = strlen(oldW);

	if (*s == NULL)
		return FAIL_PARAMETER;

	str = strdup(*s);
	l = strlen(str);

	for (i = 0; str[i] != '\0'; i++)
	{
		if (strstr(&str[i], oldW) == &str[i])
		{
			cnt++;
			i += oldWlen;
		}
	}

	if (!(r = realloc(*s, (i + cnt * (newWlen - oldWlen) + 1) * sizeof(char))))
	{
		if (*s)
			free(*s);
		*s = NULL;
		return FAIL_MEMORY;
	}

	i = 0;
	j = 0;

	for (i = 0; i < l;)
	{
		if (strstr(str + i, oldW) == str + i)
		{
			if (newW[0] != '\0')
				strcpy(&r[i], newW);
			j += newWlen;
			i += oldWlen;
		}
		else
			r[j++] = str[i++];
	}

	r[j] = '\0';

	if (str)
		free(str);
	str = NULL;

	*s = r;

	return SUCCESS;
}

int wrap_string(char **s, size_t columns)
{
	int nextspace = 0;
	size_t l, w;

	char *t;

	if (*s == NULL)
		return FAIL;

	l = strlen(*s);

	if (!(t = realloc(*s, (l + 1) * sizeof(char))))
	{
		if (*s)
			free(*s);
		*s = NULL;
		return FAIL_MEMORY;
	}

	for (w = 1; w < l; w++)
	{
		if (w % columns == 0)
			nextspace = 1;

		if (t[w] == ' ')
		{
			if (nextspace == 1)
			{
				t[w] = '\n';
				nextspace = 0;
			}
		}
	}
	t[w] = '\0';

	*s = t;

	return SUCCESS;
}

int sub_string(char **str, size_t s, size_t e)
{
	char *temp;
	size_t x;
	size_t l = strlen(*str);

	if (e < s)
		return FAIL_PARAMETER;
	if (s > l || e > l)
		return FAIL_PARAMETER;

	if (!(temp = malloc((e - s + 2) * sizeof(char))))
		return FAIL_MEMORY;

	for (x = 0; x <= (e - s); x++)
	{
		temp[x] = (*str)[s + x];
	}

	temp[x] = '\0';

	*str = temp;

	return SUCCESS;
}

int left_string(char **str, size_t s)
{
	char *temp;
	size_t x;
	size_t l = strlen(*str);

	if (s > l)
		return FAIL_PARAMETER;

	if (!(temp = malloc((s + 2) * sizeof(char))))
		return FAIL_MEMORY;

	for (x = 0; x <= s; x++)
	{
		temp[x] = (*str)[x];
	}

	temp[x] = '\0';

	*str = temp;

	return SUCCESS;
}

int right_string(char **str, size_t s)
{
	char *temp;
	size_t x;
	size_t l = strlen(*str);

	if (s > l)
		return FAIL_PARAMETER;

	if (!(temp = malloc((s + 2) * sizeof(char))))
		return FAIL_MEMORY;

	for (x = 0; x <= s; x++)
	{
		temp[x] = (*str)[x + (l - s - 1)];
	}

	temp[x] = '\0';

	*str = temp;

	return SUCCESS;
}

void pause_for_enter(const char *display)
{
	char ch;

	printf("%s", display);

	while (1)
	{
		ch = fgetc(stdin);

		if (ch == '\n')
			break;
	}

	return;
}

/* Math Functions */

/* Used with FOR loops to properly handle fractional step values */
int float_less_than(double f1, double f2, double step)
{
	if (f1 > f2 + 1e-14)
		return 0;

	if ((f2 + step) - f1 > 1e-14)
		return 1;
	else
		return 0;
}

int string_to_double(const char *str, double *v)
{
	char *ptr;
	errno = 0;

	if (str == NULL)
		return FAIL_PARAMETER;

	*v = strtod(str, &ptr);

	if (errno == ERANGE)
	{
		return FAIL_NUMBER;
	}

	if (str == ptr)
		return FAIL_NUMBER;

	return SUCCESS;
}

int string_to_int(const char *str, int *v)
{
	char *ptr;
	errno = 0;

	if (str == NULL)
		return FAIL_PARAMETER;

	*v = (int)strtol(str, &ptr, 10);

	if (errno == ERANGE)
	{
		return FAIL_NUMBER;
	}

	if (str == ptr)
	{
		return FAIL_NUMBER;
	}

	return SUCCESS;
}

size_t int_to_string(char **s, int i)
{
	sprintf_string(s, "%d", i);

	return strlen(*s);
}

size_t double_to_string(char **s, double d, int digits)
{
	char *dlen = NULL;

	sprintf_string(&dlen, "%%0.%df", digits);
	sprintf_string(s, dlen, d);

	return strlen(*s);
}

double get_double(const char *display)
{
	char *buffer = NULL;
	double value;
	int rtn;

	while (TRUE)
	{
		if (get_string(&buffer, display) == 0)
			continue;

		rtn = string_to_double(buffer, &value);

		if (buffer)
			free(buffer);
		buffer = NULL;

		if (rtn == SUCCESS)
			return value;
	}
}

int get_int(const char *display)
{
	char *buffer = NULL;
	int value;
	int rtn;

	while (TRUE)
	{
		if (get_string(&buffer, display) == 0)
			continue;

		rtn = string_to_int(buffer, &value);

		if (buffer)
			free(buffer);
		buffer = NULL;

		if (rtn == EXIT_SUCCESS)
			return value;
	}
}

double deg_to_rad(double deg)
{
	return PI / 180.0 * deg;
}

double rad_to_deg(double rad)
{
	return rad * 180.0 / PI;
}

void array_sort_double(double *array, size_t n)
{
	int i, j;
	double temp;

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n - 1; j++)
		{
			if (array[j] > array[j + 1])
			{
				temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
		}
	}
}

void array_sort_int(int *array, size_t n)
{
	int i, j, temp;

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n - 1; j++)
		{
			if (array[j] > array[j + 1])
			{
				temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
		}
	}
}

/* CSV Functions*/
int csv_parse(char ***array, char *str, size_t *number_of_fields)
{
	char *new_str = NULL;
	char current_character;
	char **str_array = NULL;
	int quote = 0;
	size_t csv_length; 
	int max_field_count = 2; /* Start with two fields as MAX */
	int *comma_positions = NULL;
	int *comma_temp = NULL;
	int current_field = 0;
	int clean_string_position = 0;
	int i;
	int start_position = 0;
	int field_length;

	if (str == NULL) return FAIL_PARAMETER;

	csv_length= strlen(str);

	/* Allocate memory for the comma position array */
	if (!(comma_positions = calloc(1, sizeof(int) * max_field_count)))
	{
		return FAIL_MEMORY;
	}

	/* Allocate memory for "cleaned up" string the same size as the original string to guarantee that it is big enough */
	if (!(new_str = calloc(1, sizeof(char) * (csv_length + 1))))
	{
		return FAIL_MEMORY;
	}

	/* First pass through to record the correct comma positions */
	for (i = 0; i < csv_length; i++)
	{
		/* Get a single character and skip any control or garbage characters */
		if ((current_character = str[i]) < 32)
			continue;

		/* Handle quotes, escapes and commas */
		switch (current_character)
		{
		/* Check for escape character not inside quotes */
		case 92:
		{
			if (quote == 0)
			{
				/* Move ahead one character */
				i++;
				/* Keep the next good character and move to the next good character position*/
				new_str[clean_string_position++] = str[i];
				/* Move on to the next new character */
				continue;
			}

			break;
		}

		/* Check for quote and keep track of pairs */
		case 34:
		{
			/* Toggle the pair indicator */
			quote = 1 - quote;
			/* Skip the quote */
			continue;
		}

		/* Check for comma that is NOT inside quotes */
		case 44:
		{
			if (quote == 0)
			{
				/* Check to see if we need to grow our comma position array */
				if (current_field == max_field_count - 1)
				{
					/* Double in size each time */
					max_field_count *= 2;

					/* Allocate more memory for the array*/
					comma_temp = realloc(comma_positions, sizeof(int) * max_field_count);

					if (comma_temp == NULL)
					{
						return FAIL_MEMORY;
					}
					else
						comma_positions = comma_temp;
				}

				/* Keep track of the comma positions and move to the next field*/
				comma_positions[current_field++] = clean_string_position;
			}
		}
		}

		/* Keep the good characters and move to the next good character position  */
		new_str[clean_string_position++] = current_character;
	}

	/* Make sure that clean string gets NULL terminator */
	new_str[clean_string_position] = 0;
	/* Make sure to mark the end of the string as a "comma" position so that the last field gets included in the array and include the last field */
	comma_positions[current_field++] = clean_string_position;
	/* Record the Total number of fields to return to the calling function */
	*number_of_fields = current_field;
	/* Allocate an array of pointers to chars, not actually allocating any strings themselves */
	str_array = malloc(sizeof(char *) * current_field);
	if (str_array == NULL)
		return FAIL_MEMORY;

	/* Copy the strings to the new string array */
	for (i = 0; i < current_field; i++)
	{
		/* Calculate length of the current field plus the Null Terminator*/
		field_length = comma_positions[i] - start_position + 1;
		/* Replace the comma with a Null terminator */
		new_str[comma_positions[i]] = 0;
		/* Allocate memory for the current field */
		str_array[i] = malloc(sizeof(char) * field_length);
		if (str_array[i] == NULL)
			return FAIL_MEMORY;
		/* Copy the string into the new array */
		memcpy(str_array[i], new_str + start_position, field_length);
		/* Move our start position to the next field */
		start_position = comma_positions[i] + 1;
	}

	/* Clean up the dynamic arrays */
	if (comma_positions)
		free(comma_positions);
	comma_positions = NULL;

	if (new_str)
		free(new_str);
	new_str = NULL;

	*array = str_array;
	/* Return the new array back to the calling function */

	return SUCCESS;
}

/*  Clean up an array of strings
	Input:  Array of strings
			Number of strings
	Return: none
*/
void cleanup_csv_strings(char **strArray, size_t numberOfStrings)
{
	int i;

	/* Free the individual strings */
	for (i = 0; i < numberOfStrings; i++)
	{
		if (strArray[i])
			free(strArray[i]);
		strArray[i] = NULL;
	}

	/* Once the strings themselves are freed, free the actual array itself */
	if (strArray)
		free(strArray);
	strArray = NULL;
}


#ifdef _WIN32
  	_Dcomplex add_complex (_Dcomplex n1, _Dcomplex n2)
	{
		_Dcomplex num;
		num._Val[0] = n1._Val[0] + n2._Val[0];
		num._Val[1] = n1._Val[1] + n2._Val[1];

		return num;
	}

	_Dcomplex sub_complex (_Dcomplex n1, _Dcomplex n2)
	{
		_Dcomplex num;
		num._Val[0] = n1._Val[0] - n2._Val[0];
		num._Val[1] = n1._Val[1] - n2._Val[1];
	
		return num;
	}

	_Dcomplex div_complex (_Dcomplex n1, _Dcomplex n2)
    {
        _Dcomplex num;
        
		if (n2._Val[0] * n2._Val[0] + n2._Val[1] * n2._Val[1] == 0.0 || n2._Val[0] * n2._Val[0] + n2._Val[1] * n2._Val[1] == 0.0 ) 
		{
			num._Val[0] = NAN;
			num._Val[1] = NAN;

			return num;
		}
				
		num._Val[0] = (n1._Val[0] * n2._Val[0] + n1._Val[1] * n2._Val[1]) / (n2._Val[0] * n2._Val[0] + n2._Val[1] * n2._Val[1]);
        num._Val[1] = (n1._Val[1] * n2._Val[0] - n1._Val[0] * n2._Val[1]) / (n2._Val[0] * n2._Val[0] + n2._Val[1] * n2._Val[1]);
        
		return num;
	}

	_Dcomplex mult_complex (_Dcomplex n1, _Dcomplex n2)
	{
		_Dcomplex num;

		num._Val[0] = n1._Val[0] * n1._Val[1] - n2._Val[0] * n2._Val[1];
		num._Val[1] = n1._Val[0] * n2._Val[1] + n2._Val[0] * n1._Val[1];

		return num;
	}
#endif