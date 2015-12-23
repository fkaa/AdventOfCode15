#include <stdio.h>

int main()
{
    int floor = 0;
    char c;

    while ((c = fgetc(stdin)) != EOF && (floor += (c == '(' ? 1 : -1), 1));

    printf("Santa is on floor %d\n", floor);
    return 0;
}
