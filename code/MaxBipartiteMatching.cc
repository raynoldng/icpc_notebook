// This code performs maximum bipartite matching.
//
// Running time: O(|E| |V|) -- often much faster in practice
//
//   INPUT: w[i][j] = edge between row node i and column node j
//   OUTPUT: mr[i] = assignment for row node i, -1 if unassigned
//           mc[j] = assignment for column node j, -1 if unassigned
//           function returns number of matches made
typedef vector<int> VI;
typedef vector<VI> VVI;

bool FindMatch(int i, const VVI &w, VI &mr, VI &mc, VI &seen) {
  for (int j = 0; j < w[i].size(); j++) {
    if (w[i][j] && !seen[j]) {
      seen[j] = true;
      if (mc[j] < 0 || FindMatch(mc[j], w, mr, mc, seen)) {
        mr[i] = j;
        mc[j] = i;
        return true;
      }
    }
  }
  return false;
}

int BipartiteMatching(const VVI &w, VI &mr, VI &mc) {
  mr = VI(w.size(), -1);
  mc = VI(w[0].size(), -1);
  
  int ct = 0;
  for (int i = 0; i < w.size(); i++) {
    VI seen(w[0].size());
    if (FindMatch(i, w, mr, mc, seen)) ct++;
  }
  return ct;
}

/*
1. max matching should have been found first
2. change each edge in matching into a directed edge from right to left
3. change each edge not used in matching into a directed edge from left to right
4. compute T: set of vertices reachable from unmatched vertices on the left (including themselves)
5. MVC = vertices cover consists of all vertices on the right that are in T, and all vertices on the left that are not in T
*/
// OUTPUT: <row/col idx, 0:row/1:col>
const int LEFT = 0;
const int RIGHT = 1;
vii MVC(vvi &w, vi &mr, vi &mc) {
    set<ii> T;
    queue<ii> q;
    for(int i=0;i<mr.size();i++){
        if(mr[i]==-1) {
            q.push({i, LEFT});
            T.insert({i, LEFT});
        } 
    }
    while(!q.empty()) {
        ii curr = q.front(); q.pop();
        int u = curr.first;
        int type = curr.second;
        if(type == LEFT) {
            for(int v=0;v<mc.size();v++){
                ii next = {v, RIGHT};
                if(w[u][v] && mr[u]!=v && !T.count(next)) {
                    T.insert(next);
                    q.push(next);
                }
            }
        } else {
            // RIGHT
            for(int v=0;v<mr.size();v++){
                ii next = {v, LEFT};
                if(w[v][u] && mr[v]==u && !T.count(next)) {
                    T.insert(next);
                    q.push(next);
                }
            }
        }
    }

    vii mvc;
    for(int i=0;i<mr.size();i++) if(!T.count({i, LEFT})) mvc.push_back({i, LEFT});
    for(int i=0;i<mc.size();i++) if(T.count({i, RIGHT})) mvc.push_back({i, RIGHT});

    return mvc;
}
