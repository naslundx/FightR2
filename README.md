# FightR 2
FightR is a cross-platform 2D platform game written in C++11, using SFML for graphics rendering. The original game was written for Windows in 2007, link and comparison will be available later. To distinguish, this is version 2.

## How to compile and run
On Ubuntu, be sure to install SFML by `sudo apt-get install libsfml-dev`. Then, it's as simple as cloning this repo, step in the `src` directory, run `make`, then run the `a.out` file.

Instructions for Windows and OS X will follow later when things are working.

## Roadmap

### Version 0.1 (FIRST BETA)
- [ ] Remove all frame-invariant hard-coded values
- [ ] Implement better system for handling different types of weapons, powerups etc.
- [ ] Load levels from file
- [ ] Implement test powerups
- [ ] Basic rendering of player stats
- [ ] Improved AI
- [ ] Implement ladders and climbing
- [ ] Render basic graphic effects
- [ ] Implement basic effects
- [ ] Implement a second test weapon and projectile
- [ ] Move all relevant constants to FWorld.hpp

### Version 0.2 (SECOND BETA)
- [ ] Better level randomization
- [ ] General bug fixes, clean memory leaks
- [ ] Improved AI
- [ ] Basic UI for starting, restarting, ending a game
- [ ] Improved in-game UI
- [ ] Document running on Windows and OS X
- [ ] Write good levels
- [ ] More weapons and projectiles
- [ ] More powerups
- [ ] More effects
- [ ] Animated character(s)
- [ ] Clean up and document code
- [ ] Optimize for efficiency

### Version 1.0
- [ ] ???