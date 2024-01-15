#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct item {
    char assetName[20][50];
    int amount[50];
    int size, top;
} Item;

int isFull(Item *s) {
    return s->top == s->size;
}

int isEmpty(Item *s) {
    return s->top < 0;
}

void insertItems(Item *a) {
    if (isFull(a)) {
        printf("You reached the maximum level of assets!\n");
    } else {
        char des = 'y';
        while (des == 'y') {
            printf("What's the name of the asset: \n");
            scanf("%s", a->assetName[a->top]);
            printf("What's the amount of the asset: \n");
            scanf("%d", &a->amount[a->top]);
            a->top++;
            printf("Do you want to insert another element? (y/n)\n");
            scanf(" %c", &des);
            if (!isFull(a)) {
                continue;
            } else {
                printf("You reached the maximum limit of having assets\n");
                break;
            }
        }
    }
}

void report_item(Item *Asset, int Asset_Deprication[]) {
    for (int i = 0; i <= Asset->top; i++) {
        printf("%d %s", i, Asset->assetName[i]);
    }

    for (int i = 0; i <= Asset->top; i++) {
        Asset_Deprication[i] = 0;
    }

    int in, percentage;
    char desc = 'c';
    while (desc == 'c') {
        printf("Enter the index of the item that got depreciated/appreciated!\n");
        scanf("%d", &in);
        printf("How much percentage was it: ");
        scanf("%d", &percentage);
        int depreciation = (Asset->amount[in]) * percentage / 100;
        Asset_Deprication[in] = depreciation;
        printf("Is there any other item that you'd like to account for? (y/n) \n");
        scanf(" %c", &desc);
    }
}

void finalReport(Item A, Item L, int AA[], int AD[], int LA[], int LD[]) {
    int A_appreciationTotal = 0;
    for (int i = 0; i < A.top; i++) {
        A_appreciationTotal += A_appreciationTotal + AA[i];
    }
    int A_depreciationTotal = 0;
    for (int i = 0; i <= A.top; i++) {
        A_depreciationTotal += A_depreciationTotal + AD[i];
    }

    int totalAssets = A_appreciationTotal - A_depreciationTotal;

    // The below is for calculating aggregate liabilities
    int L_appreciationTotal = 0;
    for (int k = 0; k < L.top; k++) {
        L_appreciationTotal += L_appreciationTotal + LA[k];
    }
    int L_depreciationTotal = 0;
    for (int i = 0; i <= A.top; i++) {
        L_depreciationTotal += L_depreciationTotal + LD[i];
    }

    int totalLiability = L_appreciationTotal - L_depreciationTotal;

    int netProfit = totalAssets - totalLiability;

    if (netProfit > 0) {
        printf("Congratulations! You had a profit of rupees: %d\n", netProfit);
    } else {
        printf("You had a Net Loss of rupees %d\n", netProfit);
    }
}

int main() {
    Item *Assets = (Item *)malloc(sizeof(Item));
    Item *Liabilities = (Item *)malloc(sizeof(Item));

    char assetsAvailable, liabilityAvailable, depreciation_assets, appreciation_assets, depreciation_liabilities, appreciation_liabilities;

    printf("Hello there, welcome!\n");

    while (1) {
        printf("If you have assets, press 'y' else 'n': ");
        scanf(" %c", &assetsAvailable);

        if (assetsAvailable == 'y') {
            insertItems(Assets);
        } else {
            continue;
        }

        printf("If you have Liabilities, press 'y' else 'n': ");
        scanf(" %c", &liabilityAvailable);

        if (liabilityAvailable == 'y') {
            insertItems(Liabilities);
        } else {
            continue;
        }

        if (isEmpty(Liabilities) && isEmpty(Assets)) {
            printf("This application isn't suitable for your firm. BYE!!! :)\n");
        } else {
            printf("Was there any depreciation in assets? (y/n): ");
            scanf(" %c", &depreciation_assets);

            if (depreciation_assets == 'y') {
                int Asset_Deprication[50];  // You can adjust the size as needed
                report_item(Assets, Asset_Deprication);
            } else {
                printf("Cool...\n");
                continue;
            }

            printf("Was there any appreciation in Assets? (y/n): ");
            scanf(" %c", &appreciation_assets);

            if (appreciation_assets == 'y') {
                int Asset_Apprecition[50];  // You can adjust the size as needed
                report_item(Assets, Asset_Apprecition);
            } else {
                printf("Cool...\n");
            }

            printf("Was there any depreciation in liabilities? (y/n): ");
            scanf(" %c", &depreciation_liabilities);

            if (depreciation_liabilities == 'y') {
                int Depricitation_Liabilities[50];  // You can adjust the size as needed
                report_item(Liabilities, Depricitation_Liabilities);
            } else {
                printf("Cool...\n");
            }

            printf("Was there any appreciation in liabilities? (y/n): ");
            scanf(" %c", &appreciation_liabilities);

            if (appreciation_liabilities == 'y') {
                int Appreciation_Liabilities[50];  // You can adjust the size as needed
                report_item(Liabilities, Appreciation_Liabilities);
            } else {
                printf("Cool...\n");
            }

            finalReport(*Assets, *Liabilities, Asset_Apprecition, Asset_Deprication, Depricitation_Liabilities, Appreciation_Liabilities);
            break;
        }
    }

    free(Assets);
    free(Liabilities);

    return 0;
}
