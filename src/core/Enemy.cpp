#include "Enemy.h"

Enemy::Enemy() {}

void Enemy::init(const sf::Texture& tex, const sf::Vector2f& pos) {
    setTexture(tex, 64, 64, 4, 0.13f);
    setPosition(pos);
    alive = true;
    health = 30.f;
}

void Enemy::save(std::ofstream& out) const {
    auto pos = getPosition();
    out << pos.x << ' ' << pos.y << ' ' << health << ' ' << alive << '\n';
}

void Enemy::load(std::ifstream& in, const sf::Texture& tex) {
    float x, y, h; int a;
    in >> x >> y >> h >> a;
    setTexture(tex, 64, 64, 4, 0.13f);
    setPosition({x, y});
    health = h;
    alive = a;
}

std::ostream& operator<<(std::ostream& os, const Enemy& e) {
    os << e.position.x << " " << e.position.y << " " << e.health;
    return os;
}
