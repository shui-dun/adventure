#include "astar.h"
#include <vector>
#include <queue>
#include <cmath>
#include "map.h"
#include <fstream>

int AStar::Cmp::predictedDistance(const AStar::Node &a) {
    return abs(a.x - dest->xPos) + abs(a.y - dest->yPos);
}

bool AStar::Cmp::operator()(const AStar::Node &a, const AStar::Node &b) {
    return a.distance + predictedDistance(a) > b.distance + predictedDistance(b);
}

Item *AStar::Cmp::dest;

pair<int, int> AStar::operator()(Item *fromItem, Item *toItem) {
    Cmp::dest = toItem;

    priority_queue<Node, vector<Node>, Cmp> q;

    vector<vector<Pre>> pres;

    pres.assign(MapUtils::nCols(), vector<Pre>(MapUtils::nLines(), Pre(-1, -1, -1)));

    Node fromNode(fromItem->xPos, fromItem->yPos, 0);
    q.push(fromNode);
    pres[fromItem->xPos][fromItem->yPos] = Pre(-1, -1, 0);

    bool success = false;
    pair<int, int> ans(-1, -1);

    while (!q.empty() && !success) {
        auto node = q.top();
        q.pop();
        for (int direction = 0; direction < 4; ++direction) {
            auto pr = MapUtils::nextPosOfDirection(node.x, node.y, direction);
            if (pres[pr.first][pr.second].distance == -1) {
                if (pr.first == toItem->xPos && pr.second == toItem->yPos) {
                    int preX = node.x, preY = node.y, curX = pr.first, curY = pr.second;
                    while (!(preX == fromNode.x && preY == fromNode.y)) {
                        curX = preX;
                        curY = preY;
                        preX = pres[curX][curY].preX;
                        preY = pres[curX][curY].preY;
                    }
                    ans.first = curX;
                    ans.second = curY;
                    success = true;
                    break;
                }
                if (!MapUtils::gameMap[pr.first][pr.second]) {
                    Node newNode(pr.first, pr.second, node.distance + 1);
                    q.push(newNode);
                    pres[pr.first][pr.second] = Pre(node.x, node.y, node.distance + 1);
                }
            }
        }
    }
    return ans;
}