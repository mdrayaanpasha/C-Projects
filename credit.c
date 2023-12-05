#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int id;
    char Costumer[20];
    int balance;
    struct Node *next;
} costumerAccount;

costumerAccount *newCostumer(costumerAccount *s) {
    char name[25];
    int choice;
    printf("What is the name of the customer: ");
    scanf("%s", name);
    costumerAccount *n = (costumerAccount*)malloc(sizeof(costumerAccount));
    n->id = s->id++;
    strcpy(n->Costumer, name);
    n->balance = 0;
    printf("If giving credit, press 1, else to quit press any number: ");
    scanf("%d", &choice);
    if (choice == 1) {
        printf("How much: ");
        scanf("%d", &n->balance);
    } else {
        printf("Great\n");
    }
    s->next = n;
    return n;
}

int searchcostumers(costumerAccount *n, int id){
  if(n==NULL){
    printf("no users present in the Database\n");
  }
  int find;
  while(n->next!=NULL){
    if (n->id==id){
      printf("%d id is of: %s & there balance is: %d", id,n->Costumer, n->balance);
      find=1;
      return find;
      break;
      }else{
      n=n->next;
    }
  }
  
  if(!find){
    printf("didnt found the costumer!");
  }
  return 0;
}

costumerAccount *addbalance(costumerAccount *n, int id){
  if(!searchcostumers(n,id)){
    int action;
    printf("no costumers found!\n");
    printf("if create new costumers press 1 else to exit press 2\n");
    scanf("%d",&action);
    if(action==1){
      return newCostumer(n);
    }else{
      int Balance;
      printf("how much do u want to add: ");
      scanf("%d",&Balance);
      n->balance=n->balance+=Balance;
      printf("added successfully!");
    }
  }
  
}

costumerAccount *Removebalance(costumerAccount *n, int id){
  if(!searchcostumers(n,id)){
    int action;
    printf("no costumers found!\n");
    printf("if create new costumers press 1 else to exit press 2\n");
    scanf("%d",&action);
    if(action==1){
      return newCostumer(n);
    }else{
      int Balance;
      printf("how much do u want to remove: ");
      scanf("%d",&Balance);
      n->balance=n->balance-=Balance;
      printf("removed successfully!");
    }
  }
  
}

int main() {
    costumerAccount *n = (costumerAccount*)malloc(sizeof(costumerAccount));
    strcpy(n->Costumer, "rayaan pasha");
    n->id = 1;
    n->balance = 0;
    n->next = NULL;

    int option;
    printf("How are you doing!\n");
    while (1) {
        printf("--Options--\n -> To Search For Credit Balance Of Customers Press '1'\n -> To Add Credit To Customer Account Press '2'\n -> To Remove Balance From Customer's Account Press '3'\n -> To Exit Press '4'\n");
        scanf("%d", &option);
        int tempid;
        printf("What is the id of the customer?\n ");
        scanf("%d", &tempid);
        if (option == 1) {
            searchcostumers(n, tempid);
        } else if (option == 2) {
            addbalance(n, tempid);
        } else if (option == 3) {
            Removebalance(n, tempid);
        } else if (option == 4) {
            free(n);  
            break;
        } else {
            printf("Sorry, we don't have that option!\n\n");
        }
    }

    return 0;
}
