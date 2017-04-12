#ifndef LIST_H
#define LIST_H
using namespace std;
template <class T>
struct Node {
	T data;
	Node<T> *next;
};

template <class T>
void PrintLinkedList(Node<T> *pHead) {
	Node<T> *temp = pHead;
	while (temp != NULL) {
		cout << temp->data << " ";
		temp = temp->next;
	}
	cout << "\n";
}

template <class T>
Node<T>* ConvertToLinkedList(T list[], int size) {
	Node<T> *root = NULL;

	Node<T> *travesalNode = NULL;
	for (int i = 0; i < size; i++){
		T data = list[i];

		Node<T> *newNode = new Node<T>();
		newNode->data = data;
		newNode->next = NULL;

		if (travesalNode == NULL){
			root = newNode;
			travesalNode = root;
		}
		else {
			travesalNode->next = newNode;
			travesalNode = newNode;
		}
	}

	return root;
}

template <class T>
void ReleaseList(Node<T> *&root) {
	while (root != NULL){
		Node<T> *tempNode = root;
		root = root->next;
		delete(tempNode);
	}
}

template <class T>
class Stack {
public:
	Stack();
	~Stack();

	void Push(T dataIn);
	int Pop(T &dataOut);
	int Top(T &dataOut);

	void Clear();

	int IsEmpty();

	void Print2Console();

private:
	Node<T> *top;
	int count;
};

template <class T>
Stack<T>::Stack() {
	this->top = NULL;
	this->count = 0;
}

template <class T>
Stack<T>::~Stack() {
	this->Clear();
}

template <class T>
void Stack<T>::Push(T dataIn) {
	Node<T>* pNew = new Node<T>();

	pNew->data = dataIn;
	pNew->next = this->top;
	this->top = pNew;
	this->count++;
}

template <class T>
int Stack<T>::Pop(T &dataOut) {
	if (this->count == 0) {
		return 0;
	}
	Node<T> *dltPtr = this->top;
	dataOut = dltPtr->data;
	this->top = dltPtr->next;
	this->count--;
	delete dltPtr;
	return 1;
}

template <class T>
int Stack<T>::Top(T &dataOut) {
	if (this->count == 0) {
		return 0;
	}
	dataOut = this->top->data;
	return 1;
}

template <class T>
void Stack<T>::Clear() {
	Node<T> *temp;
	while (this->top != NULL) {
		temp = this->top;
		this->top = this->top->next;
		delete temp;
	}
	this->count = 0;
}

template <class T>
int Stack<T>::IsEmpty() {
	return (this->count == 0);
}

template <class T>
void Stack<T>::Print2Console() {
	Node<T> *temp = this->top;
	while (temp != NULL) {
		cout << temp->data << " ";
		temp = temp->next;
	}
	cout << "\n";
}

template <class T>
class Queue {
public:
	Queue();
	~Queue();

	void EnQueue(T dataIn);
	int DeQueue(T &dataOut);
	int GetQueueFront(T &dataOut);
	int GetQueueRear(T &dataOut);

	void Clear();

	int IsEmpty();

	void Print2Console();

private:
	Node<T> *front, *rear;
	int count;
};

template <class T>
Queue<T>::Queue() {
	this->count = 0;
	this->front = NULL;
	this->rear = NULL;
}

template <class T>
Queue<T>::~Queue() {
	this->Clear();
}

template <class T>
void Queue<T>::EnQueue(T dataIn) {
	Node<T> *pNew = new Node<T>();
	pNew->data = dataIn;
	pNew->next = NULL;

	if (this->count == 0) {
		this->front = pNew;
	}
	else {
		this->rear->next = pNew;
	}

	this->rear = pNew;
	this->count++;
}

template <class T>
int Queue<T>::DeQueue(T &dataOut) {
	if (this->count == 0) {
		return 0;
	}
	Node<T> *dltPtr = this->front;
	dataOut = dltPtr->data;
	if (this->count == 1) {
		this->rear = NULL;
	}
	this->front = this->front->next;
	delete dltPtr;
	this->count--;
	return 1;
}

template <class T>
int Queue<T>::GetQueueFront(T &dataOut) {
	if (this->count == 0) {
		return 0;
	}
	dataOut = this->front->data;
	return 1;
}

template <class T>
int Queue<T>::GetQueueRear(T &dataOut) {
	if (this->count == 0) {
		return 0;
	}
	dataOut = this->rear->data;
	return 1;
}

template <class T>
void Queue<T>::Clear() {
	Node<T> *temp;

	while (this->front != NULL) {
		temp = this->front;
		this->front = this->front->next;
		delete temp;
	}
	this->front = NULL;
	this->rear = NULL;
	this->count = 0;
}

template <class T>
int Queue<T>::IsEmpty() {
	return (this->count == 0);
}

template <class T>
void Queue<T>::Print2Console() {
	Node<T> *temp = this->front;

	while (temp != NULL) {
		cout << temp->data << " ";
		temp = temp->next;
	}
	cout << "\n";
}
#endif
