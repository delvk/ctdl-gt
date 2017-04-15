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
void swapLatLong(BusInfo_t &bus){
	double temp = bus.latitude;
	bus.latitude = bus.longitude;
	bus.longitude = temp;
}
bool processEvent(busEvent_t& event, L1List<BusInfo_t>& bList, void* pGData) {
	
	AVLTree<BusInfo_t> **a = (AVLTree<BusInfo_t>**)pGData;
	if (a[0]->getRoot() == NULL){
		cout << "Emty tree" << endl;
		L1Item<BusInfo_t> *p = bList.getHead();
		L1List<BusInfo_t> swapList;
		while (p){
			a[0]->insert(p->data);
			swapList.push_back(p->data);
			p = p->pNext;
		}
		swapList.traverse(swapLatLong);
		p = swapList.getHead();

		/*for (int i = 0; i < 9; i++) {
			cout << swapList[i].longitude << " "<<  swapList[i].latitude << endl;
		}*/
		while (p){
			a[1]->insert(p->data);	
			p = p->pNext;
			swapList.removeHead();
		}
		cout << swapList.getSize() << endl;
	}
	//cout << *(BusInfo_t*)(pGData) << endl;
	//1AXXYXXXXX Y_lat Delta_lat
	switch (event.code[0])
	{
	case ('1') :
	{
				   if (event.code[1] == 'A'){
					   cout << "1A" << endl;
					   a[0]->traverseNLR(printBusInfo);
				   }
				   else if (event.code[1] == 'B'){
					   cout << "1B" << endl;
					   a[1]->traverseNLR(printBusInfo);
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
