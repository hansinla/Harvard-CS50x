/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements the Game of Fifteen (generalized to d x d).
 *
 * Usage: ./fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [MIN,MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// board's minimal dimension
#define MIN 3

// board's maximal dimension
#define MAX 9

// board, whereby board[i][j] represents row i and column j
int board[MAX][MAX];
int checkVal[MAX][MAX];

// board's dimension
int dim;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);
void save(void);
void drawHeader(void);

int main(int argc, string argv[])
{
    // greet player
    greet();

    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    dim = atoi(argv[1]);
    if (dim < MIN || dim > MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            MIN, MIN, MAX, MAX);
        return 2;
    }

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // saves the current state of the board (for testing)
        save();

        // check for win
        if (won())
        {
            printf("ftw!\n");
            return 0;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep for animation's sake
        usleep(500000);
    }

    // that's all folks
    return 1;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1,
 * (i.e., fills board with values but does not actually print them),
 * whereby board[i][j] represents row i and column j.
 */
void init(void)
{
    int startVal = dim * dim - 1;
    int fillVal = startVal;
    int val = 1;
    
    // Build game board and check matrix
    for (int i = 0 ; i < dim ; i++)
    {
        for (int j = 0 ; j < dim ; j++)
        {
            board[i][j] = fillVal;
            fillVal--;
            checkVal[i][j] = val;
            val++;
        }
    }
    // If startVal is odd, swap 1 and 2 tiles
    if (startVal % 2 != 0)
    {
        board[dim - 1][dim - 3] = 1;
        board[dim - 1][dim - 2] = 2;
    }
    // Make last position in checkVal zero
    checkVal[dim - 1][dim - 1] = 0;
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    drawHeader();
    for (int i = 0 ; i < dim ; i++)
    {
        printf("+\t");
        for (int j = 0 ; j < dim ; j++)
        {
            if (board[i][j] != 0)
            {
                printf("%2d\t",board[i][j]);
            }
            else
            {
                printf("  \t");
            }
        }
        printf("\n");
    }
    drawHeader();
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    
    // Iterate over matrix to find tile
    for(int i = 0 ; i < dim ; i++)
    {
        for(int j = 0 ; j < dim ; j++)
        {
            if (board[i][j] == tile)
            {
                // tile found, now check for empty space
                // making sure we don't get out of bound error
                if (i - 1 >= 0)
                {
                    if (board[i - 1][j] == 0)
                    {
                        // Succesful, now swap and exit
                        board[i - 1][j] = tile;
                        board[i][j] = 0;
                        return true;
                    }
                }
                
                if (j - 1 >= 0)
                {
                    if (board[i][j - 1] == 0)
                    {
                        // Succesful, now swap and exit
                        board[i][j - 1] = tile;
                        board[i][j] = 0;
                        return true;
                    }
                }
               
                if (i + 1 <= dim - 1)
                {
                    if (board[i + 1][j] == 0)
                    {
                        // Succesful, now swap and exit
                        board[i + 1][j] = tile;
                        board[i][j] = 0;
                        return true;
                    }
                }
               
                if (j + 1 <= dim - 1)
                {
                    if (board[i][j + 1] == 0)
                    {
                        // Succesful, now swap and exit
                        board[i][j + 1] = tile;
                        board[i][j] = 0;
                        return true;
                    }
                }
                
            }
        }
    }   
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    bool isWon = true;
    // Check board against solution matrix
    for(int i = 0 ; i < dim ; i++)
    {
        for(int j = 0 ; j < dim ; j++)
        {
            if (board[i][j] != checkVal[i][j])
            {
                isWon = false;
            }
        }
    }
    return isWon;
}

/**
 * Saves the current state of the board to disk (for testing).
 */
void save(void)
{
    // log
    const string log = "log.txt";

    // delete existing log, if any, before first save
    static bool saved = false;
    if (!saved)
    {
        unlink(log);
        saved = true;
    }

    // open log
    FILE* p = fopen(log, "a");
    if (p == NULL)
    {
        return;
    }

    // log board
    fprintf(p, "{");
    for (int i = 0; i < dim; i++)
    {
        fprintf(p, "{");
        for (int j = 0; j < dim; j++)
        {
            fprintf(p, "%i", board[i][j]);
            if (j < dim - 1)
            {
                fprintf(p, ",");
            }
        }
        fprintf(p, "}");
        if (i < dim - 1)
        {
            fprintf(p, ",");
        }
    }
    fprintf(p, "}\n");

    // close log
    fclose(p);
}

void drawHeader(void)
{
    for(int i = 0 ; i < dim ; i++)
    {
        printf("++++++++++");
    }
    printf("\n");
}
