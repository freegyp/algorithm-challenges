#include<iostream>
#include<vector>
#include<string>
#include<cstdlib>
using namespace std;

class Node{
public:
	int used;
	Node *match;
	vector<Node*> neighbs;
	string like,hate;
	Node(string like,string hate):like(like),hate(hate),match(NULL),used(0){}
	void addNeighb(Node *neigh){
		neighbs.push_back(neigh);
	}
	int neighbors(){
		return (int)(neighbs.size());
	}
	Node* getNeighb(int i){
		return neighbs[i];
	}
	int fights(Node *right){
		if(like==(right->hate) || hate==(right->like))return 1;
		return 0;
	}
};

int dfs(Node *n){
	n->used = 1;
	for(int i=0;i<(n->neighbors());i++){
		Node *neigh = n->getNeighb(i);
		if((neigh->match)==NULL || (!neigh->match->used && dfs(neigh->match))){
			neigh->match = n;
			return 1;
		}
	}
	return 0;
}

int main(){
	int tt;cin>>tt;
	for(int t=0;t<tt;t++){
		int c,d,v;cin>>c>>d>>v;
		vector<Node*> dogLovers,catLovers;
		for(int i=0;i<v;i++){
			string like,hate;cin>>like>>hate;
			Node *cur = new Node(like,hate);
			if(like[0]=='D')dogLovers.push_back(cur);
			else catLovers.push_back(cur);
		}
		int rans = 0;
		for(Node *dogl:dogLovers){
			for(Node *catl:catLovers){
				if(dogl->fights(catl))dogl->addNeighb(catl);
			}
			for(Node *dd:dogLovers)dd->used = 0;
			for(Node *cc:catLovers)cc->used = 0;
			rans += dfs(dogl);
		}
		cout<<v-rans<<endl;
	}
	return 0;
}