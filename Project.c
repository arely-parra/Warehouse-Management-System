//* Project 4: Warehouse Management System
//* Group Name: Can You C My Screen?
//* Group Members: Arely J. Parra López, Jarred Crystal, Alexander Vita, Kamyrn Hammond, and Sophie Ross
//* Course: CSCI 1110-01 | Introduction to C Programming
//* Author: Arely J. Parra López
//* Date: Monday, April 26th, 2021

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Menu Options For Admin
	int mainMenu(void){
		puts("\n\n\t****************************\n\t\t Admin Menu\n\t****************************\n\n");
		printf("\t[1] View Admin/Guest Usernames and Passwords\n");
		printf("\t[2] Search for Admin/Guest Usernames and/or Passwords\n");
		printf("\t[3] Change the Admin/Guest Usernames and/or Passwords\n");
		printf("\t[4] Add Guest User to WMS\n");
		printf("\t[5] Remove Guest User from WMS\n");
		printf("\t[6] Add Item to Warehouse\n");
		printf("\t[7] Delete Item from Warehouse\n");
		printf("\t[8] View List of Borrowing Requests\n");
		printf("\t[9] Accept or Deny Borrowing Requests\n");
		printf("\t[10] Exit\n");
		
		printf("\n\tPlease select one of the above options to proceed: ");
		int input;
		scanf("%d",&input);
		if(input>=1 && input <=6){
			return input;
		}else{
			system("@cls||clear");
			printf("\t<<<Your input is not available on the Admin Menu, please try again>>>\n");
			mainMenu();
		}
	}
// Case 1
void view(void){
		system("@cls||clear");
		puts("\n\n\t***********************\n\t\tView Admin/Guest Usernames and Passwords to Log In\n\t***********************\n\n");
		// Open the text file
		FILE *myfile;
		myfile = fopen("WMS.txt","r"); 
		if(myfile == NULL)
		{
		  printf("An error has happened!\n");
		  printf("Please reset everything and try again!\n");
		  exit(1);             
		}
		
		struct entity{
			char url[20];
			char username[20];
			char password[20];
		};
		struct entity new;
		//TABLE TITLES
		printf("\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 Recorded Usernames & Passwords \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n");
		printf("\t=======================================================================\n");
		printf("\tURL\t\t\t\t Username\t\t Password\n");
		printf("\t=======================================================================\n");
		char myString[100];
		int pline=0;
		while(fgets(myString, sizeof(myString),myfile) != NULL){
			pline++;
			if(pline == 1){
				myString[strcspn(myString, "\n")] = 0;
				strcpy(new.url,myString);
			}else if(pline == 2){
				myString[strcspn(myString, "\n")] = 0;
				strcpy(new.username,myString);
			}else if(pline == 3){
				myString[strcspn(myString, "\n")] = 0;
				strcpy(new.password,myString);
			}else if(pline == 4){
				printf("\t%-10s\t\t\t %-5s\t\t\t %-5s\n",&new.url,&new.username,&new.password);
				pline=0;
			}
		}
		//close the file
		fclose(myfile);
	}

// Case 2	
int* search(void){
		system("@cls||clear");
		puts("\n\n\t***********************\n\t\tSearch for Admin/Guest Usernames and/or Passwords\n\t***********************\n\n");
		// return array
		static int output[2];
		// Get the url from user
		//char key[]= {"google\n"};
		printf("\tWhere is the url? ");
		char key[100];
		char input[100];
		scanf("%s",&key);
		strcpy(input,key);
		strcat(key, "\n");
		
		// open the textfile
		FILE *myfile;
		myfile = fopen("WMS.txt","r"); 
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
		myfile = fopen("WMS.txt","r"); 
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
	
// Case 3	
void edit(void){
		puts("\n\n\t***********************\n\t\tChange the Admin/Guest Usernames and/or Passwords\n\t***********************\n\n");
		
		int* place=search();
		// return array [find, line]
		//printf("%d, %d",place[0],place[1]);
		int find=place[0];
		int line=place[1];
		if(find == 0){
			printf("\tYour desired URL does not exists!!!");
		}else{
				// Get new values
				char username[20], password[20];
				printf("\tPlease enter your new Username for this URL: ");
				scanf("%s",&username);
				printf("\tPlease enter your new Password for this URL: ");
				scanf("%s",&password);
				
				// open the textfile
				FILE *originalfile= fopen("WMS.txt","r");
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
				remove("WMS.txt");
				rename("temp.txt","WMS.txt");
				
				// double check with the user
				puts("\tThe request was successful");
				printf("\tWould you like to adjust another item(y/n): ");
				char quit;
				getchar();
				scanf("%c",&quit);
				if(quit=='y'){
					edit();
				}
			}
	};

// Case 4
void add(void){
		system("@cls||clear");
		puts("\n\n\t***********************\n\t\tAdd Guest User to WMS\n\t***********************\n\n");
		// passwords dataTypes
		struct entity{
			char url[20];
			char username[20];
			char password[20];
		};
		struct entity new;
		
		//Prompt Admin
		printf("\tTo add a new Guest username & password, please add the following inform:\n");
		printf("\turl: ");
		scanf("%s",&new.url);
		printf("\tusername: ");
		scanf("%s",&new.username);
		printf("\tpassword: ");
		scanf("%s",&new.password);
		
		// print on a textfile
		FILE *myfile;
		myfile = fopen("WMS.txt","a"); 
		if(myfile == NULL)
		{
		  printf("An error has happened!");
		  printf("Please reset everything and try again!");
		  exit(1);             
		}
		fprintf(myfile,"%s\n%s\n%s\n----------\n",&new.url,&new.username,&new.password);
		fclose(myfile);
		
		//Double check with Admin
		puts("\tThe request was successful");
		printf("\t Would you like to add another item(y/n): ");
		char quit;
		getchar();
		scanf("%c",&quit);
		if(quit=='y'){
			add();
		}
	}

// Case 5
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
				FILE *originalfile= fopen("WMS.txt","r");
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
				remove("WMS.txt");
				rename("temp.txt","WMS.txt");
				
				// double check with the user
				puts("\tThe request was successful");
				printf("\tWould you like to remove another item(y/n): ");
				char quit;
				getchar();
				scanf("%c",&quit);
				if(quit=='y'){
					delete();
				}
			}
	}

	
void main(void){
	system("@cls||clear");
	// Project Title
    puts("\n\n\t***************************************************************\n\t\tWelcome to the Warehouse Managment System (WMS)\n\t***************************************************************\n\n");
	int task;
	task=mainMenu();
		
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
		case 6:
			exit(1);
		}
		
//Repetition Request for Admin
	printf("\n\tWould you like to do another action?(y/n) ");
	char quit;
	getchar();
	scanf("%c",&quit);
	if(quit=='y'){
		main();
	}else if (quit=='n'){
		printf("\nThank you for using the Warehouse Management System! Have a good day!\n");
		exit(1);
	} 
}	
		
/*
 Menu Options
	int guestMenu(void){
		puts("\n\n\t***********************\n\t\tGuest Menu\n\t***********************\n\n");
		printf("\t[1] Search WMS for Items in Warehouse\n");
		printf("\t[2] Save List of Favorite Items\n");
		printf("\t[3] Request Borrowing/Buying Items\n");
		printf("\t[4] View Item's Borrowing History\n");
		printf("\t[5] Exit\n");
		printf("\n\tPlease select one of the above options to proceed: ");
		int input;
		scanf("%d",&input);
		if(input>=1 && input <=5){
			return input;
		}else{
			system("@cls||clear");
			printf("\t<<<Your input is not available on the Guest Menu, please try again>>>\n");
			guestMenu();
		}
*/