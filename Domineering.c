#include <stdio.h>
#include <stdbool.h>
#ifndef FIELDS
#define FIELDS 7
#endif
#ifndef HEIGHT
#define HEIGHT 26
#endif
#ifndef WIDTH
#define WIDTH 26
#endif
#ifndef RANDOM_NUMBER
#define RANDOM_NUMBER 1000
#endif

/* Domineering is a game for 1 or 2 players. To now the rules i recomend to read sth about it in wikipedia.

    My inpretation: 
        * The Board have columns named like A, B, C, D ...  and lines named like  a, b, c, d ...  and YOU CHOOSE FROM WITH FIELD WILL BE STARTING YOUR MOVE 
                IMPORTANT:
        * Player1 is plaing verticaly, and in move gives first name of COLUMN and after this name of LINE    like  Cg   or   Aa 
        * Player2 is plaing horizontaly, and in move gives first name of LINE and after this name of COLUMN    like  gC   or   aA   
          so theres different way
        
        * In the begining of the game we'll ask you how many players will play becouse you can play with your mate or with computer
        * Move of each players you write in terminal
        * When player wont to give his move to opponent, he has to write ' - ' in terminal
        * Write ' . ' (dot) when you want to give up 
        * FIELDS is value of how many field you can take with you single move
        * You can change values of FIELDS, HEIGHT, WIDTH or RANDOM_NUMBER if you want
        * RANDOM_NUMBER is the number the program use only to choose one move if computer have >1 the same good for him moves
        
    GOOD LUCK GUYS!
*/

char GetInput()
{
    char input = (char)getchar();
    while (input == ' ' || input == '\n' || input == '\r')
    {
        input = (char)getchar();
        if (input == EOF)
        {
            input = '0';
            return input;
        }
    }
    if (input != EOF)
        return input;
    else
    {
        input = '0';
        return input;
    }
}
void ClearArr(int Arr[], int size)
{
    for (int i = 0; i < size; i++)
        Arr[i] = 0;
}
void InitArr(char Board[HEIGHT][WIDTH])
{
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
            Board[i][j] = '1';
    }
}
void PrintBoard(char Board[HEIGHT][WIDTH]){
    printf("\n   ");
    for (int i = 0; i < WIDTH; i++)
    {
        printf(" %c ", 65 + i);
    }
    printf("\n");
    
    for (int i = 0; i < HEIGHT; i++)
    {   
        printf(" %c ", 97 + i);
        for (int j = 0; j < WIDTH; j++)
            printf(" %c ",Board[i][j]);
        printf("\n");
    }
}
bool Player1MoveDone(char Board[HEIGHT][WIDTH], bool InProgress, bool *MoveError)
{
    char field = GetInput();
    if (field == '0' || field == '.')
    {
        printf("\n  PLAYER2 WON!  \n");
        InProgress = false;
        return InProgress;
    }
    else if (field == '-') 
        printf("\n PlayerOne gives his move to his opponent \n");
    else
    {
        int column = 0, line = 0;
        column = (int)field - 65;
        line = (int)GetInput() - 97;

        for (int i = 0; i < FIELDS; i++){
            if(Board[line + i][column] == '#')
            {
                printf("\n YOUR MOVE COLITE WITH USED FIELD, CHOOSE ANOTHER MOVE OR SURRENDER TYPING DOT \n");
                *MoveError = true;
                return InProgress;
            }
        }
        *MoveError = false;
        for (int i = 0; i < FIELDS; i++)
            Board[line + i][column] = '#';

        PrintBoard(Board);
    }
    return InProgress;
}
bool Player2MoveDone(char Board[HEIGHT][WIDTH], bool InProgress, bool *MoveError)
{
    char field = GetInput();
    if (field == '0' || field == '.')
    {
        InProgress = false;
        printf("\n PLAYER1 WON! \n");
        return InProgress;
    }
    else if (field == '-')
        printf("\n Player2 gives his move to his opponent \n");
    else
    {
        int column = 0, line = 0;
        line = (int)field - 97;
        column = (int)GetInput() - 65;

        for (int i = 0; i < FIELDS; i++){
            if(Board[line][column + i] == '#')
            {
                printf("\n YOUR MOVE COLITE WITH USED FIELD, CHOOSE ANOTHER MOVE OR SURRENDER TYPING DOT \n");
                *MoveError = true;
                return InProgress;
            }
        }
        *MoveError = false;
        for (int i = 0; i < FIELDS; i++)
            Board[line][column + i] = '#';
        PrintBoard(Board);
    }
    return InProgress;
}
void PossibilitiesNow(char Board[HEIGHT][WIDTH], int *Possibilities1stPlayer, int *Possibilities2ndPlayer){
    for (int m = 0; m < WIDTH; m++) //counting how many opcion have 1st player after the move
    {
        int counter2 = 0;
        for (int m2 = 0; m2 < HEIGHT; m2++)
        {
            if (Board[m2][m] == '1')
                counter2++;
            else
                counter2 = 0;
            if (counter2 == FIELDS)
            {
                (*Possibilities1stPlayer)++;
                counter2 = 0;
            }
        }
    }
    for (int m = 0; m < HEIGHT; m++) //counting how many opcion have 2nd player
    {
        int counter2 = 0;
        for (int m2 = 0; m2 < WIDTH; m2++)
        {
            if (Board[m][m2] == '1')
                counter2++;
            else
                counter2 = 0;
            if (counter2 == FIELDS)
            {
                (*Possibilities2ndPlayer)++;
                counter2 = 0;
            }
        }
    }
}
int CountBestPossibilities(char Board[HEIGHT][WIDTH], int *ArrOfPossibilities){

    int Possibilities2ndPlayer = 0, Possibilities1stPlayer = 0, SumPossibilities = 0;
    int min_SumPossibilities = (HEIGHT - FIELDS + 1) * 2 * WIDTH, index = 0, possibilities = 0;
    bool MoveDone = false;

    //we gonna try every opcion to move and then count how many moves we and our opponent can make
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH + FIELDS; j++)
        {
            int counter1 = 0, counter = 0;
            for (int k = 0; k < FIELDS && j + k < WIDTH; k++)
            {
                if (Board[i][j + k] == '1')
                    counter++;
            }
            if (counter == FIELDS)
            {
                MoveDone = true;
                for (int l = 0; l < FIELDS && (j + l) < WIDTH && Board[i][j + l] != '#'; l++)
                {
                    Board[i][j + l] = '5';
                    counter1++;
                }
            }
            if (counter1 == FIELDS)
            {
                SumPossibilities = 0, Possibilities1stPlayer = 0, Possibilities2ndPlayer = 0;
                
                PossibilitiesNow(Board, &Possibilities1stPlayer, &Possibilities2ndPlayer);
                
                SumPossibilities = Possibilities1stPlayer - Possibilities2ndPlayer;
                if (SumPossibilities < min_SumPossibilities)
                {
                    min_SumPossibilities = SumPossibilities;
                    ClearArr(ArrOfPossibilities, (WIDTH - FIELDS + 1) * 2 * HEIGHT);
                    index = 0;
                    possibilities = 0;
                }
                if (SumPossibilities == min_SumPossibilities)
                {
                    ArrOfPossibilities[index] = i;
                    ArrOfPossibilities[index + 1] = j;
                    index += 2;
                    possibilities++;
                }
            }
            if (MoveDone)
                for (int p = 0; p < counter1; p++)
                    Board[i][j + p] = '1';

            MoveDone = false;
        }
    }
    return possibilities;
}
bool ComputerMoveDone(char Board[HEIGHT][WIDTH], bool InProgress)
{
    int column = 0, line = 0;
    int ArrOfPossibilities[(WIDTH - FIELDS + 1) * 2 * HEIGHT];

    ClearArr(ArrOfPossibilities, (WIDTH - FIELDS + 1) * 2 * HEIGHT);

    //serching best possibilities
    int possibilities = CountBestPossibilities(Board, ArrOfPossibilities);
    
    if (possibilities == 0)
    {
        InProgress = false;
        printf("\n YOU WON, CONGRATS!\n");
        return InProgress;
    }
    else //choosing the move 
    {
        int ChooseMove = RANDOM_NUMBER % possibilities;
        line = ArrOfPossibilities[ChooseMove * 2];
        column = ArrOfPossibilities[(ChooseMove * 2) + 1];

        for (int i = 0; i < FIELDS; i++) 
            Board[line][column + i] = '#';
        
        PrintBoard(Board);
        possibilities = 0;
    }
    if (InProgress)
        printf("\n YOUR TURN MATE! WRITE ME YOUR MOVE (: \n");

    return InProgress;
}

int main()
{
    char Board[HEIGHT][WIDTH];
    InitArr(Board);
    bool InProgress = true, MoveError = false;
    int player;
    printf("1 player or 2 players?\n \n");
    scanf("%d", &player);

    PrintBoard(Board);
    if(player == 1){
        while (InProgress)
        {
            printf("\n 1ST PLAYER MOVE(sth like Aa, Bg) \n");
            InProgress = Player1MoveDone(Board, InProgress, &MoveError);
            while (MoveError){
                printf("\n PLAYER1 REPEATS HIS MOVE \n ");
                InProgress = Player1MoveDone(Board, InProgress, &MoveError);
            }
            if (InProgress)
                InProgress = ComputerMoveDone(Board, InProgress);
        }
    }
    else if(player == 2){
        while (InProgress)
        {
            printf("\n 1ST PLAYER MOVE(sth like Aa, Bg) \n");
            InProgress = Player1MoveDone(Board, InProgress, &MoveError);
            while (MoveError){
                printf("\n PLAYER1 REPEATS HIS MOVE \n ");
                InProgress = Player1MoveDone(Board, InProgress, &MoveError);
            }
            if (InProgress){
                printf("\n 2ND PLAYER MOVE(sth like aA, cD) \n");
                InProgress = Player2MoveDone(Board, InProgress, &MoveError);
                while (MoveError){
                    printf("\n PLAYER2 REPEATS HIS MOVE \n ");
                    InProgress = Player1MoveDone(Board, InProgress, &MoveError);
                }
            }
        }
    }
    else
        printf("Wrong number. Choose beetwen 1 and 2");

    return 0;
}