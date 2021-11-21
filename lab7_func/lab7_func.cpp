#include <stdio.h>
#include <locale>

int FindMin(int n, int *a) {
	int min = a[0];

	for (int i = 0; i < n; i++) {
		if (a[i] < min) {
			min = a[i];
		}
	}

	return min;
}

int FindMax(int n, int *a) {
	int max = a[0];

	for (int i = 0; i < n; i++) {
		if (a[i] > max) {
			max = a[i];
		}
	}

	return max;
}

int FindMinIdx(int n, int *a) {
	int min = a[0];
	int minidx = 0;

	for (int i = 0; i < n; i++) {
		if (a[i] < min) {
			min = a[i];
			minidx = i;
		}
	}

	return minidx;
}

int FindMaxIdx(int n, int *a) {
	int max = a[0];
	int maxidx = 0;

	for (int i = 0; i < n; i++) {
		if (a[i] > max) {
			max = a[i];
			maxidx = i;
		}
	}

	return maxidx;
}

void InputArray(int *n, int *a) {
	printf("Количество элементов: ");
	scanf_s("%d", n);
	printf("Элементы: ");
	for (int i = 0; i < *n; i++) {
		scanf_s("%d", &a[i]);
	}
}

void OutputArray(int n, int *a) {
	for (int i = 0; i < n; i++) {
		printf("%d ", a[i]);
	}
}

void UpdateArray(int *n, int *a) {
	int maxidx = FindMaxIdx(*n, a);
	int minidx = FindMinIdx(*n, a);
	int m = 0;

	if (maxidx > minidx) {
		int c = minidx+1;
		while (c != *n-1) {
			if (a[c] % 2 != 0) {
				a[c-m] = a[c];
			} else {
				m++;
			}
			c++;
			if (c == maxidx) {
				a[c-m] = a[c];
				break;
			}
		}
        for (int i = maxidx+1; i < *n; i++) {
            a[i-m] = a[i];
        }
	} else {
        int c = maxidx+1;
        while (c != *n-1) {
            if (a[c] % 2 != 0) {
                a[c-m] = a[c];
            } else {
                m++;
            }
            c++;
            if (c == minidx) {
                a[c-m] = a[c];
                break;
            }
        }
        for (int i = minidx+1; i < *n; i++) {
            a[i-m] = a[i];
        }
	}

	*n -= m;
}

int main() {
	setlocale(LC_ALL, "rus");
	int a[10];
	int n;

	InputArray(&n, a);
	UpdateArray(&n, a);
	OutputArray(n, a);

	printf("\n");
	system("pause");
}
