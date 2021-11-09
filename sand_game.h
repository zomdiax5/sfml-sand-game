#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <random>
#include <thread>
#include <vector>
#include <string>
#include "profiler/profiler.h"
#define dmap_length_x 160 * 1
#define dmap_length_y 90 * 1
class SandGame
{
private:
    int map_length_x = dmap_length_x;
    int map_length_y = dmap_length_y;
    int map[dmap_length_x][dmap_length_y];
    int tmap[dmap_length_x][dmap_length_y];
    int changed[dmap_length_x][dmap_length_y];
    int selected_id = 1;
    sf::Color colors[5] = {sf::Color(0, 0, 0), sf::Color(255, 200, 0), sf::Color(50, 50, 255), sf::Color(94, 66, 44), sf::Color(255,15,15)};
    sf::VertexArray pixel;
    int random(int min, int max);
    void process(float start_x, float end_x, float start_y, float end_y);
    std::vector<float> recent_fps;
    float fps = 0.0;
    Profiler prof;
    sf::Clock clock;
    sf::Time main_start;
public:
    SandGame(/* args */);
    ~SandGame();
    void run(bool limit_fps);
};
