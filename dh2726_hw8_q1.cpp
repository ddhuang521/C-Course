#include <iostream>
using namespace std;

class Money{
	public:
		void operator =(const Money &rhs);//overloading the assignment operator
		Money(long dollars, int cents);
		Money(long dollars);
		Money();
		
		long get_all_cents() const;//get amount in cents
		double get_value() const; //get amount in dollars
		void set_value(long dollars, int cents);
	private: 
		long all_cents;
};

class Check{
	public: 
		void operator =(const Check &rhs);//overloading the assignment operator
		Check();
		Check(int new_number, Money new_amount, bool new_is_check);
		void set_number(int new_number);
		void set_amount(double new_amount);
		void set_is_check(bool new_is_check);
		int get_number() const;
		Money get_money_amount() const;
		double get_amount() const;
		bool get_is_check() const;
		
		void check_input();
		void check_output() const;
		
	private: 
		int number; 
		Money amount;
		bool is_check;
};

double *deposit_input(int size);//enter the deposit amounts into the deposit array
void bank_output(Check *c, int size1, double *d, int size2, double old_balance, double new_balance);//output total cashed check amount, deposit amount, expected balance and difference of new balances
void sorted_cashed_check(Check *arr, int size);//merge sort the cashed and uncashed check separately and display their information

/*merge sort the check number*/
void sort(Check *arr, int low, int high);
void merge(Check *arr, int low, int mid, int high);



/*Main Function*/
int main() {
	int num;
	cout<<"How many checks do you have?"<<endl;
	cin>>num;
	
	Check *c = new Check[num]; //record the check information
	for(int i = 0; i < num; i++){
		cout<<"Check "<<(i + 1)<<": "<<endl;
		c[i].check_input(); //input the check details
	}
	
	int num1;
	cout<<"How many deposits have been made?"<<endl;
	cin>>num1;
	double *d;
	d = deposit_input(num1); //enter deposit information
	
	
	double old_balance, bank_balance;
	cout<<"Please enter the old bank balance: $";
	cin>>old_balance;
	cout<<"Please enter the new bank balance: $";
	cin>>bank_balance;
	cout<<endl;
	//output 
	bank_output(c, num, d, num1, old_balance, bank_balance); 
	sorted_cashed_check(c, num); 
	
	//free the heap memory
	delete [] c;
	delete [] d;
	
	return 0;
}

/*Input Functions*/
double *deposit_input(int size){
	double *d = new double[size];
		
	for(int i = 0; i < size; i++){
		double number;
		cout<<"Please enter the amount of deposit "<<(i + 1)<<": $";
		cin>>number;
		d[i] = number;
	}
	cout<<endl;
	
	return d;
}

/*Display Functions*/
void bank_output(Check *c, int size1, double *d, int size2, double old_balance, double bank_balance){
	
	double total_check = 0;
	for(int i = 0; i < size1; i++){
		if(c[i].get_is_check() == 1){
			total_check += c[i].get_amount();
		}
	}
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);
	cout<<"The total of the checks cashed is $"<<total_check<<endl;
	
	double total_deposit = 0;
	for(int i = 0; i < size2; i++){
		total_deposit += d[i];
	}
	cout<<"The total of the deposits is $"<<total_deposit<<endl;

	
	double new_balance;
	new_balance = old_balance + total_deposit - total_check;
	cout<<"The new balance should be $"<<new_balance<<endl;
	
	double diff;
	diff = new_balance - bank_balance;
	if(diff < 0){
		double temp = -diff;
		cout<<"The difference between new balance and new bank balance is -$"<<temp<<endl;
	}
	else{
		cout<<"The difference between new balance and new bank balance is $"<<diff<<endl;
	}
	cout<<endl;
}

void sorted_cashed_check(Check *arr, int size){ 
	Check *sort_array = new Check[size];
	int counter1 = 0; 
	int counter2 = 0;
	
	for(int i = 0; i < size; i++){
		if(arr[i].get_is_check() == 1){
			sort_array[counter1] = arr[i];
			counter1++;
		}
		else{
			sort_array[size - counter2 - 1] = arr[i];
			counter2++;
		}
	}
	
	if(counter2 == 0){
		sort(sort_array, 0, size - 1);
		for(int i = 0; i < size; i++){
			sort_array[i].check_output();
		}	
		cout<<endl;
	}
	else if(counter1 == 0){
		sort(sort_array, 0, size - 1);
		for(int i = 0; i < size; i++){
			sort_array[i].check_output();
		}	
		cout<<endl;
		
	}
	else{
		sort(sort_array, 0, counter1 - 1);
		sort(sort_array, counter1, size - 1);
		for(int i = 0; i < counter1; i++){
			sort_array[i].check_output();
		}	
		for(int i = counter1; i < size; i++){
			sort_array[i].check_output();
		}	
		cout<<endl;
	}
	
	delete [] sort_array;
}

/*merge sort the check number*/
void sort(Check *arr, int low, int high){
	int mid;
	if(low == high){
		return;
	}
	else{
		mid = (low + high) / 2;
		sort(arr, low, mid);
		sort(arr, mid + 1, high);
		merge(arr, low, mid, high);
	}
}

void merge(Check *arr, int low, int mid, int high){
	    int tsize = high - low + 1;
		Check *temp = new Check[tsize];
		int a = low;
		int b = mid + 1; 
		int ind = 0; 
		
		while(a <= mid && b<= high){
			if(arr[a].get_number() <= arr[b].get_number()){
				temp[ind] = arr[a];
				a++;
			}
			else{
				temp[ind] = arr[b];
				b++;
			}
			ind++;
		}
		
		while(a <= mid){
			temp[ind] = arr[a];
			a++;
			ind++;
		}
		
		while(b <= high){
			temp[ind] = arr[b];
			b++;
			ind++;
		}
		
		for(int i = 0, j = low; i <  ind; i++, j++){
			arr[j] = temp[i]; 
		}

		delete [] temp;
}

/*Money Class Member Function Definition*/
void Money::operator =(const Money &rhs){//overloading the assignment operator
	all_cents = rhs.get_all_cents();
}

Money::Money(long dollars, int cents){
	all_cents = dollars * 100 + cents;
}

Money::Money(long dollars){
	all_cents = dollars * 100;
}

Money::Money(){
	all_cents = 0;
}

double Money::get_value() const{
	return all_cents * 0.01; 
}

void Money::set_value(long dollars, int cents){
	all_cents = dollars * 100 + cents;
}

long Money::get_all_cents() const{
	return all_cents;
}



/*Check Class Member Function Definition*/
void Check::operator =(const Check &rhs){//overloading the assignment operator
	number = rhs.get_number();
	amount = rhs.get_money_amount();
	is_check = rhs.get_is_check();
}

Check::Check(){
	number = 0;
	amount.set_value(0,0);
	is_check = 0;
}

Check::Check(int new_number, Money new_amount, bool new_is_check){
	number = new_number;
	int dol = new_amount.get_value() * 100 / 100;
	int cen = (new_amount.get_value() - dol)  * 100;
	amount.set_value(dol, cen);
}

void Check::set_number(int new_number){
	number = new_number;
}

void Check::set_amount(double new_amount){
	int d = new_amount * 100;
	long doll =(int) new_amount;
	int cen = d % 100;
	amount.set_value(doll, cen);
}

void Check::set_is_check(bool new_is_check){
	is_check = new_is_check;
}

int Check::get_number() const{
	return number;
}

double Check::get_amount() const{
	return amount.get_value(); 
}

Money Check::get_money_amount() const{
	return amount;
}


bool Check::get_is_check() const{
	return is_check; 
}

void Check::check_input(){
	
		int new_number = 0;
		double new_amount = 0;
		char is_check_char;
		cout<<"Please enter the check number: ";
		cin>>new_number;
		cout<<"Enter the check amount $";
		cin>>new_amount;
		cout<<"Enter if check has been cashed(y/n):";
		cin>>is_check_char;
		cout<<endl;
		if (is_check_char == 'Y' || is_check_char == 'y'){
			is_check = 1;
		}
		else {
			is_check = 0;
		}
		
		number = new_number;
		int d = new_amount * 100;
		long doll = (int) new_amount;
		int cen = d % 100;		
		amount.set_value(doll, cen);
}

void Check::check_output() const{
	
	if(is_check == 1){
		cout<<"Check number "<<number<<": amount is $"<<amount.get_value()<<"(Cashed)"<<endl;

	}
	else{
		cout<<"Check number "<<number<<": amount is $"<<amount.get_value()<<"(Not cashed yet)"<<endl;

	}
}



