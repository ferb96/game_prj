# Asteroid

A simple arcade-style Asteroid game written in C++ using SDL2 library.

## Overview

The game is the final project of a 3-week intensive C++ programming course. In the course, the professor gave us a graphical library designed for learners called cwin to work with. However its capabilities are quite limited and can only update the screen whenever there is user input. As a result, me and my coding partner ended up choosing SDL2, a full-fledged graphical library, to use for making our game of choice. Furthermore, SDL is commonly used and we believe it will give us neccessary skills later on.

The game uses a heavily object-oriented design. The four objects of the game (Player, Asteroid, Bullet, and Poof - an element purely for cosmetic purposes) are all inherited from the Object class, and implement their own function such as moving, drawing, and exploding. The other two objects are unique: GameState keeps track of everything in play as well as initializing the game and create new levels; and the Game class controls SDL and handles input, output and execute the main game loop.

This project would not came to be without my coding partner Jack Poblocki https://github.com/jpobloc2/

## Features

Basic game features include:

- Moving your ship around using Left and Right for turning and Up for accelerating.
- Press/Hold Space to shoot. Bullets have a limited lifetime.
- The game field is bounded and wrap-around in all edge. Meaning any objects go out to the left will appear on the right.
- Asteroid when hit by a bullet will shatter and broken into 2 smaller pieces. There are 3 levels of asteroid sizes.
- Big asteroids give 50 points, medium ones give 100 points and small ones give 150 points.
- For every 10000 points you get an extra life.
- Difficulty gets higher the longer you survive.
- When you are defeated, you have the option to replay by pressing 'R'

## Installation

If you want to play it on your machine (Linux / Mac only, sorry), you must first install `SDL2`, `SDL2_gfx` and `SDL2_ttf` dev library. For ubuntu, it's `sudo apt-get install libsdl2-dev libsdl2-gfx-dev libsdl2-ttf-dev`

- clone the repo
- cd into repo
- Make sure you installed the SDL2 library above
- `make`
- Run the game by `./asteroid`

## Screenshot

![screenshot](https://github.com/ferb96/game_prj/raw/master/screenshot.png)
