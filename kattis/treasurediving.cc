#include<iostream>
#include<vector>
#include<unordered_map>
#include<unordered_set>
#include<utility>
#include<queue>
using namespace std;
#define ll long long
#define umap unordered_map
#define uset unordered_set
#define pq priority_queue
#define INF 1000000000000000000;

void safeInsert(umap<int,umap<int,ll> > &graph,int left,int right,ll dist){
	if(graph.find(left)==graph.end()){
		umap<int,ll> row1;
		graph[left] = row1;
	}
	graph[left][right] = dist;
	if(graph.find(right)==graph.end()){
		umap<int,ll> row2;
		graph[right] = row2;
	}
	graph[right][left] = dist;
}

void dijkstra(umap<int,umap<int,ll> > &graph,umap<int,umap<int,ll> > &dist,uset<int> &caves,int start){
	umap<int,ll> dfstart;
	dfstart[start] = 0;
	pq<pair<ll,int> > heap;
	heap.push(make_pair(0,start));
	while(!heap.empty()){
		ll d=-(heap.top().first);
		int node=heap.top().second;
		heap.pop();
		if(d==dfstart[node]){
			for(auto it=graph[node].begin();it!=graph[node].end();it++){
				int neigh = it->first,dd = it->second;
				if(dfstart.find(neigh)==dfstart.end() || dfstart[neigh]>d+dd){
					dfstart[neigh] = d+dd;
					heap.push(make_pair(-d-dd,neigh));
				}
			}
		}
	}
	for(auto it=dfstart.begin();it!=dfstart.end();it++){
		int other = it->first,d = it->second;
		if(caves.find(other)!=caves.end() && other!=start){
			safeInsert(dist,start,other,d);
		}
	}
}

void dfs(umap<int,umap<int,ll> > &graph,uset<int> &reachable){
	reachable.insert(0);
	vector<int> stack(1,0);
	while(!stack.empty()){
		int cur = stack.back();stack.pop_back();
		for(auto it=graph[cur].begin();it!=graph[cur].end();it++){
			if(reachable.find(it->first)==reachable.end()){
				stack.push_back(it->first);
				reachable.insert(it->first);
			}
		}
	}
}

int maskSize(int mask){
	int res=0;
	for(int m=mask;m>0;m-=m&-m)res++;
	return res;
}

int main(){
	int tt;cin>>tt;
	for(int t=0;t<tt;t++){
		int n,m,ans=0,zero=0;cin>>n>>m;
		umap<int,umap<int,ll> > graph,dist;
		for(int i=0;i<m;i++){
			int a,b;ll d;
			cin>>a>>b>>d;
			safeInsert(graph,a,b,d);
		}
		uset<int> reachable,caves;
		vector<int> caveList;
		dfs(graph,reachable);
		int ii;cin>>ii;
		for(int i=0;i<ii;i++){
			int cc;cin>>cc;
			if(cc!=0 && reachable.find(cc)!=reachable.end()){
				caves.insert(cc);
				caveList.push_back(cc);
			}else if(cc==0)zero=1;
		}
		dijkstra(graph,dist,caves,0);
		for(int cave:caveList){
			dijkstra(graph,dist,caves,cave);
		}
		ii = caveList.size();
		ll limit;cin>>limit;
		umap<int,int> m2c;
		for(int i=0;i<ii;i++){
			m2c[1<<i] = caveList[i];
		}
		umap<int,umap<int,ll> > table;
		for(int mask=1;mask<(1<<ii);mask++){
			umap<int,ll> row;table[mask] = row;
			if(mask==(mask&-mask)){
				table[mask][mask] = dist[0][m2c[mask]];
				if(table[mask][mask]+dist[0][mask]<=limit){
					ans = ans>1?ans:1;
				}
			}else{
				for(int i=mask;i>0;i-=i&-i){
					int premask = mask^(i&-i);
					table[mask][i&-i] = INF;
					for(int j=premask;j>0;j-=j&-j){
						table[mask][i&-i] = table[mask][i&-i]<table[premask][j&-j]+dist[m2c[i&-i]][m2c[j&-j]]?table[mask][i&-i]:table[premask][j&-j]+dist[m2c[i&-i]][m2c[j&-j]];
					}
					if(table[mask][i&-i]+dist[0][m2c[i&-i]]<=limit){
						ans = ans>maskSize(mask)?ans:maskSize(mask);
					}
				}
			}
		}
		cout<<ans+zero<<endl;
	}
	return 0;
}

