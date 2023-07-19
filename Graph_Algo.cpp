#include<iostream>
#include<vector>
#include<stack>
#include<queue>

using namespace std;

class Graph{

    private:
    int v;
    vector<vector<int> >  adjMatrix;
    int source;
    int sink;

    public:

    Graph(int v, int source=-1, int sink=-1, bool flowGraph=false){
        this->v=v;
        this->source=source;
        this->sink=sink;
        if(!flowGraph){
            adjMatrix.resize(v, vector<int>(v, INT_MAX));
        }
        else{
            adjMatrix.resize(v, vector<int>(v, 0));
        }
        
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

    void addFlowEdge(int u, int v, int capacity){
        adjMatrix[u][v]=capacity;
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

    bool flowBFS(vector<vector<int> >& residualGraph, vector<int>& parent, int source, int sink) {
        vector<bool> visited(v, false);
        queue<int> q;

        visited[source]=true;
        q.push(source);

        while (!q.empty()) {
            int u=q.front();
            q.pop();

            for (int i=0; i<v; ++i) {
                if (!visited[i] && residualGraph[u][i]>0) {
                    visited[i]=true;
                    parent[i]=u;
                    q.push(i);
                }
            }
        }

        return visited[sink];
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
        dist[start]=0;

        for (int i=0; i<v-1; i++) {
            int u=findMinDistance(dist, visited);
            if(u==-1){
                break;
            }
            visited[u]=true;

            for (int i=0; i<v; i++) {
                int weight=adjMatrix[u][i];
                if (!visited[i] && (dist[u]+weight)<dist[i] && weight!=INT_MAX) {
                    dist[i]=dist[u]+weight;
                }
            }
        }

        cout << "Shortest distances from vertex " << start << ":" << endl;
        for (int i=0; i<v; i++) {
            if (dist[i]==INT_MAX){
                cout <<"Vertex "<<i<<": Inf"<<endl;
            }
            else{
                cout<<"Vertex "<<i<<": "<<dist[i]<<endl;
            }
            
        }
    }

    void Prim(){
        vector<int> parent(v, -1);
        vector<int> dist(v, INT_MAX);
        vector<bool> visited(v, false);

        dist[0]=0;

        for(int count=0; count<v-1; count++){
            int u=findMinDistance(dist, visited);
            visited[u]=true;

            for(int i=0; i<v; i++){
                if(adjMatrix[u][i] && !visited[i] && adjMatrix[u][i]<dist[i]){
                    parent[i]=u;
                    dist[i]=adjMatrix[u][i];
                }
            }
        }

        cout<<"Minimum Spanning Tree (MST):"<<endl;
        for(int i=1; i<v; i++){
            cout<<"Edge: "<<parent[i]<<" - "<<i<<" Weight: "<<adjMatrix[i][parent[i]]<<endl;
        }
    }

    int FordFulkerson(int source, int sink) {
        vector<vector<int> > residualGraph(adjMatrix);
        vector<int> parent(v, -1);
        int maxFlow=0;

        while (flowBFS(residualGraph, parent, source, sink)) {
            int pathFlow=INT_MAX;

            for (int v=sink; v!=source; v=parent[v]) {
                int u=parent[v];
                pathFlow=min(pathFlow, residualGraph[u][v]);
            }

            for (int v=sink; v!=source; v=parent[v]) {
                int u=parent[v];
                residualGraph[u][v]-=pathFlow;
                residualGraph[v][u]+=pathFlow;
            }

            maxFlow+=pathFlow;
        }

        return maxFlow;
    }
};

int main(){
    Graph g1(9);
    Graph g2(11, 0, 10, true);
    g1.addEdge(0,1,4);
    g1.addEdge(0,7,8);
    g1.addEdge(1,2,8);
    g1.addEdge(1,7,11);
    g1.addEdge(2,3,7);
    g1.addEdge(2,5,4);
    g1.addEdge(2,8,2);
    g1.addEdge(3,4,9);
    g1.addEdge(3,5,14);
    g1.addEdge(4,5,10);
    g1.addEdge(5,6,2);
    g1.addEdge(6,8,6);
    g1.addEdge(6,7,1);
    g1.addEdge(7,8,7);

    g2.addFlowEdge(0, 1, 7);
    g2.addFlowEdge(0, 2, 2);
    g2.addFlowEdge(0, 3, 1);
    g2.addFlowEdge(1, 4, 2);
    g2.addFlowEdge(1, 5, 4);
    g2.addFlowEdge(2, 5, 5);
    g2.addFlowEdge(2, 6, 6);
    g2.addFlowEdge(3, 4, 4);
    g2.addFlowEdge(3, 8, 8);
    g2.addFlowEdge(4, 7, 7);
    g2.addFlowEdge(4, 8, 1);
    g2.addFlowEdge(5, 7, 3);
    g2.addFlowEdge(5, 9, 3);
    g2.addFlowEdge(5, 6, 8);
    g2.addFlowEdge(6, 9, 3);
    g2.addFlowEdge(7, 10, 1);
    g2.addFlowEdge(8, 10, 3);
    g2.addFlowEdge(9, 10, 4);


    cout<<endl<<"Graph 1"<<endl;
    g1.printAdjMatrix();
    cout<<endl;

    cout<<"BFS Traversal: ";
    g1.BFS(0);
    cout<<endl;

    cout<<"DFS Traversal: ";
    g1.DFS(0);
    cout<<endl;

    g1.Dijkstra(0);
    cout<<endl;

    g1.Prim();
    cout<<endl;

    cout<<endl<<"Graph 2"<<endl;
    g2.printAdjMatrix();
    cout<<"Max Flow: "<<g2.FordFulkerson(0, 10);
    return 0;
}