#include <iostream>
#include <string>
using namespace std;

typedef enum { blank, player, machine } tValues;
const int N = 3;
typedef tValues tBoard[N][N];
typedef int tSol[N * N][3];		// Array of tuples of (posX,posY)
typedef int tMarker[N][N];


// INTERFACE
void print ( const tBoard &board );
string valueToChar ( tValues value );

// USER INPUT
void askUser ( const tBoard &board, int &posX, int &posY );

// UTILITIES
//int getArraySize ( tSol &sol );
void initializeBoardSol ( tBoard &boardSol, const tBoard &board );
void initializeArray ( tSol &arraySol );
void initializeMarkers ( const tBoard &board, tMarker &victories, tMarker &losses );
bool isPosEmpty ( const tBoard &board, int posX, int posY );
void placePiece ( tBoard &board, int posX, int posY, tValues value);
void placePieceInArray ( tSol &arraySol, int posX, int posY, tValues value, int k );
void removePiece ( tBoard &board, int posX, int posY );
void removePieceFromArray ( tSol &arraySol, int posX, int posY, int k);
bool isValidPos ( int posX, int posY );
bool isBoardFull ( const tBoard &board );
tValues hasSomeoneWin ( const tBoard &board );		// Return: blank = nobody, player = player...
bool isMachineWin ( const tBoard &board );
bool isPlayerWin ( const tBoard &board );
void getGreatestFromVictories ( const tMarker &marker, int &posX, int &posY, bool &isUnique );
void getLowestWithValueFromLosses ( const tMarker &victories, const tMarker &losses,
								    int value, int &posX, int &posY, bool &isUnique );


// ARTIFICIAL INTELLIGENCE
void computeAllPossibleMoves ( const tBoard &board, tMarker &victories, tMarker &losses );
void backtracking ( tBoard &boardSol, tSol &arraySol, int k, tMarker &victories, tMarker &losses );
void treatSol ( const tBoard &boardSol, const tSol &arraySol, tMarker &victories, tMarker &losses );
void decideNextMachMove ( const tBoard &board, int &posX, int &posY );

int main () {
	tBoard board = { blank };
	int posX, posY;

	while ( !isBoardFull ( board ) && !isMachineWin( board ) && !isPlayerWin( board )) {
		print ( board );
		askUser ( board, posX, posY );
		placePiece ( board, posX, posY, player );

		if ( !isBoardFull ( board ) && !isMachineWin ( board ) && !isPlayerWin ( board ) ) {
			decideNextMachMove ( board, posX, posY );
			placePiece ( board, posX, posY, machine );
		}
	}

	print ( board );
	if ( isPlayerWin ( board ) ) {
		cout << "Player wins" << endl;
	}
	return 0;
}

// ARTIFICIAL INTELLIGENCE

void decideNextMachMove ( const tBoard &board, int &posX, int &posY) {
	tMarker victories, losses;
	initializeMarkers ( board, victories, losses );

	computeAllPossibleMoves ( board, victories, losses );

	bool highestVictUnique;
	int highestVictPosX, highestVictPosY;
	getGreatestFromVictories ( victories, highestVictPosX, highestVictPosY, highestVictUnique );
	if ( highestVictUnique ) {
		posX = highestVictPosX;
		posY = highestVictPosY;
	}
	else {
		bool lowestLossesUnique;
		int lowestLossesPosX, lowestLossesPosY;
		getLowestWithValueFromLosses ( victories, losses, victories[highestVictPosY][highestVictPosX],
			lowestLossesPosX, lowestLossesPosY, lowestLossesUnique );
		if ( lowestLossesUnique ) {
			posX = lowestLossesPosX;
			posY = lowestLossesPosY;
		}
		else {
			// Pick one of the options because several have same num of vict and losses
			posX = lowestLossesPosX;
			posY = lowestLossesPosY;
		}
	}
}

void computeAllPossibleMoves ( const tBoard &board, tMarker &victories, tMarker &losses) {
	// 1: Create arraySol and initialize it to -1
	tSol arraySol;
	initializeArray ( arraySol );
	// 2: Create boardSol and initialize it to a copy of board
	tBoard boardSol;
	initializeBoardSol ( boardSol, board );	

	backtracking ( boardSol, arraySol, 0, victories, losses );	
}


void backtracking ( tBoard &boardSol, tSol &arraySol, int k, tMarker &victories, tMarker &losses ) {
	for ( int i = 0; i < N; i++ ) {
		for ( int j = 0; j < N; j++ ) {

			if ( isPosEmpty ( boardSol, i, j ) ) {
				placePiece ( boardSol, i, j, machine );
				placePieceInArray ( arraySol, i, j, machine, k );
				if ( hasSomeoneWin ( boardSol ) ) {
					treatSol ( boardSol, arraySol, victories, losses );
				}
				else if ( isBoardFull ( boardSol ) ) {
					// do nothing
				}
				else{
					backtracking ( boardSol, arraySol, k + 1, victories, losses );
				}
				removePiece ( boardSol, i, j );
				removePieceFromArray ( arraySol, i, j, k );
			}

		}
	}
}

void treatSol ( const tBoard &boardSol, const tSol &arraySol, tMarker &victories, tMarker &losses ) {
	if ( isPlayerWin ( boardSol ) ) {
		victories[ arraySol[0][0] ][ arraySol[0][1] ] += 1;
	}
	else if ( isMachineWin ( boardSol ) ) {
		losses[arraySol[0][0]][arraySol[0][1]] += 1;
	}
}




// UTILITIES

//int getArraySize ( tSol &sol ) {
//	int i = 0;
//	while ( i < N && sol[i][0] != -1 ) {
//		i++;
//	}
//	return 0;
//}

void initializeBoardSol ( tBoard &boardSol, const tBoard & board ) {
	for ( int i = 0; i < N; i++ ) {
		for ( int j = 0; j < N; j++ ) {
			boardSol[i][j] = board[i][j];
		}
	}
}

void initializeArray ( tSol &arraySol ) {
	for ( int i = 0; i < N * N; i++ ) {
		arraySol[i][0] = -1;
		arraySol[i][1] = -1;
		arraySol[i][2] = -1;
	}
}

void initializeMarkers ( const tBoard &board, tMarker &victories, tMarker &losses ) {
	for ( int i = 0; i < N; i++ ) {
		for ( int j = 0; j < N; j++ ) {
			if ( !isPosEmpty ( board, i, j ) ) {
				victories[i][j] = -1;
				losses[i][j] = -1;
			}
			else {
				victories[i][j] = 0;
				losses[i][j] = 0;
			}
		}
	}
}

bool isPosEmpty ( const tBoard &board, int posX, int posY ) {
	return (board[posY][posX] == blank);
}

void placePiece ( tBoard &board, int posX, int posY, tValues value ) {
	board[posY][posX] = value;
}

void placePieceInArray ( tSol &arraySol, int posX, int posY, tValues value, int k ) {
	//int size = getArraySize ( boardSol );
	arraySol[k][0] = posX;
	arraySol[k][1] = posY;
	arraySol[k][2] = value;		// Int representation of enum (blank = 0, player = 1...)
}

void removePiece ( tBoard &board, int posX, int posY ) {
	board[posY][posX] = blank;
}

void removePieceFromArray ( tSol &arraySol, int posX, int posY, int k ) {
	arraySol[k][0] = -1;
	arraySol[k][1] = -1;
	arraySol[k][2] = -1;
}

bool isValidPos ( int posX, int posY ) {
	return (posX >= 0 && posX < N && posY >= 0 && posY < N);
}

bool isBoardFull ( const tBoard &board ) {
	bool isFull = true;
	for ( int i = 0; i < N; i++ ) {
		for ( int j = 0; j < N; j++ ) {
			if ( isPosEmpty (board, i, j ) ) {
				isFull = false;
			}
		}
	}
	return isFull;
}

tValues hasSomeoneWin ( const tBoard &board ) {
	bool win = false;
	tValues whoWins = blank;

	int i = 0;
	while ( !win && i < N ) {
		// Check win by row
		bool diffValue = false;
		for ( int j = 0; j < N - 1; j++ ) {
			if ( board[i][j] != board[i][j + 1] ) {
				diffValue = true;
			}
		}
		if ( !diffValue && board[i][0] != blank) {
			win = true;
			whoWins = board[i][0];
		}
		i++;
	}

	i = 0;
	while ( !win && i < N ) {
		// Check win by column
		bool diffValue = false;
		for ( int j = 0; j < N - 1; j++ ) {
			if ( board[j][i] != board[j+1][i] ) {
				diffValue = true;
			}
		}
		if ( !diffValue && board[0][i] != blank ) {
			win = true;
			whoWins = board[0][i];
		}
		i++;
	}

	if ( !win ) {
		// Check win by descending diagonal
		bool diffValue = false;
		for ( int j = 0; j < N - 1; j++ ) {
			if ( board[j][j] != board[j + 1][j+1] ) {
				diffValue = true;
			}
		}
		if ( !diffValue && board[0][0] != blank ) {
			win = true;
			whoWins = board[0][0];
		}
	}

	if ( !win ) {
		// Check win by ascending diagonal
		bool diffValue = false;
		for ( int j = 0; j < N - 1; j++ ) {
			if ( board[N - 1 - j][j] != board[N - 2 - j][j + 1] ) {
				diffValue = true;
			}
		}
		if ( !diffValue && board[N - 1][0] != blank ) {
			win = true;
			whoWins = board[N - 1][0];
		}
	}

	return whoWins;
}

bool isMachineWin ( const tBoard &board ) {
	return (hasSomeoneWin ( board ) == machine);
}

bool isPlayerWin ( const tBoard &board ) {
	return (hasSomeoneWin ( board ) == player);
}

void getGreatestFromVictories ( const tMarker &victories, int &posX, int &posY, bool &isUnique) {
	int tmpGreatest = 0;
	int tmpGreatestPosX, tmpGreatestPosY;
	bool tmpIsUnique = true;

	for ( int i = 0; i < N; i++ ) {
		for ( int j = 0; j < N; j++ ) {
			if ( victories[i][j] > tmpGreatest ) {
				tmpIsUnique = true;
				tmpGreatest = victories[i][j];
				tmpGreatestPosX = j;
				tmpGreatestPosY = i;
			}
			else if ( victories[i][j] == tmpGreatest ) {
				tmpIsUnique = false;
				tmpGreatest = victories[i][j];
				tmpGreatestPosX = j;
				tmpGreatestPosY = i;
			}
		}
	}
	posX = tmpGreatestPosX;
	posY = tmpGreatestPosY;
	isUnique = tmpIsUnique;
}

void getLowestWithValueFromLosses ( const tMarker &victories, const tMarker &losses,
						   int value, int &posX, int &posY, bool &isUnique ) {
	int tmpLowest = 10000;		//arbitrary high number
	int tmpLowestPosX, tmpLowestPosY;
	bool tmpIsUnique = true;

	for ( int i = 0; i < N; i++ ) {
		for ( int j = 0; j < N; j++ ) {
			if ( victories[i][j] == value ) {
				if ( losses[i][j] < tmpLowest ) {
					tmpIsUnique = true;
					tmpLowest = losses[i][j];
					tmpLowestPosX = j;
					tmpLowestPosY = i;
				}
				else if ( losses[i][j] == tmpLowest ) {
					tmpIsUnique = false;
					tmpLowest = losses[i][j];
					tmpLowestPosX = j;
					tmpLowestPosY = i;
				}
			}
		}
	}
	posX = tmpLowestPosX;
	posY = tmpLowestPosY;
	isUnique = tmpIsUnique;

}



// USER INPUT
void askUser ( const tBoard &board, int &posX, int &posY ) {
	bool ok = true;
	cout << endl << "Your turn. Place piece at..." << endl;
	
	do {
		cout << "X position: ";
		cin >> posX;
		posX--;		// array vs human
		cout << "Y position: ";
		cin >> posY;
		posY--;		// array vs human
		if ( !isValidPos ( posX, posY ) ) {
			cout << "That position is out of the board" << endl;
			ok = false;
		}
		else if ( !isPosEmpty ( board, posX, posY ) ) {
			cout << "That position is already occupied" << endl;
			ok = false;
		}
	} while ( !ok );

	cout << endl;
}


// INTERFACE
void print ( const tBoard &board ) {
	cout << "Player:   " << valueToChar ( player ) << endl;
	cout << "Machine:  " << valueToChar ( machine ) << endl << endl;


	cout << "      X1     X2    X3  " << endl;
	cout << "    ###################" << endl;
	cout << "    #     #     #     #" << endl;
	cout << " Y1 #  " << valueToChar ( board[0][0] ) << "  #  " << valueToChar ( board[0][1] ) << "  #  " << valueToChar ( board[0][2] ) << "  #" << endl;
	cout << "    #     #     #     #" << endl;
	cout << "    ###################" << endl;
	cout << "    #     #     #     #" << endl;
	cout << " Y2 #  " << valueToChar ( board[1][0] ) << "  #  " << valueToChar ( board[1][1] ) << "  #  " << valueToChar ( board[1][2] ) << "  #" << endl;
	cout << "    #     #     #     #" << endl;
	cout << "    ###################" << endl;
	cout << "    #     #     #     #" << endl;
	cout << " Y3 #  " << valueToChar ( board[2][0] ) << "  #  " << valueToChar ( board[2][1] ) << "  #  " << valueToChar ( board[2][2] ) << "  #" << endl;
	cout << "    #     #     #     #" << endl;
	cout << "    ###################" << endl;
}

string valueToChar ( tValues value ) {
	string str = "";
	switch ( value ) {
		case blank:
			str = " ";
			break;
		case player:
			str = "O";
			break;
		case machine:
			str = "X";
			break;
	}
	return str;
}


