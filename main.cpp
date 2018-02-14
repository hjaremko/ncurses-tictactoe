#include <string>
#include <curses.h>

int centerPrint( int y, std::string String )
{
    int x = ( COLS - String.size() ) / 2;

    mvprintw( y, x, String.c_str() );

    return x;
}

int drawGrid()
{
    centerPrint( 4, "#########" );
    centerPrint( 5, "#| | | |#" );
    centerPrint( 6, "#|-+-+-|#" );
    centerPrint( 7, "#| | | |#" );
    centerPrint( 8, "#|-+-+-|#" );
    centerPrint( 9, "#| | | |#" );
    return 2 +
    centerPrint( 10,"#########" );
}

bool checkForWin( char Char, int& turn, const int x )
{
    if (( ( mvinch( 5, x )     == Char ) && ( mvinch( 5, x + 2 ) == Char ) && ( mvinch( 5, x + 4 ) == Char ) ) || //1poz
        ( ( mvinch( 7, x )     == Char ) && ( mvinch( 7, x + 2 ) == Char ) && ( mvinch( 7, x + 4 ) == Char ) ) || //2poz
        ( ( mvinch( 9, x )     == Char ) && ( mvinch( 9, x + 2 ) == Char ) && ( mvinch( 9, x + 4 ) == Char ) ) || //3poz
        ( ( mvinch( 5, x )     == Char ) && ( mvinch( 7, x )     == Char ) && ( mvinch( 9, x )     == Char ) ) || //1pion
        ( ( mvinch( 5, x + 2 ) == Char ) && ( mvinch( 7, x + 2 ) == Char ) && ( mvinch( 9, x + 2 ) == Char ) ) || //2pion
        ( ( mvinch( 5, x + 4 ) == Char ) && ( mvinch( 7, x + 4 ) == Char ) && ( mvinch( 9, x + 4 ) == Char ) ) || //3pion
        ( ( mvinch( 5, x )     == Char ) && ( mvinch( 7, x + 2 ) == Char ) && ( mvinch( 9, x + 4 ) == Char ) ) || //1ukos
        ( ( mvinch( 5, x + 4 ) == Char ) && ( mvinch( 7, x + 2 ) == Char ) && ( mvinch( 9, x )     == Char ) ) )  //2ukos
    {
        std::string str = "";
        str = str + Char + " won";
        centerPrint( 15, str );
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

    printw( "\n" );
    for ( int i = 0; i < COLS; i++ )
        printw( "=" );

    for ( int i = 0; i < COLS; i++ )
        printw( "-" );

    printw( "\n" );
    printw( "\n" );

    centerPrint( 1, " Tic Tac Toe " );
    centerPrint( 2, " 1.1 " );

    noecho();


    int turn = 1;
    int y = 5;
    int x = drawGrid();
    int x_ = x;

    move( y, x );

    while ( true )
    {
        if ( turn % 2 == 0 )
            centerPrint( 3, "o" );
        else
            centerPrint( 3, "x" );

        if ( turn != 10 )
        {
            checkForWin( 'x', turn, x_ );
            checkForWin( 'o', turn, x_ );
        }
        else
        {
            centerPrint( 15, "draw" );
            clear();
            drawGrid();
            turn = 1;
        }

        move( y, x );

        char Char = getch();

        switch ( Char )
        {
            case 'd':
                x += 2;
                break;
            case 'a':
                x -= 2;
                break;
            case 's':
                y++;
                break;
            case 'w':
                y--;
                break;
        }

        if ( mvinch( y, x ) == '#' )
        {
            switch ( Char )
            {
                case 'd':
                    x -= 2;
                    break;
                case 'a':
                    x += 2;
                    break;
                case 's':
                    y--;
                    break;
                case 'w':
                    y++;
                    break;
            }
        }
        else
        {
            switch ( Char )
            {
                case 's':
                    y++;
                    break;
                case 'w':
                    y--;
                    break;
            }
        }

        move( y, x );

        if ( Char == 'e' && ( mvinch( y, x ) == ' ' ) )
        {
            if ( turn % 2 == 0 )
                printw( "o" );
            else
                printw( "x" );

            centerPrint( 15, "          ");
            move( y, x );
            turn++;
        }
    } //while

    getch();
    endwin();

    return 0;
}
