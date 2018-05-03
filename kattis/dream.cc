#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<cstdlib>
using namespace std;
#define umap unordered_map

int scenarioCheck(vector<string> &events,umap<string,int> &eventIdx,int realMask){
	int trueMax=-1,falseMin=eventIdx.size();
	for(int i=0;i<events.size();i++){
		if(realMask&(1<<i)){
			if(eventIdx.find(events[i])==eventIdx.end())return -1;
			else trueMax = max(trueMax,eventIdx[events[i]]);
		}else if(eventIdx.find(events[i])!=eventIdx.end()){
			falseMin = min(falseMin,eventIdx[events[i]]);
		}
	}
	if(trueMax<falseMin)return eventIdx.size()-falseMin;
	else return -1;
}

int main(){
	int n;cin>>n;
	vector<string> events;
	umap<string,int> eventIdx;
	for(int i=0;i<n;i++){
		char type;cin>>type;
		if(type=='E'){
			string event;cin>>event;
			eventIdx[event] = events.size();
			events.push_back(event);
		}else if(type=='D'){
			int j;cin>>j;
			while(j-->0){
				eventIdx.erase(events.back());
				events.pop_back();
			}
		}else if(type=='S'){
			int k,mask=0;cin>>k;
			vector<string> scenario;
			for(int j=0;j<k;j++){
				string event;cin>>event;
				if(event[0]=='!'){
					event = event.substr(1,event.size()-1);
				}else{
					mask |= (1<<j);
				}
				scenario.push_back(event);
			}
			int res = scenarioCheck(scenario,eventIdx,mask);
			if(res==-1)cout<<"Plot Error"<<endl;
			else if(res==0)cout<<"Yes"<<endl;
			else cout<<res<<" Just A Dream"<<endl;
		}
	}
	return 0;
}