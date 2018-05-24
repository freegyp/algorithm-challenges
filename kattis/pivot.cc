#include<iostream>
#include<algorithm>
#include<cstdlib>
using namespace std;

int main(){
	int n;cin>>n;
	int *nums = (int*)malloc(n*sizeof(int)),*sorted = (int*)malloc(n*sizeof(int)),preMax=0,res=0;
	for(int i=0;i<n;i++){
		int num;cin>>num;
		nums[i] = num;
		sorted[i] = num;
		if(num<=preMax)preMax=num-1;
	}
	sort(sorted,sorted+n);
	for(int i=0;i<n;i++){
		if(nums[i]==sorted[i] && nums[i]>preMax)res++;
		preMax = preMax>nums[i]?preMax:nums[i];
	}
	cout<<res<<endl;
	return 0;
}