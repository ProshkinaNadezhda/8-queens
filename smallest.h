#include <list>
#include "board.h"

#define FREE_CELL 0

using namespace std;


list<int> workingnodes;
int p;

struct combination{
    int q;
    int board[SIZE][SIZE];
};


list<combination> findSmallest(int root[SIZE][SIZE], int nq, bool leader) {
    list<combination> box;
    int pp = 0;
    combination com;
    com.q = nq;
    memcpy(com.board, root, sizeof (int) * SIZE * SIZE);
    box.push_back(com);
    while(!box.empty()){
        int elem[SIZE][SIZE] = {FREE_CELL};
        int q = box.front().q;
        memcpy(elem, box.front().board, sizeof (int) * SIZE * SIZE);
        if (boardIsFull(elem))
            break;
        box.pop_front();
        for ( int i = 0; i < SIZE; i++ ) {
            for ( int k = 0; k < SIZE; k++ ) {
                if ( freeCell(k, i, elem) ) {
                    int leaf[SIZE][SIZE] = { FREE_CELL };
                    memcpy(leaf, elem, sizeof (int) * SIZE * SIZE);
                    markDirections(k, i, leaf);
                    if (q + 1 >= floor(SIZE / 4) && leader) {
                        int qq = q + 1;
                        int dest = (pp % (p - 1)) + 1;
                        workingnodes.push_back(dest);
                        ++pp;
                        MPI_Send (&leaf, sizeof(int) * SIZE * SIZE, MPI_CHAR, dest, 1, MPI_COMM_WORLD);
                        MPI_Send (&qq, 1, MPI_INT, dest, 1, MPI_COMM_WORLD);
                    } else {
                        combination com;
                        memcpy(com.board, leaf, sizeof (int) * SIZE * SIZE);
                        com.q = q + 1;
                        box.push_back(com);
                    }
                }
            }
        }
    }
    return box;
}


int findSmallestBoard(list<combination> list, int smallestBoard[SIZE][SIZE]){
    int smallest = SIZE * SIZE;
    for(std::list<combination>::iterator it = list.begin(); it != list.end(); it++) {
        if ((it)->q < smallest) {
            smallest = (it)->q;
            memcpy(smallestBoard, (it)->board, sizeof (int) * SIZE * SIZE);
        }
    }
    return smallest;
}