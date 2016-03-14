#include <stdio.h>
#include <stdlib.h>

typedef enum {
    LessThan = 0,
    LessThanEquals = 1,
    Equals = 2,
    GreaterThanEquals = 3,
    GreaterThan = 4
} SearchType;

typedef enum {
    NotFound,
    FoundExact,
    FoundGreater,
    FoundLess
} SearchResult;

char * SearchResultStr[] = {
    "NotFound    ",
    "FoundExact  ",
    "FoundGreater",
    "FoundLess   "
};


SearchResult Search(
    const int * const items,
    const int n_items,
    const int ascending,
    const int key,
    const SearchType type,
    int* const index)
{
    int start, stop;    // indices into the array
    int delta;          // +1 to move forward ; -1 to move backwards
    int direction = 1;  // Forward or reverse
    
    *index = -1;
    
    direction = (type >= Equals) ? 1 : 0;
    
    // If descending, reverse direction
    if (!ascending)
        direction = !direction;
        
    if (direction == 1) {
        // compare from 0 to n_items-1
        delta = +1;
        start = 0;
        stop = n_items;
    } else {
        // compare from n_items-1 to 0
        delta = -1;
        start = n_items - 1;
        stop = -1;
    }
        
    // Loop until found or end of array is reached
    do {
        // 3 possibilites (==  <  >)
        if (items[start] == key) {
            // check if type has equals comparison
            if (! ((type == LessThan) || (type == GreaterThan)) ) {
                *index = start;
                return FoundExact;
            }
        } else if (items[start] < key) {
            if ((type == LessThan) || (type == LessThanEquals)){
                *index = start;
                return FoundLess;
            }
        } else {
            if ((type == GreaterThan) || (type == GreaterThanEquals)) {
                *index = start;
                return FoundGreater;
            }
        }
        start += delta;
    } while (start != stop);
       
    return NotFound;
}


int main(int argc, char *argv[])
{
    int *a;
    int i, idx, count, key, ascending=1;
    SearchResult res;
    
    // Usage: ./compare <key> <list of integers>
    // Eg:    ./compare 12  4 8 9 12 16 22
    //
    if (argc < 3)
        return -1;
    
    // get key to search
    key = atoi(argv[1]);

    // get count of data; allocate memory; copy it to array
    count = argc - 2;
    a = malloc(sizeof(int)*count);
    if (a == NULL)
        return -1;
    
    for (i=0; i<count; i++)
        a[i] = atoi(argv[2+i]);
    
    // check if ascending or descending
    if (count > 1 && a[0] > a[1])
        ascending = 0;
    
    res = Search(a, count, ascending, key, LessThan, &idx);
    printf("<  %d : %s idx=%d\n", key, SearchResultStr[res], idx);
    
    res = Search(a, count, ascending, key, LessThanEquals, &idx);
    printf("<= %d : %s idx=%d\n", key, SearchResultStr[res], idx);
    
    res = Search(a, count, ascending, key, Equals, &idx);
    printf("== %d : %s idx=%d\n", key, SearchResultStr[res], idx);
    
    res = Search(a, count, ascending, key, GreaterThanEquals, &idx);
    printf(">= %d : %s idx=%d\n", key, SearchResultStr[res], idx);
    
    res = Search(a, count, ascending, key, GreaterThan, &idx);
    printf(">  %d : %s idx=%d\n", key, SearchResultStr[res], idx);
   
    free(a);
 
    return 0;
}

