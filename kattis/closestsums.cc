#include<iostream>
#include<vector>
#include<algorithm>
#include<cstdlib>
using namespace std;

int main(){
	int n,m,_case=1;
	while(cin>>n){
		cout<<"Case "<<_case++<<":"<<endl;
		vector<int> nums;
		for(int i=0;i<n;i++){
			int num;cin>>num;
			nums.push_back(num);
		}
		sort(nums.begin(),nums.end());
		cin>>m;
		for(int q=0;q<m;q++){
			int target,res=nums.front()+nums.back();cin>>target;
			int i=0,j=n-1;
			while(j-i>=1){
				if(abs(nums[i]+nums[j]-target)<abs(res-target)){
					res = nums[i]+nums[j];
				}
				if(nums[i]+nums[j]>target)j--;
				else if(nums[i]+nums[j]<target)i++;
				else break;
			}
			cout<<"Closest sum to "<<target<<" is "<<res<<"."<<endl;
		}
	}
	return 0;
}