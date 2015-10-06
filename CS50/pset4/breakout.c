//
// breakout.c
//
// Computer Science 50
// Problem Set 4
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include "gevents.h"
#include "gobjects.h"
#include "gwindow.h"

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// paddle height and width in pixels
#define P_HEIGHT 10
#define P_WIDTH 50

// paddle y position
#define P_Y_POS HEIGHT-(2*P_HEIGHT)

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// ball minimum speed
#define MINIMUM_SPEED 1

// lives
#define LIVES 3

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void movePaddle(GRect paddle);
void updateScoreboard(GWindow window, GLabel label, int points);
void prompt(GWindow window, GLabel label, int lives);
GObject detectCollision(GWindow window, GOval ball);
double getSpeed();

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));
    
    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);
    
    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
    
    // initial ball speed
    double speedX, speedY;
    speedX = speedY = getSpeed();
    
    // initiate ball location parameters
    GPoint bPoint = getLocation(ball);
    
    // calculate ball boundaries
    int rightWall = WIDTH - 2 * RADIUS;
    int bottomWall = HEIGHT - RADIUS;
    
    prompt(window, label, lives);
    updateScoreboard(window, label, points);

    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        // Move paddle
        movePaddle(paddle);
        
        // Move ball
        bPoint.x += speedX;
        bPoint.y += speedY;
        setLocation(ball, bPoint.x, bPoint.y);
        if (bPoint.x < 0 || bPoint.x > rightWall)
        {
            // touched left/right wall, reverse x direction
            speedX *= -1.02;
        }
        if (bPoint.y < 0)
        {
            // touched top, reverse y direction
            speedY *= -1.02;
        }
        if (bPoint.y > bottomWall)
        {
            // Ball left through bottom wall
            // Lose a live and reset ball posand  speed
            lives--;
            if (lives > 0)
            {
                prompt(window, label, lives);
                updateScoreboard(window, label, points);
            }
            bPoint.x = WIDTH / 2 - RADIUS;
            bPoint.y = HEIGHT / 2 - RADIUS;
            speedX = speedY = getSpeed();
        }
        
        // Detect object collision
        GObject object = detectCollision(window, ball);
        if (object != NULL)
        {
            if (object == paddle)
            {
                // Reverse y direction
                speedY *= -1.02;
                
                // Play sound effect
                
            }
            else if (strcmp(getType(object), "GRect") == 0)
            {
                // Play sound effect
                removeGWindow(window, object);
                speedY *= -1.02;
                bricks--;
                points++;
                updateScoreboard(window, label, points);
            }
        }
        

        pause(5);     
    }
    
    if (lives == 0)
    {
        setLabel(label, "Game Over");
    }
    else
    {
        setLabel(label, "You Won!");
    }
    setLocation(label, (getWidth(window) - getWidth(label)) / 2,
                        (getHeight(window) - getHeight(label)) / 2);
    
    // pause before exiting
    pause(2000);

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    // Calculate brick width and height
    int gap = 5;
    int brickWidth = (WIDTH - gap - gap * COLS) / COLS;
    int brickHeight = 2 * gap;
    double posX = 0;
    double posY = 0;
    
    for(int row = 0 ; row < ROWS ; row++)
    {
        for(int col = 0 ; col < COLS ; col++)
        {
            // Draw brick    
            GRect brick = newGRect(gap + col * (gap + brickWidth) ,
                    gap + row * (gap + brickHeight), brickWidth, brickHeight);
            setFilled(brick, true);
            if (row % 2 == 0)
            {
                setColor(brick, "GRAY");
            }
            else
            {
                setColor(brick, "LIGHT_GRAY");
            }
            add(window, brick);
        }
    }
    
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    // Calculate initial pos
    double x = WIDTH / 2 - RADIUS;
    double y = HEIGHT / 2 - RADIUS;
    GOval ball = newGOval(x, y, RADIUS * 2, RADIUS * 2);
    setFilled(ball, true);
    setColor(ball, "RED");
    add(window, ball);
    
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    // Calculate initial x pos
    int P_X_POS = WIDTH / 2 - P_WIDTH / 2;
    // Draw paddle    
    GRect paddle = newGRect(P_X_POS, P_Y_POS, P_WIDTH, P_HEIGHT);
    setFilled(paddle, true);
    setColor(paddle, "BLACK");
    add(window, paddle);
    return paddle;
}

/**
* Move Paddle with cursor
*/
void movePaddle(GRect paddle)
{
    // check for mouse event
    GEvent event = getNextEvent(MOUSE_EVENT);

    // if we heard one
    if (event != NULL)
    {
        // if the event was movement
        if (getEventType(event) == MOUSE_MOVED)
        {
            // ensure paddle follows cursor
            double x = getX(event) - P_WIDTH / 2;
            if (x < 0 )
            {
                x = 0;
            }
            if (x > WIDTH - P_WIDTH)
            {
                x = WIDTH - P_WIDTH;
            }
            setLocation(paddle, x, P_Y_POS);
        }
    }
}


/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    char prompt[12];
    sprintf(prompt, "%i", 0);
    GLabel label = newGLabel(prompt);
    setColor(label, "LIGHT_GRAY");
    setFont(label, "SansSerif-48");
    setLocation(label, (getWidth(window) - getWidth(label)) / 2,
                        (getHeight(window) - getHeight(label)) / 2);
    add(window, label);
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char prompt[12];
    sprintf(prompt, "%i", points);
    setLabel(label, prompt);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}

void prompt(GWindow window, GLabel label, int lives)
{
    // Prompt user
    char prompt[12];
    sprintf(prompt, "%d lives left", lives);
    setLabel(label,prompt);
    setLocation(label, (getWidth(window) - getWidth(label)) / 2,
                        (getHeight(window) - getHeight(label)) / 2);
    pause(2000);
}

double getSpeed()
{
    double speed;
    do
    {
        speed = 2 * drand48();
    }
    while (speed < MINIMUM_SPEED);
    
    return speed;
}
