# Blehmeh98's Allegro Asteroids
A clone of the game Asteroids, written in C with the Allegro development library

# Dependencies
This project requires math.c (which comes with common distributions of C, but still requires a seperate compiler flag to include, -lm), and requires [Allegro](http://www.liballeg.org), a free library for developing 2d games in C.

# Compilation
On linux, with GCC and Allegro 5 installed, I ran `gcc main.c -lm -lallegro -lallegro_primitives -lallegro_audio -lallegro_acodec -lallegro_font -lallegro_ttf -oAsteroids`.
If you're compiling this on Mac with GCC and Allegro 5 installed via Brew, add a `-lallegro_main` in there somewhere.
I have no clue how any of this would work on Windows, although Allegro does support Windows, so you can try.

# Featuring:
- Neato graphixz, with a pretty particle system
- Loud noises to get your attention
- Hours of asteroid-blasting fun
- No mouse required
- No mouse supported
- Intense rage as you die to that same super small 9000 mile per hour asteroid again and again
- Minimal memory and CPU usage; it'll run fine on any old computer
- Source: I developed this on a 2007 Macbook. It ran smooth even when I had a browser and Atom open, and I only have 1 or 2 gigs of RAM.
- It'll probably run on a raspberry Pi
- I now spend too much time playing this game
- Please help

# What's Next
- I might add a seperate explosion sound effect for when the player blows up as opposed to when the asteroids blow up. That way you can hear it's you exploding and not an asteroid.
- I might add a highscore system where it stores high scores in a text file.
