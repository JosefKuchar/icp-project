/**
 * @author Josef Kuchař <xkucha28@stud.fit.vutbr.cz>
 * @author Matej Sirovatka <xsirov00@stud.fit.vutbr.cz>
 * @file player.cpp
 * @brief Player implementation
 */

#include "player.hpp"

#include <algorithm>
#include <queue>
#include <climits>

Player::Player() {
    this->m_movementMode = MovementMode::None;
    this->m_direction = Direction::Up;
    this->m_targetPosition = Point(0, 0);
}

Player::Player(Map* map, Point position) : Object(map, position) {
    this->m_movementMode = MovementMode::None;
    this->m_direction = Direction::Up;
    this->m_targetPosition = Point(0, 0);
}

void Player::tick() {
    if (this->m_movementMode == MovementMode::None) {
        return;
    } else if (this->m_movementMode == MovementMode::Keys) {
        if (!this->m_map->isInWall(this->position + this->m_direction)) {
            this->position += this->m_direction;
        }
    } else {
        if (this->position == this->m_targetPosition) {
            this->m_movementMode = MovementMode::None;
            return;
        }
        std::vector<Point> path = this->calculateDirection();
        
        if (path.size() < 2) {
            this->m_movementMode = MovementMode::None;
            return;
        }

        Point point = path[1];

        this->position = point;

        return;
    }
}

void Player::setDirection(Direction direction) {
    this->m_direction = direction;
    this->m_movementMode = MovementMode::Keys;
}

void Player::setTargetPosition(Point position) {
    this->m_targetPosition = position;
    this->m_movementMode = MovementMode::Mouse;
}

std::vector<Point> Player::calculateDirection() {
    using namespace std;
    auto map = this->m_map->m_map;

    auto heuristic = [](int x, int y, int end_x, int end_y) {
        return abs(x - end_x) + abs(y - end_y);
    };

    int cols = map.size();
    int rows = map[0].size();

    priority_queue<pair<int, Point>, vector<pair<int, Point>>, greater<pair<int, Point>>> op;
    vector<vector<int>> g(rows, vector<int>(cols, INT_MAX));
    vector<vector<int>> h(rows, vector<int>(cols, 0));

    vector<vector<Point>> parent(rows, vector<Point>(cols, Point(1, -1)));

    int start_x = this->position.x;
    int start_y = this->position.y;

    g[start_x][start_y] = 0;
    h[start_x][start_y] = heuristic(start_x, start_y, this->m_targetPosition.x, this->m_targetPosition.y);
    op.push(make_pair(h[start_x][start_y], Point(start_x, start_y)));

    while (!op.empty()) {
        Point current = op.top().second;

        op.pop();

        if (current.x == this->m_targetPosition.x && current.y == this->m_targetPosition.y) {
            vector<Point> path;

            while (current.x != -1 && current.y != -1) {
                path.push_back(current);
                Point parent_pos = parent[current.x][current.y];
                current = parent_pos;
            }
            reverse(path.begin(), path.end());
            return path;
        }

        Direction dir[] = {Direction::Up, Direction::Right, Direction::Down, Direction::Left};
        for (auto d : dir) {
            Point new_point = current + d;

            if (!this->m_map->isInWall(new_point)) {
                int tentativeG = g[current.x][current.y] + 1;

                if (tentativeG < g[new_point.x][new_point.y]) {
                    g[new_point.x][new_point.y] = tentativeG;
                    h[new_point.x][new_point.y] = heuristic(new_point.x, new_point.y, this->m_targetPosition.x, this->m_targetPosition.y);
                    int totalCost = g[new_point.x][new_point.y] + h[new_point.x][new_point.y];
                    op.push(make_pair(totalCost, new_point));
                    parent[new_point.x][new_point.y] = current;
                }
            }
        }

    }

    return vector<Point>();
}
