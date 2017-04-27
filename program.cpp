#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include<math.h>
#include <stdlib.h> 
using namespace std;
#define NUM_SIMPLES 20000
#define SIMPLE_SIZE 3
#define PARAMS_SIZE 5
#define KHOANG_CACH 10
struct data{
	double x;
	double t;
};
void printData(data &a){
	cout << a.x << " " << a.t << endl;
}
void displayData(data *a, int size){
	if (size == 0) cout << "Emty List" << endl;
	for (int i = 0; i < size; i++){
		cout << a[i].x << " " << a[i].t << endl;
	}
}
void loadData(double *params, data *dataIn, int &simples_num){
	string str;
	string str_value;
	int n = 0;
	int temp = 0;
	simples_num = 0;
	while (getline(cin, str)){
		if (n>2 && n<8){
			stringstream scin1(str);
			scin1 >> str_value;
			scin1 >> params[temp++];
		}
		else if (n>10){
			stringstream scin1(str);
			scin1 >> dataIn[simples_num].x;
			scin1 >> dataIn[simples_num].t;
			simples_num++;
		}
		n++;
	}
}
void writeData(ofstream &f, double *heso, double &saiso, double *bieudo){
	f << heso[0] << setw(10) << heso[1] << setw(10) << saiso;
	for (int i = 0; i < KHOANG_CACH; i++)f << setw(10) << bieudo[i];
	f << endl;
}
void write(double *heso, double &saiso, double *bieudo){
	cout << heso[0] << setw(10) << heso[1] << setw(10) << saiso;
	for (int i = 0; i < KHOANG_CACH; i++)cout << setw(10) << bieudo[i];
	cout << endl;
}

double *giatridubao(int size, double *params, data *TRN){
	int STOP_NUM = (int)params[0];
	double gA, gB, a, b, alpha;
	a = params[2]; b = params[3]; alpha = params[1];
	int i = 0;
	while (i < STOP_NUM){
		gA = 0;
		gB = 0;
		for (int j = 0; j < size; j++) {
			gA += (a*TRN[j].x + b - TRN[j].t)*TRN[j].x;//ga
			gB += a*TRN[j].x + b - TRN[j].t;//gb
		}
		double g = sqrt(gA*gA + gB*gB);
		gA /= g;
		gB /= g;
		a -= alpha*gA;
		b -= alpha*gB;
		i++;
	}
	double *heso = new double[2];
	heso[0] = a; heso[1] = b;
	return heso;
}
double *mangbieudien(int D, double *e, double max, double min){
	double m[KHOANG_CACH];
	double width = (max - min) / 10;
	for (int k = 1; k < KHOANG_CACH; k++) m[k] = min + k*width;
	double *soloi = new double[KHOANG_CACH];
	for (int z = 0; z < KHOANG_CACH; z++)soloi[z] = 0;
	int tongsoloi = 0;
	for (int i = 0; i < D; i++){
		if (e[i] >= min && e[i] < m[1]) soloi[0]++;
		else if (e[i] >= m[1] && e[i] < m[2]) soloi[1]++;
		else if (e[i] >= m[2] && e[i] < m[3]) soloi[2]++;
		else if (e[i] >= m[3] && e[i] < m[4]) soloi[3]++;
		else if (e[i] >= m[4] && e[i] < m[5]) soloi[4]++;
		else if (e[i] >= m[5] && e[i] < m[6]) soloi[5]++;
		else if (e[i] >= m[6] && e[i] < m[7]) soloi[6]++;
		else if (e[i] >= m[7] && e[i] < m[8]) soloi[7]++;
		else if (e[i] >= m[8] && e[i] < m[9]) soloi[8]++;
		else if (e[i] >= m[9] && e[i] <= max) soloi[9]++;
	}
	for (int z = 0; z < KHOANG_CACH; z++)tongsoloi += soloi[z];
	for (int z = 0; z < KHOANG_CACH; z++) soloi[z] /= (double)tongsoloi;
	return soloi;
}
double *bieudotansuat(int size, double *params, double *heso, data *TST, double &Ermsd){
	double *e = new double[size];
	double dhrA, dhrB, a, b, alpha;
	double __e = 0, phi = 0;
	Ermsd = 0;
	a = heso[0]; b = heso[1]; alpha = params[1];
	for (int j = 0; j < size; j++) {
		e[j] = a * TST[j].x + b - TST[j].t;
		__e += e[j];
		Ermsd += e[j] * e[j];
	}
	Ermsd = sqrt(Ermsd / (double)size);
	__e /= (double)size;//e trung binh
	for (int i = 0; i < size; i++){
		double p = e[i] - __e;
		phi += p*p;
	}
	phi = sqrt(phi / (double)(size));//
	double V_min = __e - 3 * phi;
	double V_max = __e + 3 * phi;
	double *mang = mangbieudien(size, e, V_max, V_min);
	return mang;
}

int main(){
	double params[PARAMS_SIZE];
	data *dataIn = new data[NUM_SIMPLES];
	int M = 0;
	cout << fixed << right << setprecision(5);
	loadData(params, dataIn, M);
	int K = (int)params[4];
	int D = M / K;
	int temp = D + M%K;
	double *heso;
	//step1
	for (int i = 1; i <= K; i++){
		//cout << "O lan thu " << i << ": " << endl;
		if (i != K){
			data *TST = new data[D];
			data *TRN = new data[M - D];
			int j = 0; int t = 0; int z = 0;
			while (j < M){
				if (j >= (i - 1)*D && j< i*D){
					TST[t] = dataIn[j];
					t++; j++;
				}
				else {
					TRN[z] = dataIn[j];
					z++; j++;
				}
			}
			heso = giatridubao(M - D, params, TRN);//step2
			double ssTB;//step 3
			double *mang = bieudotansuat(D, params, heso, TST,ssTB);
			write(heso, ssTB, mang);
			//cout << fixed << right << setprecision(5);
			//cout << "--------------------------------------------------------------" << endl;
			//cout << "Lan " << i << endl;
			//cout << "--------------------------------------------------------------" << endl;
			//cout << "He so:\n" << "a: " << heso[0] << endl<< "b: " << heso[1] << endl;
			//cout << "Sai so trung binh: " << ssTB << endl;
			//cout << "Bieu do tan suat: " << endl;
			//for (int z = 0; z < KHOANG_CACH; z++)cout << mang[z] << " ";
			//cout << endl;
			delete[]TST;
			delete[]heso;
			delete[]mang;
			delete[]TRN;
		}
		else {
			data *TST = new data[temp];
			data *TRN = new data[M - temp];
			int j = 0;
			while (j < M - temp){
				TRN[j] = dataIn[j];
				j++;
			}
			int z = 0;
			while (j<M)
			{
				TST[z++] = dataIn[j++];
			}
			heso = giatridubao(M - temp, params, TRN);//step2
			double ssTB;//step 3
			double *mang = bieudotansuat(temp, params, heso, TST,ssTB);
			cout << fixed << right << setprecision(5);
			cout << heso[0] << setw(10) << heso[1] << setw(10) << ssTB;
			for (int t = 0; t < KHOANG_CACH; t++)cout << setw(10) << mang[t];
			//cout << fixed << right << setprecision(5);
			//cout << "--------------------------------------------------------------" << endl;
			//cout << "Lan " << i << endl;
			//cout << "--------------------------------------------------------------" << endl;
			//cout << "He so:\n" << "a: " << heso[0] << endl << "b: " << heso[1] << endl;
			//cout << "Sai so trung binh: " << ssTB << endl;
			//cout << "Bieu do tan suat: " << endl;
			//for (int z = 0; z < KHOANG_CACH; z++)cout << mang[z] << " ";
			//cout << endl;
			delete[]TST;
			delete[]TRN;
			delete[]heso;
			delete[]mang;
		}

	}
	delete[]dataIn;
	return 0;
}