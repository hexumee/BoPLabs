#include <stdio.h>
#include <conio.h>
#include <locale>

#pragma warning(disable: 4996)

void SliCat(char *s, char *buff) {
	char slices[32][256];
	char slice[256];
	int li = 0;
	int si = 0;
	int bi = 0;
	char bu[256];

	while (true) {
		if (s[li] == ' ' || s[li] == '\n' || s[li] == '\0') {
			bu[bi] = 0;
			strcpy(slices[si], bu);
			si++;
			if (s[li] == '\n' || s[li] == '\0')
				break;
			slice[0] = 0;
			bu[0] = 0;
			bi = 0;
			li++;
		}
		bu[bi] = s[li];
		bi++;
		li++;
	}

	for (int i = 0; i < si; i++) {
		bool ap = false;
		for (int j = 0; j < strlen(slices[i]); j++) {
			if (slices[i][j] == 'A' || slices[i][j] == 'a') {
				ap = true;
				break;
			}
		}
		
		if (ap)
			strcat(buff, "<i><b>NOP</b></i>");
		else
			strcat(buff, slices[i]);

		if (i != si-1)
			strcat(buff, " ");
	}
}

int main() {
	FILE *fin;
	FILE *fout;
	char str[256];
	char fl[256];

	fopen_s(&fin, "C:\\Users\\hexumee\\Desktop\\osnprog_labs\\lab11_text\\text.txt", "rt");
	fopen_s(&fout, "C:\\Users\\hexumee\\Desktop\\osnprog_labs\\lab11_text\\index.html", "wt");

	fgets(fl, 256, fin);
	fprintf(fout, "<HTML>\n<HEAD>\n<TITLE>%s</TITLE>\n</HEAD>\n<BODY>\n<H1>%s</H1>\n", fl, fl);

	while (!feof(fin)) {
		fgets(str, 256, fin);
		char fbuf[256] = {'\0'};
		SliCat(str, fbuf);
		fprintf(fout, fbuf);
		fprintf(fout, "<BR>\n");
		str[0] = 0;
	}

	fprintf(fout, "</BODY>\n</HTML>\n");

	fclose(fin);
	fclose(fout);
}
