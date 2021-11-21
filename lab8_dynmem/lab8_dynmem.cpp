#include <stdio.h>
#include <stdlib.h>

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

void InputArray(int *n, int **a) {
	FILE *f;
	fopen_s(&f, "text.txt", "rt");
	fscanf_s(f, "%d", n);
	*a = (int*)malloc(sizeof(int) * *n);
	for (int i = 0; i < *n; i++) {
		fscanf_s(f, "%d", &((*a)[i]));
	}
}

void OutputArray(int n, int **a) {
	for (int i = 0; i < n; i++) {
		printf("%d ", (*a)[i]);
	}
}

void UpdateArray(int *n, int **a) {
	int maxidx = FindMaxIdx(*n, *a);
	int minidx = FindMinIdx(*n, *a);
	int m = 0;

	if (maxidx > minidx) {
		int c = minidx+1;
		while (c != *n-1) {
			if ((*a)[c] % 2 != 0) {
				(*a)[c-m] = (*a)[c];
			} else {
				m++;
			}
			c++;
			if (c == maxidx) {
				(*a)[c-m] = (*a)[c];
				break;
			}
		}
        for (int i = maxidx+1; i < *n; i++) {
            (*a)[i-m] = (*a)[i];
        }
	} else {
        int c = maxidx+1;
        while (c != *n-1) {
            if ((*a)[c] % 2 != 0) {
                (*a)[c-m] = (*a)[c];
            } else {
                m++;
            }
            c++;
            if (c == minidx) {
                (*a)[c-m] = (*a)[c];
                break;
            }
        }
        for (int i = minidx+1; i < *n; i++) {
            (*a)[i-m] = (*a)[i];
        }
	}

	*n -= m;
}

int main() {
	int *arr;
	int n;

	InputArray(&n, &arr);
	UpdateArray(&n, &arr);
	OutputArray(n, &arr);

	free(arr);

	printf("\n");
	system("pause");
}
