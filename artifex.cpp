#include <vector>
#include <fstream>
#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>

using namespace sf;
using namespace std;
using json = nlohmann::json;

struct AnimationDescription {
    float width;
    float height;
    int frames;
    vector<vector<int>> data;
};

vector<RectangleShape> cells = {
    RectangleShape(Vector2f(100, 100)),
    RectangleShape(Vector2f(100, 100)),
    RectangleShape(Vector2f(100, 100)),
};

AnimationDescription readJSONFile(const string& filename) {
    json source;
    ifstream input(filename);
    input >> source;
    return {
        source["width"],
        source["height"],
        source["frames"],
        source["data"]
    };
}

int main() {
    AnimationDescription description = readJSONFile("json/file1_10_10.json");

    RenderWindow window(sf::VideoMode(800, 600), "SFML works!");

    // cells[0].setFillColor(Color::Green);
    // cells[1].setPosition(0.f, 0.f);

    // cells[1].setFillColor(Color::Green);
    // cells[1].setPosition(100.f, 0.f);

    // cells[2].setFillColor(Color::Green);
    // cells[2].setPosition(200.f, 0.f);

    // while (window.isOpen())
    // {
    //     Event event;
    //     while (window.pollEvent(event))
    //     {
    //         if (event.type == Event::Closed)
    //             window.close();
    //     }

    //     window.clear();
    //     for (auto cell : cells) {
    //         window.draw(cell);
    //     }

    //     window.display();
    // }

    return 0;
}
