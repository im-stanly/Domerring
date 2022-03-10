#include <stdio.h>
#include <stdbool.h>
#ifndef FIELDS
#define FIELDS 5
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
bool Player1MoveDone(char Board[HEIGHT][WIDTH], bool InProgress)
{
    char field = GetInput();
    if (field == '0' || field == '.')
    {
        InProgress = false;
        return InProgress;
    }
    else if (field == '-')
    { //PlayerOne gives his move to opponent  
    }
    else
    {
        int column = 0, line = 0;
        column = (int)field - 65;
        line = (int)GetInput() - 97;
        for (int i = 0; i < FIELDS; i++)
        {
            Board[line + i][column] = '#';
        }
    }
    return InProgress;
}
bool Player2MoveDone(char Board[HEIGHT][WIDTH], bool InProgress)
{
    int column = 0, line = 0, possibilities = 0, index = 0;
    int ArrOfPossibilities[(WIDTH - FIELDS + 1) * 2 * HEIGHT];
    bool MoveDone = false;
    int Possibilities2ndPlayer = 0, Possibilities1stPlayer = 0, SumPossibilities = 0, min_SumPossibilities = (HEIGHT - FIELDS + 1) * 2 * WIDTH;

    ClearArr(ArrOfPossibilities, (WIDTH - FIELDS + 1) * 2 * HEIGHT);

    //serching possibilities
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH + FIELDS; j++)//we gonna try every opcion to move and then count how many moves we and our opponent can make
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
                for (int m = 0; m < WIDTH; m++)
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
                            Possibilities1stPlayer++;
                            counter2 = 0;
                        }
                    }
                }
                for (int m2 = 0; m2 < HEIGHT; m2++)
				{
					int counter2 = 0;
					for (int m = 0; m < WIDTH; m++)
					{
						if (Board[m2][m] == '1')
							counter2++;
						else
							counter2 = 0;
						if (counter2 == FIELDS)
						{
							Possibilities2ndPlayer++;
							counter2 = 0;
						}
					}
				}
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
                {
                    Board[i][j + p] = '1';
                }
            MoveDone = false;
        }
    }
    
    if (possibilities == 0)
    {
        InProgress = false;
        printf(".\n");
        return InProgress;
    }
    else //choosing the move 
    {
        int ChooseMove = RANDOM_NUMBER % possibilities;
        line = ArrOfPossibilities[ChooseMove * 2];
        column = ArrOfPossibilities[(ChooseMove * 2) + 1];

        for (int i = 0; i < FIELDS; i++) 
            Board[line][column + i] = '#';

        possibilities = 0;
    }
    if (InProgress)
    {
        printf("%c%c\n", (char)line + 97, (char)column + 65);
        line = 0;
        column = 0;
    }
    return InProgress;
}

int main()
{
    char Board[HEIGHT][WIDTH];
    InitArr(Board);
    bool InProgress = true;

    while (InProgress)
    {
        InProgress = FirstPlayerMove(Board, InProgress);

        if (InProgress)
        {
            InProgress = Player2MoveDone(Board, InProgress);
        }
    }
    return 0;
}