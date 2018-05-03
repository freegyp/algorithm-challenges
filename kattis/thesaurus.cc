#include<iostream>
#include<vector>
#include<string>
#include<unordered_map>
#include<unordered_set>
#include<cstdlib>
using namespace std;

#define umap unordered_map
#define uset unordered_set

void safeInsert(umap<string,vector<string> > &graph,string left,string right){
	if(graph.find(left)==graph.end()){
		vector<string> r1;
		graph[left] = r1;
	}
	graph[left].push_back(right);
	if(graph.find(right)==graph.end()){
		vector<string> r2;
		graph[right] = r2;
	}
	graph[right].push_back(left);
}

void dfs(umap<string,vector<string> > &graph,umap<string,int> &wordGroupLower){
	umap<string,int> group;
	umap<int,int> groupMin;
	int curGroup = 0;
	for(auto it=graph.begin();it!=graph.end();it++){
		if(group.find(it->first)==group.end()){
			group[it->first] = curGroup;
			vector<string> stack(1,it->first);
			while(!stack.empty()){
				string cur = stack.back();stack.pop_back();
				if(groupMin.find(curGroup)==groupMin.end()){
					groupMin[curGroup] = cur.size();
				}else{
					groupMin[curGroup] = min(groupMin[curGroup],(int)(cur.size()));
				}
				for(string neigh:graph[cur]){
					if(group.find(neigh)==group.end()){
						group[neigh] = curGroup;
						stack.push_back(neigh);
					}
				}
			}
			curGroup++;
		}
	}
	for(auto it=group.begin();it!=group.end();it++){
		wordGroupLower[it->first] = groupMin[it->second];
	}
}

int main(){
	int n,m,ans=0;cin>>n>>m;
	vector<string> originalWords;
	umap<string,vector<string> > graph;
	umap<string,int> wordGroupLower;
	for(int i=0;i<n;i++){
		string s;cin>>s;
		originalWords.push_back(s);
	}
	for(int i=0;i<m;i++){
		string left,right;
		cin>>left>>right;
		safeInsert(graph,left,right);
	}
	dfs(graph,wordGroupLower);
	for(string s:originalWords){
		if(wordGroupLower.find(s)!=wordGroupLower.end()){
			ans += wordGroupLower[s];
		}else{
			ans += s.size();
		}
	}
	cout<<ans<<endl;
	return 0;
}

