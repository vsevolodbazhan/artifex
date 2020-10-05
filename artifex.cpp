#include <vector>
#include <fstream>
#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>

using namespace sf;
using namespace std;
using json = nlohmann::json;


unsigned calculateScore(
    const Time& time_to_first_frame,
    const Time& time_to_last_frame,
    const Time& time_between_frames,
    const unsigned number_of_frames
) {
    const unsigned T1 = time_to_first_frame.asMilliseconds();
    const unsigned T2 = time_to_last_frame.asMilliseconds();
    const unsigned M = time_between_frames.asMilliseconds();
    const unsigned F = number_of_frames;
    return T1 + T2 - (M * (F - 1));
}

class Frame {
    public:
        Frame(const unsigned width, const unsigned height, const vector<vector<Uint8>>& cells) {
            Image image;
            image.create(width, height);
            for (unsigned int j = 0; j < height; ++j) {
                for (unsigned int i = 0; i < width; ++i) {
                    const auto cell = cells[j * width + i];
                    const auto color = Color(cell[0], cell[1], cell[2]);
                    image.setPixel(i, j, color);
                }
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


int main(int argc, char** argv)  {
    Clock clock;

    json source;
    ifstream input(argv[1]);
    input >> source;

    const unsigned width = source["width"];
    const unsigned height = source["height"];
    const unsigned number_of_frames = source["frames"];
    const auto& data = source["data"];

    vector<Frame> frames;
    for (unsigned i = 0; i < number_of_frames; ++i) {
        frames.push_back(Frame(width, height, data[i]));
    }

    Time next_frame_time = milliseconds(0);
    Time time_between_frames = milliseconds(*argv[2]);

    Time time_to_first_frame;
    Time time_to_last_frame;

    unsigned current_frame = 0;
    unsigned displayed_frames = 0;

    RenderWindow window(VideoMode(width, height), "Artifex");

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

            if ((current_frame + 1) == number_of_frames) {
                current_frame = 0;
            } else {
                current_frame += 1;
            }

            next_frame_time += time_between_frames;
            displayed_frames += 1;

            if (displayed_frames == 1) {
                time_to_first_frame = clock.getElapsedTime();
            } else if (displayed_frames == number_of_frames) {
                time_to_last_frame = clock.getElapsedTime();

                cout << "Score = " << calculateScore(
                    time_to_first_frame, time_to_last_frame, time_between_frames, number_of_frames
                ) << endl;
            }
        }
    }

    return 0;
}
