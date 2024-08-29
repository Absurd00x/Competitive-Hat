#ifdef LOCAL_PROJECT
    #pragma GCC optimize("O0")
#else
    #pragma GCC optimize("O3")
#endif
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
#define int ll
#define double ld

#define all(x) std::begin(x),std::end(x)
#define rall(x) std::rbegin(x),std::rend(x)

const auto boostIO = []() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << fixed;
    cout.precision(12);
    return 0;
}();

#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic push
const int INF = 9e18;

struct Node {
    int sum{0}, mn{INF}, mn_ind{-1}, add{0}, ass{INF};
    void update_from_node(const Node &other, int l, int r) {
        // В детях не бывает лени, когда от них обновляешься
        sum += other.sum;
        if (mn > other.mn) {
            mn = other.mn;
            mn_ind = other.mn_ind;
        }
    }
    bool has_lazy() {
        return add != 0 || ass != INF;
    }
    void clear_lazy() {
        add = 0;
        ass = INF;
    }
    void clear() {
        sum = 0, mn = INF, mn_ind = -1;
        add = 0, ass = INF;
    }

    void propagate_lazy(Node &left, Node &right, int l, int r) {
        if (ass != INF) {
            left.ass = ass;
            right.ass = ass;
            left.add = right.add = 0;
        }
        left.add += add;
        right.add += add;
    }
    void apply_lazy(int l, int r) {
        if (ass != INF) {
            sum = (r - l) * ass;
            mn = ass;
            mn_ind = l;
        }
        sum += (r - l) * add;
        mn += add;
    }
    friend ostream& operator<<(ostream& out, Node const &me) {
        return out << me.sum;
    }
};
#pragma GCC diagnostic pop

class VirtSegTree {
protected:
    int leafs, nodes;
    vector<Node> guts;
    int qleft, qright;

    void prepare(int l, int r) {
        guts[0].clear();
        qleft = l, qright = r;
    }

    void push(int x, int l, int r) {
        if (guts[x].has_lazy()) {
            int len = r - l;
            int h = len / 2;
            if (len > 1) {
                guts[x].propagate_lazy(guts[x + 1], guts[x + 2 * h], l, r);
            }
            guts[x].apply_lazy(l, r);
            guts[x].clear_lazy();
        }
    }

    void update_from_children(int x, int l, int r) {
        guts[x].clear();
        int h = (r - l) / 2;
        int m = l + h;
        push(x + 1, l, m);
        guts[x] = guts[x + 1];
        push(x + 2 * h, m, r);
        guts[x].update_from_node(guts[x + 2 * h], l, r);
    }

    template <typename T>
    void _traverse(int x, int l, int r, T f) {
        push(x, l, r);
        if (r - l == 1) {
            f(x, l, r);  
        } else {
            int h = (r - l) / 2;
            int m = l + h;
            _traverse<T>(x + 1, l, m, f);
            _traverse<T>(x + 2 * h, m, r, f);
            update_from_children(x, l, r);
        }
    }

    template <typename T>
    void _query(int x, int l, int r, T f) {
        push(x, l, r);
        if (qleft <= l && r <= qright) {
            f(x, l, r);
            push(x, l, r);
        } else {
            int h = (r - l) / 2;
            int m = l + h;
            if (qleft < m) {
                _query<T>(x + 1, l, m, f);
            }
            if (m < qright) {
                _query<T>(x + 2 * h, m, r, f);
            }
            update_from_children(x, l, r);
        }
    }

    template <typename T>
    void _descend(int x, int l, int r, T f) {
        push(x, l, r);
        if (qleft <= l && r <= qright) {
            if (!f(x, l, r)) {
                if (r - l == 1) {
                    // Если не можем взять вершину, то правее неё
                    // тоже брать не сможем когда будем возвращаться
                    // из рекурсии
                    qright = r;
                    return;
                }
                // если вершину нельзя добавить целиком
                // пробуем добавить левого сына
                int h = (r - l) / 2;
                int m = l + h;
                push(x + 1, l, m);
                if (f(x + 1, l, m)) {
                    // Если получилось, то идём в правого сына
                    _descend<T>(x + 2 * h, m, r, f);
                } else {
                    // Иначе в левого

                    // Когда будем возвращаться, то правее m
                    // уже нельзя идти
                    qright = m;
                    _descend<T>(x + 1, l, m, f);
                }
                update_from_children(x, l, r);
            }
        } else {
            int h = (r - l) / 2;
            int m = l + h;
            if (qleft < m) {
                _descend<T>(x + 1, l, m, f);
            }
            if (m < qright) {
                _descend<T>(x + 2 * h, m, r, f);
            }
            update_from_children(x, l, r);
        }
    }

    template <typename T>
    void _descend2(int x, int l, int r, T f) {
        push(x, l, r);
        if (qleft <= l && r <= qright) {
            if (!f(x, l, r)) {
                if (r - l == 1) {
                    // Если не можем взять вершину, то ЛЕВЕЕ неё
                    // тоже брать не сможем когда будем возвращаться
                    // из рекурсии
                    qleft = l;
                    return;
                }
                // если вершину нельзя добавить целиком
                // пробуем добавить ПРАВОГО сына
                int h = (r - l) / 2;
                int m = l + h;
                push(x + 2 * h, m, r);
                if (f(x + 2 * h, m, r)) {
                    // если получилось взять ПРАВОГО, то можно идти в левого
                    _descend2<T>(x + 1, l, m, f);
                } else {
                    // иначе в правого

                    // сдвигаем границу
                    qleft = l;
                    _descend2<T>(x + 2 * h, m, r, f);
                }
                update_from_children(x, l, r);
            }
        } else {
            int h = (r - l) / 2;
            int m = l + h;
            if (m < qright) {
                _descend2<T>(x + 2 * h, m, r, f);
            }
            if (qleft < m) {
                _descend2<T>(x + 1, l, m, f);
            }
            update_from_children(x, l, r);
        }
    }

    template <typename T>
    void traverse(T f) {
        _traverse<T>(1, 0, leafs, f);
    }

    template <typename T>
    void query(T f) {
        _query<T>(1, 0, leafs, f);
    }

    template <typename T>
    void descend(T f) {
        _descend<T>(1, 0, leafs, f);
    }

    template <typename T>
    void descend_right_to_left(T f) {
        _descend2<T>(1, 0, leafs, f);
    }

public:
    void print() {
        auto on_leaf = [&](int x, int l, int r) {
            cout << (l ? " " : "") << guts[x];
        };
        traverse(on_leaf);
        cout << endl;
    }
    void wipe(int n) {
        leafs = n;
        nodes = 2 * leafs;
        guts.assign(nodes, Node());
    }
};

class SegTree : public VirtSegTree {
public:
    void build(vector<int> &init) {
        wipe((int)init.size());
        auto on_leaf = [&](int x, int l, int r) {
            guts[x].sum = guts[x].mn = init[l];
            guts[x].mn_ind = l;
        };
        traverse(on_leaf);
    }

    void update_add(int left, int right, int val) {
        prepare(left, right);
        auto on_node = [&](int x, int l, int r) {
            guts[x].add += val;
        };
        query(on_node);
    }

    void update_ass(int left, int right, int val) {
        prepare(left, right);
        auto on_node = [&](int x, int l, int r) {
            guts[x].ass = val;
        };
        query(on_node);
    }

    int get_min(int left, int right) {
        prepare(left, right);
        auto on_node = [&](int x, int l, int r) {
            guts[0].update_from_node(guts[x], l, r);
        };
        query(on_node);
        return guts[0].mn_ind;
    }

    int get_kth(int left, int right, int k) {
        prepare(left, right);
        --k;
        int res = left;
        auto try_add = [&](int x, int l, int r) {
            if (k >= guts[x].sum) {
                k -= guts[x].sum;
                res = r;
                return true;
            }
            return false;
        };
        descend(try_add);
        if (res == right) {
            res = -1;
        }
        return res;
    }
}stree;

typedef tuple<int, int, int, int> qi;

//const int N = 4;
//const int Q = 2;
//const int X = 5;
//const int K = 7;
//const bool BCHECK = false;
//const bool BSOLVE = false;

int n, q;
vector<int> arr;
vector<qi> qs;
vector<int> ans;

void read() {
    cin >> n >> q;
    arr.resize(n);
    for (int &elem : arr) {
        cin >> elem;
    }
    qs.resize(q);
    for (auto &[type, l, r, x] : qs) {
        cin >> type >> l >> r;
        if (type != 3) {
            cin >> x;
        }
    }
}

void write() {
    for (int res : ans) {
        cout << res << ' ';
    }
    cout << '\n';
}

void solve() {
    vector<int> cnts(n);
    for (int num : arr) {
        ++cnts[num];
    }
    stree.build(cnts);
    ans.clear();
    for (auto &[type, l, r, x] : qs) {
        if (type == 1) {
            stree.update_add(l, r, x);
        } else if (type == 2) {
            stree.update_ass(l, r, x);
        } else if (type == 3) {
            ans.push_back(stree.get_min(l, r));
        } else if (type == 4) {
            ans.push_back(stree.get_kth(l, r, x));
        }
    }
}

//const int SEED = 42;
//mt19937 RNG(SEED);
//int rint(int f, int t) {
//    uniform_int_distribution<int> d(f, t);
//    return d(RNG);
//}
//
//void gen() {
//    n = rint(1, N);
//    q = rint(1, Q);
//    arr.resize(n);
//    for (int &num : arr) {
//        num = rint(0, n - 1);
//    }
//    qs.resize(q);
//    for (auto &[type, l, r, x] : qs) {
//        type = rint(1, 4);
//        l = rint(0, n - 1);
//        r = rint(0, n - 1);
//        if (l > r) {
//            swap(l, r);
//        }
//        ++r;
//        if (type == 1) {
//            x = rint(1, X);
//        } else if (type == 2) {
//            x = rint(0, X);
//        } else if (type == 4) {
//            x = rint(1, K);
//        }
//    }
//}
//
//void brute() {
//    vector<int> cnts(n);
//    for (int num : arr) {
//        ++cnts[num];
//    }
//    ans.clear();
//    for (auto &[type, l, r, x] : qs) {
//        if (type == 1) {
//            for (int i = l; i < r; ++i) {
//                cnts[i] += x;
//            }
//        } else if (type == 2) {
//            for (int i = l; i < r; ++i) {
//                cnts[i] = x;
//            }
//        } else if (type == 3) {
//            int mn = INF, res = -1;
//            for (int i = l; i < r; ++i) {
//                if (mn > cnts[i]) {
//                    mn = cnts[i];
//                    res = i;
//                }
//            }
//            ans.push_back(res);
//        } else if (type == 4) {
//            int rem = x - 1, res = -1;
//            for (int i = l; i < r; ++i) {
//                rem -= cnts[i];
//                if (rem < 0) {
//                    res = i;
//                    break;
//                }
//            }
//            ans.push_back(res);
//        }
//    }
//}
//
//bool stress() {
//    static int cnt = 1;
//    solve();
//    auto mya = ans;
//    brute();
//    auto cora = ans;
//    if (mya != cora) {
//        cout << "WA test #" << cnt << '\n';
//        cout << '1' << '\n';
//        cout << n << ' ' << q << '\n';
//        for (int i = 0; i < n; ++i) {
//            cout << (i ? " " : "") << arr[i];
//        }
//        cout << '\n';
//        for (auto &[type, l, r, x] : qs) {
//            cout << type << ' ' << l << ' ' << r;
//            if (type != 3) {
//                cout << ' ' << x;
//            }
//            cout << '\n';
//        }
//        cout << "Mya  =";
//        for (int res : mya) {
//            cout << ' ' << res;
//        }
//        cout << '\n';
//        cout << "Cora =";
//        for (int res : cora) {
//            cout << ' ' << res;
//        }
//        cout << '\n';
//        return false;
//    }
//    cout << "Passed test #" << cnt++ << endl;
//    return true;
//}

signed main() {
//    if (BCHECK) {
//        do {
//            gen();
//        } while (stress());
//    } else {
        int tests = 1; cin >> tests;
        while (tests --> 0) {
            read();
            solve();
//            (BSOLVE ? brute() : solve());
            write();
        }
//    }
    cout.flush();
    return 0;
}
