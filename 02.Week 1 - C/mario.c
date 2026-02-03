#include <stdio.h>

void print_pyramid(int height);

int main(void)
{
    int height;
    do
    {
        printf("Height: ");
        scanf("%d", &height);
    }
    while (height < 1 || height > 8);

    print_pyramid(height);
}

void print_pyramid(int height)
{
    for (int i = 1; i <= height; i++)
    {
        // Print left spaces
        for (int j = 0; j < height - i; j++)
        {
            printf(" ");
        }

        // Print left blocks
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }

        // Print middle gap
        printf("  ");

        // Print right blocks
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }

        printf("\n");
    }
}
