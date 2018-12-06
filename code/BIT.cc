// BIT with range updates, inspired by Petr Mitrichev
struct BIT {
    int n;
    vector<int> slope;
    vector<int> intercept;
    // BIT can be thought of as having entries f[1], ..., f[n]
    // which are 0-initialized
    BIT(int n): n(n), slope(n+1), intercept(n+1) {}
    // returns f[1] + ... + f[idx-1]
    // precondition idx <= n+1
    int query(int idx) {
        int m = 0, b = 0;
        for (int i = idx-1; i > 0; i -= i&-i) {
            m += slope[i];
            b += intercept[i];
        }
        return m*idx + b;
    }
    // adds amt to f[i] for i in [idx1, idx2)
    // precondition 1 <= idx1 <= idx2 <= n+1 (you can't update element 0)
    void update(int idx1, int idx2, int amt) {
        for (int i = idx1; i <= n; i += i&-i) {
            slope[i] += amt;
            intercept[i] -= idx1*amt;
        }
        for (int i = idx2; i <= n; i += i&-i) {
            slope[i] -= amt;
            intercept[i] += idx2*amt;
        }
    }
};

// BIT with range updates, inspired by Petr Mitrichev
class FenwickTree {
private: vi ft1, ft2;
    int query(vi &ft, int b) {
        int sum = 0; for (; b; b -= LSOne(b)) sum += ft[b];
        return sum; }
    void adjust(vi &ft, int k, int v) {
        for (; k < (int)ft.size(); k += LSOne(k)) ft[k] += v; }
public:
    FenwickTree() {}
    FenwickTree(int n) { ft1.assign(n + 1, 0); ft2.assign(n+1, 0);}
    int query(int a) { return a * query(ft1, a) - query(ft2, a); }
    int query(int a, int b) { return query(b) - (a == 1 ? 0 : query(a-1)); }
    void adjust(int a, int b, int value){
        adjust(ft1, a, value);
        adjust(ft1, b+1, -value);
        adjust(ft2, a, value * (a-1));
        adjust(ft2, b+1, -1 * value * b);
    }
    int get(int n) {
        return query(n) - query(n-1);}
};