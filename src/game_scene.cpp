#include "game_scene.hpp"
#include "player.hpp"

Grid::Grid(MapInfo& map) {
    QPixmap pacmanPixmap(":assets/pacman.png");
    QPixmap ghostPixmap(":assets/ghost.png");
    QPixmap wallPixmap(":assets/wall.png");
    QPixmap emptyPixmap(":assets/empty.png");
    QPixmap keyPixmap(":assets/key.png");
    QPixmap targetPixmap(":assets/target.png");

    for (int row = 0; row < map.height; ++row) {
        for (int col = 0; col < map.width; ++col) {
            switch (map.map[row][col]) {
                case Tile::Player:
                    m_spritePixmap = pacmanPixmap;
                    break;
                case Tile::Ghost:
                    m_spritePixmap = ghostPixmap;
                    break;
                case Tile::Wall:
                    m_spritePixmap = wallPixmap;
                    break;
                case Tile::Empty:
                    m_spritePixmap = emptyPixmap;
                    break;
                case Tile::Key:
                    m_spritePixmap = keyPixmap;
                    break;
                case Tile::Target:
                    m_spritePixmap = targetPixmap;
                    break;
            }
            Sprite* sprite = new Sprite(m_spritePixmap);
            sprite->setPos(col * (m_spritePixmap.width()), row * (m_spritePixmap.height()));
            addItem(sprite);
            m_sprites.append(sprite);
        }
    }

    Player* player = new Player(pacmanPixmap);
    addItem(player);
}

void Grid::updatePositions() {
    for (auto sprite : m_sprites) {
        QPointF pos = sprite->pos();
        // pos.setX(pos.x() + 1.0f);  // Update the x position of the sprite
        sprite->setPos(pos);
    }
}
