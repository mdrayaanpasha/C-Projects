/**
 * @file KnapWiz.c
 * @brief A program designed to tackle the 0/1 knapsack problem efficiently through dynamic programming.
 */

#include<stdio.h>
#include<string.h>

/**
 * @struct Item
 * @brief Represents an item with its name, value, and weight.
 */
typedef struct Item {
    int weight; /**< The weight of the item. */
    int value; /**< The value of the item. */
    char name[50]; /**< The name of the item. */
} Item;

/**
 * @brief Determines the maximum of two integers.
 * @param a The first integer.
 * @param b The second integer.
 * @return The greater of the two integers.
 */
int max(int a, int b) {
    return (a > b) ? a : b;
}

/**
 * @brief Resolves the knapsack problem via dynamic programming.
 * @param items[] An array of Item structures representing the items available.
 * @param capacity The capacity of the knapsack.
 * @param n The total number of items.
 */
void getbest(Item items[], int capacity, int n) {
    int matrix[n][capacity + 1];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= capacity; j++) {
            if (j == 0 || i == 0) {
                matrix[i][j] = 0;
            } else if (items[i - 1].weight <= j) {
                matrix[i][j] = max(items[i - 1].value + matrix[i - 1][j - items[i - 1].weight], matrix[i - 1][j]);
            } else {
                matrix[i][j] = matrix[i - 1][j];
            }
        }
    }
    int i = n;
    int j = capacity;
    int totalValue = 0;
    while (i > 0 && j > 0) {
        if (matrix[i][j] != matrix[i - 1][j]) {
            printf("%s is included with a value of: %d\n", items[i - 1].name, items[i - 1].value);
            totalValue += items[i - 1].value;
            j -= items[i - 1].weight;
        }
        i--;
    }
    printf("Hence, the maximum value achievable with your items is: %d", totalValue);
}

/**
 * @brief The main function orchestrating the knapsack algorithm.
 * @details It prompts the user to input information regarding each item, including its name, value, and weight.
 * Subsequently, it requests the capacity of the knapsack from the user.
 * Finally, it invokes the getbest function to compute the optimal item combination.
 * @return 0 upon successful execution.
 */
int main() {
    int n;
    printf("Greetings! Welcome to Knap Wiz.\nHow many items do you possess? \n");
    scanf("%d", &n);
    Item items[n];
    for (int i = 0; i < n; i++) {
        printf("Kindly provide the name of item %d: ", i + 1);
        scanf("%s", items[i].name);
        printf("What is the value associated with %s: ", items[i].name);
        scanf("%d", &items[i].value);
        printf("Excellent! Could you specify the weight of %s: ", items[i].name);
        scanf("%d", &items[i].weight);
    }
    int capacity;
    printf("What is the capacity of your knapsack: ");
    scanf("%d", &capacity);
    
    getbest(items, capacity, n);
    return 0;
}
