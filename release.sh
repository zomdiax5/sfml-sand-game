g++ -O2 -I . -I ./profiler *.cpp profiler/*.cpp -std=c++17 -pthread -lstdc++ -lsfml-graphics -lsfml-window -lsfml-system -Wall -o SandGame.x86_64
echo "Here be program output:"
./SandGame.x86_64
echo "The program exited."
