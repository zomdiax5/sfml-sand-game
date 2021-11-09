g++ -ggdb3 -I . -I ./profiler *.cpp profiler/*.cpp -std=c++17 -pthread -lstdc++ -lsfml-graphics -lsfml-window -lsfml-system -Wall -o SandGame.86_64
echo "\n Tutaj będzie output programu: \n\n"
./SandGame.86_64
echo "\n\n\n To okno zniknie za 0s...\n"
