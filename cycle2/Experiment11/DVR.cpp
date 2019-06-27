#include<iostream>
using namespace std;

int main(){
    int N;
    cin>>N;
    int cost[N][N];
    int distance[N][N] = {0};
    for(int i = 0;i<N;i++)
        for(int j = 0;j<N;j++){
            cin>>cost[i][j];
            if(cost[i][j] != INT_MAX)
                distance[i][j] = cost[i][j];    
        }
    for(int i = 0;i<N;i++)
        for(int j = 0;j<N;j++)
            for(int k = 0;k<N;k++)
                distance[i][j] = min(distance[i][j],cost[i][k]+distance[k][j]);
    for(int i = 0;i<N;i++){
        cout<<"\n";
        for(int j = 0;j<N;j++)
            cout<<distance[i][j]<<" ";
    }
    return 0;
}