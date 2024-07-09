#include "mpi.h"
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <time.h>
#include "vector"
#include "smallest.h"
#include "graphics.h"

using namespace std;


list<combination> stack;


int flag;


int main(int argc, char *argv[])
{
    int my_rank;
    int source;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    if (my_rank != 0){
        while(true) {
            MPI_Iprobe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &flag, &status);
            if (status.MPI_TAG == 5)
                break;
            else if (status.MPI_TAG == 1) {
                int root[SIZE][SIZE] = {FREE_CELL};
                int q;
                MPI_Recv(&root, sizeof(int) * SIZE * SIZE, MPI_CHAR, 0, 1, MPI_COMM_WORLD, &status);
                MPI_Recv(&q, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);

                stack = findSmallest(root, q, false);
                int smallestBoard[SIZE][SIZE] = {FREE_CELL};
                int smallest = findSmallestBoard(stack, smallestBoard);
                MPI_Send(&smallestBoard, sizeof(int) * SIZE * SIZE, MPI_CHAR, 0, 3, MPI_COMM_WORLD);
                MPI_Send(&smallest, 1, MPI_INT, 0, 4, MPI_COMM_WORLD);
            }
        }
    } else {
        clock_t tStart = clock();
        cout << "There are " << p << " processes" << endl;
        int root[SIZE][SIZE] = {FREE_CELL};

        int qq = 0;

        vector<vector<int>> data = PrintBoardBeg();
        for(int i = 0; i < data.size(); ++i){
            ++qq;
            int x = data[i][0];
            int y = data[i][1];
            markDirections(x, y, root);
        }

        stack = findSmallest(root, qq, true);
        int smallestBoard[SIZE][SIZE] = {FREE_CELL};
        int smallest = SIZE * SIZE;
        int elem[SIZE][SIZE] = {FREE_CELL};
        int q = 0;
        if (workingnodes.size() == 0)
            smallest = findSmallestBoard(stack, smallestBoard);

        while (workingnodes.size() != 0) {
            source = workingnodes.front();
            workingnodes.pop_front();
            MPI_Recv(&elem, sizeof(int) * SIZE * SIZE, MPI_CHAR, source, 3, MPI_COMM_WORLD, &status);
            MPI_Recv(&q, 1, MPI_INT, source, 4, MPI_COMM_WORLD, &status);

            if (q < smallest) {
                memcpy(smallestBoard, elem, sizeof(int) * SIZE * SIZE);
                smallest = q;
            }
        }
        cout << "FINISH!" << endl;
        int w = 1;
        for(int child = 1; child < p; ++child)
            MPI_Send(&w, 1, MPI_INT, child, 5, MPI_COMM_WORLD);

        cout << "quantity of queens:" << smallest << endl;
        cout << "Time taken: " << (double) (clock() - tStart) / CLOCKS_PER_SEC << endl;

        PrintBoardFin(smallestBoard);
    }
    MPI_Finalize();
    return 0;
}

