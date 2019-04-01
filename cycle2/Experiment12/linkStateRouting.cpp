#include<iostream>
#include<vector>
#include<climits>
#include<algorithm>
using namespace std;


int main(){
    int N,S;
    cout<<"Enter the number of nodes in the network & the source node \n";
    cin>>N>>S;
    vector<int> distance(N);
    vector<bool> visited(N,false);
    int cost[N][N];
    cout<<"Enter the cost matrix\n";
    for(int i = 0;i<N;i++)
        for(int j = 0;j<N;j++)
            cin>>cost[i][j];
    for(int j = 0;j<N;j++)
        distance[j] = cost[S][j];                            
     
    int minimum,x;
    visited[S] = true;
    for(int i=0;i<N;i++){
        minimum = INT_MAX;
        for(int j = 0;j<N;j++){
            if(!visited[j])
                if(distance[j]<minimum){
                    x = j;
                    minimum = distance[j];
                }
        }
        visited[x] = true;
        for(int j = 0;j<N;j++){
            if(!visited[j]){
                if((minimum+cost[x][j])<distance[j])
                    distance[j] = minimum +cost[x][j];
                  
                
            }
        }
    
    }
    cout<<"The shortest distance from node:"<<S<<" to other nodes is ";
    for(int i = 0;i<N;i++)
        cout<<distance[i]<<" "; 
  
    return 0;
    
}