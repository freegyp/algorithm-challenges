#include<iostream>
#include<queue>
#include<utility>
using namespace std;
#define pq priority_queue

int main(){
	int tt;cin>>tt;
	for(int t=0;t<tt;t++){
		int n;cin>>n;
		pq<pair<float,int> > q;
		for(int i=1;i<=n;i++){
			double a,b,c;cin>>a>>b>>c;
			double res = c+b*b/(4.0*a);
			q.push(make_pair(res,i));
		}
		cout<<q.top().second<<endl;
	}
	return 0;
}