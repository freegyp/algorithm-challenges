#include<iostream>
#include<cstdlib>
#include<unordered_map>
#include<vector>
using namespace std;
#define umap unordered_map
#define ll long long

class Node{
public:
	int match,used;
	ll left,right;
	vector<ll> neighbs;
	Node(ll left,ll right):left(left),right(right),match(-1),used(0){
		neighbs.push_back(left+right);
		neighbs.push_back(left-right);
		neighbs.push_back(left*right);
	}
};

int dfs(Node *cur,umap<ll,Node*> &matches){
	cur->used = 1;
	for(int i=0;i<3;i++){
		if(matches.find(cur->neighbs[i])==matches.end() || (!matches[cur->neighbs[i]]->used && dfs(matches[cur->neighbs[i]],matches))){
			matches[cur->neighbs[i]] = cur;
			cur->match = i;
			return 1;
		}
	}
	return 0;
}

int main(){
	vector<char> ops;
	ops.push_back('+');
	ops.push_back('-');
	ops.push_back('*');
	int n;cin>>n;
	umap<ll,Node*> matches;
	vector<Node*> nodes;
	for(int i=0;i<n;i++){
		ll a,b;cin>>a>>b;
		Node *cur = new Node(a,b);
		nodes.push_back(cur);
	}
	int total = 0;
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++)nodes[j]->used = 0;
		total += dfs(nodes[i],matches);
	}
	if(total<n)cout<<"impossible"<<endl;
	else{
		for(int i=0;i<n;i++){
			cout<<(nodes[i]->left)<<" "<<ops[nodes[i]->match]<<" "<<(nodes[i]->right)<<" = "<<(nodes[i]->neighbs[nodes[i]->match])<<endl;
		}
	}
	return 0;
}