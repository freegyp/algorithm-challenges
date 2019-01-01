#include<iostream>
#include<fstream>
#include<cstdlib>
#include<algorithm>
using namespace std;
#define ll long long
#define ld long double

int main(){
	int *heights = (int*)malloc(sizeof(int)*200000);
	ld *ups = (ld*)malloc(sizeof(ld)*200000);
	ld *downs = (ld*)malloc(sizeof(ld)*200000);
	ifstream fin("platform_parkour.txt",ifstream::in);
	ofstream fout("C.out",ofstream::out);
	int tt;fin>>tt;
	for(int t=1;t<=tt;t++){
		int n,m;fin>>n>>m;
		fin>>heights[0]>>heights[1];
		ups[0] = 1000000.0;ups[1] = 1000000.0;
		downs[0] = 1000000.0;downs[1] = 1000000.0;
		ll w,x,y,z;fin>>w>>x>>y>>z;
		for(int i=2;i<n;i++){
			heights[i] = (int)((w*(ll)heights[i-2]+x*(ll)heights[i-1]+y)%z);
			ups[i] = 1000000.0;
			downs[i] = 1000000.0;
		}
		for(int i=0;i<m;i++){
			int a,b;
			ld u,d;
			fin>>a>>b>>u>>d;
			if(a<b){
				for(int j=a-1;j<b-1;j++){
					ups[j] = min(ups[j],u);
					downs[j] = min(downs[j],d);
				}
			}else{
				for(int j=b-1;j<a-1;j++){
					ups[j] = min(ups[j],d);
					downs[j] = min(downs[j],u);
				}
			}
		}
		ld lower=0.0,upper=(ld)z;
		while(upper-lower>=1e-6){
			int works = 1;
			ld offset = (lower+upper)/2.0,left=0.0,right=1000000000.0;
			for(int i=0;i<n;i++){
				ld left2 = (ld)heights[i]-offset,right2 = (ld)heights[i]+offset;
				left = max(left,left2);
				right = min(right,right2);
				if(right<left){
					works = 0;
					break;
				}else{
					left -= downs[i];
					right += ups[i];
					left = max((ld)0.0,left);
				}
			}
			if(works)upper = offset;
			else lower = offset;
		}
		fout.precision(11);
		fout<<"Case #"<<t<<": "<<upper<<endl;
	}
	return 0;
}