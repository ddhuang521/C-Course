#include <iostream>
using namespace std;

void printTriangle(int n);
void printOpositeTriangles(int n);
void printRuler(int n);

int main() {
	
	int n = 4; 
	
	printTriangle(n);
	
	cout<<"\n"<<"\n";
	
	printOpositeTriangles(n);
	
	cout<<"\n"<<"\n";

	printRuler(n);
	
	return 0;
	
}



void printTriangle(int n) {
	
	if (n == 1) {
		
		cout<<"*";
		
	}
	
	else {
		
		
		printTriangle(n - 1);
		
		for (int i = 0; i < n; i++) {
			
			cout<<"*";
			
		}
		
	}
	
	cout<<endl;
	
}

void printOpositeTriangles(int n) {
	
	if (n == 1) {
		
		cout<<"*"<<endl;
		cout<<"*"<<endl;
		
	}
	
	else {
		
		for(int i = 0; i < n; i++) {
			
			cout<<"*";
			
		}
		
		cout<<endl;
		
		printOpositeTriangles(n - 1);
		
		for (int i = 0; i < n; i++) {
			
			cout<<"*";
			
		}
		
		cout<<endl;
		
	}
	
}

void printRuler(int n) {
	
	if (n == 1) {
		
		cout<<"-"<<endl;
		
	}
	
	else {
		
		printRuler(n - 1);
		
		for(int i = 0; i < n; i++) {
			
			cout<<"-";
			
		}
		
		cout<<endl;
		
		printRuler(n - 1);
		
	}
	
	
	
}














