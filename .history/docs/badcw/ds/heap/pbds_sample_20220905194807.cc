#include <bits/extc++.h>
// #include <ext/pb_ds/priority_queue.hpp>

int main() {
    typedef std::pair<int, int> pii;
    typedef __gnu_pbds::priority_queue<pii> pq;
    pq p;
    auto it = p.push({1, 2});
    assert(p.top() == (pii{1, 2}));
    p.modify(it, {2, 3});
    assert(p.top() == (pii{2, 3}));
    pq q;
    q.push({1, 5});
    p.join(q);
    assert(p.size() == 2);
    for (auto i : p) std::cout << i.first << " " << i.second << std::endl;
}