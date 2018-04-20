#include<iostream>
#include<vector>
#include<tuple>
#include<algorithm>
using namespace std;

class Group{
public:
	int id,level;
	Group *top = NULL;
	Group(int id,int level=0):id(id),level(level){}
	Group* traceTop(){
		Group *cur = this;
		while(cur->top){
			cur = cur->top;
		}
		return cur;
	}
	void setParent(Group *other){
		top = other;
	}
	int sameGroup(Group &other){
		if(traceTop()==other.traceTop())return 1;
		return 0;
	}
	int join(Group &other,int maxId){
		if(!sameGroup(other)){
			Group *left=traceTop(),*right = other.traceTop();
			if(left->level > right->level){
				right->setParent(left);
			}else if(left->level < right->level){
				left->setParent(right);
			}else{
				Group *newTop = new Group(maxId++,level+1);
				left->setParent(newTop);
				right->setParent(newTop);
			}
		}
		return maxId;
	}
};

int mstLen(vector<tuple<int,int,int> > &edges,int n){
	vector<Group> groups;
	int ans = 0,curId = n;
	for(int i=0;i<n;i++){
		Group g(i);
		groups.push_back(g);
	}
	for(auto it=edges.begin();it!=edges.end();it++){
		int d,left,right;
		tie(d,left,right) = (*it);
		if(!groups[left].sameGroup(groups[right])){
			ans += d;
			curId = groups[left].join(groups[right],curId);
		}
	}
	return ans;
}

int main(){
	int tt;cin>>tt;
	for(int i=0;i<tt;i++){
		int m,c;cin>>m>>c;
		vector<tuple<int,int,int> > edges;
		for(int j=0;j<c*(c-1)/2;j++){
			int left,right,d;
			cin>>left>>right>>d;
			edges.push_back(make_tuple(d,left,right));
		}
		sort(edges.begin(),edges.end());
		int spill = mstLen(edges,c) + c;
		if(spill<=m)cout<<"yes"<<endl;
		else cout<<"no"<<endl;
	}
	return 0;
}















