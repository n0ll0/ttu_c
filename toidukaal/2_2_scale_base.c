#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../input.c"

// typedef enum
// {
//     false,
//     true
// } bool;

struct productMultipliers
{
    float pricePerKilo;
    char *name;
};

// struct productMultipliers ProductArr[9] = {
//     {1.50f, "Banana"  },
//     {2.00f, "Orange"  },
//     {2.00f, "Apple"   },
//     {2.50f, "Pear"    },
//     {3.00f, "Plum"    },
//     {2.50f, "Lemon"   },
//     {1.49f, "Tomato"  },
//     {1.20f, "Cucumber"},
//     {0.99f, "Potato"  },
// };

void printCategory(int i, int usePrefix)
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

void printProductsInCategory(int cat, int usePrefix, struct productMultipliers *ProductArr)
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

void askForCategoryNumber()
{
    printf("Enter category number: ");
}

void askForProductCode()
{
    printf("Enter product number: ");
}

void askForWeight()
{
    printf("Enter weight: ");
}

int isGoodInput(int cat)
{
    return cat > 0 && cat < 4;
}

int isPositive(float n)
{
    return n > 0;
}

void populateProducts(struct productMultipliers *ProductArr)
{
    ProductArr[0] = (struct productMultipliers){1.50f, "Banana"};
    ProductArr[1] = (struct productMultipliers){2.00f, "Orange"};
    ProductArr[2] = (struct productMultipliers){2.00f, "Apple"};
    ProductArr[3] = (struct productMultipliers){2.50f, "Pear"};
    ProductArr[4] = (struct productMultipliers){3.00f, "Plum"};
    ProductArr[5] = (struct productMultipliers){2.50f, "Lemon"};
    ProductArr[6] = (struct productMultipliers){1.49f, "Tomato"};
    ProductArr[7] = (struct productMultipliers){1.20f, "Cucumber"};
    ProductArr[8] = (struct productMultipliers){0.99f, "Potato"};
}

int main(void)
{
    float weight;
    int productCode;
    int category;

    // Heap allocation of ProductArr
    struct productMultipliers *ProductArr = malloc(9 * sizeof(struct productMultipliers));
    if (ProductArr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    populateProducts(ProductArr);

    // List all available products (INCOMPLETE!)
    printf("Available products\n");

    for (int i = 0; i < 3; i++)
    {
        printCategory(i, true);
        printProductsInCategory(i, false, ProductArr);
    }

    // Read in product code
    category = read_int(askForCategoryNumber, isGoodInput) - 1;
    printf("%d\n",category);

    printCategory(category, false);
    printProductsInCategory(category, true, ProductArr);

    productCode = read_int(askForProductCode, isGoodInput);
    productCode += category * 3 - 1;

    // Read in product weight (FIX THE MISTAKE!)
    weight = read_float(askForWeight, isPositive);

    // Calculate the total cost
    float pricePerKilo = ProductArr[productCode].pricePerKilo;
    float totalPrice = pricePerKilo * weight;

    // Output the label information (INCOMPLETE - only when no errors occurred!)
    printf("\nProduct number %d [%s] - ", productCode, ProductArr[productCode].name);
    printf("Price per kilo %.2f EUR\n", pricePerKilo);
    printf("Total price: %.2f EUR\n", totalPrice);
    
    free(ProductArr);

    return 0;
}
