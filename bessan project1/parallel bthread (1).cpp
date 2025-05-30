#include <iostream>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

double get_time()
{
    timeval tv;
    gettimeofday(&tv, nullptr);
    return tv.tv_sec + tv.tv_usec * 1e-6;
}

struct Args {
    int* arr;
    int left;
    int right;
};

int threadCount = 1;
int maxThreads = 2;
pthread_mutex_t lock;

void merge(int* arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    delete[] L;
    delete[] R;
}

void* mergeSort(void* arg) {
    Args* args = (Args*)arg;
    int left = args->left;
    int right = args->right;
    int* arr = args->arr;

    if (left < right) {
        int mid = (left + right) / 2;

        pthread_t t1, t2;
        Args leftArgs = { arr, left, mid };
        Args rightArgs = { arr, mid + 1, right };

        bool spawnLeft = false, spawnRight = false;

        pthread_mutex_lock(&lock);
        if (threadCount < maxThreads) {
            threadCount++;
            spawnLeft = true;
        }
        pthread_mutex_unlock(&lock);

        if (spawnLeft) {
            pthread_create(&t1, NULL, mergeSort, &leftArgs);
        } else {
            mergeSort(&leftArgs);
        }

        pthread_mutex_lock(&lock);
        if (threadCount < maxThreads) {
            threadCount++;
            spawnRight = true;
        }
        pthread_mutex_unlock(&lock);

        if (spawnRight) {
            pthread_create(&t2, NULL, mergeSort, &rightArgs);
        } else {
            mergeSort(&rightArgs);
        }

        if (spawnLeft) pthread_join(t1, NULL);
        if (spawnRight) pthread_join(t2, NULL);

        merge(arr, left, mid, right);
    }

    pthread_mutex_lock(&lock);
    threadCount--;
    pthread_mutex_unlock(&lock);

    return NULL;
}

int main() {
    int n;
    std::cout << "Enter array size: ";
    std::cin >> n;

    int* arr = new int[n];
    for (int i = 0; i < n; i++)
        arr[i] = rand() % 1000;

    std::cout << "Enter max number of threads: ";
    std::cin >> maxThreads;
    if (maxThreads < 1) maxThreads = 1;

    pthread_mutex_init(&lock, NULL);

    std::cout << "Before sorting: ";
    for (int i = 0; i < n; i++)
        std::cout << arr[i] << " ";
    std::cout << "\n";

    Args mainArgs = { arr, 0, n - 1 };

    double start_seq = get_time();
    mergeSort(&mainArgs);
    double end_seq = get_time();
    double duration_seq = end_seq - start_seq;
    std::cout << "Parallel time: " << duration_seq << " s" << std::endl;

    std::cout << "After sorting: ";
    for (int i = 0; i < n; i++)
        std::cout << arr[i] << " ";
    std::cout << "\n";

    pthread_mutex_destroy(&lock);
    delete[] arr;
}