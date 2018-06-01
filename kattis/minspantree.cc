#include<iostream>
#include<algorithm>
#include<cstdlib>
#include<tuple>
#include<vector>
#include<queue>
using namespace std;
#define pq priority_queue

class Group{
public:
	int depth;
	Group *parent;
	Group(int depth=1):depth(depth),parent(NULL){}
	~Group(){
		free(parent);
	}
	Group* traceTop(){
		if(parent==NULL)return this;
		return parent->traceTop();
	}
	int sameGroup(Group *other){
		if(traceTop()==other->traceTop())return 1;
		return 0;
	}
	void merge(Group *other){
		if(sameGroup(other))return;
		Group *left=traceTop(),*right=other->traceTop();
		if(left->depth==right->depth){
			Group *newTop = new Group(left->depth+1);
			left->parent = newTop;
			right->parent = newTop;
			return;
		}else if(left->depth>right->depth){
			right->parent = left;
			return;
		}else{
			left->parent = right;
			return;
		}
	}
};

int main(){
	int n,m;
	while(true){
		cin>>n>>m;
		if(n==0 && m==0)break;
		pq<tuple<int,int,int> > _queue;
		vector<Group*> groups;
		for(int i=0;i<n;i++){
			Group *g = new Group();
			groups.push_back(g);
		}
		for(int i=0;i<m;i++){
			int left,right,w;
			cin>>left>>right>>w;
			_queue.push(make_tuple(-w,left,right));
		}
		int total=0;
		vector<tuple<int,int> > edges;
		while(!_queue.empty()){
			int w,left,right;
			tie(w,left,right) = _queue.top();
			w = -w;
			_queue.pop();
			if(!groups[left]->sameGroup(groups[right])){
				groups[left]->merge(groups[right]);
				if(left<right)edges.push_back(make_tuple(left,right));
				else edges.push_back(make_tuple(right,left));
				total += w;
			}
		}
		int possible = 1;
		for(int i=1;i<n;i++){
			if(!groups[0]->sameGroup(groups[i])){
				possible = 0;
				break;
			}
		}
		if(!possible)cout<<"Impossible"<<endl;
		else{
			cout<<total<<endl;
			sort(edges.begin(),edges.end());
			for(int i=0;i<edges.size();i++){
				int left,right;
				tie(left,right) = edges[i];
				cout<<left<<" "<<right<<endl;
			}
		}
	}
	return 0;
}
