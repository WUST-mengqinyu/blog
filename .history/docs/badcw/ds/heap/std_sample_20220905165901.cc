#include <queue>
#include <cassert>
int main() {
    std::priority_queue<int> p;
    assert(p.empty() == true);
    assert(p.size() == 0);
    p.push(1);
    assert(p.empty() == false);
    assert(p.size() == 1);
}