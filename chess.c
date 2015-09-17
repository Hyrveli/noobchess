// my first attempt at a simple gui-less chess program
#include <stdio.h>
#include <search.h>
#include <string.h>
#include <stdbool.h>

int main()
{
	int i, j;
	bool wturn = 1;

	// The initial position of the chessboard, note that all elements in the
	// array are 2 characters long.
	
	char *board[8][8] = {
	{"Rb", "Nb", "Bb", "Kb", "Qb", "Bb", "Nb", "Rb"} ,
	{"pb", "pb", "pb", "pb", "pb", "pb", "pb", "pb"} ,
	{". ", ". ", ". ", ". ", ". ", ". ", ". ", ". "} ,
	{". ", ". ", ". ", ". ", ". ", ". ", ". ", ". "} ,
	{". ", ". ", ". ", ". ", ". ", ". ", ". ", ". "} ,
	{". ", ". ", ". ", ". ", ". ", ". ", ". ", ". "} ,
	{"pw", "pw", "pw", "pw", "pw", "pw", "pw", "pw"} ,
	{"Rw", "Nw", "Bw", "Qw", "Kw", "Bw", "Nw", "Rw"} ,
	};

	// This map-array will later be used to enable moving the pieces via
	// standard chess notation.
	
	char *map[8][8] = {
	{"a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8"} ,
	{"a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7"} ,
	{"a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6"} ,
	{"a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5"} ,
	{"a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4"} ,
	{"a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3"} ,
	{"a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2"} ,
	{"a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1"} ,
	};

	// This function is used to print the current board position

	void boardprint() {
	
		for (i = 0; i < 8; i++) {
			for (j = 0; j < 8; j++) {
			
				char* str = board[i][j];
				char c = str[1];

				// The weird numbers are ANSI color codes

				if (c == 'b') {
					printf("\033[01;34m%.1s ", board[i][j]);
					}
				if (c == 'w') {
					printf("\033[01;33m%.1s ", board[i][j]);
					}
				if (c == ' ') {
					printf("\033[01;30m%.1s ", board[i][j]);
					}
			}
			printf("\n");
		}
	}

	int squarexfinder(char*square) {
		int x, y;
		for (x = 0; x < 8; x++) {
			for (y = 0; y < 8; y++) {

				if (strncmp(square, map[x][y], 2) == 0) {
					return x;
					}

				}
			}
		}

	int squareyfinder(char*square) {
                int x, y;
                for (x = 0; x < 8; x++) {
                        for (y = 0; y < 8; y++) {

                                if (strncmp(square, map[x][y], 2) == 0) {
                                       return y;
                                        }

                                }
                        }
                }

	
	void movepiece(char* from, char* to) {

		int fromx = squarexfinder(from);
		int fromy = squareyfinder(from);

		int tox = squarexfinder(to);
		int toy = squareyfinder(to);

		char* str1 = board[fromx][fromy];
		char* str2 = board[tox][toy];
		char s1 = str1[1];
		char s2 = str2[1];

		if (s1 == '.') {
			printf("No piece to move on %s\n", map[fromx][fromy]);
			}
		
		if (s1 == 'w' && s2 == 'w') {
			printf("Can not move white piece on %s on top of white piece on %s\n", 
			map[fromx][fromy], map[tox][toy]);
			}

		if (s1 == 'b' && s2 == 'b') {
			printf("Can not move black piece on %s on top of black piece on %s\n",
			map[fromx][fromy], map[tox][toy]);
			}

		if ((s1 == 'w' && s2 == 'b') || (s1 == 'b' && s2 == 'w')) {
			board[fromx][fromy] = ". ";
			board[tox][toy] = str1;
			}

		else { 
                        board[fromx][fromy] = ". ";
                        board[tox][toy] = str1;

		}
	}

	char whatpiece(char* square) {

		if (square[0] =='.') {
			printf("No piece on %s", square);
			}
	
		else {
			return square[0];
			}
		}

	bool checksquare(char* square) {

		int x = squarexfinder(square);
		int y = squareyfinder(square);

		char* targetsq = board[x][y]; 


		if (targetsq[1] == 'w' || targetsq[1] == 'b') {
			return 1;
			}
		

		else {
			return 0;
			}
		}

	char worb(char* square) {

		int x = squarexfinder(square);
		int y = squareyfinder(square);

		char* targetsq = board[x][y];

		return targetsq[1];
		}

	bool isonline(char* to, char* from) {

		if (to[0] == from[0] || to[1] == from[1]) {
			return 1;
			}
		else {
			return 0;
			}
		}

	bool isondiag(char* to, char* from) {

		int fromx = squarexfinder(from);
		int fromy = squareyfinder(from);

		int tox = squarexfinder(to);
		int toy = squareyfinder(to);

		if (fromx - tox == fromy - toy || fromx - tox == toy - fromy) {
			return 1;
			}

		else {
			return 0;
			}

		}

		bool diaglooper(int tox, int toy, int fromx, bool reverse) {

			if (reverse == 0) {

				while(tox+1 != fromx) {
					tox = tox+1;
					toy = toy+1;

					if (checksquare(map[tox][toy]) == 1) {
						printf("Something found on %i %i", tox, toy);
						return 1;
						}
					 }
				return 0;
				}

			if (reverse == 1) {

				while (tox-1 != fromx) {
					tox = tox-1;
					toy = toy+1;

					if (checksquare(map[tox][toy]) == 1) {
						printf("Something found on %i %i", tox, toy);
						return 1;
						}
					}
				return 0;

			}
		}

		bool linelooper(int tox, int toy, int xory, bool direction) {

			if (direction == 0) {

				while(xory != tox){
					tox = tox+1;

					if (checksquare(map[tox][toy]) == 1) {
						printf("Something found on %i %i", tox, toy);
						return 1;
						}
					
					}
				return 0;
				}

			if (direction == 1) {
	
				while (xory != toy) {
					toy = toy+1;

					if (checksquare(map[tox][toy]) == 1) {
						printf("Something found on %i %i", tox, toy);
						return 1;
						}
					}
				return 0;
			}
		}	

		bool isbetween(char* to, char* from) {

			int fromx = squarexfinder(from);
			int fromy = squareyfinder(from);

			int tox = squarexfinder(to);
			int toy = squareyfinder(to);

			if (isondiag(to,from) == 1 && tox < fromx && toy < fromy) {
			
				if (diaglooper(tox, toy, fromx, 0) == 1) {
					return 1;
					}
				else {
					printf("Nothing found between %s and %s", to, from);
					return 0;
					}
			}

			if (isondiag(to,from) == 1 && fromx < tox && fromy < toy) {
				
				if (diaglooper(fromx, fromy, tox, 0) == 1) {
					return 1;
					}

				else {
					printf("Nothing found between %s and %s", to, from);
					return 0;
					}
			}
			
			if (isondiag(to,from) == 1 && tox > fromx && fromy > toy) {

                                if (diaglooper(tox, toy, fromx, 1) == 1) {
                                        return 1;
                                        }

                                else {
                                        printf("Nothing found between %s and %s", to, from);
                                        return 0;
                                        }
			}

			if (isondiag(to,from) == 1 && tox < fromx && toy > fromy) {

                                if (diaglooper(fromx, fromy, tox, 1) == 1) {
                                        return 1;
                                        }

                                else {
                                        printf("Nothing found between %s and %s", to, from);
                                        return 0;
                                        }

			}

		}


	void turn (char* move) {

		int x = squarexfinder(move);
		int y = squareyfinder(move);

		if ((worb(map[x][y]) == 'w' && wturn == 1) || (worb(map[x][y]) == 'b' && wturn == 0))
			{
			printf("Illegal move");
			}
			
		if (strlen(move) == 2 && move[1] == '4' && wturn == 1) {
			char* sqtocheck = map[x+1][y];
			bool check = checksquare(sqtocheck);

			if (check == 1) {
				movepiece(sqtocheck, move);
				}
			
			if (check == 0) {
				char* sqtocheck = map[x+2][y];
				bool check = checksquare(sqtocheck);
				
				if (check == 1) {
					movepiece(sqtocheck, move);
					}

				if (check == 0) {
					printf("Illegal move");
					}
				}
			}

		if (strlen(move) == 2 && move[1] == '3' && wturn == 1 && board[x+1][y] == "pw") {
			char* from = map[x+1][y];
			movepiece(from, move);
			}


		}

	boardprint();
	isbetween("h3", "e6");

	return 0;


}

