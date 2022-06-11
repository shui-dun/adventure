#include "search.h"
#include <vector>
#include <queue>
#include <cmath>
#include "map.h"
#include <fstream>
#include <unordered_set>

int AStar::Cmp::predictedDistance(const Node *a) {
    return abs(a->x - dest->xPos) + abs(a->y - dest->yPos);
}

bool AStar::Cmp::operator()(const Node *a, const Node *b) {
    return a->distance + predictedDistance(a) > b->distance + predictedDistance(b);
}

Item *AStar::Cmp::dest;

size_t AxisHash::operator()(const pair<int, int> &node) const {
    size_t seed = 0;
    hash_combine(seed, node.first);
    hash_combine(seed, node.second);
    return seed;
}

pair<int, int> AStar::operator()(Item *fromItem, Item *toItem) {
    Cmp::dest = toItem;
    // 优先队列，每个弹出代价最小的坐标
    priority_queue<Node *, vector<Node *>, Cmp> q;
    // 保存动态分配的节点，用于后续的释放
    vector<Node *> release;
    // 存放访问过的坐标
    unordered_set<pair<int, int>, AxisHash> st;

    auto fromNode = new Node(fromItem->xPos, fromItem->yPos, 0, nullptr);
    q.push(fromNode);
    release.push_back(fromNode);
    st.insert(pair<int, int>(fromNode->x, fromNode->y));

    bool success = false;
    pair<int, int> ans(-1, -1);

    while (!q.empty() && !success) {
        auto node = q.top();
        q.pop();
        for (int direction = 0; direction < 4; ++direction) {
            auto pr = MapUtils::nextPosOfDirection(node->x, node->y, direction);
            if (st.find(pr) == st.end() &&
                (!MapUtils::gameMap[pr.first][pr.second] ||
                 (pr.first == toItem->xPos && pr.second == toItem->yPos))) {
                auto newNode = new Node(pr.first, pr.second, node->distance + 1, node);
                q.push(newNode);
                release.push_back(newNode);
                st.insert(pr);
                if (pr.first == toItem->xPos && pr.second == toItem->yPos) {
                    Node *preNode = node;
                    Node *curNode = newNode;
                    while (preNode != fromNode) {
                        curNode = preNode;
                        preNode = curNode->pre;
                    }
                    ans.first = curNode->x;
                    ans.second = curNode->y;
                    success = true;
                    break;
                }
            }
        }
    }
    for (auto p: release) {
        delete p;
    }
    return ans;
}

pair<Item *, pair<int, int>> BFS::operator()(Item *fromItem, const function<bool(Item *)> &func) {
    // 队列，用于广度优先搜索
    queue<Node *> q;
    // 保存动态分配的节点，用于后续的释放
    vector<Node *> release;
    // 存放访问过的坐标
    unordered_set<pair<int, int>, AxisHash> st;
    auto fromNode = new Node(fromItem->xPos, fromItem->yPos, 0, nullptr);
    q.push(fromNode);
    release.push_back(fromNode);
    st.insert(pair<int, int>(fromNode->x, fromNode->y));

    bool success = false;
    pair<Item *, pair<int, int>> ans(nullptr, pair<int, int>(-1, -1));

    while (!q.empty() && !success) {
        auto node = q.front();
        q.pop();
        for (int direction = 0; direction < 4; ++direction) {
            auto pr = MapUtils::nextPosOfDirection(node->x, node->y, direction);
            if (st.find(pr) == st.end()) {
                st.insert(pr);
                if (!MapUtils::gameMap[pr.first][pr.second]) {
                    auto newNode = new Node(pr.first, pr.second, node->distance + 1, node);
                    release.push_back(newNode);
                    q.push(newNode);
                } else if (func(MapUtils::gameMap[pr.first][pr.second])) {
                    auto newNode = new Node(pr.first, pr.second, node->distance + 1, node);
                    release.push_back(newNode);
                    Node *preNode = node;
                    Node *curNode = newNode;
                    while (preNode != fromNode) {
                        curNode = preNode;
                        preNode = curNode->pre;
                    }
                    ans.first = MapUtils::gameMap[pr.first][pr.second];
                    ans.second = pair<int, int>(curNode->x, curNode->y);
                    success = true;
                    break;
                }
            }
        }
    }
    for (auto p: release) {
        delete p;
    }
    return ans;
}
