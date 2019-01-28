#include <iostream>
using namespace std;

//call function
void arrayenlarge(int *&arr, int size, int new_item);

int main() {
	
	//variables
	int size = 10; //size of the dynamic array
	int *arr = new int[size]; //dyanmic array on the heap
	int new_item = 17; //new number to be added the array
	
	//initialize a certain sorted int array on the heap
	cout<<"Enter 10 numbers from small to large: "<<endl; 
	
	for (int i = 0; i < size; i++) {
		
		cin>>arr[i];
		
	}
	
	arrayenlarge(arr,size, new_item);
	
	//output the enlarged array
	for (int i = 0; i < size + 1; i++) {
		
		cout<<arr[i]<<" ";
		
	}	
	
	cout<<endl;
	delete [] arr; //release the memory on the heap
	
	return 0;
	
}


void arrayenlarge(int *&arr, int size, int new_item) {
	
	int *temp = new int[size + 1]; //new dynamic array with new size
	int i = 0; //index of old array
	
	//copy the old array elements if they are no larger than the new element
	while(new_item >= arr[i]) {
		
		temp[i] = arr[i];
		i++;
		
		if (i == size) {
			
			break; //stop if all the old elements are copied
			
		}
		
	}
	
	temp[i] = new_item; //copy the new element to its sorted position
	
	//if there are elements larger than it, keep copying them to the new array
	if (i != size) {
		
		for (int j = i + 1; j < size + 1; j++) {
			
			temp[j] = arr[i];
			i++;
			
		}
		
	}
	
    delete [] arr; //delete the old array
	arr = temp;	//link it to the new largers array

}
