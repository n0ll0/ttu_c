#include <stdio.h>

struct productMultipliers {
    char* name;
    float pricePerKilo;
};

struct productMultipliers ProductArr[10] = {
    {"",0.0f},
    {"Banana",1.50f},
    {"Orange",2.00f},
    {"Lemon",2.50f},
    {"Tomato",1.49f},
    {"Cucumber",1.20f},
    {"Potato",0.99f},
    {"Apple",2.00f},
    {"Pear",2.50f},
    {"Plum",3.00f},
};

int main(void)
{
    // Variable declarations (INCOMPLETE!)
    float weight;
    float totalPrice;
    int productCode;

    // List all available products (INCOMPLETE!)
    printf("Available products\n");

    printf("1 - Banana      2 - Orange      3 - Lemon      \
4 - Tomato      5 - Cucumber    6 - Potato     \
7 - Apple       8 - Pear        9 - Plum   \n");

    // Read in product code (TODO!)
    printf("Enter product code: ");
    if (scanf("%d", &productCode) != 1)
    {
        printf("Error!\n");
        return 1;
    }
    if (productCode < 1 || productCode > 9)
    {
        printf("Error!\n");
        return 1;
    }

    // Read in product weight (FIX THE MISTAKE!)
    printf("Enter weight: ");
    if (scanf("%f", &weight) != 1)
    {
        printf("Error!\n");
        return 1;
    }
    if (weight <= 0)
    {
        printf("Please place the product onto the scale!\n");
        return 1;
    }

    // Calculate the total cost
    float pricePerKilo = ProductArr[productCode].pricePerKilo;
    totalPrice = pricePerKilo * weight;

    // Output the label information (INCOMPLETE - only when no errors occurred!)
    printf("Product number %d - ", productCode);
    printf("Price per kilo %.2f EUR\n", pricePerKilo);
    printf("Total price: %.2f EUR\n", totalPrice);

    return 0;
}
