//* Project 4: Warehouse Management System
//* Group Name: Can You C My Screen?
//* Group Members: Arely J. Parra López, Jarred Crystal, Alexander Vita, Kamyrn Hammond, and Sophie Ross
//* Course: CSCI 1110-01 | Introduction to C Programming
//* Professor: Dr. Reza Sadeghi
//* Date: Monday, April 26th, 2021


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Menu Options for Guest User Menu (Jarred Crystal)
	int guestMenu(void){
		puts("\n\n\t***************************\n\t\tGuest Menu\n\t***************************\n\n");
		printf("\t[1] Search WMS for Items in Warehouse\n");
		printf("\t[2] Generate a List of Favorite Items\n");
		printf("\t[3] View List of Favorite Items\n");
		printf("\t[4] Request Borrowing/Buying Items\n");
		printf("\t[5] View Item's Borrowing History\n");
		printf("\t[6] Exit\n");
		printf("\n\tPlease select one of the above options to proceed: ");
		int input;
		scanf("%d",&input);
		if(input>=1 && input <=6){
			return input;
		}else{
			system("@cls||clear");
			printf("\t<<<Your input is not available on the Guest Menu, please try again>>>\n");
			guestMenu();
		}
}	


// Case 1 (Arely Parra Lopez)
int* searchWMS(void){
		system("@cls||clear");
		puts("\n\n\t**********************************************\n\t\tSearch for Items in the WMS\n\t**********************************************\n\n");
		// return array
		static int output[10];
		// Get the place
		printf("\tWhat is the Item ID? ");
		char ID[100];
		char input[100];
		scanf("%s",&ID);
		strcpy(input,ID);
		strcat(ID, "\n");
		
		
		// open the textfile
		FILE *myfile;
		myfile = fopen("inventory.txt","r"); 
		if(myfile == NULL)
		{
		  printf("An error has happened!!!");
		  printf("Please reset everything and try again!!!");
		  exit(1);             
		}
		
		// search capacity
		char myString[100];
		int line=0;
		int find=0;
		int fieldNumber=0;
		while(fgets(myString, sizeof(myString),myfile) != NULL){
			line++; fieldNumber++;
			if(strcmp(myString, ID) == 0 && fieldNumber == 1){
				printf("\n\tItem ID %s was found at line %d\n", input, line);
				find=1;
				output[0]=find;
				output[1]=line;
				break;
			}
			//When we starting reading a new entity
			if(fieldNumber == 10){
				fieldNumber=0;
			}
		}
		fclose(myfile);
		if(find ==0){
			printf("\n\tItem ID %s does not exist in your records\n",input);
			//exit(1);
			return output;
		}
		
		//// return the information
		// open the textfile
		myfile = fopen("inventory.txt","r"); 
		if(myfile == NULL)
		{
		  printf("An error has happened!!!");
		  printf("Please reset everything and try again!!!");
		  exit(1);             
		}
		//print the information
		int pline=0;
		while(fgets(myString, sizeof(myString),myfile) != NULL){
			pline++;
			if(pline == (line+1)){
				printf("\tItem Type: %s",myString);
			}else if(pline == (line+2)){
				printf("\tItem Name: %s",myString);
			}else if(pline == (line+3)){
				printf("\tStored Time (MM/DD/YY_HH:MM): %s",myString);
			}else if(pline == (line+4)){
				printf("\tPickout Time (MM/DD/YY_HH:MM): %s",myString);
			}else if(pline == (line+5)){
				printf("\tProvider Name: %s",myString);
			}else if(pline == (line+6)){
				printf("\tItem Quantity: %s",myString);
			}else if(pline == (line+7)){
				printf("\tItem Place: %s",myString);
			}else if(pline == (line+8)){
				printf("\tItem Price: %s",myString);
				break;
			};
		};

		//close the file
		fclose(myfile);
		return output;
	};
	
// Case 2 (Arely Parra Lopez)
void makeList(void){
	system("@cls||clear");
		puts("\n\n\t**********************************************\n\t\tGenerate a List of Favorite Items\n\t**********************************************\n\n");
		// Item dataTypes
		struct entity{
			char Type[100];
			char ID[100];
			char Name[100];
			char Provider[100];
			char Quantity[100];
			char Place[100];
			char Price[100];
			
		};
		struct entity new;
		
		//Prompt Admin
		printf("\tTo make a list of favorite items, please add the following information about the item:\n");
		printf("\tItem ID: ");
		scanf("%s",&new.ID);
		printf("\tItem Type: ");
		scanf("%s",&new.Type);
		printf("\tItem Name: ");
		scanf("%s",&new.Name);
		printf("\tProvider Name: ");
		scanf("%s",&new.Provider);
		printf("\tItem Quantity: ");
		scanf("%s",&new.Quantity);
		printf("\tItem Place: ");
		scanf("%s",&new.Place);
		printf("\tItem Price: ");
		scanf("%s",&new.Price);
		
		// print on a textfile
		FILE *myfile;
		myfile = fopen("List.txt","a"); 
		if(myfile == NULL)
		{
		  printf("An error has happened!");
		  printf("Please reset everything and try again!");
		  exit(1);             
		}
		fprintf(myfile,"%s\n%s\n%s\n%s\n%s\n%s\n%s\n----------\n",&new.ID,&new.Type,&new.Name,&new.Provider,&new.Quantity,&new.Place,&new.Price);
		fclose(myfile);
		
		// double check with user
		puts("\n\tAddition of the item to your Favorite Items List was successful!\n");
		printf("\tWould you like to add another item to your list of favorites? (y/n): ");
		char quit;
		getchar();
		scanf("%c",&quit);
		if(quit=='y'||quit=='Y'){
			makeList();
		}
		
}

// Case 3 (Arely Parra Lopez)
void viewList(void){
		system("@cls||clear");
		puts("\n\n\t*************************************************\n\t\tView Saved List of Favorite Items\n\t*************************************************\n\n");
		// Open the text file
		FILE *myfile;
		myfile = fopen("List.txt","r"); 
		if(myfile == NULL)
		{
		  printf("An error has happened!\n");
		  printf("Please reset everything and try again!\n");
		  exit(1);             
		}
		
		struct entity{
			char Type[100];
			char ID[100];
			char Name[100];
			char Provider[100];
			char Quantity[100];
			char Place[100];
			char Price[100];
			
		};
		struct entity new;
		//TABLE TITLES
		printf("\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 Favorite Item List \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n");
		printf("\t===================================================================================================\n");
		printf("\tItem ID\t Item Type\t Item Name\t Item Provider\t Item Quantity\t Item Place\t Item Price\n");
		printf("\t===================================================================================================\n");
		char myString[10000];
		int pline=0;
		while(fgets(myString, sizeof(myString),myfile) != NULL){
			pline++;
			if(pline == 1){
				myString[strcspn(myString, "\n")] = 0;
				strcpy(new.ID,myString);
			}else if(pline == 2){
				myString[strcspn(myString, "\n")] = 0;
				strcpy(new.Type,myString);
			}else if(pline == 3){
				myString[strcspn(myString, "\n")] = 0;
				strcpy(new.Name,myString);
			}else if(pline == 4){
				myString[strcspn(myString, "\n")] = 0;
				strcpy(new.Provider,myString);
			}else if(pline == 5){
				myString[strcspn(myString, "\n")] = 0;
				strcpy(new.Quantity,myString);
			}else if(pline == 6){
				myString[strcspn(myString, "\n")] = 0;
				strcpy(new.Place,myString);
			}else if(pline == 7){
				myString[strcspn(myString, "\n")] = 0;
				strcpy(new.Price,myString);
			}else if(pline == 8){
				printf("\t%-5s\t %-10s\t %-10s\t %-10s\t %-5s\t\t %-10s\t %-5s\n",&new.ID,&new.Type,&new.Name,&new.Provider,&new.Quantity,&new.Place,&new.Price);
				pline=0;
			}
		}
		//close the file
		fclose(myfile);
	}

// Case 4 (Arely Parra Lopez)
void requestItems(void){
	system("@cls||clear");
		puts("\n\n\t***************************************************\n\t\tGenerate a Borrowing/Buying Request\n\t***************************************************\n\n");
		
		// Item dataTypes
		struct entity{
			char Type[100];
			char ID[100];
			char Name[100];
			char Provider[100];
			char Quantity[100];
			char Place[100];
			char Price[100];
			char Length[100];
			
		};
		struct entity new;
		
		//Prompt Admin
		printf("\tTo make a request, please add the following information about the desired item:\n");
		printf("\tItem ID: ");
		scanf("%s",&new.ID);
		printf("\tItem Type: ");
		scanf("%s",&new.Type);
		printf("\tItem Name: ");
		scanf("%s",&new.Name);
		printf("\tProvider Name: ");
		scanf("%s",&new.Provider);
		printf("\tItem Quantity: ");
		scanf("%s",&new.Quantity);
		printf("\tItem Place: ");
		scanf("%s",&new.Place);
		printf("\tItem Price: ");
		scanf("%s",&new.Price);
		printf("\tBorrowing Time ([Forever] indicates [To Purchase]): ");
		scanf("%s",&new.Length);
		
		// print on a textfile
		FILE *myfile;
		myfile = fopen("Requests.txt","a"); 
		if(myfile == NULL)
		{
		  printf("An error has happened!");
		  printf("Please reset everything and try again!");
		  exit(1);             
		}
		fprintf(myfile,"%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n----------\n",&new.ID,&new.Type,&new.Name,&new.Provider,&new.Quantity,&new.Place,&new.Price,&new.Length);
		fclose(myfile);
		
		
		//Double check with User
		puts("\tItem information was successfully added to your requests!\n");
		printf("\tWould you like to add another item to your request?(NOTE: You can only add 3 items max)(y/n): ");
		char quit;
		getchar();
		scanf("%c",&quit);
		if(quit=='y'||quit=='Y'){
			requestItems();
		};
}

// Case 5 (Arely Parra Lopez)
void viewHistory(void){
	system("@cls||clear");
	puts("\n\n\t****************************************\n\t\tHistory of Borrowed Items\n\t****************************************\n\n");
	// Open the text file
	FILE *myfile;
	myfile = fopen("History.txt","r"); 
	if(myfile == NULL)
	{
	  printf("An error has happened!\n");
	  printf("Please reset everything and try again!\n");
	  exit(1);             
	}
	
	struct entity{
		char ID[100];
		char Name[100];
		char Borrower[100];
		char Taken[100];
		char Returned[100];
		
	};
	struct entity new;
	//TABLE TITLES
	printf("\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 Favorite Item List \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n");
	printf("\t===================================================================\n");
	printf("\tItem ID\t Item Name\t Borrower\t Taken Out\t Returned\n");
	printf("\t===================================================================\n");
	char myString[10000];
	int pline=0;
	while(fgets(myString, sizeof(myString),myfile) != NULL){
		pline++;
		if(pline == 1){
			myString[strcspn(myString, "\n")] = 0;
			strcpy(new.ID,myString);
		}else if(pline == 2){
			myString[strcspn(myString, "\n")] = 0;
			strcpy(new.Name,myString);
		}else if(pline == 3){
			myString[strcspn(myString, "\n")] = 0;
			strcpy(new.Borrower,myString);
		}else if(pline == 4){
			myString[strcspn(myString, "\n")] = 0;
			strcpy(new.Taken,myString);
		}else if(pline == 5){
			myString[strcspn(myString, "\n")] = 0;
			strcpy(new.Returned,myString);
		}else if(pline == 6){
			printf("\t%-5s\t %-10s\t %-10s\t %-10s\t %-5s\n",&new.ID,&new.Name,&new.Borrower,&new.Taken,&new.Returned);
			pline=0;
		}
	}
	//close the file
	fclose(myfile);
}


// Menu Switch Case for Guest User Main Menu (Jarred Crystal)
void guestMain(void){
	system("@cls||clear");
	// Project Title
    puts("\n\n\t***************************************************************\n\t\tWelcome to the Warehouse Managment System (WMS)\n\t***************************************************************\n\n");
	int task;
	task=guestMenu();
		
	switch(task){
		case 1:
			searchWMS();
			break;
		case 2:
			makeList();
			break;
		case 3:
			viewList();
			break;
		case 4:
			requestItems();
			break;
		case 5:
			viewHistory();
			break;
		case 6:
			printf("\nThank you for using the Warehouse Management System! Have a good day!\n");
			exit(1);
		}

//Repetition Request for Guest User
	printf("\n\tWould you like to do another action?(y/n) ");
	char quit;
	getchar();
	scanf("%c",&quit);
	if(quit=='y'||quit=='Y'){
		guestMain();
	}else if (quit=='n'||quit=='N'){
		printf("\nThank you for using the Warehouse Management System! Have a good day!\n");
		exit(1);
	} 
}	