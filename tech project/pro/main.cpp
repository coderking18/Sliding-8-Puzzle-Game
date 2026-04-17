#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include <ctime>
#include <random>

int main() {
    sf::RenderWindow window(sf::VideoMode(400, 400), "Memory Game");

    int rows = 4, cols = 4;
    int size = 80;

    // Create pairs
    std::vector<int> cards;
    for (int i = 1; i <= 8; i++) {
        cards.push_back(i);
        cards.push_back(i);
    }

    std::random_shuffle(cards.begin(), cards.end());

    std::vector<bool> revealed(16, false);

    int first = -1, second = -1;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                int x = event.mouseButton.x / size;
                int y = event.mouseButton.y / size;

                int index = y * cols + x;

                if (!revealed[index]) {
                    if (first == -1)
                        first = index;
                    else if (second == -1 && index != first)
                        second = index;
                }
            }
        }

        // Check match
        if (first != -1 && second != -1) {
            if (cards[first] == cards[second]) {
                revealed[first] = revealed[second] = true;
            }
            sf::sleep(sf::milliseconds(500));
            first = second = -1;
        }

        window.clear();

        for (int i = 0; i < 16; i++) {
            int x = (i % cols) * size;
            int y = (i / cols) * size;

            sf::RectangleShape card(sf::Vector2f(size - 5, size - 5));
            card.setPosition(x, y);

            if (revealed[i] || i == first || i == second) {
                card.setFillColor(sf::Color::Green);
            } else {
                card.setFillColor(sf::Color::Blue);
            }

            window.draw(card);
        }

        window.display();
    }

    return 0;
}