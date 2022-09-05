#include <bits/extc++.h>
// #include <ext/pb_ds/priority_queue.hpp>

int main() {
    typedef std::pair<int, int> pii;
    // by default use pairing_heap_tag
    typedef __gnu_pbds::priority_queue<pii> pq;

    typedef __gnu_pbds::priority_queue<pii, std::greater<>, thin_heap_tag> pq;
    pq p;
    auto it = p.push({1, 2});
    assert(p.top() == (pii{1, 2}));
    p.modify(it, {2, 3});
    assert(p.top() == (pii{2, 3}));
    pq q;
    q.push({1, 5});
    p.join(q);
    assert(p.size() == 2);
    std::vector<pii> res(p.begin(), p.end());
    assert(res == (std::vector<pii>{(pii{1,5}), (pii{2,3})}));
    p.split(1);
}