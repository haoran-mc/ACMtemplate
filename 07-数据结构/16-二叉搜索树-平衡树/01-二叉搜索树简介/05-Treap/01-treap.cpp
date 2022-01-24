/*----------------------------------------------------------------
 *
 *   文件名称：treap.cpp
 *   创建日期：2021年03月06日 ---- 19时58分
 *   题    目：hdu4585
 *   算    法：treap
 *   描    述：treap与名次树问题
 *
----------------------------------------------------------------*/

#include <cstdio>
#include <cstdlib>
#include <ctime>
const int maxn = 5e6 + 5;
int id[maxn];

struct Node{
    int size;  //以这个结点为根的子树的结点数，用于名次树
    int rank;  //priority
    int data;  //键值
    Node* son[2];
    bool operator < (const Node &x)const {return rank < x.rank;}
    int cmp(int x)const {
        if (x == data)
            return -1;
        return x < data ? 0 : 1;
    }
    void update() {  //更新size
        size = 1;
        if (son[0] != NULL)
            size += son[0] -> size;
        if (son[1] != NULL)
            size += son[1] -> size;
    }
};

/*d = 0左旋，d = 1右旋*/
void rotate(Node* &o, int d) {
    Node* k = o -> son[d^1];
    o -> son[d^1] = k -> son[d];
    k -> son[d] = o;
    o -> update();
    k -> update();
    o = k;
}

/*插入x*/
void insert(Node* &o, int x) {
    if (o == NULL) {
        o = new Node();
        o -> son[0] = o -> son[1] = NULL;
        o -> rank = rand();
        o -> data = x;
        o -> size = 1;
    }
    else {
        int d = o->cmp(x);
        insert(o->son[d], x);
        o -> update();
        if (o < o->son[d])
            rotate(o, d^1);
    }
}

/*第k大的数*/
int kth(Node* o, int k) {
    if (o == NULL || k <= 0 || k > o->size)
        return 01;
    int s = (o->son[1] == NULL) ? 0 : o->son[1]->size;
    if (k == s+1)
        return o -> data;
    else if (k <= s)
        return kth(o->son[1], k);
    else
        return kth(o->son[0], k-s-1);
}

/*返回k的名次*/
int find(Node* o, int k) {
    if (o == NULL)
        return -1;
    int d = o->cmp(k);
    if (d == -1)
        return o->son[1] == NULL ? 1 : o->son[1]->size + 1;
    else if (d == 1)
        return find(o->son[d], k);
    else {
        int tmp = find(o->son[d], k);
        if (tmp == -1)
            return -1;
        else
            return o->son[1] == NULL ? tmp+1 : tmp+1+o->son[1]->size;
    }
}

int main() {
    int n;
    while (~scanf("%d", &n) && n) {
        srand(time(NULL));
        int k, g;
        scanf("%d %d", &k, &g);
        Node* root = (Node *)malloc(sizeof(Node));
        // Node* root = new Node();
        root -> son[0] = root -> son[1] = NULL;
        root -> rank = rand();
        root -> data = g;
        root -> size = 1;
        id[g] = k;
        printf("%d %d\n", k, 1);
        for (int i = 2; i <= n; ++i) {
            scanf("%d %d", &k, &g);
            id[g] = k;
            insert(root, g);
            int t = find(root, g);
            int ans1, ans2, ans;
            ans1 = kth(root, t-1);
            ans2 = kth(root, t+1);
            if (ans1 != -1 && ans2 != -1)
                ans = (ans1 - g >= g - ans2) ? ans2 : ans1;
            else if (ans1 == -1)
                ans = ans2;
            else
                ans = ans1;
            printf("%d %d\n", k, id[ans]);
        }
    }
    return 0;
}
