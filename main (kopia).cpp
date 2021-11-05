#include <SFML/Graphics.hpp>
#define map_length_x 160
#define map_length_y 90
int map[map_length_x][map_length_y];

int main()
{
    sf::RenderWindow window(sf::VideoMode(160, 90), "Sand Game");
    sf::RectangleShape pixel[map_length_x][map_length_y];
    for (int x = 0; x < map_length_x; x++)
    {
        for (int y = 0; y < map_length_y; y++)
        {
            map[x][y] = 0;
            pixel[x][y].setPosition(x, y);
            pixel[x][y].setScale(1, 1);
        }
    }

    while (window.isOpen())
    {
        window.clear();
        for (int x = 0; x < map_length_x; x++)
        {
            for (int y = 0; y < map_length_y; y++)
            {
                sf::RectangleShape shape;
                pixel[10][10] = shape;
                pixel[10][10].setFillColor(sf::Color(255,0,0));
                pixel[10][10].setOutlineColor(sf::Color(255,0,0));
                pixel[10][10].setOutlineThickness(20);
                window.draw(pixel[10][10]);
                //window.draw(pixel[x][y]);
            }
        }

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        pixel[10][10].setFillColor(sf::Color(255,0,0));
        pixel[10][10].setOutlineColor(sf::Color(255,0,0));
        pixel[10][10].setOutlineThickness(20);
        window.draw(pixel[10][10]);
        window.display();
    }

    return 0;
}
