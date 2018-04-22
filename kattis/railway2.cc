//Not accepted yet...

#include<iostream>
#include<cstdlib>
#include<unordered_map>
#include<unordered_set>
#include<vector>
using namespace std;

#define umap unordered_map
#define uset unordered_set

void constructTree(umap<int,umap<int,int> > &graph,umap<int,vector<int> > &pred,vector<int> &depth,vector<int> &order){
	vector<int> directPred(graph.size()+1,0),stack(1,1);
	uset<int> past;
	int curOrder = 1;
	pred[1] = directPred;depth[1] = 1;
	past.insert(1);
	while(!stack.empty()){
		int cur = stack.back();stack.pop_back();
		order[cur] = curOrder++;
		for(auto it=graph[cur].begin();it!=graph[cur].end();it++){
			if(past.find(it->first)==past.end()){
				pred[1][it->first] = cur;
				depth[it->first] = depth[cur]+1;
				stack.push_back(it->first);
				past.insert(it->first);
			}
		}
	}
	for(int i=1;i<17;i++){
		//vector<int> _pred(graph.size()+1,0);
		pred[1<<i] = vector<int>(graph.size()+1,0);
		for(int j=1;j<graph.size()+1;j++){
			pred[1<<i][j] = pred[1<<(i-1)][pred[1<<(i-1)][j]];
		}
	}
}

int lca(int left,int right,vector<int> &depth,umap<int,vector<int> > &pred){
	int a=left,b=right;
	if(depth[a]<depth[b]){
		int temp = a;
		a = b;
		b = temp;
	}
	int dDepth = depth[a]-depth[b];
	for(int i=dDepth;i>0;i-=i&(-i)){
		a = pred[i&(-i)][a];
	}
	for(int i=(1<<16);i>0;i>>=1){
		if(pred[i][a]!=pred[i][b]){
			a = pred[i][a];
			b = pred[i][b];
		}
	}
	if(a==b)return a;
	else return pred[1][a];
}

void dfs(int cur,int pre,umap<int,umap<int,int> > &graph,vector<int> &counts){
	for(auto it=graph[cur].begin();it!=graph[cur].end();it++){
		if(it->first != pre){
			dfs(it->first,cur,graph,counts);
			counts[cur] += counts[it->first];
		}
	}
}

void safeInsert(umap<int,umap<int,int> > &graph,int left,int right,int idx){
	if(graph.find(left)==graph.end()){
		umap<int,int> r1;
		graph[left] = r1;
	}
	graph[left][right] = idx;
	if(graph.find(right)==graph.end()){
		umap<int,int> r2;
		graph[right] = r2;
	}
	graph[right][left] = idx;
}

int main(){
	int m,n,k;cin>>n>>m>>k;
	umap<int,umap<int,int> > graph;
	umap<int,vector<int> > pred;
	vector<int> starts(1,0),ends(1,0),nodeCount(n+1,0),depth(n+1,0),order(n+1,0),ans;
	for(int i=1;i<n;i++){
		int a,b;cin>>a>>b;
		safeInsert(graph,a,b,i);
		starts.push_back(a);
		ends.push_back(b);
	}
	constructTree(graph,pred,depth,order);
	for(int i=0;i<m;i++){
		int s;cin>>s;
		vector<int> group(s,0);
		for(int j=0;j<s;j++)cin>>group[j];
		for(int j=0;j<s;j++){
			int l = lca(group[j],group[(j+1)%s],depth,pred);
			nodeCount[group[j]]++;
			nodeCount[group[(j+1)%s]]++;
			nodeCount[l] -= 2;
		}
	}
	dfs(1,-1,graph,nodeCount);
	for(int i=1;i<n;i++){
		int a=starts[i],b=ends[i];
		if(order[a]>order[b]){
			int temp = a;
			a = b;
			b = temp;
		}
		if(nodeCount[b]>=2*k)ans.push_back(i);
	}
	cout<<ans.size()<<endl;
	for(int i=0;i<ans.size();i++){
		cout<<ans[i]<<" ";
	}
	cout<<endl;
	return 0;
}