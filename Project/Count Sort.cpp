#include <bits/stdc++.h>
#include <chrono>
#include <pthread.h>

using namespace std;
using namespace chrono;

const int SIZE = 1e7, MX = 1e4, NUM_THREADS = 4;

int arr[SIZE];
int countParallel[NUM_THREADS][MX], countSequential[MX];
int sortedParallel[SIZE], sortedSequential[SIZE];

void init() {
    srand(time(NULL));
    for (int &i: arr) {
        i = (rand() % MX);
    }
}

void *countsort_thread(void *arg) {
    int thread_id = *((int *) arg);

    for (int i = thread_id; i < SIZE; i += NUM_THREADS) {
        countParallel[thread_id][arr[i]]++;
    }

    pthread_exit(NULL);
}

void CountSortParallel() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; ++i) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, countsort_thread, (void *) &thread_ids[i]);
    }

    for (auto thread: threads) {
        pthread_join(thread, NULL);
    }

    for (int i = 1; i < NUM_THREADS; ++i) {
        for (int j = 0; j < MX; ++j) {
            countParallel[0][j] += countParallel[i][j];
        }
    }

    for (int i = 1; i < MX; ++i) {
        countParallel[0][i] += countParallel[0][i - 1];
    }

    for (int i = SIZE - 1; i >= 0; --i) {
        sortedParallel[--countParallel[0][arr[i]]] = arr[i];
    }
}

void CountSortSequential() {
    for (auto num: arr) {
        countSequential[num]++;
    }

    for (int i = 1; i < MX; ++i) {
        countSequential[i] += countSequential[i - 1];
    }

    for (auto num: arr) {
        sortedSequential[--countSequential[num]] = num;
    }
}

int main() {
    init();

    auto start_time = high_resolution_clock::now();
    CountSortParallel();
    auto end_time = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(end_time - start_time);

    cout << "Does the parallel sorted array is sorted? "
         << (is_sorted(sortedParallel, sortedParallel + SIZE) ? "True" : "False")
         << "\n";

    cout << "Parallel Time: " << fixed << setprecision(7) << (double) duration.count() / 1000000.0 << " seconds";

    cout << "\n\n===========================================\n\n";

    start_time = high_resolution_clock::now();
    CountSortSequential();
    end_time = high_resolution_clock::now();

    duration = duration_cast<microseconds>(end_time - start_time);

    cout << "Does the sequential sorted array is sorted? "
         << (is_sorted(sortedSequential, sortedSequential + SIZE) ? "True" : "False")
         << "\n";

    cout << "Sequential Time: " << fixed << setprecision(7) << (double) duration.count() / 1000000.0 << " seconds";

    return 0;
}
