# FightR 2
FightR is a cross-platform 2D platform game written in C++11, using SFML for graphics rendering. The original game was written for Windows in 2007, link and comparison will be available later. To distinguish, this is version 2.

## How to compile and run
On Ubuntu, be sure to install SFML by `sudo apt-get install libsfml-dev`. Then, it's as simple as cloning this repo, step in the `src` directory, run `make`, then run the `a.out` file.

Instructions for Windows and OS X will follow later when things are working.

## Roadmap

### Version 0.1 (ALPHA)
- [ ] Implement two test weapons and projectiles
- [x] Handle fire of weapon
- [x] Handle weapon switching
- [ ] Projectile-Character collision detection
- [ ] Projectile-Wall collision detection
- [x] Rendering of projectiles
- [ ] Only halt character when reaching left or right edge
- [ ] Implement ladders
- [x] Jump only if standing solidly

### Version 0.2 (FIRST BETA)
- [ ] Remove all frame-invariant hard-coded values
- [ ] Smooth movement and jumping
- [ ] Load levels from file
- [ ] Rendering of weapons
- [ ] Implement test powerups
- [ ] Game logic (stop when a team has won)
- [ ] Basic rendering of player stats
- [ ] Basic AI
- [ ] Implement ladders and climbing
- [ ] Render basic graphic effects
- [ ] Better level randomization

### Version 0.3 (SECOND BETA)
- [ ] General bug fixes, clean memory leaks
- [ ] Improved AI
- [ ] Basic UI for starting, restarting, ending a game
- [ ] Improved in-game UI (better player stats rendering)
- [ ] Document running on Windows and OS X
- [ ] Write good levels
- [ ] More weapons and projectiles
- [ ] More powerups
- [ ] More effects
- [ ] Animated character(s)
- [ ] Clean up and document code
- [ ] Optimize for efficiency
