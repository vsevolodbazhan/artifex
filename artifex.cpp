#include <vector>
#include <fstream>
#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>

using namespace sf;
using namespace std;
using json = nlohmann::json;

int main() {
    json source;
    ifstream input("json/file2_100_100.json");
    input >> source;
    vector<RectangleShape> cells;

    for (auto& item : source["data"][0]) {
        auto cell = RectangleShape(Vector2f(1, 1));
        auto color = Color(item[0], item[1], item[2]);
        cell.setFillColor(color);
        cells.push_back(cell);
    }

    RenderWindow window(VideoMode(source["width"], source["height"]), "Artifex");

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear();

        float position_x = 0.f;
        float position_y = 0.f;

        int drawn_cells = 0;

        for (auto& cell : cells) {
            cell.setPosition(position_x, position_y);
            window.draw(cell);
            position_x += 1.f;
            drawn_cells += 1;
            if (drawn_cells == source["width"]) {
                position_x = 0.f;
                position_y += 1.f;
                drawn_cells = 0;
            }
        }

        window.display();
    }

    return 0;
}
