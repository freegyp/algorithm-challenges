#include<iostream>
#include<vector>
#include<string>
#include<unordered_map>
#include<unordered_set>
using namespace std;
#define umap unordered_map
#define uset unordered_set

int recTrace(umap<int,uset<int> > &graph,umap<int,int> &masks,vector<int> &order,int index){
	if(index==order.size())return 1;
	int mask = 15,cur = order[index];
	for(int neigh:graph[cur]){
		if(masks.find(neigh)!=masks.end()){
			mask &= (15^masks[neigh]);
		}
	}
	if(mask==15)mask=1;
	for(int m=mask;m>0;m-=m&-m){
		masks[cur] = m&-m;
		if(recTrace(graph,masks,order,index+1))return 1;
	}
	if(masks.find(cur)!=masks.end())masks.erase(cur);
	return 0;
}

int main(){
	int n;cin>>n;
	umap<int,uset<int> > graph;
	for(int i=1;i<=n;i++){
		uset<int> neighs;
		graph[i] = neighs;
	}
	string line;
	while(cin>>line){
		int left=0,right=0,lMode=1;
		for(char c:line){
			if(c=='-')lMode = 0;
			else if(lMode)left = left*10 + (int)(c-'0');
			else right = right*10 + (int)(c-'0');
		}
		if(left==0 || right==0)break;
		graph[left].insert(right);
		graph[right].insert(left);
	}
	uset<int> checked;
	umap<int,int> masks;
	vector<int> stack,order;
	for(int i=1;i<=n;i++){
		if(checked.find(i)==checked.end()){
			checked.insert(i);
			stack.push_back(i);
			while(!stack.empty()){
				int cur = stack.back();stack.pop_back();
				order.push_back(cur);
				for(int neigh:graph[cur]){
					if(checked.find(neigh)==checked.end()){
						checked.insert(neigh);
						stack.push_back(neigh);
					}
				}
			}
		}
	}
	recTrace(graph,masks,order,0);
	for(int i=1;i<=n;i++){
		cout<<i<<" ";
		if(masks[i]==1)cout<<1<<endl;
		else if(masks[i]==2)cout<<2<<endl;
		else if(masks[i]==4)cout<<3<<endl;
		else cout<<4<<endl;
	}
	return 0;
}