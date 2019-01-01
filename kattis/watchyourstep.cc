#include<iostream>
#include<unordered_map>
#include<cstdlib>
#include<vector>
using namespace std;
#define vint vector<int>
#define umap unordered_map
#define uimap umap<int,vector<int> >

int dfs(uimap &neighbors,int s){
	int total = 0, *checked = (int*)malloc(sizeof(int)*neighbors.size());
	for(int i=0;i<neighbors.size();i++)checked[i] = 0;
	checked[s] = 1;
	vint stack(1,s);
	while(!stack.empty()){
		int cur = stack.back();stack.pop_back();
		total++;
		for(int neigh:neighbors[cur]){
			if(!checked[neigh]){
				checked[neigh] = 1;
				stack.push_back(neigh);
			}
		}
	}
	return total-neighbors[s].size()-1;
}

int check(uimap &neighbors){
	int res = 0;
	for(int i=0;i<neighbors.size();i++){
		res += dfs(neighbors,i);
	}
	return res;
}

int main(){
	int n;cin>>n;
	uimap neighbors;
	for(int i=0;i<n;i++){
		vint row;
		for(int j=0;j<n;j++){
			int conn;cin>>conn;
			if(conn)row.push_back(j);
		}
		neighbors[i] = row;
	}
	cout<<check(neighbors)<<endl;
	return 0;
}