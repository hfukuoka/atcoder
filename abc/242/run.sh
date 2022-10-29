g++ $1.cpp -o $1 -std=c++17 -I /usr/local/include
cat input.txt | ./$1
