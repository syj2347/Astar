#include <bits/stdc++.h>

using namespace std;

const int N = 105;
int m, n;
int v1, v2;// 直线代价，斜线代价
int stx, sty, edx, edy;
int mp[N][N];
int ans_mp[N][N];
int v[8];
int dir[8][2] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}, {-1, 1}, {-1, -1}, {1, 1}, {1, -1}};
int vis[N][N];
int success;
class Node {
public:
    Node(int x, int y) : x(x), y(y) {}
    Node() : x(0), y(0) {}
    int x;
    int y;
    int c1;// 实际代价
    int c2;// 估计代价
    int c; // c1+c2
    bool operator==(const Node &pos) {
        return (pos.x == x && pos.y == y);
    }
    void Cal(const Node &a, const Node &b) {
        c2 = abs(a.x - b.x) + abs(a.y - b.y);
        c = c1 + c2;
    }
};
struct TNode {
    Node pos;
    TNode *pParent;
    vector<TNode *> pChild;
    TNode(const Node &pos) {
        this->pos = pos;
        pParent = NULL;
    }
};
// openlist
vector<TNode *> buff;

void init() {
    cin >> m >> n;
    cin >> v1 >> v2;
    cin >> stx >> sty >> edx >> edy;
    memset(mp, 0, sizeof(mp));
    memset(ans_mp, 0, sizeof(ans_mp));
    memset(vis, 0, sizeof(vis));
    buff.clear();
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> mp[i][j];
        }
    }
    for (int i = 0; i < 8; i++) {
        if (abs(dir[i][0]) && abs(dir[i][1]))
            v[i] = v2;
        else
            v[i] = v1;
    }
    success = 0;
}
int main() {
    init();
    TNode *root = new TNode(Node(stx, sty));
    TNode *p = root;
    TNode *pnext = NULL;
    while (1) {
        for (int i = 0; i < 8; i++) {
            pnext = new TNode(p->pos);
            pnext->pos.x += dir[i][0];
            pnext->pos.y += dir[i][1];
            pnext->pos.c1 += v[i];
            if (pnext->pos.x < 0 || pnext->pos.y < 0 || pnext->pos.x >= m || pnext->pos.y >= n) {
                delete pnext;
                pnext = NULL;
            } else if ((vis[pnext->pos.x][pnext->pos.y] || mp[pnext->pos.x][pnext->pos.y])) {
                delete pnext;
                pnext = NULL;
            } else {
                pnext->pos.Cal(pnext->pos, Node(edx, edy));
                p->pChild.push_back(pnext);
                pnext->pParent = p;
                buff.push_back(pnext);
                vis[pnext->pos.x][pnext->pos.y] = 1;
            }
        }
        auto it = min_element(buff.begin(), buff.end(), [&](TNode *p1, TNode *p2) { return p1->pos.c < p2->pos.c; });
        p = *it;
        buff.erase(it);
        if (p->pos == Node(edx, edy)) {
            success = 1;
            break;
        }
        if (buff.size() == 0) {
            break;
        }
    }
    if (success) {
        vector<Node> ans;
        while (p) {
            ans.insert(ans.begin(), p->pos);
            ans_mp[p->pos.x][p->pos.y] = 1;
            p = p->pParent;
        }
        cout << "route:\n";
        for (int i = 0; i < ans.size(); i++) {
            if (i)
                cout << "->";
            cout << "(" << ans[i].x << "," << ans[i].y << ")";
        }
        cout << "\n";
        cout << "map:\n";
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (ans_mp[i][j] == 1)
                    if (i == stx && j == sty)
                        cout << "s ";
                    else if (i == edx && j == edy)
                        cout << "e ";
                    else
                        cout << ". ";
                else
                    cout << mp[i][j] << " ";
            }
            cout << "\n";
        }
    } else {
        cout << "no way\n";
    }
    return 0;
}

// 10 10
// 10 14
// 0 0 9 9
// 0 0 1 0 1 0 0 0 0 0
// 0 1 0 0 1 0 0 0 0 0
// 0 1 0 1 1 0 1 0 0 0
// 0 0 0 0 1 0 1 0 0 0
// 0 0 0 0 1 0 1 0 0 0
// 0 1 1 1 1 0 0 0 0 0
// 0 0 0 0 1 0 0 0 1 0
// 0 0 0 0 0 0 1 0 0 0
// 0 0 0 0 1 1 0 0 0 1
// 0 0 0 0 1 0 1 0 1 0

// 10 10
// 10 14
// 0 0 9 9
// 0 0 1 0 1 0 0 0 0 0
// 0 1 0 0 1 0 0 0 0 0
// 0 1 0 1 1 0 1 0 0 0
// 0 0 0 0 1 0 1 0 0 0
// 0 0 0 0 1 0 1 0 0 0
// 0 1 1 1 1 0 0 0 0 0
// 0 0 0 0 1 0 0 1 1 1
// 0 0 0 0 0 0 1 0 0 0
// 0 0 0 0 1 1 0 0 1 1
// 0 0 0 0 1 0 1 0 1 0