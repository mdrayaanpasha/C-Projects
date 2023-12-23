/**
 * @file graph_automater.c
 * @brief A program to create a graph using an adjacency matrix.
 *
 * This program allows the user to input nodes and create connections in a graph
 * represented as an adjacency matrix. The user can add nodes in sequence and
 * specify connections to other nodes in the graph.
 *
 * @author [Mohammed Rayaan Pasha]
 * @date [23/12/2023]
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Connects a node in the graph to specified nodes.
 * 
 * This function takes an adjacency matrix 'a', a node 'num', and an array 'arr'
 * representing nodes to which 'num' should be connected. It sets the corresponding
 * elements in the matrix to 1, indicating the connection.
 *
 * @param a The graph represented as an adjacency matrix.
 * @param num The node to connect.
 * @param arr An array of nodes to connect to 'num'.
 * 
 * @return void
 */
void connectNodes(int a[][100], int num, int arr[]) {
    for (int i = 0; i < 100; i++) {
        // Connect 'num' to the nodes specified in 'arr'
        if (i == num) {
            a[num][i] = 1;
        }
    }
}

/**
 * @brief Main function to execute the graph creation program.
 * 
 * Initializes a graph represented as an adjacency matrix and allows the user
 * to add nodes and create connections.
 * 
 * @return 0 upon successful execution.
 */
int main() {
    int a[100][100];

    // Initialize the graph with zeros
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            a[i][j] = 0;
        }
    }

    char dec;
    printf("Press 'q' to add nodes and connections to the graph: ");
    scanf(" %c", &dec); // Notice the space before %c to consume the newline character

    if (dec == 'q') {
        int arr[100];
        int num;

        printf("Enter the initial node: ");
        scanf("%d", &num);
        printf("Initial node added successfully.\n");

        printf("Keep inserting nodes to connect, if you're done, insert 101: ");
        int nodeToAdd;
        for (int k = 0; k < 100; k++) {
            scanf("%d", &nodeToAdd);
            if (nodeToAdd == 101) {
                break;
            }
            if (nodeToAdd != 101) {
                arr[k] = nodeToAdd;
            }
        }

        // Connect the initial node to specified nodes
        connectNodes(a, num, arr);
    }

   

    return 0;
}
