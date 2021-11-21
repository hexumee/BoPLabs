#include <stdio.h>
#include <locale>

int main() {
    setlocale(LC_ALL, "rus");

    int n = 0;
    printf("Количество элементов: ");
    scanf_s("%d", &n);
    int a[10];
    printf("Элементы: ");
    for (int i = 0; i < n; i++) {
        int t;
        scanf_s("%d", &t);
        a[i] = t;
    }

    int min = a[0], max = a[0], minidx = 0, maxidx = 0, m = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] > max) {
            max = a[i];
            maxidx = i;
        }
        if (a[i] < min) {
            min = a[i];
            minidx = i;
        }
    }

    if (maxidx > minidx) {
        int c = minidx+1;
        while (c != n-1) {
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
        for (int i = maxidx+1; i < n; i++) {
            a[i-m] = a[i];
        }
    } else {
        int c = maxidx+1;
        while (c != n-1) {
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
        for (int i = minidx+1; i < n; i++) {
            a[i-m] = a[i];
        }
    }

    for (int i = 0; i < n-m; i++) {
        printf("%d ", a[i]);
    }

    printf("\n");
    system("pause");

    return 0;
}
