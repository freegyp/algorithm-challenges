#include<iostream>
#include<vector>
#include<cstdlib>
#include<utility>
#include<algorithm>
using namespace std;

class Group{
public:
	int depth,nodes,edges;
	Group *parent;
	Group(int depth=1,int nodes=1,int edges=0):depth(depth),nodes(nodes),edges(edges),parent(NULL){}
	Group* traceTop(){
		if(parent)return parent->traceTop();
		return this;
	}
	int groupType(){
		Group *g = traceTop();
		if(g->edges==g->nodes-1)return 1;
		else if(g->edges==g->nodes)return 0;
		else return -1;
	}
	int sameGroup(Group *other){
		if(traceTop()==other->traceTop())return 1;
		return 0;
	}
	void merge(Group *other){
		if(sameGroup(other)){
			traceTop()->edges++;
			return;
		}
		Group *left = traceTop(),*right = other->traceTop();
		if(left->depth == right->depth){
			Group *newTop = new Group(left->depth+1,left->nodes+right->nodes,left->edges+right->edges+1);
			left->parent = newTop;
			right->parent = newTop;
		}else if(left->depth > right->depth){
			left->nodes += right->nodes;
			left->edges += right->edges+1;
			right->parent = left;
		}else{
			right->nodes += left->nodes;
			right->edges += left->edges+1;
			left->parent = right;
		}
	}
};

int main(){
	int tt;cin>>tt;
	for(int t=0;t<tt;t++){
		int n;cin>>n;
		vector<Group*> groups;
		for(int i=0;i<n;i++){
			Group *g = new Group();
			groups.push_back(g);
		}
		for(int i=0;i<n-1;i++){
			int left,right;cin>>left>>right;
			groups[left-1]->merge(groups[right-1]);
		}
		vector<int> ratings,types,insertables;
		int possible = 1;
		for(int i=0;i<n;i++){
			int rating;cin>>rating;
			ratings.push_back(rating);
			types.push_back(groups[i]->groupType());
			if(types[i]==-1)possible = 0;
			else if(types[i]==1)insertables.push_back(i);
		}
		if(possible){
			int left,right;
			if(insertables.size()==1){
				int i=0;
				while(i==insertables[0])i++;
				left = i<insertables[0]?i:insertables[0];
				right = i<insertables[0]?insertables[0]:i;
			}else{
				vector<pair<int,int> > res;
				for(int i:insertables){
					res.push_back(make_pair(ratings[i],-i));
				}
				sort(res.begin(),res.end());
				left = -res[res.size()-1].second;
				right = -res[res.size()-2].second;
				for(int i=0;i<n;i++){
					if(types[i]==0 || (types[i]==1 && i!=left && ratings[i]==ratings[left])){
						right = i;
						break;
					}
				}
				if(left>right){
					int temp = left;
					left = right;
					right = temp;
				}
			}
			left++;right++;
			cout<<left<<" "<<right<<endl;
		}else{
			cout<<"impossible"<<endl;
		}
	}
	return 0;
}
