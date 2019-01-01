#include<iostream>
#include<vector>
#include<cstdlib>
using namespace std;

int main(){
	int n,ans=0;cin>>n;
	vector<int> table(2001,0);
	table[0] = 1;
	for(int i=0;i<n;i++){
		int p;cin>>p;
		vector<int> newTable(2001,0);
		for(int j=0;j<=2000;j++){
			if(table[j]&&(j+p<=2000)){
				newTable[j+p] = 1;
			}
		}
		for(int j=0;j<=2000;j++)table[j] |= newTable[j];
	}
	for(int i=0;i<=2000;i++){
		if(table[i] && abs(i-1000)<=abs(ans-1000))ans = i;
	}
	cout<<ans<<endl;
	return 0;
}