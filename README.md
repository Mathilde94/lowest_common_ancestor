Be the following tree on the image.

Let's compute the Lowest Common ancestor of all the couples in tests.txt.


For this, we will need a Class Tree to :

     - write the tree, 

     - determine the Euler Tour of it, 

     - take the node with the lowest level appearing in the path between the 2 numbers of a couple.

To determine the higher node, we can do it linearly (but too long), or preparing a heap (RMQ method), and then make a query for every couple.

To execute test the program: 
   - g++ lca.cpp -o lca
   - ./lca < input.txt 
   - Output of the program: 
        A      B    Ancestor
        11     4    5  
        8      15   10
        21     15   1
        8      7    10
        4      15   10   
        3      8    5
        11     8    5
        11     0    10
        5      0    10
        10     21   10

