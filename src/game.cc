#include "game.h"
#include "gameState.h"
#include "const.h"
#include "poof.h"
#include <SDL2/SDL.h>
#include "SDL2/SDL2_gfxPrimitives.h"
#include "SDL2/SDL_ttf.h"
#include <sstream>
#include <iostream>
#include <string>
using namespace std;

/*
 * Implementing the functions in the Game class
 */
bool Game::runGame(GameState& thegamestate){
	gamemgr = thegamestate;
	gamemgr.resetGameState();
	gamemgr.initLevel();
	if (!gameLoop())
		return false;
	bool playAgain = scoreBoard();
	return playAgain;
}

bool Game::gameLoop(){
	bool loop = true;
	while (loop){
		if ( !checkLevel() )
			loop = false;
		if ( !getInput() ){
			loop = false;
			return false;
		}
		processInput();
		checkCollisions();
		moveObjects();
		renderObjects();
		frame++;
		SDL_Delay(FRAME_RATE_DELAY);
	}
	return true;
}

bool Game::checkLevel(){
	bool gameOver = false;

	// Handling player respawn
	Player* lePlayer = gamemgr.getPlayer();

	if ( lePlayer->isAlive() ){
		if ( lePlayer->isInvul() && SDL_GetTicks() - lastDeath >= INVULNERABLE_DURATION )
			lePlayer->setInvul(false);
		if ( !lePlayer->isInvul() )
			lastDeath = SDL_GetTicks();
	}
	if ( !lePlayer->isAlive() ){
		if ( lePlayer-> getLivesLeft() == 0 )
			gameOver = true;
		if ( lePlayer-> getLivesLeft() > 0 )
			if ( SDL_GetTicks() - lastDeath >= DELAY_BETWEEN_RESPAWNS ){
				lePlayer->setAlive(true);
				lePlayer->setInvul(true);
				lePlayer->resetPlayer(WINDOW_SIZE_X, WINDOW_SIZE_Y);
			}
	}

	// Handling new levels
	if (gamemgr.zeroAsteroid()){
		if (SDL_GetTicks() - lastLevelClear >= DELAY_BETWEEN_LEVELS)
			gamemgr.initLevel();
	}
	else
		lastLevelClear = SDL_GetTicks();

	return (!gameOver);
}

void Game::checkCollisions(){
	Player* lePlayer = gamemgr.getPlayer();
	gamemgr.resetIteRoid();
	while ( !gamemgr.noMoreAsteroid() ){
		Asteroid* roid = gamemgr.getAsteroid();
		//check for collision between player and roid
		if ( roid != NULL && lePlayer->checkCollision(roid) && lePlayer->isAlive() && !lePlayer->isInvul()){
			gamemgr.addPoofs(lePlayer->goBoom());
			lePlayer->setAlive(false);
			lePlayer->minusOneLife();
			gamemgr.addScore(roid->getLevel());
			gamemgr.splitAsteroid(roid);
		}
		gamemgr.resetIteBullet();
		while ( !gamemgr.noMoreBullet() ){
			Bullet* bull = gamemgr.getBullet();
			//check for collision between roid and bull
			if ( roid != NULL && bull != NULL && roid->checkCollision(bull) ){
				gamemgr.addPoofs(roid->goBoom());
				gamemgr.addScore(roid->getLevel());
				gamemgr.splitAsteroid(roid);
				gamemgr.delBullet();
				gamemgr.destroyBull(bull);
			}
		}
	}
}

void Game::moveObjects(){
	Player* lePlayer = gamemgr.getPlayer();
	lePlayer->updatePosition(WINDOW_SIZE_X, WINDOW_SIZE_Y);
	gamemgr.resetIteRoid();
	while ( !gamemgr.noMoreAsteroid() ){
		Asteroid* roid = gamemgr.getAsteroid();
		roid->updatePosition(WINDOW_SIZE_X, WINDOW_SIZE_Y);
	}
	gamemgr.resetIteBullet();
	while ( !gamemgr.noMoreBullet() ){
		Bullet* bull = gamemgr.getBullet();
		bull->updatePosition(WINDOW_SIZE_X, WINDOW_SIZE_Y);
		//check for bullet expiration
		if ( bull->isExpired() ){
			gamemgr.delBullet();
			gamemgr.destroyBull(bull);
		}
	}
	gamemgr.resetItePoof();
	while ( !gamemgr.noMorePoof() ){
		Poof* puff = gamemgr.getPoof();
		puff->updatePosition(WINDOW_SIZE_X, WINDOW_SIZE_Y);
		//check for bullet expiration
		if ( puff->isExpired() ){
			gamemgr.delPoof();
			gamemgr.destroyPoof(puff);
		}
	}
}

void Game::processInput(){
	Player* lePlayer = gamemgr.getPlayer();
	if (lePlayer->isAlive()){
		if (playerAction[MOVING_UP])
			lePlayer->setAccel(PLAYER_ACCELERATION);
		if (!playerAction[MOVING_UP])
			lePlayer->setAccel(0);
		if (playerAction[MOVING_RIGHT])
			lePlayer->changeTrajectory(PLAYER_TURN_RATE);
		if (playerAction[MOVING_LEFT])
			lePlayer->changeTrajectory(-PLAYER_TURN_RATE);
		if (playerAction[SHOOTING])
			if (SDL_GetTicks() - lastShot > DELAY_BETWEEN_BULLETS){
				lastShot = SDL_GetTicks();
				gamemgr.addBullet(lePlayer->shoot(BULLET_MOVE_SPEED, BULLET_LIFESPAN));
			}
		if (!playerAction[SHOOTING])
			lastShot = 0;
	}
}

void Game::renderObjects(){
	Player* lePlayer = gamemgr.getPlayer();
	
	// Change color of background
	SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0x00, 255 );

	// First we clear the window with that background color
	SDL_RenderClear( renderer );

	// Color of every other objects
	SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 255 );

	// Level text
	string lvl = static_cast<ostringstream*>( &(ostringstream() << gamemgr.getLevel()) )->str();
	lvl = "Level " + lvl;
	renderText(lvl, WINDOW_SIZE_X / 2, LEVEL_TEXT_DISTANCE_FROM_TOP, font);
	
	// Lives text
	if (lePlayer->getLivesLeft() > 0){
		string lives = "";
		for (int i = 0; i < lePlayer->getLivesLeft(); i++)
			lives += "♥";
		renderText(lives, WINDOW_SIZE_X / 2, LIVES_TEXT_DISTANCE_FROM_TOP, symbolfont);
	}
	else{
		string gameOverText = "!!! GAME OVER !!!";
		renderText(gameOverText, WINDOW_SIZE_X /2, LIVES_TEXT_DISTANCE_FROM_TOP, font);
		string replayText = "Press r to play again!";
		renderText(replayText, WINDOW_SIZE_X /2, WINDOW_SIZE_Y /2, font);
	}

	// Score text
	string scoreText = static_cast<ostringstream*>( &(ostringstream() << gamemgr.getScore()) )->str();
	renderText(scoreText, WINDOW_SIZE_X /2, POINTS_TEXT_DISTANCE_FROM_TOP, font);

	// Render the player
	if (lePlayer->isAlive()) {
		if (!lePlayer->isInvul())
			lePlayer->drawSelf( renderer );
		else if (frame % 2 == 0) 
			lePlayer->drawSelf( renderer );
	}

	//Render the Asteroids
	gamemgr.resetIteRoid();
	while ( !gamemgr.noMoreAsteroid() ){
		Asteroid* roid = gamemgr.getAsteroid();
		roid->drawSelf(renderer);
	}

	//Render the Bullets
	gamemgr.resetIteBullet();
	while ( !gamemgr.noMoreBullet() ){
		Bullet* bull = gamemgr.getBullet();
		bull->drawSelf(renderer);
	}

	//Render the Poofs
	gamemgr.resetItePoof();
	while ( !gamemgr.noMorePoof() ){
		Poof* puff = gamemgr.getPoof();
		puff->drawSelf(renderer);
	}
 
	// Render the changes above to the window
	SDL_RenderPresent( renderer );
}

void Game::renderText(string text, double x, double y, TTF_Font *font){
	SDL_Color textColor = { 0xFF, 0xFF, 0xFF };
	SDL_Color bgColor = { 0x00, 0x00, 0x00 };
	SDL_Surface* textSurface = TTF_RenderUTF8_Shaded( font, text.c_str(), textColor, bgColor );
	if( textSurface == NULL )
	{
		cout << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << endl;
	}
	else
	{
		//Create texture from surface pixels
        texture = SDL_CreateTextureFromSurface( renderer, textSurface );
		if( texture == NULL )
		{
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			int xx = x - textSurface->w / 2;
			int yy = y - textSurface->h / 2;
			// The surface we are rendering to
			SDL_Rect renderQuad = { xx, yy, textSurface->w, textSurface->h };

			// Render to screen
			SDL_RenderCopy( renderer, texture, NULL, &renderQuad );
		}

		//Get rid of old surface
		SDL_FreeSurface( textSurface );
		textSurface = NULL;
	}
}

Game::Game(){
	window = NULL;
	renderer = NULL;
	texture = NULL;
	for (int i = 0; i < TOTAL; i++)
		playerAction[i] = false;
	frame = 0;
	lastShot = 0;
	lastDeath = 0;
	lastLevelClear = 0;
	respawnDelay = false;
	levelDelay = false;
}

bool Game::init(){
	// Init the SDL and everything
	if ( !initSDL() )
		return false;
 
 	// Create a window
	if ( !createWindow() )
		return false;
 
 	// Create the renderer
	if ( !createRenderer() )
		return false;
 	
 	// Setup the renderer
	setupRenderer();

	return true;
}

bool Game::initSDL()
{
	if ( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
	{
		std::cout << " Failed to initialize SDL : " << SDL_GetError() << std::endl;
		return false;
	}
	if( TTF_Init() == -1 )
	{
		std::cout << " Failed to initialize SDL_ttf! SDL_ttf Error: " << TTF_GetError() << endl;
		return false;
	}
	font = TTF_OpenFont( "fonts/zefont.ttf", NORMAL_FONT_SIZE );
	if( font == NULL )
		{
			cout << " Failed to load font! SDL_ttf Error: " << TTF_GetError() << endl;
		return false;
	}
	symbolfont = TTF_OpenFont( "fonts/zefont2.ttf", LIVES_FONT_SIZE );
	if( font == NULL )
		{
			cout << " Failed to load font! SDL_ttf Error: " << TTF_GetError() << endl;
		return false;
	}
 
	return true;
}

bool Game::createWindow()
{
	window = SDL_CreateWindow( "Asteroids", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_SIZE_X, WINDOW_SIZE_Y, 0 );
 
	if ( window == NULL )
	{
		std::cout << "Failed to create window : " << SDL_GetError();
		return false;
	}
 
	return true;
}

bool Game::createRenderer()
{
	this->renderer = SDL_CreateRenderer( window, -1, 0 );
 
	if ( this->renderer == NULL )
	{
		std::cout << "Failed to create renderer : " << SDL_GetError();
		return false;
	}
 
	return true;
}

void Game::setupRenderer()
{
	// Set size of renderer to the same as window
	SDL_RenderSetLogicalSize( this->renderer, WINDOW_SIZE_X, WINDOW_SIZE_Y );
 
	// Set color of renderer to red
	SDL_SetRenderDrawColor( this->renderer, 0x00, 0x00, 0x00, 255 );
}

void Game::close()
{
	//Destroy Texture
	SDL_DestroyTexture( texture );
	texture = NULL;

	//Destroy Renderer
	SDL_DestroyRenderer( renderer );
	this->renderer = NULL;

	//Destroy window
	SDL_DestroyWindow( window );
	window = NULL;

	//Quit SDL subsystems
	SDL_Quit();

	return;
}

bool Game::getInput(){
	bool notQuitted = true;
	SDL_Event event;
	while ( SDL_PollEvent( &event ) ) {
		switch( event.type ) {
			case SDL_QUIT:
				notQuitted = false;
				break;

			case SDL_KEYDOWN:
				switch( event.key.keysym.sym ) {
					case SDLK_RIGHT:
						playerAction[MOVING_RIGHT] = true;
						break;
					case SDLK_LEFT:
						playerAction[MOVING_LEFT] = true;
						break;
					case SDLK_DOWN:
						playerAction[MOVING_DOWN] = true;
						break;
					case SDLK_UP:
						playerAction[MOVING_UP] = true;
						break;
					case SDLK_SPACE:
						playerAction[SHOOTING] = true;
						break;
					case SDLK_r:
						playerAction[REPLAY] = true;
						break;
					default :
						break;
				}
				break;

			case SDL_KEYUP:
	            switch( event.key.keysym.sym ){
					case SDLK_RIGHT:
						playerAction[MOVING_RIGHT] = false;
						break;
					case SDLK_LEFT:
						playerAction[MOVING_LEFT] = false;
						break;
					case SDLK_DOWN:
						playerAction[MOVING_DOWN] = false;
						break;
					case SDLK_UP:
						playerAction[MOVING_UP] = false;
						break;
					case SDLK_SPACE:
						playerAction[SHOOTING] = false;
						break;
					case SDLK_r:
						playerAction[REPLAY] = false;
						break;
					default :
						break;
	    	    }
	        	break;

	        default:
		    	break;
		}
	}
	return notQuitted;
}

bool Game::scoreBoard(){
	bool loop = true;
	while (loop){
		if ( !getInput() )
			loop = false;
		if (playerAction[REPLAY]){
			loop = false;
			return true;
		}
		moveObjects();
		renderObjects();
		SDL_Delay(FRAME_RATE_DELAY);
	}
	return false;
}
