#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

void merge(vector<int> &arr, int low, int mid, int high) {
    vector<int> temp; // temporary array
    int left = low;      // starting index of left half of arr
    int right = mid + 1;   // starting index of right half of arr

    //storing elements in the temporary array in a sorted manner//

    while (left <= mid && right <= high) {
        if (arr[left] <= arr[right]) {
            temp.push_back(arr[left]);
            left++;
        }
        else {
            temp.push_back(arr[right]);
            right++;
        }
    }
    // if elements on the left half are still left //
    while (left <= mid) {
        temp.push_back(arr[left]);
        left++;
    }
    //  if elements on the right half are still left //
    while (right <= high) {
        temp.push_back(arr[right]);
        right++;
    }
    // transfering all elements from temporary to arr //
    for (int i = low; i <= high; i++) {
        arr[i] = temp[i - low];
    }
}

void mergeSortSequential(vector<int> &arr, int low, int high) {
    if (low >= high) return;
    int mid = (low + high) / 2 ;
    mergeSortSequential(arr, low, mid);  // left half
    mergeSortSequential(arr, mid + 1, high); // right half
    merge(arr, low, mid, high);  // merging sorted halves
}

void mergeSortParallel(vector<int> &arr, int low, int high) {
    if (low >= high) return;
    int mid = (low + high) / 2 ;
    #pragma omp parallel sections
    {
        #pragma omp section
        mergeSortParallel(arr, low, mid);  // left half
        #pragma omp section
        mergeSortParallel(arr, mid + 1, high); // right half
    }
    merge(arr, low, mid, high);  // merging sorted halves
}

int main() {

    vector<int> arr ;
    int n = 10;
    double start_time, end_time;
    // Create an array with numbers starting from n to 1.
    for(int i = 0, j = n; i < n; i++, j--) 
        arr.push_back(j) ;
    

    cout << "Before Sorting Array: " << endl;
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " "  ;
    }
    cout << endl;
    
    
    // Sequential merge sort
    start_time = omp_get_wtime(); 
    mergeSortSequential(arr, 0, n - 1);
    end_time = omp_get_wtime(); 
    cout << "After Sorting Array Sequentially: " << endl;
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " "  ;
    }
    cout << endl;
    
    cout << "Time taken by sequential algorithm: " << end_time - start_time << " seconds\n";
    
    // Reset array
    for(int i = 0, j = n; i < n; i++, j--) 
        arr.push_back(j) ;
    
    // Parallel merge sort
    start_time = omp_get_wtime(); 
    mergeSortParallel(arr, 0, n - 1);
    end_time = omp_get_wtime(); 
    cout << "After Sorting Array in Parallel: " << endl;
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " "  ;
    }
    cout << endl;
    cout << "Time taken by parallel algorithm: " << end_time - start_time << " seconds\n";

    return 0 ;
}