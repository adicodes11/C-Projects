/*******************************************************************************
 *
 * Mini Mini Project: Automated Receipt Generator
 *
 * Description: Just a learning step towards the working of an automated receipt generator
 *
 * By: Aditya Chikte
 *
 * Github: @adicodes11
 *
 *******************************************************************************/

#include <stdio.h>
#include <string.h>

void print_receipt(char *shop_name, char *address, char *mobile, char item[100][100], double price[], int quantity[], int count, double amount[], double total, double tax, char *transaction_id)
{
    // Display format
    printf("\n\n");
    printf("|%60s|\n", " ");
    printf("%25s%s\n", " ", "CASH RECEIPT");
    printf("%28s%s\n\n", " ", "*****");
    printf("%27s%s\n", " ", shop_name);
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
}

void new_receipt(char item[100][100], double price[], int quantity[], int *count, double amount[], double *total, double tax)
{
    int i = 0;
    int stop;
    while (stop != 0)
    {
        (*count)++;
        fflush(stdin);
        printf("Enter item: ");
        fgets(item[i], 100, stdin);
        item[i][strlen(item[i]) - 1] = '\0';
        printf("Enter price: ");
        scanf("%lf", &price[i]);
        printf("Enter quantity: ");
        scanf("%d", &quantity[i]);
        amount[i] = price[i] * quantity[i];
        (*total) += amount[i];
        i++;

        printf("Press 0 to stop:");
        scanf(" %d", &stop);
        printf("\n");
    }
}

int main()
{
    char shop_name[100] = "Walmart";
    char address[200] = "22 Main Streets, Big City 00087";
    char mobile[11] = "8385919201";

    char item[100][100];
    double price[100];
    int quantity[100];
    int count = 0;
    double amount[100];
    double total = 0;
    double tax = 18;
    char transaction_id[20];

    char to_new;
    printf("Press N for new: ");
    scanf(" %c", &to_new);
    if (to_new == 'N' || to_new == 'n')
    {
        new_receipt(item, price, quantity, &count, amount, &total, tax);
    }
    char to_print;
    printf("Press P to print receipt: ");
    scanf(" %c", &to_print);
    if (to_print == 'p' || to_print == 'P')
    {
        print_receipt(shop_name, address, mobile, item, price, quantity, count, amount, total, tax, transaction_id);
    }

    return 0;
}
