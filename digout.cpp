#include <iostream>
#include <conio.h>
#include <ctime> // to generate random numbers
using namespace std;
// Orginal Map
const int row = 5, col = 10;
int sizerow = row;
int sizecol = col;
char gameMap[row][col] =
    {
        {'!', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '@', '#', '#', '#', '+', '#', '#'},
        {'#', '@', '#', '#', '#', '#', '$', '#', '&', '#'},
        {'@', '#', '#', '#', '#', '@', '#', '#', '&', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '+', '#'},
};
char mapList[5] = {'#', '@', '$', '+', '&'};

// Player Position
int xpos = 0;
int ypos = 0;
// number block and life
int BlockLevel = 4;
static int life = 2;

// number Bomb
int Bomb = 2;
bool boom = false;
// number Plus
int Plus = 1;
bool EatPuls = false;
// number $
static int score = 0;
// exit
bool isExit = false;
int WannaPlayAgain = 0;
bool isWinTheGame = false;
// this function is we need

void SearchForBomb();
void SearchForPuls();
void SearchForBlockGravity();
void SearchForDolarGravity();
void GenerateRandomMap();
bool IsMapGoodToPlay();
void ShowGameMap();

// menu function
void showmenu();
char input();
char cin_function();
void menu();
void StartGame();
void Settings();
void Records();
void Exit();
//----------
void UpdateGame(char action);
bool Movements(int x, int y, int xDir, int yDir);
void BreakDir(int x, int y, int xDir, int yDir);

int main()
{
    // Generating random Numbers.
    srand(time(NULL));
    // Show Menu

    showmenu();
    if (isExit)
    {
        return EXIT_SUCCESS;
    }
// Play Again
PlayAgain:
    // Generate Random Map and Check The Map Again.
    do
    {
        GenerateRandomMap();

    } while (!IsMapGoodToPlay());

    // Show Game Map.
    ShowGameMap();

// Starting Game Loop.
GameLoop:
    /* <----- Update -----> */

    char action;
    cout << "life :" << life << "\n";
    cout << "input :";

    action = getch();
    UpdateGame(action);
    if (EatPuls)
    {
        life += 1;
        EatPuls = false;
    }
    if (boom)
    {
        life -= 1;
        boom = false;
        if (life == 0)
        {
            ShowGameMap();
            cout << "    \n  -----You lost the game-----    \n";
            cout << "1. play new game\n2. Exit\n";
            cout << "Choose: ";
            WannaPlayAgain = getch();
            if (WannaPlayAgain == 1)
            {
                xpos = 0;
                ypos = 0;
                gameMap[0][0] = '!';
                life = 2;
                GenerateRandomMap();
                goto PlayAgain;
            }
            else if (WannaPlayAgain == 0)
            {
                cout << "Bye!";
                return EXIT_SUCCESS;
            }
        }
    }

    /* <----- Render -----> */
    // Clear
    system("cls");
    // Draw
    ShowGameMap();
    if (isWinTheGame)
    {
        static int level = 0;
        score += 1;

        level += 1;
        cout << "\n   You Win !\n";
        cout << "Score :" << ' ' << score << endl;
        cout << "Level :" << ' ' << level << endl;

        isWinTheGame = false;
        xpos = 0;
        ypos = 0;
        gameMap[0][0] = '!';

        goto PlayAgain;
    }
    goto GameLoop;
}
char input()
{
    char input;
    input = _getche();
    return input;
}
char cin_function()
{
    char input;
    cout << " \ninput :";
    cin >> input;
    return input;
}
void showmenu()
{

    cout << "======================================\n";
    cout << " \t\tMENU \t \n ";
    cout << "======================================\n";
    cout << " 1. Start Game\n";
    cout << " 2. Settings\n";
    cout << " 3. Records \n";
    cout << " 4. Exit \n";

    switch (cin_function())
    {
    case '1':
        system("cls");
        StartGame();
        break;
    case '2':
        system("cls");
        Settings();

        break;
    case '3':
        system("cls");
        Records();
        break;

    case '4':
        system("cls");

        Exit();
        break;

    default:
        cout << "error";
        break;
    }
}

void StartGame()
{
    ShowGameMap();
}
void Settings()
{
    cout << "1.Row of the game play \n2.Column of the game play \n";
    cout << "3.Number of stone. \n4.Number of bomb  \n5.Number of life\n6.Number of plus\n7.Exit";
    switch (cin_function())
    {
    case '1':
        system("cls");
        cout << "Edit size of row : ";
        cin >> sizerow;

        break;
    case '2':
        system("cls");
        cout << "Edit size of column : ";
        cin >> sizecol;

        break;
    case '3':
        system("cls");
        cout << "Edit number of stone : ";
        cin >> BlockLevel;
        break;
    case '4':
        system("cls");
        cout << "Edit number of bomb : ";
        cin >> Bomb;
    case '5':
        system("cls");
        cout << "Edit number of life : ";
        cin >> life;
    case '6':
        system("cls");
        cout << "Edit number of puls : ";
        cin >> Plus;
        break;
    case '7':
        system("cls");
        break;
        // cin >> number_of_coin;
    default:
        system("cls");
    }
}
void Records()
{
}

void Exit()
{
    isExit = true;
}
void ShowGameMap()
{
    system("cls");
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            cout << gameMap[i][j] << ' ';
        }
        cout << endl;
    }
}

void UpdateGame(char action)
{

    // User Input
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            /* 4 direction to go with w,a,s,d */
            if (action == 'w')
                if (Movements(i, j, 0, -1))
                    break;
            if (action == 's')
                if (Movements(i, j, 0, 1))
                    break;
            if (action == 'd')
                if (Movements(i, j, 1, 0))
                    break;
            if (action == 'a')
                if (Movements(i, j, -1, 0))
                    break;

            /* 4 Way to break i,j,k,l */
            if (action == 'i')
                BreakDir(i, j, 0, -1);
            if (action == 'k')
                BreakDir(i, j, 0, 1);
            if (action == 'l')
                BreakDir(i, j, 1, 0);
            if (action == 'j')
                BreakDir(i, j, -1, 0);
        }
    }
    // Fix Block Gravity and Dolar Gravity and Puls  .
    SearchForBlockGravity();
    SearchForDolarGravity();
    SearchForPuls();
    SearchForBomb();
}

bool Movements(int x, int y, int xDir, int yDir)
{
    if (gameMap[x][y] == ' ' || gameMap[x][y] == '$' || gameMap[x][y] == '+' || gameMap[x][y] == '&')
    {
        if (xpos + xDir == y && ypos + yDir == x)
        {
            if (gameMap[x][y] == '$')
                isWinTheGame = true;
            if (gameMap[x][y] == '+')
                EatPuls = true;
            if (gameMap[x][y] == '&')
                boom = true;
            xpos += xDir;
            ypos += yDir;
            gameMap[x - yDir][y - xDir] = ' ';
            gameMap[x][y] = '!';
            return true;
        }
    }
    return false;
}
void BreakDir(int x, int y, int xDir, int yDir)
{
    if (gameMap[x][y] == '#')
    {
        if (xpos + xDir == y && ypos + yDir == x)
        {
            // Check if block is above.
            if (gameMap[x - 1][y] == '@')
            {
                gameMap[x - 1][y] = ' ';
                gameMap[x][y] = '@';
                return;
            }
            gameMap[x][y] = ' ';
        }
    }
}

void SearchForBlockGravity()
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (gameMap[i][j] == '@')
            {
                if (gameMap[i + 1][j] == ' ')
                {
                    gameMap[i][j] = ' ';
                    gameMap[i + 1][j] = '@';
                }
            }
        }
    }
}

void SearchForDolarGravity()
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (gameMap[i][j] == '$')
            {
                if (gameMap[i + 1][j] == ' ')
                {
                    gameMap[i][j] = ' ';
                    gameMap[i + 1][j] = '$';
                }
            }
        }
    }
}
void SearchForPuls()
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (gameMap[i][j] == '+')
            {
                if (gameMap[i + 1][j] == ' ')
                {
                    gameMap[i][j] = ' ';
                    gameMap[i + 1][j] = '+';
                }
            }
        }
    }
}
void SearchForBomb()
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (gameMap[i][j] == '&')
            {
                if (gameMap[i + 1][j] == ' ')
                {
                    gameMap[i][j] = ' ';
                    gameMap[i + 1][j] = '&';
                }
            }
        }
    }
}

void GenerateRandomMap()
{
    char getMapList[32];
    int interval = 0;
    int counterOfDollar = 0;
    int counterOfBlock = 0;
    int counterOfplus = 0;
    int counterOfBomb = 0;
    int entireBlockInRow = 0;
    int entireBlockInCol = 0;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            // Skip Touching the player.
            if (i == 0 && j == 0)
                continue;
        // Touch other things.
        Retry:
            int getRandom = rand() % 5;
            gameMap[i][j] = mapList[rand() % 5];

            // We should set $ at 5 - 10 position at least.
            if (gameMap[i][j] == '$' && j < 5)
                goto Retry;
            // We should set + at 5 - 10 position at least.
            if (gameMap[i][j] == '+' && j < 5)
                goto Retry;
            // We should set + at 5 - 10 position at least.
            if (gameMap[i][j] == '&' && j < 5)
                goto Retry;
            // We shouldn't make to much block maybe 4 is enough.
            if (gameMap[i][j] == '@')
                counterOfBlock++;

            if (counterOfBlock > BlockLevel)
            {
                counterOfBlock--;
                goto Retry;
            }

            // We shouldn't make to much plus maybe 1 is enough.
            if (gameMap[i][j] == '+')
                counterOfplus++;

            if (counterOfplus > Plus)
            {
                counterOfplus--;
                goto Retry;
            }
            // We shouldn't make to much plus maybe 2 is enough.
            if (gameMap[i][j] == '&')
                counterOfBomb++;

            if (counterOfBomb > Bomb)
            {
                counterOfBomb--;
                goto Retry;
            }

            // We should check if player's both side is not blocked.
            if (gameMap[i][j] == gameMap[0][1] || gameMap[i][j] == gameMap[1][0])
            {
                if (gameMap[i][j] == '@')
                {
                    counterOfBlock--;
                    goto Retry;
                }
            }

            // We should check if entire row or column is not blocked.
            entireBlockInRow = 2;
            entireBlockInCol = 2;
            for (int row1 = 0; row1 < row; row1++)
            {
                if (gameMap[row1][j] == '@')
                    entireBlockInRow++;
                if (entireBlockInRow > 3)
                {
                    entireBlockInRow--;
                    counterOfBlock--;
                    goto Retry;
                }
            }
            for (int col1 = 0; col1 < col; col1++)
            {
                if (gameMap[i][col1] == '@')
                    entireBlockInRow++;
                if (entireBlockInCol > 7)
                {
                    entireBlockInCol--;
                    counterOfBlock--;
                    goto Retry;
                }
            }
            // We should only set one dollar $.
            if (gameMap[i][j] == '$')
                counterOfDollar++;
            if (counterOfDollar > 1)
            {
                counterOfDollar--;
                goto Retry;
            }
        }
    }
    if (counterOfBlock < BlockLevel)
        GenerateRandomMap();
}
bool IsMapGoodToPlay()
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (gameMap[i][j] == gameMap[j][i])
            {
                if (gameMap[i][j] == '@' && gameMap[j][i] == '@')
                {
                    return false;
                }
            }
        }
    }
    return true;
}