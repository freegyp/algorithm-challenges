#include<iostream>
#include<cstdlib>
#include<vector>
using namespace std;

class Group{
public:
	int id,depth;
	Group *parent;
	Group(int id,int depth=0):id(id),depth(depth),parent(NULL){}
	~Group(){
		if(parent!=NULL){
			free(parent);
		}
	}
	Group* traceTop(){
		if(parent!=NULL)return parent->traceTop();
		return this;
	}
	int sameGroup(Group *other){
		return traceTop()==other->traceTop();
	}
	int merge(Group *other,int maxGroup){
		if(sameGroup(other))return maxGroup;
		Group *left = traceTop(),*right = other->traceTop();
		if(left->depth == right->depth){
			Group *newTop = new Group(maxGroup,(left->depth)+1);
			left->parent = newTop;
			right->parent = newTop;
			return maxGroup+1;
		}else if(left->depth < right->depth){
			left->parent = right;
		}else{
			right->parent = left;
		}
		return maxGroup;
	}
};

int main(){
	int tt;cin>>tt;
	for(int t=0;t<tt;t++){
		int n;cin>>n;
		vector<int> xList,yList;
		vector<Group*> groups;
		for(int i=0;i<n+2;i++){
			int x,y;cin>>x>>y;
			xList.push_back(x);
			yList.push_back(y);
			Group *g = new Group(groups.size());
			groups.push_back(g);
		}
		int maxGroup = groups.size();
		for(int i=0;i<groups.size();i++){
			for(int j=i+1;j<groups.size();j++){
				if(abs(xList[i]-xList[j])+abs(yList[i]-yList[j])<=1000){
					maxGroup = groups[i]->merge(groups[j],maxGroup);
				}
			}
		}
		if(groups[0]->sameGroup(groups.back())){
			cout<<"happy"<<endl;
		}else{
			cout<<"sad"<<endl;
		}
	}
	return 0;
}

