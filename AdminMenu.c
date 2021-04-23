//* Project 4: Warehouse Management System
//* Group Name: Can You C My Screen?
//* Group Members: Arely J. Parra López, Jarred Crystal, Alexander Vita, Kamyrn Hammond, and Sophie Ross
//* Course: CSCI 1110-01 | Introduction to C Programming
//* Professor: Dr. Reza Sadeghi
//* Date: Monday, April 26th, 2021


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Menu Options For Admin (Jarred Crystal)
	int adminMenu(void){
		puts("\n\n\t****************************\n\t\t Admin Menu\n\t****************************\n\n");
		printf("\t[1] View Admin/Guest Usernames and Passwords\n");
		printf("\t[2] Search for Admin/Guest Usernames and/or Passwords\n");
		printf("\t[3] Change the Admin/Guest Usernames and/or Passwords\n");
		printf("\t[4] Add Guest User to WMS\n");
		printf("\t[5] Remove Guest User from WMS\n");
		printf("\t[6] Add Items to Warehouse\n");
		printf("\t[7] Delete Items from Warehouse\n");
		printf("\t[8] Edit Items from Warehouse\n");
		printf("\t[9] View List of Borrowing Requests\n");
		printf("\t[10] Accept or Deny Borrowing Requests\n");
		printf("\t[11] Exit\n");
		
		printf("\n\tPlease select one of the above options to proceed: ");
		int input;
		scanf("%d",&input);
		if(input>=1 && input <=11){
			return input;
		}else{
			system("@cls||clear");
			printf("\t<<<Your input is not available on the Admin Menu, please try again>>>\n");
			adminMenu();
		}
	}

// Case 1 (Kamyrn Hammond)
void view(void){
		system("@cls||clear");
		puts("\n\n\t***********************\n\t\tView Admin/Guest Usernames and Passwords to Log In\n\t***********************\n\n");
		// Open the text file
		FILE *myfile;
		myfile = fopen("LogIn.txt","r"); 
		if(myfile == NULL)
		{
		  printf("An error has happened!\n");
		  printf("Please reset everything and try again!\n");
		  exit(1);             
		}
		
		struct entity{
			char encrypt[20];
			char username[20];
			char password[20];
		};
		struct entity new;
		//TABLE TITLES
		printf("\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 Recorded Usernames & Passwords \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n");
		printf("\t=======================================================================\n");
		printf("\tKey\t\t\t\t Username\t\t Password\n");
		printf("\t=======================================================================\n");
		char myString[100];
		int pline=0;
		while(fgets(myString, sizeof(myString),myfile) != NULL){
			pline++;
			if(pline == 1){
				myString[strcspn(myString, "\n")] = 0;
				strcpy(new.encrypt,myString);
			}else if(pline == 2){
				myString[strcspn(myString, "\n")] = 0;
				strcpy(new.username,myString);
			}else if(pline == 3){
				myString[strcspn(myString, "\n")] = 0;
				strcpy(new.password,myString);
			}else if(pline == 4){
				printf("\t%-10s\t\t\t %-5s\t\t\t %-5s\n",&new.encrypt,&new.username,&new.password);
				pline=0;
			}
		}
		//close the file
		fclose(myfile);
	}

// Case 2 (Kamyrn Hammond)
int* search(void){
		system("@cls||clear");
		puts("\n\n\t***********************\n\t\tSearch for Admin/Guest Usernames and/or Passwords\n\t***********************\n\n");
		// return array
		static int output[2];
		
		printf("\tWhat is the encryption key to view login credentials? ");
		char key[100];
		char input[100];
		scanf("%s",&key);
		strcpy(input,key);
		strcat(key, "\n");
		
		// open the textfile
		FILE *myfile;
		myfile = fopen("LogIn.txt","r"); 
		if(myfile == NULL)
		{
		  printf("An error has happened!");
		  printf("Please reset everything and try again!");
		  exit(1);             
		}
		
		//Search for Admin/Guest Usernames and/or Passwords
		char myString[100];
		int line=0;
		int find=0;
		int fieldNumber=0;
		while(fgets(myString, sizeof(myString),myfile) != NULL){
			line++; fieldNumber++;
			if(strcmp(myString, key) == 0 && fieldNumber == 1){
				printf("\n\tI found %s at line %d\n", input, line);
				find=1;
				output[0]=find;
				output[1]=line;
				break;
			}
			//When we starting reading a new entity
			if(fieldNumber == 4){
				fieldNumber=0;
			}
		}
		fclose(myfile);
		if(find ==0){
			printf("\n\t%s does not exist in your records\n",input);
			//exit(1);
			return output;
		}
		
		// return the inform
		// open the textfile
		myfile = fopen("LogIn.txt","r"); 
		if(myfile == NULL)
		{
		  printf("An error has happened!");
		  printf("Please reset everything and try again!");
		  exit(1);             
		}
		//print the information
		int pline=0;
		while(fgets(myString, sizeof(myString),myfile) != NULL){
			pline++;
			if(pline == (line+1)){
				printf("\tUsername: %s",myString);
			}else if(pline == (line+2)){
				printf("\tPassword: %s",myString);
				break;
			};
		}
		//close the file
		fclose(myfile);
		return output;
	};
	
// Case 3 (Kamryn Hammond)
void edit(void){
		puts("\n\n\t***********************\n\t\tChange the Admin/Guest Usernames and/or Passwords\n\t***********************\n\n");
		
		int* place=search();
		// return array [find, line]
		//printf("%d, %d",place[0],place[1]);
		int find=place[0];
		int line=place[1];
		if(find == 0){
			printf("\tYour encrytption key does not exists!!!");
		}else{
				// Get new values
				char username[20], password[20];
				printf("\tPlease enter your new Username for this encryption key: ");
				scanf("%s",&username);
				printf("\tPlease enter your new Password for this encyrption key: ");
				scanf("%s",&password);
				
				// open the textfile
				FILE *originalfile= fopen("LogIn.txt","r");
				FILE *tempfile= fopen("temp.txt","w");
				if(originalfile == NULL || tempfile == NULL )
				{
				  printf("An error has happened!");
				  printf("Please reset everything and try again!");
				  exit(1);             
				}
				
				// paste all content to temporary file except the ones we want to edit
				char myString[100];
				int pline=0;
				while(fgets(myString, sizeof(myString),originalfile) != NULL){
					pline++;
					if(pline != (line+1) && pline != (line+2)){//we just want to change username and password
						fprintf(tempfile,"%s",myString);
						printf("\t%s has been deleted\n",myString);
					}else if(pline == (line+1)){
						fprintf(tempfile,"%s\n",username);
					}else if(pline == (line+2)){
						fprintf(tempfile,"%s\n",password);
					}
				}
				fclose(originalfile);
				fclose(tempfile);
				
				// remove the original file and rename the temorary file
				remove("LogIn.txt");
				rename("temp.txt","LogIn.txt");
				
				// double check with the user
				puts("\tThe request was successful");
				printf("\tWould you like to adjust another item(y/n): ");
				char quit;
				getchar();
				scanf("%c",&quit);
				if(quit=='y'||quit=='Y'){
					edit();
				}
			}
	};

// Case 4 (Kamyrn Hammond)
void add(void){
		system("@cls||clear");
		puts("\n\n\t***********************\n\t\tAdd Guest User to WMS\n\t***********************\n\n");
		// passwords dataTypes
		struct entity{
			char encrypt[20];
			char username[20];
			char password[20];
		};
		struct entity new;
		
		//Prompt Admin
		printf("\tTo add a new Guest username & password, please add the following inform:\n");
		printf("\tencyrption key: ");
		scanf("%s",&new.encrypt);
		printf("\tusername: ");
		scanf("%s",&new.username);
		printf("\tpassword: ");
		scanf("%s",&new.password);
		
		// print on a textfile
		FILE *myfile;
		myfile = fopen("LogIn.txt","a"); 
		if(myfile == NULL)
		{
		  printf("An error has happened!");
		  printf("Please reset everything and try again!");
		  exit(1);             
		}
		fprintf(myfile,"%s\n%s\n%s\n----------\n",&new.encrypt,&new.username,&new.password);
		fclose(myfile);
		
		//Double check with Admin
		puts("\tThe request was successful");
		printf("\t Would you like to add another item(y/n): ");
		char quit;
		getchar();
		scanf("%c",&quit);
		if(quit=='y'||quit=='Y'){
			add();
		}
	}

// Case 5 (Kamryn Hammond)
void delete(void){
		// We want to make sure the desired URL, Username, and Password exist
		int* place=search();
		// return array [find, line]
		//printf("%d, %d",place[0],place[1]);
		int find=place[0];
		int line=place[1];
		if(find == 0){
			printf("\tYour desired URL does not exists!");
		}else{
				// open the textfile
				FILE *originalfile= fopen("LogIn.txt","r");
				FILE *tempfile= fopen("temp.txt","w");
				if(originalfile == NULL || tempfile == NULL )
				{
				  printf("An error has happened!");
				  printf("Please reset everything and try again!");
				  exit(1);             
				}
				
				// paste all content of the original file to the temporary file except the ones that we want to remove
				char myString[100];
				int pline=0;
				while(fgets(myString, sizeof(myString),originalfile) != NULL){
					pline++;
					if(pline != line && pline != (line+1) && pline != (line+2) && pline != (line+3)){
						fprintf(tempfile,"%s",myString);
						printf("\t%s has been deleted\n",myString);
					}
				}
				fclose(originalfile);
				fclose(tempfile);
				
				// remove the original file and rename the temorary file
				remove("LogIn.txt");
				rename("temp.txt","LogIn.txt");
				
				// double check with the user
				puts("\tThe request was successful");
				printf("\tWould you like to remove another item(y/n): ");
				char quit;
				getchar();
				scanf("%c",&quit);
				if(quit=='y'||quit=='Y'){
					delete();
				}
			}
	}

/*
// Case 6 (Alex Vita)
void  (){

}

// Case 7 (Alex Vita)
void  (){

}

// Case 8 (Alex Vita)
void  (){

}

// Case 9 (Sophie Ross)
void viewBorrowing(void){
	int loopNum = 0;

    while (loopNum <= 99) { //while loop to list all barroing requests
    	if (barrowingList[loopNum][0] != NUll) { 
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
        }

        ++loopNum;//Esentially loopNum = loopNum + 1
    }
}

// Case 10 (Sophie Ross)
void approveBorrowing(void) {
	int listRow;
	printf("Enter List Row:");
	scanf("%int", &listRow);

	while (TRUE) {
		printf("Name:");
		printf(barrowingList[listRow][0]);
		printf("\n");

		printf("Item type:");
		printf(barrowingList[listRow][1]);
		printf("\n");

		printf("Stored:");
		printf(barrowingList[listRow][2]);
		printf("\n");

    	printf("Pick up:");
		printf(barrowingList[listRow][3]);
    	printf("\n");

		printf("Comment:");
		printf(barrowingList[listRow][4]);
		printf("\n");

    	printf("Quality:");
    	printf(barrowingList[listRow][5]);
		printf("\n");

		printf("Location:");
		printf(barrowingList[listRow][6]);
		printf("\n");

		printf("Price:");
		printf(barrowingList[listRow][7]);
		printf("\n");

		printf("Accept or Deny borrow request[A/D]");
		scanf("%c", &menuChoice);
		if (menuChoice == 'A' || menuChoice == 'a' || menuChoice == 'D' || menuChoice == 'd') {
			if (menuChoice == 'A' || menuChoice == 'a') {
				for (int i = 0; i <= 99; ++i) {
					if (acceptedBorrowing[i][0] == NULL) {
						int listRowTwo = i;
						break;
					}
				}
			
				acceptedBorrowing[listRowTwo][0] = borrowList[listRow][0];
				acceptedBorrowing[listRowTwo][1] = borrowList[listRow][1];
				acceptedBorrowing[listRowTwo][2] = borrowList[listRow][2];
				acceptedBorrowing[listRowTwo][3] = borrowList[listRow][3];
				acceptedBorrowing[listRowTwo][4] = borrowList[listRow][4];
				acceptedBorrowing[listRowTwo][5] = borrowList[listRow][5];
				acceptedBorrowing[listRowTwo][6] = borrowList[listRow][6];
				acceptedBorrowing[listRowTwo][7] = borrowList[listRow][7];
			}
			borrowList[listRow][0] = NULL;
			borrowList[listRow][1] = NULL;
			borrowList[listRow][2] = NULL;
			borrowList[listRow][3] = NULL;
			borrowList[listRow][4] = NULL;
			borrowList[listRow][5] = NULL;
			borrowList[listRow][6] = NULL;
			borrowList[listRow][7] = NULL;
			break;
		} else {
			printf("Invaild Input");
		}
	}
}
*/

// Menu Switch Case for Admin Main Menu (Kamyrn Hammond)
void admin(void){
	system("@cls||clear");
	// Project Title
    puts("\n\n\t***************************************************************\n\t\tWelcome to the Warehouse Managment System (WMS)\n\t***************************************************************\n\n");
	int task;
	task=adminMenu();
		
	switch (task){
		case 1:
			view();
			break;
		case 2:
			search();
			break;
		case 3:
			edit();
			break;
		case 4:
			add();
			break;
		case 5:
			delete();
			break;
		/*case 6:
			//
			break;
		case 7:
			//
			break;
		case 8:
			//
			break;
		case 9:
			viewBorrowing();
			break;
		case 10:
			approvingBorrowing();
			break;*/
		case 11:
			printf("\nThank you for using the Warehouse Management System! Have a good day!\n");
			exit(1);
		}
		
//Repetition Request for Admin
	printf("\n\tWould you like to do another action?(y/n) ");
	char quit;
	getchar();
	scanf("%c",&quit);
	if(quit=='y'||quit=='Y'){
		adminMenu();
	}else if (quit=='n'||quit=='N'){
		printf("\nThank you for using the Warehouse Management System! Have a good day!\n");
		exit(1);
	} 
}

