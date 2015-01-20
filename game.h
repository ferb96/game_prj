Class Game
{
public:
	Game(int winSizeX, int WinSizeY);
	bool init();
	void runGame(); 
private:
	//declare vector of asteroids here (not sure how to works with pointers yet so just leave it here)
	//declare vector of bullets here
	//declare player object here
	SDL_Window* window;
	SDL_Renderer* renderer;

	//init functions
	bool InitSDL();
	bool createWindow();
	bool createRenderer();
	bool setup Renderer();

	//processing functions
	void processInput();
	void moveObjects();
	void renderObjects();
	void close();
}