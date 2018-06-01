#include<iostream>
#include<vector>
#include<unordered_map>
#include<unordered_set>
#include<string>
using namespace std;
#define umap unordered_map
#define uset unordered_set

int dfs(umap<string,uset<string> > &graph,umap<string,int> &tags,string start,int curTag){
	tags[start] = curTag;
	for(string neigh:graph[start]){
		if(tags.find(neigh)==tags.end()){
			if(!dfs(graph,tags,neigh,1-curTag))return 0;
		}else if(tags[neigh]==curTag)return 0;
	}
	return 1;
}

int main(){
	umap<string,uset<string> > graph;
	umap<string,int> tags;
	vector<string> nodes;
	int n,m;cin>>n;
	for(int i=0;i<n;i++){
		string cur;cin>>cur;
		nodes.push_back(cur);
		uset<string> neighs;
		graph[cur] = neighs;
	}
	cin>>m;
	for(int i=0;i<m;i++){
		string left,right;cin>>left>>right;
		graph[left].insert(right);
		graph[right].insert(left);
	}
	int possible = 1;
	for(string s:nodes){
		if(tags.find(s)==tags.end()){
			if(!dfs(graph,tags,s,0)){
				possible = 0;
				break;
			}
		}
	}
	if(!possible){
		cout<<"impossible"<<endl;
	}else{
		vector<string> zeros,ones;
		for(string s:nodes){
			if(tags[s]==1)ones.push_back(s);
			else zeros.push_back(s);
		}
		for(string s:zeros)cout<<s<<" ";
		cout<<endl;
		for(string s:ones)cout<<s<<" ";
		cout<<endl;
	}
	return 0;
}