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
inline bool operator==(BusInfo_t& lhs, char* rhs) {
	return strcmp(lhs.id, rhs) == 0;
}
inline bool operator==(char* lhs, BusInfo_t& rhs)  {
	return strcmp(rhs.id, lhs) == 0;
}
inline bool operator==(BusInfo_t& lhs, BusInfo_t& rhs) {
	return strcmp(lhs.id, rhs.id) == 0;
}
inline bool operator!=(BusInfo_t& lhs, char* rhs) {
	return !(lhs == rhs);
}
inline bool operator!=(char* lhs, BusInfo_t& rhs)  {
	return !(rhs == lhs);
}
inline bool operator!=(BusInfo_t& lhs, BusInfo_t& rhs) {
	return !(lhs == rhs);
}
inline bool operator < (BusInfo_t& lhs, BusInfo_t& rhs){
	return (lhs.latitude < rhs.latitude);
}
inline bool operator > (BusInfo_t& lhs, BusInfo_t& rhs){
	return (lhs.latitude > rhs.latitude);
}
inline bool operator >= (BusInfo_t& lhs, BusInfo_t& rhs){
	return (lhs.latitude >= rhs.latitude);
}
inline bool operator <= (BusInfo_t& lhs, BusInfo_t& rhs){
	return (lhs.latitude <= rhs.latitude);
}
bool initBusGlobalData(void** pGData) {
	AVLTree<BusInfo_t> **a = new AVLTree<BusInfo_t>*();
	a[0] = new AVLTree<BusInfo_t>();
	a[1] = new AVLTree<BusInfo_t>();
	*pGData = (void*)a;
	return true;
}

void releaseBusGlobalData(void* pGData) {
	// TODO: do your cleanup, left this empty if you don't have any dynamically allocated data
	AVLTree<BusInfo_t> **a = (AVLTree<BusInfo_t>**)pGData;
	a[0]->~AVLTree();
	a[1]->~AVLTree();
}
void getID(char *des, int idx, char *source){
	strcpy(des, source + idx*sizeof(char));
}
void swapLatLong(BusInfo_t &bus){
	double temp = bus.latitude;
	bus.latitude = bus.longitude;
	bus.longitude = temp;
}
bool isPass(double &X, double &Y, double &delta){
	return (Y - delta <= X && Y + delta >= X);
}
bool intervalVisit(double &a, double &b, AVLNode<BusInfo_t>* &root)
{
	if (root == NULL) return false;
	if (root->data.latitude >= a && root->data.latitude <= b){
		return true;
		//intervalVisit(a, b, root->left);
		//intervalVisit(a, b, root->right);
	}
	else if (root->data.latitude < a) return intervalVisit(a, b, root->right);
	else return intervalVisit(a, b, root->left);
}
bool processEvent(busEvent_t& event, L1List<BusInfo_t>& bList, void* pGData) {
	/*************************THIS IS THE 2AVLTREE - myTree[0] save depend latlatide, other is longtitude******************/
	AVLTree<BusInfo_t> **myTree = (AVLTree<BusInfo_t>**)pGData;
	if (myTree[0]->getRoot() == NULL){
		L1Item<BusInfo_t> *p = bList.getHead();
		L1List<BusInfo_t> swapList;
		while (p){
			myTree[0]->insert(p->data);
			swapList.push_back(p->data);
			p = p->pNext;
		}
		swapList.traverse(swapLatLong);
		p = swapList.getHead();
		while (p){
			myTree[1]->insert(p->data);
			p = p->pNext;
			swapList.removeHead();
		}
		//myTree[1]->traverseNLR(swapLatLong);//Swap again to gain right value
	}
	/************************************************* end 2 Tree**********************************************************/
	//1AXXYXXXXX Y_lat Delta_lat
	cout << event.code << ": ";
	char busID[ID_MAX_LENGTH];
	BusInfo_t temp;
	switch (event.code[0])
	{
	case ('1') :
	{
				   if (event.code[1] == 'A'){
					   AVLNode<BusInfo_t> *pR = myTree[0]->getRoot();
					   getID(busID, 2, event.code);
					   if (!bList.find(busID)) cout << "Failed" << endl;
					   else{
						   if (event.params[0] == NULL || event.params[1] == NULL) return false;
						   double x_lat = event.params[0];
						   double a = x_lat - event.params[1];
						   double b = x_lat + event.params[1];
						   if (intervalVisit(a, b, pR)) cout << "Succeed" << endl;
						   else cout << "Failed" << endl;
					   }
					   return true;
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
