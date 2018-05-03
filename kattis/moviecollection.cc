#include<iostream>
#include<cstdlib>
#include<algorithm>
using namespace std;

int main(){
	int *BIT = (int*)malloc(200001*sizeof(int));
	int *numPos = (int*)malloc(100001*sizeof(int));
	int tt;cin>>tt;
	for(int t=0;t<tt;t++){
		int m,r,curFill=100000;cin>>m>>r;
		fill(BIT,BIT+200001,0);
		fill(numPos,numPos+100001,0);
		for(int i=1;i<=m;i++){
			for(int j=100000+i;j<=200000;j+=j&-j)BIT[j]++;
			numPos[i] = 100000+i;
		}
		for(int i=0;i<r;i++){
			int num,total=0;cin>>num;
			for(int j=numPos[num]-1;j>0;j-=j&-j)total+=BIT[j];
			for(int j=numPos[num];j<=200000;j+=j&-j)BIT[j]--;
			numPos[num] = curFill--;
			for(int j=numPos[num];j<=200000;j+=j&-j)BIT[j]++;
			cout<<total;
			if(i!=r-1)cout<<" ";
			else cout<<endl;
		}
	}
	return 0;
}