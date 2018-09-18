#include <bits/stdc++.h>
using namespace std;

#define FOR(x,n) for(int x = 0; x < n; ++x)

typedef unsigned long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<string> vs;
typedef vector<vi> vvi;

#define UNVISITED 0

vvi AdjList;
int dfsCounter, rootChildren, dfsRoot;
vi dfs_num, dfs_low, dfs_parent, art_vertex;

void artPointAndBridge(int u) {
	dfs_low[u] = dfs_num[u] = dfsCounter++;
	for(auto &v : AdjList[u]) {
		if(dfs_num[v] == UNVISITED) {
			dfs_parent[v] = u;
			if(u == dfsRoot) rootChildren++;

			artPointAndBridge(v);

			if(dfs_low[v] >= dfs_num[v]) // art point
				art_vertex[v] = true;
			if(dfs_low[v] > dfs_num[u]) {
				// (u,v) is bridge
				printf("(%d,%d) is a bridge\n", u, v);
			}
			//update dfs_low
			dfs_low[u] = min(dfs_low[u], dfs_low[v]);
		} else if(v != dfs_parent[u]) {
			// back edge and not direct cycle
			dfs_low[u] = min(dfs_low[u], dfs_low[v]);
		}
	}
}

int main() {

	int v = 6;

	AdjList.assign(v, vi());
	AdjList[0].push_back(1); AdjList[1].push_back(0);
	AdjList[1].push_back(2); AdjList[2].push_back(1);
	AdjList[1].push_back(3); AdjList[3].push_back(1);
	AdjList[1].push_back(4); AdjList[4].push_back(1);
	AdjList[4].push_back(5); AdjList[5].push_back(4);
	AdjList[1].push_back(5); AdjList[5].push_back(1);

	dfsCounter = 0, dfs_num.assign(v, UNVISITED), dfs_low.assign(v, 0);
	dfs_parent.assign(v, 0), art_vertex.assign(v, 0);

	printf("Bridges\n"); // (0,1), (1,2), (1,3)
	for(int i = 0; i < v; i++) {
		if(dfs_num[i] == UNVISITED) {
			dfsRoot = 1, rootChildren = 0, artPointAndBridge(i);
			art_vertex[dfsRoot] = (rootChildren > 1); // special case
		}
	}

	printf("Articuation points\n"); // 0,1,2,3
	for(int i = 0; i < v; i++) {
		if(art_vertex[i])
	 		printf("Vertex %d\n", i);
	}
}
