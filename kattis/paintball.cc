#include<iostream>
#include<cstdlib>
#include<vector>
using namespace std;

class Node{
public:
	int id,used;
	Node *match;
	vector<Node*> neighbs;
	Node(int id):id(id),used(0),match(NULL){}
};

int dfs(Node *cur){
	cur->used = 1;
	for(int i=0;i<cur->neighbs.size();i++){
		if(cur->neighbs[i]->match==NULL || (!cur->neighbs[i]->match->used && dfs(cur->neighbs[i]->match))){
			cur->neighbs[i]->match = cur;
			cur->match = cur->neighbs[i];
			return 1;
		}
	}
	return 0;
}

int main(){
	int n,m;cin>>n>>m;
	vector<Node*> shooters,shots;
	for(int i=1;i<=n;i++){
		Node *cur = new Node(i);
		Node *cur1 = new Node(i);
		shooters.push_back(cur);
		shots.push_back(cur1);
	}
	for(int i=0;i<m;i++){
		int a,b;cin>>a>>b;
		shooters[a-1]->neighbs.push_back(shots[b-1]);
		shooters[b-1]->neighbs.push_back(shots[a-1]);
	}
	int matched = 0;
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++)shooters[j]->used = 0;
		matched += dfs(shooters[i]);
	}
	if(matched!=n)cout<<"Impossible"<<endl;
	else{
		for(int i=0;i<n;i++){
			cout<<(shooters[i]->match->id)<<endl;
		}
	}
	return 0;
}