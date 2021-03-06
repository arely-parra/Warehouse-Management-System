
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
		puts("\n\n\t*********************************************************************\n\t\tView Admin/Guest Usernames and Passwords to Log In\n\t*********************************************************************\n\n");
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
		printf("\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 Recorded Usernames & Passwords \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n");
		printf("\t=================================================================\n");
		printf("\tKey\t\t\t\t Username\t\t Password\n");
		printf("\t=================================================================\n");
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
		puts("\n\n\t*******************************************************************************\n\t\tSearch and/or Change for Admin/Guest Usernames and/or Passwords\n\t*******************************************************************************\n\n");
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
		};
		//close the file
		fclose(myfile);
		return output;
	};
	
// Case 3 (Kamryn Hammond) (ALEX) ------
void edit(void){
		int* place=search();
		int find=place[0];
		int line=place[1];
		if(find == 0){
			printf("\tYour encrytption key does not exists!!!");
		}else{
			// Get new values
			char username[20], password[20];
			
			printf("\n\tPlease enter your new Username for this encryption key: ");
			scanf("%s",&username);
			printf("\tPlease enter your new Password for this encyrption key: ");
			scanf("%s",&password);
			
			// open the textfile
			FILE *invfile=fopen("LogIn.txt","r+");
			FILE *tempfile=fopen("tempLogin.txt","w");
			if(invfile == NULL || tempfile == NULL )
			{
			  printf("An error has happened!");
			  printf("Please reset everything and try again!");
			  exit(1);             
			}
			
			// paste all content to temporary file except the ones we want to edit
			char myString[100];
			int pline=0;
			while(fgets(myString, sizeof(myString),invfile) != NULL){
				pline++;
				if(pline != (line+1) && pline != (line+2)){//we just want to change username and password
					fprintf(tempfile,"%s",myString);
				}else if(pline == (line+1)){
					fprintf(tempfile,"%s\n",username);
				}else if(pline == (line+2)){
					fprintf(tempfile,"%s\n",password);
				}
			}
			fclose(invfile);
			
			fclose(tempfile);
			
			// remove the original file and rename the temporary file
			remove("LogIn.txt");
			rename("tempLogin.txt","LogIn.txt");
			
			// double check with the user
			puts("\n\tThe change in log-in credentials was successful!\n");
			printf("\tWould you like to change another log-in credential? (y/n): ");
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
		puts("\n\n\t*************************************\n\t\tAdd Guest User to WMS\n\t*************************************\n\n");
		// passwords dataTypes
		struct entity{
			char encrypt[20];
			char username[20];
			char password[20];
		};
		struct entity new;
		
		//Prompt Admin
		printf("\tTo add a new Guest username & password, please add the following information:\n");
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
		puts("\n\tThe request was successful!");
		printf("\n\tWould you like to add another item(y/n): ");
		char quit;
		getchar();
		scanf("%c",&quit);
		if(quit=='y'||quit=='Y'){
			add();
		}
	}

// Case 5 (Kamryn Hammond) (ALEX) ------
void delete(void){
		// We want to make sure the desired URL, Username, and Password exist
		int* place=search();
		int find=place[0];
		int line=place[1];
		if(find == 0){
			printf("\tYour desired encryption key does not exists!");
		}else{
				// open the textfile
				FILE *originalfile= fopen("LogIn.txt","r");
				FILE *tempfile= fopen("tempLogin.txt","w");
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
					}
				}
				fclose(originalfile);
				fclose(tempfile);
				
				// remove the original file and rename the temporary file
				remove("LogIn.txt");
				rename("tempLogin.txt","LogIn.txt");
				
				// double check with the user
				puts("\n\tThe guest user has been removed.\n");
				printf("\tWould you like to remove another guest user? (y/n): ");
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
	int* searchItems();
	
	system("@cls||clear");
	puts("\n\n\t******************************************\n\t\tAdd Items to WMS Inventory\n\t******************************************\n\n");
	struct entity {
		
		char Type[100];
		char ID[100];
		char Name[100];
		char store[100];
		char pick[100];
		char provider [100];
		char quantity [100];
		char place [100];
		char price [100];
		
	};
	struct entity new;
	
	// Prompt Admin
	printf("Please enter the following information\n");
	
	//Enter Item ID
	//printf("Enter Item ID: ");
	//scanf("%s",&new.ID); 
	


		static int output[2];
		printf("Enter Item ID: ");
		
		char key[100];
		char input[100];
		scanf("%s",&key);
		strcpy(input,key);
		strcat(key, "\n");
		FILE *invfile;
			invfile = fopen("inventory.txt","r");
				
				char myString[100];
				int line = 0 ;
				int find = 0;
				int fieldNumber = 0 ;
				
				
				
				while(fgets(myString, sizeof(myString),invfile) != NULL){
					line++;  fieldNumber++;
					if(strcmp(myString, key) == 0 && fieldNumber ==1) {
						printf("\nItem ID %s already exists, please use a different ID!\n", input);
						find = 1;
						output[0] = find;
						output[1] = line;
						break;
					}
					
					if(fieldNumber == 10)
					{
					fieldNumber=0;
					
					}
				}
				
				
			fclose(invfile);
			if(find !=1 ){
				
	//Enter Item ID
	printf("Please Enter ID for Verification: ");
	scanf("%s",&new.ID); 
	
	//Enter Item type 
	printf("Enter Item Type: ");
	scanf("%s",&new.Type);
	
	//Enter Item Name  
	printf("Enter Item Name ");
	scanf("%s",&new.Name);
	
	//Enter Pickout time
	printf("Enter Stored Time (MM/DD/YY_HH:MM): ");
	scanf("%s",&new.store);
	
	//Enter Pickout time
	printf("Enter Pickout Time(MM/DD/YY_HH:MM): ");
	scanf("%s",&new.pick);
			
	//Enter Company's Name 
	printf("Enter Provider Name: ");
	scanf("%s",&new.provider);
		
	//Enter Quantity
	printf("Enter Item Quantity: ");
	scanf("%s",&new.quantity);
		
	//Enter Item Location
	printf("Enter Item's Place (Shelf_#): ");
	scanf("%s",&new.place);
		
	//Price
	printf("Enter Item's Price: ");
	scanf("%s",&new.price);
	
	
	// print on a textfile
	FILE *myfile;
	myfile = fopen("inventory.txt","a");
		if (myfile == NULL)
		{
			printf("invalid file");
			exit(1);
		}
		fprintf(myfile,"%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n--------\n"
		,&new.ID,&new.Type,&new.Name,&new.store,&new.pick,&new.provider,&new.quantity,&new.place,&new.price);
		fclose(myfile);
			
		// double check with admin	
		puts("Item successfully added to WMS inventory!");
		printf("Would you like to add another item? (y/n):");
		char quit;
		getchar();
		scanf("%c",&quit);
		if(quit=='y'||quit=='Y'){
			addItems();
		}
}

else if (find ==1){
}
}





// Case 7 (Alex Vita)
int* searchItems(void){
		system("@cls||clear");
		puts("\n\n\t***********************************************************************\n\t\tSearch and/or Change for Items in the Warehouse MS\n\t***********************************************************************\n\n");
		
		static int output[2];
		printf("What is the Item ID? ");
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
				
				char myString[100];
				int line = 0 ;
				int find = 0;
				int fieldNumber = 0 ;
				while(fgets(myString, sizeof(myString),invfile) != NULL){
					line++;  fieldNumber++;
					if(strcmp(myString, key) == 0 && fieldNumber ==1) {
						printf("\nItem ID %s was found at line %d\n", input, line);
						find = 1;
						output[0] = find;
						output[1] = line;
						break;
					}
					
					if(fieldNumber == 10)
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
				printf("An error has happened!!!");
			printf("Please reset everything and try again!!!");
				exit(1);	
			}
			
			// print the information
			int pline = 0 ;
			while(fgets(myString, sizeof(myString),invfile) != NULL){
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
			
			fclose(invfile);
			return output;
			
	};	

// Case 8 (Alex Vita) 
void editItems (void){
	int* place=searchItems();
	int find = place[0];
	int line = place [1];
	if(find == 0){
		printf("\nThis Item does not exist in the WMS Inventory!\n");
	}else{
		
		// Get new values
		char Type[100];
		char ID[100];
		char Name[100];
		char store[100];
		char pick[100];
		char provider [100];
		char quantity [100];
		char place [100];
		char price [100];
		
		printf("\n\tPlease enter your new Item Type for this Item ID: ");
		scanf("%s",&Type);
		printf("\tPlease enter your new Item Name for this Item ID: ");
		scanf("%s",&Name);
		printf("\tPlease enter your new Item Stored Time (MM/DD/YY_HH:MM) for this Item ID: ");
		scanf("%s",&store);
		printf("\tPlease enter your new Item Pickout Time (MM/DD/YY_HH:MM) for this Item ID: ");
		scanf("%s",&pick);
		printf("\tPlease enter your new Item Provider Name for this Item ID: ");
		scanf("%s",&provider);
		printf("\tPlease enter your new Item Quantity for this Item ID: ");
		scanf("%s",&quantity);
		printf("\tPlease enter your new Item Place (Shelf_#) for this Item ID: ");
		scanf("%s",&place);
		printf("\tPlease enter your new Item Price for this Item ID: ");
		scanf("%s",&price);


		FILE *invfile=fopen("inventory.txt","r");
		FILE *tempfile = fopen("tempinventory.txt","w");
		if (invfile == NULL || tempfile == NULL)
		{
		printf("An error has happened!");
		printf("Please reset everything and try again!");
		exit(1);   
		}
			
		char myString[100];
		int pline = 0;
			
		while (fgets(myString, sizeof(myString),invfile) != NULL){
		pline++;
		if(pline != (line+1) && pline != (line+2) && pline != (line+3)&& pline != (line+4)&& pline != (line+5)&& pline != (line+6)&& pline != (line+7)&& pline != (line+8)){
			fprintf(tempfile,"%s",myString);
		}else if(pline == (line+1)){
			fprintf(tempfile,"%s\n",Type);
		}else if(pline == (line+2)){
			fprintf(tempfile,"%s\n",Name);
		}else if(pline == (line+3)){
			fprintf(tempfile,"%s\n",store);
		}else if(pline == (line+4)){
			fprintf(tempfile,"%s\n",pick);
		}else if(pline == (line+5)){
			fprintf(tempfile,"%s\n",provider);
		}else if(pline == (line+6)){
			fprintf(tempfile,"%s\n",quantity);
		}else if(pline == (line+7)){
			fprintf(tempfile,"%s\n",place);
		}else if(pline == (line+8)){
			fprintf(tempfile,"%s\n",price);
		}
	}
			
		fclose(invfile);
		fclose(tempfile);
			
		remove("inventory.txt");
		rename("tempinventory.txt","inventory.txt");
		
		puts("\n\tItem has been edited successfully!\n");
		printf("\tWould you like to adjust another item? (y/n): ");
		char quit;
		getchar();
		scanf("%c",&quit);
		if(quit=='y'){
			editItems();
		}
	}
};

// Case 9 (Alex Vita)
void deleteItems(void){
		int* place=searchItems();
		
		int find=place[0];
		int line=place[1];
		if(find == 0){
			printf("\tThis Item ID does not exist!");
		}else{
				FILE *invfile= fopen("inventory.txt","r");
				FILE *tempfile= fopen("tempinventory.txt","w");
				if(invfile == NULL || tempfile == NULL )
				{
				  printf("An error has happened!!!");
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
					    && pline != (line+8) && pline != (line+9)){
					fprintf(tempfile,"%s",myString);
						//printf("\t%s has been deleted\n",myString);
					}
				}
				
				fclose(invfile);
				fclose(tempfile);
				
				// remove the original file and rename the temorary file
				remove("inventory.txt");
				rename("tempinventory.txt","inventory.txt");
				
				// double check with the user
				puts("\n\tThe Item was deleted successfully from the WMS inventory!\n");
				printf("\tWould you like to remove another item? (y/n): ");
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
		puts("\n\n\t*****************************************\n\t\tView WMS Item Inventory\n\t*****************************************\n\n");
		FILE *invfile;
		invfile = fopen("inventory.txt","r"); 
		if(invfile == NULL)
		{
		  printf("An error is happend!!!");
		  printf("Please reset everything and try again!!!");
		  exit(1);             
		}
		
		struct entity{
		char Type[100];
		char ID[100];
		char Name[100];
		char store[100];
		char pick[100];
		char provider[100];
		char quantity[100];
		char place[100];
		char price[100];
	};
		struct entity new;
		//TABLE TITLES
		printf("\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 WMS Item Inventory \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n");
		printf("\t=======================================================================================================================\n");
		printf("\tID\tType\tName\t\tPicked\t\tStored\t\tProvider\tQuantity\tPlace\t\tPrice\n");
		printf("\t=======================================================================================================================\n");
		char myString[100000];
		int pline=0;
		while(fgets(myString, sizeof(myString),invfile) != NULL){
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
				strcpy(new.store,myString);
			}else if(pline == 5){
				myString[strcspn(myString, "\n")] = 0;
				strcpy(new.pick,myString);
			}else if(pline == 6){
				myString[strcspn(myString, "\n")] = 0;
				strcpy(new.provider,myString);
			}else if(pline == 7){
				myString[strcspn(myString, "\n")] = 0;
				strcpy(new.quantity,myString);
			}else if(pline == 8){
				myString[strcspn(myString, "\n")] = 0;
				strcpy(new.place,myString);
			}else if(pline == 9){
				myString[strcspn(myString, "\n")] = 0;
				strcpy(new.price,myString);
			}else if(pline == 10){
				printf("\t%-5s\t%-5s\t%-5s\t%-5s\t%-5s\t%-5s\t\t%-5s\t\t%-5s\t\t%-5s\n",&new.ID,&new.Type,&new.Name,&new.pick,&new.store,&new.provider,&new.quantity,&new.place,&new.price);
				pline=0;
			}
		}
		//close the file
		fclose(invfile);
	}
	
// Case 11 (Sophie Ross)
void viewBorrowing(void){
		system("@cls||clear");
		puts("\n\n\t****************************************************\n\t\tView Guest User's Borrowing Requests\n\t****************************************************\n\n");
		// Open the text file
		FILE *myfile;
		myfile = fopen("Requests.txt","r"); 
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
			char Length[100];
			
		};
		struct entity new;
		//TABLE TITLES
		printf("\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 Guest User's Request List \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n");
		printf("\t===============================================================================================================================\n");
		printf("\tItem ID\t Item Type\t Item Name\t\t Item Provider\t Item Quantity\t Item Place\t Item Price\t Borrowing Time\n");
		printf("\t===============================================================================================================================\n");
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
				myString[strcspn(myString, "\n")] = 0;
				strcpy(new.Length,myString);
			}else if(pline == 9){
				printf("\t%-5s\t %-10s\t %-10s\t\t %-10s\t %-5s\t\t %-5s\t %-10s\t %-5s\n",&new.ID,&new.Type,&new.Name,&new.Provider,&new.Quantity,&new.Place,&new.Price,&new.Length);
				pline=0;
			}
		}
		//close the file
		fclose(myfile);
}


// Case 12 (Sophie Ross)
void acceptDeny(void){
		system("@cls||clear");
		puts("\n\n\t****************************************************\n\t\tDeny or Accept Guest User's Requests\n\t****************************************************\n\n");
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
		printf("\tAccept Item Request? (y/n): ");
		scanf("%s",&new.accept);
		printf("\tDeny Items Request? (y/n): ");
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
		puts("\n\tYou have successfully accepted or denied this guest user's item request!\n");
		printf("\tWould you like to accept/deny another guest user's item request? (y/n): ");
		char quit;
		getchar();
		scanf("%c",&quit);
		if(quit=='y'||quit=='Y'){
			acceptDeny();
		}
	}

// Menu Switch Case for Admin Main Menu (Jarred Crystal)
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
		admin();
	}else if (quit=='n'||quit=='N'){
		printf("\nThank you for using the Warehouse Management System! Have a good day!\n");
		exit(1);
	} 
}
