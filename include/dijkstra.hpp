#include <queue>
#include <unordered_set>
#include <vector>
#include <functional>
#include <iostream>
#include <cstring>

using namespace std;

template <typename S, typename GS>
struct Dijkstra
{
    struct Hash { size_t operator()(S const& s) const { return s.hash(); } };

    Dijkstra(GS f) : fn(f) {}
    GS fn;

    S solve(S init)
    {
        std::priority_queue<S, std::vector<S>, std::greater<S>> pq;
        std::unordered_set<S, Hash> ss;

        pq.push(init);
        while(!pq.empty()){
            S s = pq.top(); pq.pop();
            auto g = ss.find(s);
            if(g != ss.end()) continue;
            if(s.isEnd()) return s;
            ss.insert(s);
            fn.iterP(s, [&](S const & t){ if(ss.find(t) == ss.end()) { pq.push(t); } });
        }

        S s{};
        return s;
    }
};


template <typename S, typename GS>
struct Dijkstra1D
{
    Dijkstra1D(GS f, size_t n) : fn(f), N(n) {}
    GS fn;
    size_t N;

    S solve(S init)
    {
        std::priority_queue<S, std::vector<S>, std::greater<S>> q;
        vector<bool> ss(N, false);

        q.push(init);
        while(!q.empty()){
            S s = q.top(); q.pop();
            if(ss[s.i]) continue;
            if(s.isEnd()) return s;
            ss[s.i] = 1;
            fn.iterP(s, [&](S const & t){ if(!ss[t.i]) { q.push(t); } });
        }

        S s{};
        return s;
    }
};


template <typename S, typename GS>
struct Dijkstra2D
{
    Dijkstra2D(GS f, size_t r, size_t c) : fn(f), R(r), C(c) {}
    GS fn;
    size_t R, C;

    S solve(S init)
    {
        std::priority_queue<S, std::vector<S>, std::greater<S>> q;
        vector<vector<bool>> m(R, vector<bool>(C, false));

        q.push(init);
        while(!q.empty()){
            S s = q.top(); q.pop();
            if(m[s.i][s.j]) continue;
            if(s.isEnd()) return s;
            m[s.i][s.j] = 1;
            fn.iterP(s, [&](S const & t){ if(!m[t.i][t.j]) { q.push(t); } });
        }

        S s{};
        return s;
    }
};


template <typename S, typename GS>
struct Dijkstra3D
{
    Dijkstra3D(GS f, size_t a, size_t b, size_t c) : fn(f), A(a), B(b), C(c) {}
    GS fn;
    size_t A, B, C;

    S solve(S init)
    {
        std::priority_queue<S, std::vector<S>, std::greater<S>> q;
        vector<vector<vector<bool>>> m(A, vector<vector<bool>>(B, vector<bool>(C, false)));

        q.push(init);
        while(!q.empty()){
            S s = q.top(); q.pop();
            if(m[s.i][s.j][s.k]) continue;
            if(s.isEnd()) return s;
            m[s.i][s.j][s.k] = 1;
            fn.iterP(s, [&](S const & t){ if(!m[t.i][t.j][t.k]) { q.push(t); } });
        }

        S s{};
        return s;
    }
};


/** example Project Euler 18
using uint = unsigned int;
std::vector<std::vector<int>> v = {{75},
{95,64},
{17,47,82},
{18,35,87,10},
{20, 4,82,47,65},
{19, 1,23,75, 3,34},
{88, 2,77,73, 7,63,67},
{99,65, 4,28, 6,16,70,92},
{41,41,26,56,83,40,80,70,33},
{41,48,72,33,47,32,37,16,94,29},
{53,71,44,65,25,43,91,52,97,51,14},
{70,11,33,28,77,73,17,78,39,68,17,57},
{91,71,52,38,17,14,91,43,58,50,27,29,48},
{63,66, 4,68,89,53,67,30,73,16,69,87,40,31},
{04,62,98,27,23, 9,70,98,73,93,38,53,60, 4,23}};

// 状態を表す型
struct S {
    int i, j, c;

    // コストの大きさを比較
    bool operator>(S const & e) const { return (i*100 - c) > (e.i*100 - e.c); }

    // 状態が等しいか比較
    bool operator==(S const & e) const { return i == e.i && j == e.j; }

    // ハッシュ関数
    size_t hash() const { return i + j; }

    // 終了判定
    bool isEnd() const { return i == v.size()-1; }
};

// 全体の状態
struct GS
{
    // ある状態から到達できる次の状態を列挙する
    template <typename Fn>
    void iterP(S & s, Fn fn)
    {
        auto i = s.i+1, j = s.j;

        if(i == v.size()) return;

        fn({i, j, v[i][j] + s.c});
        fn({i, j+1, v[i][j+1] + s.c});
    }
};

// 2次元バージョン
struct S2D {
    int i, j,   // i, j is necessary.
           c;
    bool operator>(S2D const & e) const { return (i*100 - c) > (e.i*100 - e.c); }
    bool isEnd() const { return i == v.size()-1; }
};

// 2次元バージョン
struct GS2D
{
    template <typename Fn>
    void iterP(S2D & s, Fn fn)
    {
        auto i = s.i+1, j = s.j;
        if(i == v.size()) return;
        fn({i, j, v[i][j] + s.c});
        fn({i, j+1, v[i][j+1] + s.c});
    }
};


int main()
{
    GS fn; GS2D fn2D;
    std::cout << Dijkstra<S, GS>(fn).solve({0, 0, v[0][0]}).c << std::endl;
    std::cout << Dijkstra2D<S2D, GS2D>(fn2D, 15, 15).solve({0, 0, v[0][0]}).c << std::endl;
}
*/