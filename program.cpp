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

		//skip ---: read form file or console

		if (n>2 && n<8){
			stringstream scin1(str);
			scin1 >> str_value;
			scin1 >> params[temp++];
		}//get a parameter
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
	//y=a*x+b
	//x->0 t->1

	int STOP_NUM = (int)params[0];
	//double *y = new double[STOP_NUM];
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
		gA = gA / labs(gA + gB);
		gB = gB / labs(gA + gB);
		a -= alpha*gA;
		b -= alpha*gB;
		i++;
	}
	double *heso = new double[2];
	heso[0] = a; heso[1] = b;
	return heso;
}
double saisoTB(int size, double *heso, data *TST){
	double sum = 0, temp = 0;
	for (int i = 0; i < size; i++){
		temp = (heso[0] * TST[i].x + heso[1] - TST[i].t);
		sum += temp*temp;
	}
	return sqrt(sum / size);
}
double *mangbieudien(int D, double *e, double max, double min){
	double *m = new double[KHOANG_CACH];
	int i = 0;// 1 2 3 4 5 6 7 8 9 0
	for (int j = 0; j < KHOANG_CACH; j++) m[j] = 0;
	double width = max / min;
	while (i < D){
		if (min <= e[i] && e[i] < min + width) m[0]++;
		else if (min + width <= e[i] && e[i] < 2 * width) m[1]++;
		else if (min + 2 * width <= e[i] && e[i] < min + 3 * width) m[2]++;
		else if (min + 3 * width <= e[i] && e[i] < min + 4 * width) m[3]++;
		else if (min + 4 * width <= e[i] && e[i] < min + 5 * width) m[4]++;
		else if (min + 5 * width <= e[i] && e[i] < min + 6 * width) m[5]++;
		else if (min + 6 * width <= e[i] && e[i] < min + 7 * width) m[6]++;
		else if (min + 7 * width <= e[i] && e[i] < min + 8 * width) m[7]++;
		else if (min + 8 * width <= e[i] && e[i] < min + 9 * width) m[8]++;
		else if (min + 9 * width <= e[i] && e[i] <= max) m[9]++;
		i++;
	}
	double sum = 0;
	for (int j = 0; j < KHOANG_CACH; j++){
		sum += m[j];
	}
	for (int j = 0; j < KHOANG_CACH; j++) m[j] = m[j] / sum;
	return m;
}
double *bieudotansuat(int size, double *params, double *heso, data *TST){
	double *e = new double[size];
	double dhrA, dhrB, a, b, alpha;
	double __e = 0, phi = 0;
	a = heso[0]; b = heso[1]; alpha = params[1];
	for (int j = 0; j < size; j++) {
		e[j] = a * TST[j].x + b - TST[j].t;
		__e += e[j];
	}
	__e /= size;//e trung binh
	for (int i = 0; i < size; i++)
		phi += pow(e[i] - __e, 2);
	phi /= size;
	phi = sqrt(phi);
	double V_min = __e - 3 * phi;
	double V_max = __e + 3 * phi;
	double *mang = mangbieudien(size, e, V_max, V_min);
	return mang;
}

int main(){
	double params[PARAMS_SIZE];
	data *dataIn = new data[NUM_SIMPLES];//MAU DU LIEU DUOC LUU O DAY
	int M = 0;
	cout << fixed << right << setprecision(5);
	loadData(params, dataIn, M);
	/*ofstream outputFile;
	initalOutput(outputFile);*/
	//cout << "Danh sach tham so dau vao: " << endl;
	//for (int i = 0; i < PARAMS_SIZE; i++) cout << params[i] << endl;
	//cout << "--------------------------------------------------------------" << endl;
	//cout << "Danh sach mau so lieu:" << endl;
	//displayData(dataIn,M);
	//cout << "--------------------------------------------------------------" << endl;
	int K = (int)params[4];
	int D = M / K;
	int temp = D + M%K;
	/*cout << "Tong mau (M): " << M << endl;
	cout << "So ngan(K): " << K << endl;
	cout << "Du lieu moi ngan: " << D << endl;
	cout << "Ngan cuoi co: " << temp << endl;*/
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
			double ssTB = saisoTB(D, heso, TST);//step 3
			double *mang = bieudotansuat(D, params, heso, TST);
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
			double ssTB = saisoTB(temp, heso, TST);//step 3
			double *mang = bieudotansuat(temp, params, heso, TST);
			cout << fixed << right << setprecision(5);
			cout << heso[0] << setw(10) << heso[1] << setw(10) << ssTB;
			for (int t = 0; t < KHOANG_CACH; t++)cout << setw(10) << mang[i];
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