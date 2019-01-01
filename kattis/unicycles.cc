#include<iostream>
#include<cstdlib>
#include<algorithm>
#include<vector>
using namespace std;
#define inf 1000000000

int main(){
	int m;
	while(cin>>m){
		int n;cin>>n;
		int *marks = (int*)malloc(sizeof(int)*n);
		int *table = (int*)malloc(sizeof(int)*(1<<n));
		for(int i=0;i<n;i++)cin>>marks[i];
		sort(marks,marks+n);
		for(int i=0;i<(1<<n);i++)table[i] = inf;
		for(int i=0;i<(1<<n);i++){
			int diff=-1,pre=-1,unidiff=1;
			int rng = 0;
			vector<int> submarks;
			while((1<<rng)<=i){
				if(((1<<rng)&i)>0){
					submarks.push_back(marks[rng]);
					if(diff<0){
						if(pre<0)pre=marks[rng];
						else{
							diff = marks[rng]-pre;
							pre = marks[rng];
						}
					}else{
						if(marks[rng]-pre==diff)pre = marks[rng];
						else{
							unidiff = 0;
							break;
						}
					}
				}
				rng++;
			}
			if(unidiff){
				if(diff==-1 || (submarks[0]-diff<0 && submarks.back()+diff>=m))table[i] = 1;
			}
		}
		for(int i=0;i<(1<<n);i++){
			for(int j=0;j<(1<<n);j++){
				table[i|j] = min(table[i|j],table[i]+table[j]);
			}
		}
		cout<<table[(1<<n)-1]<<endl;
	}
	return 0;
}