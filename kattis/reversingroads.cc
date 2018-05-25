#include<iostream>
#include<vector>
#include<utility>
#include<unordered_map>
#include<unordered_set>
using namespace std;
#define umap unordered_map
#define uset unordered_set

int entirelyCycle(umap<int,uset<int> > &graph){
	int res=1;
	for(int i=0;i<graph.size();i++){
		vector<int> stack(1,i);
		uset<int> checked;checked.insert(i);
		while(!stack.empty()){
			int cur = stack.back();stack.pop_back();
			for(int neigh:graph[cur]){
				if(checked.find(neigh)==checked.end()){
					checked.insert(neigh);
					stack.push_back(neigh);
				}
			}
		}
		if(checked.size()!=graph.size()){
			res = 0;
			break;
		}
	}
	return res;
}

int reverseAndTry(umap<int,uset<int> > &graph,int left,int right){
	graph[left].erase(right);
	graph[right].insert(left);
	int res = entirelyCycle(graph);
	graph[right].erase(left);
	graph[left].insert(right);
	return res;
}

int main(){
	int m,n,t=1;
	while(cin>>m>>n){
		umap<int,uset<int> > graph;
		for(int i=0;i<m;i++){
			uset<int> neighbors;
			graph[i] = neighbors;
		}
		vector<pair<int,int> > edges;
		for(int i=0;i<n;i++){
			int left,right;cin>>left>>right;
			edges.push_back(make_pair(left,right));
			graph[left].insert(right);
		}
		cout<<"Case "<<t++<<": ";
		if(entirelyCycle(graph))cout<<"valid"<<endl;
		else{
			int found = 0;
			for(int i=0;i<n;i++){
				if(reverseAndTry(graph,edges[i].first,edges[i].second)){
					cout<<edges[i].first<<" "<<edges[i].second<<endl;
					found = 1;
					break;
				}
			}
			if(!found)cout<<"invalid"<<endl;
		}
	}
	return 0;
}