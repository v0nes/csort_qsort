#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
int compare(const void* a,
    const void* b) {
    return (*(int*)a - *(int*)b);
}
int swaping(int* arr, int low, int high) {
    int i, j, num_buffer;
    i = low;
    j = high;
    int pivot = arr[(i + j) / 2];
    while (1) {
        while ((arr[i]) < pivot) {
            i++;
        }
        while ((arr[j]) > pivot) {
            j--;
        }
        if (i >= j) {
            return j;
            break;
        }
        num_buffer = *(arr + j);
        *(arr + j) = *(arr + i);
        *(arr + i) = num_buffer;
        i++;
        j--;
    }
}
int quick_sort(int* arr, int lo, int hi) {
    if (lo >= 0 && hi >= 0 && lo < hi) {
        int p = swaping(arr, lo, hi);
        quick_sort(arr, lo, p);
        quick_sort(arr, ++p, hi);

    }
}
int counting_sort(int* arr, int length) {
    clock_t begin_counting = clock();
    int max = arr[0];
    int min = arr[0];
    int i;
    for (i = 1; i < length; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
        if (arr[i] < min) {
            min = arr[i];
        }
    }

    max++;
    FILE* Sortfile;

    if ((Sortfile = fopen("Counting_sort.txt", "w")) == NULL) {
        printf("Cannot open file.\n");
        exit(1);
    }
    int* tnuoc = (int*)malloc(sizeof(int));
    if (min < 0) {
        int r = 0;
        min = -min++;
        for (i = 0; i < min; i++) {
            r++;
            tnuoc = (char*)realloc(tnuoc, (r) * sizeof(int));
            tnuoc[i] = 0;
        }
        for (i = 0; i < length; i++) {
            if (arr[i] < 0) {
                tnuoc[-arr[i]]++;
            }
        }
    }

    int* count = (int*)malloc((max) * sizeof(int));
    for (i = 0; i < max; i++) {
        count[i] = 0;
    }
    for (i = 0; i < length; i++) {
        if (arr[i] >= 0) {
            count[arr[i]]++;
        }
    }
    clock_t finish_counting = clock();
    for (i = min; i > 0; i = i - 1) {
        if (tnuoc[i] != 0) {
            for (int j = 0; j < tnuoc[i]; j++) {
                fprintf(Sortfile, "%d\n", -i);
            }
        }
    }
    for (i = 0; i < max; i++) {
        if (count[i] != 0) {
            for (int j = 0; j < count[i]; j++) {
                fprintf(Sortfile, "%i\n", i);
            }
        }
    }
    clock_t counting_time = finish_counting - begin_counting;
    return(counting_time);
}
int main(void) {
    int length = 0, n = 0;
    int i = 0;
    char* number = (char*)malloc((n + 1) * sizeof(char));
    int* arr = (int*)malloc((length + 1) * sizeof(int));
    int support;
    FILE* file;
    FILE* quick_sort_file;

    if ((file = fopen("numbers.txt", "r")) == NULL) {
        printf("Cannot open file.\n");
        exit(1);
    }
    char buffer = getc(file);
    while (buffer != EOF) {
        if (buffer != '\n') {
            n++;
            number = (char*)realloc(number, (n) * sizeof(char));
            *(number + n - 1) = buffer;
        }
        else {
            n++;
            number = (char*)realloc(number, (n) * sizeof(char));
            *(number + n - 1) = '\0';
            length++;
            arr = (int*)realloc(arr, (length) * sizeof(int));
            sscanf(number, "%d", (arr + length - 1));
            n = 0;
            number = (char*)realloc(number, (n + 1) * sizeof(char));
        }
        buffer = getc(file);
    }

    printf("\ncounting sort starts");

    clock_t counting_time = counting_sort(arr, length);

    printf("\ncounting sort ends");



    printf("\nquick sort starts");
    clock_t begin_quick = clock();
    quick_sort(arr, 0, (length - 1));
    clock_t finish_quick = clock();
    printf("\nquick sort ends");


    if ((quick_sort_file = fopen("Quick_sort.txt", "w")) == NULL) {
        printf("Cannot open file.\n");
        exit(1);
    }
    for (i = 0; i < length; i++) {
        fprintf(quick_sort_file, "%d\n", *(arr + i));
    }
    double time_spent_counting = (double)(counting_time) / CLOCKS_PER_SEC;
    double time_spent_quick = (double)(finish_quick - begin_quick) / CLOCKS_PER_SEC;
    printf("\n\nquick sort time :%lf", time_spent_quick);
    printf("\ncounting sort time :%lf", time_spent_counting);
    printf("\nnumbers sorted: %d", length);
}