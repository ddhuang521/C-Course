#include <iostream>
using namespace std;

const int arrSize = 4; 

int sumOfSquares(int arr[], int arrSize);
bool isSorted(int arr[], int arrSize);

int main() {
	
	int arr[arrSize] = {2, -1, 3, 10};
	cout<<sumOfSquares(arr, arrSize)<<endl;
	
	cout<<endl;
	
	int arrSorted[arrSize] = {1, 2, 3, 4};
	int arrunSorted[arrSize] = {3, 4, 4, 3};
	cout<<isSorted(arrSorted, arrSize)<<endl;
	cout<<isSorted(arrunSorted, arrSize)<<endl;
	
	return 0;
	
}



int sumOfSquares(int arr[], int arrSize) {
	
	if (arrSize == 1) {
		
		return arr[0] * arr[0];
		
	}
	
	else {
				
		return arr[0] * arr[0] + sumOfSquares(arr + 1, arrSize - 1);
		
	}
	
	
}




bool isSorted(int arr[], int arrSize) {
	
	if (arrSize == 1) { // array with only one number
		
		return false;
	}
		
	else if (arrSize == 2) { // base case: array with two numbers
		
		if (arr[0] >= arr[1]) {
			
			return false;
			
		}
					
		return true;
		
	}
	
	else { //induction case
		
		if (arr[0] >= arr[1]) {
			
			return false; 
			
		}
				
		return isSorted(arr + 1, arrSize - 1);
		
	}
		
}
