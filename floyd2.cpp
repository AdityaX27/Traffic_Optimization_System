#include <bits/stdc++.h>
#include <cstdlib>
using namespace std;
const int N=1000;
const int INF=1e9+10;

int dist[N][N];
int td[N][N];
double ko[N][N];
int dis[N];
int net[N][N];


int main()
{
    for(int i=0;i<N;++i)
    {
        for(int j=0;j<N;++j)
        {
            if(i==j){dist[i][j]=0;td[i][j]==0;ko[i][j]=0;}
            else {dist[i][j]=INF;td[i][j]=INF;ko[i][j]=INF;}
        }
    }
    int n,m; //n vertices m no of edges
    cin >> n >>m;
    for(int i=0;i<m;++i)
    {
        int x,y,wt,kt;// inputting weights and no of vehicals between two nodes
        cin>>x>>y>>wt>>kt; 
        dist[x][y]=wt;
        td[x][y]=kt;
        ko[x][y]=(wt/(60-(0.05*kt)));//optimization equation
     
    }
   // net[i][j] stores vertex next to i in the shortest path between (i,j)
      for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
          if(ko[i][j]==0)ko[i][j]=INF;  // there is no edge b/w (i,j)
          else net[i][j]=j;    // if there is an edge b/w i and j then j should be next to i
        }
      }

      for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++){
          for(int j=1;j<=n;j++){
            if(ko[i][j]>ko[i][k]+ko[k][j]){
              ko[i][j]=ko[i][k]+ko[k][j];
              net[i][j]=net[i][k];  // we found a vertx k next to i which further decrease the shortest path b/w (i,j) so updated it
            }
          }
        }
      }
      cout<<"-----OPTIMIZED SHORTEST TIME MATRIX(hrs)----"<<endl;
    cout<<endl;
    for(int i=1;i<=n;++i)
        {
            for(int j=1;j<=n;++j)
            { if(ko[i][j]==INF)
            {
                cout<<"I"<<" ";
            }
            else{
               cout<< ko[i][j]<<" ";
            }
        }
        cout<<endl;
    }
      // for printing the shortest optimized path between any two nodes in the graph given by the user
      int u,v;
      cout<<"Enter starting and ending node respectively to find the shortest path"<<endl;
      cin>>u>>v;
         
          cout<<u;
          while(u!=v){
            u=net[u][v];
            cout<<"-->"<<u;
          }
          cout<<endl;
       
}