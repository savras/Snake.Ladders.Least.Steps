# Snake.Ladders.Least.Steps
This problem requires us to find the least number of steps we can make to reach square 100.

##Overview
This is my solution for the Quickest Way Up<sup> [1] (https://www.hackerrank.com/challenges/the-quickest-way-up)</sup> HackerRank question. Been a really long time since I did questions on Graph Theory so this took me a while to finish.

The solution to the question was to figure out how each square on the board can be represented as a graph, and how they are linked to the other squares. Theory of Programming<sup> [2] (http://theoryofprogramming.com/2014/12/25/snakes-and-ladders-game-code)</sup> shows us how this is done. :thumbsup:

Once that relationship has been established, Breadth First Search (BFS), which guarantees the shortest path to a destination node <sup> [3] (https://www.topcoder.com/community/data-science/data-science-tutorials/introduction-to-graphs-and-their-data-structures-section-2/)</sup>, will easily find the quickest path to square 100. This is because BFS explores all neighbouring nodes first therefore the first destination node you encounter is the shortest path.

## Sample Input
2

3

32 62

42 68

12 98

7

95 13

97 25

93 37

79 27

75 19

49 47

67 17

4

8 52

6 80

26 42

2 72

9

51 19

39 11

37 29

81 3

59 5

79 23

53 7

43 33

77 21 

## Sample Output
3

5

## References
1. [Quickest Way Up] (https://www.hackerrank.com/challenges/the-quickest-way-up)
2. [Theory of Programming] (http://theoryofprogramming.com/2014/12/25/snakes-and-ladders-game-code)
3. [TopCoder Graph Tutorial] (https://www.topcoder.com/community/data-science/data-science-tutorials/introduction-to-graphs-and-their-data-structures-section-2/)
