#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

class edmond_blossom {
private:
    std::vector<std::vector<int>> adj_list;
    std::vector<int> match;
    std::vector<int> parent;
    std::vector<int> blossom_root;
    std::vector<bool> in_queue;
    std::vector<bool> in_blossom;
    std::queue<int> process_queue;
    int num_v;

    /// Find the lowest common ancestor between u and v.
    /// The specified root represents an upper bound.
    int get_lca(int root, int u, int v) {
        std::vector<bool> in_path(num_v, false);

        for (u = blossom_root[u]; ; u = blossom_root[parent[match[u]]]) {
            in_path[u] = true;
            if (u == root) {
                break;
            }
        }

        for (v = blossom_root[v]; ; v = blossom_root[parent[match[v]]]) {
            if (in_path[v]) {
                return v;
            }
        }
    }

    /// Mark the vertices between u and the specified lowest
    /// common ancestor for contraction where necessary.
    void mark_blossom(int lca, int u) {
        while (blossom_root[u] != lca) {
            int v = match[u];
            in_blossom[blossom_root[u]] = true;
            in_blossom[blossom_root[v]] = true;

            u = parent[v];
            if (blossom_root[u] != lca) {
                parent[u] = v;
            }
        }
    }

    /// Contract the blossom that is formed after processing
    /// the edge u-v.
    void contract_blossom(int source, int u, int v) {
        int lca = get_lca(source, u, v);
        std::fill(in_blossom.begin(), in_blossom.end(), false);

        mark_blossom(lca, u);
        mark_blossom(lca, v);

        if (blossom_root[u] != lca) {
            parent[u] = v;
        }
        if (blossom_root[v] != lca) {
            parent[v] = u;
        }

        for (int i = 0; i < num_v; ++i) {
            if (in_blossom[blossom_root[i]]) {
                blossom_root[i] = lca;
                if (!in_queue[i]) {
                    process_queue.push(i);
                    in_queue[i] = true;
                }
            }
        }
    }

    /// Return the vertex at the end of an augmenting path
    /// starting at the specified source, or -1 if none exist.
    int find_augmenting_path(int source) {
        for (int i = 0; i < num_v; ++i) {
            in_queue[i] = false;
            parent[i] = -1;
            blossom_root[i] = i;
        }

        // Empty the queue
        process_queue = std::queue<int>();

        process_queue.push(source);
        in_queue[source] = true;

        while (!process_queue.empty()) {
            int u = process_queue.front();
            process_queue.pop();

            for (int v : adj_list[u]) {
                if (blossom_root[u] != blossom_root[v] && match[u] != v) {
                    // Process if
                    // + u-v is not an edge in the matching
                    // && u and v are not in the same blossom (yet)
                    if (v == source || (match[v] != -1 && parent[match[v]] != -1)) {
                        // Contract a blossom if
                        // + v is the source
                        // || v is matched and v's match has a parent.
                        //
                        // The fact that parents are assigned to vertices
                        // with odd distances from the source is used to
                        // check if a cycle is odd or even. u is always an
                        // even distance away from the source, so if v's
                        // match is assigned a parent, you have an odd cycle.
                        contract_blossom(source, u, v);
                    } else if (parent[v] == -1) {
                        parent[v] = u;

                        if (match[v] == -1) {
                            // v is unmatched; augmenting path found
                            return v;
                        } else {
                            // Enqueue v's match.
                            int w = match[v];
                            if (!in_queue[w]) {
                                process_queue.push(w);
                                in_queue[w] = true;
                            }
                        }
                    }
                }
            }
        }

        return -1;
    }

    /// Augment the path that ends with the specified vertex
    /// using the parent and match fields. Returns the increase
    /// in the number of matchings. (i.e. 1 if the path is valid,
    /// 0 otherwise)
    int augment_path(int end) {
        int u = end;
        while (u != -1) {
            // Currently w===v----u
            int v = parent[u];
            int w = match[v];

            // Change to w---v===u
            match[v] = u;
            match[u] = v;

            u = w;
        }

        // Return 1 if the augmenting path is valid
        return end == -1 ? 0 : 1;
    }

public:

    edmond_blossom(int v) :
        adj_list(v),
        match(v, -1),
        parent(v),
        blossom_root(v),
        in_queue(v),
        in_blossom(v),
        num_v(v) {}


    /// Add a bidirectional edge from u to v.
    void add_edge(int u, int v) {
        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
    }

    /// Returns the maximum cardinality matching
    int get_max_matching() {
        int ans = 0;

        // Reset
        std::fill(match.begin(), match.end(), -1);

        for (int u = 0; u < num_v; ++u) {
            if (match[u] == -1) {
                int v = find_augmenting_path(u);
                if (v != -1) {
                    // An augmenting path exists
                    ans += augment_path(v);
                }
            }
        }

        return ans;
    }

    /// Constructs the maximum cardinality matching
    std::vector<std::pair<int, int>> construct_matching() {
        std::vector<std::pair<int, int>> output;
        std::vector<bool> is_processed(num_v, false);

        for (int u = 0; u < num_v; ++u) {
            if (!is_processed[u] && match[u] != -1) {
                output.emplace_back(u, match[u]);
                is_processed[u] = true;
                is_processed[match[u]] = true;
            }
        }

        return output;
    }
};

int main() {
    /*
    10 18
    0 1
    0 2
    1 2
    1 3
    1 4
    3 4
    2 4
    2 5
    4 5
    3 6
    3 7
    4 7
    4 8
    5 8
    5 9
    6 7
    7 8
    8 9
    */
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int num_vertices;
    int num_edges;

    std::cin >> num_vertices >> num_edges;

    edmond_blossom eb(num_vertices);
    for (int i = 0; i < num_edges; ++i) {
        int u, v;
        std::cin >> u >> v;

        eb.add_edge(u, v);
    }

    std::cout << "Maximum Cardinality: " << eb.get_max_matching() << "\n";

    std::vector<std::pair<int, int>> matching = eb.construct_matching();
    for (auto& match : matching) {
        std::cout << match.first << " " << match.second << "\n";
    }

}
