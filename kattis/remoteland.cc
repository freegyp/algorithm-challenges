#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;

#define MOD 1000000007
#define umap unordered_map

long long pow(long long base,long long exponent){
	if(exponent==0)return 1;
	else if(exponent==1)return base;
	long long half = pow(base,exponent/2);
	long long additional = exponent%2==0?1:base;
	long long ans = (half*half)%MOD;
	return (ans*additional)%MOD;
}

long long countPrimes(long long prime,long long upper){
	if(upper<prime)return 0;
	return upper/prime + countPrimes(prime,upper/prime);
}

long long maxPerfectSquare(long long n,vector<int> &primeTable){
	long long ans=1;
	for(long long i=2;i<=n;i++){
		if(primeTable[i]){
			long long exponent = countPrimes(i,n);
			exponent -= exponent%2;
			ans = (ans*pow(i,exponent))%MOD;
		}
	}
	return ans;
}

void initPrimeTable(vector<int> &table){
	table[0]=0;table[1]=0;
	for(int i=2;i<table.size();i++){
		if(table[i]){
			for(int j=2*i;j<table.size();j+=i){
				table[j] = 0;
			}
		}
	}
}

int main(){
	vector<int> isPrime(10000001,1);
	initPrimeTable(isPrime);
	while(true){
		long long n;cin>>n;
		if(n==0)break;
		cout<<maxPerfectSquare(n,isPrime)<<endl;
	}
	return 0;
}