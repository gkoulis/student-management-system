/*********************************
* Programmer: Dimitrios Gkoulis  *
* Mail: it21204@hua.gr           *
* Harokopio University of Athens *
* 2nd Project - Spring semeser   *
* Period: 2012 - 2013            *
*********************************/


/* I N C L U D E S */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

/* D E F I N E S */

/* A R R A Y S '    S I Z E */
#define ARRAYLENGTH 100    //Array length for name and surname arrays.
#define ARRAYLENGTH_AM 7   //6 digits and \0.
#define ARRAYLENGTH_YEAR 5 //4 digits and \0.

/* Y E A R S '    L I M I T S */
#define YEAR_MIN 1990
#define YEAR_MAX 2050

/* R E G I S T R A T I O N    Y E A R S '    L I M I T S */
#define AM_MIN 199000
#define AM_MAX 205099


/* Struct with students' data. */
struct elements{
    char AM[ARRAYLENGTH_AM];     //Student's AM.
    char name[ARRAYLENGTH];      //Student's name.
    char surname[ARRAYLENGTH];   //Student's surname.
    char year[ARRAYLENGTH_YEAR]; //Student's registration year.
    struct elements *ptrNext;    //Pointer to next student.
};

typedef struct elements Elements;
typedef Elements *ptrElements;

/* F U N C T I O N S */
void MainMenu(); //Main Menu of program.

void UsersInput(ptrElements *startPtr); //Users Input for New Student.

int  CheckUsersInputName(char table[ARRAYLENGTH]); //Check for correct Name and Surname.

int  CheckUsersInputYear(int Year); //Check for correct Registration Year.

int  AMGenerator(ptrElements currentPtr, char tableName[ARRAYLENGTH], char tableSurname[ARRAYLENGTH], char tableYear[ARRAYLENGTH_YEAR], int Year); //This function calculates each student's registrtion number based on position in list (alphabetical order).

void InsertElements(ptrElements *sPtr, char tableAM[ARRAYLENGTH_AM], char tableName[ARRAYLENGTH], char tableSurname[ARRAYLENGTH], char tableYear[ARRAYLENGTH_YEAR]); //This function inserts stundents' registration number, name, surname and year to list, sorted by registration number.

int  ListIsEmpty(ptrElements sPtr); //Check if list is empty.

void PrintList(ptrElements currentPtr); //Show list with students from list.

void EditStudent(ptrElements currentPtr); //Edit student. (Search by AM).

int  DeleteStudent(ptrElements *sPtr); //Delete student from list.

void ReduceAM(ptrElements currentPtr, int am); //Reduce the rest of students' AM -1. (After deleted student).

void SaveToFile(ptrElements currentPtr); //Save list to file.

void LoadFile(ptrElements *startPtr); //Load students from file to list.


/* M A I N */
int main()
{
    MainMenu(); //Go to main menu.
    
    return 0;   //Return zero. Success. End of program.
} //End of MAIN.


/* P R O G R A M ' S    M A I N    M E N U */
void MainMenu()
{
    system("cls");   //clear screen.
    
    int selection=0; //Each option has a number. This number called selection.
    int input=0;     //User's input.
    
    int am;          //This vaiables will be needed to the function RaiseAM. After delete the rest of the students' am will raise up +1.
    
    ptrElements startPtr=NULL; //Initialization of pointer to struct.
    
    LoadFile(&startPtr);       //Load students' data from file to list.
    
    //How menu will shown up.
    while(true) {
        
        system("cls"); //Clear screen.
        
        if(selection==0) {
            printf("> New student\n  Edit student\n  Delete student\n  List of students\n  Save\n  Exit\n\n\n");
        }
        else if(selection==1) {
            printf("  New student\n> Edit student\n  Delete student\n  List of students\n  Save\n  Exit\n\n\n");
        }
        else if(selection==2) {
            printf("  New student\n  Edit student\n> Delete student\n  List of students\n  Save\n  Exit\n\n\n");
        }
        else if(selection==3) {
            printf("  New student\n  Edit student\n  Delete student\n> List of students\n  Save\n  Exit\n\n\n");
        }
        else if(selection==4) {
            printf("  New student\n  Edit student\n  Delete student\n  List of students\n> Save\n  Exit\n\n\n");
        }
        else if(selection==5) {
            printf("  New student\n  Edit student\n  Delete student\n  List of students\n  Save\n> Exit\n\n\n");
        }
        
        input = _getch(); //input from user (UP, DOWN, ENTER).
        
        if(input==13) {
        
            if(selection==0) {
                UsersInput(&startPtr); //User's selection: New student.
            }
            else if(selection==1) {
                EditStudent(startPtr); //Edit student. (Search by registration number).
            }
            else if(selection==2) {
                am=DeleteStudent(&startPtr); //Delete student. (Search by registration number).
                //Reduce the rest of students' AM -1. (After deleted student).
                if(am!=1) {
                    ReduceAM(startPtr, am);
                } //end if.
            }
            else if(selection==3) {
                PrintList(startPtr); //Show the list of students.
            }
            else if(selection==4) {
                
                system("cls"); //Clear bad data from buffer.
                 
                if(ListIsEmpty(startPtr)) {
                    printf("No students in list!\n\n");
                } //End if.
                else {
                    SaveToFile(startPtr); //Save list to file.
                    printf("List of students successfully saved!\n\n");
                } //End else.
                
                system("PAUSE");
                
            }
            else if(selection==5) {
                SaveToFile(startPtr); //Save list to file. (Before program's exit.
                break; //Break loop. End of program.             
            }
            
        }
        else if(input==224) {
        
            input=_getch(); //input from user (UP, DOWN, ENTER).
            
            if( (input==72) && (selection==5) ) {
                selection--;
            }
            else if( (input==72) && (selection==4) ) {
                selection--;
            }
            else if( (input==72) && (selection==3) ) {
                selection--;
            }
            else if( (input==72) && (selection==2) ) {
                selection--;
            }
            else if( (input==72) && (selection==1) ) {
                selection--;
            }
            else if( (input==80) && (selection==0) ) {
                selection++;
            }
            else if( (input==80) && (selection==1) ) {
                selection++;
            }
            else if( (input==80) && (selection==2) ) {
                selection++;
            }
            else if( (input==80) && (selection==3) ) {
                selection++;
            }
            else if( (input==80) && (selection==4) ) {
                selection++;
            }
            
        } //End else if.
        
    } //End while.
        
    return; //End of Main Menu. End of program.
        
} //End of Main Menu.


/* U S E R ' S    I N P U T    ( S T U D E N T ' S    E L E M E N T S ) */
void UsersInput(ptrElements *startPtr)
{
    fflush(stdin); //Clear bad data from buffer.
    
    system("cls"); //Clear screen.
    
    printf("Enter student's data\n\n");
    
    //After student's element, user will decide to save or not the new student.
    int selection=0; //Selection (YES or NO). User will decide if student will be saved.
    int input=0;     //User's input (UP, DOWN, ENTER). (YES or NO).
    
    //Student's elements. Initialized arrays.
    char tableAM[ARRAYLENGTH_AM]={'\0'};     //Student's registration number.
    char tableName[ARRAYLENGTH]={'\0'};      //Student's name.
    char tableSurname[ARRAYLENGTH]={'\0'};   //Student's surname.
    char tableYear[ARRAYLENGTH_YEAR]={'\0'}; //Student's registration year.
    
    //These variables will be needed for easier and faster check. After these acions, these variables will be converted to strings.
    int AM;   //Student's registration number. (Will be calculated as integer and then will be converted to string).
    int Year; //Student's registration year. (Integer -> faster and easier check).
    
    int check; //Integer for checks. (0 -> true)
    
    int i;     //Simple loop counter.
    
    
    printf("First Name          : ");
    
    //Student's name.
    while(true) {
        scanf("%s", tableName); //Users input (student's name).
        
        fflush(stdin);          //Clear bad data from buffer.
        
        //If user types 0 will return to main menu.
        if( (tableName[0]=='0') && (tableName[1]=='\0') ) {
            return; //Return to main menu.
        } //End if.
        
        check=CheckUsersInputName(tableName); //Check for user's mistakes.
        
        if(check==0) {
            break; //Correct - break and continue to next input.
        }
        else {
            //Initialization if array.
            for(i=0 ; i<ARRAYLENGTH ; i++) {
                tableName[i]='\0';
            } //End for.

            system("cls"); //clear screen.
            
            printf("Enter student's data\n\n");
            printf("First Name          : ");
        } //End else.
        
    } //Input for name.
    
    //Student's surname.
    while(true) {
        printf("Last Name          : ");
        scanf("%s", tableSurname); //Users input (student's surname).
        
        fflush(stdin);             //Clear bad data from buffer.
        
        //If user type 0 will return to main menu.
        if( (tableSurname[0]=='0') && (tableSurname[1]=='\0') ) {
            return; //Return to main menu.
        } //End if.
        
        check=CheckUsersInputName(tableSurname); //Check for user's mistakes.
        
        if(check==0) {
            break; //Correct - break and continue to next input.
        }
        else {
            //Initialization if array.
            for(i=0 ; i<ARRAYLENGTH ; i++) {
                tableSurname[i]='\0';
            } //End for.
            
            system("cls"); //clear screen.
            
            printf("Enter student's data\n\n");
            printf("First Name          : %s\n", tableName);
        } //End else.
        
    } //Input for surname.
    
    //Student's ragistration year.
    while(true) {
        printf("Registration year : ");
        scanf("%d", &Year); //Users input (student's registration year).
        
        fflush(stdin);      //Clear bad data from buffer.
        
        if(Year==0) { 
            return; //Return to main menu.
        } //End if.
        
        check=CheckUsersInputYear(Year); //Check for user's mistakes.
        
        if(check==0) {
            itoa(Year, tableYear, 10);        //Convert integer to string (registration year).
            tableYear[ARRAYLENGTH_YEAR]='\0'; //The last pos of array \0.
            break;                            //Break and continue.
        }
        else {
            system("cls"); //Clear screen.
            
            printf("Enter student's data\n\n");
            printf("First Name : %s\n", tableName);
            printf("Last Name  : %s\n", tableSurname);
        } //End else.
    
    } //Input for registration year.
    
    //Make the first character to capital.
    tableName[0]=toupper(tableName[0]);
    tableSurname[0]=toupper(tableSurname[0]);
    
    AM=AMGenerator(*startPtr, tableName, tableSurname, tableYear, Year);  //A.M. Generator will return the student's registration number (integer).
    
    itoa(AM, tableAM, 10); //Convert integer to string (registration number).
    
    tableAM[ARRAYLENGTH_AM]='\0'; //Last pos of array \0.
    
    /* Check if user want to save student in file */
    while(true) {
            
        system("cls"); //clear screen.
            
        printf("AM: %s\nName: %s\nSurname: %s\nRegistration year: %s\n\n", tableAM, tableName, tableSurname, tableYear);
        printf("Save student?\n");
        
        if(selection==0) {
            printf("> Yes\n  No\n\n");
        } 
        else if(selection==1) {
            printf("  Yes\n> No\n\n");
        }  
        
        input = _getch(); //input from user (UP, DOWN, ENTER).
            
        if(input==13) {
        
            if(selection==0) {
                InsertElements(startPtr, tableAM, tableName, tableSurname, tableYear); //Insert student's elements to list.
                break; //Break loop and continue program.
            }
            else if(selection==1) {
                printf("Save cancelled!\n\n");
                system("PAUSE");
                break; //Break loop and continue program.
            }
        }
        else if(input==224) {
                
            input=_getch(); //input from user (UP, DOWN, ENTER).
                
            if( (input==72) && (selection==1) ) {
                selection--;
            }
            else if( (input==80) && (selection==0) ) {
                selection++;
            }
                
        } //End else if.
            
    } //End of WHILE.
        
    return; //End of function.
    
} //End of Users Input.


/* C H E C K    U S E R ' S    I N P U T    ( N A M E    &    S U R N A M E ) */
int CheckUsersInputName(char table[ARRAYLENGTH])
{
    int i=0;      //Simple loop counter.
    int errors=0; //Errors
    
    while(table[i]!='\0') {
        
        //If is digit.
        if( isdigit(table[i]) ) { 
            errors++;
            break; //Break loop and continue.
        }
        //If is punctuation.
        if( ispunct(table[i]) ) {
            errors++;
            break; //Break loop and continue.
        }
        //If is white space.
        if(isspace(table[i]) ) {
            errors++;
            break; //Break loop and continue.
        }
        
        i++;
        
    } //End of WHILE.
    
    if(errors==0) {
        return 0; //Correct input.
    }
    else {
        printf("ERROR!\n");
        return 1; //Incorrect input.
    } //End else.
           
} //End of Check for name and surname.


/* C H E C K    U S E R ' S    I N P U T    ( R E G I S T R A T I O N    Y E A R ) */
int CheckUsersInputYear(int Year)
{
    if( (Year>=YEAR_MIN) && (Year<=YEAR_MAX) ) {    //Check for year. (Year has limits - see defines).
        return 0; //Correct year. 
    }
    else {
        return 1; //Incorrect year.
    } //End else.
    
} //End of Check for registrtion year.


/* R E G I S T R A T I O N    N U M B E R    G E N E R A T O R */
int AMGenerator(ptrElements currentPtr, char tableName[ARRAYLENGTH], char tableSurname[ARRAYLENGTH], char tableYear[ARRAYLENGTH_YEAR], int Year)
{
    int am;        //Integer registration number. This value will be returned as student's registration number.
    
    am=Year*100;   //Registration number is a six-digit number.
    
    int tempAM;    //Temporary registration number.
    
    int test1;     //Check years.
    int test2;     //Check surnames.
    int test3;     //Check names.
    
    int counter=0; //Counter. If conditions are not satisfied then the registration number will be occuer by this treaty: (Year X 100) + Counter
        
    if(currentPtr==NULL) {
        return am; //No students in list. So students will take registration number (year00).
    } //End if.
    
    while(currentPtr!=NULL) {

        //Check if year is the same.
        test1=strcmp(tableYear, currentPtr->year);
        //If year is the same.
        if(test1==0) {
                     
            //Check about surname.
            test2=strcmp(tableSurname, currentPtr->surname);
            //If name (from input) is 'smaller'.
            if(test2<0) {
                j: /* point */
                tempAM=atoi(currentPtr->AM);      //Convert string am to integer.
                
                am=tempAM;
                
                tempAM=tempAM+1;
                
                itoa(tempAM, currentPtr->AM, 10); //Convert integer am to string.
                
                currentPtr=currentPtr->ptrNext;   //Next node.
                
                if(currentPtr==NULL) {
                    return am; //Return am - end function.
                } //End if.
                
                while(currentPtr!=NULL) {
                    //Check for year.
                    test1=strcmp(tableYear, currentPtr->year);
                    //If year is the same.
                    if(test1==0) {
                       
                        tempAM=atoi(currentPtr->AM);      //Convert string am to integer.
                        tempAM=tempAM+1;
                        
                        itoa(tempAM, currentPtr->AM, 10); //Convert integer am to string.
                        
                        currentPtr=currentPtr->ptrNext;   //Next node.
                    } //End if.
                    else {
                        break; //Break loop.
                    } //End else.
                    
                } //End while.
                
                return am;
                    
            } //End if (surname < node's surname).
            else if(test2==0) {
                
                //Check about name.
                test3=strcmp(tableName, currentPtr->name);
                //If name is 'smaller'.
                if(test3<0) {
                    goto j;
                } //End if (name < node's name).
                else {
                    
                    tempAM=atoi(currentPtr->AM);    //Convert string am to integer.
                    
                    am=tempAM+1;
                
                    currentPtr=currentPtr->ptrNext; //Next node.
                
                    if(currentPtr==NULL) {
                        return am;
                    } //End if.
                
                    while(currentPtr!=NULL) {
                        //Check for year.
                        test1=strcmp(tableYear, currentPtr->year);
                        //If year is the same.
                        if(test1==0) {
                       
                            tempAM=atoi(currentPtr->AM);      //Convert string am to integer.
                            tempAM=tempAM+1;
                        
                            itoa(tempAM, currentPtr->AM, 10); //Convert integer am to string.
                        
                            currentPtr=currentPtr->ptrNext;   //Next node.
                        } //End if.
                        else {
                            break; //break loop.
                        } //End else.
                    
                    } //End while.
                
                    return am; //Return am - end function.
                    
                } //End else if (names are the same).
                
            } //End if (surnames are the same.
            else {
                counter++;                      //Increase Counter.
                currentPtr=currentPtr->ptrNext; //Next node.
            } //End else.
            
        } //End if (year is the same).
        else {
            currentPtr=currentPtr->ptrNext; //Go to next node.
        } //End else.
        
    } //End while.
     
    return am+counter; //Return am - end function.
    
} //End am generator.


/* I N S E R T    S T U D E N T ' S    E L E M E N T S    T O    L I S T */
void InsertElements(ptrElements *sPtr, char tableAM[ARRAYLENGTH_AM], char tableName[ARRAYLENGTH], char tableSurname[ARRAYLENGTH], char tableYear[ARRAYLENGTH_YEAR])
{   
    ptrElements newPtr;      //Pointer to new node.
    ptrElements previousPtr; //Pointer to previous node in list.
    ptrElements currentPtr;  //Pointer to current node in list.
    
    newPtr=malloc(sizeof(Elements)); //Create a node.
    
    int AM_1=atoi(tableAM);  //Convert string to integer.  (table's AM).
    int AM_2;                //Convert string to integer. (struct's AM).
    
    if(newPtr != NULL) {
        
        strcpy(newPtr->AM, tableAM);           //Copy AM to struct's array.
        strcpy(newPtr->name, tableName);       //Copy name to struct's array.
        strcpy(newPtr->surname, tableSurname); //Copy surname to struct's array.
        strcpy(newPtr->year, tableYear);       //Copy registration year to struct's array.
        
        newPtr->ptrNext=NULL;  //Next node of inserted node is NULL. 
        previousPtr=NULL;      //Previous node initialized NULL.
        currentPtr=*sPtr;      //Current node is the inserted node.
        
        AM_2=atoi(currentPtr->AM); //Convert string to integer. (Registration number).
        
        //Find the position in list where student must be inserted. (Sorted by registration number).
        while( (currentPtr != NULL) && (AM_1 > AM_2) ) {
        
            previousPtr=currentPtr;          //Current node to previous node assignenment.
            currentPtr=currentPtr->ptrNext;  //Next node.
            //If node is not null.
            if(currentPtr!=NULL) {
                AM_2=atoi(currentPtr->AM);   //Convert string to integer (registration number).
            } //End if.
            else {
                break; //Break loop.
            } //End else if.
            
        } //End while.
        
        if(previousPtr==NULL) {
            newPtr->ptrNext=*sPtr;
            *sPtr=newPtr;
        } //End if.
        else {
            previousPtr->ptrNext=newPtr;
            newPtr->ptrNext=currentPtr;
        } //End else.
        
    } //End of IF.
    else {
        printf("Elements not inserted. No memory available.\n");
    } //End of ELSE.
    
    return; //Return - end function.
        
} //End of insert function.


/* C H E C K    I F    L I S T    I S    E M P T Y */
int ListIsEmpty(ptrElements sPtr)
{
    return sPtr==NULL; //Return 0 if it is true. ! 0 is not true.
} //End of check. (if list is empty).


/* S H O W    L I S T    O F    S T U D E N T S */
void PrintList(ptrElements currentPtr)
{
    system("cls"); //Clear screnn.
    
    //Check if list is empty.
    if(currentPtr==NULL) {
        printf("Students List is empty.\n\n");
    } //End if.
    else {
        printf("Students List: \n\n");
    
        while(currentPtr!=NULL) {
            printf("| AM: %s | First Name: %s | Last Name: %s | Registration year: %s | \n\n", currentPtr->AM, currentPtr->name, currentPtr->surname, currentPtr->year);
            currentPtr=currentPtr->ptrNext; //Assign to current ptr (node) the next ptr (next node).
        } //End of WHILE.
        
        printf("\n"); //New line.
        
    } //End of ELSE.
    
    system("PAUSE"); //pause.
    
    return; //return - end function.
    
} //End of printing list.


/* E D I T    S T U D E N T */
void EditStudent(ptrElements currentPtr)
{
    //Check if list is empty.
    if(ListIsEmpty(currentPtr)) {
        system("cls"); //clear screen.
        
        printf("List is empty!\n");
        printf("No students to edit.\n\n");
        system("PAUSE"); //Pause.
        return; //return - end of function.
    } //End if.
    
    int inputInt;                        //Am (integer). (User input - to search student via registration number).
    char AMInput[ARRAYLENGTH_AM]={'\0'}; //Am (string).
    
    int test; //This variable need for check.
    int check;//This variable need for check. (in function).
    
    int Year; //Variable to check year (user's input).
    
    //After student's element, user will decide to save or not the edited student.
    int selection=0; //Selection (YES or NO). User will decide if student will be saved.
    int input=0;     //User's input (UP, DOWN, ENTER). (YES or NO).
    
    //Tables for new input.
    char tableName[ARRAYLENGTH]={'\0'};      //Array for (new) name.
    char tableSurname[ARRAYLENGTH]={'\0'};   //Array for (new) surname.
    char tableYear[ARRAYLENGTH_YEAR]={'\0'}; //Array for (new) year.
    
    int i; //simple loop counter.
    
    while(true) {
        system("cls"); //Clear screen.
        
        printf("Student to edit\nRegistration number: ");
        scanf("%s", &AMInput);  //User's input (am to search student).
        
        fflush(stdin);          //Clear bad data from buffer.
        
        inputInt=atoi(AMInput); //Convert string am to integer.
        
        //AMs' limit. (check for correct input).
        if( (inputInt>=AM_MIN) && (inputInt<=AM_MAX) ) {
            break; //Break loop.
        } //End if.
        else if(inputInt==0) {
            return; //Return to main menu.
        } //End else if.
        else {
            printf("\nPlease type a six-digit number.\nPress 0 to return to main menu.\n\n");
            
            system("PAUSE"); //Pause.
        } //End else.
        
    } //End while.
    
    fflush(stdin);                //Clear bad data from buffer.
    
    itoa(inputInt, AMInput, 10);  //Convert integer am to string.
    
    AMInput[ARRAYLENGTH_AM]='\0'; //Last pos of array.
    
    while(currentPtr!=NULL) {
        //Check for the right am.
        test=strncmp(AMInput, currentPtr->AM, 7);
        //If am is corrent.
        if(test==0) {
            system("cls"); //Clear screen.
            
            printf("A.M.: %s\nFirst Name: %s\nLast Name: %s\nRegistration year: %s\n\n", currentPtr->AM, currentPtr->name, currentPtr->surname, currentPtr->year);
            
            printf(" Enter student's data\n\n");
            
            printf("Name              : ");
    
            while(true) {
                scanf("%s", tableName); //User's input (new name).
                
                fflush(stdin); //Clear bad data from buffer.
                
                //If user type 0 will return to main menu.
                if( (tableName[0]=='0') && (tableName[1]=='\0') ) {
                    return; //Return to main menu.
                } //End if.
                
                check=CheckUsersInputName(tableName); //Check for correct input (check for name).
        
                if(check==0) {
                    break; //Break loop.
                } //End if.
                else {
                    //Initialization of array.
                    for(i=0 ; i<ARRAYLENGTH ; i++) {
                        tableName[i]='\0';
                    } //End for.
                    
                    system("cls"); //Clear screen.
                    printf("A.M.: %s\nFirst Name: %s\nLast Name: %s\nRegistration year: %s\n\n", currentPtr->AM, currentPtr->name, currentPtr->surname, currentPtr->year);            
                    printf(" Enter student's data\n\n");
                    printf("Name              : ");
                } //End else.    
        
            } //Input for name.
    
            while(true) {
                printf("Surname           : ");
                scanf("%s", tableSurname); //User's input. (new surname).
                
                fflush(stdin); //Clear bad data from buffer.
                
                //If user type 0 will return to main menu.
                if( (tableSurname[0]=='0') && (tableSurname[1]=='\0') ) {
                    return; //Return to main menu.
                } //End if.
                
                check=CheckUsersInputName(tableSurname); //Check for correct input (check for surname).
        
                if(check==0) {
                    break; //Break loop.
                }
                else {
                    //Initialization of array.
                    for(i=0 ; i<ARRAYLENGTH ; i++) {
                        tableSurname[i]='\0';
                    } //End for.
                    
                    system("cls"); //Clear screen.
                    printf("A.M.: %s\nFirst Name: %s\nLast Name: %s\nRegistration year: %s\n\n", currentPtr->AM, currentPtr->name, currentPtr->surname, currentPtr->year);
                    printf(" Enter student's data\n\n");
                    printf("Name              : %s\n", tableName);
                } //End else.
        
            } //Input for surname.
    
            while(true) {
                printf("Registration year : ");
                scanf("%d", &Year); //User input (new year).
                
                fflush(stdin); //Clear bad data from buffer.
                
                //If user type 0 will return to main menu.
                if(Year==0) {
                    return; //Return to main menu.
                } //End if.
                
                check=CheckUsersInputYear(Year); //Check for correct input (check for year).
        
                if(check==0) {
                    itoa(Year, tableYear, 10);        //Convert integer year to string.
                    tableYear[ARRAYLENGTH_YEAR]='\0'; //Last pos in array.
                    break;                            //Break loop.
                } //End if.
                else {
                    system("cls"); //Clear screen.
                    printf("AM: %s\nFirst Name: %s\nLast Name: %s\nRegistration year: %s\n\n", currentPtr->AM, currentPtr->name, currentPtr->surname, currentPtr->year);
                    printf(" Enter student's data\n\n");
                    printf("Name              : %s\n", tableName);
                    printf("Surname           : %s\n", tableSurname);
                } //End else.
    
            } //End input for registration year.
    
            //Make the first character to capital.
            tableName[0]=toupper(tableName[0]);
            tableSurname[0]=toupper(tableSurname[0]);
            
            /* Check if user want to save student in file */
            while(true) {
                        
                fflush(stdin); //Clear bad data from buffer.
                
                system("cls"); //Clear screen.
                
                printf("Current    --------->    New\n");
                printf("AM: %s \t\t AM: %s\n", currentPtr->AM, currentPtr->AM);
                printf("First Name: %s \t\t First Name: %s\n", currentPtr->name, tableName);
                printf("Last Name: %s \t Last Name: %s\n", currentPtr->surname, tableSurname);
                printf("Reg. Year: %s \t Reg. Year: %s\n", currentPtr->year, tableYear);
            
                printf("\n\nSave changes?\n");
        
                if(selection==0) {
                    printf("> Yes\n  No\n\n");
                }
                else if(selection==1) {
                    printf("  Yes\n> No\n\n");
                }  
        
                input = _getch(); //input from user (UP, DOWN, ENTER).
            
                if(input==13) {
        
                    if(selection==0) {
                        
                        strcpy(currentPtr->name, tableName);       //Copy new name to old name (old name will be 'deleted').
                        strcpy(currentPtr->surname, tableSurname); //Copy new surname to old surname (old surname will be 'deleted').
                        strcpy(currentPtr->year, tableYear);       //Copy new year to old year (old year will be 'deleted').
                        
                        printf("Changes saved!\n\n");
                        system("PAUSE");
                        return; //Return to main menu.
                    }
                    else if(selection==1) {
                        printf("Editing cancelled!\n\n");
                        system("PAUSE");
                        break; //Break loop.
                    }
                }
                else if(input==224) {
                
                    input=_getch();
                
                    if( (input==72) && (selection==1) ) {
                        selection--;
                    }
                    else if( (input==80) && (selection==0) ) {
                        selection++;
                    }
                
                } //End of else if.
            
            } //End of WHILE.
                
        } //End of if.
        
        currentPtr=currentPtr->ptrNext; //Next node.
        
    } //End WHILE.
    
    return; //Return to main menu.
    
} //End edit student.


/* D E L E T E    S T U D E N T */
int DeleteStudent(ptrElements *sPtr)
{
    ptrElements currentPtr;
    ptrElements tempPtr;
    ptrElements previousPtr;
    
    int test; //Variable 'test': show if the node must be deleted.
    
    int input;                    //Am integer.
    char AMInput[ARRAYLENGTH_AM]; //Am string.
    
    if(ListIsEmpty(*sPtr)) {
        system("cls"); //Clear screen.
        
        printf("List is empty!\n");
        printf("No students for deletion.\n\n");
        system("PAUSE");
        return 1; //No student deleted.
    }
    
    while(true) {
        system("cls"); //Clear screen.
        
        printf("Student for deletion\nRegistration number: ");
        scanf("%s", AMInput); //User's input.
        
        fflush(stdin); //Clear bad data from buffer.
        
        if( (AMInput[0]=='0') && (AMInput[1]=='\0') ) {
            return 1; //Return to main menu. No student deleted.
        } //End if.   
        
        input=atoi(AMInput);  //Convert string to integer.
        
        if( (input>=AM_MIN) && (input<=AM_MAX) ) {
            break;  //break loop.
        } //End if.
        else {
            printf("\nPlease type a six-digit number.\n0 to return to main menu.\n\n");
            
            system("PAUSE"); 
        } //End else.
    } //End while. 
    
    fflush(stdin); //Clear bad data from buffer.
    
    currentPtr=*sPtr;
    
    test=strncmp(AMInput, currentPtr->AM, 7);
    
    if(test==0) {
        tempPtr=*sPtr;
        *sPtr=(*sPtr)->ptrNext;
        free(tempPtr);
        
        printf("\nStudent (%d) deleted\n\n", input);
        system("PAUSE");
        
        return input; //Return am. (to change the other AMs).
        
    } //End of IF.
    else {
        previousPtr=*sPtr;
        currentPtr=(*sPtr)->ptrNext;
        
        if(currentPtr==NULL) {
            printf("\n\nStudent's registration number does not exist!\n\n");
            
            system("PAUSE");
            
            return 1; //Return to main menu. No student deleted.
        }

        test=strncmp(AMInput, (currentPtr->AM), 7);
        
        while( (currentPtr!=NULL) && (test!=0) ) {
            
            previousPtr=currentPtr;
            currentPtr=currentPtr->ptrNext;
            
            if(currentPtr==NULL) {
                printf("\n\nStudent's registration number does not exist!\n\n");
                
                system("PAUSE");
                
                return 1; //Return to main menu. No student deleted.
            } //End IF.
                                 
            
            test=strncmp(AMInput, (currentPtr->AM), 7);
            
        } //End of WHILE.
        
        if(currentPtr!=NULL) {
            tempPtr=currentPtr;
            previousPtr->ptrNext=currentPtr->ptrNext;
            free(tempPtr);
            
            printf("\nStudent (%d) deleted!\n\n", input);
            system("PAUSE");
            
            return input; //Return am. (to change the other AMs).
        }
    } //End of ELSE.
    
    printf("\n\nStudent's registration number does not exist!\n\n");
    system("PAUSE");
    return 1; //Return to main menu. No student deleted.
    
} //End of delete student.


/* R E D U S E    R E G I S T R A T I O N    N U M B E R */
void ReduceAM(ptrElements currentPtr, int am)
{
    int year; //This variable will be needed to check for students who were registrated at the same year. 
    char stringYear[ARRAYLENGTH_YEAR]={'\0'}; //Convert integer year to string.
     
    int test1;  //Variable need for check. (year).
    int test2;  //Variable need for check. (year).
    
    int testAM; //Temporary AM. (need for check).
    int tempAM; //Temporaty AM. (Need for original AM's change).
    
    if(currentPtr==NULL) {
        return; //return - end of function.
    } //End if.
    
    year=am/100;
    
    itoa(year, stringYear, 10); //Convert integer year to string.
    
    while(currentPtr!=NULL) {
        
        test1=strcmp(stringYear, currentPtr->year);
        
        if(test1==0) {
                     
            testAM=atoi(currentPtr->AM); //Convert string AM to integer.
            
            if( (am+1)==testAM ) {
                
                while(currentPtr!=NULL) {
                    
                    test2=strcmp(stringYear, currentPtr->year); //Check for year.
                    
                    //If year is the same.
                    if(test2==0) {
                        
                        tempAM=atoi(currentPtr->AM);      //Convert string AM to integer.
                        
                        tempAM=tempAM-1;
                        
                        itoa(tempAM, currentPtr->AM, 10); //Convert integer AM to string.
                        
                    } //End if.
                    
                    if(currentPtr->ptrNext==NULL) {
                        return; //Return - end of function.
                    } //End if.
                    
                    currentPtr=currentPtr->ptrNext; //Next node.
                    
                } //End while.
                    
            } //End if.
            
        } //End if.
        
        currentPtr=currentPtr->ptrNext; //Next node.
        
    } //End while.
    
} //End of raise am.


/* S A V E    L I S T    T O    F I L E */
void SaveToFile(ptrElements currentPtr)
{ 
    FILE *stream; //Pointer to file.
    
    stream=fopen("database.bin", "w"); //Open file to write.
    
    if(stream==NULL) {
        system("cls"); //clear screen.
        printf("\nError: Students' list did not saved!\n\n");
        fclose(stream); //Close file.
        system("PAUSE"); 
        return; //return - end of function.
    } //End if.
    
    //Write to file each student's elements.
    while(currentPtr!=NULL) {
        
        fwrite(currentPtr, sizeof(struct elements), 1, stream); //Write srtuct to file.
    
        currentPtr=currentPtr->ptrNext; //Next node.
        
    } //End while.
    
    fclose(stream); //Close file.
    
    return; //return - end of function.
    
} //End of saving to file.


/* L O A D    F I L E ' S    E L E M E N T S    T O    L I S T */
void LoadFile(ptrElements *startPtr)
{
    FILE *stream; //Pointer to file.
    
    ptrElements student;
    
    char tableAM[ARRAYLENGTH_AM]={'\0'};     //Array where stundent's registration number will be inserted.
    char tableName[ARRAYLENGTH]={'\0'};      //Array where stundent's name will be inserted.
    char tableSurname[ARRAYLENGTH]={'\0'};   //Array where stundent's surname will be inserted.
    char tableYear[ARRAYLENGTH_YEAR]={'\0'}; //Array where stundent's registration year will be inserted.
    
    int i;          //Simple loop counter.
    int SizeOfFile; //Size of file (bytes).
    int j;          //Simple loop counter. (Will be needed to initialize tables.
    
    //Open file (READ ONLY).
    stream=fopen("database.bin", "r"); 
    
    if(stream==NULL) {
        fclose(stream); //close file.
        return; //return - end of function.
    } //End if.
    
    fseek(stream, 0, SEEK_END);                       //Go to end of file.
    SizeOfFile=ftell(stream)/sizeof(struct elements); //Find how many students are in file (AM, name, surname, year).
    fseek(stream, 0, SEEK_SET);                       //Go to the begging of file.
    
    for(i=0 ; i<SizeOfFile ; i++) {
        
        student=(ptrElements)malloc(sizeof(struct elements));
        
        assert(student);

        fread(student, sizeof(struct elements), 1, stream);
        
        strcpy(tableAM,      student->AM);      //Copy AM from file to table. After this will be inserted to list.
        strcpy(tableName,    student->name);    //Copy name from file to table. After this will be inserted to list.
        strcpy(tableSurname, student->surname); //Copy surname from file to table. After this will be inserted to list.
        strcpy(tableYear,    student->year);    //Copy year from file to table. After this will be inserted to list.
        
        InsertElements(startPtr, tableAM, tableName, tableSurname, tableYear); //Insert student's elements to list.
        
        //Arrays' initialization.
        for(j=0 ; j<ARRAYLENGTH ; j++) {
            tableName[j]='\0';
            tableSurname[j]='\0';
        } //End for.
        
        for(j=0 ; j<ARRAYLENGTH_AM ; j++) {
            tableAM[j]='\0';
        } //End for.
        
        for(j=0 ; j<ARRAYLENGTH_YEAR ; j++) {
            tableYear[j]='\0';
        } //End for.
        
    } //End for.
    
    fclose(stream); //Close file.
    
    return; //return - end of function.
    
} //End of loading file to program.

/**********************************************************************************************************************************************/
