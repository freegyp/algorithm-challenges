#include<iostream>
#include<cstdlib>
#include<vector>
using namespace std;

class Group{
private:
	int count,id;
	long long sum;
public:
	int depth;
	Group *parent;
	Group(int id,long long value,int depth=0,int count=1):id(id),depth(depth),sum(value),count(count),parent(NULL){}
	Group* traceTop(){
		if(parent!=NULL){
			return parent->traceTop();
		}
		return this;
	}
	int sameGroup(Group *other){
		Group *left=traceTop(),*right=other->traceTop();
		if(left==right)return 1;
		return 0;
	}
	void addChildWith(int _count,long long _sum){
		count += _count;
		sum += _sum;
		if(parent!=NULL)parent->addChildWith(_count,_sum);
	}
	void delMemberWith(long long value){
		sum -= value;
		count--;
		if(parent!=NULL)parent->delMemberWith(value);
	}
	void delSelf(){
		if(depth==0)delMemberWith(sum);
	}
	void printInfo(){
		if(parent!=NULL){
			parent->printInfo();
			return;
		}
		cout<<count<<" "<<sum<<endl;
	}
	int merge(Group *other,int maxGroup){
		if(sameGroup(other))return maxGroup;
		Group *left = traceTop(),*right = other->traceTop();
		if(left->depth == right->depth){
			Group *newTop = new Group(maxGroup,0,(left->depth)+1,0);
			newTop->addChildWith(left->count,left->sum);
			newTop->addChildWith(right->count,right->sum);
			left->parent = newTop;
			right->parent = newTop;
			return maxGroup+1;
		}else if(left->depth > right->depth){
			right->parent = left;
			left->addChildWith(right->count,right->sum);
		}else{
			left->parent = right;
			right->addChildWith(left->count,left->sum);
		}
		return maxGroup;
	}
};

int main(){
	int n,m;
	while(cin>>n>>m){
		int maxGroup=n+1;
		vector<Group*> groups;
		for(int i=0;i<=n;i++){
			Group *g = new Group(i,(long long)i);
			groups.push_back(g);
		}
		for(int i=0;i<m;i++){
			int type;cin>>type;
			if(type==1){
				int left,right;cin>>left>>right;
				maxGroup = groups[left]->merge(groups[right],maxGroup);
			}else if (type==2){
				int left,right;cin>>left>>right;
				if(!groups[left]->sameGroup(groups[right])){
					groups[left]->delSelf();
					groups[left] = new Group(maxGroup++,(long long)left);
					maxGroup = groups[left]->merge(groups[right],maxGroup);
				}
			}else{
				int target;cin>>target;
				groups[target]->printInfo();
			}
		}
	}
	return 0;
}

