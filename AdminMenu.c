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
		printf("\t[7] Search Items from Warehouse\n");
		printf("\t[8] Edit Items from Warehouse\n");
		printf("\t[9] Delete Items from Warehouse\n");
		printf("\t[10] View Items from Warehouse\n");
		printf ("\t[11] View List of Borrowing Requests\n");
		printf("\t[12] Accept or Deny Borrowing Requests\n");
		printf("\t[13] Exit\n");
		
		printf("\n\tPlease select one of the above options to proceed: ");
		int input;
		scanf("%d",&input);
		if(input>=1 && input <=13){
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

// Case 6 (Alex Vita)
void addItems (void){
	struct entity {
		
		char type[100];
		char ID[100];
		char store[100];
		char pick[100];
		char creator [100];
		char qty [100];
		char place [100];
		char price [100];
	};
	struct entity new;
	printf("Please enter the following information\n");
	
			//Enter Item Name
		printf("Enter A 4 Character ID: ");
		scanf("%c",&new.ID); //clears buffer
		scanf("%[^\n]",&new.ID);
				
		
			//Enter product type 
		printf("Item Type: ");
		scanf("%c",&new.type);
		scanf("%[^\n]",&new.type);
		
				//Enter Pickout time
		printf("Enter Stored Time (M/D/Y H:M): ");
		scanf("%c",&new.store); //clears buffer
		scanf("%[^\n]",&new.store);
		
			//Enter Pickout time
		printf("Enter Pickout Time (M/D/Y H:M): ");
		scanf("%c",&new.pick); //clears buffer
		scanf("%[^\n]",&new.pick);
				
			//Enter Comments 
		printf("Enter Your Name: ");
		scanf("%c",&new.creator); //clears buffer
		scanf("%[^\n]",&new.creator);
			
			//Enter Quatity
		printf("Enter Quatity: ");
		scanf("%c",&new.qty);
		scanf("%[^\n]",&new.qty);
			
			//Enter Item Location
		printf("Enter Storage Location: ");
		scanf("%c",&new.place); //clears buffer
		scanf("%[^\n]",&new.place);
			
			//Price
		printf("Enter Price: ");
		scanf("%c",&new.price);
		scanf("%[^\n]",&new.price);
		
	

	
		FILE *invfile;
			invfile = fopen("inventory.txt","a");
				if (invfile == NULL)
				{
					printf("invalid file");
					exit(1);
				}
				fprintf(invfile,"%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n--------\n"
				,&new.ID,&new.type,&new.store,&new.pick,&new.creator,&new.qty,&new.place,&new.price);
				fclose(invfile);
				
				puts("Request Succesful");
				printf("Would you like to add another item (y/n):");
				char quit;
				getchar();
				scanf("%c",&quit);
				if(quit =='y'){
					addItems();
				}
}

// Case 7 (Alex Vita)
int* searchItems(void){
		
		static int output[2];
		printf("What is the Name?");
		char key[100];
		char input[100];
		scanf("%s",&key);
		strcpy(input,key);
		strcat(key, "\n");
		
		FILE *invfile;
			invfile = fopen("inventory.txt","r");
				if (invfile == NULL)
				{
					printf("invalid file");
					exit(1);
				}
				
				char mystring[100];
				int line = 0 ;
				int find = 0;
				int fieldNumber = 0 ;
				while(fgets(mystring, sizeof(mystring),invfile) != NULL){
					line++;  fieldNumber++;
					if(strcmp(mystring, key) == 0 && fieldNumber ==1) {
						printf("\n found %s at line %d\n", input, line);
						find = 1;
						output[0] = find;
						output[1] = line;
						break;
					}
					if(fieldNumber == 8)
					{
					fieldNumber=0;
					}
				}
				
				fclose(invfile);
				if(find ==0 ){
					printf("\ndoes not exist 1\n");
					return output;
				}
				
			invfile = fopen("inventory.txt","r");
			if (invfile == NULL)
			{
				printf("\n ERROR \n");
				exit(1);
				
			}
			
			int pline = 0 ;
			while(fgets(mystring, sizeof(mystring),invfile) != NULL){
				pline++;
				if (pline == (line+1)){
					printf("Stored: %s", mystring);
				}
				else if (pline == (line+2)){
					printf("Picked: %s", mystring);
					
				}
				else if (pline == (line+3)){
					printf("ID: %s", mystring);
					
				}
				else if (pline == (line+4)){
					printf("Creator: %s", mystring);
					
				}
				else if (pline == (line+5)){
					printf("QTY: %s", mystring);
					
				}
				else if (pline == (line+6)){
					printf("Location: %s", mystring);
					
				}
				else if (pline == (line+7)){
					printf("Price: %s", mystring);
					break;
				};
			}
			
			fclose(invfile);
			return output;
			
	};	

// Case 8 (Alex Vita)
void editItems (void){
	int* place = search();
	int find = place[0];
	int line = place [1];
	if(find == 0){
		printf("\n Does not exist\n");
	}
	else
	{
		char name[20], type[20];
		printf("Enter the name:");
		scanf("%s", &name);
		printf("Enter the type:");
		scanf("%s", &type);
		
			FILE *invfile;
			invfile = fopen("inventory.txt","r");
			
			FILE *tempfile;
			tempfile = fopen("temp.txt","w");
			
				if (invfile == NULL || tempfile == NULL)
				{
					printf("invalid file");
					exit(1);
				}
				
				char mystring[100];
				int pline = 0;
				
				while (fgets(mystring, sizeof(mystring),invfile) != NULL){
				pline++;
				if(pline != (line+1) && pline != (line+2))
				{
					fprintf(tempfile,"%s",mystring);
				}
				else if(pline == (line+1))
				{
					fprintf(tempfile,"%s\n",name);	
				}
				else if(pline == (line+2))
				{
					fprintf(tempfile,"%s\n",type);
				}
				}
				
				fclose(invfile);
				fclose(tempfile);
				
				remove("inventory.txt");
				rename("temp.txt","inventory.txt");
				
				puts("\tThe request was successful");
				printf("\tWould you like to adjust another item(y/n): ");
				char quit;
				getchar();
				scanf("%c",&quit);
				if(quit=='y'){
					editItems();
				}
	}
}

// Case 9 (Alex Vita)
void deleteItems(void){
		
		int* place=search();
		
		int find=place[0];
		int line=place[1];
		if(find == 0){
			printf("does not exist");
		}else{
				
				FILE *invfile= fopen("inventory.txt","r");
				FILE *tempfile= fopen("temp.txt","w");
				if(invfile == NULL || tempfile == NULL )
				{
				  printf("An error is happend!!!");
				  printf("Please reset everything and try again!!!");
				  exit(1);             
				}
				
				// paste all content of the original file to the temporary file except the ones that we want to remove
				char myString[100];
				int pline=0;
				while(fgets(myString, sizeof(myString),invfile) != NULL){
					pline++;
					if(pline != line && pline != (line+1) && pline != (line+2) && pline != (line+3)
						&& pline != (line+4) && pline != (line+5)&& pline != (line+6) && pline != (line+7)
					    && pline != (line+8)){
						fprintf(tempfile,"%s",myString);
						//printf("\t%s has been deleted\n",myString);
					}
				}
				fclose(invfile);
				fclose(tempfile);
				
				// remove the original file and rename the temorary file
				remove("inventory.txt");
				rename("temp.txt","inventory.txt");
				
				// doauble check with the user
				puts("\tThe request was successful");
				printf("\tWould you like to remove another item(y/n): ");
				char quit;
				getchar();
				scanf("%c",&quit);
				if(quit=='y'){
					deleteItems();
				}
			}
	}	

// Case 10 (Alex Vita)
void viewItems(void){
		system("@cls||clear");
		
		FILE *invfile;
		invfile = fopen("inventory.txt","r"); 
		if(invfile == NULL)
		{
		  printf("An error is happend!!!");
		  printf("Please reset everything and try again!!!");
		  exit(1);             
		}
		
		struct entity {
		char type[100];
		char ID[100];
		char store[100];
		char pick[100];
		char creator [100];
		char qty [100];
		char place [100];
		char price [100];
	};
		struct entity new;
		//TABLE TITLES
		printf("\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 Inventory \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n");
		printf("\t=======================================================================\n");
		printf("\tType\t\tStored\t\tPicked\t\t\tID\tCreator\t\tQTY\tLocation\tPrice\t \n");
		printf("\t=======================================================================\n");
		char myString[100];
		int pline=0;
		while(fgets(myString, sizeof(myString),invfile) != NULL){
			pline++;
			if(pline == 1){
				myString[strcspn(myString, "\n")] = 0;
				strcpy(new.type,myString);
			}else if(pline == 2){
				myString[strcspn(myString, "\n")] = 0;
				strcpy(new.store,myString);
			}else if(pline == 3){
				myString[strcspn(myString, "\n")] = 0;
				strcpy(new.pick,myString);
			}else if(pline == 4){
				myString[strcspn(myString, "\n")] = 0;
				strcpy(new.ID,myString);
			}else if(pline == 5){
				myString[strcspn(myString, "\n")] = 0;
				strcpy(new.creator,myString);
			}else if(pline == 6){
				myString[strcspn(myString, "\n")] = 0;
				strcpy(new.qty,myString);
			}else if(pline == 7){
				myString[strcspn(myString, "\n")] = 0;
				strcpy(new.place,myString);
			}else if(pline == 8){
				myString[strcspn(myString, "\n")] = 0;
				strcpy(new.price,myString);
			}else if(pline == 9){
				printf("\t%-10s\t\t%-5s\t\t%-5s\t%-5s\t%-5s\t\t%-5s\t%-5s\t%-5s\n",
				&new.type,&new.store,&new.pick,&new.ID,&new.creator,&new.qty,&new.place,&new.price);
				pline=0;
			}
		}
		//close the file
		fclose(invfile);
	}
	
// Case 11 (Sophie Ross)
void viewBorrowing(void){
		system("@cls||clear");
		puts("\n\n\t***********************\n\t\tView User's Borrowing Request\n\t***********************\n\n");
		// Open the text file
		FILE *myfile;
		myfile = fopen("List.txt","r"); 
		if(myfile == NULL)
		{
		  printf("An error has happened!\n");
		  printf("Please reset everything and try again!\n");
		  exit(1);             
		}
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
		printf("\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 Favorite Item List \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n");
		printf("\t=======================================================================\n");
		printf("\tItem Type\t\t Item ID\t\t Item Name\t\t Item Provider\t\t Item Quantity\t\t Item Place\t\t Item Price\n");
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
				printf("\t%-5s\t\t %-5s\t\t %-5s\t\t %-5s\t\t %-5s\t\t %-5s\t\t %-5s\t\t %-5s\n",&new.Type,&new.ID,&new.Name,&new.Provider,&new.Quantity,&new.Place,&new.Price);
				pline=0;
			}
		}
		//close the file
		fclose(myfile);
	}
}


// Case 12 (Kamryn Hammond)
void acceptDeny(void){
		system("@cls||clear");
		puts("\n\n\t***********************\n\t\tDeny or Accept Guest User's Requests\n\t***********************\n\n");
		// passwords dataTypes
		struct entity{
			char ID[20];
			char accept[20];
			char deny[20];
		};
		struct entity new;
		
		//Prompt Admin
		printf("\tTo accept or deny the Guest User's requests:\n");
		printf("\tItem ID: ");
		scanf("%s",&new.ID);
		printf("\tAccept (y/n): ");
		scanf("%s",&new.accept);
		printf("\tpassword: ");
		scanf("%s",&new.deny);
		
		// print on a textfile
		FILE *myfile;
		myfile = fopen("AcceptDeny.txt","a"); 
		if(myfile == NULL)
		{
		  printf("An error has happened!");
		  printf("Please reset everything and try again!");
		  exit(1);             
		}
		fprintf(myfile,"%s\n%s\n%s\n----------\n",&new.ID,&new.accept,&new.deny);
		fclose(myfile);
		
		//Double check with Admin
		puts("\tThe request was successful");
		printf("\t Would you like to add another item(y/n): ");
		char quit;
		getchar();
		scanf("%c",&quit);
		if(quit=='y'||quit=='Y'){
			acceptDeny();
		}
	}

// Menu Switch Case for Admin Main Menu (Kamyrn Hammond)
void admin(void){
	system("@cls||clear");
	// Project Title
    puts("\n\n\t***************************************************************\n\t\tWelcome to the Warehouse Managment System (WMS)\n\t***************************************************************\n\n");
	int option;
	option=adminMenu();
		
	switch (option){
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
			addItems();
			break;
		case 7:
			searchItems();
			break;
		case 8:
			editItems();
			break;
		case 9:
			deleteItems();
			break;
		case 10:
			viewItems();
			break;
		case 11:
			viewBorrowing();
			break;
		case 12:
			acceptDeny();
			break;
		case 13:
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

