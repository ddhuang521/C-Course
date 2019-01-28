#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

class Employee{ //Employee class
	public:
		void operator =(const Employee &rhs);
		Employee();
		Employee(int new_num, double new_pay, int new_hour, double new_total, string new_name);
		
		void setnum(int new_num);
		void setpay(double new_pay);
		void sethour(int new_hour);
		void settotal(double new_total);
		void setname(string new_name);
		
		int getnum()  const;
		double getpay() const;
		int gethour() const;
		double gettotal() const;
		string getname() const;
				
	private:
		int num;
		double pay;
		int hour;
		double total;
		string name;
};

class LList{ //Link List class
	public: 
		LList();
		LList(Employee new_worker, LList *for_next, LList *back_next);
		
		void setdata(Employee new_worker);
		void set_for_Link(LList *for_next);
		void set_back_Link(LList *back_next);
		
		Employee getdata() const;
		LList *get_for_Link() const;
		LList *get_back_Link() const;
		
	private:
		Employee worker;
		LList *for_link;
		LList *back_link;
}; 

void head_insert(LList *&head, Employee new_worker); //insert new node to the LList
void input_data(fstream &fin, fstream &fin2, LList *&next); //read the data file and write to the LList
void sort_LList(LList *next);    //sort the total pay in descending order
void LList_output(fstream &fout, LList *head);  //output the payroll informaiton
void LList_delete(LList *&head); //delete the LList pointers


/*Main Function*/
int main() {
	//read in and read out objects
	fstream fin, fin2;
	fstream fout; 
	
	//Linked List pointer
	LList *head = new LList;
	
	input_data(fin, fin2, head);
	sort_LList(head);
	LList_output(fout, head);
	LList_delete(head);
	
}




void head_insert(LList *&head, Employee new_worker){
	LList *temp = new LList; 
	temp -> setdata(new_worker);
	temp -> set_for_Link(head);
	head -> set_back_Link(temp);
	head  = temp;
}

void input_data(fstream &fin, fstream &fin2, LList *&next){
	int new_num;
	int new_num2; 
	double new_pay;
	int new_hour;
	string new_name; 
	Employee new_worker; 
	LList *temp = next; //make a copy of last node

		
	fin.open("employee_data.txt");
	fin2.open("working_hours.txt");
	if(fin.fail() || fin2.fail()){
		cout<<"Input file opening failed"<<endl;
		exit(1);
	}
	
	fin>>new_num>>new_pay;
	getline(fin, new_name);
			
	new_worker.setnum(new_num);
	new_worker.setpay(new_pay);
	new_worker.setname(new_name);
	next -> setdata(new_worker);
	
	while(!fin.eof()){
		
		fin>>new_num>>new_pay;
		getline(fin, new_name);
				
		new_worker.setnum(new_num);
		new_worker.setpay(new_pay);
		new_worker.setname(new_name);
				
		head_insert(next, new_worker);
	}
	
	//read the 2nd file
	int temp_num;
	int total_hour = 0;
	Employee temp_worker;
	
	fin2>>new_num2>>new_hour;
	temp_num = new_num2; 
	total_hour = new_hour;
	
	while(!fin2.eof()){
		
		fin2>>new_num2>>new_hour;
		
		if(new_num2 == temp_num){
			total_hour += new_hour;
		}
		else{
			temp_worker = temp -> getdata(); 
			temp_worker.sethour(total_hour); 
			temp_worker.settotal(temp_worker.getpay() * total_hour); 
			temp -> setdata(temp_worker);
			temp = temp -> get_back_Link();
			total_hour = new_hour;
			Employee temp_worker;
		}
		
		temp_num = new_num2; 
	}
	
	temp_worker = temp -> getdata(); 
	temp_worker.sethour(total_hour); 
	temp_worker.settotal(temp_worker.getpay() * total_hour); 
	temp -> setdata(temp_worker);
	
	fin.close();
	fin2.close();

}

void sort_LList(LList *next){
	LList *iter = new LList;
	LList *iter2 = new LList;
	LList *iter3 = new LList;
	Employee emp1, emp2;
	iter = next -> get_for_Link();
	bool stop;
	
	while(iter != NULL){
		stop = false;
		iter2 = iter -> get_back_Link();
		
		while(iter2 != NULL && stop == false){
			
			iter3 = iter2 -> get_for_Link();
			
			emp1 = iter2 -> getdata();
			emp2 = iter3 -> getdata();
			
			if(emp1.gettotal() < emp2.gettotal()){
				iter3 -> setdata(emp1);
				iter2 -> setdata(emp2);
			}
			else{
				stop = true;
			}
			
			iter2 = iter2 -> get_back_Link();
		}
		
		next = iter;
		iter = next -> get_for_Link();
	}

}

void LList_output(fstream &fout, LList *head){
	
	Employee worker; 
	
	fout.open("payroll.txt");
	if(fout.fail()){
		cout<<"Output file opening failed"<<endl;
		exit(1);
	}
	
	fout<<"************Payroll Information************"<<endl;
	while(head != NULL){
		
		worker = head -> getdata();
		
		fout<<worker.getname()<<", "<<"$"<<worker.gettotal()<<endl;
		head = head -> get_for_Link();

	}	
	fout<<"***************End Payroll*****************"<<endl;
	
	fout.close();
}

void LList_delete(LList *&head){
	LList *temp = head;
	
	while(temp != NULL){
		LList *del = temp;
		temp = temp -> get_for_Link();
		delete del;		
	}	
	
}

//LList class functions declaration
LList::LList(){
	Employee worker; 
	for_link = NULL;
	back_link = NULL;
}

LList::LList(Employee new_worker, LList *for_next, LList *back_next){
	worker = new_worker;
	for_link = for_next; 
	back_link = back_next;
}

Employee LList::getdata() const{
	return worker;
}

LList *LList::get_for_Link() const{
	return for_link;
}

LList *LList::get_back_Link() const{
	return back_link;
}

void LList::setdata(Employee new_worker){
	worker = new_worker;
}

void LList::set_for_Link(LList *for_next){
	for_link = for_next;
}

void LList::set_back_Link(LList *back_next){
	back_link = back_next;
}


//Employee class declaration
void Employee::operator =(const Employee &rhs){
	num = rhs.getnum();
	pay = rhs.getpay();
	hour = rhs.gethour();
	name = rhs.getname();
	total = rhs.gettotal();
}

Employee::Employee(){
	num = 0; 
	pay = 0; 
	hour = 0; 
	total = 0;
	name = "null";
}

Employee::Employee(int new_num, double new_pay, int new_hour, double new_total, string new_name){
	num = new_num;
	pay = new_pay;
	hour = new_hour;
	total = new_total;
	name = new_name;
}

void Employee::setnum(int new_num){
	num = new_num;
}
void Employee::setpay(double new_pay){
	pay = new_pay;
}
void Employee::sethour(int new_hour){
	hour = new_hour;
}
void Employee::settotal(double new_total) {
	total = new_total;
}
void Employee::setname(string new_name){
	name = new_name;
}

int Employee::getnum() const {
	return num;
}
double Employee::getpay() const {
	return pay;
}
int Employee::gethour() const {
	return hour;
}
double Employee::gettotal() const{
	return total;
}
string Employee::getname() const {
	return name; 
}


