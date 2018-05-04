#include<iostream>
#include<vector>
using namespace std;
long long mergeSort(vector<int> &nums){
	if(nums.size()==1)return 0;
	else if(nums.size()==2){
		if(nums[0]>nums[1]){
			int temp = nums[0];
			nums[0] = nums[1];
			nums[1] = temp;
			return 1;
		}
		return 0;
	}
	vector<int> left(nums.begin(),nums.begin()+nums.size()/2),right(nums.begin()+nums.size()/2,nums.end());
	long long ans = mergeSort(left) + mergeSort(right);
	long long il=0,ir=0,j=0;
	while(j<nums.size()){
		if(ir>=right.size() || (il<left.size() && left[il]<right[ir])){
			ans += ir;
			nums[j++] = left[il++];
		}else{
			nums[j++] = right[ir++];
		}
	}
	return ans;
}

int main(){
	int n;cin>>n;
	vector<int> nums;
	for(int i=0;i<n;i++){
		int num;cin>>num;
		nums.push_back(num);
	}
	cout<<mergeSort(nums)<<endl;
	return 0;
}