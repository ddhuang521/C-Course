#include <iostream>
using namespace std;

class AvlNode{
public:
	AvlNode(): element(0),height(0),left(NULL),right(NULL) {}
	void set_element(int x){element = x;}
	void set_height(int h){height = h;}
	void set_left(AvlNode *l){left = l;}
	void set_right(AvlNode *r){right = r;}
	
	int get_element(){return element;}
	int get_height(){return height;}
	AvlNode* get_left(){return left;}
	AvlNode* get_right(){return right;}
	
private:
	int element;
	int height;
	AvlNode *left;
	AvlNode *right;
};

class Avl{
public:
	Avl(){ root = NULL; }
	~Avl(){ makeEmpty(root); } //delete all the nodes which are not removed
	void insert(int x);
	void remove(int x);
	void printTree();
	
private:
	AvlNode *root;
	
	void insert(int x, AvlNode *&t);
	void remove(int x, AvlNode *&t);
	void balance(AvlNode *&t);
	
	void RightRotation(AvlNode *&t);
	void LeftRotation(AvlNode *&t);
	void leftRightRotation(AvlNode *&t);
	void rightLeftRotation(AvlNode *&t);
	
	AvlNode *findMin(AvlNode *t);
	AvlNode *findMax(AvlNode *t);
	
	int height(AvlNode *t);
	void inorderDisplay(AvlNode *t);
	void makeEmpty(AvlNode *&t);
};

int main(){
	
	Avl tree;
	
	cout<<"AVL Tree After Insertion"<<endl;
	int arr_insert[20] = {3,16,7,18,9,2,1,11,8,19,6,15,17,12,13,5,14,4,20,10};
	for(int i = 0; i < 20; i++){
		tree.insert(arr_insert[i]);
	}
	tree.printTree();
	cout<<endl;
	
	cout<<"AVL Tree After Removing 5, 3, 12, 7"<<endl;
	int arr_remove[4] = {5,3,12,7};
	for(int i = 0; i < 4; i++){
		tree.remove(arr_remove[i]);
	}
	tree.printTree();
}

// Avl Public Functions
void Avl::insert(int x){
	insert(x, root);
}

void Avl::remove(int x){
	remove(x, root);
}

void Avl::printTree(){
	if(root == NULL){
		cout<<"Empty Tree"<<endl;
	}
	else{
		inorderDisplay(root);
		cout<<endl;
	}
}

// Avl Private Functions
void Avl::insert(int x, AvlNode *&t){
	if(t == NULL){
		t = new AvlNode;
		t -> set_element(x);
		t -> set_height(0);
		t -> set_left(NULL);
		t -> set_right(NULL);
	}
	else if(x < t -> get_element()){
		AvlNode *temp = t -> get_left();
		insert(x, temp);
		t -> set_left(temp);
	}
	else if(x > t -> get_element()){
		AvlNode *temp1 = t -> get_right();
		insert(x, temp1);
		t -> set_right(temp1);
	}
	
	balance(t);
}

void Avl::remove(int x, AvlNode *&t){
	if(t == NULL){
		return;
	}
	if(x < t -> get_element()){
		AvlNode *temp = t -> get_left();
		remove(x, temp);
		t -> set_left(temp);
	}
	else if(x > t -> get_element()){
		AvlNode *temp1 = t -> get_right();
		remove(x, temp1);
		t -> set_right(temp1);
	}
	else if(t -> get_left() != NULL && t -> get_right() != NULL){
		t -> set_element(findMin(t -> get_right()) -> get_element());
		int new_x = t -> get_element();
		AvlNode* temp2 = t -> get_right();
		remove(new_x, temp2);
		t -> set_right(temp2);
	}
	else{
		AvlNode *oldNode = t;
		t = (t -> get_left() != NULL) ? t -> get_left(): t -> get_right();
		delete oldNode;
	}
	
	balance(t);

}

void Avl::balance(AvlNode *&t){
	if(t == NULL){
		return;
	}
	if(height(t -> get_left()) - height(t -> get_right()) > 1){
		if(height(t -> get_left() -> get_left() ) >= height(t -> get_left() -> get_right())){
			RightRotation(t);
		}
		else{
			leftRightRotation(t);
		}
	}
	else if(height(t -> get_right()) - height(t -> get_left()) > 1){
		if(height(t -> get_right() -> get_right() ) >= height(t -> get_right() -> get_left())){
			LeftRotation(t);
		}
		else{
			rightLeftRotation(t);
		}
	}
	t -> set_height(max(height(t -> get_left()), height(t -> get_right())) + 1);
}

void Avl::RightRotation(AvlNode *&t){
	AvlNode *temp = t -> get_left();
	t -> set_left(temp -> get_right());
	temp -> set_right(t);
	t -> set_height(max(height(t -> get_left()), height(t -> get_right())) + 1);
	temp -> set_height(max(height(t -> get_left()), t -> get_height()) + 1);
	t = temp;
}

void Avl::LeftRotation(AvlNode *&t){
	AvlNode *temp = t -> get_right();
	t -> set_right(temp -> get_left());
	temp -> set_left(t);
	t -> set_height(max(height( t -> get_left()), height(t -> get_right())) + 1);
	temp -> set_height(max(height(t -> get_right()), t -> get_height()) + 1);
	t = temp;
}

void Avl::leftRightRotation(AvlNode *&t){
	AvlNode* temp = t -> get_left();
	LeftRotation(temp);
	t -> set_left(temp);
	RightRotation(t);
}

void Avl::rightLeftRotation(AvlNode *&t){
	AvlNode* temp = t -> get_right();
	RightRotation(temp);
	t -> set_right(temp);
	LeftRotation(t);
}

AvlNode *Avl::findMin(AvlNode *t){
	if(t == NULL){
		return NULL;
	}
	if(t -> get_left() == NULL){
		return t;
	}
	return findMin(t -> get_left());
}

AvlNode *Avl::findMax(AvlNode *t){
	if(t == NULL){
		return NULL;
	}
	if(t -> get_right() == NULL){
		return t;
	}
	return findMin(t -> get_right());
}

int Avl::height(AvlNode *t){
	if(t == NULL){
		return -1;
	}
	else{
		return t -> get_height();
	}
}

void Avl::inorderDisplay(AvlNode *t){
	if(t == NULL){
		return;
	}
	inorderDisplay(t -> get_left());
	cout<<t -> get_element()<<" ";
	inorderDisplay(t -> get_right());
}

void Avl::makeEmpty(AvlNode *&t){// free all the nodes memory space
	if(t != NULL){
		AvlNode* temp = t -> get_left();
		makeEmpty(temp);
		t -> set_left(temp);
		temp = t -> get_right();
		makeEmpty(temp);
		t -> set_right(temp);
		delete t;
	}
	t = NULL;
}
