# game_prj

	As a game, Asteroids shares territory with Tetris for being a program tha updates and animates continuously, 
	independent from user input. If you stand still, an asteroid is liable to knock you out of space. For this reason 
	(among others), we deemed that the cwin program provided in-class was insufficient to properly construct it.

	We had reason to think that SDL would provide us with the functionality we required at a difficulty manageable in 
	the time provided. Furthermore, SDL is common, and we believed we may be leaving class with skills we would find 
	useful later in life. We used an online tutorial from Lazy Foo' Productions (found at this address: http://lazyfoo
	.net/tutorials/SDL/index.php) to learn the basics of SDL functionality. For the functions that draw basic shapes in the window, we used the extension library SDL_gfx; for text, we used SDL_ttf. 

	A heavily object-oriented design fit the challenges of programming this game well. There are four types of 
	objects apparent on-screen: Player, Asteroid, Bullet, and Poof. Player, Asteroid and Bullet inherit from the 
	invisible Object class, while Poof inherits from Bullet. Object contains data members and functions common to 
	some or all of the visible classes, such as x/y coordinates, trajectory, x/y velocity, and a function that checks 
	collision with another object. Every Object inheritor has a drawSelf() function, which draws the desired shape 
	relative to that object's position and (in the case of Player) trajectory. An asteroid can be one of four 
	different shapes, a random data member generated in its constructor. A Player is an isosceles triangle with a 
	line running from the long point to the midpoint of the base, and an exhaust triangle that animates if the player 
	is moving. The bullet is a circle with a radius of one pixel and a Poof is always just a single pixel. "Poof" is 
	a simple class that represents a single pixel with a velocity and trajectory which expires after a set amount of 
	time (like a bullet) but does not collide with anything (not like a bullet). It is used to create the particle 
	bursts that fan out after an Asteroid or Player is destroyed.

	The GameState object is essentially a registry of vectors with matching accessors and mutators to keep track of 
	every object in the game. It has a couple useful functions of its own as well; the GameState is responsible for 
	initializing the level (with the initLevel() function) by creating a host of new asteroids with random parameters.
	GameState also manages asteroid splitting; when an Asteroid collides with a bullet, the asteroid is deleted from 
	the game's vector, deallocated, and replaced by two new asteroids of a greater level with speeds and tajectories 
	loosely based on that of the original (handled by the splitAsteroid() function).

	Virtually everything else is handled by the Game class. Game holds a number of data members necessary for 
	operating SDL, keeping track of player actions and handling global variables like score and lives. Game's 
	runGame() function either directly or vicariously calls all necessary member functions needed to run the program. 
	runGame() calls gameLoop(), a function that repeats indefinitely until the program is closed and calls 
	processInput(), checkCollisions(), moveObjects() and renderObjects() to move and animate every object held in the
	GameState. When gameLoop() ends, runGame() calls scoreBoard(), which creates the endgame screen that waits for
	the player's input to reset the GameState and play again. 
