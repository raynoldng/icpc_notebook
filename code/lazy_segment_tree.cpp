#include <iostream>
#include <algorithm>
using namespace std;
const int n=10; // number of elements in the tree should be at most (1<<n)
int arr[1<<(n+1)]; // store values
int low[1<<(n+1)]; // left of range
int high[1<<(n+1)]; // right of range
int lazyadd[1<<(n+1)];

// should be commutative and associative. most commonly used: a+b, max(a,b), min(a,b)
int acc(int a, int b) {
    return max(a,b);
}
int acc2(int a, int b) {
    // a "acts" on b, the function needs to be distributive over acc, commutative + associative
    // common uses: a+max(b,c) = max(a+b, a+c), a*max(b,c)=max(a*b,a*c) (only if a>0)
    // a*(b+c) = (a*b)+(a*c)
    return a+b;
}
void init() {
    for(int i=0; i<(1<<n); i++) {
        low[i+(1<<n)] = i;
        high[i+(1<<n)] = i;
        arr[i+(1<<n)] = 0; // initial value
    }
    for(int i=(1<<n)-1; i>=0; i--) {
        low[i] = min(low[2*i], low[2*i+1]);
        high[i] = max(high[2*i], high[2*i+1]);
        arr[i] = acc(arr[2*i], arr[2*i+1]);
    }
    for(int i=0; i<(1<<(n+1)); i++) {
        lazyadd[i] = 0; // identity of the acc2 function
    }
}
int value(int node) { // gives the true value of the node
    arr[node] = acc2(lazyadd[node], arr[node]);
    if(node<(1<<n)) { // not the leaf, propagate downwards
        lazyadd[2*node] = acc2(lazyadd[node], lazyadd[2*node]); // stack values on children
        lazyadd[2*node+1] = acc2(lazyadd[node], lazyadd[2*node+1]); // stack values on children
    }
    lazyadd[node] = 0; // reset to identity function
    return arr[node];
}
void update(int node, int left, int right, int change) {
    if(right>=high[node] && left<=low[node]) { // case 1: updated range covers node
        lazyadd[node] = acc2(lazyadd[node],change); // stack the change
    } else if(right<low[node] || left>high[node]) { // case 2: empty intersection
        return;
    } else { // case 3: need to propagate
        update(2*node, left, right, change);
        update(2*node+1, left, right, change);
        arr[node] = acc(value(node*2), value(node*2+1));
    }
}
void update(int left, int right, int change) {
    update(1, left, right, change);
}
int query(int node, int left, int right) {
    value(node); // important to call this!
    if(right>=high[node] && left<=low[node]) {
        return arr[node];
    } else if(right<low[node] || left>high[node]) {
        return -(1<<30); // identity operator of acc
    } else {
        return acc(query(node*2, left, right), query(node*2+1, left, right));
    }
}
int query(int left, int right) {
    return query(1, left,right);
}
int main()
{
    init();
    cout << query(1,5); //0
    update(2,5,3); // 0 3 3 3 3 -> max=3
    cout << query(1,5); // 3
    update(2,3,2); // 0 5 5 3 3 -> max=5
    cout << query(1,5); // 5
    update(2,4,-4); // 0 1 1 -1 3 -> max=5
    cout << query(1,5); // 5
    update(5,5,-1); // 0 1 1 -1 2 -> max=2
    cout << query(1,5); // 2
    return 0;
}
