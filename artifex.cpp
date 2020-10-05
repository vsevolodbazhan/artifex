#include <vector>
#include <fstream>
#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>

using namespace sf;
using namespace std;
using json = nlohmann::json;

class Frame {
    public:
        Frame(const unsigned width, const unsigned height, const vector<vector<Uint8>>& cells) {
            Image image;
            image.create(width, height);
            for (unsigned int j = 0; j < height; ++j) {
                for (unsigned int i = 0; i < width; ++i) {
                    const auto cell = cells[j * width + i];
                    // cout << i << ' ' << j << ' ' << j * height << ' ' << cells.size() << ' ' << endl;
                    const auto color = Color(cell[0], cell[1], cell[2]);
                    image.setPixel(i, j, color);
                }
            }

            for (unsigned int i = 0; i < cells.size(); ++i) {

            }

            texture.loadFromImage(image);
        }

        const Sprite& getSprite() {
            sprite.setTexture(texture);
            return sprite;
        }

    private:
        Sprite sprite;
        Texture texture;
};


int main() {
    json source;
    ifstream input("json/file6_1500_600.json");
    input >> source;

    vector<Frame> frames;
    for (unsigned i = 0; i < source["frames"]; ++i) {
        frames.push_back(Frame(source["width"], source["height"], source["data"][i]));
    }

    Clock clock;

    int current_frame = 0;
    Time next_frame_time = milliseconds(0);
    Time time_between_frames = milliseconds(100);

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
            window.clear();
            window.draw(frames[current_frame].getSprite());
            window.display();

            if ((current_frame + 1) == source["frames"]) {
                current_frame = 0;
            } else {
                current_frame += 1;
            }

            next_frame_time += time_between_frames;
        }
    }

    return 0;
}
