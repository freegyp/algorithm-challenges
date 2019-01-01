#include<iostream>
#include<algorithm>
#include<cstdlib>
using namespace std;
#define inf 1000000000

void tableInit(int ***table,int *times,int n,int t,int g){
	int *cdf = (int*)malloc(sizeof(int)*n*2+1);
	cdf[0] = 0;
	for(int i=0;i<2*n;i++)cdf[i+1] = cdf[i]+times[i%n]+t*(i/n);
	for(int offset=0;(1<<offset)<=g;offset++){
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				table[offset][i][j] = inf;
			}
		}
		if(offset==0){
			for(int i=0;i<n;i++){
				for(int j=0;j<n;j++){
					int jj = j<i?j+n:j;
					int base = j<i?times[j]+t:times[j];
					base *= ((j-i+n+1)%n==0)?n:((j-i+n+1)%n);
					table[offset][i][j] = base - (cdf[jj+1]-cdf[i]);
				}
			}
		}else{
			for(int i=0;i<n;i++){
				for(int j=0;j<n;j++){
					int jj = j<i?j+n:j;
					if(i==j)table[offset][i][j] = 0;
					for(int k=i;k<jj;k++){
						table[offset][i][j] = min(table[offset][i][j],table[offset-1][i][k%n]+table[offset-1][(k+1)%n][jj%n]);
					}
				}
			}
		}
	}
}

int main(){
	int *offset = (int*)malloc(sizeof(int)*500),***table,***ansTable,*times;
	for(int i=0;i<10;i++)offset[1<<i] = i;
	int n,t,g,state=0;cin>>n>>t>>g;
	t*=2;
	times = (int*)malloc(sizeof(int)*n);
	table = (int***)malloc(sizeof(int**)*10);
	ansTable = (int***)malloc(sizeof(int**)*2);
	for(int i=0;i<10;i++){
		table[i] = (int**)malloc(sizeof(int*)*n);
		for(int j=0;j<n;j++){
			table[i][j] = (int*)malloc(sizeof(int)*n);
		}
		if(i<2){
			ansTable[i] = (int**)malloc(sizeof(int*)*n);
			for(int j=0;j<n;j++){
				ansTable[i][j] = (int*)malloc(sizeof(int)*n);
				for(int k=0;k<n;k++){
					ansTable[i][j][k] = inf;
				}
			}
		}
	}
	for(int i=0;i<n;i++){
		cin>>times[i];
		times[i] %= t;
	}
	sort(times,times+n);
	tableInit(table,times,n,t,g);
	for(int gg=g;gg>0;gg-=gg&(-gg)){
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				ansTable[state^1][i][j] = inf;
			}
		}
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				int jj = j<i?j+n:j;
				if(i==j)ansTable[state^1][i][j] = 0;
				if(gg==g){
					ansTable[state^1][i][j] = table[offset[gg&(-gg)]][i][j];
				}else{
					for(int k=i;k<jj;k++){
						ansTable[state^1][i][j] = min(ansTable[state^1][i][j],ansTable[state][i][k%n]+table[offset[gg&(-gg)]][(k+1)%n][jj%n]);
						ansTable[state^1][i][j] = min(ansTable[state^1][i][j],table[offset[gg&(-gg)]][i][k%n]+ansTable[state][(k+1)%n][jj%n]);
					}
				}
			}
		}
		state ^= 1;
	}
	int ans=inf;
	for(int i=0;i<n;i++){
		ans = min(ans,ansTable[state][i][(i-1+n)%n]);
	}
	cout<<ans<<endl;
	return 0;
}