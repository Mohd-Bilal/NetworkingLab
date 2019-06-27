#include<iostream>
#include<climits>
using namespace std;


int main(){
    int N;
    cout<<"Enter the size of the matrix \n";
    cin>>N;
    int cost[N][N];
    int distance[N][N] = {INT_MAX};
    cout<<"Enter the cost matrix \n";
    for(int i = 0;i<N;i++)
        for(int j = 0;j<N;j++){
            cin>>cost[i][j];
            if(cost[i][j]!=INT_MAX)
            distance[i][j] = cost[i][j];
        }
    for(int i = 0;i<N;i++)   
        for(int j = 0;j<N;j++)
            for(int k = 0;k<N;k++)
            distance[i][j] = min(distance[i][j],cost[i][k]+distance[k][j]);
    cout<<"The distance matrix of the network is \n";
    for(int i = 0;i<N;i++){
        cout<<"\n";
        for(int j = 0;j<N;j++)
            cout<<distance[i][j]<<" ";
    }
    cout<<"\n";
    return 0;
}