#include <curses.h>
#include <string>

using namespace std;

void rysuj()
{
    mvprintw( 4, 35, "#########\n");
    mvprintw( 5, 35, "#| | | |#\n");
    mvprintw( 6, 35, "#-------#\n");
    mvprintw( 7, 35, "#| | | |#\n");
    mvprintw( 8, 35, "#-------#\n");
    mvprintw( 9, 35, "#| | | |#\n");
    mvprintw( 10, 35,"#########\n");
}

bool sprawdz( char znak, int &tura )
{
    if( ((mvinch( 5, 37 ) == znak) && (mvinch( 5, 39 ) == znak) && (mvinch( 5, 41 ) == znak)) || //1poz
        ((mvinch( 6, 37 ) == znak) && (mvinch( 6, 39 ) == znak) && (mvinch( 6, 41 ) == znak)) || //2poz
        ((mvinch( 7, 37 ) == znak) && (mvinch( 7, 39 ) == znak) && (mvinch( 7, 41 ) == znak)) || //3poz
        ((mvinch( 5, 37 ) == znak) && (mvinch( 7, 37 ) == znak) && (mvinch( 9, 37 ) == znak)) || //1pion
        ((mvinch( 5, 39 ) == znak) && (mvinch( 7, 39 ) == znak) && (mvinch( 9, 39 ) == znak)) || //2pion
        ((mvinch( 5, 41 ) == znak) && (mvinch( 7, 41 ) == znak) && (mvinch( 9, 41 ) == znak)) || //3pion
        ((mvinch( 5, 37 ) == znak) && (mvinch( 7, 39 ) == znak) && (mvinch( 9, 41 ) == znak)) || //1ukos
        ((mvinch( 5, 41 ) == znak) && (mvinch( 7, 39 ) == znak) && (mvinch( 9, 37 ) == znak)) )  //2ukos
    {
        mvprintw( 15, 35, "wygral %c", znak);
        rysuj();
        tura = 1;
        return 1;
    }else
        return 0;
}

int main()
{
    initscr();

    printw( "\n=============================== Kolko i krzyzyk ===============================\n" );
    printw(   "--------------------------------------1.0--------------------------------------\n\n" );
    noecho();

    rysuj();

    move( 5, 37 );
    int x = 5;
    int y = 37;
    int tura = 1;

    for( ; ; )
    {
        if( tura != 10 )
        {
            sprawdz( 'x', tura );
            sprawdz( 'o', tura );
        }else
        {
            mvprintw( 15, 38, "pat");
            rysuj();
            tura = 1;
        }

        move( x, y ); //ruch

        char znak = getch();

        switch( znak )
        {
        case 'd':
            y+=2;
            break;
        case 'a':
            y-=2;
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
            switch( znak ) //cofniecie
            {
            case 'd':
                y-=2;
                break;
            case 'a':
                y+=2;
                break;
            case 's':
                x--;
                break;
            case 'w':
                x++;
                break;
            }
        }else
        {
            switch( znak )
            {
            case 's':
                x++;
                break;
            case 'w':
                x--;
                break;
            }
        }
        mvprintw( 23, 67, "%d, %d, %d, ", x, y, tura ); //wypisanie aktualnych wartosci
        if( tura % 2 == 0 )
            mvprintw( 23, 77, "o");
        else
            mvprintw( 23, 77, "x");
        move( x, y );

        if( znak == 'e' && (mvinch( x, y ) == ' ' ) ) //jesli pusty
        {
            if( tura % 2 == 0 ) //zmiana znaku co druga ture
                printw( "o");
            else
                printw( "x");
            tura++;
            mvprintw( 15, 35, "          ");
            move( x, y );
        }
    } //koniec petli

    getch();
    endwin();

    return 0;
}
