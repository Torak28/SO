```
void Ncurses()
{
    initscr();
for (;;)
{

    refresh();
        for(int i=0; i<M ;i++)
        {
            for(int j=0; j<N; j++)
            {
                    move(i,j);
                    printw("%c", MACIERZ[i][j]);

            }
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));

}
    getch();
    endwin();                  // zakończenie tryby curses
}
```