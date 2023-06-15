/*******************************************************************************
 *
 * Mini Project: Google Forms Interpretation
 *
 * Description: Just a learning step towards google forms and their basics.
 *
 * By: Aditya Chikte
 *
 * Github: @adicodes11
 *
 *******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>

#define short_ans 20
#define mid_ans 100
#define long_ans 1024

// Function Declarations
void barplot(int score, int question_count, FILE *fptr);
void clear_screen(int start_row, int start_col, int end_row, int end_col);
int get_console_line_number();
void boxer(char *pre, char *per, int line, FILE *fptr);
void boxer1(char *pre, char per, int line, FILE *fptr);
int email_checker(char *email);

// Driver Code
int main()
{
    int valid = 0;
    int line;
    FILE *fptr = fopen("response.txt", "w");

    if (fptr == NULL)
    {
        printf("Some error occured...\n");
        exit(4);
    }

    printf("-------Welcome to Google Forms Interpretation-------\n\n");
    fprintf(fptr, "%s", "-------Welcome to Google Forms Interpretation-------\n\n");

    // New form creation
    char heading[mid_ans];
    char enter_heading[mid_ans] = "College name: ";     // heading in this case is college name:
    printf("%s", enter_heading);
    fgets(heading, mid_ans, stdin);
    heading[strlen(heading) - 1] = '\0';
    line = get_console_line_number();
    clear_screen(line, 0, line, strlen(enter_heading) + strlen(heading));
    printf("%10s%10s\n", " ", heading);
    fprintf(fptr, "%10s%10s\n", " ", heading);
    printf("%10s", " ");
    fprintf(fptr, "%10s", " ");
    for (int i = 0; i < strlen(heading); i++)
    {
        printf("-");
        fprintf(fptr, "%s", "-");
    }
    printf("\n\n");
    fprintf(fptr, "%s", "\n\n");

    // Name
    char enter_name[mid_ans] = "Name: ";
    char name[mid_ans];
    printf("%s", enter_name);
    fgets(name, mid_ans, stdin);
    name[strlen(name) - 1] = '\0';
    line = get_console_line_number();
    boxer(enter_name, name, line, fptr);

    // Email
    char enter_email[mid_ans] = "Email: ";
    char email[mid_ans]; // checks
remail:
    printf("%s", enter_email);
    scanf(" %s", &email);
    fflush(stdin);
    valid = email_checker(email);
    if (valid == 1)
    {
        line = get_console_line_number();
        boxer(enter_email, email, line, fptr);
    }
    else
    {
        printf("Enter vaild email id!!\n");
        goto remail;
    }

    // Age
    char age[short_ans]; // Taking age as string as per our function ...will typecast to integer if needed
    printf("Age: ");
    fgets(age, 4, stdin);
    age[strlen(age) - 1] = '\0';
    line = get_console_line_number();
    boxer("Age: ", age, line, fptr);

    // Department
    char enter_department[mid_ans] = "Department: ";
    char department[mid_ans];
    printf("%s", enter_department);
    fgets(department, mid_ans, stdin);
    department[strlen(department) - 1] = '\0';
    line = get_console_line_number();
    boxer(enter_department, department, line, fptr);

    // Semester
    char sem[short_ans];
    printf("SEM: ");
    fgets(sem, short_ans, stdin);
    sem[strlen(sem) - 1] = '\0';
    line = get_console_line_number();
    boxer("SEM: ", sem, line, fptr);

    printf("QUESTIONS: \n\n");
    fprintf(fptr, "%s", "QUESTIONS: \n\n");
    // Form Questions
    // File used for questions: questions.txt
    int question_count = 0;
    line = 0;
    int score = 0;
    char answer;
    char buffer[long_ans];
    FILE *file = fopen("questions.txt", "r");
    if (file == NULL)
    {
        printf("Error viewing questions...\n");
        return 1;
    }
    while (!feof(file))
    {
        line++;
        if (ferror(file))
        {
            printf("Error viewing questions...\n");
            return 1;
        }
        fgets(buffer, long_ans, file);
        buffer[strlen(buffer) - 1] = '\0';
        if (line != 6)
        {
            puts(buffer);
            fprintf(fptr, "%s\n", buffer);
        }
        if (line == 6)
        {
            printf("Enter your response: ");
            scanf(" %c", &answer);
            if (answer != buffer[0])
            {

                fprintf(fptr, "%s", "Enter your response: ");
                fprintf(fptr, "%c\n", answer);
            }
            if (answer == buffer[0])
            {
                line = get_console_line_number();
                boxer1("Enter your response: ", answer, line, fptr);
                score += 10;
            }
            question_count++;
            line = -1;
        }
    }
    fclose(file);

    printf("Score: %d/%d\n", score, question_count * 10);
    fprintf(fptr, "Score: %d/%d\n", score, question_count * 10);

    barplot(score, question_count, fptr);

    char my_response = 'N';
    printf("Download the copy of your response (y/n): ");

    scanf(" %c", &my_response);
    if (my_response == 'y' || my_response == 'Y')
    {
        printf("Response copy downloaded successfully.\n");
        fprintf(fptr, "%13s%s\n\n", " ", "Thank You for using G-Forms");
        fprintf(fptr, "Date: %s%20sTime: %s\n", __DATE__, " ", __TIME__);
        fclose(fptr);
        system("start notepad response.txt"); // system call to open the response file
    }
    return 0;
}




// Function Definitions
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

void boxer(char *pre, char *per, int line, FILE *fptr)
{

    clear_screen(line, 0, line, strlen(pre));
    for (int i = 0; i < strlen(pre) + 1; i++)
    {
        printf(" ");
        fprintf(fptr, "%s", " ");
    }
    for (int i = 0; i < strlen(per) + 2; i++)
    {
        printf("-");
        fprintf(fptr, "%s", "-");
    }
    printf("\n");
    fprintf(fptr, "%s", "\n");
    printf("%s| %s |\n", pre, per);
    fprintf(fptr, "%s| %s |\n", pre, per);
    for (int i = 0; i < strlen(pre) + 1; i++)
    {
        printf(" ");
        fprintf(fptr, "%s", " ");
    }
    for (int i = 0; i < strlen(per) + 2; i++)
    {
        printf("-");
        fprintf(fptr, "%s", "-");
    }
    printf("\n");
    fprintf(fptr, "%s", "\n");
}

void boxer1(char *pre, char per, int line, FILE *fptr)
{

    clear_screen(line, 0, line, strlen(pre));
    for (int i = 0; i < strlen(pre) + 1; i++)
    {
        printf(" ");
        fprintf(fptr, "%s", " ");
    }
    for (int i = 0; i < 3; i++)
    {
        printf("-");
        fprintf(fptr, "%s", "-");
    }
    printf("\n");
    fprintf(fptr, "%s", "\n");
    printf("%s| %c |\n", pre, per);
    fprintf(fptr, "%s| %c |\n", pre, per);
    for (int i = 0; i < strlen(pre) + 1; i++)
    {
        printf(" ");
        fprintf(fptr, "%s", " ");
    }
    for (int i = 0; i < 3; i++)
    {
        printf("-");
        fprintf(fptr, "%s", "-");
    }
    printf("\n");
    fprintf(fptr, "%s", "\n");
}

int email_checker(char *email)
{
    strlwr(email);
    char *com = "@gmail.com";
    char *in = "@gmail.in";
    bool looks_fine = true;
    int com_len = strlen(com);
    int in_len = strlen(in);

    if (strlen(email) < strlen(com) + 4)
    {
        return 0;
    }

    for (int i = strlen(email) - 1; com_len > 0; i--)
    {
        if (email[i] != com[com_len - 1])
        {
            looks_fine = false;
            break;
        }
        com_len--;
    }
    if (looks_fine)
        return 1;

    looks_fine = true;
    for (int i = strlen(email) - 1; in_len > 0; i--)
    {
        if (email[i] != in[in_len - 1])
        {
            looks_fine = false;
            break;
        }
        in_len--;
    }
    if (looks_fine)
        return 1;

    return 0;
}

void barplot(int score, int question_count, FILE *fptr)
{
    int correct = score / 10;
    int wrong = question_count - correct;

    printf("Bar Plot analysis:\n\n");
    fprintf(fptr, "%s", "Bar Plot analysis:\n\n");

    while (correct != 0 && wrong != 0)
    {
        if (correct > wrong)
        {
            printf("%s|=| %3s\n", " ", " ");
            fprintf(fptr, "%s|=| %3s\n", " ", " ");
            correct--;
        }
        else if (wrong > correct)
        {
            printf("%s%3s |=|\n", " ", " ");
            fprintf(fptr, "%s%3s |=|\n", " ", " ");
            wrong--;
        }
        if (correct == wrong)
        {
            printf("%s|=| |=|\n", " ");
            fprintf(fptr, "%s|=| |=|\n", " ");
            correct--;
            wrong--;
        }
    }
    for (int i = 0; i < 10; i++)
    {
        printf("-");
        fprintf(fptr, "%s", "-");
    }
    printf("\n%2sC%3sW", " ", " ");
    fprintf(fptr, "\n%2sC%3sW", " ", " ");
    printf("%5sC: Correct  W: Wrong\n\n\n", " ");
    fprintf(fptr, "%5sC: Correct  W: Wrong\n\n\n", " ");
}
