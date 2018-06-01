#include<iostream>
#include<string>
#include<vector>
#include<utility>
#include<queue>
using namespace std;
#define pq priority_queue
#define INF 100000000

void dijkstra(int height,int width,int x,int y,vector<vector<char> > &_map,vector<vector<int> > &dist){
	pq<pair<int,int> > queue;
	queue.push(make_pair(0,x*width+y));
	dist[x][y] = 0;
	int dx[] = {-1,1,0,0},dy[] = {0,0,-1,1};
	while(!queue.empty()){
		int d=-queue.top().first,x=queue.top().second/width,y=queue.top().second%width;
		queue.pop();
		if(d>dist[x][y])continue;
		for(int i=0;i<4;i++){
			int xx=x+dx[i],yy=y+dy[i];
			if(_map[xx][yy]!='*'){
				int dd = _map[xx][yy]=='.'?0:1;
				if(d+dd<dist[xx][yy]){
					dist[xx][yy] = d+dd;
					queue.push(make_pair(-dist[xx][yy],xx*width+yy));
				}
			}
		}
	}
}

int main(){
	int tt;cin>>tt;
	for(int t=0;t<tt;t++){
		int h,w;cin>>h>>w;
		vector<vector<char> > _map;
		vector<vector<int> > dist,dist1,dist2;
		vector<int> xs(2,-1),ys(2,-1);
		int cp=0;
		for(int i=0;i<h+4;i++){
			vector<char> mr(w+4,'*');
			vector<int> dr(w+4,INF);
			vector<int> dr1(w+4,INF);
			vector<int> dr2(w+4,INF);
			_map.push_back(mr);
			dist.push_back(dr);
			dist1.push_back(dr1);
			dist2.push_back(dr2);
		}
		for(int i=0;i<h;i++){
			string row;cin>>row;
			_map[i+2][1] = '.';
			_map[i+2][w+2] = '.';
			for(int j=0;j<w;j++){
				_map[i+2][j+2] = row[j];
				if(row[j]=='$'){
					_map[i+2][j+2] = '.';
					xs[cp] = i+2;
					ys[cp] = j+2;
					cp++;
				}
			}
		}
		for(int i=1;i<w+3;i++){
			_map[1][i] = '.';
			_map[h+2][i] = '.';
		}
		dijkstra(h+4,w+4,1,1,_map,dist);
		dijkstra(h+4,w+4,xs[0],ys[0],_map,dist1);
		dijkstra(h+4,w+4,xs[1],ys[1],_map,dist2);
		int ans = INF;
		for(int i=0;i<h;i++){
			for(int j=0;j<w;j++){
				int res = dist[i+2][j+2]+dist1[i+2][j+2]+dist2[i+2][j+2];
				if(_map[i+2][j+2]=='#')res-=2;
				ans = res<ans?res:ans;
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}

