#include <stdio.h>

int main()
{
    int floor = 0, down = 0, i = 0;
    char c;

    while ((c = fgetc(stdin)) != EOF && (++i, floor += (c == '(' ? 1 : -1), 1))
        if (floor < 0 && !(down++)) printf("Santa went down at %d\n", i);

    printf("Santa is on floor %d\n", floor);
    return 0;
}
