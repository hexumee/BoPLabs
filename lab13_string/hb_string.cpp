#include <stdio.h>
#include "hb_string.h"

#pragma warning(disable: 4996)

unsigned int _strlen(char *s) {
	int i = 0;

	while (s[i] != '\0')
		i++;

	return i;
}

void _strcpy(char *src, char *dst) {
	for (unsigned int i = 0; i <= _strlen(src); i++)
		dst[i] = src[i];
}

void _strcat(char *src, char *dst) {
	int s_size = _strlen(dst);
	int r_size = _strlen(src)+_strlen(dst);

	for (unsigned int i = s_size; i <= r_size; i++)
		dst[i] = src[i-s_size];
}

int _strcmp(char *s1, char *s2) {
	for (int i = 0; ; i++) {
        if (s1[i] != s2[i])
			return s1[i]-s2[i];

        if (s1[i] == '\0')
            return 0;
    }
}

char* _strchr(char *s, char c) {
	for (; *s != '\0'; s++)
		if (*s == c)
			return (char*)s;

	return NULL;
}

char* _strstr(char *s, char *ss) {
	char *temp, *c;
	temp = ss;

	while (*s) {
		c = s;
		while(*(s++) == *(ss++)) {
			if (!(*ss))
				return (char*)c;

			if(!(*s))
				return NULL;
		}
		ss = temp;
	}

	return NULL;
}

void full_scanf(char &dst) {
	char c;

	scanf("%s", &dst);
	int sl = _strlen(&dst);

	do {
		scanf("%c", &c);
		(&dst)[sl++] = c;
	} while (c != '\n'); 

	(&dst)[sl-1] = 0;
}
