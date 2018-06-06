#include<iostream>
#include<cstdlib>
#include<algorithm>
using namespace std;

int main(){
	int n,m;
	while(cin>>n>>m){
		int *table = (int*)malloc(sizeof(int)*(n+1));
		int *offsets = (int*)malloc(sizeof(int)*m);
		for(int i=0;i<m;i++){
			cin>>offsets[i];
		}
		sort(offsets,offsets+m);
		table[0] = 0;
		for(int i=1;i<=n;i++){
			int res = 0;
			for(int j=0;j<m;j++){
				if(i-offsets[j]>=0){
					if(table[i-offsets[j]]==0){
						res = 1;
						break;
					}
				}else{
					break;
				}
			}
			table[i] = res;
		}
		if(table[n])cout<<"Stan wins"<<endl;
		else cout<<"Ollie wins"<<endl;
	}
	return 0;
}