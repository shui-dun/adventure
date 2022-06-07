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


size_t AStar::NodeHash::operator()(const AStar::Node *node) const {
    size_t seed = 0;
    hash_combine(seed, node->x);
    hash_combine(seed, node->y);
    return seed;
}

bool AStar::NodeEquals::operator()(const AStar::Node *a, const AStar::Node *b) const {
    return a->x == b->x && a->y == b->y;
}

pair<int, int> AStar::operator()(Item *fromItem, Item *toItem) {
    Cmp::dest = toItem;

    priority_queue<Node *, vector<Node *>, Cmp> q;

    unordered_set<Node *, NodeHash, NodeEquals> st;

    auto fromNode = new Node(fromItem->xPos, fromItem->yPos, 0, nullptr);
    q.push(fromNode);
    st.insert(fromNode);

    bool success = false;
    pair<int, int> ans(-1, -1);

    while (!q.empty() && !success) {
        auto node = q.top();
        q.pop();
        for (int direction = 0; direction < 4; ++direction) {
            auto pr = MapUtils::nextPosOfDirection(node->x, node->y, direction);
            auto newNode = new Node(pr.first, pr.second, node->distance + 1, node);
            if (st.find(newNode) == st.end()) {
                st.insert(newNode);
                if (newNode->x == toItem->xPos && newNode->y == toItem->yPos) {
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
                if (!MapUtils::gameMap[pr.first][pr.second]) {
                    q.push(newNode);
                }
            } else {
                delete newNode;
            }
        }
    }
    for (auto p: st) {
        delete p;
    }
    return ans;
}