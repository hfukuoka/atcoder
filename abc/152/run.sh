g++ $1.cpp -o $1 -std=c++17 -I /usr/local/include -I /opt/homebrew/Cellar/boost/1.80.0/include
cat input.txt | ./$1
