/*
* ==========================================================================================
* Name        : processData.cpp
* Description : student code for Assignment 2 - Data structures and Algorithms - Spring 2017
* ==========================================================================================
*/
#include <iostream>

#include "eventLib.h"
#include "dbLib.h"

using namespace std;

#define GPS_DISTANCE_ERROR 0.005
#define X 2
bool initBusGlobalData(void** pGData) {
	// TODO: allocate and initialize global data
	// return false if failed
	/*AVLTree<int> **myTree=new AVLTree<int> *[X];
	myTree[0] = new AVLTree<int>();
	myTree[1] = new AVLTree<int>();
	pGData = (void**)myTree;*/
	
	AVLTree<int> *a = new AVLTree<int>();
	
	*pGData = (void*)a;
	return true;
}

void releaseBusGlobalData(void* pGData) {
	// TODO: do your cleanup, left this empty if you don't have any dynamically allocated data
	AVLTree<int> *a = (AVLTree<int>*)pGData;
	a->~AVLTree();
}

bool processEvent(busEvent_t& event, L1List<BusInfo_t>& bList, void* pGData) {
	int t = 80;
	AVLTree<int> *a = (AVLTree<int>*)pGData;
	if (a->getRoot() == NULL){
		cout << "Emty tree" << endl;
		a->insert(t);
	}
	else {
		a->printTree();
		a->insert(t);
	}
	//cout << *(int*)(pGData) << endl;
	//1AXXYXXXXX Y_lat Delta_lat
	switch (event.code[0])
	{
	case ('1') :
	{
				   if (event.code[1] == 'A'){
					   cout << "1A" << endl;
				   }
				   else if (event.code[1] == 'B'){
					   cout << "1B" << endl;
				   }
				   else return false;
				   return true;
		}
	case ('2') :
	{
				   if (event.code[1] == 'A'){
					   cout << "2A" << endl;
				   }
				   else if (event.code[1] == 'B'){
					   cout << "2B" << endl;
				   }
				   else return false;
				   return true;
	}
	case('3') : 
	{
				  cout << "3" << endl;
					return true;
	}
	case('4') :
	{
				  cout << "4" << endl;
				  return true;

	}
	case('5') :
	{
				  cout << "5" << endl;
				  return true;

	}
	case('6') :
	{
				  cout << "6" << endl;
				  return true;

	}
	case('7') :
	{
				  cout << "7" << endl;
				  return true;

	}
	default:
		return false;
	}
	return false;
}
