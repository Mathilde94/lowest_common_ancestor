Be the following tree:
        10 
       /  \
      5    1
    / | \  | \
   3  8  4 7  15
  /|    /  |\
11 9   2  21 0

Let's compute the Lowest Common ancestor of all the following couples: 
11 4
8 15
21 15
8 7
4 15
3 8
11 8
11 0
5 0
10 21

For this, we will need a Class Tree to :
    - write the tree, 
    - determine the Euler Tour of it, 
    - take the node with the lowest level appearing in the path between the 2 numbers of a couple.

   To determine the higher node, we can do it linearly (but too long), or preparing a heap (RMQ method), and then make a query for every couple.

