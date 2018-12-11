int V, E, s, u, v, w;
vector<vii> AdjList;

int main() {
    cin>>V>>E>>s;
    AdjList.assign(V, vii());
    int u,v,w;
    for(int i = 0; i < E; i++) {
        cin>>u>>v>>w;
        AdjList[u].push_back(ii(v, w));
    }
    // Dijkstra routine
    vi dist(V, INF); dist[s] = 0;
    // distance, node
    priority_queue<ii, vector<ii>, greater<ii> > pq;
    pq.push(ii(0,s));

    while(!pq.empty()) {
        ii front = pq.top(); pq.pop();
        int d = front.first, u = front.second;
        if (d > dist[u]) continue; // handle duplicates
        for(int j = 0; j < (int) AdjList[u].size(); j++) {
            ii v = AdjList[u][j];
            if(dist[u] + v.second < dist[v.first]) {
                dist[v.first] = dist[u] + v.second;
                pq.push(ii(dist[v.first], v.first));
            }
        }
    }

    // SPFA (Faster Bellman Ford)
    queue<int> q; q.push(S);
    vi in_queue(n, 0); in_queue[S] = 1;

    while(!q.empty()) {
        int u = q.front(); q.pop(); in_queue[u] = 0;
        for(auto v : AdjList[u]) {
            if(dist[u] + v.second < dist[v.first]) {
                dist[v.first] = dist[u] + v.second;
                if (!in_queue[v.first]) {
                    q.push(v.first);  // add to queue only if it's not in queue
                    in_queue[v.first] = 1;
                }
            }
        }
     }
 
}

