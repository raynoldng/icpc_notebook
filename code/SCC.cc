bool adjList[55][55];
vi dfs_num, dfs_low, S, visited;
int dfs_counter = 0, numSCC = 0;
int m, n; // nLocations, nEdges 

void tarjanSCC(int u) {
    dfs_low[u] = dfs_num[u] = dfs_counter++;
    S.push_back(u);
    visited[u] = 1;
    for(int v = 0; v < m; v++) {
        if(adjList[u][v]) {
            if(dfs_num[v] == -1) tarjanSCC(v);
            if(visited[v] == 1)
                dfs_low[u] = min(dfs_low[v], dfs_low[u]);
        }
    } 

    if(dfs_low[u] == dfs_num[u]) { //root
        printf("SCC %d\n", ++numSCC);
        while(1) {
            int v = S.back(); S.pop_back(); visited[v] = 0;
            printf("%d ", v);
            if(u == v) break;
        }
        printf("\n");
    }
}

int main() {
    m=8,n=9; // edges and vertices

    adjList[0][1] = true; adjList[1][3] = true; adjList[3][4] = true;
    adjList[4][5] = true; adjList[5][7] = true; adjList[7][6] = true;
    adjList[6][4] = true; adjList[3][2] = true; adjList[2][1] = true;

    dfs_num = vi(m, -1); dfs_low = vi(m, 0); visited = vi(m, 0);
    dfs_counter = numSCC = 0;

    for(int i = 0; i < m; i++) {
        if(dfs_num[i] == -1) {
            tarjanSCC(i);
        }
    }
    // 1: 6 7 4 5
    // 2: 2 3 1
    // 3: 0
}
