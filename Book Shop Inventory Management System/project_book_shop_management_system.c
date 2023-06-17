/*******************************************************************************
 *
 * Project: Book Shop Management System
 *
 * Description: Just a learning step towards the working of a book shop inventory management system
 *
 * By: Aditya Chikte
 *
 * Github: @adicodes11
 *
 *******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>

#define MIN_SIZE 20
#define MID_SIZE 50
#define LARGE_SIZE 100
#define XTRA_LARGE_SIZE 500
#define BUFFER_SIZE 2048

#define MAX_FIELDS 12
#define MAX_FIELD_SIZE 100

// 3 IMPS
void start();
void login();
void main_menu();

// MAIN MENU FUNCTIONS
void add_book();
void delete_book();
void search_book();
void buy_book();
void new_receipt(char item[100][100], double price[], int quantity[], int *count, double amount[], double *total, double tax);
void print_receipt(char *shop_name, char *address, char *mobile, char item[100][100], float price[], int quantity[], int count, float amount[], float total, float tax, char *transaction_id);
void view_all();
void modify_record();
void change_password();

// OTHER FUNCTIONS
int get_console_line_number();
void liner();
void clear_screen(int start_row, int start_col, int end_row, int end_col);
void boxer(char *pre, char *per, int line);

// DRIVER CODE
int main()
{
    start();
    login();
    main_menu();

    return 0;
}

// Starting Interface of the system
void start()
{
    printf(" __        __   _                            _ \n");
    printf(" \\ \\      / /__| | ___ ___  _ __ ___   ___  | |\n");
    printf("  \\ \\ /\\ / / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\ | |\n");
    printf("   \\ V  V /  __/ | (_| (_) | | | | | |  __/ |_|\n");
    printf("    \\_/\\_/ \\___|_|\\___\\___/|_| |_| |_|\\___| (_)");
    printf("\n\n\n");
}

// Function for Administrator Login
void login()
{
    int line;
    FILE *file = fopen("admin.txt", "r");
    char buffer[MID_SIZE];

    // Error Handling
    if (file == NULL)
    {
        printf("Error loading login screen...\n");
        exit(0);
    }
    char name[MID_SIZE], id[MIN_SIZE], password[MIN_SIZE];

    printf("%20sLOGIN\n\n\n", " ");

    // Enter Name
    fgets(buffer, MID_SIZE, file);
    buffer[strlen(buffer) - 1] = '\0';
    while (true)
    {
        printf("Enter Name: ");
        fgets(name, MID_SIZE, stdin);
        name[strlen(name) - 1] = '\0';

        // Verfication
        if (strcmp(name, buffer) == 0)
        {
            line = get_console_line_number();
            boxer("Enter name: ", name, line);
            printf("\n");
            break;
        }
        else
        {
            line = get_console_line_number();
            clear_screen(line - 1, 0, line - 1, 1000);
            printf("Enter valid name!!\n");
        }
    }

    // Enter ID
    fgets(buffer, MID_SIZE, file);
    buffer[strlen(buffer) - 1] = '\0';
    while (true)
    {
        printf("Enter ID: ");
        scanf(" %s", &id);

        // Verfication
        if (strcmp(id, buffer) == 0)
        {
            line = get_console_line_number();
            boxer("Enter ID: ", id, line);
            printf("\n");
            break;
        }
        else
        {
            line = get_console_line_number();
            clear_screen(line - 1, 0, line - 1, 1000);
            printf("Enter valid ID!!\n");
        }
    }

    // Enter Password
    fgets(buffer, MID_SIZE, file);
    buffer[strlen(buffer) - 1] = '\0';
    while (true)
    {
        printf("Enter password: ");
        scanf(" %s", &password);

        // Verification
        if (strcmp(password, buffer) == 0)
        {
            line = get_console_line_number();
            boxer("Enter password: ", password, line);
            printf("LOGIN SUCCESSFUL\n\n");
            printf("Welcome %s\n\n", name);
            printf("\n");
            break;
        }
        else
        {
            line = get_console_line_number();
            clear_screen(line - 1, 0, line - 1, 1000);
            printf("Enter valid password!!\n");
        }
    }
    fclose(file);
}

// Function to display the Main Menu
void main_menu()
{
    int choice;
    do
    {
        printf("\n\n\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB   MAIN MENU   \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\n\n", " ");
        printf("1.ADD BOOKS\n");
        printf("2.DELETE BOOKS\n");
        printf("3.SEARCH BOOKS\n");
        printf("4.BUY BOOKS\n");
        printf("5.VIEW ALL BOOKS\n");
        printf("6.MODIFY RECORD\n");
        printf("7.CHANGE PASSWORD\n");
        printf("8.EXIT APPLICATION\n\n");
        printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\n\n", " ");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            add_book();
            break;
        case 2:
            delete_book();
            break;
        case 3:
            search_book();
            break;
        case 4:
            buy_book();
            break;
        case 5:
            view_all();
            break;
        case 6:
            modify_record();
            break;
        case 7:
            change_password();
            break;
        case 8:
            printf("Application exited successfully\n\n");
            exit(0);
            break;

        default:
            printf("Enter a valid choice!!\n\n");
            break;
        }
    } while (true);
}

// Function to add new books
void add_book()
{
    fflush(stdin);
    FILE *file = fopen("book_records.txt", "a");

    // Error Handling
    if (file == NULL)
    {
        printf("Error adding book...\n");
        exit(0);
    }

    fputc('\n', file);

    char title[MID_SIZE];
    char author[MID_SIZE];
    char publisher[MID_SIZE];
    char publication_year[MID_SIZE];
    char genre[MID_SIZE];
    char language[MID_SIZE];
    char page_count[MID_SIZE];
    char availability[MID_SIZE];
    char location[MID_SIZE];
    char ratings[MID_SIZE];
    char price[MID_SIZE];
    char stock[MID_SIZE];

    // New Book Input
    printf("Title: ");
    fgets(title, MID_SIZE, stdin);
    title[strlen(title) - 1] = '\0';

    printf("Author: ");
    fgets(author, MID_SIZE, stdin);
    author[strlen(author) - 1] = '\0';

    printf("Publisher: ");
    fgets(publisher, MID_SIZE, stdin);
    publisher[strlen(publisher) - 1] = '\0';

    printf("Publication Year: ");
    fgets(publication_year, MID_SIZE, stdin);
    publication_year[strlen(publication_year) - 1] = '\0';

    printf("Genre: ");
    fgets(genre, MID_SIZE, stdin);
    genre[strlen(genre) - 1] = '\0';

    printf("Language: ");
    fgets(language, MID_SIZE, stdin);
    language[strlen(language) - 1] = '\0';

    printf("Page count: ");
    fgets(page_count, MID_SIZE, stdin);
    page_count[strlen(page_count) - 1] = '\0';

    printf("Availability: ");
    fgets(availability, MID_SIZE, stdin);
    availability[strlen(availability) - 1] = '\0';

    printf("Location: ");
    fgets(location, MID_SIZE, stdin);
    location[strlen(location) - 1] = '\0';

    printf("Ratings: ");
    fgets(ratings, MID_SIZE, stdin);
    ratings[strlen(ratings) - 1] = '\0';

    printf("Price: ");
    fgets(price, MID_SIZE, stdin);
    price[strlen(price) - 1] = '\0';

    printf("Stock: ");
    fgets(stock, MID_SIZE, stdin);
    stock[strlen(stock) - 1] = '\0';

    // Adding new book to the book records
    fprintf(file, "\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",",
            title, author, publisher, publication_year, genre, language, page_count, availability, location, ratings, price, stock);

    fclose(file);
}

// Function to delete a book from record
void delete_book()
{
    fflush(stdin);
    FILE *file = fopen("book_records.txt", "r");

    // Error Handling
    if (file == NULL)
    {
        printf("Error searching book...\n");
        exit(0);
    }

    char search[MID_SIZE];
    fflush(stdin);
    printf("Enter the book to delete: ");
    fgets(search, MID_SIZE, stdin);
    search[strlen(search) - 1] = '\0';

    char line[BUFFER_SIZE];
    int record_number = 0;
    int delete_line = 0;
    bool found = false;
    while (fgets(line, BUFFER_SIZE, file) != NULL)
    {
        record_number++;
        // Remove trailing newline character
        line[strcspn(line, "\n")] = '\0';

        // Tokenize the line using comma as the delimiter
        char *field;
        char *tokens[MAX_FIELDS];
        int fieldCount = 0;

        field = strtok(line, "\",");
        while (field != NULL && fieldCount < MAX_FIELDS)
        {
            tokens[fieldCount] = field;
            fieldCount++;
            field = strtok(NULL, "\",");
        }
        // Ensure we have the correct number of fields
        if (fieldCount == MAX_FIELDS)
        {
            char *title = tokens[0];
            char *author = tokens[1];
            char *publisher = tokens[2];
            char *publication_year = tokens[3];
            char *genre = tokens[4];
            char *language = tokens[5];
            char *page_count = tokens[6];
            char *availability = tokens[7];
            char *location = tokens[8];
            char *ratings = tokens[9];
            char *price = tokens[10];
            char *stock = tokens[11];

            if (strcmp(search, title) == 0)
            {
                found = true;
                printf("\n\n");
                printf("SR NO.| TITLE                 | AUTHOR                | PUBLISHER          | YEAR | GENRE             | LANGUAGE    | PAGES | STATUS      | LOCATION                 | RATING | PRICE | STOCK |\n");
                printf("===============================================================================================================================================================================================\n");
                printf("%-5d", record_number);
                printf("%3s%-21s", " ", title);
                printf("%3s%-21s", " ", author);
                printf("%3s%-18s", " ", publisher);
                printf("%3s%-4s", " ", publication_year);
                printf("%3s%-17s", " ", genre);
                printf("%3s%-11s", " ", language);
                printf("%3s%-5s", " ", page_count);
                printf("%3s%-11s", " ", availability);
                printf("%3s%-25s", " ", location);
                printf("%3s%-6s", " ", ratings);
                printf("%3s%-5s", " ", price);
                printf("%3s%-5s\n", " ", stock);

                // Validation to delete
                char sure = 'n';
                printf("\n\nAre you sure to delete this book (y/n): ");
                scanf(" %c", &sure);
                if (sure == 'N' || sure == 'n')
                {
                    goto end;
                }
                else
                {
                    rewind(file);
                }

                FILE *temp = fopen("temp_book_records.txt", "w");
                char buffer[XTRA_LARGE_SIZE];
                // Error Handling
                if (temp == NULL)
                {
                    printf("Error searching book...\n");
                    exit(0);
                }

                while (fgets(buffer, XTRA_LARGE_SIZE, file) != NULL)
                {
                    delete_line++;
                    if (delete_line != record_number)
                    {
                        fputs(buffer, temp);
                    }
                }
                fclose(file);
                fclose(temp);

                printf("\nBook deleted successfully!!\n\n");

                remove("book_records.txt");
                rename("temp_book_records.txt", "book_records.txt");
                goto end;
            }
        }
    }
    if (!found)
    {
        printf("Book Record not found\n\n");
    }
end:
    printf("\n\n");
}

// Function to search book
void search_book()
{
    FILE *file = fopen("book_records.txt", "r");

    // Error Handling
    if (file == NULL)
    {
        printf("Error searching book...\n");
        exit(0);
    }

    char search[MID_SIZE];
    fflush(stdin);
    printf("Enter the book search: ");
    fgets(search, MID_SIZE, stdin);
    search[strlen(search) - 1] = '\0';

    char line[BUFFER_SIZE];
    int record_number = 0;
    bool found = false;
    while (fgets(line, BUFFER_SIZE, file) != NULL)
    {
        record_number++;
        // Remove trailing newline character
        line[strcspn(line, "\n")] = '\0';

        // Tokenize the line using comma as the delimiter
        char *field;
        char *tokens[MAX_FIELDS];
        int fieldCount = 0;

        field = strtok(line, "\",");
        while (field != NULL && fieldCount < MAX_FIELDS)
        {
            tokens[fieldCount] = field;
            fieldCount++;
            field = strtok(NULL, "\",");
        }
        // Ensure we have the correct number of fields
        if (fieldCount == MAX_FIELDS)
        {
            char *title = tokens[0];
            char *author = tokens[1];
            char *publisher = tokens[2];
            char *publication_year = tokens[3];
            char *genre = tokens[4];
            char *language = tokens[5];
            char *page_count = tokens[6];
            char *availability = tokens[7];
            char *location = tokens[8];
            char *ratings = tokens[9];
            char *price = tokens[10];
            char *stock = tokens[11];

            if (strcmp(search, title) == 0)
            {
                fclose(file);
                found = true;
                printf("\n\n");
                printf("SR NO.| TITLE                 | AUTHOR                | PUBLISHER          | YEAR | GENRE             | LANGUAGE    | PAGES | STATUS      | LOCATION                 | RATING | PRICE | STOCK |\n");
                printf("===============================================================================================================================================================================================\n");
                printf("%-5d", record_number);
                printf("%3s%-21s", " ", title);
                printf("%3s%-21s", " ", author);
                printf("%3s%-18s", " ", publisher);
                printf("%3s%-4s", " ", publication_year);
                printf("%3s%-17s", " ", genre);
                printf("%3s%-11s", " ", language);
                printf("%3s%-5s", " ", page_count);
                printf("%3s%-11s", " ", availability);
                printf("%3s%-25s", " ", location);
                printf("%3s%-6s", " ", ratings);
                printf("%3s%-5s", " ", price);
                printf("%3s%-5s\n", " ", stock);

                goto end;
            }
        }
    }
    if (!found)
    {
        printf("Book Record not found\n\n");
    }
end:
    printf("\n\n");
}

// Function to buy books
void buy_book()
{
    int i = 0;
    char to_print = 'c';
    char shop_name[LARGE_SIZE] = "The Book Haven";
    char address[LARGE_SIZE] = "22 Main Streets, Big City 00087";
    char mobile[11] = "8385919201";
    char item[LARGE_SIZE][LARGE_SIZE];
    float receipt_price[LARGE_SIZE];
    int quantity[LARGE_SIZE];
    int count = 0;
    float total = 0;
    float tax = 12;
    float amount[LARGE_SIZE];
    char transaction_id[MIN_SIZE];

    while (true)
    {
        FILE *file = fopen("book_records.txt", "r");
        FILE *temp = fopen("temp_book_records.txt", "w");
        fflush(stdin);
        char buffer[XTRA_LARGE_SIZE];

        // Error Handling
        if (file == NULL || temp == NULL)
        {
            printf("Error loading...\n");
            exit(0);
        }

        bool found = false;

        rewind(file);
        char search[MID_SIZE];
        fflush(stdin);
        printf("\n\nEnter title: ");
        fgets(search, MID_SIZE, stdin);
        search[strlen(search) - 1] = '\0';

        char line[BUFFER_SIZE];
        int record_number = 0;
        int modify_line = 0;
        while (fgets(line, BUFFER_SIZE, file) != NULL)
        {
            record_number++;
            // Remove trailing newline character
            line[strcspn(line, "\n")] = '\0';

            // Tokenize the line using comma as the delimiter
            char *field;
            char *tokens[MAX_FIELDS];
            int fieldCount = 0;

            field = strtok(line, "\",");
            while (field != NULL && fieldCount < MAX_FIELDS)
            {
                tokens[fieldCount] = field;
                fieldCount++;
                field = strtok(NULL, "\",");
            }
            // Ensure we have the correct number of fields
            if (fieldCount == MAX_FIELDS)
            {
                char *title = tokens[0];
                char *author = tokens[1];
                char *publisher = tokens[2];
                char *publication_year = tokens[3];
                char *genre = tokens[4];
                char *language = tokens[5];
                char *page_count = tokens[6];
                char *availability = tokens[7];
                char *location = tokens[8];
                char *ratings = tokens[9];
                char *price = tokens[10];
                char *stock = tokens[11];

                if (strcmp(search, title) == 0)
                {

                    found = true;
                    printf("\n\n");
                    printf("SR NO.| TITLE                 | AUTHOR                | PUBLISHER          | YEAR | GENRE             | LANGUAGE    | PAGES | STATUS      | LOCATION                 | RATING | PRICE | STOCK |\n");
                    printf("===============================================================================================================================================================================================\n");
                    printf("%-5d", record_number);
                    printf("%3s%-21s", " ", title);
                    printf("%3s%-21s", " ", author);
                    printf("%3s%-18s", " ", publisher);
                    printf("%3s%-4s", " ", publication_year);
                    printf("%3s%-17s", " ", genre);
                    printf("%3s%-11s", " ", language);
                    printf("%3s%-5s", " ", page_count);
                    printf("%3s%-11s", " ", availability);
                    printf("%3s%-25s", " ", location);
                    printf("%3s%-6s", " ", ratings);
                    printf("%3s%-5s", " ", price);
                    printf("%3s%-5s\n", " ", stock);

                    int copy_count = 0;
                    printf("\n\nEnter number of copies: ");
                    scanf("%d", &copy_count);

                    //
                    //
                    //  Hnady Variables
                    //
                    //
                    char temp_title[MID_SIZE];
                    strcpy(temp_title, title);

                    char temp_author[MID_SIZE];
                    strcpy(temp_author, author);

                    char temp_publisher[MID_SIZE];
                    strcpy(temp_publisher, publisher);

                    char temp_publication_year[MID_SIZE];
                    strcpy(temp_publication_year, publication_year);

                    char temp_genre[MID_SIZE];
                    strcpy(temp_genre, genre);

                    char temp_language[MID_SIZE];
                    strcpy(temp_language, language);

                    char temp_page_count[MID_SIZE];
                    strcpy(temp_page_count, page_count);

                    char temp_availability[MID_SIZE];
                    strcpy(temp_availability, availability);

                    char temp_location[MID_SIZE];
                    strcpy(temp_location, location);

                    char temp_ratings[MID_SIZE];
                    strcpy(temp_ratings, ratings);

                    char temp_price[MID_SIZE];
                    strcpy(temp_price, price);
                    float book_price = atof(temp_price);

                    char temp_stock[MID_SIZE];
                    strcpy(temp_stock, stock);
                    int book_stock = atoi(temp_stock);

                    if (book_stock >= copy_count)
                    {

                        // Modification fetch
                        book_stock = book_stock - copy_count;
                        sprintf(temp_stock, "%d", book_stock);

                        // Validation to modify
                        char sure = 'n';
                        printf("\nConfirm Purchase (y/n): ");
                        scanf(" %c", &sure);
                        if (sure == 'N' || sure == 'n')
                        {
                            goto end;
                        }

                        rewind(file);

                        while (fgets(buffer, XTRA_LARGE_SIZE, file) != NULL)
                        {
                            modify_line++;
                            if (modify_line != record_number)
                            {
                                fputs(buffer, temp);
                            }
                            else if (modify_line == record_number)
                            {
                                // Adding modified record
                                fprintf(temp, "\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",",
                                        temp_title, temp_author, temp_publisher, temp_publication_year, temp_genre, temp_language,
                                        temp_page_count, temp_availability, temp_location, temp_ratings, temp_price, temp_stock);
                                fputc('\n', temp);
                            }
                        }

                        fclose(file);
                        fclose(temp);
                        remove("book_records.txt");
                        rename("temp_book_records.txt", "book_records.txt");

                        //*****************************************************************************************************************************************

                        strcpy(item[i], temp_title);
                        receipt_price[i] = book_price;
                        quantity[i] = copy_count;
                        amount[i] = receipt_price[i] * quantity[i];
                        total += amount[i];
                        count++;
                        i++;

                        if (count > 0)
                        {
                            printf("Press P to print receipt: ");
                            scanf(" %c", &to_print);
                            if (to_print == 'p' || to_print == 'P')
                            {
                                print_receipt(shop_name, address, mobile, item, receipt_price, quantity, count, amount, total, tax, transaction_id);
                                goto end;
                            }
                        }

                        //*****************************************************************************************************************************************
                    }
                    else
                    {
                        printf("Book stock can't meet the demanded copy count!!\n");
                    }
                }
            }
        }

        if (!found)
        {
            printf("Book Record not found\n\n");
        }
    }
end:
    printf("\n\n");
}

// Function to print the cash receipt
void print_receipt(char *shop_name, char *address, char *mobile, char item[100][100], float price[], int quantity[], int count, float amount[], float total, float tax, char *transaction_id)
{
    // Display format
    printf("\n\n");
    printf("|%60s|\n", " ");
    printf("%25s%s\n", " ", "CASH RECEIPT");
    printf("%28s%s\n\n", " ", "*****");
    printf("%24s%s\n", " ", shop_name);
    printf("%15s%s\n", " ", address);
    printf("%26s%s\n", " ", mobile);
    printf("%28s%s\n\n", " ", "*****");
    printf("%2sDate:%55s\n", " ", __DATE__);
    printf("%2s============================================================\n", " ");
    printf("%2sItems             Price             Qty.              Amount\n\n", " ");
    for (int i = 0; i < count; i++)
    {
        printf("%2s%-16s%2s%-16.2lf%2s%-5d%2s%17.2lf\n", " ", item[i], " ", price[i], " ", quantity[i], " ", amount[i]);
    }

    printf("\n");
    printf("%2s------------------------------------------------------------\n", " ");
    printf("%2sTotal:%54.2lf\n", " ", total);
    double tax_amount = ((total * tax) / 100.0);
    printf("%2sTax:%56.2lf\n", " ", tax_amount);
    printf("%2sAmount to pay:%46.2lf\n", " ", total + tax_amount);
    printf("%2s------------------------------------------------------------\n", " ");
    printf("%2sTransaction id:\n", " ");
    printf("%2s%s%49s\n\n", " ", __DATE__, __TIME__);
    printf("%25sTHANK YOU!\n", " ");
    printf("%2s------------------------------------------------------------\n", " ");
    printf("%2s------------------------------------------------------------\n", " ");
    printf("\n\n");
}

// Function to read all book records in the system
void view_all()
{
    FILE *file = fopen("book_records.txt", "r");

    // Error Handling
    if (file == NULL)
    {
        printf("Error loading book records...\n");
        exit(0);
    }

    printf("SR NO.| TITLE                 | AUTHOR                | PUBLISHER          | YEAR | GENRE             | LANGUAGE    | PAGES | STATUS      | LOCATION                 | RATING | PRICE | STOCK |\n");
    printf("===============================================================================================================================================================================================\n");
    int record_number = 0;
    char line[BUFFER_SIZE];
    while (fgets(line, BUFFER_SIZE, file) != NULL)
    {
        record_number++;
        // Remove trailing newline character
        line[strcspn(line, "\n")] = '\0';

        // Tokenize the line using comma as the delimiter
        char *field;
        char *tokens[MAX_FIELDS];
        int fieldCount = 0;

        field = strtok(line, "\",");
        while (field != NULL && fieldCount < MAX_FIELDS)
        {
            tokens[fieldCount] = field;
            fieldCount++;
            field = strtok(NULL, "\",");
        }

        // Ensure we have the correct number of fields
        if (fieldCount == MAX_FIELDS)
        {
            char *title = tokens[0];
            char *author = tokens[1];
            char *publisher = tokens[2];
            char *publication_year = tokens[3];
            char *genre = tokens[4];
            char *language = tokens[5];
            char *page_count = tokens[6];
            char *availability = tokens[7];
            char *location = tokens[8];
            char *ratings = tokens[9];
            char *price = tokens[10];
            char *stock = tokens[11];

            printf("%-5d", record_number);
            printf("%3s%-21s", " ", title);
            printf("%3s%-21s", " ", author);
            printf("%3s%-18s", " ", publisher);
            printf("%3s%-4s", " ", publication_year);
            printf("%3s%-17s", " ", genre);
            printf("%3s%-11s", " ", language);
            printf("%3s%-5s", " ", page_count);
            printf("%3s%-11s", " ", availability);
            printf("%3s%-25s", " ", location);
            printf("%3s%-6s", " ", ratings);
            printf("%3s%-5s", " ", price);
            printf("%3s%-5s\n", " ", stock);

            printf("\n");
        }
    }

    fclose(file);
}

// Function to modify records
void modify_record()
{
    fflush(stdin);
    FILE *file = fopen("book_records.txt", "r");
    FILE *temp = fopen("temp_book_records.txt", "w");
    char buffer[XTRA_LARGE_SIZE];

    // Error Handling
    if (file == NULL || temp == NULL)
    {
        printf("Error modifying book...\n");
        exit(0);
    }

    char search[MID_SIZE];
    fflush(stdin);
    printf("Enter the book record to be modified: ");
    fgets(search, MID_SIZE, stdin);
    search[strlen(search) - 1] = '\0';

    char line[BUFFER_SIZE];
    int record_number = 0;
    int modify_line = 0;
    bool found = false;
    while (fgets(line, BUFFER_SIZE, file) != NULL)
    {
        record_number++;
        // Remove trailing newline character
        line[strcspn(line, "\n")] = '\0';

        // Tokenize the line using comma as the delimiter
        char *field;
        char *tokens[MAX_FIELDS];
        int fieldCount = 0;

        field = strtok(line, "\",");
        while (field != NULL && fieldCount < MAX_FIELDS)
        {
            tokens[fieldCount] = field;
            fieldCount++;
            field = strtok(NULL, "\",");
        }
        // Ensure we have the correct number of fields
        if (fieldCount == MAX_FIELDS)
        {
            char *title = tokens[0];
            char *author = tokens[1];
            char *publisher = tokens[2];
            char *publication_year = tokens[3];
            char *genre = tokens[4];
            char *language = tokens[5];
            char *page_count = tokens[6];
            char *availability = tokens[7];
            char *location = tokens[8];
            char *ratings = tokens[9];
            char *price = tokens[10];
            char *stock = tokens[11];

            if (strcmp(search, title) == 0)
            {

                found = true;
                printf("\n\n");
                printf("SR NO.| TITLE                 | AUTHOR                | PUBLISHER          | YEAR | GENRE             | LANGUAGE    | PAGES | STATUS      | LOCATION                 | RATING | PRICE | STOCK |\n");
                printf("===============================================================================================================================================================================================\n");
                printf("%-5d", record_number);
                printf("%3s%-21s", " ", title);
                printf("%3s%-21s", " ", author);
                printf("%3s%-18s", " ", publisher);
                printf("%3s%-4s", " ", publication_year);
                printf("%3s%-17s", " ", genre);
                printf("%3s%-11s", " ", language);
                printf("%3s%-5s", " ", page_count);
                printf("%3s%-11s", " ", availability);
                printf("%3s%-25s", " ", location);
                printf("%3s%-6s", " ", ratings);
                printf("%3s%-5s", " ", price);
                printf("%3s%-5s\n", " ", stock);

                //
                //
                // Modification variables
                //
                //
                char temp_title[MID_SIZE];
                strcpy(temp_title, title);

                char temp_author[MID_SIZE];
                strcpy(temp_author, author);

                char temp_publisher[MID_SIZE];
                strcpy(temp_publisher, publisher);

                char temp_publication_year[MID_SIZE];
                strcpy(temp_publication_year, publication_year);

                char temp_genre[MID_SIZE];
                strcpy(temp_genre, genre);

                char temp_language[MID_SIZE];
                strcpy(temp_language, language);

                char temp_page_count[MID_SIZE];
                strcpy(temp_page_count, page_count);

                char temp_availability[MID_SIZE];
                strcpy(temp_availability, availability);

                char temp_location[MID_SIZE];
                strcpy(temp_location, location);

                char temp_ratings[MID_SIZE];
                strcpy(temp_ratings, ratings);

                char temp_price[MID_SIZE];
                strcpy(temp_price, price);

                char temp_stock[MID_SIZE];
                strcpy(temp_stock, stock);

                // Modification fetch
                int choice;
                do
                {
                    fflush(stdin);
                    printf("\n\n------------- MODIFICATION MENU -------------\n\n", " ");
                    printf("0.SAVE\n");
                    printf("1.CHANGE TITLE\n");
                    printf("2.CHANGE AUTHOR\n");
                    printf("3.CHANGE PUBLISHER\n");
                    printf("4.CHANGE PUBLICATION YEAR\n");
                    printf("5.CHANGE GENRE\n");
                    printf("6.CHANGE LANGUAGE\n");
                    printf("7.CHANGE PAGE COUNT\n");
                    printf("8.CHANGE AVAILABILITY\n");
                    printf("9.CHANGE LOCATION\n");
                    printf("10.CHANGE RATINGS\n");
                    printf("11.CHANGE PRICE\n");
                    printf("12.CHANGE STOCK\n");
                    printf("13.BACK TO MAIN MENU\n\n");
                    printf("Enter your choice: ");
                    scanf("%d", &choice);
                    fflush(stdin);

                    switch (choice)
                    {
                    case 0:
                        goto validation;
                        break;
                    case 1:
                        printf("New Title: ");
                        fgets(temp_title, MID_SIZE, stdin);
                        temp_title[strlen(temp_title) - 1] = '\0';
                        break;
                    case 2:
                        printf("New Author: ");
                        fgets(temp_author, MID_SIZE, stdin);
                        temp_author[strlen(temp_author) - 1] = '\0';

                        break;
                    case 3:
                        printf("New Publisher: ");
                        fgets(temp_publisher, MID_SIZE, stdin);
                        temp_publisher[strlen(temp_publisher) - 1] = '\0';

                        break;
                    case 4:
                        printf("New Publication Year: ");
                        fgets(temp_publication_year, MID_SIZE, stdin);
                        temp_publication_year[strlen(temp_publication_year) - 1] = '\0';

                        break;
                    case 5:
                        printf("New Genre: ");
                        fgets(temp_genre, MID_SIZE, stdin);
                        temp_genre[strlen(temp_genre) - 1] = '\0';

                        break;
                    case 6:
                        printf("New Language: ");
                        fgets(temp_language, MID_SIZE, stdin);
                        temp_language[strlen(temp_language) - 1] = '\0';

                        break;
                    case 7:
                        printf("New Page count: ");
                        fgets(temp_page_count, MID_SIZE, stdin);
                        temp_page_count[strlen(temp_page_count) - 1] = '\0';

                        break;
                    case 8:
                        printf("New Availability: ");
                        fgets(temp_availability, MID_SIZE, stdin);
                        temp_availability[strlen(temp_availability) - 1] = '\0';

                        break;
                    case 9:
                        printf("New Location: ");
                        fgets(temp_location, MID_SIZE, stdin);
                        temp_location[strlen(temp_location) - 1] = '\0';

                        break;
                    case 10:
                        printf("New Ratings: ");
                        fgets(temp_ratings, MID_SIZE, stdin);
                        temp_ratings[strlen(temp_ratings) - 1] = '\0';

                        break;
                    case 11:
                        printf("New Price: ");
                        fgets(temp_price, MID_SIZE, stdin);
                        temp_price[strlen(temp_price) - 1] = '\0';

                        break;
                    case 12:
                        printf("New Stock: ");
                        fgets(temp_stock, MID_SIZE, stdin);
                        temp_stock[strlen(temp_stock) - 1] = '\0';

                        break;
                    case 13:
                        goto end;
                        break;

                    default:
                        printf("Enter a valid choice!!\n\n");
                        break;
                    }
                } while (true);

                // Validation to modify
                char sure = 'n';
            validation:
                printf("\n\nSave the modification (y/n): ");
                scanf(" %c", &sure);
                if (sure == 'N' || sure == 'n')
                {
                    goto end;
                }

                rewind(file);

                while (fgets(buffer, XTRA_LARGE_SIZE, file) != NULL)
                {
                    modify_line++;
                    if (modify_line != record_number)
                    {
                        fputs(buffer, temp);
                    }
                    else if (modify_line == record_number)
                    {
                        // Adding modified record
                        fprintf(temp, "\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",",
                                temp_title, temp_author, temp_publisher, temp_publication_year, temp_genre, temp_language,
                                temp_page_count, temp_availability, temp_location, temp_ratings, temp_price, temp_stock);
                        fputc('\n', temp);
                    }
                }
                fclose(file);
                fclose(temp);
                printf("\nBook record modified successfully!!\n\n");

                remove("book_records.txt");
                rename("temp_book_records.txt", "book_records.txt");
                goto end;
            }
        }
    }
    if (!found)
    {
        printf("Book Record not found\n\n");
    }
end:
    printf("\n\n");
}

// Function to change the Password
void change_password()
{
    int line;
    FILE *file = fopen("admin.txt", "r");
    FILE *temp = fopen("temp_admin.txt", "w");
    char buffer[MID_SIZE];

    // Error handling
    if (file == NULL || temp == NULL)
    {
        printf("Error changing password...\n");
        exit(0);
    }

    fgets(buffer, MID_SIZE, file);
    buffer[strlen(buffer)] = '\0';
    fputs(buffer, temp);
    fgets(buffer,MID_SIZE, file);
    buffer[strlen(buffer)] = '\0';
    fputs(buffer, temp);
    fgets(buffer, MID_SIZE, file);
    buffer[strlen(buffer) - 1] = '\0';

    char new_pass[MID_SIZE];
    char old_pass[MID_SIZE];
    while (true)
    {
        printf("\nEnter current password: ");
        scanf(" %s", &old_pass);
        printf("\nEnter new password: ");
        scanf(" %s", &new_pass);

        // Verfication
        if (strcmp(old_pass, buffer) == 0 && strcmp(new_pass, buffer) != 0)
        {
            fputs(new_pass, temp);
            fputc('\n', temp);
            fputc('\n', temp);
            fputs("__________________________  PASSWORD  __________________________", temp);

            line = get_console_line_number();
            boxer("Enter new password: ", new_pass, line);
            printf("\n\n");
            printf("Password changed successfully!!\n\n");
            break;
        }
        else if (strcmp(old_pass, buffer) != 0)
        {
            line = get_console_line_number();
            clear_screen(line - 2, 0, line - 2, 1000);
            printf("Enter correct current password!!\n");
        }
        else
        {
            line = get_console_line_number();
            clear_screen(line - 2, 0, line - 2, 1000);
            printf("New password can't be the same as old...\n");
        }
    }
    fclose(file);
    fclose(temp);
    remove("admin.txt");
    rename("temp_admin.txt", "admin.txt");
}

// Line adder
void liner()
{
    for (int i = 0; i < 200; i++)
    {
        printf("-");
    }
    printf("\n\n");
}

// Function to determin console screen line number
int get_console_line_number()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if (GetConsoleScreenBufferInfo(hConsole, &csbi))
    {
        return csbi.dwCursorPosition.Y;
    }

    return -1; // Error occurred
}

// Function to clear a specified part of the console screen
void clear_screen(int start_row, int start_col, int end_row, int end_col)
{
    // Move the cursor to the top-left position of the area to be cleared
    printf("\033[%d;%dH", start_row, start_col);

    // Clear the specified area
    for (int i = start_row; i <= end_row; i++)
    {
        for (int j = start_col; j <= end_col; j++)
        {
            printf(" ");
        }
        printf("\n");
    }

    // Move the cursor back to the original position
    printf("\033[%d;%dH", start_row, start_col);
}

// Function to create box around specified objects
void boxer(char *pre, char *per, int line)
{

    clear_screen(line, 0, line, strlen(pre));
    for (int i = 0; i < strlen(pre) + 1; i++)
    {
        printf(" ");
    }
    for (int i = 0; i < strlen(per) + 2; i++)
    {
        printf("-");
    }
    printf("\n");
    printf("%s| %s |\n", pre, per);
    for (int i = 0; i < strlen(pre) + 1; i++)
    {
        printf(" ");
    }
    for (int i = 0; i < strlen(per) + 2; i++)
    {
        printf("-");
    }
    printf("\n");
}
