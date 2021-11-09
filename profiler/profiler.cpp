#include "profiler.h"

Profiler::Profiler()
{
}
void Profiler::add_profile(std::string name)
{
    names.push_back(name);
    int id = names.size() - 1;
    std::vector<float> dummy = {0};
    values.push_back(dummy);
    for (int i = 0; i < 25; i++)
    {
        values[id].push_back(0);
    }
    sf::Time dummy_time = clock.getElapsedTime();
    times.push_back(dummy_time);
};
void Profiler::start_profiling(int id)
{
    times[id] = clock.getElapsedTime();
};
void Profiler::end_profiling(int id)
{
    values[id].push_back(clock.getElapsedTime().asMilliseconds() - times[id].asMilliseconds());
    values[id].erase(values[id].begin());
};
void Profiler::reset_profiling(int id){
    // NOT IMPLEMENTED
};
void Profiler::show_results()
{
    for (int i = 0; i < names.size(); i++)
    {
        float sum = 0.0;
        for (int j = 0; j < values[i].size(); j++)
        {
            sum += values[i][j];
        }
        std::cout << names[i] << "(ms): " << sum/values[i].size() << std::endl;
    }
};
