/* Ref: http://theoryofprogramming.com/2014/12/25/snakes-and-ladders-game-code/ */

#include <cmath>
#include <climits>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_set>
using namespace std;

struct Node {
    int value;
    struct Node *next;
};


/*
 * Replaces the value of a node
 */
void Replace(struct Node *adjList[], int oldValue, int newValue) {
    struct Node *traverse = NULL;
    
    int startRow = 0;
    for(int i = 1; i <= 6; i++)
    {
        startRow = oldValue - i; // Start before the current row
        if(startRow >= 1 && startRow < 100)  // Ladders start from vertex 2 and snakes are before 100
        {
            traverse = adjList[startRow];
            
            while(traverse != NULL)
            {               
                if(traverse->value == oldValue)
                {   
                    traverse->value = newValue;
                    break;
                }
                traverse = traverse->next;
            }
        }
        else
        {
            break;
        }
    }
}

/*
 * Build the list backwards. Created node is always head.
 */
Node * Add(struct Node *head, int vertex) {
    struct Node *node = (struct Node *) malloc(sizeof(struct Node));
    
    node->value = vertex;
    node->next = head;
    
    return node;
}

/*
 * Print adjacency list
 */
void TraverseAndPrint(struct Node *head) {
    struct Node *traverse = head;
    
    while(traverse != NULL) {
        cout << traverse->value << " -> ";
        traverse = traverse->next;
    }
    
    cout << "NULL";
}

/*
 * The level at which the destination node is found is the number of die rolls needed.
 * We take the earliest level of a node when it was visited because that will be the shortest path for its path.
 */
void Bfs(struct Node *adjList[], int parent[], int level[], int vertices)
{
    struct Node *temp = NULL;    
    vector<int> queue;    
    unordered_set<int> visited;    
    int levelCount = 0; // Tracks the current level in a BFS search
    int lowestLevel = INT_MAX;  // Tracks the lowest level of a BFS finding vertex 100
    
    // Get the number of items in the first level.
    int itemsInLevel = 0;
    temp = adjList[1];
    
    while(temp != NULL)
    {        
        temp = temp->next;        
        itemsInLevel++;
    }    
    //cout << "Items in level: " << itemsInLevel << endl;
    
    queue.push_back(1); // Starting vertex

    while(queue.size() > 0)
    {        
        //cout << "Queue size " << queue.size() << endl;
        int poppedValue = queue[0];
        queue.erase(queue.begin());
        visited.insert(poppedValue);
        //cout << "Processing vertex no " << poppedValue << endl;
        itemsInLevel--;

        if(poppedValue == 100)
        {
            lowestLevel = levelCount;
            break;
        }
        
        // Queue each neighbour
        temp = adjList[poppedValue];
        //cout << "Going to queue neighbours, starting with vertex " << temp->value << endl;
        while(temp != NULL)
        {
            //cout << "Visiting vertex no " << temp->value << endl;
            if(visited.find(temp->value) == visited.end())  // Not yet visited
            {
                queue.push_back(temp->value);                
            }
            temp = temp->next;
        }
        
        if(itemsInLevel == 0)
        {
            itemsInLevel = queue.size();
            levelCount++;
        }
    }
    
    if(lowestLevel == INT_MAX)
    {
        cout << -1 << endl;
    }
    else
    {
        cout << lowestLevel  + 1 << endl;   // Add 1 because we are breaking out as soon as we hit 100, so 
        // we havent added the level from the logic further down: if(itemsInLevel == 0) { // Add Level }
    }
}

void PrintAdjList(struct Node *head[], int vertices) {
    for(int i = 1; i <= vertices; i++) {
        cout << i << ": ";
        TraverseAndPrint(head[i]);
        cout << endl;
    }
}

int main() {
    // I/O
    int T, l, s;
    cin >> T;
    
    // Initialize
    const int vertices = 100;
    int parent[vertices + 1] = {0};
    int level[vertices + 1] = {0};
    
    int edges = 0;
    struct Node *adjList[vertices + 1]; // So that we can map the board without worrying about array offset
    
    while(T--) {
        for(int i = 1; i <= vertices; i++) {
            adjList[i] = NULL;
        }

        // Build adj list
        for(int i = 1; i <= vertices; i++) {
            level[i] = -1;
            for(int p = 1; (p <= 6) && ((i + p) <= vertices); p++)
            {                
                adjList[i] = Add(adjList[i], i + p);
                edges++;
            }
        }

        // Account for ladders
        cin >> l;
        int lstart, ldest;  // Ladder start and destination
        while(l--) {
            cin >> lstart >> ldest;            
            Replace(adjList, lstart, ldest);
        }
        
        // Account for snakes
        cin >> s;
        int sstart, sdest;  // Snake start and destination
        while(s--) {
            cin >> sstart >> sdest;
            Replace(adjList, sstart, sdest);
        }
        
        Bfs(adjList, parent, level, vertices);
        
        //PrintAdjList(adjList, vertices);
    }    
    
    return 0;
}