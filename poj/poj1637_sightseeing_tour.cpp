#include<iostream>
#include<algorithm>
#include<cstdlib>
#include<string>
#include<vector>
using namespace std;
#define Graph vector<vector<Edge*> >
#define inf 2000

class Edge{
public:
	int dest,isrev,cap;
	Edge *rev;
	Edge(int dest,int isrev=0):dest(dest),isrev(isrev){
		if(isrev)cap=0;
		else cap=1;
	}
};

int dfs(Graph &graph,int s,int t){
	vector<int> stack(1,s),cap(graph.size(),0);
	vector<Edge*> pred(graph.size(),NULL);
	cap[s] = inf;
	while(!stack.empty()){
		int cur = stack.back();stack.pop_back();
		for(int i=0;i<graph[cur].size();i++){
			if((graph[cur][i]->cap)>0 && (cap[graph[cur][i]->dest]==0)){
				stack.push_back(graph[cur][i]->dest);
				pred[graph[cur][i]->dest] = graph[cur][i]->rev;
				cap[graph[cur][i]->dest] = min(cap[cur],graph[cur][i]->cap);
			}
		}
	}
	if(cap[t]>0){
		int cur = t;
		while(cur!=s){
			pred[cur]->cap+=cap[t];
			pred[cur]->rev->cap -= cap[t];
			cur = pred[cur]->dest;
		}
		return cap[t];
	}
	return 0;
}

int max_flow(Graph &graph){
	int flow = 0;
	while(1){
		int f=dfs(graph,0,graph.size()-1);
		if(f==0)return flow;
		flow += f;
	}
}

void safeInsert(Graph &graph,int s,int t,int mode=0){
	Edge *edge = new Edge(t);
	Edge *revEdge = new Edge(s,mode);
	edge->rev = revEdge;
	revEdge->rev = edge;
	graph[s].push_back(edge);
	graph[t].push_back(revEdge);
}


int main(){
	int tt;cin>>tt;
	for(int t=0;t<tt;t++){
		int m,s,expectedFlow=0;cin>>m>>s;
		Graph graph;
		for(int i=0;i<m+2;i++){
			vector<Edge*> row;
			graph.push_back(row);
		}
		for(int i=0;i<s;i++){
			int x,y,d;cin>>x>>y>>d;
			if(x!=y){
				if(d==0)safeInsert(graph,x,y);
				else{
					safeInsert(graph,0,y,1);
					safeInsert(graph,x,m+1,1);
					expectedFlow++;
				}
			}
		}
		int f = max_flow(graph);
		if(f==expectedFlow){
			int possible = 1;
			for(int i=0;i<graph.size();i++){
				int count = 0;
				for(int j=0;j<graph[i].size();j++){
					if(!(graph[i][j]->isrev) && (graph[i][j]->cap)==1)count++;
				}
				if(count%2==1){
					possible=0;
					break;
				}
			}
			if(possible)cout<<"possible"<<endl;
			else cout<<"impossible"<<endl;
		}else{
			cout<<"impossible"<<endl;
		}
	}
	return 0;
}
