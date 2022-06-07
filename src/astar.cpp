#include "astar.h"
#include <vector>
#include <queue>
#include <cmath>
#include "map.h"
#include <fstream>
#include <unordered_set>

int AStar::Cmp::predictedDistance(const AStar::Node *a) {
    return abs(a->x - dest->xPos) + abs(a->y - dest->yPos);
}

bool AStar::Cmp::operator()(const AStar::Node *a, const AStar::Node *b) {
    return a->distance + predictedDistance(a) > b->distance + predictedDistance(b);
}

Item *AStar::Cmp::dest;

size_t AStar::AxisHash::operator()(const pair<int, int> &node) const {
    size_t seed = 0;
    hash_combine(seed, node.first);
    hash_combine(seed, node.second);
    return seed;
}

pair<int, int> AStar::operator()(Item *fromItem, Item *toItem) {
    Cmp::dest = toItem;

    priority_queue<Node *, vector<Node *>, Cmp> q;

    vector<Node *> release;

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

