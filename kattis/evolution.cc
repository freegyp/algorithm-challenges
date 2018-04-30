#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<algorithm>
using namespace std;

#define umap unordered_map

bool strCmp(string &left,string &right){
	return left.size()>right.size();
}

int isSubseq(vector<string> &fossils,int left,int right,umap<int,int> &mem){
	int target = left*4001+right;
	if(mem.find(target)==mem.end()){
		mem[target] = 0;
		for(int i=0,j=0;i<fossils[right].size() && j<fossils[left].size();i++){
			if(fossils[right][i]==fossils[left][j]){
				j++;
				if(j==fossils[left].size())mem[target] = 1;
			}
		}
	}
	return mem[target];
}

void recoverAns(vector<string> &fossils,vector<string> &ans1,vector<string> &ans2,int target,umap<int,int> &pred){
	if(target==0)return;
	int i=target/4001,j=target%4001,x=pred[target]/4001,y=pred[target]%4001;
	if(y==i){
		recoverAns(fossils,ans2,ans1,pred[target],pred);
	}else{
		recoverAns(fossils,ans1,ans2,pred[target],pred);
	}
	ans2.push_back(fossils[j]);
}

int main(){
	int n;cin>>n;
	vector<string> fossils,ans1,ans2;
	for(int i=0;i<=n;i++){
		string s;cin>>s;
		fossils.push_back(s);
	}
	sort(fossils.begin(),fossils.end(),strCmp);
	vector<int> stack(1,0);
	umap<int,int> pred,mem;
	while(!stack.empty() && stack.back()%4001<n){
		int i=stack.back()/4001,j=stack.back()%4001;
		stack.pop_back();
		if(pred.find(j*4001+j+1)==pred.end() && isSubseq(fossils,j+1,i,mem)){
			pred[j*4001+j+1] = i*4001+j;
			stack.push_back(j*4001+j+1);
		}
		if(pred.find(i*4001+j+1)==pred.end() && isSubseq(fossils,j+1,j,mem)){
			pred[i*4001+j+1] = i*4001+j;
			stack.push_back(i*4001+j+1);
		}
	}
	if(stack.empty()){
		cout<<"impossible"<<endl;
	}else{
		recoverAns(fossils,ans1,ans2,stack.back(),pred);
		cout<<ans1.size()<<' '<<ans2.size()<<endl;
		reverse(ans1.begin(),ans1.end());
		reverse(ans2.begin(),ans2.end());
		for(string s:ans1)cout<<s<<endl;
		for(string s:ans2)cout<<s<<endl;
	}
	return 0;
}

