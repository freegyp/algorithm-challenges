#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<utility>
#include<unordered_map>
using namespace std;
#define umap unordered_map
#define pq priority_queue
#define INF 100000000

class Node{
public:
	umap<Node*,int> neighbors;
	int dist,x,y,digit;
	Node *pred;
	Node(int x,int y,int digit,int dist=INF,Node *pred=NULL):x(x),y(y),dist(dist),pred(pred),digit(digit){}
	void addNeighbor(Node *other,int weight){
		neighbors[other] = weight;
	}
};

int main(){
	int h,w;
	int dj[] = {-1,0,1};
	while(true){
		cin>>h>>w;
		if(h==0 && w==0)break;
		vector<vector<char> > res;
		vector<vector<Node*> > nodes;
		pq<pair<int,Node*> > _queue;
		for(int i=0;i<h;i++){
			string s;cin>>s;
			vector<char> row;
			vector<Node*> nRow;
			for(int j=0;j<w;j++){
				int digit = (int)(s[j]-'0');
				row.push_back(s[j]);
				if(i==0){
					Node *node = new Node(i,j,digit,digit,NULL);
					_queue.push(make_pair(-digit,node));
					if(j>0){
						nRow[j-1]->addNeighbor(node,digit);
						node->addNeighbor(nRow[j-1],nRow[j-1]->digit);
					}
					nRow.push_back(node);
				}else{
					Node *node = new Node(i,j,digit);
					if(j>0){
						nRow[j-1]->addNeighbor(node,digit);
						node->addNeighbor(nRow[j-1],nRow[j-1]->digit);
					}
					for(int k=0;k<3;k++){
						if((j+dj[k])>=0 && (j+dj[k])<w){
							nodes[i-1][j+dj[k]]->addNeighbor(node,digit);
							node->addNeighbor(nodes[i-1][j+dj[k]],nodes[i-1][j+dj[k]]->digit);
						}
					}
					nRow.push_back(node);
				}
			}
			res.push_back(row);
			nodes.push_back(nRow);
		}
		Node *end = new Node(-1,-1,0);
		for(int i=0;i<w;i++){
			nodes[h-1][i]->addNeighbor(end,0);
			end->addNeighbor(nodes[h-1][i],nodes[h-1][i]->digit);
		}
		while(!_queue.empty()){
			int dist = -_queue.top().first;
			Node *cur = _queue.top().second;
			_queue.pop();
			if(dist==cur->dist){
				for(auto it=(cur->neighbors).begin();it!=(cur->neighbors).end();it++){
					Node *neigh = it->first;
					int dd = it->second;
					if(dist+dd<neigh->dist){
						neigh->dist = dist+dd;
						neigh->pred = cur;
						_queue.push(make_pair(-dist-dd,neigh));
					}
				}
			}
		}
		Node *cur = end;
		while(cur!=NULL){
			if(cur->x>=0 && cur->y>=0){
				res[cur->x][cur->y] = ' ';
			}
			cur = cur->pred;
		}
		for(int i=0;i<h;i++){
			for(int j=0;j<w;j++)cout<<res[i][j];
			cout<<endl;
		}
		cout<<endl;
	}
	return 0;
}