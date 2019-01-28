#include <iostream>
using namespace std;

const int size = 6;
int mincost(int arr[], int arrSize);

int main() {
	
	int arr[size] = {0, 3, 80, 6, 57, 10};
	
	cout<<mincost(arr, size)<<endl;
	
	return 0;
}



int mincost(int arr[], int arrSize) {
	
	if (arrSize == 2 || arrSize == 3) { //base case
		
		return arr[arrSize - 1];
		
	}
	
	else {
		
		if (mincost(arr, arrSize - 1) <= mincost(arr, arrSize - 2)) { // which smaller case has smaller value
			
			return mincost(arr, arrSize - 1) + arr[arrSize - 1]; // use the smaller case plus the final number
			
		}
		
		else {
			
			return mincost(arr, arrSize - 2) + arr[arrSize - 1]; // use the smaller case plus the final number
			
		}
		
	}
	
}