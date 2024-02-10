
# So Long Network

So Long Network is a multiplayer game inspired by the project "so_long" from School 42, with a twist of multiplayer functionality and a different graphics library. In So Long Network, players navigate through a maze-like environment filled with obstacles, collectibles, and enemies while competing against each other to reach the end goal.

It's a work in progress, with a lot to do and bugs to fix.

Thanks to https://pipoya.itch.io/ and http://rogames.com.ua/ for the images used.


## Installation

dependencies: libsfml-dev

```bash
  sudo apt-get install libsfml-dev

  and then just run make inside the project folder.
```
    
## Usage/Examples

```bash
Server:
./so_long -s [PORT]

Client:
./so_long -c [IP] [PORT]

./so_long -s 3001
./so_long -c 127.0.0.1 3001
```

