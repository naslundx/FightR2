# FightR 2
FightR is a cross-platform 2D platform game written in C++11, using SFML for graphics rendering. The original game was written for Windows in 2007, link and comparison will be available later. To distinguish, this is version 2.

## How to compile and run
On Ubuntu, be sure to install SFML by `sudo apt-get install libsfml-dev`. Then, it's as simple as running this repo, step in the `src` directory, run `make`, then run the `a.out` file.

Instructions for Windows and OS X will follow later when things are working.

## Roadmap

### Version 0.01
- [x] Rendering of tiles
- [x] Rendering of characters
- [ ] Rendering of powerups
- [x] Basic character-wall collision detection
- [x] Move character left-right
- [ ] Jumping
- [x] Gravity
- [x] Correctly identify human player for movement
- [x] Call AI on AI characters
- [ ] Improve object-to-texture mapping

### Version 0.02
- [ ] Implement two test weapons and projectiles
- [ ] Remove all frame-invariant hard-coded values
- [ ] Handle fire of weapon
- [ ] Handle weapon switching
- [ ] Projectile-Character collision detection
- [ ] Projectile-Wall collision detection
- [ ] Rendering of projectiles
- [ ] Halt character when reaching left or right edge

### Version 0.03
- [ ] Rendering of weapons
- [ ] Implement test powerups
- [ ] Game logic (stop when a team has won)
- [ ] Basic rendering of player stats
- [ ] Basic AI
- [ ] Implement ladders and climbing
- [ ] Render basic graphic effects
- [ ] Better level randomization

### Version 0.1 (BETA)
- [ ] General bug fixes, clean memory leaks
- [ ] Improved AI
- [ ] Basic UI for starting, restarting, ending a game
- [ ] Improved in-game UI (better player stats rendering)
- [ ] Document running on Windows and OS X

### Version 0.2 (BETA 2)
- [ ] Write good levels
- [ ] More weapons and projectiles
- [ ] More powerups
- [ ] More effects
- [ ] Animated character(s)
- [ ] Clean up and document code
- [ ] Optimize for efficiency
