#include <string>
#include <curses.h>

void drawGrid()
{
    mvprintw( 4, 35, "#########\n" );
    mvprintw( 5, 35, "#| | | |#\n" );
    mvprintw( 6, 35, "#-------#\n" );
    mvprintw( 7, 35, "#| | | |#\n" );
    mvprintw( 8, 35, "#-------#\n" );
    mvprintw( 9, 35, "#| | | |#\n" );
    mvprintw( 10,35, "#########\n" );
}

bool checkForWin( char Char, int& turn )
{
    if( ( ( mvinch( 5, 37 ) == Char ) && ( mvinch( 5, 39 ) == Char) && ( mvinch( 5, 41 ) == Char ) ) || //1poz
        ( ( mvinch( 6, 37 ) == Char ) && ( mvinch( 6, 39 ) == Char) && ( mvinch( 6, 41 ) == Char ) ) || //2poz
        ( ( mvinch( 7, 37 ) == Char ) && ( mvinch( 7, 39 ) == Char) && ( mvinch( 7, 41 ) == Char ) ) || //3poz
        ( ( mvinch( 5, 37 ) == Char ) && ( mvinch( 7, 37 ) == Char) && ( mvinch( 9, 37 ) == Char ) ) || //1pion
        ( ( mvinch( 5, 39 ) == Char ) && ( mvinch( 7, 39 ) == Char) && ( mvinch( 9, 39 ) == Char ) ) || //2pion
        ( ( mvinch( 5, 41 ) == Char ) && ( mvinch( 7, 41 ) == Char) && ( mvinch( 9, 41 ) == Char ) ) || //3pion
        ( ( mvinch( 5, 37 ) == Char ) && ( mvinch( 7, 39 ) == Char) && ( mvinch( 9, 41 ) == Char ) ) || //1ukos
        ( ( mvinch( 5, 41 ) == Char ) && ( mvinch( 7, 39 ) == Char) && ( mvinch( 9, 37 ) == Char ) ) )  //2ukos
    {
        mvprintw( 15, 35, "%c won", Char );
        drawGrid();
        turn = 1;

        return 1;
    }
    else
        return 0;
}

int main()
{
    initscr();

    printw( "\n================================= Tic tac toe =================================\n" );
    printw(   "--------------------------------------1.0--------------------------------------\n\n" );
    noecho();

    drawGrid();

    move( 5, 37 );
    int x = 5;
    int y = 37;
    int turn = 1;

    while( true )
    {
        if( turn != 10 )
        {
            checkForWin( 'x', turn );
            checkForWin( 'o', turn );
        }
        else
        {
            mvprintw( 15, 38, "draw" );
            drawGrid();
            turn = 1;
        }

        move( x, y );

        char Char = getch();

        switch( Char )
        {
            case 'd':
                y += 2;
                break;
            case 'a':
                y -= 2;
                break;
            case 's':
                x++;
                break;
            case 'w':
                x--;
                break;
        }

        if( mvinch( x, y ) == '#' )
        {
            switch( Char )
            {
                case 'd':
                    y -= 2;
                    break;
                case 'a':
                    y += 2;
                    break;
                case 's':
                    x--;
                    break;
                case 'w':
                    x++;
                    break;
            }
        }
        else
        {
            switch( Char )
            {
                case 's':
                    x++;
                    break;
                case 'w':
                    x--;
                    break;
            }
        }

        mvprintw( 23, 67, "%d, %d, %d, ", x, y, turn );

        if( turn % 2 == 0 )
            mvprintw( 23, 77, "o" );
        else
            mvprintw( 23, 77, "x" );

        move( x, y );

        if( Char == 'e' && ( mvinch( x, y ) == ' ' ) )
        {
            if( turn % 2 == 0 )
                printw( "o" );
            else
                printw( "x" );

            mvprintw( 15, 35, "          ");
            move( x, y );
            turn++;
        }
    } //while

    getch();
    endwin();

    return 0;
}
