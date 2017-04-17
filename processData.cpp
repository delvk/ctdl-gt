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
	// TODO: allocate and initialize global data
	// return false if failed
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
//1A - 1B
bool intervalVisit(char *id,double &min, double &max, AVLNode<BusInfo_t>* &root)
{
	if (root == NULL) return false;
	if (root->data.latitude >= min && root->data.latitude <= max){
		if (root->data==id)
		return true;
		if(intervalVisit(id,min,max,root->left))return true;
		else return intervalVisit(id, min, max, root->right);
	}
	else if (root->data.latitude < min) return intervalVisit(id,min, max, root->right);
	else return intervalVisit(id,min, max, root->left);
}
//2A - 2B
int countPassingTimes(char *id, double &min, double &max, AVLNode<BusInfo_t>*root){
	if (root == NULL) return 0;
	if (root->data.latitude >= min && root->data.latitude <= max){
		if (root->data == id) return 1 + countPassingTimes(id, min, max, root->left) + countPassingTimes(id, min, max, root->right);
		else return countPassingTimes(id, min, max, root->left) + countPassingTimes(id, min, max, root->right);
	}
	else if (root->data.latitude < min) return countPassingTimes(id, min, max, root->right);
	else return countPassingTimes(id, min, max, root->left);
}
//3
int countPassingTimes(char*id,bool &isFound, double &lat_min, double &lat_max, double &long_min, double &long_max, AVLNode<BusInfo_t>*root){
	if (root == NULL) return 0;
	if (root->data.latitude >= lat_min && root->data.latitude <= lat_max){
		if (root->data == id && root->data.longitude >= long_min && root->data.longitude <= long_max){
			isFound = true;
			return 1 + countPassingTimes(id, isFound, lat_min, lat_max, long_min, long_max, root->left) + countPassingTimes(id, isFound, lat_min, lat_max, long_min, long_max, root->right);
	}
		else return countPassingTimes(id, isFound, lat_min, lat_max, long_min, long_max, root->left) + countPassingTimes(id, isFound, lat_min, lat_max, long_min, long_max, root->right);
	}
	else if (root->data.latitude < lat_min) return countPassingTimes(id, isFound, lat_min, lat_max, long_min, long_max, root->right);
	else return countPassingTimes(id, isFound, lat_min, lat_max, long_min, long_max, root->left);
}
//4
void pushToList(double &lat_min, double &lat_max, double &long_min, double &long_max,AVLNode<BusInfo_t> *root, L1List<BusInfo_t> &List){
	if (root == NULL) return;
	if (root->data.latitude >= lat_min && root->data.latitude <= lat_max) {
		List.push_back(root->data);
		pushToList(lat_min, lat_max, long_min, long_max,root->right,List);
		pushToList(lat_min, lat_max, long_min, long_max,root->left,List);
	}
	else if (root->data.latitude < lat_min) return pushToList(lat_min, lat_max, long_min, long_max, root->right,List);
	else return pushToList(lat_min, lat_max, long_min, long_max, root->left,List);
}
int numOfBusThrough(double &lat_min, double &lat_max, double &long_min, double &long_max, AVLNode<BusInfo_t>*root){
	L1List<BusInfo_t> List;
	pushToList(lat_min, lat_max, long_min, long_max, root, List);
	return List.count_dis();
}
//5
int numOfThrough(double &lat_min,double &lat_max,double &long_min,double &long_max, AVLNode<BusInfo_t>*root){
	if (root == NULL) return 0;
	if (root->data.latitude >= lat_min && root->data.latitude <= lat_max){
		if (root->data.longitude >= long_min, root->data.longitude <= long_max)
		return 1 + numOfThrough(lat_min, lat_max, long_min, long_max, root->left) + numOfBusThrough(lat_min, lat_max, long_min, long_max, root->right);
		else return numOfThrough(lat_min, lat_max, long_min, long_max, root->left) + numOfBusThrough(lat_min, lat_max, long_min, long_max, root->right);
	}
	else if (root->data.latitude < lat_min) return numOfThrough(lat_min, lat_max, long_min, long_max, root->right);
	else return numOfThrough(lat_min, lat_max, long_min, long_max, root->left);
}
//6
bool isPass(char *id,double &lat_min, double &lat_max, double &long_min, double &long_max, AVLNode<BusInfo_t>*root){
	if (root == NULL)return false;
	if (root->data.latitude >= lat_min && root->data.latitude <= lat_max){
		if (root->data == id && root->data.longitude >= long_min && root->data.longitude <= long_max)
			return true;
		else return isPass(id, lat_min, lat_max, long_min, long_max, root->left) || isPass(id, lat_min, lat_max, long_min, long_max, root->right);
	}
	else if (root->data.latitude < lat_min) return isPass(id, lat_min, lat_max, long_min, long_max, root->right);
	else return isPass(id, lat_min, lat_max, long_min, long_max, root->right);
}
//7
int passingRecord(char *id, bool &isFound, double &lat_min, double &lat_max, double &long_min, double &long_max, AVLNode<BusInfo_t>*root){
	if (root == NULL) return 0;
	if (root->data.latitude >= lat_min && root->data.latitude <= lat_max){
		if (root->data == id && root->data.longitude >= long_min && root->data.longitude <= long_max)
		{
			isFound = true;
			return 1 + passingRecord(id, isFound, lat_min, lat_max, long_min, long_max, root->left) + passingRecord(id, isFound, lat_min, lat_max, long_min, long_max, root->right);
		}
		else return passingRecord(id, isFound, lat_min, lat_max, long_min, long_max, root->left) + passingRecord(id, isFound, lat_min, lat_max, long_min, long_max, root->right);
	}
	else if (root->data.latitude < lat_min) return passingRecord(id, isFound, lat_min, lat_max, long_min, long_max, root->right);
	else return passingRecord(id, isFound, lat_min, lat_max, long_min, long_max, root->left);
}
/***********  Prototype  **********/
void display(L1List<BusInfo_t>& bList);
bool processEvent(busEvent_t& event, L1List<BusInfo_t>& bList, void* pGData) {
	/************************* THIS IS THE 2AVLTREE - myTree[0] save depend latlatide, other is longtitude ******************/
	AVLTree<BusInfo_t> **myTree = (AVLTree<BusInfo_t>**)pGData;
	if (myTree[0]->getRoot() == NULL){
		L1Item<BusInfo_t> *p = bList.getHead();
		L1List<BusInfo_t> swapList;
		while (p){
			myTree[0]->insert(p->data);
			swapList.push_back(p->data);
			p = p->pNext;
		}
		p = swapList.getHead();
		while (p){
			swapLatLong(p->data);// Swap
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
	switch (event.code[0])
	{
	case ('1') :
	{
				   if (event.code[1] == 'A'){
					   AVLNode<BusInfo_t> *pR = myTree[0]->getRoot();
					   getID(busID, 2, event.code);
					  /* if (!bList.find(busID)) cout << "Failed" << endl;
					   else{*/
						  // if (event.params[0] == NULL || event.params[1] == NULL) return false;
						   double x_lat = event.params[0];
						   double min = event.params[0] - event.params[1];
						   double max = event.params[0] + event.params[1];
						   if (intervalVisit(busID,min, max, pR)) cout << "Succeed" << endl;
						   else cout << "Failed" << endl;
					   //}
					   return true;
				   }
				   else if (event.code[1] == 'B'){
					   AVLNode<BusInfo_t> *pR = myTree[1]->getRoot();  //long
					   getID(busID, 2, event.code);
					  // if (!bList.find(busID)) cout << "Failed" << endl;
					  // else{
						  // if (event.params[0] == NULL || event.params[1] == NULL) return false;
						   double x_lat = event.params[0];
						   double min = event.params[0] - event.params[1];
						   double max = event.params[0] + event.params[1];
						   if (intervalVisit(busID,min, max, pR)) cout << "Succeed" << endl;
						   else cout << "Failed" << endl;
					   //}
					   return true;
				   }
				   else return false;
				   return true;
		}
	case ('2') :
	{
				   if (event.code[1] == 'A'){
					   getID(busID, 2, event.code);
						   AVLNode<BusInfo_t> *pRoot = myTree[0]->getRoot();
						   double min = event.params[0] - event.params[1];
						   double max = event.params[0] + event.params[1];
						   cout << countPassingTimes(busID, min, max, pRoot) << endl;//TODO: check wheather cout Failed
					   }
				   else if (event.code[1] == 'B'){
					   getID(busID, 2, event.code);
					   AVLNode<BusInfo_t> *pRoot = myTree[1]->getRoot();
					   double min = event.params[0] - event.params[1];
					   double max = event.params[0] + event.params[1];
					   cout << countPassingTimes(busID, min, max, pRoot) << endl;//TODO: check wheather cout Failed * if(!countPassing) if(find) cout<<0 else cout Failed 
				   }
				   else return false;
				   return true;
	}
	case('3') : 
	{
				  getID(busID,1,event.code);
				  double lat_max, lat_min, long_max, long_min;
				  lat_max = event.params[0] + event.params[2];
				  lat_min = event.params[0] - event.params[2];
				  long_max = event.params[1] + event.params[3];
				  long_min = event.params[1] - event.params[3];
				  AVLNode<BusInfo_t> *pR = myTree[0]->getRoot();
				  bool found = false;
				  int n = countPassingTimes(busID, found, lat_min, lat_max, long_min, long_max, pR);
				  if (found) cout << n << endl;
				  else cout << "Failed"<<endl;//TODO: check wheather cout Failed
				  return true;
	}
	case('4') :///SO LUONG PHUONG TIEN
	{
				   double lat_max, lat_min, long_max, long_min;
				   lat_max = event.params[0] + event.params[2];
				   lat_min = event.params[0] - event.params[2];
				   long_max = event.params[1] + event.params[3];
				   long_min = event.params[1] - event.params[3];
				   AVLNode<BusInfo_t> *pR = myTree[0]->getRoot();
				   cout << numOfBusThrough(lat_min, lat_max, long_min, long_max, pR) << endl;
				  return true;

	}
	case('5') :
	{
				  getID(busID, 1, event.code);
				  double lat_max, lat_min, long_max, long_min;
				  lat_max = event.params[0] + event.params[2];
				  lat_min = event.params[0] - event.params[2];
				  long_max = event.params[1] + event.params[3];
				  long_min = event.params[1] - event.params[3];
				  AVLNode<BusInfo_t> *pR = myTree[0]->getRoot();
				  cout << numOfThrough(lat_min, lat_max, long_min, long_max, pR) << endl;
				  return true;

	}
	case('6') :
	{
				  getID(busID, 1, event.code);
				  double lat_max, lat_min, long_max, long_min;
				  lat_max = event.params[0] + event.params[2];
				  lat_min = event.params[0] - event.params[2];
				  long_max = event.params[1] + event.params[3];
				  long_min = event.params[1] - event.params[3];
				  AVLNode<BusInfo_t> *pR = myTree[0]->getRoot();
				  if (isPass(busID, lat_min, lat_max, long_min, long_max, pR))cout << "Succeed" << endl;
				  else cout << "Failed" << endl;
				  return true;

	}
	case('7') :
	{
				  getID(busID, 1, event.code);
				  double lat_max, lat_min, long_max, long_min;
				  lat_max = event.params[0] + event.params[2];
				  lat_min = event.params[0] - event.params[2];
				  long_max = event.params[1] + event.params[3];
				  long_min = event.params[1] - event.params[3];
				  AVLNode<BusInfo_t> *pR = myTree[0]->getRoot();
				  bool found = false;
				  int n = passingRecord(busID, found, lat_min, lat_max, long_min, long_max, pR);
				  if (found) cout << n << endl;
				  else cout <<"Failed" << endl;
				  return true;

	}
	default:
		return false;
	}
	return false;
}
