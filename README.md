Be the following tree on the image.

Let's compute the Lowest Common ancestor of all the couples in tests.txt.


For this, we will need a Class Tree to :

     - write the tree, 

     - determine the Euler Tour of it, 

     - take the node with the lowest level appearing in the path between the 2 numbers of a couple.

To determine the higher node, we can do it linearly (but too long), or preparing a heap (RMQ method), and then make a query for every couple.

