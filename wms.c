#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int mainmenu(void){
	printf("Select the following options: \n");
	printf("1: Add Item\n");
	printf("2: Edit Item\n");
	printf("3: Delete Item\n");
	printf("4: View Inventory\n");
	printf("5: Exit\n");
	printf("Selection :"); 
	int edit;
	
	scanf("%d",&edit);
	if(edit>=1 && edit<=5){
		return edit;
	}else{
		printf("invalid input try again");
		mainmenu();
	}
}

void add (void){
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
					printf("invalied file");
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
					add();
				}
}

int* search(void){
		
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
					printf("invalied file");
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

void edit (void){
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
					printf("invalied file");
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
					edit();
				}
	}
}

void delete(void){
		
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
					delete();
				}
			}
	}	

void view(void){
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
	
void main(void){
	int task ;
	task = mainmenu();
	
	switch (task){
		
		case 1:
		add();
		break;
		
		case 2:
		edit();
		break;
		
		case 3:
		delete();
		break;
		
		case 4:
		view();
		break;
		
		case 5:
		exit(1);

	}
		
		//repeatation request
		printf("\n\tWould you like to do another action?(y/n) ");
		char quit;
		getchar();
		scanf("%c",&quit);
		if(quit=='y'){
			main();
		}else if (quit=='n'){
			exit(1);
		}
}

