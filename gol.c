#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#define X 80
#define Y 50

// Start with blank game board.
// Tell game which positions are initially 'alive'
// Based on rule, determine which cells will next be alive
// Update board

// 1-----2-----3
// |           |
// 8     9     4
// |           |
// 7-----6-----5

typedef struct {
  int board[X][Y];
  int neighbors[X][Y];
} board;

board *updateBoard(board *mainBoard) {
  int i = 0;
  int j = 0;
  int neighb;
  board *newBoard = (board *)malloc(sizeof(board));
  // Calculate neighbors
  while (i < Y) {
    j = 0;
    while (j < X) {
      // Case 1
      if (i == 0 && j == 0) {
	if (mainBoard->board[0][1] == 1) {
	  neighb++;
	} 
	if (mainBoard->board[1][0] == 1) {
	  neighb++;
	}
	if (mainBoard->board[1][1] == 1) {
	  neighb++;
	}
	// Case 2
      } 
      else if (j != X-1 && i == 0) {
	if (mainBoard->board[j-1][0] == 1) {
	  neighb++;
	}
	if (mainBoard->board[j+1][0] == 1) {
	  neighb++;
	}
	if (mainBoard->board[j][1] == 1) {
	  neighb++;
	}
	if (mainBoard->board[j-1][1] == 1) {
	  neighb++;
	}
	if (mainBoard->board[j+1][1] == 1) {
	  neighb++;
	}
	// Case 3
      } else if ( (j == X-1) && (i == 0)) {
	if (mainBoard->board[X-2][0] == 1) {
	  neighb++;
	}
	if (mainBoard->board[X-2][1] == 1) {
	  neighb++;
	}
	if (mainBoard->board[X-1][1] == 1) {
	  neighb++;
	}
	// Case 4
      } else if (i != Y-1 && j == X-1) {
	if (mainBoard->board[X-1][i-1] == 1) {
	  neighb++;
	}
	if (mainBoard->board[X-2][i-1] == 1) {
	  neighb++;
	}
	if (mainBoard->board[X-2][i] == 1) {
	  neighb++;
	}	
	if (mainBoard->board[X-2][i+1] == 1) {
	  neighb++;
	}
	if (mainBoard->board[X-1][i+1] == 1) {
	  neighb++;
	}
	// Case 5
      } else if (i == Y-1 && j == X-1) {
	if (mainBoard->board[X-1][Y-2] == 1) {
	  neighb++;
	}
	if (mainBoard->board[X-2][Y-2] == 1) {
	  neighb++;
	}
	if (mainBoard->board[X-2][Y-1] == 1) {
	  neighb++;
	}
	// Case 6
      } else if (i == Y-1 && j != X-1 && j != 0) {
	if (mainBoard->board[j-1][Y-1] == 1) {
	  neighb++;
	}
	if (mainBoard->board[j-1][Y-2] == 1) {
	  neighb++;
	}
	if (mainBoard->board[j][Y-2] == 1) {
	  neighb++;
	}	
	if (mainBoard->board[j+1][Y-2] == 1) {
	  neighb++;
	}
	if (mainBoard->board[j+1][Y-1] == 1) {
	  neighb++;
	}
	// Case 7
      } else if (i == Y-1 && j == 0) {
	if (mainBoard->board[0][Y-2] == 1) {
	  neighb++;
	}
	if (mainBoard->board[1][Y-2] == 1) {
	  neighb++;
	}
	if (mainBoard->board[1][Y-1] == 1) {
	  neighb++;
	} 
	// Case 8
      } else if (i != Y-1 && j == 0) {
	if (mainBoard->board[0][i-1] == 1) {
	  neighb++;
	}
	if (mainBoard->board[1][i-1] == 1) {
	  neighb++;
	}
	if (mainBoard->board[1][i] == 1) {
	  neighb++;
	}
	if (mainBoard->board[1][i+1] == 1) {
	  neighb++;
	}
	if (mainBoard->board[0][i+1] == 1) {
	  neighb++;
	}
	// Case 9
      } else {
	if (mainBoard->board[j-1][i+1] == 1) {
	  neighb++;
	}
	if (mainBoard->board[j][i+1] == 1) {
	  neighb++;
	}
	if (mainBoard->board[j+1][i+1] == 1) {
	  neighb++;
	}
	if (mainBoard->board[j+1][i] == 1) {
	  neighb++;
	}
	if (mainBoard->board[j+1][i-1] == 1) {
	  neighb++;
	}
	if (mainBoard->board[j][i-1] == 1) {
	  neighb++;
	}
	if (mainBoard->board[j-1][i-1] == 1) {
	  neighb++;
	}
	if (mainBoard->board[j-1][i] == 1) {
	  neighb++;
	}
      }
      mainBoard->neighbors[j][i] = neighb;
      //printf(" %d",mainBoard->neighbors[j][i]);
      neighb=0;
      j++;
    }
    //printf("\n");
    i++;
  }
  i = 0;
  j = 0;
  for (i; i<Y; i++) {
    for (j; j<X; j++) {
      // Cases:
      // (alive)
      // One neighbor -> die
      // Two, three neighbors -> live
      // Four+ neighbors -> die
      // (dead)
      // Three neighbors -> alive
      // Else -> stay dead
      if (mainBoard->board[j][i] == 1) {
	if (mainBoard->neighbors[j][i] == 1) {
	  newBoard->board[j][i] = 0;
	} else if ((mainBoard->neighbors[j][i] == 2) || (mainBoard->neighbors[j][i] == 3)) {
	  newBoard->board[j][i] = 1;
	} else {
	  newBoard->board[j][i] = 0;
	}
      } else if (mainBoard->board[j][i] == 0) {
        if (mainBoard->neighbors[j][i] == 3) {
	  newBoard->board[j][i] = 1;
	} else {
	  newBoard->board[j][i] = 0;
	}
      }
    }
    j = 0;
  }
  return newBoard;
}

void output(board *mainBoard) {
  int i = 0;
  int j = 0;
  for (i; i<Y; i++) {
    for (j; j<X; j++) {
      if (mainBoard->board[i][j] == 1) {
	printf("@ ");
      } else {
	printf("  ");
      }
    }
    printf("\n");
    j = 0;
  }
}


int main() {
  board *mBoard = (board *)malloc(sizeof(board));
  int i = 0;
  int j = 0;
  srand(time(NULL));
  for (i; i<Y; i++) {
    for (j; j<X; j++) {
      mBoard->board[j][i] = rand()%2;
    }
    j = 0;
  }
  int k = 0;
  output(mBoard);
  for (k; k<1000; k++) {
    printf("Generation: %d\n",k);
    mBoard = updateBoard(mBoard);
    output(mBoard);
    printf("\n");
    usleep(100000);
  }
}
