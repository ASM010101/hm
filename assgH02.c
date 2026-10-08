#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#define MAX 200000

int arr[MAX];        
int original[MAX];   
int n;               
long long comparisons; 

double getTime() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec / 1000000.0;
}

void resetArray() {
    for (int i = 0; i < n; i++) {
        arr[i] = original[i];
    }
}

void bubbleSort() {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            comparisons++;
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int mergeTemp[MAX];

void merge(int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right) {
        comparisons++;
        if (arr[i] <= arr[j]) {
            mergeTemp[k] = arr[i];
            i++;
        } else {
            mergeTemp[k] = arr[j];
            j++;
        }
        k++;
    }

    while (i <= mid) {
        mergeTemp[k] = arr[i];
        i++;
        k++;
    }

    while (j <= right) {
        mergeTemp[k] = arr[j];
        j++;
        k++;
    }

    for (i = left; i <= right; i++) {
        arr[i] = mergeTemp[i];
    }
}

void mergeSort(int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        mergeSort(left, mid);
        mergeSort(mid + 1, right);
        merge(left, mid, right);
    }
}

void quickSort(int left, int right) {
    if (left < right) {
        int randomIndex = left + rand() % (right - left + 1);
        int temp = arr[randomIndex];
        arr[randomIndex] = arr[right];
        arr[right] = temp;

        int pivot = arr[right];
        int i = left - 1;

        for (int j = left; j < right; j++) {
            comparisons++;
            if (arr[j] < pivot) {
                i++;
                int temp2 = arr[i];
                arr[i] = arr[j];
                arr[j] = temp2;
            }
        }

        int temp3 = arr[i + 1];
        arr[i + 1] = arr[right];
        arr[right] = temp3;

        int pivotPosition = i + 1;

        quickSort(left, pivotPosition - 1);
        quickSort(pivotPosition + 1, right);
    }
}

void quickSort3(int left, int right) {
    if (left < right) {
        if (right - left + 1 >= 3) {
            int idx1 = left + rand() % (right - left + 1);
            int idx2 = left + rand() % (right - left + 1);
            int idx3 = left + rand() % (right - left + 1);

            int medianIdx;
            comparisons++;
            if (arr[idx1] < arr[idx2]) {
                comparisons++;
                if (arr[idx2] < arr[idx3]) {
                    medianIdx = idx2;
                } else {
                    comparisons++;
                    if (arr[idx1] < arr[idx3]) {
                        medianIdx = idx3;
                    } else {
                        medianIdx = idx1;
                    }
                }
            } else {
                comparisons++;
                if (arr[idx1] < arr[idx3]) {
                    medianIdx = idx1;
                } else {
                    comparisons++;
                    if (arr[idx2] < arr[idx3]) {
                        medianIdx = idx3;
                    } else {
                        medianIdx = idx2;
                    }
                }
            }

            int temp = arr[medianIdx];
            arr[medianIdx] = arr[right];
            arr[right] = temp;
        } else {
            int randomIndex = left + rand() % (right - left + 1);
            int temp = arr[randomIndex];
            arr[randomIndex] = arr[right];
            arr[right] = temp;
        }

        int pivot = arr[right];
        int i = left - 1;

        for (int j = left; j < right; j++) {
            comparisons++;
            if (arr[j] < pivot) {
                i++;
                int temp2 = arr[i];
                arr[i] = arr[j];
                arr[j] = temp2;
            }
        }

        int temp3 = arr[i + 1];
        arr[i + 1] = arr[right];
        arr[right] = temp3;

        int pivotPosition = i + 1;

        quickSort3(left, pivotPosition - 1);
        quickSort3(pivotPosition + 1, right);
    }
}

int partitionSelect(int left, int right, int pivotIndex) {
    int pivotValue = arr[pivotIndex];
    int temp = arr[pivotIndex];
    arr[pivotIndex] = arr[right];
    arr[right] = temp;

    int i = left - 1;
    for (int j = left; j < right; j++) {
        comparisons++;
        if (arr[j] < pivotValue) {
            i++;
            int temp2 = arr[i];
            arr[i] = arr[j];
            arr[j] = temp2;
        }
    }
    int temp3 = arr[i + 1];
    arr[i + 1] = arr[right];
    arr[right] = temp3;
    return i + 1;
}

int quickSelect(int left, int right, int k) {
    if (left == right) {
        return left;
    }
    int randomIndex = left + rand() % (right - left + 1);
    int pivotPosition = partitionSelect(left, right, randomIndex);

    if (k == pivotPosition) {
        return pivotPosition;
    } else if (k < pivotPosition) {
        return quickSelect(left, pivotPosition - 1, k);
    } else {
        return quickSelect(pivotPosition + 1, right, k);
    }
}

void quickSortM(int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        quickSelect(left, right, mid);
        quickSortM(left, mid - 1);
        quickSortM(mid + 1, right);
    }
}

int main(int argc, char *argv[]) {

    n = atoi(argv[1]);    
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        original[i] = rand();
    }

    double startTime, endTime;

    resetArray();
    comparisons = 0;
    startTime = getTime();
    bubbleSort();
    endTime = getTime();
    printf("%lld %.6f ", comparisons, endTime - startTime);

    resetArray();
    comparisons = 0;
    startTime = getTime();
    mergeSort(0, n - 1);
    endTime = getTime();
    printf("%lld %.6f ", comparisons, endTime - startTime);

    resetArray();
    comparisons = 0;
    startTime = getTime();
    quickSort(0, n - 1);
    endTime = getTime();
    printf("%lld %.6f ", comparisons, endTime - startTime);

    resetArray();
    comparisons = 0;
    startTime = getTime();
    quickSort3(0, n - 1);
    endTime = getTime();
    printf("%lld %.6f ", comparisons, endTime - startTime);

    resetArray();
    comparisons = 0;
    startTime = getTime();
    quickSortM(0, n - 1);
    endTime = getTime();
    printf("%lld %.6f ", comparisons, endTime - startTime);

    printf("\n");
    return 0;
}