#include <SFML/Graphics.hpp>
#include <vector>
#include "iostream"
#include <thread>
#include <chrono>

#define SIZE 8

using namespace  std;


vector<vector<int>> PrintBoardBeg(){
    vector<vector<int>> coord;
    vector<int> data;
    sf::RenderWindow window(sf::VideoMode(800, 800), "Chessboard");
    sf::RectangleShape square(sf::Vector2f(100, 100));

    bool isWhite = true;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (isWhite) {
                square.setFillColor(sf::Color::White);
            } else {
                square.setFillColor(sf::Color::Black);
            }

            square.setPosition(i * 100, j * 100);
            window.draw(square);

            isWhite = !isWhite;
        }
        isWhite = !isWhite;
    }

    window.display();

    bool isPieceSelected = false;
    sf::Vector2f selectedPosition;

    vector<sf::Vector2f> q;

    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)) {
            isPieceSelected = false;
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y)); // получаем позицию мыши в координатах окна
                    int x = mousePosition.x / 100;
                    int y = mousePosition.y / 100;
                    data.push_back(x);
                    data.push_back(y);
                    coord.push_back(data);
                    data.clear();
                    if (!isPieceSelected) {
                        selectedPosition = sf::Vector2f(x * 100, y * 100);
                        isPieceSelected = true;
                        q.push_back(selectedPosition);
                    }
                }
            }
        }
        window.clear();
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if ((i + j) % 2 == 0) {
                    square.setFillColor(sf::Color(255, 206, 158));
                } else {
                    square.setFillColor(sf::Color(209, 139, 71));
                }

                square.setPosition(i * 100, j * 100);
                window.draw(square);
            }
        }
        for(int i = 0; i < q.size(); ++i){
            sf::CircleShape shape(50.f);
            shape.setFillColor(sf::Color::Red);
            shape.setPosition(q[i]);
            window.draw(shape);
        }
        window.display();
    }
    return coord;
};


void PrintBoardFin(int final[SIZE][SIZE]){
    sf::RenderWindow window_f(sf::VideoMode(800, 800), "Chessboard");
    sf::RectangleShape square_f(sf::Vector2f(100, 100));
    bool isWhite = true;
    sf::Vector2f selectedPosition;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (isWhite)
                square_f.setFillColor(sf::Color::White);
            else
                square_f.setFillColor(sf::Color::Black);
            square_f.setPosition(i * 100, j * 100);
            window_f.draw(square_f);

            isWhite = !isWhite;
        }
        isWhite = !isWhite;
    }

    window_f.display();

    while (window_f.isOpen()){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if ((i + j) % 2 == 0) {
                    square_f.setFillColor(sf::Color(255, 206, 158));
                } else {
                    square_f.setFillColor(sf::Color(209, 139, 71));
                }

                square_f.setPosition(i * 100, j * 100);
                window_f.draw(square_f);
            }
        }

        for(int i = 0; i < SIZE; ++i){
            for (int j = 0; j < SIZE; ++j) {
                if (final[i][j] == 2){
                    selectedPosition = sf::Vector2f(i * 100, j * 100);
                    sf::CircleShape shape(50.f);
                    shape.setFillColor(sf::Color::Red);
                    shape.setPosition(selectedPosition);
                    window_f.draw(shape);
                }
                else if (final[i][j] == 1) {
                    selectedPosition = sf::Vector2f(i * 100, j * 100);
                    sf::CircleShape shape(50.f);
                    shape.setFillColor(sf::Color::Green);
                    shape.setPosition(selectedPosition);
                    window_f.draw(shape);
                }
            }
        }
        window_f.display();

        const auto start = std::chrono::high_resolution_clock::now();
        std::this_thread::sleep_for(10000ms);
        const auto end = std::chrono::high_resolution_clock::now();
        const std::chrono::duration<double, std::milli> elapsed = end - start;
        window_f.close();
    }
}
