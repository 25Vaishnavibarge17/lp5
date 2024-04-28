#include<iostream>
#include <omp.h>
#include <climits>
using namespace std;

void min_sequential(int arr[], int n) {
    int min_value = INT_MAX;
    
    for (int i = 0; i < n; i++) 
    {
        if (arr[i] < min_value) 
        {
            min_value = arr[i];
        }
    }
    cout << "Minimum value: " << min_value << endl;
}

void min_reduction(int arr[], int n) {
    int min_value = INT_MAX;
    #pragma omp parallel for reduction(min: min_value)
    for (int i = 0; i < n; i++) 
    {
        if (arr[i] < min_value) 
        {
            min_value = arr[i];
        }
    }
    cout << "Minimum value (parallel): " << min_value << endl;
}


void max_sequential(int arr[], int n) {
    int max_value = INT_MIN;

    for (int i = 0; i < n; i++) 
    {
        if (arr[i] > max_value) 
        {
            max_value = arr[i];
        }
    }
    cout << "Maximum value: " << max_value << endl;
}

void max_reduction(int arr[], int n) {
    int max_value = INT_MIN;
    
    #pragma omp parallel for reduction(max: max_value)
    for (int i = 0; i < n; i++) 
    {
        if (arr[i] > max_value) 
        {
            max_value = arr[i];
        }
    }
    cout << "Maximum value (parallel): " << max_value << endl;
}


void sum_sequential(int arr[], int n) {
    int sum = 0;

    for (int i = 0; i < n; i++) 
    {
        sum += arr[i];
    }
    cout << "Sum: " << sum << endl;
}

void sum_reduction(int arr[], int n) {
    int sum = 0;
    
    #pragma omp parallel for reduction(+: sum)
    for (int i = 0; i < n; i++) 
    {
        sum += arr[i];
    }
    cout << "Sum (parallel): " << sum << endl;
}


void average_sequential(int arr[], int n) {
    int sum = 0;
    
    #pragma omp parallel for reduction(+: sum)
    for (int i = 0; i < n; i++) 
    {
        sum += arr[i];
    }
    cout << "Average: " << (double)sum / n << endl;

}

void average_reduction(int arr[], int n) {
    int sum = 0;
    
    #pragma omp parallel for reduction(+: sum)
    for (int i = 0; i < n; i++) 
    {
        sum += arr[i];
    }
    cout << "Average (parallel): " << (double)sum / n << endl;

}


void printArray(int arr[], int n){
    
    for(int i = 0; i < n; i++) 
        cout << arr[i] << " ";
        
    cout << "\n";
}


int main() {
    int n;
    double start_time, end_time;

    cout<<"\n enter total no of elements :"<<" ";
    cin>>n;

    int arr[n];
    cout<<"\n enter elements : "<<endl;
    for(int i=0;i<n;i++)
    {
        cin>>arr[i];
    }
    
    start_time = omp_get_wtime();
    min_sequential(arr,n);
    end_time = omp_get_wtime(); 
    cout << "Sequential execution time ( min value ): " << end_time - start_time << " seconds.\n";
    
    start_time = omp_get_wtime();
    min_reduction(arr, n);
    end_time = omp_get_wtime(); 
    cout << "Parallel execution time ( min value ): " << end_time - start_time << " seconds.\n";

    start_time = omp_get_wtime();
    max_sequential(arr, n);
    end_time = omp_get_wtime();
    cout << "Sequential execution time ( max value ): " << end_time - start_time << " seconds.\n";

    start_time = omp_get_wtime();
    max_reduction(arr, n);
    end_time = omp_get_wtime();
    cout << "Prallel execution time ( max value ): " << end_time - start_time << " seconds.\n";
    
    start_time = omp_get_wtime();
    sum_sequential(arr, n);
    end_time = omp_get_wtime();
    cout << "Sequential execution time ( sum ): " << end_time - start_time << " seconds.\n";
    
    
    start_time = omp_get_wtime();
    sum_reduction(arr, n);
    end_time = omp_get_wtime();
    cout << "Parallel execution time ( sum ): " << end_time - start_time << " seconds.\n";
    
    start_time = omp_get_wtime();
    average_sequential(arr, n);
    end_time = omp_get_wtime();
    cout << "Sequential execution time ( average ): " << end_time - start_time << " seconds.\n";
    
    start_time = omp_get_wtime();
    average_reduction(arr, n);
    end_time = omp_get_wtime();
    cout << "Parallel execution time ( average ): " << end_time - start_time << " seconds.\n";
    
    cout<<endl;

 
}