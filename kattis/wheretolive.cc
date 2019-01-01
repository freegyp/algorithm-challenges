#include<iostream>
#include<cstdlib>
using namespace std;

long eval(int *coords,int n,int x,int y){
	long res = 0;
	for(int i=0;i<n;i++){
		int xx = coords[i]/1001;
		int yy = coords[i]%1001;
		res += (xx-x)*(xx-x)+(yy-y)*(yy-y);
	}
	return res;
}

long rowEval(int *coords,int n,int x){
	int low=0,high=1001;
	while(high-low > 1){
		int mid = (high+low)/2;
		if(eval(coords,n,x,mid-1)>eval(coords,n,x,mid))low = mid;
		else high = mid;
	}
	return eval(coords,n,x,low);
}

int yEval(int *coords,int n,int x){
	int low=0,high=1001;
	while(high-low > 1){
		int mid = (high+low)/2;
		if(eval(coords,n,x,mid-1)>eval(coords,n,x,mid))low = mid;
		else high = mid;
	}
	return low;
}

int main(){
	int *coords = (int*)malloc(1000*sizeof(int));
	while(1){
		int n;cin>>n;
		if(n==0)break;
		for(int i=0;i<n;i++){
			int x,y;cin>>x>>y;
			coords[i] = x*1001+y;
		}
		int low=0,high=1001;
		while(high-low > 1){
			int mid = (high+low)/2;
			if(rowEval(coords,n,mid-1)>rowEval(coords,n,mid))low = mid;
			else high = mid;
		}
		cout<<low<<" ";
		int y = yEval(coords,n,low);
		cout<<y<<endl;
	}
	return 0;
}