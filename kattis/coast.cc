#include<iostream>
#include<vector>
#include<string>
using namespace std;

int main(){
	int n,m,ans=0;cin>>n>>m;
	int dx[] = {0,0,-1,1};
	int dy[] = {-1,1,0,0};
	vector<vector<int> > matrix,checked;
	vector<int> row0(m+2,0),rChecked0(m+2,0),rowl(m+2,0),rCheckedl(m+2,0);
	matrix.push_back(row0);
	checked.push_back(rChecked0);
	for(int i=0;i<n;i++){
		vector<int> row(1,0),rChecked(1,0);
		string rstr;cin>>rstr;
		for(int j=0;j<m;j++){
			int num = (int)(rstr[j]-'0');
			row.push_back(num);
			rChecked.push_back(0);
		}
		row.push_back(0);
		rChecked.push_back(0);
		matrix.push_back(row);
		checked.push_back(rChecked);
	}
	matrix.push_back(rowl);
	checked.push_back(rCheckedl);
	vector<int> stack(1,0);
	checked[0][0] = 1;
	while(!stack.empty()){
		int x=stack.back()/(m+2),y=stack.back()%(m+2);stack.pop_back();
		for(int i=0;i<4;i++){
			int nx=x+dx[i],ny=y+dy[i];
			if(nx>=0 && nx<n+2 && ny>=0 && ny<m+2){
				if(matrix[nx][ny]==0 && checked[nx][ny]==0){
					checked[nx][ny] = 1;
					stack.push_back(nx*(m+2)+ny);
				}else if(matrix[nx][ny]==1){
					ans++;
				}
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}