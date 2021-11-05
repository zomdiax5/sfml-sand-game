#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <thread>
#include <vector>
#define map_length_x 160
#define map_length_y 90
int map[map_length_x][map_length_y];
int tmap[map_length_x][map_length_y];
int selected_id = 1;
sf::Color colors[3] = {sf::Color(0, 0, 0), sf::Color(255, 200, 0), sf::Color(50, 50, 255)};
sf::VertexArray pixel(sf::Quads, (map_length_x*map_length_y)*4);

int random(int min, int max) //range : [min, max]
{
    static bool first = true;
    if (first)
    {
        srand(time(NULL)); //seeding for the first time only!
        first = false;
    }
    return min + rand() % ((max + 1) - min);
}
void process(float start_x, float end_x, float start_y, float end_y)
{
    for (int x = map_length_x * start_x; x < map_length_x * end_x; x++)
    {
        for (int y = map_length_y * start_y; y < map_length_y * end_y; y++)
        {
            //tmap[x][y] = map[x][y];
            int right = x + 1;
            if (right > map_length_x-1)
            {
                right = map_length_x - 2;
            }
            int left = x - 1;
            if (left < 0)
            {
                left = 0;
            }
            int down = y + 1;
            if (down > map_length_y - 1)
            {
                down = map_length_y - 1;
            }
            int up = y - 1;
            if (up < 2)
            {
                up = 2;
            }
            if (map[x][y] == 0)
            {
                // Nothing
            }
            else if (map[x][y] == 1) //Sand
            {
                if (map[x][down] == 0 || map[x][down] == 1 || map[x][down] == 2)
                {
                    int temp = tmap[x][down];
                    tmap[x][down] = 1;
                    tmap[x][y] = temp;
                }
                if (random(0, 1) && map[x][down] != 0 && y < map_length_y - 1)
                {
                    if (map[right][down] == 0)
                    {
                        int temp = tmap[right][down];
                        tmap[right][down] = 1;
                        tmap[x][y] = temp;
                    }
                    else if (map[left][down] == 0)
                    {
                        int temp = tmap[left][down];
                        tmap[left][down] = 1;
                        tmap[x][y] = temp;
                    }
                }
            }
            else if (map[x][y] == 2) //water
            {
                if (map[x][down] == 0)
                {
                    int temp = tmap[x][down];
                    tmap[x][down] = 2;
                    tmap[x][y] = temp;
                }
                if (map[x][down]!=0)
                {
                    if (random(0, 1))
                    {
                        if (map[right][y] == 0)
                        {
                            int temp = tmap[right][y];
                            tmap[right][y] = 2;
                            tmap[x][y] = temp;
                        }
                    }
                    else
                    {
                        if (map[left][y] == 0)
                        {
                            int temp = tmap[left][y];
                            tmap[left][y] = 2;
                            tmap[x][y] = temp;
                        }
                    }
                }
                
            }
        }
    }
}
std::vector<float> recent_fps;
int main()
{
    sf::Clock clock;
    for (int i = 0; i < 20; i++)
    {
        recent_fps.push_back(0);
    }
    sf::RenderWindow window(sf::VideoMode(map_length_x, map_length_y), "Sand Game");
    //window.setVerticalSyncEnabled(false);
    window.setFramerateLimit(9999);
    for (int x = 0; x < map_length_x; x++)
    {
        for (int y = 0; y < map_length_y; y++)
        {
            map[x][y] = 0;
            tmap[x][y] = 0;
            pixel[((x+(y*map_length_x))*4)-1].position=sf::Vector2f(x,y);
            pixel[((x+(y*map_length_x))*4)-2].position=sf::Vector2f(x+1,y);
            pixel[((x+(y*map_length_x))*4)-3].position=sf::Vector2f(x+1,y+1);
            pixel[((x+(y*map_length_x))*4)-4].position=sf::Vector2f(x,y+1);
        }
    }
    sf::Time main_start;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // Input
        sf::Time t_input_start = clock.getElapsedTime();
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            int x = sf::Mouse::getPosition(window).x * (float(map_length_x) / float(window.getSize().x));
            int y = sf::Mouse::getPosition(window).y * (float(map_length_y) / float(window.getSize().y));
            if (x < 1)
            {
                x = 1;
            }
            if (y < 1)
            {
                y = 1;
            }
            if (x > map_length_x - 1)
            {
                x = map_length_x - 1;
            }
            if (y > map_length_y - 1)
            {
                y = map_length_y - 1;
            }

            tmap[x][y] = selected_id;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
        {
            selected_id = 1;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
        {
            selected_id = 2;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0))
        {
            selected_id = 0;
        }
        sf::Time t_input_end = clock.getElapsedTime();
        window.clear();
        // Updating Colors
        sf::Time t_color_start = clock.getElapsedTime();
        for (int x = 0; x < map_length_x; x++)
        {
            for (int y = 0; y < map_length_y; y++)
            {
                map[x][y] = tmap[x][y];
                pixel[((x+(y*map_length_x))*4)-1].color=colors[map[x][y]];
                pixel[((x+(y*map_length_x))*4)-2].color=colors[map[x][y]];
                pixel[((x+(y*map_length_x))*4)-3].color=colors[map[x][y]];
                pixel[((x+(y*map_length_x))*4)-4].color=colors[map[x][y]];
            }
        }
        sf::Time t_color_end = clock.getElapsedTime();
        sf::Time t_draw_start = clock.getElapsedTime();
        window.draw(pixel);
        std::thread thread1(process, 0.0, 1.0, 0.0, 0.5);
        std::thread thread2(process, 0.0, 1.0, 0.5, 1.0);
        thread1.join();
        thread2.join();
        //process(0.0, 1.0, 0.0, 1.0);

        window.display();
        sf::Time t_draw_end = clock.getElapsedTime();
        sf::Time main_end = clock.getElapsedTime();
        float fps = 1.0f / (main_end.asSeconds() - main_start.asSeconds());
        recent_fps.push_back(fps);
        recent_fps.erase(recent_fps.begin());
        main_start = main_end;
        float sum = 0.0;
        for(auto value : recent_fps)
        {
            sum+=value;
        }
        std::cout << "FPS: " << sum/recent_fps.size() << std::endl;
    }

    return 0;
}