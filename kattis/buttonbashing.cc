#include<iostream>
#include<cstdlib>
#include<vector>
#include<algorithm>
#include<deque>
using namespace std;

int main(){
	int tt;cin>>tt;
	for(int t=0;t<tt;t++){
		int n,time;cin>>n>>time;
		vector<int> offsets;
		for(int i=0;i<n;i++){
			int num;cin>>num;
			offsets.push_back(num);
		}
		int *distance = (int*)malloc(sizeof(int)*3601);
		for(int i=1;i<=3600;i++){
			distance[i] = -1;
		}
		distance[0] = 0;
		deque<int> queue;
		queue.push_back(0);
		while(queue.size()>0 && distance[time]<0){
			int cur = queue.front();queue.pop_front();
			for(int dPod:offsets){
				int neigh = cur+dPod;
				if(neigh<0)neigh = 0;
				else if(neigh>3600)neigh = 3600;
				if(distance[neigh]<0){
					distance[neigh] = distance[cur]+1;
					queue.push_back(neigh);
				}
			}
		}
		int actual = time;
		while(actual<=3600 && distance[actual]<0)actual++;
		cout<<distance[actual]<<" "<<actual-time<<endl;
	}
	return 0;
}