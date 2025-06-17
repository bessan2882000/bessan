#include <stdio.h>
#include <iostream>
#include <sys/time.h>
#include <omp.h>

double get_time() {
    timeval tv;
    gettimeofday(&tv, nullptr);
    return tv.tv_sec + tv.tv_usec * 1e-6;
}

void merge(int arr[], int left, int mid, int right) {
    int i = left, j = mid + 1, k = 0;
    int temp[100];
    while (i <= mid && j <= right) {
        if (arr[i] < arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }
    while (i <= mid)
        temp[k++] = arr[i++];
    while (j <= right)
        temp[k++] = arr[j++];
    for (i = left, k = 0; i <= right; i++, k++)
        arr[i] = temp[k];
}

void mergeSortParallel(int arr[], int left, int right, int depth = 0) {
    if (left < right) {
        int mid = (left + right) / 2;
        if (depth < 4) {
            #pragma omp task firstprivate(arr, left, mid, depth)
            mergeSortParallel(arr, left, mid, depth + 1);
            #pragma omp task firstprivate(arr, mid, right, depth)
            mergeSortParallel(arr, mid + 1, right, depth + 1);
            #pragma omp taskwait
        } else {
            mergeSortParallel(arr, left, mid, depth + 1);
            mergeSortParallel(arr, mid + 1, right, depth + 1);
        }
        merge(arr, left, mid, right);
    }
}

int main() {
    int n;
    std::cin >> n;
    int arr[n], arr_copy[n];
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000;
        arr_copy[i] = arr[i];
    }

    double start_seq = get_time();
    mergeSortParallel(arr, 0, n - 1);
    double end_seq = get_time();
    std::cout << "Sequential-like time: " << end_seq - start_seq << " s\n";

    double start_par = get_time();
    #pragma omp parallel
    {
        #pragma omp single
        mergeSortParallel(arr_copy, 0, n - 1);
    }
    double end_par = get_time();
    std::cout << "Parallel time with OpenMP: " << end_par - start_par << " s\n";

    return 0;
}
