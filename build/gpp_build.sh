g++ -c ../projektpi1/main.cpp -o main.o
g++ main.o -o flanki -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
cp -rf ../projektpi1/assets ../build
./flanki