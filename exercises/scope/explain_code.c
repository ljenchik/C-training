#include <stdio.h> 

int main(void)
{
    int i;
    for( i = 0; i < 10; i++ )
    {
        int j = 0;
        for( j = 10; j > 0; j-- )
        {
            if( i > j )
            {
                printf("Variable i (%d) is bigger than j (%d) \n", i, j);
                break;
            }
        }
    }
    
    /* print result */
    // j's scope is in the inner loop
    //printf("Last values: i (%d), j (%d) \n", i, j);
    // i is global
    printf("Last values: i (%d)\n", i);
    
    return 0;
}