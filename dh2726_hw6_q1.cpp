#include <iostream>
using namespace std;

//call function define array const size
const int max_size = 100; 
void string_reverse(char str[]);

int main() {
	
	//define char array to store string 
	char str[max_size];  //initialize the input of the function
	cout<<"Please enter a string"<<endl;
	cin>>str;

	string_reverse(str);
	
	//display reversed string
	
	for(int i = 0; i < strlen(str); i++) {
		
		cout<<str[i];
		
	}
	
	cout<<endl;
	
	return 0;
	
}


void string_reverse(char str[]) {
	
	//define front and rear points
	char *f = str;//f is intitialized to 1st element of the array
	char *r = str + strlen(str) - 1; //r is intitialized to last element of the array
	char temp; //define intermediate temp variable
	
	while (f < r) { //when f is to the left of r
		
		//reverse the symmetrical elements
		temp = *f; 
		*f = *r;
		*r = temp;
		 
		//move the points to the next element
		f++;
		r--;
	}
	
	
}
