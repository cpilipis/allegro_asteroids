# Chandler's Allegro Asteroids
A clone of the game Asteroids, written in C with the Allegro development library

# Dependencies
This project requires math.c (which comes with common distributions of C, but still requires a seperate compiler flag to include, -lm), and requires [Allegro](http://www.liballeg.org), a free library for developing 2d games in C.

# Compilation
If you're on Linux or Mac and have both Allegro5 and gcc installed, run compile.sh to compile this code.
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
- Nothing, because I haven't touched any of this code in 4 years. That being said . . . 
# Potential Improvements if I were to make some
- Shorten the time to respawn. Some playtesters thought the game softlocked for a moment after the player died. 5 seconds is too long to reappear.
- Add a seperate explosion sound effect for when the player blows up as opposed to when the asteroids blow up. This should make it easier to tell apart asteroid destruction and the player's death in chaotic gameplay.
- Impose reasonable limits and tampers on an asteroid's velocity when splitting up, as well as perhaps a little bit of random direction to the new asteroid chunks.
- Or, add different asteroid types that split in different directions or even different quantities when shot. 
- Make the asteroids more interesting to look at by adding different rugged shapes.
- Add a highscore system where it stores high scores in a text file, or perhaps even a binary file to discourage user tampering.
- Distribute some kind of package of this that runs on Windows, Mac, and most major Linux distributions
