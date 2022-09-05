#include <queue>
#include <cassert>
#include <iostream>

int main() {
    // big heap
    std::priority_queue<int> p;
    assert(p.empty() == true);
    assert(p.size() == 0);
    // p.top(), p.pop(), core dump
    p.push(1);
    assert(p.empty() == false);
    assert(p.size() == 1);
    assert(p.top() == 1);
    p.push(2);
    assert(p.empty() == false);
    assert(p.size() == 2);
    assert(p.top() == 2);
    p.pop();
    assert(p.empty() == false);
    assert(p.size() == 1);
    assert(p.top() == 1);

    std::priority_queue<int, std::vector<int>, std::greater<>> p2;
    p2.push(2);
    p2.push(1);
    assert(p2.top() == 1);
    
    std::vector<int> a = {2, 3, 5, 1, 4};
    std::make_heap(a.begin(), a.end());
    assert(a == (std::vector<int>{5, 4, 2, 1, 3}));

    a.push_back(6);
    std::push_heap(a.begin(), a.end());
    assert(a == (std::vector<int>{6, 4, 5, 1, 3, 2}));

    std::pop_heap(a.begin(), a.end());
    assert(a == (std::vector<int>{5, 4, 2, 1, 3, 6}));
    assert(std::is_heap(a.begin(), a.end()) == false); // has pop one but not delete from vector
    a.pop_back();
    assert(std::is_heap(a.begin(), a.end()) == true);
    return 0;
}
