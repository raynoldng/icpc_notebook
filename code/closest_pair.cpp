// Source: e-maxx.ru
#define upd_ans(x, y) {}
#define MAXN 100
double mindist = 1e20; // will be the result
void rec(int l, int r, Point a[]) {
    if (r - l <= 3) {
        for (int i=l; i<=r; ++i)
            for (int j=i+1; j<=r; ++j)
                    upd_ans(a[i], a[j]);
        sort(a+l, a+r+1); // compare by y
        return;
    }

    int m = (l + r) >> 1;
    int midx = a[m].x;
    rec(l, m, a), rec(m+1, r, a);
    static Point t[MAXN];
    merge(a+l, a+m+1, a+m+1, a+r+1, t); // compare by y
    copy(t, t+r-l+1, a+l);

    int tsz = 0;
    for (int i=l; i<=r; ++i)
        if (fabs(a[i].x - midx) < mindist) {
            for (int j=tsz-1; j>=0 && a[i].y - t[j].y < mindist; --j)
                upd_ans(a[i], t[j]);
            t[tsz++] = a[i];
        }
}