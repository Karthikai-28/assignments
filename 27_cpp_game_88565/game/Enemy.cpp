#include "SFML-2.5.1\include\SFML\Graphics.hpp"
#include "Enemy.h"
class Enemy
{
public:
Enemy();
~Enemy();

void init(std::string textureName, sf::Vector2f position, float_speed);

void update(float dt);
    sf::Sprite getSprite();
    private:
    sf::Texture m_texture;
    sf::Sprite m_sprite;
    sf::Vector2f m_position;
    float m_speed;
}

Enemy::Enemy(){}
Enemy::~Enemy(){}

void Enemy::init(std::string textureName, sf::Vector2f position, float _speed) {
    m_speed = _speed;
    m_position = position;
    // Load a Texture
    m_texture.loadFromFile(textureName.c_str());
    // Create Sprite and Attach a Texture
    m_sprite.setTexture(m_texture);
    m_sprite.setPosition(m_position);
    m_sprite.setOrigin(m_texture.getSize().x / 2,
    m_texture.getSize().y / 2);
}

void Enemy::update(float dt) {
    m_sprite.move(m_speed * dt, 0);
    }
    sf::Sprite Enemy::getSprite() {
    return m_sprite;
}