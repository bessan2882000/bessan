#include <stdio.h>

#include<iostream>

#include <sys/time.h>





double get_time()

{

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



void mergeSort(int arr[], int left, int right) {

    if (left < right) {

        int mid = (left + right) / 2;

        mergeSort(arr, left, mid);

        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);

    }

}



int main() {

    std::cout<<"Enter array size"<<std::endl;

    int n;

    std::cin>>n;

    int arr[n];



    for(int i=0;i<n;i++){

        arr[i]= rand() % 1000;

    }

    int size = 7;



    printf("Before sorting: ");

    for (int i = 0; i < size; i++)

        printf("%d ", arr[i]);

    printf("\n");



     double start_seq = get_time();

     mergeSort(arr, 0, size - 1);

    double end_seq = get_time();

    double duration_seq = end_seq - start_seq;

    std::cout << "Sequential time: " << duration_seq << " s" << std::endl;

    



    printf("After sorting: ");

    for (int i = 0; i < size; i++)

        printf("%d ", arr[i]);

    printf("\n");





}