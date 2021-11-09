#include <iostream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
class Profiler
{
private:
    std::vector<std::vector<float>> values;
    std::vector<std::string> names;
    std::vector<sf::Time> times;
    sf::Clock clock;
public:
    Profiler();
    void add_profile(std::string name);
    void start_profiling(int id);
    void end_profiling(int id);
    void reset_profiling(int id);
    void show_results();
};