//Not accepted yet...
#include<iostream>
#include<cstdlib>
#include<set>
using namespace std;
#define miset multiset<int>
#define _round 360000
#define inf 1000000000

int normalize(int angle){
	while(angle<0)angle += _round;
	angle %= _round;
	return angle;
}

void insertAngle(int angle,miset &angles,miset &diffs){
	auto it = angles.insert(angle);
	//if(angles.size()==1)return;
	auto pt=it,lt=it;lt++;
	int prev,next=(lt==angles.end())?(*angles.begin()):(*lt);
	if(pt==angles.begin()){
		prev = *angles.rbegin();
	}else{
		pt--;prev = (*pt);
	}
	int o=next-prev,n1=angle-prev,n2=next-angle;
	while(o<=0)o+=_round;
	while(n1<=0)n1+=_round;
	while(n2<=0)n2+=_round;
	if(diffs.find(o)!=diffs.end())diffs.erase(diffs.find(o));
	diffs.insert(n1);
	if(angles.size()>1)diffs.insert(n2);
	while(diffs.size()>1 && diffs.find(_round)!=diffs.end())diffs.erase(diffs.find(_round));
}

void removeAngle(int angle,miset &angles,miset &diffs){
	if(angles.find(angle)==angles.end())return;
	auto it=angles.find(angle);
	auto pt=it,lt=it;lt++;
	int prev,next=(lt==angles.end())?(*angles.begin()):(*lt);
	if(pt==angles.begin()){
		prev = *angles.rbegin();
	}else{
		pt--;prev = (*pt);
	}
	angles.erase(it);
	int n=next-prev,o1=angle-prev,o2=next-angle;
	while(n<=0)n+=_round;
	while(o1<=0)o1+=_round;
	while(o2<=0)o2+=_round;
	if(diffs.find(o1)!=diffs.end())diffs.erase(diffs.find(o1));
	if(angles.size()>0){
		if(diffs.find(o2)!=diffs.end())diffs.erase(diffs.find(o2));
		diffs.insert(n);
	}
	while(diffs.size()>1 && diffs.find(_round)!=diffs.end())diffs.erase(diffs.find(_round));
}

int angleScope(miset &diffs){
	if(diffs.empty())return 0;
	return _round-(*diffs.rbegin());
}

int main(){
	int t,n;cin>>t>>n;
	int ***ranges,**transTable,**pointTable;
	transTable = (int**)malloc(sizeof(int*)*t);
	for(int i=0;i<t;i++){
		transTable[i] = (int*)malloc(sizeof(int)*2);
		cin>>transTable[i][0]>>transTable[i][1];
	}
	pointTable = (int**)malloc(sizeof(int*)*n);
	for(int i=0;i<n;i++){
		pointTable[i] = (int*)malloc(sizeof(int)*2);
		if(i>0){
			cin>>pointTable[i][0]>>pointTable[i][1];
			normalize(pointTable[i][1]);
		}
	}
	for(int i=0;i<n;i++){
		if(i==0){
			pointTable[i][0] = 0;
			pointTable[i][1] = (n>1)?pointTable[i+1][1]:0;
		}else if(i>1){
			pointTable[i][1] += pointTable[i-1][1];
			pointTable[i][1] = normalize(pointTable[i][1]);
		}
	}
	ranges = (int***)malloc(t*sizeof(int**));
	for(int i=0;i<t;i++){
		ranges[i] = (int**)malloc(n*sizeof(int*));
		int start=-1,end=-1,dist=0;
		miset angles,diffs;
		//cout<<i<<endl;
		for(int j=0;j<n;j++){
			ranges[i][j] = (int*)malloc(2*sizeof(int));
			dist -= pointTable[j][0];
			removeAngle(pointTable[j][1],angles,diffs);
			while(dist<transTable[i][0] && start<n)if((++start)<n)dist += pointTable[start][0];
			while(angleScope(diffs)<=transTable[i][1] && end<n)if((++end)<n)insertAngle(pointTable[end][1],angles,diffs);
			ranges[i][j][0] = start;
			ranges[i][j][1] = end;
			/*cout<<start<<" "<<end<<endl;
			for(auto it=angles.begin();it!=angles.end();it++)cout<<(*it)<<" ";
			cout<<endl;
			for(auto it=diffs.begin();it!=diffs.end();it++)cout<<(*it)<<" ";
			cout<<endl;*/
		}
	}
	int **table = (int**)malloc(n*sizeof(int*));
	for(int i=n-1;i>=0;i--){
		table[i] = (int*)malloc(16*sizeof(int));
		if(i==n-1)table[i][0] = 0;
		else{
			table[i][0] = inf;
			for(int j=0;j<t;j++){
				if(ranges[j][i][0]<ranges[j][i][1]){
					int offset = 0;
					while(ranges[j][i][0]+(1<<offset)<ranges[j][i][1]-(1<<offset))offset++;
					table[i][0] = min(table[i][0],min(table[ranges[j][i][0]][offset],table[ranges[j][i][1]-(1<<offset)][offset])+1);
				}
			}
		}
		for(int j=1;j<16;j++){
			int nidx = i+(1<<(j-1));
			int nxt = nidx<n?table[nidx][j]:inf;
			table[i][j] = min(table[i][j-1],nxt);
		}
	}
	if(table[0][0]==inf)cout<<"IMPOSSIBLE"<<endl;
	else cout<<table[0][0]<<endl;
	return 0;
}