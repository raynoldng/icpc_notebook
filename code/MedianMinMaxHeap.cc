#include <bits/stdc++.h>
using namespace std;

int main() {
	priority_queue<int> maxPQ;
	priority_queue<int, vector<int>, greater<int> > minPQ;
	string s;
	while(cin >> s) {
		if (s == "#") {
			int m = minPQ.top(); minPQ.pop();
			if (minPQ.size() != maxPQ.size()) {
				minPQ.push(maxPQ.top());
				maxPQ.pop();
			}
			cout << m << endl;
		} else {
			int c = stoi(s);
			if(!minPQ.empty() && c > minPQ.top()) {
				minPQ.push(c);
				if(minPQ.size() > maxPQ.size() + 1) {
					int d = minPQ.top(); minPQ.pop();
					maxPQ.push(d);
				}
			} else {
				maxPQ.push(c);
				if (maxPQ.size() > minPQ.size()) {
					minPQ.push(maxPQ.top());
					maxPQ.pop();
				}
			}
		}
	}
}
