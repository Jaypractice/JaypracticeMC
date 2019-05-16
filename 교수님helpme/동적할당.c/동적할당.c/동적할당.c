#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

void swap(int* a, int* b) { int t = *b; *b = *a, *a = t; }
void sort(int *arr, int size) {
	for (int i = size - 1; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			if (arr[j] > arr[j + 1]) {
				swap(arr + j, arr + j + 1);
			}
		}
	}
}
int Max(int *arr, int size) {
	return arr[size - 1];
}
int Min(int *arr) {
	return *arr;
}
float Mean(int* arr, int size) {
	float s = 0;
	for (int i = 0; i < size; i++) {
		s += arr[i];
	}
	return (float)s / size;
}
int main()
{
	printf("N? ");
	int size;
	scanf("%d", &size);
	int* arr = malloc(size * sizeof(int));
	for (int i = 0; i < size; i++) {
		scanf("%d", arr + i);
	}
	sort(arr, size);
	int max = Max(arr, size);
	int min = Min(arr);
	float mean = Mean(arr, size);
	printf("최대값: %d\n", max);
	printf("최소값: %d\n", min);
	printf("평균값: %f\n", mean);

	free(arr);

	return 0;
}