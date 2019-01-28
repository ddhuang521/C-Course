#include <iostream>
using namespace std;

const int size = 8;
int findChange(int arr01[], int arr01Size);

int main() {
	
	int arr01[size] = {0,0,0,0,0,1,1,1};
	int arr02[size] = {0,1,1,1,1,1,1,1};
	int arr03[size] = {0,0,0,0,0,0,0,1};

	cout<<findChange(arr01, size)<<endl;
	cout<<findChange(arr02, size)<<endl;
	cout<<findChange(arr03, size)<<endl;

	return 0;
	
}


int findChange(int arr01[], int arr01size) { //Only work for array type qualified by Question 7: zeros followed by ones, other wise may return invalid values
	
	int low = 0;
	int high = arr01size - 1; 
	int mid; 
	
	while (low <= high) {
		
		mid = (low + high) / 2; 
		
		if (arr01[mid] == 1 && arr01[mid - 1] == 0) {
			
			return mid;
			
		} 
		
		else if (arr01[mid] == 1 && arr01[mid - 1] == 1){
			
			high = mid - 1;
			
		}
		
		else {
			
			low = mid + 1;
			
		}
		
	}
	
	return -1; //for certain invalid arrray input, return -1;
		
}
