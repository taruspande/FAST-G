#include<iostream>
#include<vector>
#include<stack>
#include<queue>

using namespace std;

class Graph{

    private:
    int v;
    vector<vector<int> >  adjMatrix;

    public:

    Graph(int v){
        this->v=v;
        adjMatrix.resize(v, vector<int>(v, INT_MAX));
    }

    int findMinDistance(vector<int>& dist, vector<bool>& visited) {
        int minDist = INT_MAX;
        int minIndex = -1;

        for (int i = 0; i < v; i++) {
            if (!visited[i] && dist[i] < minDist) {
                minDist = dist[i];
                minIndex = i;
            }
        }

        return minIndex;
    }

    void addEdge(int u, int v, int weight, bool dir=0){
        adjMatrix[u][v]=weight;
        if(!dir){
            adjMatrix[v][u]=weight;
        }
    }

    void BFS(int start){
        vector<bool> visited(v, false);
        queue<int> q;
        visited[start]=true;
        q.push(start);

        while(!q.empty()){
            int u=q.front();
            q.pop();
            cout<<u<<" ";
            for(int i=0; i<v; i++){
                if(!visited[i] && adjMatrix[u][i]!=INT_MAX){
                    visited[i]=true;
                    q.push(i);
                }
            }
        }
    }

    void DFS(int start){
        vector<bool> visited(v, false);
        stack<int> s;
        s.push(start);

        while(!s.empty()){
            int u=s.top();
            s.pop();

            if(!visited[u]){
                visited[u]=true;
                cout<<u<<" ";

                for(int i=0; i<v; i++){
                    if(!visited[i] && adjMatrix[u][i]!=INT_MAX){
                        s.push(i);
                    }
                }
            }
        }
        cout<<endl;
    }

    void printAdjMatrix(){
        for(int i=0; i<v; i++){
            for(int j=0; j<v; j++){
                if(adjMatrix[i][j]==INT_MAX){
                    cout<<"∞"<<"\t";
                }
                else{
                    cout<<adjMatrix[i][j]<<"\t";
                }
            }
            cout<<endl;
        }
    }

    void Dijkstra(int start) {
        vector<int> dist(v, INT_MAX);
        vector<bool> visited(v, false);
        dist[start] = 0;

        for (int i = 0; i < v - 1; i++) {
            int u = findMinDistance(dist, visited);
            if(u==-1){
                break;
            }
            visited[u] = true;

            for (int i=0; i<v; i++) {
                int weight = adjMatrix[u][i];
                if (!visited[i] && (dist[u] + weight) < dist[i] && weight!=INT_MAX) {
                    dist[i] = dist[u] + weight;
                }
            }
        }

        cout << "Shortest distances from vertex " << start << ":" << endl;
        for (int i = 0; i < v; i++) {
            if (dist[i]==INT_MAX){
                cout << "Vertex " << i << ": Inf" << endl;
            }
            else{
                cout << "Vertex " << i << ": " << dist[i] << endl;
            }
            
        }
    }

    void Prim(){
        vector<int> parent(v, -1);
        vector<int> dist(v, INT_MAX);
        vector<bool> visited(v, false);

        dist[0]=0;

        for(int count = 0; count < v - 1; count++){
            int u = findMinDistance(dist, visited);
            visited[u] = true;

            for(int i = 0; i < v; i++){
                if(adjMatrix[u][i] && !visited[i] && adjMatrix[u][i] < dist[i]){
                    parent[i] = u;
                    dist[i] = adjMatrix[u][i];
                }
            }
        }

        cout << "Minimum Spanning Tree (MST):" << endl;
        for(int i = 1; i < v; i++){
            cout << "Edge: " << parent[i] << " - " << i << " Weight: " << adjMatrix[i][parent[i]] << endl;
        }
    }
};

int main(){
    Graph g(9);
    g.addEdge(0,1,4);
    g.addEdge(0,7,8);
    g.addEdge(1,2,8);
    g.addEdge(1,7,11);
    g.addEdge(2,3,7);
    g.addEdge(2,5,4);
    g.addEdge(2,8,2);
    g.addEdge(3,4,9);
    g.addEdge(3,5,14);
    g.addEdge(4,5,10);
    g.addEdge(5,6,2);
    g.addEdge(6,8,6);
    g.addEdge(6,7,1);
    g.addEdge(7,8,7);

    cout<<endl;
    g.printAdjMatrix();
    cout<<endl;

    cout<<"BFS Traversal: ";
    g.BFS(0);
    cout<<endl;

    cout<<"DFS Traversal: ";
    g.DFS(0);
    cout<<endl;

    g.Dijkstra(0);
    cout<<endl;

    g.Prim();
    cout<<endl;

    return 0;
}