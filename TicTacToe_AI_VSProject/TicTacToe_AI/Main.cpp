#include <iostream>
using namespace std;

typedef enum { blank, player, machine } tValues;
const int N = 3;
typedef tValues tBoard [N][N];

void print ( const tBoard &board ) {
	cout << "###################" << endl;
	cout << "#     #     #     #" << endl;
	cout << "#  " << board[0][0] << "  #  " << board[0][1] << "  #  " << board[0][2] << "  #" << endl;
	cout << "#     #     #     #" << endl;
	cout << "###################" << endl;
	cout << "#     #     #     #" << endl;
	cout << "#  " << board[1][0] << "  #  " << board[1][1] << "  #  " << board[1][2] << "  #" << endl;
	cout << "#     #     #     #" << endl;
	cout << "###################" << endl;
	cout << "#     #     #     #" << endl;
	cout << "#  " << board[2][0] << "  #  " << board[2][1] << "  #  " << board[2][2] << "  #" << endl;
	cout << "#     #     #     #" << endl;
	cout << "###################" << endl;
}

int main () {

	tBoard board = { blank };
	print ( board );
	return 0;
}
