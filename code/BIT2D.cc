// WARNING NOT FIELD TESTED YET
class FenwickTree {
private:
  vi ft;

public:
  FenwickTree() {}
  // initialization: n + 1 zeroes, ignore index 0
  FenwickTree(int n) { ft.assign(n + 1, 0); }

  int rsq(int b) {                                     // returns RSQ(1, b)
    int sum = 0; for (; b; b -= LSOne(b)) sum += ft[b];
    return sum; }

  int rsq(int a, int b) {                              // returns RSQ(a, b)
    return rsq(b) - (a == 1 ? 0 : rsq(a - 1)); }

  // adjusts value of the k-th element by v (v can be +ve/inc or -ve/dec)
  void adjust(int k, int v) {                    // note: n = ft.size() - 1
    for (; k < (int)ft.size(); k += LSOne(k)) ft[k] += v; }
};

class FenwickTree2D {
private:
  vector<FenwickTree> ft2d;

public:
  FenwickTree2D() {}
  FenwickTree2D(int n) { ft2d.assign(n+1, FenwickTree(n)); }

  int rsq(int r, int c) {
    int sum = 0;
    for(; r; r -= LSOne(r)) sum += ft2d[r].rsq(c);
    return sum;
  }

  // top left, bottom right
  int rsq(int r1, int c1, int r2, int c2) {
    return rsq(r2, c2) - rsq(r2, c1-1) - rsq(r1-1, c2) + rsq(r1-1, c2-1);
  }

  void adjust(int r, int c, int v) {
    for (; r < (int)ft2d.size(); r += LSOne(r)) ft2d[r].adjust(c, v);
  }
};


int main() {              
  FenwickTree2D ft2d(4);
  ft2d.adjust(1, 1, 1);
  ft2d.adjust(2, 2, 1);
  ft2d.adjust(3, 3, 1);
  ft2d.adjust(4, 4, 1);
  printf("%d\n", ft2d.rsq(1,1));      // 1
  printf("%d\n", ft2d.rsq(2,2));      // 2
  printf("%d\n", ft2d.rsq(3,3));      // 3
  printf("%d\n", ft2d.rsq(2,2,3,3));  // 2
  return 0;
}

