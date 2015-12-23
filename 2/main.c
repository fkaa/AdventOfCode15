#include <stdio.h>

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
#define BUF_LEN 64

/*
 * convenience for getting smallest side, we sort all the sides of the cuboid
 * as an array using a sorting network. the two first entries will then be the
 * smallest ones
 */

static __inline void sort2(int *p1, int *p2)
{
    int temp = MIN(*p1, *p2);
    *p2 = MAX(*p1, *p2);
    *p1 = temp;
}

static __inline void sort3(int *arr)
{
    sort2(arr, arr + 1);
    sort2(arr + 1, arr + 2);
    sort2(arr, arr + 1);
}

int main()
{
    int c[3];
    int total = 0;

    char buf[BUF_LEN];
    while (fgets(buf, BUF_LEN, stdin) && sscanf(buf, "%dx%dx%d\n", c, c + 1, c + 2)) {
        /*
         * before sorting we can assign a few local variables that point to the
         * original input
         */
        int l = c[0], w = c[1], h = c[2];

        /* sort the dimensions so we can get the smallest side */
        sort3(c);

        /* all the cube sides */
        total += (2 * l * w)
               + (2 * w * h)
               + (2 * h * l)
               /* the slack side */
               + (c[0] * c[1]);
    }

    printf("The elves need %d sq ft of wrapping paper!\n", total);
    return 0;
}
