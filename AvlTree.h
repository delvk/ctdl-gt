#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <iostream>
using namespace std;

enum Balance_factor {left_higher,equal_height,right_higher};

template <class T>
struct AvlNode
{
        T element;
        AvlNode *left;
        AvlNode *right;
        Balance_factor balance;

        AvlNode(T x)
        {
            element = x;
            left = NULL;
            right = NULL;
			balance = equal_height;
        }
};

template <class T>
class AvlTree
{
  public:
    AvlTree()
    {
        root = NULL;
    }

    ~AvlTree()
    {
        makeEmpty();
    }

    bool isEmpty()
    {
        return root == NULL;
    }

    void printTree()
    {
		
        if(isEmpty())
            cout << "Empty tree" << endl;
        else
            printTree(root);
		cout << endl;
    }
	void print(){
		print(root);
	}
    void makeEmpty()
    {
        makeEmpty(root);
    }

    void insert(T x)
    {
        insert(x, root);
    }

    void remove(T x)
    {
        remove(x, root);
    }

    void generateAVLfromList(T arr[], int n)
    {
        for (int i = 0; i < n; i++)
        {
            insert(arr[i]);
        }
    }

  private:
    AvlNode<T> *root;
	bool isShorter;
	bool isTaller;
	bool isChild;
	void rotRight(AvlNode<T> *&pR){
		AvlNode<T>  *p = pR->left;
		pR->left = p->right;
		p->right = pR;

		pR = p;
	}
	void rotLeft(AvlNode<T> *&pR){
		AvlNode<T>  *p = pR->right;
		pR->right = p->left;
		p->left = pR;
		pR = p;
	}
	void rotLR(AvlNode<T> *&pR){
		rotLeft(pR->left);
		rotRight(pR);
	}
	void rotRL(AvlNode<T> *&pR){
		rotRight(pR->right);
		rotLeft(pR);
	}
    void insert(T &x, AvlNode<T> *&t)
    {
		
        // to do
		if (t==NULL){
			t = new AvlNode<T>(x);
			//t->balance = equal_height;
		}
		else if (x < t->element){
			isTaller = true;
			insert(x, t->left);
			//cout << "t->element: " << t->element << endl;
			if (isTaller){
				if (t->balance == equal_height)t->balance = left_higher;
				else if (t->balance == right_higher){
					t->balance = equal_height;
					isTaller = false;
				}
				else{
					if (t->left->balance == left_higher){//L-L
						rotRight(t);
						t->balance = t->right->balance = equal_height;
					}
					else if (t->left->balance == equal_height || t->left->right->balance == equal_height){
						/*t->balance = t->left->balance = equal_height;
						t->right->balance=right_higher;*/
					}
					else{
						rotLR(t);
						t->balance = t->right->balance = equal_height;
						t->left->balance = left_higher;
					}
				}
			}

		}//end Insert-LEFT
		else{
			isTaller = true;
			insert(x, t->right);
			//cout << "t->element: " << t->element << endl;
			if (isTaller){
				if (t->balance == equal_height)t->balance = right_higher;
				else if (t->balance == left_higher)	{
					t->balance = equal_height;
					isTaller = false;
				}
				else{
					//cout << t->right->element << endl;
					if (t->right->balance == right_higher){//R-R
						rotLeft(t);
						t->balance = t->left->balance = equal_height;
						isTaller = false;
					}
					else if (t->right->balance == equal_height || t->right->left->balance == equal_height){
					}
					else{//R-L
						rotRL(t);
						t->balance = t->left->balance = equal_height;
						t->right->balance = right_higher;
						isTaller = false;
					}
				}
			}
		}
		//printTree(); cout << endl;
		//end
    }

    void remove(T &x, AvlNode<T> *&t)
    {
		isChild = false;
		bool delLeft = false;
		if (t == NULL){
			return;
		}
		if (x < t->element) {
			delLeft = true;
			isShorter = true;
			remove(x, t->left);
			
		}
		else if (x>t->element){
			isShorter = true;
			remove(x, t->right);
	
		}
		else{//x==t->element
			//cout << endl << t->element << endl;
			if (t->left == NULL && t->right ==NULL){
				delete t;
				t = NULL;
				return;
			}
			else if (t->right == NULL){
				AvlNode<T> *p = t->left;
				delete t;
				t = p;
				return;
				//shorter = true;
			}
			else if (t->left == NULL){
				AvlNode<T> *p = t->right;
				delete t;
				t = p;
				return;
				//shorter = true;
			}
			else{//MAX OF LEFT
				AvlNode<T> *p = max(t->left);
				t->element = p->element;
				remove(p->element, t->left);
				isChild = true;
				
			}
		}
		if (isShorter){
			if (delLeft) {
				balanceRight(t);
			}
			else balanceLeft(t);
		}
    }
	void balanceRight(AvlNode<T> *&root){
		if (root->balance == left_higher) {
			root->balance = equal_height;
			//isShorter = false;
		}
		else if (root->balance == equal_height){
			isShorter = false;
			if (isChild) root->balance = left_higher;
			else root->balance = right_higher;
		}
		else{
			AvlNode<T> *rightTree = root->right;
			if (rightTree->balance == left_higher){
				AvlNode<T> *leftTree = rightTree->left;
				if (leftTree->balance == left_higher){
					rightTree->balance = right_higher;
					root->balance = equal_height;
				}
				else if (leftTree->balance == equal_height){
					root->balance = left_higher;
					rightTree->balance = equal_height;
				}
				else {
					root->balance = left_higher;
					rightTree->balance = equal_height;
				}
				leftTree->balance = equal_height;
				rotRL(root); 
			}
			else {
				if (rightTree->balance != equal_height){
					root->balance = equal_height;
					rightTree->balance = equal_height;
				}
				else {
					root->balance = right_higher;
					rightTree->balance = left_higher;
					isShorter = false;
				}
				rotLeft(root);
			}
		}
	}
	void balanceLeft(AvlNode<T> *&root){
		if (root->balance == right_higher){
			root->balance = equal_height;
//			isShorter = false;
		}
		else if (root->balance == equal_height){
			isShorter = false;
			if (isChild) root->balance = right_higher;
			else root->balance = left_higher;
		}
		else{
			AvlNode<T> *leftTree = root->left;
			if (leftTree->balance == right_higher){
				AvlNode<T> *rightTree = leftTree->right;
				if (rightTree->balance == right_higher){
					leftTree->balance = left_higher;
					root->balance = equal_height;
				}
				else if (rightTree->balance == equal_height){
					root->balance = right_higher;
					leftTree->balance = equal_height;
				}
				else{
					root->balance = right_higher;
					leftTree->balance = equal_height;
				}
				rightTree->balance = equal_height;
				rotLR(root); 
			}
			else{
				if (leftTree->balance != equal_height){
					root->balance = equal_height;
					leftTree->balance = equal_height;
				}
				else {
					root->balance = left_higher;
					leftTree->balance = right_higher;
					isShorter = false;
				}
				rotRight(root);
			}
			
		}
	}
	AvlNode<T> *max(AvlNode<T> *&t){
		if (t->right == NULL) return t;
		return max(t->right);
	}
	AvlNode<T> *min(AvlNode<T> *&t){
		if (t->left == NULL)return t;
		return min(t->left);
	}
    void makeEmpty(AvlNode<T> *&t)
    {
        if(t != NULL)
        {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        t = NULL;
    }

    void printTree(AvlNode<T> *t)
    {
        if(t != NULL)
        {
			cout << t->element << " ";
            printTree(t->left);
            printTree(t->right);
        }
    }
	void print(AvlNode<T> *t)
	{
		if (t != NULL)
		{
			cout << t->element << " :" << t->balance << endl;
			print(t->left);
			print(t->right);
		}
	}
};

#endif
