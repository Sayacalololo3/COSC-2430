#include "ArgumentManager.h"
#include <fstream>
#include <map>
#include <vector>
#include <time.h>
#include <sstream>



template<typename T>
void display(vector<T> arr){
    for(auto i: arr){
        cout << i << " ";
    }
}
void bubbleSort(vector<int> &arr){
      bool swapped = true;
      while(swapped){
        swapped = false;
        for (int i = 0; i < arr.size()-1; i++) {
            if (arr[i]>arr[i+1] ){
                swap(arr[i],arr[i+1]);
                swapped = true;
            }
        }
    }
}
void selectionSort(vector<int> arr)  {  
  
    // One by one move boundary of unsorted subarray  
    for (int i = 0; i < arr.size() - 1; i++)  
    {  
        // Find the minimum element in unsorted array  
        int min = i;  
        for (int j = i+1; j < arr.size(); j++) {
            if (arr[j] < arr[min]){
             swap(arr[min], arr[i]);  
              min = j; 
            } 
        }  
            
    }  
}

void insertionSort(vector<int> arr){  
    for (int i = 1; i < arr.size(); i++) {  
        int key = arr[i];  
        int j = i - 1;  
        while (j >= 0 && arr[j] > key){  
            arr[j + 1] = arr[j];  
            j = j - 1;  
        }  
        arr[j + 1] = key;  
    }  
}

void merge(vector<int> arr, int size, int low, int middle, int high){
    int temp[size];
    for(int i = low; i <= high; i++){
        temp[i] = arr[i];
    }
    int i = low;
    int j = middle+1;
    int k = low;

    while (i <= middle && j <= high){
        if(temp[i] <= temp[j]){
            arr[k] = temp[i++];
            i++;
        }
        else {
            arr[k] = temp[j++];
            ++j;
        }
        k++;
    }
    while (i <= middle){
        arr[k++] = temp[i++];
    }
}

void mergeSort(vector<int> arr, int size, int low, int high){
    if (low < high){
        int middle = (low + high) / 2;
        mergeSort(arr, size, low, middle);
        mergeSort(arr, size, middle+1, high);
        merge(arr, size, low, middle, high);
    }
}

void quickSort(vector<int> arr, int left, int right){
    int i = left;
    int j = right;
    int mid = left + (right - left) / 2;
    int piv = arr[mid];

    while (i<right || j>left) {
        while (arr[i] < piv)
            i++;
        while (arr[j] > piv)
            j--;
        if (i <= j) {
            swap(arr[i++],arr[j--]);
        }
        else {
            if (i < right)
                quickSort(arr, i, right);
            if (j > left)
                quickSort(arr, left, j);
            return;
        }
    }
}
int main(int argc,char *argv[]){
    ArgumentManager am(argc,argv);
    ifstream ifs(am.get("input"));
    ofstream ofs(am.get("output"));
    map<int,string> order;
    clock_t time;
    stringstream ss;
    int size,num;
    ifs >> size;
    vector<int> arr;
    while(ifs >> num){
        arr.push_back(num);
    }
    vector<int> sorted(arr);

    time = clock();
    bubbleSort(sorted);
    order[clock() - time] = "Bubble Sort";sorted = arr;
    sorted = arr;

    time = clock();
    selectionSort(sorted);
    order[clock() - time] = "Selection Sort";
    sorted = arr;

    time = clock();
    insertionSort(sorted);
    order[clock() - time] = "Insertion Sort";
    sorted = arr;

    time = clock();
    mergeSort(sorted,arr.size(),0,arr.size() - 1);
    order[clock() - time] = "Merge Sort";
    sorted = arr;

    time = clock();
    quickSort(sorted,0,arr.size()-1);
    order[clock() - time] = "Quick Sort";


    for(auto i = order.begin(); i != order.end(); i++){
        ss << i->second << ", ";
    }
    string answer = ss.str();
    answer.pop_back();
    answer.pop_back();
    ofs << answer << endl;



}
