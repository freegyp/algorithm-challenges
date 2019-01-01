#include<iostream>
#include<algorithm>
#include<cstdlib>
#include<vector>
#include<queue>
using namespace std;
#define pq priority_queue
#define inf 1000000

class Edge{
public:
	int from,to,cap,cost;
	Edge *rev;
	Edge(int from,int to,int cap,int cost):from(from),to(to),cap(cap),cost(cost){}
};

class Node{
public:
	int x,y,dist,h;
	Edge *pred,*rpred;
	vector<Edge*> edges;
	Node(int x,int y):x(x),y(y),dist(inf),h(0),pred(NULL),rpred(NULL){}
};

int min_cost_flow(vector<Node*> &graph,int f){
	int res = 0;
	while(f>0){
		for(int i=0;i<202;i++){
			if(graph[i]){
				graph[i]->dist = inf;
				graph[i]->pred = NULL;
				graph[i]->rpred = NULL;
			}
		}
		graph[0]->dist = 0;
		pq<int> q;q.push(0);
		while(!q.empty()){
			int t = -q.top();q.pop();
			int d = t/1000,i = t%1000;
			//if(i==201)break;
			if(d==(graph[i]->dist)){
				for(int j=0;j<(graph[i]->edges.size());j++){
					if(graph[i]->edges[j]->cap>0 && (graph[graph[i]->edges[j]->to]->dist)>(graph[i]->dist + graph[i]->edges[j]->cost + graph[i]->h - graph[graph[i]->edges[j]->to]->h)){
						graph[graph[i]->edges[j]->to]->dist=graph[i]->dist + graph[i]->edges[j]->cost + graph[i]->h - graph[graph[i]->edges[j]->to]->h;
						graph[graph[i]->edges[j]->to]->pred = graph[i]->edges[j]->rev;
						graph[i]->rpred = graph[i]->edges[j];
						q.push(-1000*(graph[graph[i]->edges[j]->to]->dist)-graph[i]->edges[j]->to);
					}
				}
			}
		}
		if(graph[201]->dist==inf)return -1;
		int cur = 201,d = inf;
		while(cur>0){
			d = min(d,graph[cur]->pred->rev->cap);
			cur = graph[cur]->pred->to;
		}
		d = min(d,f);
		for(int i=0;i<202;i++){
			if(graph[i] && graph[i]->dist!=inf){
				graph[i]->h += graph[i]->dist;
			}
		}
		res += d*graph[201]->h;
		cur = 201;
		while(cur>0){
			graph[cur]->pred->cap += d;
			graph[cur]->pred->rev->cap -= d;
			cur = graph[cur]->pred->to;
		}
		f -= d;
	}
	return res;
}


int main(){
	vector<Node*> graph;for(int i=0;i<202;i++)graph.push_back(NULL);
	graph[0] = new Node(0,0);
	graph[201] = new Node(0,0);
	int n,m,total=0;cin>>n>>m;
	for(int i=0;i<n;i++){
		int x,y,b;cin>>x>>y>>b;
		Node *cur = new Node(x,y);
		Edge *pos = new Edge(0,i+1,b,0);
		Edge *neg = new Edge(i+1,0,0,0);
		pos->rev = neg;
		neg->rev = pos;
		graph[0]->edges.push_back(pos);
		cur->edges.push_back(neg);
		graph[i+1] = cur;
		total += b;
	}
	for(int i=0;i<m;i++){
		int x,y,b;cin>>x>>y>>b;
		Node *cur = new Node(x,y);
		Edge *pos = new Edge(i+101,201,b,0);
		Edge *neg = new Edge(201,i+101,0,0);
		pos->rev = neg;
		neg->rev = pos;
		cur->edges.push_back(pos);
		graph[201]->edges.push_back(neg);
		graph[i+101] = cur;
	}
	int real = 0;
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			int w;cin>>w;
			Edge *pos = new Edge(i+1,j+101,inf,abs(graph[i+1]->x-graph[j+101]->x)+abs(graph[i+1]->y-graph[j+101]->y)+1);
			Edge *neg = new Edge(j+101,i+1,0,-(pos->cost));
			pos->rev = neg;
			neg->rev = pos;
			graph[i+1]->edges.push_back(pos);
			graph[j+101]->edges.push_back(neg);
			real += w*(pos->cost);
		}
	}
	//cout<<real<<endl;
	int ideal = min_cost_flow(graph,total);
	if(ideal==real)cout<<"OPTIMAL"<<endl;
	else{
		cout<<"SUBOPTIMAL"<<endl;
		vector<vector<int> > table;
		for(int i=0;i<n;i++){
			vector<int> row(m,0);
			table.push_back(row);
		}
		for(int i=0;i<graph.size();i++){
			if(graph[i]){
				for(int j=0;j<graph[i]->edges.size();j++){
					if(graph[i]->edges[j]->to < graph[i]->edges[j]->from){
						if(graph[i]->edges[j]->to!=0 && graph[i]->edges[j]->from!=201){
							table[graph[i]->edges[j]->to-1][graph[i]->edges[j]->from-101] = graph[i]->edges[j]->cap;
						}
					}
				}
			}
		}
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				cout<<table[i][j];
				if(j!=m-1)cout<<" ";
				else cout<<endl;
			}
		}
	}
	return 0;
}