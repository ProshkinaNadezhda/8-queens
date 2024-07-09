#define QUEEN 2
#define BITE 1
#define SIZE 8


bool freeCell(int x, int y, int board[SIZE][SIZE]) {
    return board[x][y] == 0;
}


bool boardIsFull(int board[SIZE][SIZE]){
    for(int i = 0; i < SIZE; ++i)
        for (int k = 0; k < SIZE; ++k)
            if (board[i][k] == 0 )
                return false;
    return true;
}


void markDirections(int x, int y, int board[SIZE][SIZE]){
    for(int i = 0; i < SIZE; ++i){
        board[x][i] = BITE;
        board[i][y] = BITE;
    }
    int h = 1;
    int f1 = 0; int f2 = 0; int f3 = 0; int f4 = 0;
    while(1){
        if (y + h < SIZE and x + h < SIZE)
            board[x + h][y + h ] = BITE;
        else f1 = 1;
        if (y - h >= 0 and x - h >= 0)
            board[x - h][y - h ] = BITE;
        else f2 = 1;
        if (y + h < SIZE and x - h >= 0)
            board[x - h][y + h ] = BITE;
        else f3 = 1;
        if (y - h >= 0 and x + h < SIZE)
            board[x + h][y - h ] = BITE;
        else f4 = 1;
        if(f1 and f2 and f3 and f4) break;
        ++h;
    }
    board[x][y] = QUEEN;
}
