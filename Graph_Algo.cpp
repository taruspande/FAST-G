#include<iostream>
#include<vector>
#include<stack>
#include<queue>

using namespace std;

class Graph{

    private:
    int v;
    vector<vector<pair<int, int> > > adjMatrix;

    public:

    Graph(int v){
        this->v=v;
        adjMatrix.resize(v);
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

    void addEdge(int u, int v, int w){
        adjMatrix[u].push_back(make_pair(v, w));
        adjMatrix[v].push_back(make_pair(u, w));
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
            int n=adjMatrix[u].size();
            for(int i=0; i<n; i++){
                v=adjMatrix[u][i].first;
                if(!visited[v]){
                    visited[v]=true;
                    q.push(v);
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
                int n=adjMatrix[u].size();

                for(int i=0; i<n; i++){
                    int v=adjMatrix[u][i].first;
                    if(!visited[v]){
                        s.push(v);
                    }
                }
            }
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

            for (int i=0; i<adjMatrix[u].size(); i++) {
                int v=adjMatrix[u][i].first;
                int weight = adjMatrix[u][i].second;
                if (!visited[v] && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
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
    
    cout<<"BFS Traversal: ";
    g.BFS(0);
    cout<<endl;

    cout<<"DFS Traversal: ";
    g.DFS(0);
    cout<<endl;

    g.Dijkstra(7);
    cout<<endl;

    return 0;
}