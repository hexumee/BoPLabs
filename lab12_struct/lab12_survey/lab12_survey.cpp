#include <stdio.h>
#include <conio.h>
#include <locale>
#include <windows.h>

#pragma warning(disable: 4996)

struct objF {
	int x;
	int y;
	char text[256];
	int r;
	int g;
	int b;
	int size;
};

int main() {
	setlocale(LC_ALL, "rus");
	SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
	objF o1;
	int n = 0;
	FILE *f;
	fopen_s(&f, "C:\\Users\\hexumee\\Desktop\\osnprog_labs\\lab12_struct\\s.bin", "wb");
	printf("Количество фигур: ");
	scanf_s("%d", &n);
	fwrite(&n, sizeof(int), 1, f);

	for (int i = 0; i < n; i++) {
		printf("Фигура №%d\n", i+1);
		printf("- Координата X: ");
		scanf_s("%d", &o1.x);
		printf("- Координата Y: ");
		scanf_s("%d", &o1.y);
		printf("- Текст: ");
		char buf[256], c;
		scanf("%s", &buf);
		int sl = strlen(buf);
		do {
			scanf("%c", &c);
			buf[sl++] = c;
		} while (c != '\n'); 
		buf[sl-1] = 0;
		strcpy(o1.text, buf);
		printf("- Цвет (красный канал) [0-255]: ");
		scanf_s("%d", &o1.r);
		printf("- Цвет (зеленый канал) [0-255]: ");
		scanf_s("%d", &o1.g);
		printf("- Цвет (синий канал) [0-255]: ");
		scanf_s("%d", &o1.b);
		printf("- Размер шрифта: ");
		scanf_s("%d", &o1.size);
		fwrite(&o1, sizeof(objF), 1, f);
	}

	fclose(f);
	return 0;
}