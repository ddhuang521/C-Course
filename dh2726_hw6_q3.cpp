#include <iostream>
#include <vector>
using namespace std;

//call functions
void readgrade(vector<int> &v); //read the user input and store them in a vector
void histogram(int *arr_hist, vector<int> v, int size); //calculate the histogram of the grades
void readhist(int *arr_hist); //output the historgram

int main() {
	
	//variables
	vector<int> v; //vector to store the grades
	int *hist = new int[101]; //initialize a dynamic array to store the histogram of student grade, max size required is 101 (integers between 0-100)
	
	readgrade(v); //read the user input
	
	histogram(hist, v, v.size());
	readhist(hist);
	
	//release the memory
	v.clear();
	delete [] hist;	
	
	return 0;
	
}

void readgrade(vector<int> &v) {
	
	int grade = 0;
	cout<<"Please enter the grades of the students, end with -1:"<<endl;
		
	while(grade >= 0) { 
		
		cin>>grade;
		v.push_back(grade);
	}
	
	cout<<endl;
	
}

void histogram(int *arr_hist, vector<int> v, int size) {
	
	int j; //index of the histogram array
	
	for(int i = 0; i < size; i++) {
		
		j = v[i]; //record the grade of the students
		arr_hist[j]++; //put it to the proper position in the histogram
		
	}
		
}

void readhist(int *arr_hist) {
	
	for (int i = 0; i < 101; i++) {
		
		if (arr_hist[i] != 0) { 
			
			cout<<"Number of "<<i<<"'s: "<<arr_hist[i]<<endl;
			
		}
		
	}
		
}