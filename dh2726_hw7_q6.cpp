#include <iostream>
using namespace std;

const int size = 10;

int binarySearch(int arr[], int arrSize, int val);

int main() {
	
	int arr[size] = {1,4,7,10,13,16,19,22,25,28};
	
	cout<<binarySearch(arr, size, 7)<<endl;
	cout<<binarySearch(arr, size, 17)<<endl;
	
	
}

int binarySearch(int arr[], int arrSize, int val) {
	
	int low = 0;
	int high = arrSize - 1; 
	int mid;
	
	while (low <= high) {
		
		mid = (low + high) / 2;
		
		if (val == arr[mid]) {
			
			return mid;
			
		}
		
		else if (val < arr[mid]) {
			
			high = mid - 1;
			
		}
		
		else {
			
			low = mid + 1;
			
		}
				
	}
	
	return -1; 
	
}
