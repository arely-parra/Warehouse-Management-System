#include <stdio.h>
#include <stdlib.h>
#include <string.h>
     
// Menu Options for Guest User (Arely Parra López)
int guestMenu(void){
		puts("\n\n\t***********************\n\t\tGuest Menu\n\t***********************\n\n");
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
		time
		puts("\n\n\t***********************\n\t\tSearch for Items in the WMS\n\t***********************\n\n");
		// return array
		static int output[8];
		// Get the place
		printf("\tWhat is the Item Type? ");
		char Type[100];
		char input[100];
		scanf("%s",&Type);
		strcpy(input,Type);
		strcat(Type, "\n");
		
		
		// open the textfile
		FILE *myfile;
		myfile = fopen("WMS.txt","r"); 
		if(myfile == NULL)
		{
		  printf("An error is happend!!!");
		  printf("Please reset everything and try again!!!");
		  exit(1);             
		}
		
		// search
		char myString[100];
		int line=0;
		int find=0;
		int fieldNumber=0;
		while(fgets(myString, sizeof(myString),myfile) != NULL){
			line++; fieldNumber++;
			if(strcmp(myString, Type) == 0 && fieldNumber == 1){
				printf("\n\tI found Item Type %s at line %d\n", input, line);
				find=1;
				output[0]=find;
				output[1]=line;
				break;
			}
			//When we starting reading a new entity
			if(fieldNumber == 8){
				fieldNumber=0;
			}
		}
		fclose(myfile);
		if(find ==0){
			printf("\n\t%s does not exist in your records\n",input);
			//exit(1);
			return output;
		}
		
		//// return the information
		// open the textfile
		myfile = fopen("WMS.txt","r"); 
		if(myfile == NULL)
		{
		  printf("An error is happend!!!");
		  printf("Please reset everything and try again!!!");
		  exit(1);             
		}
		//print the information
		int pline=0;
		while(fgets(myString, sizeof(myString),myfile) != NULL){
			pline++;
			if(pline == (line+1)){
				printf("\tItem ID: %s",myString);
			}else if(pline == (line+2)){
				printf("\tItem Name: %s",myString);
			}else if(pline == (line+3)){
				printf("\tProvider Name: %s",myString);
			}else if(pline == (line+4)){
				printf("\tItem Quantity: %s",myString);
			}else if(pline == (line+5)){
				printf("\tItem Place: %s",myString);
			}else if(pline == (line+6)){
				printf("\tItem Price: %s",myString);
				break;
			};
		}
		//close the file
		fclose(myfile);
		return output;
	};


// Case 2 (Arely Parra Lopez)
void makeList(void){
	system("@cls||clear");
		puts("\n\n\t***********************\n\t\tGenerate a List of Favorite Items\n\t***********************\n\n");
		// Item dataTypes
		struct entity{
			char Type[20];
			int ID[20];
			char Name[20];
			char Provider[20];
			int Quantity[20];
			char Place[20];
			int Price[20]
			
		};
		struct entity new;
		
		//Prompt Admin
		printf("\tTo make a list of favorite items, please add the following information about an item:\n");
		printf("\tItem Type: ");
		scanf("%s",&new.Type);
		printf("\tItem ID: ");
		scanf("%s",&new.ID);
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
		fprintf(myfile,"%s\n%s\n%s\n----------\n",&new.Type,&new.ID,&new.Name,&new.Provider,&new.Quantity,&new.Place,&new.Price);
		fclose(myfile);
		
		//Double check with Admin
		puts("\tItem Information was successfully added to your Favorite List");
		printf("\t Would you like to add another item(y/n): ");
		char quit;
		getchar();
		scanf("%c",&quit);
		if(quit=='y'||quit=='Y'){
			searchWMS();
		}
	}
}

// Case 3 (Arely Parra Lopez)
void viewList(void){
		system("@cls||clear");
		puts("\n\n\t***********************\n\t\tView Saved List of Favorite Items\n\t***********************\n\n");
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
			char Type[20];
			int ID[20];
			char Name[20];
			char Provider[20];
			int Quantity[20];
			char Place[20];
			int Price[20];
			
		};
		struct entity new;
		//TABLE TITLES
		printf("\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 Favorite Item List \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n");
		printf("\t=======================================================================\n");
		printf("\tItem Type\t\t\t\t Item ID\t\t Item Name\t\t Item Provider\t\t Item Quantity\t\t Item Place\t\t Item Price\n");
		printf("\t=======================================================================\n");
		char myString[100];
		int pline=0;
		while(fgets(myString, sizeof(myString),myfile) != NULL){
			pline++;
			if(pline == 1){
				myString[strcspn(myString, "\n")] = 0;
				strcpy(new.Type,myString);
			}else if(pline == 2){
				myString[strcspn(myString, "\n")] = 0;
				strcpy(new.ID,myString);
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
				printf("\t%-10s\t\t\t %-5s\t\t\t %-5s\n",&new.Type,&new.ID,&new.Name,&new.Provider,&new.Quantity,&new.Place,&new.Price);
				pline=0;
			}
		}
		//close the file
		fclose(myfile);
	}

// Case 4 (Arely Parra Lopez)
void requestItems(void){
	system("@cls||clear");
		puts("\n\n\t***********************\n\t\tGenerate a Borrowing/Buying Request\n\t***********************\n\n");
		// Item dataTypes
		struct entity{
			char Type[20];
			int ID[20];
			char Name[20];
			char Provider[20];
			int Quantity[20];
			char Place[20];
			int Price[20];
			int Length[20];
			
		};
		struct entity new;
		
		//Prompt Admin
		printf("\tTo make a request, please add the following information about an item:\n");
		printf("\tItem Type: ");
		scanf("%s",&new.Type);
		printf("\tItem ID: ");
		scanf("%s",&new.ID);
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
		printf("\tBorrowing Time (as in # of Weeks) : ");
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
		fprintf(myfile,"%s\n%s\n%s\n----------\n",&new.Type,&new.ID,&new.Name,&new.Provider,&new.Quantity,&new.Place,&new.Price,&new.Length);
		fclose(myfile);
		
		//Double check with User
		puts("\tItem Information was successfully added to Request");
		printf("\t Would you like to add another item to your request(y/n): ");
		char quit;
		getchar();
		scanf("%c",&quit);
		if(quit=='y'||quit=='Y'){
			requestItems();
		}
}

// Case 5 (Arely Parra Lopez)
void viewHistory(void){
	void viewList(void){
		system("@cls||clear");
		puts("\n\n\t***********************\n\t\tHistory of Borrowed Items\n\t***********************\n\n");
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
			int ID[20];
			char Name[20];
			char Borrower[20];
			int Taken[20];
			int Returned[20];
			
		};
		struct entity new;
		//TABLE TITLES
		printf("\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 Favorite Item List \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n");
		printf("\t=======================================================================\n");
		printf("\tItem IDt\t\t\t Item Name\t\t Borrowert\t Taken Out\t\t Returned\t\t\n");
		printf("\t=======================================================================\n");
		char myString[100];
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
				printf("\t%-10s\t\t\t %-5s\t\t\t %-5s\n",&new.ID,&new.Name,&new.Borrower,&new.Taken,&new.Returned);
				pline=0;
			}
		}
		//close the file
		fclose(myfile);
	}
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

//Repetition Request for Admin
	printf("\n\tWould you like to do another action?(y/n) ");
	char quit;
	getchar();
	scanf("%c",&quit);
	if(quit=='y'||quit=='Y'){
		guestMenu();
	}else if (quit=='n'||quit=='N'){
		printf("\nThank you for using the Warehouse Management System! Have a good day!\n");
		exit(1);
	} 
}	
