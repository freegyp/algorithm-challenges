#include<iostream>
#include<cstdlib>
#include<cmath>
using namespace std;

int main(){
	double *table = (double*)malloc(sizeof(double)*1000001);
	table[0] = 1.0;
	for(int i=1;i<=1000000;i++){
		table[i] = table[i-1] + log10((double)i);
	}
	int i;
	while(cin>>i){
		cout<<(int)table[i]<<endl;
	}
	return 0;
}