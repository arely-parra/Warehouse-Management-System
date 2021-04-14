#include <stdio.h>
#include <stdlib.h>
#include <time.h>

string barrowingList[99][7]; //3d array named borrowList with 100 rows and 8 columns(one for each item detail)
/*Test array:
    0	     1       2    3      4       5     6       7
0 Carrots vegetable bay7 7:30 isOrange fresh asile15 2.50
1 Apples  fruit     bay4 6:45 isRed    fresh asile12 1.25
2 Grapes
3 
4 spoons utensile   bay2 3:30 isMetal  N/A   asile2  5.99
5
6
7
8
9
*/

int loopNum;
char menuChoice;
int listRow;

void main (void) {
	
	while (TRUE) {
		printf("View barrowing requests or Accept borrowing requests [V/A]\n");
		scanf("%c", &menuChoice);

		if (menuChoice == "V" || menuChoice == "v") {
			/*




			*/

			loopNum = 0;

    		while (loopNum <= 99) { //while loop to list all barroing requests
			
       			if (barrowingList[loopNum][0] == NUll) { //ends loop if row in array is empty
            		break;
        		}

				printf("List row:");
				printf(loopNum);
				printf(" ");

        		printf("Name:");
        		printf(barrowingList[loopNum][0]);
        		printf(" ");

        		printf("Item type:");
        		printf(barrowingList[loopNum][1]);
        		printf(" ");

        		printf("Stored:");
        		printf(barrowingList[loopNum][2]);
        		printf(" ");

        		printf("Pick up:");
        		printf(barrowingList[loopNum][3]);
        		printf(" ");

        		printf("Comment:");
        		printf(barrowingList[loopNum][4]);
        		printf(" ");

        		printf("Quality:");
        		printf(barrowingList[loopNum][5]);
        		printf(" ");

        		printf("Location:");
        		printf(barrowingList[loopNum][6]);
        		printf(" ");

        		printf("Price:");
        		printf(barrowingList[loopNum][7]);
        		printf(" ");

        		++loopNum;//Esentially loopNum = loopNum + 1
    		}

			printf("Press M to go back to menu")
			scanf("%c", &menuChoice);

			if (menuChoice != "M" || menuChoice != "m") { //makes sure they didnt type M or m then quits the pogram is they didnt or goes backt o main menu if they did
				break;
			}

		} else if (menuChoice == "A" || menuChoice == "a") {

			printf("Enter List Row:");
			scanf("%int", &listRow);

			printf("Name:");
        	printf(barrowingList[listRow][0]);
        	printf("\n");

        	printf("Item type:");
        	printf(barrowingList[listRow][1]);
        	printf("\n");

        	printf("Stored:");
        	printf(barrowingList[loopRow][2]);
        	printf("\n");

        	printf("Pick up:");
        	printf(barrowingList[loopRow][3]);
        	printf("\n");

        	printf("Comment:");
        	printf(barrowingList[loopRow][4]);
        	printf("\n");

        	printf("Quality:");
        	printf(barrowingList[loopRow][5]);
        	printf("\n");

        	printf("Location:");
        	printf(barrowingList[loopRow][6]);
        	printf("\n");

        	printf("Price:");
        	printf(barrowingList[loopRow][7]);
        	printf("\n");

			/*while () {
				printf("Accept or Deny borrow request[A/D]");
				scanf("%c", &menuChoice);


				if (menuChoice == "A") {

				} else if {

				} else {

				}
			}*/

			printf("Press M to go back to menu")
			scanf("%c", &menuChoice);

			if (menuChoice != "M" || menuChoice != "m") { //makes sure they didnt type M or m then quits the pogram is they didnt or goes backt o main menu if they did
				break;
			}

		} else {
			printf("Invalid Option");
		}
	}
}