/*
	**************************************************************
	** 		Project that controls a library - ProLib v4.2.1		**
	** EDII - Verônica											**
	** By : Vinicius Silvestre Bueno and Pedro Henrique Botecchi**
	**************************************************************
*/

/*
	File Header includes :
		- 1 int representing the byte offset(used in exclusion)
		- 1 int representing the record used in the struct BOOKS (used to save the value of the struct when the programm is closed)
		- 1 int representing the record used in the struct BookRemover (used to save the value of the struct when the programm is closed)
*/

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#define MAXRec 16	// ** Controls the maximum value of Records
#define MAXDel 8	// ** Controls the ISBN to delete


// ** Define the Books struct form
	struct Books{
		char ISBN[14];
		char Title[50];
		char Autor[50];
		char Year[5];
	};
	// ** Define the BookRemover struct form
	struct BookRemover{
		char ISBN[14];
	};

// ** Main Functions
	void insert(FILE * Library,struct Books * books);								// ** Insert a record on Library file
	void remove_Record(FILE * Library,struct BookRemover * bookRemoverRec);			// ** BookRemover a record
	void compact(FILE * Library);													// ** Compact a File						
	void dump(FILE * Library);														// ** Makes the Dump of the Lybrary File

// ** Auxiliary Functions
	void loadMenu(FILE * Library,struct Books * books,struct BookRemover * bookRemoverRec);							// ** Load the menu
	void loadFile(FILE * DataFile,FILE * RemoveFile,struct Books * books,struct BookRemover * bookRemoverRec);		// ** Load all the records to be inserted and deleted in the FILE
	int format_record(struct Books * books,int * pos,char * record);												// ** Format the record to put in the File
	void get_record(char * record,char * ISBNR);																	// ** Get the ISBN from the read record
	int count_RecordSize(char * record);																			// ** Count the number of valid characters
	void printData(struct Books * books,struct BookRemover * bookRemoverRec);										// ** Print the content, just to see if it's right

int main()
{
	setlocale(LC_ALL,"");

	// SET UP ALL Vars
		struct Books books[MAXRec];					// ** Creating a Books vector
		struct BookRemover bookRemoverRec[MAXDel]; 	// ** Creating a BookRemover vector

		FILE * DataFile;			// ** File that contains all records to be inserted
		FILE * RemoveFile;			// ** File that contains all records to be deleted
		FILE * Library;				// ** File that contains the Library records

	// ** Calls a function to load all the data from auxiliary files
	loadFile(DataFile,RemoveFile,books,bookRemoverRec);

	if((Library = fopen("library.bin","r+b"))==NULL)			// ** Try to open the FILE, if it doesn't exist create it
	{
		fclose(Library);										// ** Close to open again (avoid erros)
		Library = fopen("library.bin","w+b");
	}

	if(Library != NULL)											// ** Check if the file exists and start the menu
	{
		loadMenu(Library,books,bookRemoverRec);
	}
	else
	{
		printf("File Error - The DataBase File could not be set up - Quiting\n");
		exit(1);
	}

	fclose(Library);
	
	return 0;
}

// ** Function that insert data in Library
void insert(FILE * Library,struct Books * books)
{
	// ** Set up vars
		// ** Loaded from the Library File
			int offset;				// ** Catch the offset if possible, this is the record List in case of exclusion
			int recordNumber = 0;	// ** Controls the record inserted from struct Books
			int removeNumber = 0;	// ** Controls the record removal from struct Books
		int record_Len;			// ** Controls the lenght of a formated record
		int flag = 0;			// ** Controls if a record was inserted or not, or if all records were inserted
		// ** OffSet Stack 
			int actualPointer;		// ** Receive the actual offset, to move with the Stack. They're not pointers, it's just to make it easier
			int nextPointer;		// ** Receive the next offset, to move with the Stack
			int temp;				// ** Save the value of the stack

		char record[120];		// ** String that will contain the full record formated

		int max;				// ** value that the user type to add multiple records

	printf("\nType how many records would you like to insert : ");		// ** The user can insert thow many records he wanted in a row, but we need to verify the space
	scanf("%d",&max);

	if((max > MAXRec)||(max < 0))			// ** Verufy if it's valid
	{
		do
		{
			if (max > MAXRec)				// ** If pass MAXRec, then we can't insert all of them
			{
				printf("\nThe system can't insert all these values. Reducing to the max (%d values) : ",MAXRec);
				system("PAUSE");
				max = MAXRec;
			}
			else 							// ** Else, it's just an invalid number
			{
				printf("\nInvalid value. Type again : ");
				max = getche() - '0';
			}			
		}while((max > MAXRec)||(max < 0));
	} 
	
	while((max!=0)&&(flag!=2))								// ** While, max!=0, or flag !=2 (control the maximum number of records that can be insert, if passed marks flag = 2)
	{
		flag = 0;

		fseek(Library,0,SEEK_SET);							// ** Set the beginning of file

		if(fread(&offset,sizeof(int),1,Library))			// ** Try to catch the byte offset
		{
			fread(&recordNumber,sizeof(int),1,Library);		// ** If it catched the offset, we must see in which record it stopped recording, so we catch another byte to see this
			fseek(Library,4,SEEK_CUR);						// ** Jump the removal number, 'cause it's not necessary now

			if(recordNumber<MAXRec)							// ** Verifies if the next record don't surpass MAXRec
			{
				actualPointer = 0;							// ** Set the beginning of the stack
				nextPointer = offset;						// ** Save the next value of the stack

				record_Len = format_record(books,&recordNumber,record);			// ** Format the record, and receive it's size

				// ** If there's a space in the File, try to fill it with the new record
				while((offset!=-1)&&(!flag))
				{
					int recordSize = 0;										// ** Auxiliary to receive the size of a read record
					fseek(Library,(offset),SEEK_SET);						// ** Jump to catch the next Offset
					fread(&recordSize,sizeof(int),1,Library);				// ** Read the size of the Offset

					if(recordSize>=record_Len)
					{
						fseek(Library,1,SEEK_CUR);							// ** Go to the offset, jumping '*'
						fread(&temp,sizeof(int),1,Library);					// ** Save the next

						fseek(Library,-5,SEEK_CUR);							// ** Return to insert
						fwrite(record, sizeof(char), record_Len, Library);	// ** Insert the new record
						if(recordNumber>record_Len)
							fputc('%',Library);								// ** COntrols end of the new record

						fseek(Library,actualPointer,SEEK_SET);				// ** Moves to previous element
						fwrite(&temp,sizeof(int),1,Library);				// ** Change the previous pointer
			        	fwrite(&recordNumber,sizeof(int),1,Library);		// ** Write the number of the next record in the struct
						flag = 1;											// ** Mark flag
					}
					else
					{
						fseek(Library,1,SEEK_CUR);							// ** Jump to the next Offset
						fread(&offset,sizeof(int),1,Library);				// ** Read it
						actualPointer = nextPointer;						// ** Move the stack
						nextPointer = offset;								// ** Move the stack
					}
				}

				if(!flag)
				{
					fseek(Library,0,SEEK_END);							// ** Moves to the final
					fwrite(&record_Len, sizeof(int), 1, Library);		// ** Insert the record lenght
			        fwrite(record, sizeof(char), record_Len, Library);	// ** Insert the record
			        fseek(Library,4,SEEK_SET);							// ** Moves to header
			        fwrite(&recordNumber,sizeof(int),1,Library);		// ** Write the number of the next record in the struct
			        flag = 1;
				}
			}
			else
			{
				printf("\nThere's no more records to be inserted\n");
				flag = 2;
			}
		}
		else
		{
			// ** if there's is nothing in the file, we must add the header (which will have, 1 Int representing the offset and 1 int for the record control)
			offset = -1;

			fwrite(&offset,sizeof(int),1,Library);						// ** Write the Offset

			record_Len = format_record(books,&recordNumber,record);

			fwrite(&recordNumber,sizeof(int),1,Library);				// ** Write the number of the next record in the struct Books
			fwrite(&removeNumber,sizeof(int),1,Library);				// ** Write the number of the next record to BookRemover in the struct BookRemover

			fwrite(&record_Len, sizeof(int), 1, Library);				// ** Write the record lenght
	        fwrite(record, sizeof(char), record_Len, Library);			// ** Write the record

	        flag = 1;
		}	
		max--;
	}
	if(flag == 1)					// ** Verify if the record was seccessfully inserted
	{
        printf("\nSuccessfully inserted the record\n");
	}
	else if(flag == 0) 				// ** Else, shows a error message
	{
		printf("\nError - The record couldn't be inserted\n");
	}
	system("PAUSE");
}

// ** Function that BookRemovers a record in Library
void remove_Record(FILE * Library,struct BookRemover * bookRemoverRec)
{
	int removeNumber = 0;			// ** Controls the number in the struct BookRemover
	int offset;						// ** Controls the offset from the header
	int offsetR;					// ** Offset obtained from the BookRemoverd record
	char record[120];				// ** String to catch all the record
	int record_size;				// ** Catch the record size
	int actualPosition;				// ** will mark the actual position to became the new offset to jump
	int flag = 0;						// ** Auxiliary to mark if a exclusion was successful

	char ISBNR[14];					// ** String to save the ISBN from the read record 

	fseek(Library,0,SEEK_SET);		// ** Return to the File beginning

	if(fread(&offset,sizeof(int),1,Library))		// ** Verify if the file isn't empty
	{
		fseek(Library,4,SEEK_CUR);					// ** Jump to catch the BookRemover number in the struct
		fread(&removeNumber,sizeof(int),1,Library);	// ** Catch the removal number

		if(removeNumber<MAXDel)
		{
			while((!flag)&&(fread(&record_size,sizeof(int),1,Library)))								// ** Read the int with the record size
			{
				fread(record,record_size,1,Library);		// ** Read the record

				get_record(record,ISBNR);					// ** Catch ISBNR to BookRemover

				if(!strcmp(ISBNR,bookRemoverRec[removeNumber].ISBN))
				{
					fseek(Library,-(record_size + 4),SEEK_CUR);		// ** return to record_size + 4 'cause i need to catch the offset
					offsetR = ftell(Library);						// ** Catch the new offset to insert

					fseek(Library,4,SEEK_CUR);						// ** Move to insert in the format <Past Record Size>*<Next Offset>
					fputc('*',Library);								// ** Insert the marker
					fwrite(&offset,sizeof(int),1,Library);			// ** Write the old offset pointed by offset

					fseek(Library,0,SEEK_SET);						// ** Return to the beginning
					fwrite(&offsetR,sizeof(int),1,Library);			// ** Put the new value in the header

					removeNumber++;									// ** Increment the number to BookRemover	
					fseek(Library,4,SEEK_CUR);						// ** Move to jump the struct Books controller
					fwrite(&removeNumber,sizeof(int),1,Library);	// ** Change the removal control

					flag = 1;										// ** Mark as deleted
				}
			}

			if(flag == 1)					// ** Verify if the record was seccessfully inserted
			{
		        printf("\nThe record was successfully removed\n");
		        system("PAUSE");
			}
			else if(flag == 0) 						// ** Else, shows a error message
			{
				printf("\nError - The record couldn't be removed\n");
				printf("\nMoving to the next one to delete\n");
				
				removeNumber++;									// ** Increment the number to BookRemover	
				fseek(Library,8,SEEK_SET);						// ** Move to jump the struct Books controller
				fwrite(&removeNumber,sizeof(int),1,Library);	// ** Change the removal control
		        system("PAUSE");
			}
		}
		else
		{
			printf("\nThere are no ISBN left to be deleted\n");
			system("PAUSE");
		}
	}
}

// ** Function that catch the values of a record
void get_record(char * record,char * ISBNR)
{
	int i = 0;				// ** Controls the letter position
	char ch;				// ** Receive the chars

	ISBNR[i] = '\0';		// ** Add end of string in the beginnig of ISBRN
	
	ch = record[i];
	while(ch !='#')	// ** As i know i just want the first field, I will read onli till the fiste pipeline
	{
		ISBNR[i] = ch;			// ** Put ch in the string
		i++;
		ch = record[i];				// ** increment i
	}

	ISBNR[i] = '\0';			// ** Add the End of string
}

// ** Function that Compacts a File, removing internal and external fragmentation
void compact(FILE * Library)
{
	FILE * temporary; 		// ** File that will help the compactation
	int auxL;				// ** Help to copy int values from Library
	int auxR;				// ** Help to count the record size 
	char auxS[160];			// ** Help to control string values (used in the records)
	char ch;				// ** char to verify the '*' character

	if((temporary = fopen("temporary.bin","w+b"))==NULL)
	{
		printf("\nError - compactation will be canceled\n");
	}
	else
	{
		fseek(Library,0,SEEK_SET);					// ** Return to the File beginning

		if(fread(&auxL,sizeof(int),1,Library))		// ** Start copying the header if the first int exists
		{
			auxL = -1;								// ** Write -1 in the offset, because there's no queue anymore
			fwrite(&auxL,sizeof(int),1,temporary);	// ** Write the offset in the temporary file 

			fread(&auxL,sizeof(int),1,Library);		// ** Read the struct Books number in the library file
			fwrite(&auxL,sizeof(int),1,temporary);	// ** Write the struct Books number in the temporary file

			fread(&auxL,sizeof(int),1,Library);		// ** Read the struct BookRemover number in the library file
			fwrite(&auxL,sizeof(int),1,temporary);	// ** Write the struct Books number in the temporary file

			while(fread(&auxL,sizeof(int),1,Library))	// ** read the first, while it's still possible to read something
			{
				if((ch = fgetc(Library))=='*')			// ** Verify if the record was deleted and it's just occuping space
					fseek(Library,auxL-1,SEEK_CUR);			// ** Return the position of what was the possible '*', and move to the next size of file
				else
				{
					fseek(Library,-1,SEEK_CUR);			// ** Return the position to read the full record size

					fread(auxS,sizeof(char),auxL,Library);	// ** Read the record
					auxR = count_RecordSize(auxS);			// ** Count how many valid letters are in the record

					if(auxR == auxL)						// ** If it was of the same lenght of auxL, it means that the file is ok
					{
						fwrite(&auxL,sizeof(int),1,temporary);		// ** insert the lenght
						fwrite(auxS,sizeof(char),auxL,temporary);	// ** insert the record
					}
					else											// ** Else the record is in place of another, and we have a internal fragmentation
					{
						fwrite(&auxR,sizeof(int),1,temporary);		// ** Write the correct size
						fwrite(auxS,sizeof(char),auxR,temporary);	// ** insert the record
					}
				}
			}
			
			fclose(temporary);
			fclose(Library);
			
			if(remove("library.bin") == 0)					// ** BookRemover the old File
			{	
				rename("temporary.bin","library.bin");		// ** Replace for the new one
				
				Library = fopen("library.bin","r+b");		// ** Re-open the new file

				printf("\ncompactation was successfully\n");
				system("PAUSE");
			}	
			else
			{
				printf("\nFail to delete File\n");
				system("PAUSE");	
			}
		}		
		
	}
}

// ** Count how many valid character we have in a record
int count_RecordSize(char * record)
{
	int aux = 0;		// ** Controls record Size

	while(record[aux]!='\0')
	{
		aux++;		// ** increment aux
	}
	aux++;	// ** Count the \0

	return aux;
}

// ** Function that makes the DUMP 
void dump(FILE * Library)
{
	unsigned char ch;	// Controls the letters typed
	
	int count = 0;		// Counts till 16, than change the line
	int i;
	char dumpA[17];		// ** Dump Auxiliary that will receive a string
	
	fseek(Library,0,SEEK_SET);		// ** Return to the File beginning

	if (!fread(&ch,sizeof(unsigned char),1,Library))
	{
		printf("\nFile is Empty. Try to insert some records\n");
		system("PAUSE");
	}
	else
	{
		system("CLS");
		printf("Dumping FILE ...\n\n");
		
		fseek(Library,0,SEEK_SET);

		while(fread(&ch,sizeof(unsigned char),1,Library))
		{
			dumpA[count] = ch;				// ** Save ch	
			
			if(count<16)					// ** This controls the line
				{
					printf("%2X  ", ch);	// ** Print in Hex
					count++;				// ** increase count
				}
			else							// ** Entering here means that 16 characters were printed in HEX
				{
					dumpA[count] = '\0'; 	// ** Add end of string, even though it's not necessary
					printf("\t");					// ** creates the separator between the tables
					for(i=0;i<16;i++)				// ** How i know that i printed 16 characters, then just print the again, but this time using %c
					{
						if(isprint(dumpA[i]))							// ** If it's a printable character, prints
							printf("%c  ", dumpA[i]);
						else
							printf(".  ");								// ** Else, we put a . in place
					}
					printf("\n");										// ** Change the line

					fseek(Library,-1,SEEK_CUR);							// ** Return 1 position, because fread read a character that was not counted
					count = 0;											// ** Reset count
				}
		}
		
		dumpA[count] = '\0'; 						// ** That is not necessary, but we put just to end the string
		int blank = 16 - count;						// ** Auxiliary to know how many characters were printed before loop ending
	
		for(i = blank; i>0;i--)						// ** For each character not printed, puts a espace between then to fill the first column
			printf("    ");
				
		printf("\t");								// ** Separates the columns again
		
		for(i=0;i<count;i++)						// ** Now, just print the last character as %c
		{
			if(isprint(dumpA[i]))
				printf("%c  ", dumpA[i]);
			else
				printf(".  ");	
		}
		
		printf("\n\n");
		system("PAUSE");			
	}
}

// ** Function that loads the menu 
void loadMenu(FILE * Library,struct Books * books,struct BookRemover * bookRemoverRec)
{
	char answer;			// ** Control the typed answer for menu
	int ia;					// ** IntegarAnswer, tranforms in int to verify answer
	do
	{		
		system("CLS");
		printf("::::: PROJECT LYBRARY SISTEM v4.2.1 :::::\n\n");
		printf("1 - Insert a Book\n2 - Remove a Book\n\nSupport Options : \n3 - Compact the File\n4 - DUMP File\n\n0 - Exit\n\nType an option : ");
		ia = getche();
		ia = ia - '0';				// ** Transforms answer in int ('0' = 48)

		switch(ia) 
		{
			case 1 : 
			{
				insert(Library,books);					// ** Calls insert
				break;
			}
			case 2 :
			{
				remove_Record(Library,bookRemoverRec);	// ** Calls remove
				break;
			}
			case 3 :
			{
				compact(Library);						// ** Calls compact
				break;
			}
			case 4 :
			{
				dump(Library);							// ** Calls dump
				break;
			}
			case 5 :
			{
				printData(books,bookRemoverRec);		// ** Calls print (FIXME - DEBUG)
				break;
			}
			case 0 :
			{
				break;
			}
			default :
			{
				printf("\n\nInvalid option. Please, retype\n");
				system("PAUSE");
				break;
			}
		}
	}while((ia!=0));
}

// ** Function that load the File with all records to be inserted and BookRemoverd
void loadFile(FILE * DataFile,FILE * RemoveFile,struct Books * books,struct BookRemover * bookRemoverRec)
{
	// ** Verify if the files can be opened
	if((((DataFile = fopen("biblioteca.bin","r+b")) == NULL))||((RemoveFile = fopen("remove.bin","r+b"))==NULL))
	{
		printf("Error - The Data Files could not be open. Quiting\n");		// ** if one of them couldn't quit the program
		getch();
		exit(1);
	}
	else
	{
		int i;
		for(i=0;i<MAXRec;i++)
		{
			fread(&books[i],sizeof(struct Books),1,DataFile);		// ** How I know the maximum number of records, we just use a for
		}

		for(i=0;i<MAXDel;i++)
		{
			fread(&bookRemoverRec[i],sizeof(struct BookRemover),1,RemoveFile);// ** How I know the maximum number of records to be BookRemovers, just use a for
		}
	}

	fclose(DataFile);
}

// ** Function that format the record to put in the file
int format_record(struct Books * books,int * pos,char * record)
{
	int len;		// ** Receive the formated record lenght

	sprintf(record,"%s#%s#%s#%s",books[*pos].ISBN,books[*pos].Title,books[*pos].Autor,books[*pos].Year);
   	(*pos)++;			// ** Mark the record as inserted and move to the next
    len = strlen(record);
    len++;				// ** Inclues end of string

    return len;
}

// ** Function that print all datas (to be BookRemoverd and to be inserted) DON'T NEED THIS IN THE FINAL PROGRAMM IT'S JUST TO MAKE OUR LIVES EASIER
void printData(struct Books * books,struct BookRemover * bookRemoverRec)
{
	int i;
	
	system("cls");
	printf("Printing all records to be inserted and the primary keys to be deleted\n\n");

	for(i = 0; i<MAXRec; i++)
	{
		printf("ISBN : %s\n",books[i].ISBN);
		printf("TITLE : %s\n",books[i].Title);
		printf("AUTOR : %s\n",books[i].Autor);
		printf("YEAR :%s\n",books[i].Year);
	}
	printf("\n\nData to DELETE : \n");
	for(i = 0; i<MAXDel; i++)
	{
		printf("ISBN : %s\n",bookRemoverRec[i].ISBN);
	}

	system("PAUSE");
}