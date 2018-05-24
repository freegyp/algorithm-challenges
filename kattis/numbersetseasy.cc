#include<iostream>
#include<cstdlib>
#include<vector>
#include<unordered_set>
using namespace std;
#define uset unordered_set

class Group{
public:
	int id,depth;
	Group *parent;
	Group(int id,int depth=0):id(id),depth(depth){parent = NULL;}
	Group* traceTop(){
		if(!parent)return this;
		return parent->traceTop();
	}
	int sameGroup(Group *other){
		return traceTop()==(other->traceTop());
	}
	int merge(Group *other,int maxId){
		if(sameGroup(other))return maxId;
		Group *left = traceTop(),*right = other->traceTop();
		if(left->depth==right->depth){
			Group *newTop = new Group(maxId,left->depth + 1);
			left->parent = newTop;
			right->parent = newTop;
			maxId++;
		}else if(left->depth>right->depth){
			right->parent = left;
		}else{
			left->parent = right;
		}
		return maxId;
	}
};

int main(){
	int c;cin>>c;
	int *isPrime = (int*)malloc(1001*sizeof(int));
	for(int i=0;i<=1000;i++)isPrime[i] = 1;
	isPrime[0] = 0;isPrime[1] = 0;
	for(int i=2;i<=1000;i++){
		if(isPrime[i]){
			for(int j=i*2;j<=1000;j+=i){
				isPrime[j] = 0;
			}
		}
	}
	for(int t=0;t<c;t++){
		int a,b,p;
		cin>>a>>b>>p;
		vector<Group*> groups;
		for(int i=a;i<=b;i++){
			Group *curGroup = new Group(i);
			groups.push_back(curGroup);
		}
		int maxId = b+1;
		for(int i=p;i<=b;i++){
			if(isPrime[i]){
				Group *pGroup = new Group(maxId++);
				for(int j=i;j<=b;j+=i){
					if(j>=a){
						maxId = pGroup->merge(groups[j-a],maxId);
					}
				}
			}
		}
		uset<int> groupSet;
		for(int i=a;i<=b;i++){
			Group *top = groups[i-a]->traceTop();
			groupSet.insert(top->id);
		}
		cout<<"Case #"<<t+1<<": "<<groupSet.size()<<endl;
	}
	return 0;
}
