//This solution has not passed all test cases yet...

#include<iostream>
#include<unordered_map>
#include<vector>
#include<string>
#include<deque>
#include<cstdlib>
using namespace std;

#define iiMap unordered_map<int,unordered_map<int,int> >

class TheFlippingGame2{
private:
    int minFlips(int **board,int n,int m){
        int **gridId = (int**)malloc(sizeof(int*)*n);
        for(int i=0;i<n;i++){
            int *row = (int*)malloc(sizeof(int)*m);
            gridId[i] = row;
            for(int j=0;j<m;j++)gridId[i][j] = -1;
        }
        int curId = 0;
        iiMap dist;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(gridId[i][j]<0){
                    unordered_map<int,int> distRow;
                    dist[curId] = distRow;
                    gridId[i][j] = curId;
                    vector<int> stack(1,i*m+j);
                    while(!stack.empty()){
                        int cur = stack.back();stack.pop_back();
                        int ci = cur/m,cj = cur%m;
                        int up = ci-1,low = ci+1,left = cj-1,right = cj+1;
                        vector<int> neighbors;
                        if(up>=0)neighbors.push_back(up*m+cj);
                        if(low<n)neighbors.push_back(low*m+cj);
                        if(left>=0)neighbors.push_back(ci*m+left);
                        if(right<m)neighbors.push_back(ci*m+right);
                        for(int neigh:neighbors){
                            int ni = neigh/m,nj = neigh%m;
                            if(gridId[ni][nj]<0 && board[ni][nj]==board[ci][cj]){
                                stack.push_back(neigh);
                                gridId[ni][nj] = curId;
                            }else if(gridId[ni][nj]!=curId && gridId[ni][nj]>=0){
                                dist[curId][gridId[ni][nj]] = 1;
                                dist[gridId[ni][nj]][curId] = 1;
                            }
                        }
                    }
                    curId++;
                }
            }
        }
        for(int i=0;i<n;i++)free(gridId[i]);
        free(gridId);
        int ans = curId;
        for(int i=0;i<curId;i++){
            int *distance = (int*)malloc(sizeof(int)*curId), maxDist=0;
            for(int j=0;j<curId;j++)distance[j] = -1;
            distance[i] = 0;
            deque<int> queue(1,i);
            while(!queue.empty()){
                int cur = queue.front();queue.pop_front();
                maxDist = maxDist<distance[cur]?distance[cur]:maxDist;
                for(auto it=dist[cur].begin();it!=dist[cur].end();it++){
                    if(distance[it->first]<0){
                        distance[it->first] = distance[cur]+1;
                        queue.push_back(it->first);
                    }
                }
            }
            free(distance);
            ans = ans<maxDist?ans:maxDist;
        }
        return ans+1;
    }
public:
    int MinimumMoves(int n,int m,vector<string> x){
        int **flip0,**flip1;
        flip0 = (int**)malloc(sizeof(int*)*n);
        flip1 = (int**)malloc(sizeof(int*)*n);
        for(int i=0;i<n;i++){
            int *r0 = (int*)malloc(sizeof(int)*n);
            int *r1 = (int*)malloc(sizeof(int)*n);
            flip0[i] = r0;flip1[i] = r1;
            for(int j=0;j<m;j++){
                if(x[i][j]=='b'){
                    flip0[i][j] = 1;
                    flip1[i][j] = 1;
                }else if(x[i][j]=='e'){
                    flip0[i][j] = 0;
                    flip1[i][j] = 1;
                }else{
                    flip0[i][j] = 0;
                    flip1[i][j] = 0;
                }
            }
        }
        int ans0 = minFlips(flip0,n,m),ans1 = minFlips(flip1,n,m);
        return ans0<ans1?ans0:ans1;
    }
};


int main(){
    vector<string> x;
    x.push_back("ewewbbbb");
    x.push_back("bwebewww");
    TheFlippingGame2 solution;
    cout<<solution.MinimumMoves(2,8,x);
    return 0;
}













