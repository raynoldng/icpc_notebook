// remove duplicated from vector
#define UNIQUE(x) x.erase(unique(x.begin(), x.end()), x.end())
// filters.erase(unique(filters.begin(), filters.end()), filters.end());

// convert string to int
int myint = stoi("123");

// memset
int res[MAX_V][MAX_V];
memset(res, 0, sizeof res);
fill (myvector.begin(),myvector.begin()+4,5);
int myint1 = stoi(str1); // convert string to int

// Convert int to binary string
cout << bitset<32>(val).to_string() << endl;

// Generate all permutations
sort(nodes.begin(), nodes.end());
do {
  int sum = 0;
  for(int i = 1; i < nodes.size(); i++)
    sum += __builtin_popcount(nodes[i] & nodes[i-1]);
  best = min(best, sum);
 } while(next_permutation(nodes.begin(), nodes.end()));

// Generate all set of n elements
unsigned next_set_n(unsigned x) {
  unsigned smallest, ripple, new_smallest, ones;
  if(x==0) return 0;
  smallest = (x & -x);
  ripple = x + smallest;
  new_smallest = (ripple & -ripple);
  ones = ((new_smallest/smallest) >> 1 ) - 1;
  return ripple | ones;
}
