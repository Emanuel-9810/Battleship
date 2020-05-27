#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <iomanip>
#include <cstdlib>

using namespace std;

// CONSTANT VARIABLES
const string dashes="----";     //Global constant - Outputs the dashes
const int FLEET_SIZE = 5;       //Global constant - Size of the fleet
const int carrier = 5;          //Global constant - Carrier Size
const int battleship = 4;       //Global constant - Battleship size
const int cruiser = 3;          //Global constant - Cruiser size
const int submarine = 3;        //Global constant - Sub size
const int destroyer = 2;        //Global constant - Destroyer size

//CONST STRUCT
struct Point
{
    int   row;               //Row index of cell in grid
    int   col;               //Column index of cell in grid
};

//CONST STRUCT
struct Ship
{
    string shipName;        //The name of the ship
    int shipSize;           //The size of the ship
    int hitCount;           //The hitCount
    vector<Point> pos;      //Vector that stores the indices of hit ships
};

//CONST STRUCT
struct PlayerBoard
{
    char board[10][10];      //Stores the board for the particular player
    Ship ships[FLEET_SIZE];  //Stores an array of Ship structs of size FLEET_SIZE
};

// FUNCTION PROTOTYPES
/*******************************************************************************
* displayBoards
* This function creates the gameboards for the 2 players, and displays both of
* the boards side by side with the columns numbered from 1 to 10 at the top and
* the rows as the letters from A to J
* returns - nothing
*******************************************************************************/
void displayBoards(char [][10], char [][10]);

/*******************************************************************************
* initFleet
* This function takes in a PlayerBoard object as a parameter and initializes
* all the ships in the fleet with the appropriate information. For example, the
* name and size of the ship should be initialized within the function.
* returns - nothing
*******************************************************************************/
void initFleet(PlayerBoard&);

/*******************************************************************************
* setShip
* This function takes in a PlayerBoard object by reference and an int variable
* that stores the index of the ship that is currently being placed, and places
* the ship onto the board. It then calls the getValidShipInfo function to
* determine which spots on the board the ship will occupy.
* returns - nothing
*******************************************************************************/
void setShip(PlayerBoard&, int);

/*******************************************************************************
* getValidShipInfo
* This function takes in four parameters by reference, two ints holding the row
* and the column of the starting coordinates of the ship, a char that will hold
* the orientation of the ship (horizontal or vertical), and the PlayerBoard. The
* function will also take a fifth argument by value which is the index of the
* ship being placed.  The function will prompt the user for the starting row
* and column coordinates of the ship which the user will enter as:letter number.
* These will then need to be converted to the proper row and column index of the
* array.  The function will also prompt the user for the horizontal or vertical
* orientation of the ship.  The function will be responsible for performing the
* error checking so that a valid ship placement is received from the user.  The
* function will also call the function spaceOccupied to determine if any of the
* spaces the ship would take up if placed on the board are currently occupied.
* returns - nothing
*******************************************************************************/
void getValidShipInfo(int&, int&, char&, PlayerBoard&, int);

/*******************************************************************************
* initBoard
* This function takes in the PlayerBoard objects and initializes the boards in
* the main.
* returns - nothing
*******************************************************************************/
void initBoard(PlayerBoard&, PlayerBoard&);

/*******************************************************************************
* shots1
* This function takes in 3 paramaters for both Playerboards and an int value.
* It takes the users input for the coordinates of the shot and then checks if the
* position is invalid, if it is a hit, or a miss. It updates the board with an H
* or M depending on a hit or miss. It calls the checkwin function to determine
* if there is a gamewinning shot.
* returns - nothing
*******************************************************************************/
void shots1(PlayerBoard &, PlayerBoard &, int);

/*******************************************************************************
* shots2
* This function takes the shots from the computer and checks if they are valid
* and if the player hits a ship, prints a hit or miss if they don't.
* returns - nothing
*******************************************************************************/
void shots2(PlayerBoard&, PlayerBoard&);

/*******************************************************************************
* initCompBoard
* This function takes in the PlayerBoard objects and initializes the boards in
* the main.
* returns - nothing
*******************************************************************************/
void initCompBoard(PlayerBoard&, PlayerBoard&);

/*******************************************************************************
* getValidShipinfo2
* This function takes the input for the computer and uses the rand function to
* get the coordinates. It takes in five parameters similarly to the getValidShi-
* pInfo function and works in a similar fashion.
*******************************************************************************/
void getValidShipinfo2(int&, int&, char&,
                      PlayerBoard&, int);

/*******************************************************************************
* spaceOccupied
* This function takes in the PlayerBoard object, an int for the row and col
* placement of the ship, a character for the orientation, and the ship size. It
* will return true if the placement of the ship would overlap an already existing
* ship placement or false if the space is not occupied.
* returns - true or false depending on placement
*******************************************************************************/
bool spaceOccupied(PlayerBoard &p, int row, int col,
                   char orien, int s_size);

/*******************************************************************************
* check
* This function takes in 3 parameters. The function checks if the coordinates
* are valid, if they are then the function returns the boolean statement
* returns - true/false if the coordinates are valid/invalid
*******************************************************************************/
bool check(int row, int col, char orien);

/*******************************************************************************
* setShipCP
* This function sets the positions of the ships for the computer.
* returns - nothing
*******************************************************************************/
void setShipCP(PlayerBoard &p, int shipIndex);

/*******************************************************************************
* checkwin
* This function checks if the coordinates are valid, if they are then the funct-
* ion returns true
* returns - true if the coordinates are valid
*******************************************************************************/
bool checkwin(char b[][10]);

/*******************************************************************************
* randInput
* This function randomizes the inputs for the coordinates.
* returns - nothing
*******************************************************************************/
void randInput (int& row, int& col);

/*******************************************************************************
* initSpace
* This function sets the empty spots of the board to a blank space
* returns - nothing
*******************************************************************************/
void initSpace(char [][10]);

int main()
{

    PlayerBoard user;           //Player 1
    PlayerBoard enemy;          //Player 2
    int player_turn;            //Players turn


    string answer;              //INPUT - user inputs yes or no

    //Call initSpace for both player's boards
    initSpace(user.board);
    initSpace(enemy.board);

    //Call initFleet for both players to initialize fleet
    initFleet(user);
    initFleet(enemy);

    //INPUT - Ask the user if they wanna play vs computer
    cout << "Would you like to play with the computer?" << endl;
    cin >> answer;


    //If the user answers yes, play vs computer
    if (answer== "yes")
    {
        srand(0);
        initCompBoard(user,enemy);
        player_turn = 1;

        while(1)
        {
            if(player_turn == 1)
            {
                shots1(user,enemy,player_turn);
                displayBoards(user.board, enemy.board);

                player_turn = 2;
            }
            else if (player_turn == 2)
            {
                shots2(enemy, user);

                displayBoards(enemy.board, user.board);
                player_turn =1;
            }
        }
    }

    //If the user answers no, player vs player
    else if (answer == "no")
    {
        initBoard(user, enemy);

        cout << endl;

        player_turn = 1;

        while (1)
        {
            if (player_turn == 2)
            {
                shots1(enemy, user, player_turn);
                displayBoards(enemy.board, user.board);

                player_turn = 1;
            }
            else
            {
                shots1(user, enemy, player_turn);
                displayBoards(user.board, enemy.board);


                player_turn = 2;
            }
        }
    }

    return 0;
}
/*******************************************************************************
*
* FUNCTION displayBoards
*
*-------------------------------------------------------------------------------
* displayBoards
* This function creates the gameboards for the 2 players, and displays both of
* the boards side by side with the columns numbered from 1 to 10 at the top and
* the rows as the letters from A to J
* returns - nothing
*******************************************************************************/
void displayBoards(char board1[][10], char board2[][10])
{
    char alpha;
    cout << setw(25)<< "Your Board"<<setw(50)<<"Enemy Board"<<endl;
    for( int row = 0; row < 10; row++ )
    {
        //Numbers for player board
        if (row == 0)
        {
            for( int nums = 0; nums < 10; nums++ )
            {
                cout << setw(4) << nums +1;
            }
            cout << setw(11)<<" ";
        }

        //Numbers for enemy board
        if (row == 0)
        {
            for( int nums2 = 0; nums2 < 10; nums2++ )
            {
                cout << setw(4) << nums2 + 1;
            }
            cout <<setw(11)<<" "<< endl;
        }

        //Dashes for the player board
        cout << "  ";
        for( int col = 0; col < 10; col++ )
        {
            cout << dashes;
        }
        cout << "-"<<setw(11);

        //Dashes for the enemy board
        cout << "  ";
        for( int col = 0; col < 10; col++ )
        {
            cout << dashes;
        }
        cout << "-" <<endl;

        //Letters for the player board
        alpha = 'A' + row;
        cout << alpha  << " |";
        for( int col = 0; col < 10; col++ )
        {
            cout << " " << board1[ row ][ col ] << " |";
        }

        cout << "         ";

        //Letters for the enemy board
        alpha = 'A' + row;
        cout << alpha  << " |";
        for( int col = 0; col < 10; col++ )
        {
            cout << " " << board2[row][col] << " |";
        }
        cout << endl;
    }

     //Last row for players board
    cout << "  ";
    const string DASHES(41,'-');
    const string SPACING(11, ' ');

    cout << DASHES << SPACING << DASHES << endl;
}
/*******************************************************************************
*
* FUNCTION initBoard
*
*-------------------------------------------------------------------------------
* initBoard
* This function takes in the PlayerBoard objects and initializes the boards in
* the main.
* returns - nothing
*******************************************************************************/

void initBoard(PlayerBoard &user, PlayerBoard &enemy)
{

    cout << "Player 1 set your board.\n";
    displayBoards(user.board, enemy.board);

    for (size_t i = 0; i < FLEET_SIZE; i++)
    {
        setShip(user, i);
        displayBoards(user.board, enemy.board);
    }

    cout << "Player 2 set your board.\n";
    displayBoards(enemy.board, user.board);
    for (size_t i = 0; i < FLEET_SIZE; i++)
    {
        setShip(enemy, i);
        displayBoards(enemy.board, user.board);
    }

}
/*******************************************************************************
*
* FUNCTION initFleet
*
*-------------------------------------------------------------------------------
* This function takes in a PlayerBoard object as a parameter and initializes
* all the ships in the fleet with the appropriate information. For example, the
* name and size of the ship should be initialized within the function.
* returns - nothing
*******************************************************************************/
void initFleet(PlayerBoard &p)
{
    for (int i = 0; i < FLEET_SIZE; i++)
    {
        if (i == 0)
        {
            p.ships[i].shipName = "carrier";
            p.ships[i].shipSize = carrier;
        }
        else if (i == 1)
        {
            p.ships[i].shipName = "battleship";
            p.ships[i].shipSize = battleship;
        }
        else if (i == 2)
        {
            p.ships[i].shipName = "cruiser";
            p.ships[i].shipSize = cruiser;
        }
        else if (i == 3)
        {
            p.ships[i].shipName = "submarine";
            p.ships[i].shipSize = submarine;
        }
        else if (i == 4)
        {
            p.ships[i].shipName = "destroyer";
            p.ships[i].shipSize = destroyer;
        }

        p.ships[i].hitCount = 0;

        for (int v = 0; v < p.ships[i].shipSize; v++)
        {
            p.ships[i].pos.push_back(Point());
            p.ships[i].pos[v].row = -1;
            p.ships[i].pos[v].col = -1;

        }

    }
}
/*******************************************************************************
*
* FUNCTION getValidShipInfo
*
*-------------------------------------------------------------------------------
* getValidShipInfo
* This function takes in four parameters by reference, two ints holding the row
* and the column of the starting coordinates of the ship, a char that will hold
* the orientation of the ship (horizontal or vertical), and the PlayerBoard. The
* function will also take a fifth argument by value which is the index of the
* ship being placed.  The function will prompt the user for the starting row
* and column coordinates of the ship which the user will enter as:letter number.
* These will then need to be converted to the proper row and column index of the
* array.  The function will also prompt the user for the horizontal or vertical
* orientation of the ship.  The function will be responsible for performing the
* error checking so that a valid ship placement is received from the user.  The
* function will also call the function spaceOccupied to determine if any of the
* spaces the ship would take up if placed on the board are currently occupied.
* returns - nothing
*******************************************************************************/
void getValidShipInfo(int &row, int &col, char &orien,
                      PlayerBoard &p, int shipIndex)
{
    char letter='x';

    //PROCESSING - User inputs coordinates while they pass the checks
    do{

        //INPUT - Ask the user for starting coordinates
        cout << "Enter the starting coordinates of your "
             << p.ships[shipIndex].shipName << ": ";
        cin >> letter >> col;
        cout << endl;

        //INPUT - Ask the user for the orientation
        cout << "Enter the orientation of your "
             << p.ships[shipIndex].shipName << " (horizontal(h) or vertical(v)): ";
        cin >> orien;
        cout << endl;

        row = (char)toupper(letter) - 'A';
        col -= 1;
        orien = (char)tolower(orien);

    }
    while (!check(row, col, orien));

    if (spaceOccupied(p, row, col,
                      orien, p.ships[shipIndex].shipSize))
        getValidShipInfo(row, col, orien, p, shipIndex);
}
/*******************************************************************************
*
* FUNCTION getValidShipinfo2
*
*-------------------------------------------------------------------------------
* getValidShipinfo2
* This function takes the input for the computer and uses the rand function to
* get the coordinates. It takes in five parameters similarly to the getValidShi-
* pInfo function and works in a similar fashion.
*******************************************************************************/

void getValidShipinfo2(int &row, int &col, char &orien,
                      PlayerBoard &p, int shipIndex)
{
    char letter;            //Row of the board
    int col1;               //Column of the board
    int randnum;            //Random number generated

    row = rand() % 10;
    col = rand() % 10;

    letter = row + 65;
    col1 = col + 1;

    //Get randnum
    randnum = rand() % 2;

    if (randnum == 0)
    {
        orien = 'h';
    }
    else if (randnum == 1)
    {
        orien = 'v';
    }

    //PROCESSING - Input coordinates while they pass the checks
    do{

        //INPUT - Ask the user for starting coordinates
        cout << "Enter the starting coordinates of your "
             << p.ships[shipIndex].shipName << ": ";
        cout << letter << col1;
        cout << endl;

        //INPUT - Ask the user for the orientation
        cout << "Enter the orientation of your "
           << p.ships[shipIndex].shipName << " (horizontal(h) or vertical(v)): ";
        cout << orien;
        cout << endl;

    }
    while (!check(row, col, orien));

    if (spaceOccupied(p, row, col,
                      orien, p.ships[shipIndex].shipSize))
        getValidShipinfo2(row, col, orien, p, shipIndex);
}
/*******************************************************************************
*
* FUNCTION setShip
*
*-------------------------------------------------------------------------------
* setShip
* This function takes in a PlayerBoard object by reference and an int variable
* that stores the index of the ship that is currently being placed, and places
* the ship onto the board. It then calls the getValidShipInfo function to
* determine which spots on the board the ship will occupy.
* returns - nothing
*******************************************************************************/
void setShip(PlayerBoard &p, int shipIndex)
{
    int row=-1;
    int col=-1;
    char orien='x';

    getValidShipInfo(row, col, orien, p, shipIndex);

    if (orien == 'v')
    {
        if (p.ships[shipIndex].shipSize + row > 10)
        {
            cout << "Error: Ship placement is outside the board.\n";
            return (setShip(p, shipIndex));
        }

        for (int i = 0; i < p.ships[shipIndex].shipSize; i++)
        {
            p.board[row+i][col] = 's';
            p.ships[shipIndex].pos[i].row = row +i;
            p.ships[shipIndex].pos[i].col = col;
        }
    }
    else if (orien == 'h')
    {
        if (p.ships[shipIndex].shipSize + col > 10)
        {
            cout << "Error: Ship placement is outside the board.\n";
            return (setShip(p, shipIndex));
        }

        for (int i = 0; i < p.ships[shipIndex].shipSize; i++)
        {
            p.board[row][col+i] = 's';
            p.ships[shipIndex].pos[i].row = row;
            p.ships[shipIndex].pos[i].col = col + i;
        }
    }

}
/*******************************************************************************
*
* FUNCTION randInput
*
*-------------------------------------------------------------------------------
* randInput
* This function randomizes the inputs for the coordinates.
* returns - nothing
*******************************************************************************/
void randInput (int& row, int& col)
{
    char row1;
    int col1;

    row = rand() % 10;
    col = rand() % 10;

    row1 = row + 65;
    col1 = col + 1;

    cout << row1 << col1 << endl;
}

/*******************************************************************************
*
* FUNCTION initSpace
*
*-------------------------------------------------------------------------------
* initSpace
* This function sets the empty spots of the board to a blank space
* returns - nothing
*******************************************************************************/
void initSpace(char a[][10])
{
    for (size_t r = 0; r < 10; r++)
        for (size_t c = 0; c < 10; c++)
            a[r][c] = ' ';
}
/*******************************************************************************
*
* FUNCTION checkwin
*
*-------------------------------------------------------------------------------
* checkwin
* This function checks if the coordinates are valid, if they are then the funct-
* ion returns true
* returns - true if the coordinates are valid
*******************************************************************************/
bool checkwin(char b[][10])
{

    for (size_t r = 0; r < 10; r++)
        for (size_t c = 0; c < 10; c++)
            if (b[r][c] == 's')
                return false;

    cout << "You sunk the fleet!!! You win!!!\n";
    exit(1);

    return true;
}
/*******************************************************************************
*
* FUNCTION initCompBoard
*
*-------------------------------------------------------------------------------
* initBoard
* This function takes in the PlayerBoard objects and initializes the boards in
* the main.
* returns - nothing
*******************************************************************************/

void initCompBoard(PlayerBoard &user, PlayerBoard &enemy)
{

    cout << "Player 1 set your board.\n";
    displayBoards(user.board, enemy.board);
    for (size_t i = 0; i < FLEET_SIZE; i++)
    {
        setShip(user, i);
        displayBoards(user.board, enemy.board);
    }

    cout << "Player 2 set your board.\n";
    displayBoards(enemy.board, user.board);
    for (size_t i = 0; i < FLEET_SIZE; i++)
    {
        setShipCP(enemy, i);
        displayBoards(enemy.board, user.board);
    }
}

/*******************************************************************************
*
* FUNCTION setShipCP
*
*-------------------------------------------------------------------------------
* setShipCP
* This function sets the positions of the ships for the computer.
* returns - nothing
*******************************************************************************/
void setShipCP(PlayerBoard &p, int shipIndex)
{
    int row=-1;
    int col=-1;
    char orien='x';

    getValidShipinfo2(row, col, orien, p, shipIndex);

    if (orien == 'v')
    {
        if (p.ships[shipIndex].shipSize + row > 10)
        {
            cout << "Error: Ship placement is outside the board.\n";
            return (setShipCP(p, shipIndex));
        }

        for (int i = 0; i < p.ships[shipIndex].shipSize; i++)
        {
            p.board[row+i][col] = 's';
            p.ships[shipIndex].pos[i].row = row +i;
            p.ships[shipIndex].pos[i].col = col;
        }
    }
    else if (orien == 'h')
    {
        if (p.ships[shipIndex].shipSize + col > 10)
        {
            cout << "Error: Ship placement is outside the board.\n";
            return (setShipCP(p, shipIndex));
        }

        for (int i = 0; i < p.ships[shipIndex].shipSize; i++)
        {
            p.board[row][col+i] = 's';
            p.ships[shipIndex].pos[i].row = row;
            p.ships[shipIndex].pos[i].col = col + i;
        }
    }

}

/*******************************************************************************
*
* FUNCTION shots1
*
*-------------------------------------------------------------------------------
* shots1
* This function takes in 3 paramaters for both Playerboards and an int value.
* It takes the users input for the coordinates of the shot and then checks if the
* position is invalid, if it is a hit, or a miss. It updates the board with an H
* or M depending on a hit or miss. It calls the checkwin function to determine
* if there is a gamewinning shot.
* returns - nothing
*******************************************************************************/
void shots1(PlayerBoard &user, PlayerBoard &enemy, int playnum)
{
    char letter='x';
    int row=-1;
    int col=-1;

    cout <<endl<<endl<<endl;

    //Display the boards
    displayBoards(user.board, enemy.board);
    cout << endl;
    cin.clear();
    do{
        letter = 'x';
        row = -1;
        col = -1;

        //INPUT - The user is asked to input the coordinates of their shot
        cout << "Player "<< playnum<<":\n" << "Fire a shot: ";
        cin >> letter >> col;

        row = (char)toupper(letter) - 'A';
        col -= 1;

        if (!(row >= 0 && row <= 9) || !(col >= 0 && col <= 9)
            || (enemy.board[row][col] != ' ' && enemy.board[row][col] != 's'))
        {
            cout << "Invalid\n";
        }
    }
    while (!(row >= 0 && row <= 9) || !(col >= 0 && col <= 9)
           || (enemy.board[row][col] != ' ' && enemy.board[row][col] != 's'));

    if (enemy.board[row][col] == 's')
    {
        cout << "Hit!!!\n";
        enemy.board[row][col] = 'H';
    }

    if (enemy.board[row][col] == ' ')
    {
        cout << "You Missed.\n";
        enemy.board[row][col] = 'M';
    }

    //Calculate the hitcount and if ship is sunk, output the ship's name
    for(int i = 0; i < FLEET_SIZE; i++)
    {
        int k;
        k = enemy.ships[i].shipSize;
        for ( int j = 0; j < k; j++)
        {
          if(enemy.ships[i].pos[j].row ==row && enemy.ships[i].pos[j].col==col)
          {
             enemy.ships[i].hitCount ++;
             if (enemy.ships[i].hitCount == k)
             {
               cout << "You sunk the " << enemy.ships[i].shipName <<"!!!"<<"\n";
             }
          }
        }
    }

    checkwin(enemy.board);

}
/*******************************************************************************
*
* FUNCTION shots2
*
*-------------------------------------------------------------------------------
* shots2
* This function takes the shots from the computer and checks if they are valid
* and if the player hits a ship, prints a hit or miss if they don't.
* returns - nothing
*******************************************************************************/
void shots2(PlayerBoard &user, PlayerBoard &enemy)
{
    int row;
    int col;

    cout <<endl<<endl<<endl;
    //Display the boards
    displayBoards(user.board, enemy.board);
    cout << endl;
    cin.clear();
    do{

        cout << "Player 2:\n"<< "Fire a shot: ";
        //Takes the random input for shot coordinates
        randInput(row, col);


        if (!(row >= 0 && row <= 9) || !(col >= 0 && col <= 9)
            || (enemy.board[row][col] != ' ' && enemy.board[row][col] != 's'))
        {
            cout << "Invalid\n";
        }
    }
    while (!(row >= 0 && row <= 9) || !(col >= 0 && col <= 9)
           || (enemy.board[row][col] != ' ' && enemy.board[row][col] != 's'));


    if (enemy.board[row][col] == 's')
    {
        cout << "Hit!!!\n";
        enemy.board[row][col] = 'H';
    }

    if (enemy.board[row][col] == ' ')
    {
        cout << "You Missed.";
        enemy.board[row][col] = 'M';
    }

    //Calculate the hitcount and if ship is sunk, output the ship's name
    for(int i = 0; i < FLEET_SIZE; i++)
    {
        int k;
        k= enemy.ships[i].shipSize;
        for ( int j = 0; j < k; j++)
        {
            if(enemy.ships[i].pos[j].row == row && enemy.ships[i].pos[j].col == col)
            {
                enemy.ships[i].hitCount ++;
                if (enemy.ships[i].hitCount ==k)
                {
                    cout<<"You sunk the "<<enemy.ships[i].shipName<<"!!!" <<"\n";
                }
            }
        }
    }
    checkwin(enemy.board);

}

/*******************************************************************************
*
* FUNCTION spaceOccupied
*
*-------------------------------------------------------------------------------
* spaceOccupied
* This function takes in the PlayerBoard object, an int for the row and col
* placement of the ship, a character for the orientation, and the ship size. It
* will return true if the placement of the ship would overlap an already existing
* ship placement or false if the space is not occupied.
* returns - true or false depending on placement
*******************************************************************************/
bool spaceOccupied(PlayerBoard &p, int row, int col,
                   char orien, int s_size)
{

    //Check if vertical space is occupied
    if (orien == 'v')
    {
        for (size_t i = row; i < s_size + row; i++)
        {
            if (p.board[i][col] != ' ')
            {
                cout << "Error: Space already occupied.\n";
                return true;
            }
        }
    }
    //Check if the horizontal space is occupied
    else if (orien == 'h')
    {
        for (size_t i = col; i < s_size + col; i++)
        {
            if (p.board[row][i] != ' ')
            {
                cout << "Error: Space already occupied.\n";
                return true;
            }
        }
    }
    //If space is not occupied, return false
    return false;
}

/*******************************************************************************
*
* FUNCTION check
*
*-------------------------------------------------------------------------------
* check
* This function takes in 3 parameters. The function checks if the coordinates
* are valid, if they are then the function returns the boolean statement
* returns - true/false if the coordinates are valid/invalid
*******************************************************************************/
bool check(int row, int col, char orien)
{
    //If the rows are not within range, false
    if (!(row >= 0 && row <= 9))
    {
        cout << "Error: Coordinates are not valid.\n";
        return false;
    }
    //If the columns are not within range, false
    else if (!(col >= 0 && col <= 9))
    {
        cout << "Error: Coordinates are not valid.\n";
        return false;
    }
    //If the orientation is not the right letter, false
    if (orien != 'v' && orien != 'h')
    {
        cout << "Error: orientation of ship is invalid.\n";
        return false;
    }

    return true;
}
