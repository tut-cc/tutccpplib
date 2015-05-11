#include <queue>
#include <unordered_set>
#include <vector>
#include <functional>
#include <iostream>

template <typename S, typename P, typename GS>
struct Dijkstra
{
    struct Hash { size_t operator()(S const& s) const { return s.hash(); } };

    using namespace std;

    Dijkstra(GS f) : fn(f) {}
    GS fn;

    S solve(S init)
    {
        priority_queue<S, vector<S>, greater<S>> pq;
        unordered_set<S, Hash> ss;

        pq.push(init);
        while(!pq.empty()){
            S s = pq.top();
            pq.pop();

            fn.iterP(s, [&](P const & p){
                S e = p.apply(s);
                auto g = ss.find(e);
                if(g == ss.end()){
                    ss.insert(e);
                    pq.push(e);
                }else if(e > *g){
                    ss.erase(g);
                    ss.insert(e);
                    pq.push(e);
                }
            });
        }

        auto l = &*(ss.begin());
        for(auto& e: ss)
            if(e > *l)
                l = &e;

        return *l;
    }
};

/** example Project Euler 18のExample
using uint = unsigned int;
vector<vector<uint>> v = {{3}, {7, 5}, {2, 4, 6}, {8, 5, 9, 3}};

// 状態を表す型
struct S {
    uint i, j, c;

    // 評価値の高さを比較
    bool operator>(S const & e) const { return c > e.c; }

    // 状態が等しいか比較
    bool operator==(S const & e) const { return i == e.i && j == e.j; }

    // ハッシュ関数
    size_t hash() const { return s.i + s.j; }
};

// パス(枝)を表す型
struct P {
    uint i, j, c;

    // ある状態から、このパスを通った次の状態への遷移
    S apply(S const & s) const { return {i, j, s.c + c}; }
};

// 全体の状態
struct GS
{
    // ある状態から通ることができるパスを列挙する
    template <typename Fn>
    void iterP(S & s, Fn fn)
    {
        if(s.i == 3)
            return;

        auto i = s.i+1,
             j = s.j;
        fn({i, j, v[i][j]});
        fn({i, j+1, v[i][j+1]});
    }
};


int main()
{
    GS fn;
    cout << Dijkstra<S, P, GS>(fn).solve({0, 0, v[0][0]}).c << endl;
    return 0;
}
*/