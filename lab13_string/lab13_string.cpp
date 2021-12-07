#include <stdio.h>
#include "hb_string.h"
#include <locale.h>
#include <windows.h>

#pragma warning(disable: 4996)

void test_strlen() {
	char s[128];
	printf("Тест strlen(): ");
	full_scanf(*s);
	printf("Длина строки: %d\n\n", _strlen(s));
}

void test_strcpy() {
	char s[128], s1[128];
	printf("Тест strcpy(): ");
	full_scanf(*s);
	_strcpy(s, s1);
	printf("Результат: %s\n\n", s1);
}

void test_strcat() {
	char s[256], s1[128];
	printf("Тест strcat() - нужно ввести две строки:\n");
	full_scanf(*s);
	full_scanf(*s1);
	_strcat(s1, s);
	printf("Результат: %s\n\n", s);
}

void test_strcmp() {
	char s[256], s1[128];
	printf("Тест strcmp() - нужно ввести две строки:\n");
	full_scanf(*s);
	full_scanf(*s1);
	printf("Результат: %d\n\n", _strcmp(s, s1));
}

void test_strchr() {
	char s[256], c;
	printf("Тест strchr() - нужно ввести строку и символ:\n");
	full_scanf(*s);
	scanf_s("%c", &c);
	printf("Результат: %d\n\n", _strchr(s, c));
}

void test_strstr() {
	char s[256], s1[128];
	printf("Тест strstr() - нужно ввести две строки:\n");
	full_scanf(*s);
	full_scanf(*s1);
	printf("Результат: %d\n\n", _strstr(s, s1));
}

int main() {
	setlocale(LC_ALL, "rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	test_strlen();
	test_strcpy();
	test_strcat();
	test_strcmp();
	test_strchr();
	test_strstr();
}
