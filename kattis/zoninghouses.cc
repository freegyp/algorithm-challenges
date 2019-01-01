#include<iostream>
#include<cstdlib>
#include<vector>
#include<algorithm>
#include<unordered_map>
using namespace std;
#define umap unordered_map
#define ll long long
#define unset 2147483647
#define bound 1000000000

int main(){
	int n,q;cin>>n>>q;
	umap<ll,int> address;
	int ***segTree = (int***)malloc(sizeof(int**)*n);
	for(int i=0;i<n;i++){
		segTree[i] = (int**)malloc(sizeof(int*)*17);
		int x,y;cin>>x>>y;
		address[(ll)(x+bound)*(2*bound+1)+(ll)(y+bound)] = i+1;
		for(int j=0;j<17;j++){
			segTree[i][j] = (int*)malloc(sizeof(int)*8);//xs,xs,xl,xl,ys,ys,yl,yl
			if(j==0){
				segTree[i][j][0] = x;segTree[i][j][1] = unset;
				segTree[i][j][2] = x;segTree[i][j][3] = unset;
				segTree[i][j][4] = y;segTree[i][j][5] = unset;
				segTree[i][j][6] = y;segTree[i][j][7] = unset;
			}else{
				vector<int> xss,xsl,yss,ysl;
				if(i-(1<<(j-1))>=0){
					for(int k=0;k<2;k++)if(segTree[i-(1<<(j-1))][j-1][k]!=unset)xss.push_back(segTree[i-(1<<(j-1))][j-1][k]);
					for(int k=2;k<4;k++)if(segTree[i-(1<<(j-1))][j-1][k]!=unset)xsl.push_back(segTree[i-(1<<(j-1))][j-1][k]);
					for(int k=4;k<6;k++)if(segTree[i-(1<<(j-1))][j-1][k]!=unset)yss.push_back(segTree[i-(1<<(j-1))][j-1][k]);
					for(int k=6;k<8;k++)if(segTree[i-(1<<(j-1))][j-1][k]!=unset)ysl.push_back(segTree[i-(1<<(j-1))][j-1][k]);
				}
				for(int k=0;k<2;k++)if(segTree[i][j-1][k]!=unset)xss.push_back(segTree[i][j-1][k]);
				for(int k=2;k<4;k++)if(segTree[i][j-1][k]!=unset)xsl.push_back(segTree[i][j-1][k]);
				for(int k=4;k<6;k++)if(segTree[i][j-1][k]!=unset)yss.push_back(segTree[i][j-1][k]);
				for(int k=6;k<8;k++)if(segTree[i][j-1][k]!=unset)ysl.push_back(segTree[i][j-1][k]);
				sort(xss.begin(),xss.end());
				sort(xsl.begin(),xsl.end());
				sort(yss.begin(),yss.end());
				sort(ysl.begin(),ysl.end());
				segTree[i][j][0] = xss[0];segTree[i][j][1] = xss.size()>1?xss[1]:unset;
				segTree[i][j][2] = xsl[xsl.size()-1];segTree[i][j][3] = xsl.size()>1?xsl[xsl.size()-2]:unset;
				segTree[i][j][4] = yss[0];segTree[i][j][5] = yss.size()>1?yss[1]:unset;
				segTree[i][j][6] = ysl[ysl.size()-1];segTree[i][j][7] = ysl.size()>1?ysl[ysl.size()-2]:unset;
			}
		}
	}
	for(int i=0;i<q;i++){
		int start,end;cin>>start>>end;
		int cur = end-1,offset = end-start+1;
		vector<int> xss,xsl,yss,ysl;
		while(offset>0){
			int rng=0;while((1<<rng)<(offset&-offset))rng++;
			for(int k=0;k<2;k++)if(segTree[cur][rng][k]!=unset)xss.push_back(segTree[cur][rng][k]);
			for(int k=2;k<4;k++)if(segTree[cur][rng][k]!=unset)xsl.push_back(segTree[cur][rng][k]);
			for(int k=4;k<6;k++)if(segTree[cur][rng][k]!=unset)yss.push_back(segTree[cur][rng][k]);
			for(int k=6;k<8;k++)if(segTree[cur][rng][k]!=unset)ysl.push_back(segTree[cur][rng][k]);
			cur -= (1<<rng);
			offset -= (1<<rng);
		}
		sort(xss.begin(),xss.end());
		sort(xsl.begin(),xsl.end());
		sort(yss.begin(),yss.end());
		sort(ysl.begin(),ysl.end());
		int xs1=xss[0],xs2=xss[1],xl1=xsl[xsl.size()-1],xl2=xsl[xsl.size()-2];
		int ys1=yss[0],ys2=yss[1],yl1=ysl[ysl.size()-1],yl2=ysl[ysl.size()-2];
		ll c1 = (ll)(xs1+bound)*(2*bound+1)+(ll)(ys1+bound);
		ll c2 = (ll)(xs1+bound)*(2*bound+1)+(ll)(yl1+bound);
		ll c3 = (ll)(xl1+bound)*(2*bound+1)+(ll)(ys1+bound);
		ll c4 = (ll)(xl1+bound)*(2*bound+1)+(ll)(yl1+bound);
		int ans = unset;
		if(address.find(c1)!=address.end() && address[c1]>=start && address[c1]<=end)ans = min(ans,max(xl1-xs2,yl1-ys2));
		if(address.find(c2)!=address.end() && address[c2]>=start && address[c2]<=end)ans = min(ans,max(xl1-xs2,yl2-ys1));
		if(address.find(c3)!=address.end() && address[c3]>=start && address[c3]<=end)ans = min(ans,max(xl2-xs1,yl1-ys2));
		if(address.find(c4)!=address.end() && address[c4]>=start && address[c4]<=end)ans = min(ans,max(xl2-xs1,yl2-ys1));
		ans = min(ans,max(xl1-xs2,yl1-ys1));
		ans = min(ans,max(xl2-xs1,yl1-ys1));
		ans = min(ans,max(xl1-xs1,yl1-ys2));
		ans = min(ans,max(xl1-xs1,yl2-ys1));
		ans = min(ans,max(xl1-xs1,yl1-ys1));
		cout<<ans<<endl;
	}
	return 0;
}