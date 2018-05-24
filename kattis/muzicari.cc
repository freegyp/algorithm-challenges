#include<iostream>
#include<vector>
#include<utility>
using namespace std;

int main(){
	int t,n,q1,q2;cin>>t>>n;
	vector<vector<int> > pred;
	vector<int> nums,ans(n,-1);
	for(int i=0;i<n;i++){
		int num;cin>>num;
		nums.push_back(num);
	}
	for(int i=0;i<=t;i++){
		vector<int> pRow(t+1,-1);
		pred.push_back(pRow);
	}
	vector<pair<int,int> > stack;
	stack.push_back(make_pair(0,0));
	while(!stack.empty()){
		int t1=stack.back().first/(t+1),t2=stack.back().first%(t+1),i=stack.back().second;
		stack.pop_back();
		if(i==n){
			q1 = t1;q2 = t2;break;
		}else{
			if(t1+nums[i]<=t && pred[t1+nums[i]][t2]<0){
				pred[t1+nums[i]][t2] = t1*(t+1)+t2;
				stack.push_back(make_pair((t1+nums[i])*(t+1)+t2,i+1));
			}
			if(t2+nums[i]<=t && pred[t1][t2+nums[i]]<0){
				pred[t1][t2+nums[i]] = t1*(t+1)+t2;
				stack.push_back(make_pair(t1*(t+1)+t2+nums[i],i+1));
			}
		}
	}
	for(int i=n-1;i>=0;i--){
		int p1=pred[q1][q2]/(t+1),p2=pred[q1][q2]%(t+1);
		if(p1<q1)ans[i] = p1;
		else ans[i] = p2;
		q1 = p1;q2 = p2;
	}
	for(int i=0;i<n;i++)cout<<ans[i]<<" ";
	cout<<endl;
	return 0;
}