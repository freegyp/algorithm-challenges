#include<iostream>
#include<unordered_map>
#include<vector>
#include<utility>
using namespace std;
#define umap unordered_map

int main(){
	float l,w,r;
	int n;
	cin>>l>>w>>n>>r;
	vector<pair<float,float> > walls;
	walls.push_back(make_pair(-l/2.0,0.0));
	walls.push_back(make_pair(l/2.0,0.0));
	walls.push_back(make_pair(0.0,-w/2.0));
	walls.push_back(make_pair(0.0,w/2.0));
	vector<int> bitSet(16,0);
	for(int i=0;i<n;i++){
		float x,y;cin>>x>>y;
		int mask=0;
		for(int j=0;j<4;j++){
			auto wall = walls[j];
			if((x-wall.first)*(x-wall.first)+(y-wall.second)*(y-wall.second)<=r*r){
				mask |= (1<<j);
			}
		}
		if(mask!=0)bitSet[mask]=1;
	}
	umap<int,int> masks;
	for(int i=0,j=0;i<16;i++){
		if(bitSet[i])masks[(1<<(j++))] = i;
	}
	int ans=5;
	for(int i=1;i<(1<<(int)masks.size());i++){
		int j=i,res=0,digits=0;
		while(j){
			res |= masks[j&-j];
			digits++;
			j -= j&-j;
		}
		if(res==15){
			ans = ans<digits?ans:digits;
		}
	}
	if(ans>4)cout<<"Impossible"<<endl;
	else cout<<ans<<endl;
	return 0;
}