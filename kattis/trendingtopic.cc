#include<iostream>
#include<vector>
#include<string>
#include<set>
#include<deque>
#include<unordered_map>
#include<utility>
#include<cstdlib>
using namespace std;
#define umap unordered_map

int main(){
	deque<vector<string> > queue;
	umap<string,int> wordCount;
	set<pair<int,string> > wordSet;
	string token;
	while(cin>>token){
		if(token=="<text>"){
			vector<string> text;
			umap<string,int> w2a;
			while(true){
				string word;cin>>word;
				if(word=="</text>")break;
				else if(word.size()>=4){
					text.push_back(word);
					if(w2a.find(word)==w2a.end())w2a[word]=0;
					w2a[word]++;
				}
			}
			if(queue.size()>=7){
				for(string word:queue.front()){
					if(w2a.find(word)==w2a.end())w2a[word]=0;
					w2a[word]--;
				}
				queue.pop_front();
			}
			queue.push_back(text);
			for(auto it=w2a.begin();it!=w2a.end();it++){
				if(w2a[it->first]!=0){
					if(wordCount.find(it->first)!=wordCount.end()){
						wordSet.erase(make_pair(-wordCount[it->first],it->first));
						wordCount[it->first]+=w2a[it->first];
					}else{
						wordCount[it->first] = w2a[it->first];
					}
					wordSet.insert(make_pair(-wordCount[it->first],it->first));
				}
			}
		}else if(token=="<top"){
			int num,checked=0,minOccur=20000001;string tail;cin>>num>>tail;
			cout<<"<top "<<num<<">"<<endl;
			for(auto it=wordSet.begin();it!=wordSet.end();it++){
				if(checked++>=num && -(it->first)<minOccur)break;
				cout<<it->second<<" "<<-(it->first)<<endl;
				minOccur = min(minOccur,-(it->first));
			}
			cout<<"</top>"<<endl;
		}
	}
	return 0;
}