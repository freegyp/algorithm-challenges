#include<iostream>
#include<deque>
#include<vector>
#include<utility>
#include<cstdlib>
using namespace std;

int main(){
	int n,m,c;cin>>n>>m>>c;
	deque<pair<int,int> > maxQueue,minQueue;
	vector<int> ans;
	for(int i=1;i<=n;i++){
		int num;cin>>num;
		while(!maxQueue.empty() && maxQueue.back().second<=num)maxQueue.pop_back();
		maxQueue.push_back(make_pair(i,num));
		while(!maxQueue.empty() && maxQueue.front().first<=i-m)maxQueue.pop_front();
		while(!minQueue.empty() && minQueue.back().second>=num)minQueue.pop_back();
		minQueue.push_back(make_pair(i,num));
		while(!minQueue.empty() && minQueue.front().first<=i-m)minQueue.pop_front();
		if(i>=m && (maxQueue.front().second - minQueue.front().second <= c)){
			ans.push_back(i-m+1);
		}
	}
	if(ans.empty())cout<<"NONE"<<endl;
	else{
		for(int i:ans)cout<<i<<endl;
	}
	return 0;
}