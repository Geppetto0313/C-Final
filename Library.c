#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define KRED "\x1B[31m"
#define KCYN "\x1B[36m"
#define UYEL "\e[4;33m"
#define reset "\e[0m"

//STRUCT DEFINING ATTRIBUTES
typedef struct Book
{
    char bookName[100];
    char author[100];
    char publisher[100];
    double replacementCost;
    char subjectOfMaterial[100];
    int indexNumber;
    char currentlyOnLoanTo[100];
    char dueDate[100];
    struct Book *next;

} Book;
//SEEN ALOT OF PEOPLE CODE THESE RIGHT UNDER THE STRUCT DECLARATION
// Book *start = NULL;
// Book *move = NULL;
// Book *last = NULL;

//DECLEAR PROTOTYPES
Book *NewEntry(Book *start, Book *last, Book *move);
Book *LoadData(Book *start, Book *last, Book *move);
void Save(Book *start);
void BrowseEntries(Book *start, Book *last, Book *move);
Book *ReadNextFromFile(Book *start, Book *last, Book *move, FILE *fptr);
Book *Append(Book *start, Book *last, Book *move);
Book *NewBook(Book *start, Book *last, Book *move);
void MainMenu();
void Menu();
void Delete(Book **start, Book *last, Book *move);
void Sort(Book *start);
void SearchBookName(Book *start, Book *move);
void SearchAuthorName(Book *start, Book *move);
void Modify(Book *start, Book *move);
void ModifyMenu(Book *temp);
void ModSelection(Book *start, Book *move, Book *temp);
void ClearOnExit(Book **start);
void TEST();

int main()
{
    char ch;
    int userInput = -1;
    int newInput = -1;
    Book *start = NULL;
    Book *move = NULL;
    Book *last = NULL;

    //CALL MAIN MENU
    MainMenu();

    //WHILE LOOP - USER INPUT DATA OR LOAD
    while (newInput != 0)
    {
        printf("Select An Option: ");
        scanf("%d", &newInput);
        while ((ch = getchar()) != '\n' && ch != EOF)
            ;
        switch (newInput)
        {
        case 0:
            ClearOnExit(&start);
            printf(KRED "\nLogging out...\n" reset);
            exit(3);

        case 1:
            start = NewEntry(start, last, move);
            newInput = 0;
            break;
        case 2:
            start = LoadData(start, last, move);
            newInput = 0;
            break;
        default:
            printf(KRED "\n*Invalid Selection\n" reset);
            MainMenu();
        }
    }
    //CALLING MENU
    Menu();

    //WHILE LOOP FOR MENU
    while (userInput != 0)
    {
        printf("Select An Option: ");
        scanf("%d", &userInput);
        while ((ch = getchar()) != '\n' && ch != EOF)
            ;

        switch (userInput)
        {
        case 0:
            ClearOnExit(&start);
            printf(KRED "\nLogging out...\n" reset);
            break;
        case 1:
            start = Append(start, last, move);
            Menu();
            break;
        case 2:
            BrowseEntries(start, last, move);
            Menu();
            break;
        case 3:
            Save(start);
            Menu();
            break;
        case 4:
            Delete(&start, last, move);
            Menu();
            break;
        case 5:
            Sort(start);
            Menu();
            break;
        case 6:
            SearchBookName(start, move);
            Menu();
            break;
        case 7:
            SearchAuthorName(start, move);
            Menu();
            break;
        case 8:
            Modify(start, move);
            Menu();
            break;
        case 66:
            TEST(start, last, move);
            newInput = 0;
            break;
        default:
            printf(KRED "\n*Invalid Selection\n" reset);
            Menu();
        }
    }
    return 0;
}

//  MAIN MENU FUNCTION - PRINTS OUT MENU
void MainMenu()
{
    printf("\n");
    printf(UYEL "\tLibrary\n" reset);
    printf("--------------------------\n");
    printf(KCYN "1" reset ". Add Entry\n");
    printf(KCYN "2" reset ". Load Data\n");
    printf(KRED "0" reset ". Quit\n");
    printf("--------------------------\n");
}

//  MENU FUNCTION - PRINTS OUT MENU
void Menu()
{
    printf("\n");
    printf(UYEL "\tMENU\n" reset);
    printf("--------------------------\n");
    printf(KCYN "1" reset ". Add Entry\n");
    printf(KCYN "2" reset ". Browse Entries\n");
    printf(KCYN "3" reset ". Save\n");
    printf(KCYN "4" reset ". Delete\n");
    printf(KCYN "5" reset ". Sort\n");
    printf(KCYN "6" reset ". Search By Book Name\n");
    printf(KCYN "7" reset ". Search By Author Name\n");
    printf(KCYN "8" reset ". Modify Entry\n");
    printf(KRED "0" reset ". Quit\n");
    printf("--------------------------\n");
}

//  MEW ENTRY FUNCTION
Book *NewEntry(Book *start, Book *last, Book *move)
{

    Book *new = NULL;

    int keepGoing = 'y';
    int ch;
    char userInput[255];
    double numDouble;
    int numInt;

    while (keepGoing == 'y')
    {

        if (start == NULL)
        {

            //allocate a block of memory for Book
            new = (Book *)malloc(sizeof(Book));

            if (new == NULL)
            {
                puts(KRED "\nError: Memory allocation\n" reset);
                exit(1);
            }

            //assign new block to start
            start = new;

            //get information
            printf("\n");

            printf("Enter Book Title: ");
            fgets(userInput, 255, stdin);
            strcpy(start->bookName, userInput);

            printf("Enter Author Name: ");
            fgets(userInput, 255, stdin);
            strcpy(start->author, userInput);

            printf("Enter Publisher: ");
            fgets(userInput, 255, stdin);
            strcpy(start->publisher, userInput);

            printf("Enter Replacement Cost: ");
            scanf("%lf", &numDouble);
            start->replacementCost = numDouble;
            while ((ch = getchar()) != '\n' && ch != EOF)
                ;

            printf("Enter Subject: ");
            fgets(userInput, 255, stdin);
            strcpy(start->subjectOfMaterial, userInput);

            printf("Enter Index Number: ");
            scanf("%d", &numInt);
            start->indexNumber = numInt;
            while ((ch = getchar()) != '\n' && ch != EOF)
                ;

            printf("Currently Loaned To: ");
            fgets(userInput, 255, stdin);
            strcpy(start->currentlyOnLoanTo, userInput);

            printf("Enter Due Date[YYYY-MM-DD]: ");
            fgets(userInput, 255, stdin);
            strcpy(start->dueDate, userInput);

            printf("\n");

            //pointer to next is null to indicate nothing follows
            start->next = NULL;
            //change last pointer to point to the one just created
            last = start;
            move = last;
        }
        else
        {

            new = (Book *)malloc(sizeof(Book));

            if (new == NULL)
            {
                puts(KRED "\nError: Memory allocation\n" reset);
                exit(1);
            }

            //last node linked to new
            last->next = new;

            //get information
            printf("\n");

            printf("Enter Book Title: ");
            fgets(userInput, 255, stdin);
            strcpy(new->bookName, userInput);

            printf("Enter Author Name: ");
            fgets(userInput, 255, stdin);
            strcpy(new->author, userInput);

            printf("Enter Publisher Name: ");
            fgets(userInput, 255, stdin);
            strcpy(new->publisher, userInput);

            printf("Enter Replacement Cost: ");
            scanf("%lf", &numDouble);
            new->replacementCost = numDouble;
            while ((ch = getchar()) != '\n' && ch != EOF)
                ;

            printf("Enter Subject: ");
            fgets(userInput, 255, stdin);
            strcpy(new->subjectOfMaterial, userInput);

            printf("Enter Index Number: ");
            scanf("%d", &numInt);
            new->indexNumber = numInt;
            while ((ch = getchar()) != '\n' && ch != EOF)
                ;

            printf("Currently Loaned To: ");
            fgets(userInput, 255, stdin);
            strcpy(new->currentlyOnLoanTo, userInput);

            printf("Enter Due Date[YYYY-MM-DD]: ");
            fgets(userInput, 255, stdin);
            strcpy(new->dueDate, userInput);

            printf("\n");
            //set next pointer to null
            //set the last pointer to newest
            new->next = NULL;
            last = new;
            move = last;
        }

        puts("Create a new node? [y/n]?");
        scanf("%c", &keepGoing);
        while ((ch = getchar()) != '\n' && ch != EOF)
            ;
    }
    //returns memory address to the last block
    return start;
}

//  READ FROM FILE FUNCTION
Book *ReadNextFromFile(Book *start, Book *last, Book *move, FILE *fptr)
{
    Book *new = NULL;
    //SETTING AN UNSIGNED LONG LONG VALUE FOR THE FILE TO BE READ BACK ON
    size_t returnValue;

    //START EQUAL NULL START AT START
    if (start == NULL)
    {
        start = new;
        start = (Book *)malloc(sizeof(Book));
        returnValue = fread(start, sizeof(Book), 1, fptr);

        start->next = NULL;
        last = start;
    }
    else
    {
        //ELSE MOVE TO START AND START
        move = start;
        new = (Book *)malloc(sizeof(Book));
        while (move->next != NULL)
        {
            move = move->next;
        }
        returnValue = fread(new, sizeof(Book), 1, fptr);
        move->next = new;

        new->next = NULL;
        last = new;
        move = last;
    }

    return start;
}

//  LOAD DATA FUNCTION
Book *LoadData(Book *start, Book *last, Book *move)
{
    //OPEN FILE
    FILE *fptr;
    fptr = fopen("Books.bin", "rb");
    //IF NOTHING
    if (fptr != NULL)
    {
        //FIND THE END OF THE FILE, GET SIZE AND GO TO THE START
        start = NULL;
        fseek(fptr, 0, SEEK_END);
        long fileSize = ftell(fptr);
        rewind(fptr);

        //COUNT ENTRIES
        int numEntries = (int)(fileSize / (sizeof(Book)));
        printf("\nNumber of Entries: " KCYN "%d" reset "\n", numEntries);

        //LOOK THROUGH FILE BASED ON ENTRIES
        for (int i = 0; i < numEntries; ++i)
        {
            fseek(fptr, (sizeof(Book) * i), SEEK_SET);
            start = ReadNextFromFile(start, last, move, fptr);
        }
    }
    else
    {
        printf(KRED "\nError: Reading File\n" reset);
        exit(2);
    }
    //CLOSE FILE
    fclose(fptr);
    return start;
}

//  BROWSE FUNCTION
void BrowseEntries(Book *start, Book *last, Book *move)
{
    move = start;
    //START IS NULL, LIST IS EMPTY
    if (start == NULL)
    {
        printf(KRED "\n*List is empty.\n" reset);
    }
    else
    {
        while (move->next != NULL)
        {
            printf("\n");
            printf(UYEL "Book\n" reset);
            printf("");
            printf(KCYN "Book Title: " reset "%s", move->bookName);
            printf(KCYN "Author: " reset "%s", move->author);
            printf(KCYN "Publisher: " reset " %s", move->publisher);
            printf(KCYN "Replacement Cost: " reset "%.2lf\n", move->replacementCost);
            printf(KCYN "Subject: " reset "%s", move->subjectOfMaterial);
            printf(KCYN "Index Number: " reset "%d\n", move->indexNumber);
            printf(KCYN "Currently Loaned To: " reset "%s", move->currentlyOnLoanTo);
            printf(KCYN "Due Date: " reset "%s", move->dueDate);
            printf("--------------------------\n\n");
            //advance to next node
            move = move->next;
        }

        //print out the last node
        printf("\n");
        printf(UYEL "Book\n" reset);
        printf("");
        printf(KCYN "Book Title: " reset "%s", move->bookName);
        printf(KCYN "Author: " reset "%s", move->author);
        printf(KCYN "Publisher: " reset "%s", move->publisher);
        printf(KCYN "Replacement Cost: " reset "%.2lf\n", move->replacementCost);
        printf(KCYN "Subject: " reset "%s", move->subjectOfMaterial);
        printf(KCYN "Index Number: " reset "%d\n", move->indexNumber);
        printf(KCYN "Currently Loaned To: " reset "%s", move->currentlyOnLoanTo);
        printf(KCYN "Due Date: " reset "%s", move->dueDate);
        printf("--------------------------\n\n");

        last = move;
    }
}

//  SAVE FUNCTION
void Save(Book *start)
{
    //   POINT TO FILE AND OPEN FILE IN BINARY
    FILE *fptr;
    fptr = fopen("Books.bin", "wb");

    //  IF FILE OPENS
    if (fptr != NULL)
    {

        Book *new = start;
        Book *temp = NULL;

        //IF START POSITION ISNT NULL WRITE TO FILE
        while (new != NULL)
        {
            //  TEMP
            temp = new->next;

            new->next = NULL;

            //  FILE PTR TO END OF FILE PRINT BOOKSTRUCT
            fseek(fptr, 0, SEEK_END);
            fwrite(new->bookName, sizeof(Book), 1, fptr);

            printf("Writing To File Book: " KCYN "%s" reset "", new->bookName);

            //  SET POINTERS BACK TO NOT BREAK THE LIST
            new->next = temp;
            temp = NULL;

            //  NEW IS NEXT POINTER
            new = new->next;
        }

        fclose(fptr);
        fptr = NULL;
    }
    else
    {
        printf(KRED "\nError: Opening File\n" reset);
        exit(2);
    }
}

//  APPEND FUNCTION
Book *Append(Book *start, Book *last, Book *move)
{
    char ch;
    double numDouble;
    int numInt;
    char userInput[255];
    Book *new = NULL;

    if (start == NULL)
    {
        //  allocate a block of memory for Book
        new = (Book *)malloc(sizeof(Book));

        if (new == NULL)
        {
            puts(KRED "\nError: Memory allocation\n" reset);
            exit(1);
        }

        //  assign new block to start
        start = new;

        //  get information
        printf("\n");

        printf("Enter Book Title: ");
        fgets(userInput, 255, stdin);
        strcpy(start->bookName, userInput);

        printf("Enter Author Name: ");
        fgets(userInput, 255, stdin);
        strcpy(start->author, userInput);

        printf("Enter Publisher Name: ");
        fgets(userInput, 255, stdin);
        strcpy(start->publisher, userInput);

        printf("Enter Replacement Cost: ");
        scanf("%lf", &numDouble);
        start->replacementCost = numDouble;
        while ((ch = getchar()) != '\n' && ch != EOF)
            ;

        printf("Enter Subject: ");
        fgets(userInput, 255, stdin);
        strcpy(start->subjectOfMaterial, userInput);

        printf("Enter Index Number: ");
        scanf("%d", &numInt);
        start->indexNumber = numInt;
        while ((ch = getchar()) != '\n' && ch != EOF)
            ;

        printf("Currently Loaned To: ");
        fgets(userInput, 255, stdin);
        strcpy(start->currentlyOnLoanTo, userInput);

        printf("Enter Due Date[YYYY-MM-DD]: ");
        fgets(userInput, 255, stdin);
        strcpy(start->dueDate, userInput);

        printf("\n");

        //  pointer to next is null to indicate nothing follows
        start->next = NULL;
        //  change last pointer to point to the one just created
        last = start;
        move = last;
    }
    else
    {
        // IF INDEX = START AND NEXT IS NOT NULL INDEX = INDEXBOOK-NEXT
        Book *indexBook = start;
        while (indexBook->next != NULL)
        {
            indexBook = indexBook->next;
        }
        //  WHEN INDEX-> IS NULL CALL NEWBOOK FUNCTION
        new = NewBook(start, last, move);
        indexBook->next = new;
        new->next = NULL;
    }
    return start;
}

//  NEW ENTRY FUNCTION
Book *NewBook(Book *start, Book *last, Book *move)
{
    Book *new = NULL;
    double numDouble;
    int numInt;
    char ch;
    char userInput[255];

    //  ALLOCATE MEMORY
    new = (Book *)malloc(sizeof(Book));

    //get information
    printf("\n");

    printf("Enter Book Title: ");
    fgets(userInput, 255, stdin);
    strcpy(new->bookName, userInput);

    printf("Enter Author Name: ");
    fgets(userInput, 255, stdin);
    strcpy(new->author, userInput);

    printf("Enter Publisher Name: ");
    fgets(userInput, 255, stdin);
    strcpy(new->publisher, userInput);

    printf("Enter Replacement Cost: ");
    scanf("%lf", &numDouble);
    new->replacementCost = numDouble;
    while ((ch = getchar()) != '\n' && ch != EOF)
        ;

    printf("Enter Subject: ");
    fgets(userInput, 255, stdin);
    strcpy(new->subjectOfMaterial, userInput);

    printf("Enter Index Number: ");
    scanf("%d", &numInt);
    new->indexNumber = numInt;
    while ((ch = getchar()) != '\n' && ch != EOF)
        ;

    printf("Currently Loaned To: ");
    fgets(userInput, 255, stdin);
    strcpy(new->currentlyOnLoanTo, userInput);

    printf("Enter Due Date[YYYY-MM-DD]: ");
    fgets(userInput, 255, stdin);
    strcpy(new->dueDate, userInput);

    printf("\n");

    new->next = NULL;
    last = new;
    move = last;

    return new;
}

//  DELETE FUNCTION USING POINTER TO A POINTER
void Delete(Book **start, Book *last, Book *move)
{
    Book *temp = *start;
    // Book *previous = NULL;

    //  CHECK IF LIST IS EMPTY
    if (*start == NULL)
    {
        last = NULL;
        move = NULL;
        printf(KRED "\n*List is empty.\n" reset);
        return;
    }

    //  USER INPUT
    printf("\nEnter Book Title To Delete Book: ");
    char userInput[255];
    fgets(userInput, 255, stdin);

    if (temp != NULL && strncmp(userInput, temp->bookName, strlen(temp->bookName)) == 0)
    {
        //  IF FIRST POSITION MOVE START TO TEMP->NEXT; FREE TEMP
        *start = temp->next;
        move = *start;
        printf(KRED "\n*%sMemory Freed\n" reset "", temp);
        free(temp);
        return;
    }

    while ((temp != NULL && strncmp(userInput, temp->bookName, strlen(temp->bookName)) != 0))
    {
        //  IF NOT MOVE = TEMP; TEMP = TEMP->NEXT;
        move = temp;
        temp = temp->next;
    }
    //GET TEMP->NEXT POSTION; DELETE TEMP
    move->next = temp->next;
    last = move;
    printf(KRED "\n*%sMemory Freed 2\n" reset "", temp);
    free(temp);
}
//  SORT FUNCTION
void Sort(Book *start)
{
    Book *i, *j;
    char temp[100];
    double tempDouble;
    int tempInt;

    //COMPARE I TO J SAME AS ASSIGNMENT 2
    for (i = start; i->next != NULL; i = i->next)
    {
        for (j = i->next; j != NULL; j = j->next)
        {
            //IF I IS > J I EQUALS 1
            if (strcmp(i->bookName, j->bookName) > 0)
            {
                //  COPY I  VALUE TO TEMP
                strcpy(temp, i->bookName);
                //  COPY J VALUE T I
                strcpy(i->bookName, j->bookName);
                //  COPY TEMP TO J -> SWITCHING THE VALUES OF I AND J
                strcpy(j->bookName, temp);

                strcpy(temp, i->author);
                strcpy(i->author, j->author);
                strcpy(j->author, temp);

                strcpy(temp, i->publisher);
                strcpy(i->publisher, j->publisher);
                strcpy(j->publisher, temp);

                tempDouble = i->replacementCost;
                i->replacementCost = j->replacementCost;
                j->replacementCost = tempDouble;

                strcpy(temp, i->subjectOfMaterial);
                strcpy(i->subjectOfMaterial, j->subjectOfMaterial);
                strcpy(j->subjectOfMaterial, temp);

                tempInt = i->indexNumber;
                i->indexNumber = j->indexNumber;
                j->indexNumber = tempInt;

                strcpy(temp, i->currentlyOnLoanTo);
                strcpy(i->currentlyOnLoanTo, j->currentlyOnLoanTo);
                strcpy(j->currentlyOnLoanTo, temp);

                strcpy(temp, i->dueDate);
                strcpy(i->dueDate, j->dueDate);
                strcpy(j->dueDate, temp);
            }
        }
    }
}

//  SEARCH BOOK NAME FUNCTION
void SearchBookName(Book *start, Book *move)
{
    move = start;

    if (start == NULL)
    {
        printf(KRED "\n*List is empty.\n" reset);
        main();
    }

    //  USER INPUT
    printf("Enter Book Title To Search: ");
    char userInput[255];
    fgets(userInput, 255, stdin);

    printf("\nSearch Results: " KCYN "%s" reset "\n", userInput);
    while (move != NULL)
    {

        //  COMPARE USER INPUT TO BOOKNAME IF EQUAL PRINT
        if (strcmp(move->bookName, userInput) == 0)
        {
            printf("\n");
            printf(UYEL "BOOK\n" reset);
            printf(KCYN "Book Title: " reset "%s", move->bookName);
            printf(KCYN "Author: " reset "%s", move->author);
            printf(KCYN "Publisher: " reset "%s", move->publisher);
            printf(KCYN "Replacement Cost: " reset "%.2lf\n", move->replacementCost);
            printf(KCYN "Subject: " reset "%s", move->subjectOfMaterial);
            printf(KCYN "Index Number: " reset "%d\n", move->indexNumber);
            printf(KCYN "Currently Loaned To: " reset "%s", move->currentlyOnLoanTo);
            printf(KCYN "Due Date: " reset "%s", move->dueDate);
            printf("--------------------------\n\n");
            return;
        } //IF NOT LOOP BACK THROUGH
        move = move->next;
    }

    printf(KRED "*No Book By That Name.\n" reset);
}

//  SEARCH AUTHOR NAME FUNCTION
void SearchAuthorName(Book *start, Book *move)
{
    move = start;

    if (start == NULL)
    {
        printf(KRED "\n*List is empty.\n" reset);
        main();
    }

    //GET USER INPUT
    printf("Enter Author Name To Search: ");
    char userInput[255];
    fgets(userInput, 255, stdin);

    printf("\nSearch Results: " KCYN "%s" reset "\n", userInput);
    while (move != NULL)
    {

        //  COMPARE USER INPUT TO AUTHOR IF EQUAL PRINT
        if (strcmp(move->author, userInput) == 0)
        {
            printf("\n");
            printf(UYEL "BOOK\n" reset);
            // printf("--------------------------\n");
            printf(KCYN "Book Title: " reset "%s", move->bookName);
            printf(KCYN "Author: " reset "%s", move->author);
            printf(KCYN "Publisher: " reset "%s", move->publisher);
            printf(KCYN "Replacement Cost: " reset "%.2lf\n", move->replacementCost);
            printf(KCYN "Subject: " reset "%s", move->subjectOfMaterial);
            printf(KCYN "Index Number: " reset "%d\n", move->indexNumber);
            printf(KCYN "Currently Loaned To: " reset "%s", move->currentlyOnLoanTo);
            printf(KCYN "Due Date: " reset "%s", move->dueDate);
            printf("--------------------------\n\n");
            return;
        }
        //  ELSE LOOP THOUGH
        else
        {
            move = move->next;
        }
    }
    printf(KRED "*No Author By That Name.\n" reset);
}

void Modify(Book *start, Book *move)
{
    Book *temp = NULL;

    move = start;

    if (start == NULL)
    {
        printf(KRED "\n*List is empty.\n" reset);
        main();
    }

    //  GET USER INPUT
    printf("\nEnter Book Title To Modify: ");
    char userInput[255];
    fgets(userInput, 255, stdin);

    while (move != NULL)
    {

        //  IF BOOKNAME EQUALS USER INPUT PRINT THAT POINTER
        if (strcmp(move->bookName, userInput) == 0)
        {
            printf("\n");
            printf(UYEL "BOOK\n" reset);
            // printf("--------------------------\n");
            printf(KCYN "Book Title: " reset "%s", move->bookName);
            printf(KCYN "Author: " reset "%s", move->author);
            printf(KCYN "Publisher: " reset "%s", move->publisher);
            printf(KCYN "Replacement Cost: " reset "%.2lf\n", move->replacementCost);
            printf(KCYN "Subject: " reset "%s", move->subjectOfMaterial);
            printf(KCYN "Index Number: " reset "%d\n", move->indexNumber);
            printf(KCYN "Currently Loaned To: " reset "%s", move->currentlyOnLoanTo);
            printf(KCYN "Due Date: " reset "%s", move->dueDate);
            printf("--------------------------\n\n");

            temp = move;
        }

        move = move->next;
    }

    ModSelection(start, move, temp);
}

//  MODIIFY SELECTION FUCNTION
void ModSelection(Book *start, Book *move, Book *temp)
{
    double numDouble;
    int numInt;
    int menuInput = -1;
    char ch;

    //CALL MENU
    ModifyMenu(temp);

    // GET USER INPUT
    printf("\nSelect An Option ");
    scanf("%d", &menuInput);
    while ((ch = getchar()) != '\n' && ch != EOF)
        ;
    char titleName[255];
    while (menuInput != 0)
    {
        switch (menuInput)
        {
        case 0:
            menuInput = 0;
        case 1:
            //  CALL MODIFY MENU TO ENTER A NEW BOOK
            Modify(start, move);
        case 2:
            //  PROMPT FOR USER INPUT -> COPY NEW INOUT OVER OLD -> BREAK LOOP -> CALL FUNCTION AGAIN
            printf("\nEdit Book Title - " KCYN "%s" reset "", temp->bookName);
            printf("Edit: ");
            fgets(titleName, 255, stdin);
            strcpy(temp->bookName, titleName);
            menuInput = 0;
            ModSelection(start, move, temp);
            break;
        case 3:
            printf("\nEdit Author Name - " KCYN "%s" reset "", temp->author);
            printf("Edit: ");
            fgets(titleName, 255, stdin);
            strcpy(temp->author, titleName);
            menuInput = 0;
            ModSelection(start, move, temp);
            break;
        case 4:
            printf("\nEdit Publisher - " KCYN "%s" reset "", temp->publisher);
            printf("Edit: ");
            fgets(titleName, 255, stdin);
            strcpy(temp->publisher, titleName);
            menuInput = 0;
            ModSelection(start, move, temp);
            break;
        case 5:
            printf("\nEdit Replacement Cost - " KCYN "%.2lf\n" reset "", temp->replacementCost);
            printf("Edit: ");
            scanf("%lf", &numDouble);
            temp->replacementCost = numDouble;
            while ((ch = getchar()) != '\n' && ch != EOF)
                ;
            menuInput = 0;
            ModSelection(start, move, temp);
            break;
        case 6:
            printf("\nEdit Subject - " KCYN "%s" reset "", temp->subjectOfMaterial);
            printf("Edit: ");
            fgets(titleName, 255, stdin);
            strcpy(temp->subjectOfMaterial, titleName);
            menuInput = 0;
            ModSelection(start, move, temp);
            break;
        case 7:
            printf("\nEdit Index Number - " KCYN "%d\n" reset "", temp->indexNumber);
            printf("Edit: ");
            scanf("%d", &numInt);
            temp->indexNumber = numInt;
            while ((ch = getchar()) != '\n' && ch != EOF)
                ;
            menuInput = 0;
            ModSelection(start, move, temp);
            break;
        case 8:
            printf("\nEdit Currently Loaned To - " KCYN "%s" reset "", temp->currentlyOnLoanTo);
            printf("Edit: ");
            fgets(titleName, 255, stdin);
            strcpy(temp->currentlyOnLoanTo, titleName);
            menuInput = 0;
            ModSelection(start, move, temp);
            break;
        case 9:
            printf("\nEdit Due Date[YYYY-MM-DD] - " KCYN "%s" reset "", temp->dueDate);
            printf("Edit: ");
            fgets(titleName, 255, stdin);
            strcpy(temp->dueDate, titleName);
            menuInput = 0;
            ModSelection(start, move, temp);
            break;
        default:
            printf(KRED "\n*Invalid Selection\n" reset);
        }
    }
}

// MODIFY MENU FUNCTION
void ModifyMenu(Book *temp)
{
    printf("\n");
    printf(UYEL "\tModify\n" reset);
    printf("--------------------------\n");
    printf(KRED "1" reset ". Select A Different Book\n");
    printf(KCYN "2" reset ". Book Title: %s", temp->bookName);
    printf(KCYN "3" reset ". Author: %s", temp->author);
    printf(KCYN "4" reset ". Publisher: %s", temp->publisher);
    printf(KCYN "5" reset ". Replacement Cost: %.2lf\n", temp->replacementCost);
    printf(KCYN "6" reset ". Subject: %s", temp->subjectOfMaterial);
    printf(KCYN "7" reset ". Index Number: %d\n", temp->indexNumber);
    printf(KCYN "8" reset ". Currently Loaned To: %s", temp->currentlyOnLoanTo);
    printf(KCYN "9" reset ". Due Date: %s", temp->dueDate);
    printf(KRED "0" reset ". Menu\n");
}

//  CLEAR ON EXIT FUNCTION I DIDNT WRITE THIS I FOUND IT TRYING TO BETTER UNDERSTAND POINTER TO POINTER
void ClearOnExit(Book **start)
{
    if (*start == NULL)
    {
        return;
    }

    if ((*start)->next)
    {
        ClearOnExit(&((*start)->next));
    }

    printf("\nDeleting %s", (*start)->bookName);
    free(*start);
}

//  I USED THIS TO FOLLOW MY POINTERS TO MAKE SURE I UNDERSTOOD WHAT WAS HAPPENING.
//  IN THE END I THINK IT DID MORE DAMAGE THEN GOOD GETTING ME TO ADD MORE PARAMETERS TO FUNCTIONS THEN NEEDED RESULTING IN MORE CODE.
//  ORDER 66 TO CALL THIS FUNCTION.
void TEST(Book *start, Book *last, Book *move)
{
    printf("\n");

    printf("Start Pointer: %s\n", start);
    printf("Last Pointer: %s\n", last);
    printf("Move Pointer: %s\n", move);
    Menu();
}
