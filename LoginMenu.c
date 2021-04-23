//* Project 4: Warehouse Management System
//* Group Name: Can You C My Screen?
//* Group Members: Arely J. Parra López, Jarred Crystal, Alexander Vita, Kamyrn Hammond, and Sophie Ross
//* Course: CSCI 1110-01 | Introduction to C Programming
//* Professor: Dr. Reza Sadeghi
//* Date: Monday, April 26th, 2021

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GuestMenu.c"
#include "AdminMenu.c"


// Menu Options for Logging In (Arely Parra López)
	int loginMenu(void){
		puts("\n\n\t****************************\n\t\t Main Menu\n\t****************************\n\n");
		printf("\t[1] Registration Page\n");
		printf("\t[2] Admin Log-In Page\n");
		printf("\t[3] Guest User Log-In Page\n");
		printf("\t[4] Exit\n");
		
		printf("\n\tPlease select one of the above options to proceed: ");
		int input;
		scanf("%d",&input);
		if(input>=1 && input <=4){
			return input;
		}else{
			system("@cls||clear");
			printf("\t<<<Your input is not available on the Admin Menu, please try again>>>\n");
			loginMenu();
		}
	}

// Case 1 (Arely Parra López)
void registration(void){
		system("@cls||clear");
		puts("\n\n\t***********************\n\t\tRegistration for New Users\n\t***********************\n\n");
		// passwords dataTypes
		struct entity{
			char encrypt[20];
			char username[20];
			char password[20];
		};
		struct entity new;
		
		// prompt user
		printf("\tTo register a new encryption key, username, & password to the WMS, please add the following information:\n");
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
		
		// double check with user
		puts("\tThe request was successful");
		printf("\t Would you like to register another url, username, and password(y/n): ");
		char quit;
		getchar();
		scanf("%c",&quit);
		if(quit=='y'||quit=='Y'){
			registration();
		}
	}

// Case 2 (Kamyrn Hammond & Arely Parra López)
int* adminLogin(void){
		system("@cls||clear");
		puts("\n\n\t***********************\n\t\tAdmin Log-In Page\n\t***********************\n\n");
	
		// return array
		static int output[2];

		printf("\tWhat is your encryption key for your login credentials? ");
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
		
		//Verify the Presence for Admin Username and Password at private url
		char myString[100];
		int line=0;
		int find=0;
		int fieldNumber=0;
		while(fgets(myString, sizeof(myString),myfile) != NULL){
			line++; fieldNumber++;
			if(strcmp(myString, key) == 0 && fieldNumber == 1){
				printf("\n\tThe system found your encrytpion key %s at line %d\n", input, line);
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
			printf("\n\tThe %s does not exist in the Admin Log-In Records.\n",input);
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
				printf("\tAccess Has Been Granted. You have logged into the WMS as an Admin.\n");
				break;
			};
		}
		
		// Done by APL (9 lines)
		printf("\tWould you like to enter the Admin Menu(y/n): ");
		char quit;
		getchar();
		scanf("%c",&quit);
		if(quit=='y'||quit=='Y'){
			adminMenu();
		}else if(quit=='n'||quit=='N'){
			loginMenu();
		}
		
		//close the file
		fclose(myfile);
		return output;
	};

// Case 3 (Kamryn Hammond & Arely Parra López
int* guestLogin(void){
		system("@cls||clear");
		puts("\n\n\t***********************\n\t\tAdmin Log-In Page\n\t***********************\n\n");
	
		// return array
		static int output[2];
		
		printf("\tWhat is your encryption key for your login credentials? ");
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
		
		//Verify the Presence for Guest Username and Password at private url
		char myString[100];
		int line=0;
		int find=0;
		int fieldNumber=0;
		while(fgets(myString, sizeof(myString),myfile) != NULL){
			line++; fieldNumber++;
			if(strcmp(myString, key) == 0 && fieldNumber == 1){
				printf("\n\tThe system found your encyrption key %s at line %d\n", input, line);
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
			printf("\n\tThe %s does not exist in the Admin Log-In Records.\n",input);
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
				printf("\tAccess Has Been Granted. You have logged into the WMS as a Guest User.\n");
				break;
			};
		}
		
		// Done by APL (9 lines)
		printf("\tWould you like to enter the Guest User Menu(y/n): ");
		char quit;
		getchar();
		scanf("%c",&quit);
		if(quit=='y'||quit=='Y'){
			guestMenu(); //// CHANGE THIS WHEN COMBINED
		}else if(quit=='n'||quit=='N'){
			loginMenu();
		}
		
		//close the file
		fclose(myfile);
		return output;
	};


// Menu Switch Case for Log-In Main Menu (Arely Parra López) 
void main(void){ 
	system("@cls||clear");
	// Project Title
    puts("\n\n\t***************************************************************\n\t\tWelcome to the Warehouse Managment System (WMS)\n\t***************************************************************\n\n");
	int task;
	task=loginMenu();
		
	switch (task){
		case 1:
			registration();
			break;
		case 2:
			adminLogin();
			break;
		case 3:
			guestLogin();
			break;
		case 4:
			printf("\nThank you for using the Warehouse Management System! Have a good day!\n");
			exit(1);
		}
		
//Repetition Request for Admin
	printf("\n\tWould you like to do another action?(y/n) ");
	char quit;
	getchar();
	scanf("%c",&quit);
	if(quit=='y'||quit=='Y'){
		loginMenu();
	}else if (quit=='n'||quit=='N'){
		printf("\nThank you for using the Warehouse Management System! Have a good day!\n");
		exit(1);
	} 
}