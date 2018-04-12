# Tic-tac-toe console game

This is an unbeatable tic-tac-toe console game written in C++.

## Motivation

I made this game program just as an exercise to learn C++.


## The game

Tic-tac-toe is a two players' game with a game board of 9 cells in a 3x3 grid.
A player puts his/her symbol 'X' or 'O' to a free cell on his/her turn.
The player who gets three symbols in vertical, horizontal or diagonal line wins the game.
Otherwise if all cells are played and neither got the winning line, the game is draw.
The game is pretty simple to learn and play, and if the both players make their moves
optimally, the game ends to a draw.

## Getting Started

Clone the Tic-tac-toe repository, compile, and run the game executable on your Linux computer.

### Prerequisites

c++11 support required in g++ compiler.

Tested in Linux Ubuntu 16.04 with g++ 5.4.0.


### Installing

Open your Linux terminal and clone the game repository:
```
git clone https://github.com/pt1k/Tic-tac-toe.git
```

Move to the game directory:
```
cd Tic-tac-toe
```
Compile to produce executable:
```
make
```

## Starting the game

Start the compiled executable:
```
./ttt
```

Then the program asks for the both players their name and whether the player is a human or a machine.
Therefore, there are the following options for the players: two humans plays against each other, a human plays against the computer or the computer plays against itself.

The first player gets symbol 'X' and starts the first game. The latter player gets symbol 'O'.
Subsequent games are started alternately, i.e. by 'O', 'X', 'O', ..

The game can be quit at any stage by pressing <ctrl-C>.

### Playing the game

A player is asked to make his/her move by entering the cell number 1-9 for the move.
By entering 0 (zero) the current game quits and next players are asked.

## TODOs and Further Development 

Here listed some ideas for further development:

  - there are similar functionality in rules.cc and computermove.cc; these should be generalized
  - currently the computerplay is unbeatable; it ends up always on computer win or draw.
    It would be more interesting to play if a human could sometimes win the computer.
    For example, that a player can give some factor of difficulty of the game so the 
    computerplay looks ahead only given amount of moves. As currently it always looks ahead till the 
    end of the game
  - user interface could be more sophisticated, it shouldn't be too challenging to implement e.g. by ncurses


## Author

* **Pekka Koivuniemi**

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details

