#include <iostream>
using namespace std;

class Avl{
	public: 
		Avl(){
			root = NULL;
		}
		~Avl(){
			makeEmpty(root);
		}
		void insert(int x){
			insert(x, root);
		}
//		void remove(int x){
//			remove(x, root);
//		}
		void printTree(){
			if(root == NULL){
				cout<<"Empty Tree"<<endl;
			}
			else{
				inorderDisplay(root);
				cout<<endl;
			}
		}
		
	private: 
		struct AvlNode{
			int element; 
			int color; //red 0, black 1
			AvlNode *left;
			AvlNode *right;
			AvlNode *parent;
		};
		
		AvlNode *root;
		
		void insert(int x, AvlNode *&t){
			if(t == NULL){
				t = new AvlNode;
				t -> element = x; 
				t -> color = 0;
				t -> left = NULL;
				t -> right = NULL;
				t -> parent = NULL;
			}
			else if(x < t -> element){
				insert(x, t -> left);
				t -> left -> parent = t;
			}
			else if(x > t -> element){
				insert(x, t -> right);
				t -> right -> parent = t;
			}
			
			insertionFix(t);
		}
		
//		void remove(int x, AvlNode *&t){
//			if(t == NULL){
//				return;
//			}
//			if(x < t -> element){
//				remove(x, t -> left);
//			}
//			else if(x > t -> element){
//				remove(x, t -> right);
//			}
//			else if(t -> left != NULL && t -> right != NULL){//delete node with double children 
//				t -> element = findMin(t -> right) -> element;
//				t -> color =  findMin(t -> right) -> color;
//				remove(t -> element, t -> right);
//				}
//			else{   //delete node with single child
//				AvlNode *oldNode = t; 
//				if(t -> left != NULL){
//					t = t -> left;
//					if(t != NULL){
//						t -> parent = oldNode -> parent;
//					}
//				}
//				else{
//					t = t -> right;
//					if(t != NULL){
//						t -> parent = oldNode -> parent;
//					}
//				}
//				
//				delete oldNode;
//			}
//			
//			if(t -> color == 1){
//				removeFix(t);
//			}
//			
//		}
		
		void insertionFix(AvlNode *&t){
			
			AvlNode *gp = new AvlNode; //grandparent node
					
			if(t -> parent == NULL){ //t is the root,color black
				t -> color = 1;
			}
			
			else{
				gp = t -> parent -> parent; 
				 if(t -> parent -> color == 0 && gp -> left == t -> parent){//parent is red
					if(gp -> right != NULL && gp -> right -> color == 0){//uncle is red and right
						gp -> left -> color = 1;
						gp -> right -> color = 1;
						gp -> color = 0;
						insertionFix(gp); //set t's gp as new t
					}
					else if(gp -> right == NULL || gp -> right -> color == 1){
						if(t == t -> parent -> left){//left-left case
							rightRotation(gp);	
							gp -> color = 1;
							gp -> right -> color = 0; 
						}
						else{ //left-right case
							leftRightRotation(gp);
							gp -> color = 1;
							gp -> right -> color = 0;
						}
					}
				}
				
				else if(t -> parent -> color == 0 && gp -> right == t -> parent){
					if(gp -> left != NULL && gp -> left -> color == 0){//uncle is red and left
						gp -> right -> color = 1;
						gp -> left -> color = 1;
						gp -> color = 0;
						insertionFix(gp);
					}
					else if(gp -> left == NULL || gp -> left -> color == 1){
						if(t == t -> parent -> right){
							leftRotation(gp);
							gp -> color = 1;
							gp -> left -> color = 0; 
						}
						else{
							rightLeftRotation(gp);
							gp -> color = 1;
							gp -> left -> color = 0;
						}
					}
				}
			}	
			
		}
		
//		void removeFix(AvlNode *&t){
//			AvlNode* w;
//			if(t -> color == 0){
//				t -> color = 1;
//			}
//			
//			else{
//				if(t -> parent == NULL){
//					return;
//				}
//				else if(t == t -> parent -> left){
//					w = t -> parent -> right;
//					if(w -> color == 0){
//						w -> color = 1;
//						t -> parent -> color = 0; 
//						leftRotation(t -> parent);
//						w = t -> parent -> right;
//					}
//					if(w -> left -> color == 1 && w -> right -> color == 1){
//						w -> color = 0;
//						t = t -> parent;
//						removeFix(t);
//					}
//					else{
//						
//						if(w -> right -> color == 1){
//							w -> left -> color = 1; 
//							w -> color = 0;
//							rightRotation(w);
//							w = t -> parent -> right;
//						}
//						w -> color = t -> parent -> color;
//						t -> parent -> color = 1;
//						w -> right -> color = 1;
//						leftRotation(t -> parent);
//					}
//				}
//				
//				else{
//					w = t -> parent -> left;
//					
//					if(w -> color == 0){
//						w -> color = 1;
//						t -> parent -> color= 0; 
//						rightRotation(t -> parent);
//						w = t -> parent -> left;
//					}
//					
//					if(w -> right -> color == 1 && w -> left -> color == 1){
//						w -> color = 0;
//						t = t -> parent;
//						removeFix(t);
//					}
//					
//					else{
//						if(w -> left -> color == 1){
//							w -> right -> color = 1; 
//							w -> color = 0;
//							leftRotation(w);
//							w = t -> parent -> left;
//						}
//						
//						w -> color = t -> parent -> color;
//						t -> parent -> color = 1;
//						w -> left -> color = 1;
//						rightRotation(t -> parent);
//					}
//				}
//			}
//		}
		void rightRotation(AvlNode *&t){
			AvlNode *temp = t -> left;
			t -> left = temp -> right;
			temp -> right = t;
			t = temp;
		}
		
		void leftRotation(AvlNode *&t){
			AvlNode *temp = t -> right;
			t -> right = temp -> left;
			temp -> left = t; 
			t = temp;
		}
		
		void leftRightRotation(AvlNode *&t){
			leftRotation(t -> left);	
			rightRotation(t);
		}
		
		void rightLeftRotation(AvlNode *&t){
			rightRotation(t -> right);
			leftRotation(t);
		}
		
		AvlNode *findMin(AvlNode *t){
			if(t == NULL){
				return NULL;
			}
			if(t -> left == NULL){
				return t;
			}
			return findMin(t -> left);
		} 
		
		AvlNode *findMax(AvlNode *t){
			if(t == NULL){
				return NULL;
			}
			if(t -> right == NULL){
				return t;
			}
			return findMin(t -> right);
		} 			
		
		AvlNode *findElement(int x, AvlNode *t){
		    if(x == t -> element){
				return t;
			}
			else if(x < t -> element){
				return findElement(x, t -> left);
			}
			else if(x > t -> element){
				return findElement(x, t -> right);
			}
			else{
				return NULL;
			}
		}
		
		void inorderDisplay(AvlNode *t){
			if(t == NULL){
				return;
			}
			inorderDisplay(t -> left);
			cout<<t -> element<<" ";
			inorderDisplay(t -> right);
		}
		
		void makeEmpty(AvlNode *&t){
			if(t != NULL){
				makeEmpty(t -> left);
				makeEmpty(t -> right);
				delete t;
			}
			t = NULL;
		}
};

int main(){
	
	Avl tree; 
	
	int arr_insert[20] = {12, 1, 9, 2, 0, 11, 7, 19, 4, 15, 18, 5, 14, 13, 10, 16, 6, 3, 8, 17};
	for(int i = 0; i < 20; i++){
		tree.insert(arr_insert[i]);
	}
	tree.printTree();
	
//	int arr_remove[3] ={13, 4, 9};
//	for(int i = 0; i < 3; i++){
//		tree.remove(arr_remove[i]);
//	}
//	tree.printTree();

}

