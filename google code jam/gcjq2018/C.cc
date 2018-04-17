#include<iostream>
#include<set>
#include<unordered_map>
#include<tuple>
#include<fstream>
using namespace std;

int main(){
	int tt;cin>>tt;
	for(int t=0;t<tt;t++){
		int a;cin>>a;
		int curX=3,curY=3,area=0;
		while(area<a){
			int mask=0;
			while(mask != 511){
				cout<<curX<<" "<<curY<<endl;
				int xx,yy,base=0;cin>>xx>>yy;
				if(xx==0 && yy==0){
					area=a;break;
				}else if(xx==-1 && yy==-1){
					return 0;
				}
				if(xx==curX)base=3;
				else if(xx==curX+1)base=6;
				if(yy==curY)base+=1;
				else if(yy==curY+1)base+=2;
				mask |= 1<<base;
			}
			area += 9;
			curX += 3;
		}
	}
	return 0;
}