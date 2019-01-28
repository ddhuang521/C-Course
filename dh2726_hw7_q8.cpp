#include <iostream>
using namespace std;

const int size = 10;

void insertionSort(int a[], int aSize);
void swap(int a[], int m, int n);

int main() {
	
	int arr[size] = {8,6,10,2,16,4,18,14,12,10};
		
	insertionSort(arr, size);
	
	for (int i = 0; i < size; i++) {
		
		cout<<arr[i]<<" ";
		
	}
	
	cout<<endl;
	
	return 0;
	
}



void insertionSort(int a[], int aSize) {
	
	int j;
	
	for (int i = 1; i < aSize; i++) {
		
		j = i;
		
		while (j != 0 && a[j] < a[j - 1]) {
			
			swap(a, j, j - 1); 
			j = j - 1; 
			
		}
			
	}
	
	
	
}

void swap(int a[], int m, int n) {
	
	int temp;
	
	temp = a[m];
	a[m] = a[n];
	a[n] = temp;

}