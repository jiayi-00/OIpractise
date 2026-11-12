#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN = 100005;
struct Node {
    int sum;
    int l0, r0, mx0;
    int l1, r1, mx1;
    int tag;
} tree[MAXN << 2];
int n, m;
int a[MAXN];
void pushUp(int root, int len) {
    int lc = root << 1;
    int rc = root << 1 | 1;
    int lenl = len - (len >> 1);
    int lenr = len >> 1;
    tree[root].sum = tree[lc].sum + tree[rc].sum;
    if (tree[lc].l0 == lenl)  tree[root].l0 = lenl + tree[rc].l0;
    else  tree[root].l0 = tree[lc].l0;
    if (tree[rc].r0 == lenr)  tree[root].r0 = lenr + tree[lc].r0;
    else  tree[root].r0 = tree[rc].r0;
    tree[root].mx0 = max(tree[lc].mx0, tree[rc].mx0);
    tree[root].mx0 = max(tree[root].mx0, tree[lc].r0 + tree[rc].l0);
    if (tree[lc].l1 == lenl)  tree[root].l1 = lenl + tree[rc].l1;
    else  tree[root].l1 = tree[lc].l1;
    if (tree[rc].r1 == lenr)  tree[root].r1 = lenr + tree[lc].r1;
    else  tree[root].r1 = tree[rc].r1;
    tree[root].mx1 = max(tree[lc].mx1, tree[rc].mx1);
    tree[root].mx1 = max(tree[root].mx1, tree[lc].r1 + tree[rc].l1);
}
void applyAssign(int root, int len, int val) {
    tree[root].tag = val;
    tree[root].sum = val ? len : 0;
    if (val) {
        tree[root].l1 = tree[root].r1 = tree[root].mx1 = len;
        tree[root].l0 = tree[root].r0 = tree[root].mx0 = 0;
    } else {
        tree[root].l0 = tree[root].r0 = tree[root].mx0 = len;
        tree[root].l1 = tree[root].r1 = tree[root].mx1 = 0;
    }
}
void applyReverse(int root, int len) {
    if (tree[root].tag != -1)  tree[root].tag ^= 1;
    else {
        if (tree[root].tag == 2) tree[root].tag = -1;
        else tree[root].tag = 2;
    }
    
    swap(tree[root].l0, tree[root].l1);
    swap(tree[root].r0, tree[root].r1);
    swap(tree[root].mx0, tree[root].mx1);
    tree[root].sum = len - tree[root].sum;
}
void pushDown(int root, int len) {
    if (tree[root].tag == -1) return;
    int lenl = len - (len >> 1);
    int lenr = len >> 1;
    if (tree[root].tag == 0) {
        applyAssign(root << 1, lenl, 0);
        applyAssign(root << 1 | 1, lenr, 0);
    } else if (tree[root].tag == 1) {
        applyAssign(root << 1, lenl, 1);
        applyAssign(root << 1 | 1, lenr, 1);
    } else if (tree[root].tag == 2) {
        applyReverse(root << 1, lenl);
        applyReverse(root << 1 | 1, lenr);
    }
    tree[root].tag = -1;
}
void build(int root, int l, int r) {
    tree[root].tag = -1;
    if (l == r) {
        int val = a[l];
        tree[root].sum = val;
        if (val) {
            tree[root].l1 = tree[root].r1 = tree[root].mx1 = 1;
            tree[root].l0 = tree[root].r0 = tree[root].mx0 = 0;
        } else {
            tree[root].l0 = tree[root].r0 = tree[root].mx0 = 1;
            tree[root].l1 = tree[root].r1 = tree[root].mx1 = 0;
        }
        return;
    }
    int mid = (l + r) >> 1;
    build(root << 1, l, mid);
    build(root << 1 | 1, mid + 1, r);
    pushUp(root, r - l + 1);
}
void assign(int root, int l, int r, int ql, int qr, int val) {
    if (ql <= l && r <= qr) {
        applyAssign(root, r - l + 1, val);
        return;
    }
    pushDown(root, r - l + 1);
    int mid = (l + r) >> 1;
    if (ql <= mid) assign(root << 1, l, mid, ql, qr, val);
    if (qr > mid) assign(root << 1 | 1, mid + 1, r, ql, qr, val);
    pushUp(root, r - l + 1);
}
void reverse(int root, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) {
        applyReverse(root, r - l + 1);
        return;
    }
    pushDown(root, r - l + 1);
    int mid = (l + r) >> 1;
    if (ql <= mid) reverse(root << 1, l, mid, ql, qr);
    if (qr > mid) reverse(root << 1 | 1, mid + 1, r, ql, qr);
    pushUp(root, r - l + 1);
}
int querySum(int root, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr)  return tree[root].sum;
    pushDown(root, r - l + 1);
    int mid = (l + r) >> 1;
    int res = 0;
    if (ql <= mid) res += querySum(root << 1, l, mid, ql, qr);
    if (qr > mid) res += querySum(root << 1 | 1, mid + 1, r, ql, qr);
    return res;
}
Node queryMax(int root, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr)  return tree[root];
    pushDown(root, r - l + 1);
    int mid = (l + r) >> 1;
    if (qr <= mid) return queryMax(root << 1, l, mid, ql, qr);
    if (ql > mid) return queryMax(root << 1 | 1, mid + 1, r, ql, qr);
    Node left = queryMax(root << 1, l, mid, ql, qr);
    Node right = queryMax(root << 1 | 1, mid + 1, r, ql, qr);
    Node res;
    int lenl = min(mid - ql + 1, mid - l + 1);
    int lenr = min(qr - mid, r - mid);
    res.sum = left.sum + right.sum;
    if (left.l0 == lenl) res.l0 = lenl + right.l0;
    else  res.l0 = left.l0;
    if (right.r0 == lenr) res.r0 = lenr + left.r0;
    else  res.r0 = right.r0;
    res.mx0 = max(left.mx0, right.mx0);
    res.mx0 = max(res.mx0, left.r0 + right.l0);
    if (left.l1 == lenl) res.l1 = lenl + right.l1;
    else res.l1 = left.l1;
    if (right.r1==lenr)  res.r1 = lenr + left.r1;
    else res.r1=right.r1;
    res.mx1=max(left.mx1,right.mx1);
    res.mx1=max(res.mx1,left.r1+right.l1);
    return res;
}
int main() {
    scanf("%d%d",&n,&m);
    for (int i=0; i<n; i++)  scanf("%d",&a[i]);
    build(1,0,n-1);
    while(m--){
        int op,l,r;
        scanf("%d%d%d",&op, &l, &r);
        if (op==0)  assign(1,0,n-1,l,r,0);
        else if (op==1)  assign(1,0,n-1,l,r,1);
        else if (op==2)  reverse(1,0,n-1,l,r);
        else if (op==3)  printf("%d\n", querySum(1,0,n-1,l,r));
        else if (op==4){
            Node ans=queryMax(1,0,n-1,l,r);
            printf("%d\n", ans.mx1);
        }
    }
    return 0;
}