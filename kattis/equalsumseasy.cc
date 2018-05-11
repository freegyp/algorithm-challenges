#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;
#define umap unordered_map

int main(){
	int tt;cin>>tt;
	for(int t=1;t<=tt;t++){
		int n,found=0;cin>>n;
		vector<int> nums;
		umap<int,int> sumMask;
		for(int i=0;i<n;i++){
			int num;cin>>num;
			nums.push_back(num);
		}
		cout<<"Case #"<<t<<":"<<endl;
		for(int i=1;i<(1<<n);i++){
			int total=0;
			for(int j=0;j<n;j++){
				if(i&(1<<j))total+=nums[j];
			}
			if(sumMask.find(total)==sumMask.end()){
				sumMask[total] = i;
			}else{
				for(int j=0;j<n;j++){
					if(sumMask[total]&(1<<j))cout<<nums[j]<<" ";
				}
				cout<<endl;
				for(int j=0;j<n;j++){
					if(i&(1<<j))cout<<nums[j]<<" ";
				}
				cout<<endl;
				found = 1;
				break;
			}
		}
		if(found==0)cout<<"Impossible"<<endl;
	}
	return 0;
}