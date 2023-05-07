/**
 * @author Josef Kuchař <xkucha28@stud.fit.vutbr.cz>
 * @author Matej Sirovatka <xsirov00@stud.fit.vutbr.cz>
 * @file player.cpp
 * @brief Player implementation
 */

#include "player.hpp"

#include <algorithm>
#include <climits>
#include <queue>

Player::Player() {
    this->movementMode = MovementMode::None;
    this->direction = Direction::Up;
    this->targetPosition = Point(0, 0);
}

Player::Player(Map* map, Point position) : Object(map, position) {
    this->movementMode = MovementMode::None;
    this->direction = Direction::Up;
    this->targetPosition = Point(0, 0);
}

void Player::tick() {
    // No movement
    if (this->movementMode == MovementMode::None) {
        return;
        // Movement by keys
    } else if (this->movementMode == MovementMode::Keys) {
        if (!this->map->isInWall(this->position + this->direction)) {
            this->position += this->direction;
        }
        // Movement by mouse
    } else {
        if (this->position == this->targetPosition) {
            this->movementMode = MovementMode::None;
            return;
        }
        std::vector<Point> path = this->calculateDirection();
        if (path.size() < 2) {
            this->movementMode = MovementMode::None;
            return;
        }
        Point point = path[1];
        this->position = point;
    }
}

void Player::setDirection(Direction direction) {
    this->direction = direction;
    this->movementMode = MovementMode::Keys;
}

void Player::setTargetPosition(Point position) {
    this->targetPosition = position;
    this->movementMode = MovementMode::Mouse;
}

/**
 * @brief Calculate direction with A* algorithm
 */
std::vector<Point> Player::calculateDirection() {
    using namespace std;
    auto map = this->map->map;

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
    h[start_x][start_y] =
        heuristic(start_x, start_y, this->targetPosition.x, this->targetPosition.y);
    op.push(make_pair(h[start_x][start_y], Point(start_x, start_y)));

    while (!op.empty()) {
        Point current = op.top().second;

        op.pop();

        if (current.x == this->targetPosition.x && current.y == this->targetPosition.y) {
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

            if (!this->map->isInWall(new_point)) {
                int tentativeG = g[current.x][current.y] + 1;

                if (tentativeG < g[new_point.x][new_point.y]) {
                    g[new_point.x][new_point.y] = tentativeG;
                    h[new_point.x][new_point.y] = heuristic(
                        new_point.x, new_point.y, this->targetPosition.x, this->targetPosition.y);
                    int totalCost = g[new_point.x][new_point.y] + h[new_point.x][new_point.y];
                    op.push(make_pair(totalCost, new_point));
                    parent[new_point.x][new_point.y] = current;
                }
            }
        }
    }

    return vector<Point>();
}
