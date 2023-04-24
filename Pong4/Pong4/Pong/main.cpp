#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "Animation.hpp"
#include "Grass.hpp"
#include "Hurdle.hpp"
#include "Obstacle.hpp"
#include "Spawner.hpp"

using std::vector;

int main() {
    int UNITSIZE = 96;

    sf::Texture textures[3];

    // dirt texture
    sf::Texture &blockTexture = textures[0];
    blockTexture.loadFromFile("testDirt.png");
    blockTexture.setRepeated(true);

    /// grass texture
    sf::Texture grassTexture;
    grassTexture.loadFromFile("testGrass.png");
    grassTexture.setRepeated(true);

    // tree texture
    sf::Texture &treeTexture = textures[1];
    treeTexture.loadFromFile("testTree.png");
    // treeTexture.setRepeated(true);

    // shrub texture
    sf::Texture &shrubTexture = textures[2];
    shrubTexture.loadFromFile("testShrub.png");

    // the speed at which obstacles should move
    float curSpeed = 1;

    // self explanatory
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "runner game");
    window.setFramerateLimit(100);

    // creates the collection of obstacles
    vector<Obstacle *>
        obVect;  // we need to have pointers, copies don't work I tried

    // 96 is pixels per unit/block
    int generationCounter = 0;

    spawnStartingGround(obVect, textures[0], UNITSIZE);

    /// player animation test
    Animation player(sf::Vector2f(500, 404), 10);

    while (window.isOpen()) {
        if (generationCounter == 0) {
            spawnNewGround(generationCounter, obVect, textures, UNITSIZE);
        }

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // set each obstacles speed
        for (auto i : obVect) {
            i->setSpeed(curSpeed);
        }

        // move each obstacle
        for (auto i : obVect) {
            i->move(-i->getSpeed(), 0);
        }

        /// update animation fram
        player.frameUpdate();

        // clear the window before drawing shit
        window.clear();

        // draw each obstacle
        for (auto i : obVect) {
            window.draw(*i);
        }

        window.draw(player);

        window.display();

        generationCounter--;
    }

    return 0;
}