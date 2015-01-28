
const double RADIAN_CIRCLE = 2 * M_PI;
const double THIRD_OF_CIRCLE = RADIAN_CIRCLE / 3;
const double QUARTER_CIRCLE = RADIAN_CIRCLE / 4;

const int BIG_ASTEROID_SCORE = 50;
const int MEDIUM_ASTEROID_SCORE = 100;
const int SMALL_ASTEROID_SCORE = 150;

const int WINDOW_SIZE_X = 800;
const int WINDOW_SIZE_Y = 600;
const int ASTEROID_SPLIT_NUMBER = 2; //not working
const int DELAY_BETWEEN_BULLETS = 200; 
const int BULLET_LIFESPAN = 500;
const int PLAYER_MOVE_SPEED = 8; //not working
const int PLAYER_LIVES = 3;
const double PLAYER_DECELERATION = .02;
const int BULLET_MOVE_SPEED = 15; 
const double ASTEROID_MAX_SPD = 3.0;
const int DELAY_BETWEEN_LEVELS = 1000;
const int DELAY_BETWEEN_RESPAWNS = 1000;
const int INVULNERABLE_DURATION = 4000;
const double SAFETY_ZONE = 175;
const int POOF_LIFESPAN = 300;

const int PLAYER_HIT_RADIUS = 22.0;
const double PLAYER_FRONT_POINT_DISTANCE = (25.0 / 22.0) * PLAYER_HIT_RADIUS;
const double PLAYER_SIDE_POINT_DISTANCE = (15.0 / 22.0) * PLAYER_HIT_RADIUS;
// The long exhaust triangle will be this proportion taller than the short one
const double EXHAUST_VARIABILITY = 1.3; 
const double PLAYER_ACCELERATION = .08;
const double PLAYER_TURN_RATE = .07;
const int SCORE_TO_GET_EXTRA_LIFE = 10000;

const int BULLET_RADIUS = 600;

const int LEVEL_TEXT_DISTANCE_FROM_TOP = 50;
const int LIVES_TEXT_DISTANCE_FROM_TOP = 70;
const int POINTS_TEXT_DISTANCE_FROM_TOP = 90;
const int NORMAL_FONT_SIZE = 12;
const int LIVES_FONT_SIZE = 15;

const int FRAME_RATE_DELAY = 17; // The gmae will play at 60 fps if this is set to 17
