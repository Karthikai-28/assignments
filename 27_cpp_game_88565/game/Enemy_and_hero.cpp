#include "SFML-2.5.1\include\SFML\Graphics.hpp"
#include <vector>
#include "Player.h"
#include "Enemy.h"

sf::Texture bgTexture;
sf::Sprite bgSprite;

Player::Player;

std::vector<Enemy*> enemies;

sf::Vector2f viewSize(1024, 768);
sf::VideoMode vm(viewSize.x, viewSize.y);
sf::RenderWindow window(vm, "Hello SFML Game !!!",
sf::Style::Default);
void spawnEnemy();
player.init("Assets/graphics/hero.png", sf::Vector2f(viewSize.x *
0.25f, viewSize.y * 0.5f), 200);
srand((int)time(0));

void spawnEnemy() {
    int randLoc = rand() % 3;
    sf::Vector2f enemyPos;
    float speed;
    switch (randLoc) {
    case 0: enemyPos = sf::Vector2f(viewSize.x, viewSize.y * 0.75f);
    speed = -400; break;
    case 1: enemyPos = sf::Vector2f(viewSize.x, viewSize.y * 0.60f);
    speed = -550; break;
    case 2: enemyPos = sf::Vector2f(viewSize.x, viewSize.y * 0.40f);
    speed = -650; break;
    default: printf("incorrect y value \n"); return;
    }
    Enemy* enemy = new Enemy();
    enemy->init("Assets/graphics/enemy.png", enemyPos, speed);
    enemies.push_back(enemy);
}

Player::Player;
std::vector<Enemy*> enemies;
float currentTime;
float prevTime = 0.0f;

Player.update(dt);
currentTime += dt;
// Spawn Enemies
if (currentTime >= prevTime + 1.125f)))) {
spawnEnemy();
prevTime = currentTime;
}
// Update Enemies
for (int i = 0; i < enemies.size(); i++) {
Enemy *enemy = enemies[i];
enemy->update(dt);
if (enemy->getSprite().getPosition().x < 0) {
enemies.erase(enemies.begin() + i);
delete(enemy);
}
}
window.draw(skySprite);
window.draw(bgSprite);
window.draw(hero.getSprite());
for (Enemy *enemy : enemies) {
window.draw(enemy->getSprite());
}