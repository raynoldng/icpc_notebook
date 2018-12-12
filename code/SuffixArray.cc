// Suffix array construction in O(L log^2 L) time.  Routine for
// computing the length of the longest common prefix of any two
// suffixes in O(log L) time.
//
// INPUT:   string s
//
// OUTPUT:  array suffix[] such that suffix[i] = index (from 0 to L-1)
//          of substring s[i...L-1] in the list of sorted suffixes.
//          That is, if we take the inverse of the permutation suffix[],
//          we get the actual suffix array.
struct SuffixArray {
  const int L;
  string s;
  vector<vector<int> > P;
  vector<pair<pair<int,int>,int> > M;

  SuffixArray(const string &s) : L(s.length()), s(s), P(1, vector<int>(L, 0)), M(L) {
    for (int i = 0; i < L; i++) P[0][i] = int(s[i]);
    for (int skip = 1, level = 1; skip < L; skip *= 2, level++) {
      P.push_back(vector<int>(L, 0));
      for (int i = 0; i < L; i++) 
	M[i] = make_pair(make_pair(P[level-1][i], i + skip < L ? P[level-1][i + skip] : -1000), i);
      sort(M.begin(), M.end());
      for (int i = 0; i < L; i++) 
	P[level][M[i].second] = (i > 0 && M[i].first == M[i-1].first) ? P[level][M[i-1].second] : i;
    }    
  }

  vector<int> GetSuffixArray() { return P.back(); }

  // returns the length of the longest common prefix of s[i...L-1] and s[j...L-1]
  int LongestCommonPrefix(int i, int j) {
    int len = 0;
    if (i == j) return L - i;
    for (int k = P.size() - 1; k >= 0 && i < L && j < L; k--) {
      if (P[k][i] == P[k][j]) {
	i += 1 << k;
	j += 1 << k;
	len += 1 << k;
      }
    }
    return len;
  }
};

// BEGIN CUT
// The following code solves UVA problem 11512: GATTACA.
#define TESTING
#ifdef TESTING
int main() {
  int T;
  cin >> T;
  for (int caseno = 0; caseno < T; caseno++) {
    string s;
    cin >> s;
    SuffixArray array(s);
    vector<int> v = array.GetSuffixArray();
    int bestlen = -1, bestpos = -1, bestcount = 0;
    for (int i = 0; i < s.length(); i++) {
      int len = 0, count = 0;
      for (int j = i+1; j < s.length(); j++) {
	int l = array.LongestCommonPrefix(i, j);
	if (l >= len) {
	  if (l > len) count = 2; else count++;
	  len = l;
	}
      }
      if (len > bestlen || len == bestlen && s.substr(bestpos, bestlen) > s.substr(i, len)) {
	bestlen = len;
	bestcount = count;
	bestpos = i;
      }
    }
    if (bestlen == 0) {
      cout << "No repetitions found!" << endl;
    } else {
      cout << s.substr(bestpos, bestlen) << " " << bestcount << endl;
    }
  }
}

#else
// END CUT
int main() {

  // bobocel is the 0'th suffix
  //  obocel is the 5'th suffix
  //   bocel is the 1'st suffix
  //    ocel is the 6'th suffix
  //     cel is the 2'nd suffix
  //      el is the 3'rd suffix
  //       l is the 4'th suffix
  SuffixArray suffix("bobocel");
  vector<int> v = suffix.GetSuffixArray();
  
  // Expected output: 0 5 1 6 2 3 4
  //                  2
  for (int i = 0; i < v.size(); i++) cout << v[i] << " ";
  cout << endl;
  cout << suffix.LongestCommonPrefix(0, 2) << endl;
}
// BEGIN CUT
#endif
// END CUT


// Yan Hao's Implementation
#include <bits/stdc++.h>
using namespace std;

#define all(o) (o).begin(), (o).end()
#define allr(o) (o).rbegin(), (o).rend()
const int INF = 2147483647;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<vi> vvi;
typedef vector<vii> vvii;
template <class T> int size(T &x) { return x.size(); }

// assert or gtfo

struct suffix_array {
    struct entry {
        pair<int, int> nr;
        int p;

        bool operator <(const entry &other) const {
            return nr < other.nr;
        }
    };

    string s;
    int n;
    vector<vector<int> > P;
    vector<entry> L;
    vector<int> idx;

    suffix_array(string _s) : s(_s), n(s.size()) {
        L = vector<entry>(n);
        P.push_back(vector<int>(n));
        idx = vector<int>(n);

        for (int i = 0; i < n; i++) {
            P[0][i] = s[i];
        }

        for (int stp = 1, cnt = 1; (cnt >> 1) < n; stp++, cnt <<= 1) {
            P.push_back(vector<int>(n));
            for (int i = 0; i < n; i++) {
                L[i].p = i;
                L[i].nr = make_pair(P[stp - 1][i],
                        i + cnt < n ? P[stp - 1][i + cnt] : -1);
            }

            sort(L.begin(), L.end());
            for (int i = 0; i < n; i++) {
                if (i > 0 && L[i].nr == L[i - 1].nr) {
                    P[stp][L[i].p] = P[stp][L[i - 1].p];
                } else {
                    P[stp][L[i].p] = i;
                }
            }
        }

        for (int i = 0; i < n; i++) {
            idx[P[P.size() - 1][i]] = i;
        }
    }

    int lcp(int x, int y) {
        int res = 0;
        if (x == y) return n - x;
        for (int k = P.size() - 1; k >= 0 && x < n && y < n; k--) {
            if (P[k][x] == P[k][y]) {
                x += 1 << k;
                y += 1 << k;
                res += 1 << k;
            }
        }
        return res;
    }

    int longestRepeatedSubsequence() {
        int ans=0;
        for(int i=1; i<n; i++) {
            ans = max(ans, lcp(idx[i-1], idx[i]));
        }
        return ans;
    }
};

int main() {
    while(true) {
        string x,y;
        getline(cin, x);
        getline(cin, y);
        y.push_back('$');
        if(!cin.good()) break;
        suffix_array sa(y);
        //do binary search
        int low = 0;
        int high = y.length();
        while(high-low>1) {
            int mid = (high+low)/2;
            int z = sa.idx[mid];
            for(int i=0; i<x.length() && z+i<y.length(); i++) {
                if(x[i]<y[z+i]) {
                    high=mid; break;
                } else if(x[i]>y[z+i]) {
                    low=mid; break;
                }
            }
            if(high!=mid && low!=mid) {
                high=mid;
            }
        }
        int low2 = 0;
        int high2 = y.length();
        while(high2-low2>1) {
            int mid = (high2+low2)/2;
            int z = sa.idx[mid];
            for(int i=0; i<x.length() && z+i<y.length(); i++) {
                if(x[i]<y[z+i]) {
                    high2=mid; break;
                } else if(x[i]>y[z+i]) {
                    low2=mid; break;
                }
            }
            if(high2!=mid && low2!=mid) {
                low2=mid;
            }
        }
        vector<int> ans;
        for(int i=low+1; i<=low2; i++) {
            ans.push_back(sa.idx[i]);
        }
        sort(ans.begin(), ans.end());
        for(int v: ans) {
            cout << v << " ";
        }
        cout << "\n";
    }
    return 0;
}
