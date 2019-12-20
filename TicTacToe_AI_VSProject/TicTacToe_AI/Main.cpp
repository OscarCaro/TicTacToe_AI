#include <iostream>
#include <string>
using namespace std;

typedef enum { blank, player, machine } tValues;
const int N = 3;
typedef tValues tBoard[N][N];

// INTERFACE
void print ( const tBoard &board );
string valueToChar ( tValues value );

// USER INPUT
void askUser ( const tBoard &board, int &posX, int &posY );

// UTILITIES
bool isPosEmpty ( const tBoard &board, int posX, int posY );
void placePiece ( tBoard &board, int posX, int posY, tValues value);
bool isValidPos ( int posX, int posY );
bool isBoardFull ( const tBoard &board );
tValues hasSomeoneWin ( const tBoard &board );		// Return: blank = nobody, player = player...
bool isMachineWin ( const tBoard &board );
bool isPlayerWin ( const tBoard &board );

int main () {
	tBoard board = { blank };
	int posX, posY;

	while ( !isBoardFull ( board ) && !isMachineWin( board ) && !isPlayerWin( board )) {
		print ( board );
		askUser ( board, posX, posY );
		placePiece ( board, posX, posY, player );
	}

	print ( board );
	if ( isPlayerWin ( board ) ) {
		cout << "Player wins" << endl;
	}
	return 0;
}

// UTILITIES
bool isPosEmpty ( const tBoard &board, int posX, int posY ) {
	return (board[posY][posX] == blank);
}

void placePiece ( tBoard &board, int posX, int posY, tValues value ) {
	board[posY][posX] = value;
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


