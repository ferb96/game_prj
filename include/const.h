//Mathematical Constants
const double RADIAN_CIRCLE = 2 * M_PI;
const double THIRD_OF_CIRCLE = RADIAN_CIRCLE / 3;
const double QUARTER_CIRCLE = RADIAN_CIRCLE / 4;

// Asteroids
const double ASTEROID_MAX_SPD = 2.5;
const int ASTEROID_INITIAL_RADIUS = 50;
//const int ASTEROID_SPLIT_NUMBER = 2; //not working

// Scores
const int BIG_ASTEROID_SCORE = 50;
const int MEDIUM_ASTEROID_SCORE = 100;
const int SMALL_ASTEROID_SCORE = 150;
const int SCORE_TO_GET_EXTRA_LIFE = 10000;

// Bullets
const int DELAY_BETWEEN_BULLETS = 200; 
const int BULLET_LIFESPAN = 500;
const int BULLET_RADIUS = 1;
const int BULLET_MOVE_SPEED = 15; 

// Poofs
const int POOF_LIFESPAN = 300;

// Player constants
const int PLAYER_LIVES = 3;
const int PLAYER_HIT_RADIUS = 22.0;
const double PLAYER_ACCELERATION = .08;
const double PLAYER_DECELERATION = .02;
const double PLAYER_TURN_RATE = .07;
//const int PLAYER_MOVE_SPEED = 8; //not working

// Animations
const double PLAYER_FRONT_POINT_DISTANCE = (25.0 / 22.0) * PLAYER_HIT_RADIUS;
const double PLAYER_SIDE_POINT_DISTANCE = (15.0 / 22.0) * PLAYER_HIT_RADIUS;
// The long exhaust triangle will be this proportion taller than the short one
const double EXHAUST_VARIABILITY = 1.3; 

// Spawning
const int DELAY_BETWEEN_LEVELS = 1000;
const int DELAY_BETWEEN_RESPAWNS = 1000;
const int INVULNERABLE_DURATION = 4000;
// Minimum distance a spawning asteroid must be from the player at level start
const double SAFETY_ZONE = 175;

// Window constants
const int WINDOW_SIZE_X = 800;
const int WINDOW_SIZE_Y = 600;

// Text
const int LEVEL_TEXT_DISTANCE_FROM_TOP = 50;
const int LIVES_TEXT_DISTANCE_FROM_TOP = 70;
const int POINTS_TEXT_DISTANCE_FROM_TOP = 90;
const int NORMAL_FONT_SIZE = 12;
const int LIVES_FONT_SIZE = 15;

// Frame Delay
const int FRAME_RATE_DELAY = 17; // The gmae will play at 60 fps if this is set to 17
