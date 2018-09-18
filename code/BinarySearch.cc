// n is size of array, c is value looking for
// sematically equiv to std::lower_bound and std::upper_bound
int lower_bound(int A[], int n, int c) {
	int l = 0, r = n;
	while(l < r) {
		int m = (r-l)/2+l;
		if(A[m] < c) l = m+1; else r=m;
	}
	return l;
}

int upper_bound(int A[], int n, int c) {
	int l = 0, r = n;
	while(l < r) {
		int m = (r-l)/2+l;
		if(A[m] <= c) l = m+1; else r=m;
	}
	return l;
}
