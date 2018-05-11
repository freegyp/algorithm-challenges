#include<iostream>
#include<cstdlib>
#include<algorithm>
using namespace std;

long long smallerTotal(long long *nums,long long checked,int length,int start){
	if(start==length || checked+nums[start]>=200)return 0;
	long long res=0;
	for(int i=start;i<length;i++){
		if(checked+nums[i]<200){
			res += checked+nums[i]+smallerTotal(nums,checked+nums[i],length,i+1);
		}else{
			break;
		}
	}
	return res;
}

int main(){
	int n;cin>>n;
	long long total = 0;
	long long *nums = (long long*)malloc(n*sizeof(long long));
	for(int i=0;i<n;i++){
		cin>>nums[i];
		total += nums[i]<<(n-1);
	}
	sort(nums,nums+n);
	cout<<total-smallerTotal(nums,0,n,0)<<endl;
	return 0;
}