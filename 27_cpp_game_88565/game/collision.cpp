void spawnEnemy();
void shoot();
bool checkCollision(sf::Sprite sprite1, sf::Sprite sprite2);
void shoot() {
Rocket* rocket = new Rocket();
rocket->init("Assets/graphics/rocket.png",
hero.getSprite().getPosition(), 400.0f);
rockets.push_back(rocket);
}
bool checkCollision(sf::Sprite sprite1, sf::Sprite sprite2) {
sf::FloatRect shape1 = sprite1.getGlobalBounds();
sf::FloatRect shape2 = sprite2.getGlobalBounds();
if (shape1.intersects(shape2)) {
return true;
}
else {
return false;
}
}
