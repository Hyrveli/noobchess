// my first attempt at a simple gui-less chess program
#include <stdio.h>
#include <search.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

int main()
{
	int i, j;
	bool wturn = 1;

	// The initial position of the chessboard, note that all elements in the
	// array are 2 characters long.
	
	char *board[8][8] = {
	{"Rb", "Nb", "Bb", "Qb", "Kb", "Bb", "Nb", "Rb"} ,
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

				if (c == 'b')
					printf("\033[01;34m%.1s ", board[i][j]);
					
                else if (c == 'w') 
					printf("\033[01;33m%.1s ", board[i][j]);
					
                else if (c == ' ') 
					printf("\033[01;30m%.1s ", board[i][j]);
					
			}
			printf("\n");
		}
	}

	int squarexfinder(char*square) {
		int x, y;
		for (x = 0; x < 8; x++) {
			for (y = 0; y < 8; y++) {

				if (strncmp(square, map[x][y], 2) == 0) 
					return x;
					

				}
			}
		}

	int squareyfinder(char*square) {
        int x, y;
        for (x = 0; x < 8; x++) {
            for (y = 0; y < 8; y++) {
                if (strncmp(square, map[x][y], 2) == 0) 
                    return y;
                

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

		if (s1 == '.') 
			printf("No piece to move on %s\n", map[fromx][fromy]);
			
		
        else if (s1 == 'w' && s2 == 'w') {
			printf("Can not move white piece on %s on top of white piece on %s\n", 
			map[fromx][fromy], map[tox][toy]);
			}

        else if (s1 == 'b' && s2 == 'b') {
			printf("Can not move black piece on %s on top of black piece on %s\n",
			map[fromx][fromy], map[tox][toy]);
			}

        else if ((s1 == 'w' && s2 == 'b') || (s1 == 'b' && s2 == 'w')) {
			board[fromx][fromy] = ". ";
			board[tox][toy] = str1;
			}

		else { 
            board[fromx][fromy] = ". ";
            board[tox][toy] = str1;

		}
	}

	char whatpiece(char* square) {

		if (square[0] =='.') 
			printf("No piece on %s", square);
			
	
		else 
			return square[0];
			
		}

	bool checksquare(char* square) {

		int x = squarexfinder(square);
		int y = squareyfinder(square);

		char* targetsq = board[x][y]; 


		if (targetsq[1] == 'w' || targetsq[1] == 'b') 
			return 1;
			
		

		else 
			return 0;
			
		}

	char worb(char* square) {

		int x = squarexfinder(square);
		int y = squareyfinder(square);

		char* targetsq = board[x][y];

		return targetsq[1];
		}

	bool isonline(char* to, char* from) {

		if (to[0] == from[0] || to[1] == from[1]) 
			return 1;
			
		else 
			return 0;
			
		}

	bool isondiag(char* to, char* from) {

		int fromx = squarexfinder(from);
		int fromy = squareyfinder(from);

		int tox = squarexfinder(to);
		int toy = squareyfinder(to);

		if (fromx - tox == fromy - toy || fromx - tox == toy - fromy) 
			return 1;
			

		else 
			return 0;
			

		}

		bool diaglooper(int tox, int toy, int fromx, bool reverse) {

			if (reverse == 0) {

				while(tox+1 != fromx) {
					tox = tox+1;
					toy = toy+1;

					if (checksquare(map[tox][toy]) == 1) 
						return 1;
						
					 }
				return 0;
				}

			if (reverse == 1) {

				while (tox-1 != fromx) {
					tox = tox-1;
					toy = toy+1;

					if (checksquare(map[tox][toy]) == 1) 
						return 1;
						
					}
				return 0;

			}
		}

		bool linelooper(int tox, int toy, int xory, bool direction) {

			if (direction == 0) {

				while(xory != tox){
					tox = tox+1;

					if (checksquare(map[tox][toy]) == 1) {
						return 1;
						}
					
					}
				return 0;
				}

			if (direction == 1) {
	
				while (xory != toy) {
					toy = toy-1;

					if (checksquare(map[tox][toy]) == 1) 
						return 1;
						
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
			
				if (diaglooper(tox, toy, fromx, 0) == 1) 
					return 1;
					
				else 
					return 0;
					
			}

            else if (isondiag(to,from) == 1 && fromx < tox && fromy < toy) {
				
				if (diaglooper(fromx, fromy, tox, 0) == 1) 
					return 1;
					

				else 
					return 0;
					
			}
			
            else if (isondiag(to,from) == 1 && tox > fromx && fromy > toy) {

                if (diaglooper(tox, toy, fromx, 1) == 1) 
                    return 1;
                                        

                else 
                    return 0;
                                        
			}

            else if (isondiag(to,from) == 1 && tox < fromx && toy > fromy) {

                if (diaglooper(fromx, fromy, tox, 1) == 1) 
                    return 1;
                                        

                else 
                    return 0;
                                        

			}

            else if (isonline(to,from) == 1 &&  fromx > tox) {

                if (linelooper(tox, toy, fromx, 0) == 1)
                   return 1;
                

                else {
                    printf("Nothing found between %s and %s\n", to, from);
                    return 0;
                }
            }

            else if (isonline(to,from) == 1 && tox > fromx) {

                if (linelooper(fromx, toy, tox, 0) == 1)
                    return 1;
                

                else 
                    return 0;
                
            }

            else if (isonline(to,from) == 1 && fromy > toy){

                if (linelooper(tox, fromy, toy, 1) == 1) 
                    return 1;
                

                else 
                    return 0;
                
            }

            else if (isonline(to,from) == 1 && toy > fromy) {

                if (linelooper(tox, toy, fromy, 1) == 1) 
                    return 1;
                

                else 
                    return 0;
                
            }

            else
                printf("%s and %s are not on the same line or diagonal\n", to, from);
            
            

		}


	bool isknight(char* square, char* knight) {

		int x = squarexfinder(square);
		int y = squareyfinder(square);

		char* targetsq = board[x][y]; 

		if (targetsq == knight)
			return 1;
			
		else 
			return 0;
			
		}
       

    char* knightlooper(char* move, char* knight) {

        int count = 0;
        int foundx = 0;
        int foundy = 0;
        
        int x = squarexfinder(move);
        int y = squareyfinder(move);

        if (x-2 >= 0 && y+1 <= 7 && isknight(map[x-2][y+1], knight) == 1) {
            count++;
            foundx = x-2;
            foundy = y+1;
        }

        
        if (x-2 >= 0 && y-1 >= 0 && isknight(map[x-2][y-1], knight) == 1){
            count++;
            foundx = x-2;
            foundy = y-1;
        }
        
        if (x+2 <= 7 && y+1 <= 7 && isknight(map[x+2][y+1], knight) == 1){
            count++;
            foundx = x+2;
            foundy = y+1;
        }

        if (x+2 <= 7 && y-1 >= 0 && isknight(map[x+2][y-1], knight) == 1){
            count++;
            foundx = x+2;
            foundy = y-1;
        }

        if (x-1 >= 0 && y+2 <= 7 && isknight(map[x-1][y+2], knight) == 1){
            count++;
            foundx = x-1;
            foundy = y+2;
        }

        if (x-1 >= 0 && y-2 >= 0 && isknight(map[x-1][y-2], knight) == 1){
            count++;
            foundx = x-1;
            foundy = y-2;
        }

        if (x+1 <= 7 && y+2 <= 7 && isknight(map[x+1][y+2], knight) == 1){
            count++;
            foundx = x+1;
            foundx = y+2;
        }

        if (x+1 <= 7 && y-2 >= 0 && isknight(map[x+1][y-2], knight) == 1){
            count++;
            foundx = x+1;
            foundy = y-2;
        }

        if (count == 0)
            return "0";

        else if (count == 1)
            return map[foundx][foundy];

        else if (count > 1)
            return "1";
        
    }
       
    char* bishoplooper(char* square){

        int count = 0;
        int foundx = 0;
        int foundy = 0;

        int x = squarexfinder(square);
        int y = squareyfinder(square);

        int i = j = 0;

        for (i = 0; i < 8; i++){
            for (j = 0; j < 8; j++){
                char* status = board[i][j];

                if (wturn == 1 && isondiag(square, map[i][j]) == 1 && status == "Bw"
                    && isbetween(square, map[i][j]) == 0){
                    count++;
                    foundx = i;
                    foundy = j;
                }

                else if (wturn == 0 && isondiag(square, map[i][j]) == 1 && status == "Bb"
                    && isbetween(square, map[i][j]) == 0){
                    count++;
                    foundx = i;
                    foundy = j;
                }
            }
        }
        
        if (count == 0)
            return "-1";

        else if (count == 1)
            return map[foundx][foundy];

        else if (count > 1)
            return "0";

    }

    char* rooklooper(char* square){

        int count = 0;
        int foundx = 0;
        int foundy = 0;

        int x = squarexfinder(square);
        int y = squareyfinder(square);

        int i = j = 0;

        for (i = 0; i < 8; i++){
            for (j = 0; j < 8; j++){
                char* status = board[i][j];

                if (wturn == 1 && isonline(square, map[i][j]) == 1 && status == "Rw"
                    && isbetween(square, map[i][j]) == 0){
                    count++;
                    foundx = i;
                    foundy = j;
                }

                else if (wturn == 0 && isonline(square, map[i][j]) == 1 && status == "Rb"
                    && isbetween(square, map[i][j]) == 0){
                    count++;
                    foundx = i;
                    foundy = j;
                }
            }
        }
        
        if (count == 0)
            return "-1";

        else if (count == 1)
            return map[foundx][foundy];

        else if (count > 1)
            return "0";

    }
 
    char* queenlooper(char* square){

        int count = 0;
        int foundx = 0;
        int foundy = 0;

        int x = squarexfinder(square);
        int y = squareyfinder(square);

        int i = j = 0;

        for (i = 0; i < 8; i++){
            for (j = 0; j < 8; j++){
                char* status = board[i][j];

                if (wturn == 1 && status == "Qw" && isbetween(square, map[i][j]) == 0 &&
                    (isonline(square, map[i][j]) == 1 || isondiag(square, map[i][j]) == 1)){
                    count++;
                    foundx = i;
                    foundy = j;
                }

                else if (wturn == 0 && status == "Qb" && isbetween(square, map[i][j]) == 0 &&
                    (isonline(square, map[i][j]) == 1 || isondiag(square, map[i][j]) == 1)){
                    count++;
                    foundx = i;
                    foundy = j;
                }
            }
        }
        
        if (count == 0)
            return "-1";

        else if (count == 1)
            return map[foundx][foundy];

        else if (count > 1)
            return "0";

    }

    int arraydistance(char* to, char* from){

        int fromx = squarexfinder(from);
        int fromy = squareyfinder(from);

        int tox = squarexfinder(to);
        int toy = squareyfinder(to);

        if (isonline(to, from) == 1) 
            return abs((fromx - tox) + (toy - fromy));
        
        else if (isondiag(to, from) == 1)
            return abs(tox - fromx);

        else
            return -1;
    }

    char* kinglooper(char* square) {
        
        int x = squarexfinder(square);
        int y = squareyfinder(square);

        int i = j = 0;

        for (i = 0; i < 8; i++) {
            for (j = 0; j < 8; j++) {

                if (wturn == 1 && arraydistance(map[x][y], map[i][j]) == 1 &&
                    board[i][j] == "Kw")
                    return map[i][j];

                else if (wturn == 0 && arraydistance(map[x][y], map[i][j]) == 1 &&
                         board[i][j] == "Kb")
                    return map[i][j];

            }
        }

        return "-1";

    }

    int kingfinder(bool xory) {

        int i, j;

        if (wturn == 1 && xory == 0) {
            for (i = 0; i < 8; i++) {
                for (j = 0; j < 8; j++) {

                   if (strncmp("Kw", board[i][j], 2) == 0)
                       return i;
                }
            }
        }

        else if (wturn == 1 && xory == 1) {
            for (i = 0; i < 8; i++) {
                for (j = 0; j < 8; j++) {

                   if (strncmp("Kw", board[i][j], 2) == 0)
                       return j;
                }
            }
        }

        else if (wturn == 0 && xory == 0) {
            for (i = 0; i < 8; i++) {
                for (j = 0; j < 8; j++) {

                   if (strncmp("Kb", board[i][j], 2) == 0)
                       return i;
                }
            }
        }
        
        else if (wturn == 0 && xory == 1) {
            for (i = 0; i < 8; i++) {
                for (j = 0; j < 8; j++) {

                   if (strncmp("Kb", board[i][j], 2) == 0)
                       return j;
                }
            }
        }

    }

    bool checkcheck() {

        int kingx = kingfinder(0);
        int kingy = kingfinder(1);

        if (wturn == 1) {

            int i, j;

            for (i = 0; i < 8; i++) {
                for (j = 0; j < 8; j++) {

                    if (isonline(map[kingx][kingy], map[i][j]) == 1 &&
                        isbetween(map[kingx][kingy], map[i][j]) == 0 &&
                        (board[i][j] == "Qb" || board[i][j] == "Rb"))
                        return 1;

                    if (isondiag(map[kingx][kingy], map[i][j]) == 1 &&
                        isbetween(map[kingx][kingy], map[i][j]) == 0 &&
                        (board[i][j] == "Qb" || board[i][j] == "Bb"))
                        return 1;

                    if (board[kingx-1][kingy-1] == "pb" || board[kingx-1][kingy+1] == "pb")
                        return 1;
                    
                    if (arraydistance(map[kingx][kingy], map[i][j]) == 1 &&
                        board[i][j] == "Kb")
                        return 1;

                    if (knightlooper(map[kingx][kingy], "Nb") != "0")
                        return 1;
                }
            }

            return 0;
        }


        else if (wturn == 0) {

            int i, j;

            for (i = 0; i < 8; i++) {
                for (j = 0; j < 8; j++) {

                    if (isonline(map[kingx][kingy], map[i][j]) == 1 &&
                        isbetween(map[kingx][kingy], map[i][j]) == 0 &&
                        (board[i][j] == "Qw" || board[i][j] == "Rw"))
                        return 1;

                    if (isondiag(map[kingx][kingy], map[i][j]) == 1 &&
                        isbetween(map[kingx][kingy], map[i][j]) == 0 &&
                        (board[i][j] == "Qw" || board[i][j] == "Bw"))
                        return 1;

                    if (board[kingx+1][kingy-1] == "pw" || board[kingx+1][kingy+1] == "pw")
                        return 1;
                    
                    if (arraydistance(map[kingx][kingy], map[i][j]) == 1 &&
                        board[i][j] == "Kw")
                        return 1;

                    if (knightlooper(map[kingx][kingy], "Nw") != "0")
                        return 1;
                }
            }

            return 0;
        }
    }

    void bishopmover(char* square) {

            if (bishoplooper(square) == "-1")
                printf("No bishop can move to %s\n", square);
            

            else if (bishoplooper(square) == "0")
                printf("Specify which bishop to move to %s\n", square);
            

            else {
                char* bishopis = bishoplooper(square);
                movepiece(bishopis, square);
            }
        }

    void rookmover(char* square) {

            if (rooklooper(square) == "-1")
                printf("No rook can move to %s\n", square);
            

            else if (rooklooper(square) == "0")
                printf("Specify which rook to move to %s\n", square);
            

            else {
                char* rookis = rooklooper(square);
                movepiece(rookis, square);
            }
        }

    void queenmover(char* square) {

            if (queenlooper(square) == "-1")
                printf("No queen can move to %s\n", square);

            else if (queenlooper(square) == "0")
                printf("Specify which queen to move to %s\n", square);

            else {
                char* queenis = queenlooper(square);
                movepiece(queenis, square);
            }
        }

    void kingmover(char* square) {

            if (kinglooper(square) == "-1")
                printf("No king can move to %s\n", square);

            else {
                char* kingis = kinglooper(square);
                movepiece(kingis, square);
            }
    }

    void knightmover(char* square, char* knight) {

            if (knightlooper(square, knight) == "0") 
                printf("Illegal move\n");

            else if (knightlooper(square, knight) == "1")
                printf("Specify which knight to move\n");
            
            else {
                char* knightis = knightlooper(square, knight);
                movepiece(knightis, square);
            }
    }

    void turn (char* move) {

        int len = strlen(move);

        char square[3];
        strncpy(square, &move[len-2], 2);
        square[2] = '\0';

        int x = squarexfinder(square);
		int y = squareyfinder(square);

		if ((worb(map[x][y]) == 'w' && wturn == 1) || (worb(map[x][y]) == 'b' && wturn == 0))
			printf("Illegal move");
			
			
        else if (strlen(move) == 2 && move[1] == '4' && wturn == 1 && checksquare(move) == 0
                 && (board[x+1][y] == "pw" || board[x+2][y] == "pw")) {
			
            char* sqtocheck = map[x+1][y];
			bool check = checksquare(sqtocheck);

			if (check == 1) 
				movepiece(sqtocheck, move);
				
			
            else if (check == 0) {
				char* sqtocheck = map[x+2][y];
				bool check = checksquare(sqtocheck);
				
				if (check == 1) 
					movepiece(sqtocheck, move);
					

                else if (check == 0) 
					printf("Illegal move");
					
				}
			}

        else if (strlen(move) == 2 && wturn == 1 && board[x+1][y] == "pw" && board[x][y] == ". ") {
			char* from = map[x+1][y];
			movepiece(from, move);
			}

        else if (strlen(move) == 2 && move[1] == '5' && wturn == 0 && checksquare(move) == 0
                 && (board[x-1][y] == "pb" || board[x-2][y] == "pb")) {
			
            char* sqtocheck = map[x-1][y];
			bool check = checksquare(sqtocheck);

			if (check == 1) 
				movepiece(sqtocheck, move);
				
			
            else if (check == 0) {
				char* sqtocheck = map[x-2][y];
				bool check = checksquare(sqtocheck);
				
				if (check == 1) 
					movepiece(sqtocheck, move);
					

                else if (check == 0) 
					printf("Illegal move");
					
				}
			}

        else if (strlen(move) == 2 && wturn == 0 && board[x-1][y] == "pb" && board[x][y] == ". ") {
            char* from = map[x-1][y];
			movepiece(from, move);
			}


        else if (strlen(move) == 3 && move[0] == 'N' && wturn == 1)
            knightmover(square, "Nw");    

        else if (strlen(move) == 3 && move[0] == 'N' && wturn == 0) 
            knightmover(square, "Nb");

        else if (strlen(move) == 4 && move[0] == 'N' && wturn == 1 && move[1] == 'x' &&
                 board[x][y] != ". ") {

            char* status = board[x][y];

            if (status[1] == 'b')
                knightmover(square, "Nb");
            
            else
                printf("Illegal move\n");
        }

        else if (strlen(move) == 4 && move[0] == 'N' && wturn == 0 && move[1] == 'x' &&
                 board[x][y] != ". ") {

            char* status = board[x][y];

            if (status[1] == 'w')
                knightmover(square, "Nw");
            
            else
                printf("Illegal move\n");
        }

        else if (strlen(move) == 3 && move[0] == 'B' && board[x][y] == ". ")
            bishopmover(square);            

        else if (strlen(move) == 4 && move[0] == 'B' && move[1] == 'x' && board[x][y] != ". ") {

            char* status = board[x][y];

            if (wturn == 1 && status[1] == 'b')
                bishopmover(square);

            else if (wturn == 0 && status[1] == 'w')
                bishopmover(square);

            else
                printf("Illegal move\n");
        }

        else if (strlen(move) == 3 && move[0] == 'R' && board[x][y] == ". ")
            rookmover(square);

        else if (strlen(move) == 4 && move[0] == 'R' && move[1] == 'x' && board[x][y] != ". ") {

            char* status = board[x][y];

            if (wturn == 1 && status[1] == 'b')
                rookmover(square);

            else if (wturn == 0 && status[1] == 'w')
                rookmover(square);

            else
                printf("Illegal move\n");

        }
            

        else if (strlen(move) == 3 && move[0] == 'Q')
            queenmover(square);

        else if (strlen(move) == 4 && move[0] == 'Q' && move[1] == 'x' && board[x][y] != ". ") {

            char* status = board[x][y];

            if (wturn == 1 && status[1] == 'b')
                queenmover(square);

            else if (wturn == 0 && status[1] == 'w')
                queenmover(square);

            else
                printf("Illegal move\n");
        }

        else if (strlen(move) == 3 && move[0] == 'K')
            kingmover(square);

        else if (strlen(move) == 4 && move[0] == 'K' && move[1] == 'x' && board[x][y] != ". ") {

            char* status = board[x][y];

            if (wturn == 1 && status[1] == 'b')
                kingmover(square);

            else if (wturn == 0 && status[1] == 'w')
                kingmover(square);

            else
                printf("Illegal move\n");
        }

        else if (strlen(move) == 4 && wturn == 1 && move[1] == 'x' && worb(square) == 'b') {

            char str[3] = "\0";
            char m = move[0];
            str[0] = m;
            str[1] = '1';

            int column = squareyfinder(str);
            int row = x+1;

            movepiece(map[row][column], map[x][y]);

        }
            
        else if (strlen(move) == 4 && wturn == 0 && move[1] == 'x' && worb(square) == 'w') {

            char str[3] = "\0";
            char m = move[0];
            str[0] = m;
            str[1] = '1';

            int column = squareyfinder(str);
            int row = x-1;

            movepiece(map[row][column], map[x][y]);

        }

        else
            printf("error");

		}

    void pturn() {

        while (true) {

           if (checkcheck())
             printf("Check!\n");

            char *boardchk[8][8];

            memcpy(boardchk, board, sizeof(board));
            
            boardprint();
            char move[4];
            printf("Please type a move in standard chess notation: ");
            scanf("%s", move);
            turn(move);

            if (checkcheck()) {
                memcpy(board, boardchk, sizeof(board));
                printf("Can not move into check!\n");
            }


            if (memcmp(board, boardchk, sizeof(board)) != 0)
                (wturn == 1) ? (wturn = 0) : (wturn = 1);


        }
    }

    pturn();

	return 0;


}

