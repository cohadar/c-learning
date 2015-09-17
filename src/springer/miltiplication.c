#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "asrt.h"

struct Big {
	size_t length;
	char *digits;
};


// TODO: handle len == 0
struct Big *
Big_junk(size_t len)
{
	struct Big *junk = malloc(sizeof(*junk));
	if (junk == NULL) goto nomem_junk;
	junk->length = len;
	junk->digits = malloc(len);
	if (junk->digits == NULL) goto nomem_digits;
	return junk;
nomem_digits:
	free(junk);
nomem_junk:
	return NULL;
}

void
Big_free(struct Big *big)
{
	free(big->digits);
	big->digits = NULL;
	big->length = 0;
	free(big);
}

struct Big *
Big_from_strz(char *strz)
{
	// TODO: handle len == 0 && strz == NULL
	size_t len = strlen(strz);
	struct Big *big = Big_junk(len);
	if (big == NULL) goto nomem_big;
	// we do not copy terminating zero
	for (int i = 0; i < big->length; i++) {
		big->digits[i] = strz[i] - '0';
	}
	return big;
nomem_big:
	return NULL;
}

char *
Big_to_strz(struct Big *big)
{
	char *strz = malloc(big->length + 1);
	if (strz == NULL) goto nomem_strz;
	for (int i = 0; i < big->length; i++) {
		strz[i] = big->digits[i] + '0';
	}
	strz[big->length] = '\0';
	return strz;
nomem_strz:
	return NULL;
}

void
add_digits(char a, char b, char c, char *d, char *e)
{
	char sum = a + b + c;
	*d = sum / 10;
	*e = sum % 10;
}

struct Big *
add2(struct Big *a, struct Big *b)
{
	size_t len_c = (a->length >= b->length) ? a->length : b->length;
	// adition can create overflow digit
	len_c++;
	struct Big *c = Big_junk(len_c);
	if (c == NULL) goto nomem_c;
	return c;
nomem_c:
	return NULL;
}

void
test_add_digits()
{
	for (char a = 0; a < 10; a++) {
		for (char b = 0; b < 10; b++) {
			for (char c = 0; c < 10; c++) {
				char d = 0;
				char e = 0;
				add_digits(a, b, c, &d, &e);
				ASRT_char((a + b + c) / 10, d);
				ASRT_char((a + b + c) % 10, e);
			}
		}
	}
}

void
test_to_from_strz()
{
	char *strz = "1234567890";
	struct Big *big = Big_from_strz(strz);
	ASRT_true(big);
	char *strz2 = Big_to_strz(big);
	ASRT_true(strz2);
	ASRT_strz(strz, strz2);
	Big_free(big);
	free(strz2);
}

int
main(int argc, char const *argv[])
{
	test_add_digits();
	test_to_from_strz();
	printf("All OK.\n");
	return 0;
}
