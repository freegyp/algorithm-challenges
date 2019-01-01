#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_set>
#include<map>
using namespace std;
#define uset unordered_set
#define uiset uset<int>
#define vnode vector<Node*>
#define imap map<int,int>

class Node{
public:
	int id;
	vector<Node*> neighbors;
	vector<int> starts;
	vector<int> ends;
	Node(int id):id(id){}
	void addNeigh(Node *neigh,int start,int end){
		neighbors.push_back(neigh);
		starts.push_back(start);
		ends.push_back(end);
	}
};

int dfs(Node *src,Node *dest,int start,int end){
	vnode stack(1,src);
	uiset checked;
	checked.insert(src->id);
	while(!stack.empty() && checked.find(dest->id)==checked.end()){
		Node *cur = stack.back();stack.pop_back();
		for(int i=0;i<cur->neighbors.size();i++){
			if(cur->starts[i]<=start && cur->ends[i]>=end && checked.find(cur->neighbors[i]->id)==checked.end()){
				checked.insert(cur->neighbors[i]->id);
				stack.push_back(cur->neighbors[i]);
			}
		}
	}
	if(checked.find(dest->id)==checked.end())return 0;
	return 1;
}

int main(){
	int n,l,b,s,t;
	cin>>n>>l>>b>>s>>t;
	vnode nodes;
	for(int i=0;i<=n;i++){
		Node *cur = new Node(i);
		nodes.push_back(cur);
	}
	imap offsets;
	for(int i=0;i<l;i++){
		int aa,bb,x,y;
		cin>>aa>>bb>>x>>y;
		if(offsets.find(x)==offsets.end())offsets[x] = 0;
		if(offsets.find(y+1)==offsets.end())offsets[y+1] = 0;
		offsets[x]++;
		offsets[y+1]--;
		nodes[aa]->addNeigh(nodes[bb],x,y+1);
	}
	int pre=0,preCount=0,ans=0;
	for(auto it=offsets.begin();it!=offsets.end();it++){
		if(preCount>0 && dfs(nodes[s],nodes[t],pre,it->first)){
			ans += it->first-pre;
		}
		preCount += it->second;
		pre = it->first;
	}
	cout<<ans<<endl;
	return 0;
}