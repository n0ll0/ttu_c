#include <stdio.h>

typedef enum
{
    false,
    true
} bool;

struct productMultipliers
{
    float pricePerKilo;
    char* name;
};

struct productMultipliers ProductArr[9] = {
    {1.50f, "Banana"},
    {2.00f, "Orange"},
    {2.00f, "Apple"},
    {2.50f, "Pear"},
    {3.00f, "Plum"},
    {2.50f, "Lemon"},
    {1.49f, "Tomato"},
    {1.20f, "Cucumber"},
    {0.99f, "Potato"},
};

void printCategory(int i, bool usePrefix)
{
    switch (i)
    {
    case 0:
        if (usePrefix)
        {
            printf("1 - Fruits: \n");
        }
        else
        {
            printf("Fruits: \n");
        }
        break;
    case 1:
        if (usePrefix)
        {
            printf("2 - Other: \n");
        }
        else
        {
            printf("Other: \n");
        }
        break;
    case 2:
        if (usePrefix)
        {
            printf("3 - Vegetables: \n");
        }
        else
        {
            printf("Vegetables: \n");
        }
    default:
        break;
    }
}

void printProductsInCategory(int cat, bool usePrefix)
{
    for (int j = 0; j < 3; j++)
    {
        if (usePrefix)
        {
            printf("\t%d\t-\t%s\n", j + 1, ProductArr[cat * 3 + j].name);
        }
        else
        {
            printf("\t%s,", ProductArr[cat * 3 + j].name);
        }
    }
    printf("\n");
}

bool printError(bool erroryExpression)
{
    if (erroryExpression) {
        printf("\nError!\n");
        while (getchar() != '\n');
    }
    return erroryExpression;
};

int main(void)
{
    // Variable declarations (INCOMPLETE!)
    float weight;
    int productCode;
    int category;

    // List all available products (INCOMPLETE!)
    printf("Available products\n");

    // Read in product code
    do
    {
        for (int i = 0; i < 3; i++)
        {
            printCategory(i, true);
            printProductsInCategory(i, false);
        }
        printf("Enter category number: ");
    } while (printError((scanf("%d", &category) != 1) || (category < 1 || category > 3)));
    category--;

    do
    {
        printCategory(category, false);
        printProductsInCategory(category, true);
        printf("Enter product number: ");
    } while (printError((scanf("%d", &productCode) != 1) || (productCode < 1 || productCode > 3)));
    productCode += category * 3 - 1;

    // Read in product weight (FIX THE MISTAKE!)
    do
    {
        // if (weight <= 0)
        //     printf("Asetage toode kaalule!\n");
        printf("Enter weight: ");
    } while (printError((scanf("%f", &weight) != 1) || (weight <= 0)));

    // Calculate the total cost
    float pricePerKilo = ProductArr[productCode].pricePerKilo;
    float totalPrice = pricePerKilo * weight;

    // Output the label information (INCOMPLETE - only when no errors occurred!)
    printf("\nProduct number %d [%s] - ", productCode, ProductArr[productCode].name);
    printf("Price per kilo %.2f EUR\n", pricePerKilo);
    printf("Total price: %.2f EUR\n", totalPrice);

    return 0;
}
