# Spider

To run/build Main.cpp `g++ -c Main.cpp -o main.o`

Then compile `main.o` with flags `-lsfml-graphics -lsfml-window -lsfml-system`

i.e. `g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system`

Then run `./sfml-app`

## Easy way

Use this single command
`g++ -c Main.cpp -o main.o && g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system && ./sfml-app`