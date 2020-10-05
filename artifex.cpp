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
    Clock clock;

    int current_frame = 0;
    Time next_frame_time = milliseconds(0);
    Time time_between_frames = milliseconds(30);

    json source;
    ifstream input("json/file5_1160_786.json");
    input >> source;
    vector<vector<RectangleShape>> frames;

    for (int i = 1; i <= source["frames"]; i++) {
        vector<RectangleShape> cells;
        for (auto& item : source["data"][i]) {
            auto cell = RectangleShape(Vector2f(1, 1));
            auto color = Color(item[0], item[1], item[2]);
            cell.setFillColor(color);
            cells.push_back(cell);
        }
        frames.push_back(cells);
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

        if (next_frame_time <= clock.getElapsedTime()) {

            float position_x = 0.f;
            float position_y = 0.f;

            int drawn_cells = 0;

            for (auto& cell : frames[current_frame]) {
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

            if ((current_frame  + 1) == source["frames"]) {
                current_frame = 0;
            } else {
                current_frame += 1;
            }

            next_frame_time += time_between_frames;
        }

        window.display();
    }

    return 0;
}
