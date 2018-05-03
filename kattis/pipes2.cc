#include<iostream>
#include<string>
#include<vector>
#include<cstdlib>
using namespace std;

int main(){
	vector<string> answers;
	while(true){
		int rr,cc;cin>>rr>>cc;
		if(rr==0 && cc==0)break;
		int _mask = 1<<(cc+1);
		int *table1 = (int*)malloc(_mask*sizeof(int)),*table2 = (int*)malloc(_mask*sizeof(int));
		for(int i=0;i<_mask;i++){
			table1[i] = 0;table2[i] = 0;
		}
		table1[0] = 1;
		for(int r=0;r<rr;r++){
			for(int c=0;c<cc;c++){
				string s;cin>>s;
				if(s=="x")s.clear();
				int type = s.size();
				for(int i=0;i<_mask;i++)table2[i] = 0;
				for(int i=0;i<_mask;i++){
					if(table1[i]==1){
						switch(type){
							case 0:
								if((i&((1<<cc)+1))==0){
									table2[(i<<1)&(_mask-4)] = 1;
								}
								break;
							case 1:
								if((i&((1<<cc)+1))==1 || (i&((1<<cc)+1))==(1<<cc)){
									table2[(i<<1)&(_mask-4)] = 1;
								}else if((i&((1<<cc)+1))==0){
									if(r!=rr-1)table2[((i<<1)&(_mask-4))|2] = 1;
									if(c!=cc-1)table2[((i<<1)&(_mask-4))|1] = 1;
								}
								break;
							case 2:
								if((i&((1<<cc)+1))==(1<<cc)+1){
									table2[(i<<1)&(_mask-4)] = 1;
								}else if((i&((1<<cc)+1))==(1<<cc) && c!=cc-1){
									table2[((i<<1)&(_mask-4))|1] = 1;
								}else if((i&((1<<cc)+1))==1 && r!=rr-1){
									table2[((i<<1)&(_mask-4))|2] = 1;
								}else if((i&((1<<cc)+1))==0 && r!=rr-1 && c!=cc-1){
									table2[((i<<1)&(_mask-4))|3] = 1;
								}
								break;
							case 3:
								if((i&((1<<cc)+1))==(1<<cc)+1){
									if(r!=rr-1)table2[((i<<1)&(_mask-4))|2] = 1;
									if(c!=cc-1)table2[((i<<1)&(_mask-4))|1] = 1;
								}else if((i&((1<<cc)+1)) && r!=rr-1 && c!=cc-1){
									table2[((i<<1)&(_mask-4))|3] = 1;
								}
								break;
							case 4:
								if((i&((1<<cc)+1))==(1<<cc)+1 && r!=rr-1 && c!=cc-1){
									table2[((i<<1)&(_mask-4))|3] = 1;
								}
								break;
							default:
								break;
						}
					}
				}
				int *temp = table1;
				table1 = table2;
				table2 = temp;
			}
		}
		int found = 0;
		for(int i=0;i<_mask;i++){
			if(table1[i]==1){
				found = 1;
				break;
			}
		}
		if(found){
			answers.push_back("SOLVABLE");
		}else{
			answers.push_back("UNSOLVABLE");
		}
		free(table1);
		free(table2);
	}
	for(string ans:answers){
		cout<<ans<<endl;
	}
	return 0;
}