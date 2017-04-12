#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

using namespace std;

template <class T>
struct BinaryNode
{
	T element;
	BinaryNode<T> *left;
	BinaryNode<T> *right;

	BinaryNode(T x) {
		element = x;
		left = NULL;
		right = NULL;
	}
};

template <class T>
class BinarySearchTree
{
public:
	BinarySearchTree()
	{
		root = NULL;
	}

	~BinarySearchTree()
	{
		makeEmpty();
	}

	bool isEmpty()
	{
		return root == NULL;
	}

	void printTree() {
		if (isEmpty())
			cout << "Empty tree" << endl;
		else
			printTree(root);
	}

	void makeEmpty()
	{
		makeEmpty(root);
	}

	void insert(T x)
	{
		insert(x, root);
	}

	void generateBSTfromList(T arr[], int n)
	{
		for (int i = 0; i < n; i++)
		{
			insert(arr[i]);
		}
	}

	void remove(T x)
	{
		remove(x, root);
	}

	int height()
	{
		return height(root);
	}

	void intervalVisit(T a, T b)
	{
		intervalVisit(a, b, root);
	}

	int evaluateExpress()
	{
		return evaluateExpress(root);
	}

	int testAVL()
	{
		return testAVL(root);
	}

	int isNearlyCompleteBST()
	{
		return isNearlyCompleteBST(root);
	}
	int count_nodes(){
		return count_nodes(root);
	}
private:
	BinaryNode<T> *root;

	void insert(T x, BinaryNode<T>* &root)
	{
		if (root == NULL)
		{
			BinaryNode<T>* newNode = new BinaryNode<T>(x);
			root = newNode;
		}
		else
		{
			if (x < root->element)
			{
				insert(x, root->left);
			}
			else
			{
				insert(x, root->right);
			}
		}
	}

	void remove(T &x, BinaryNode<T>* &t)
	{
		if (x < t->element) remove(x, t->left);
		else if (x > t->element) remove(x, t->right);
		else {   //When x==t->element
			if (t->left == NULL && t->right == NULL){
				delete t;
				t = NULL;

			}
			else if (t->left == NULL){
				BinaryNode<T> *temp = t;
				t = t->right;
				delete temp;
			}
			else if (t->right == NULL){
				BinaryNode<T> *temp = t;
				t = t->left;
				delete temp;
			}
			else{
				BinaryNode<T> *temp = FindMax(t->left);
				t->element = temp->element;
				remove(temp->element, t->left);
			}
		}
	}
	BinaryNode<T> * FindMin(BinaryNode<T> *&t){
		if (t->left == NULL) return t;
		else return FindMin(t->left);
	}
	BinaryNode<T> * FindMax(BinaryNode<T> *&t){
		if (t->right == NULL) return t;
		else return FindMax(t->right);
	}

	int height(BinaryNode<T> *t)
	{
		// to do
		if (t == NULL)
			return 0;
		else {
			int leftHeight = height(t->left);
			int rightHeight = height(t->right);
			return leftHeight > rightHeight ? (leftHeight + 1) : (rightHeight + 1);
		}
	}

	void intervalVisit(T a, T b, BinaryNode<T> *t)
	{
		if (t == NULL) return;
		if (t->element >= a && t->element <= b){
			cout << t->element << " ";
			intervalVisit(a, b, t->left);
			intervalVisit(a, b, t->right);
		}
		else if (t->element < a) intervalVisit(a, b, t->right);
		else intervalVisit(a, b, t->left);
	}

	int evaluateExpress(BinaryNode<T> *t)
	{
		if (!t)return 0;
		if (!t->left && !t->right) return t->element;
		int x = evaluateExpress(t->left);
		int y = evaluateExpress(t->right);
		if (t->element % 2 == 0) return x + y;
		else return x*y;
	}

	int testAVL(BinaryNode<T> *root)
	{

		if (root == NULL)
			return 1;

		int lh; 
		int rh;

		
		lh = height(root->left);
		rh = height(root->right);

		if (abs(lh - rh) <= 1 && testAVL(root->left) && testAVL(root->right))
			return 1;

		
		return 0;

	}
	int exponent(int x, int n) { 
		int pow = 1; int i = 0; 
		for (i = 0; i<n; i++) pow *= x;
		return pow;
	}
	int count_nodes(BinaryNode<T> *root){
		if (root == NULL) return 0;
		return 1 + count_nodes(root->right) + count_nodes(root->left);
	}
	int isCompleteBST(BinaryNode<T> *root)
	{
		if (root == NULL) return 1; 
		int h = height(root);
		int n = count_nodes(root);
		if (n == exponent(2, h) - 1) return 1;
		else return 0;
	}
	int isNearlyCompleteBST(BinaryNode<T> *root){
		int idx = 0; int num_of_nodes = count_nodes(root);
		if (isNearlyComplete(root,idx,num_of_nodes))return 1;
		return 0;
	}
	bool isNearlyComplete(BinaryNode<T>* root,  int index,  int number_nodes)
	{
		if (root == NULL)
			return (true);
		if (index >= number_nodes)
			return (false);
		return (isNearlyComplete(root->left, 2 * index + 1, number_nodes) && isNearlyComplete(root->right, 2 * index + 2, number_nodes));
	}
	void makeEmpty(BinaryNode<T>* &t)
	{
		if (t != NULL)
		{
			makeEmpty(t->left);
			makeEmpty(t->right);
			delete t;
		}
		t = NULL;
	}

	void printTree(BinaryNode<T> *t)
	{
		if (t != NULL)
		{
			cout << t->element << " ";
			printTree(t->left);
			printTree(t->right);
		}
	}
};

#endif
