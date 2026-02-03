// Simulate genetic inheritance of blood types

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Each person has two parents and two alleles
typedef struct person
{
    struct person *parents[2];
    char          alleles[2];
} person;

const int GENERATIONS  = 3;
const int INDENT_LENGTH = 4;

// Function prototypes
person *create_family(int generations);
void    print_family(person *p, int generation);
void    free_family(person *p);
char    random_allele(void);

int main(void)
{
    // Seed the random-number generator
    srand(time(NULL));

    // Create a new family with GENERATIONS generations
    person *p = create_family(GENERATIONS);

    // Print family tree of blood types
    print_family(p, 0);

    // Free memory
    free_family(p);

    return 0;
}

// ---------- create_family ----------
// Recursively allocates a family tree.
// Base case  (generations == 1): oldest ancestors — alleles are random, parents are NULL.
// Recursive  (generations > 1) : first create both parents, then inherit one random
//                                 allele from each parent.
person *create_family(int generations)
{
    // Allocate memory for a new person
    person *p = malloc(sizeof(person));
    if (p == NULL)
    {
        exit(1);
    }

    // Base case: oldest generation — no parents, random alleles
    if (generations == 1)
    {
        p->parents[0] = NULL;
        p->parents[1] = NULL;
        p->alleles[0] = random_allele();
        p->alleles[1] = random_allele();
    }
    // Recursive case: younger generations inherit from parents
    else
    {
        // Recursively create both parents first
        p->parents[0] = create_family(generations - 1);
        p->parents[1] = create_family(generations - 1);

        // Inherit one randomly chosen allele from each parent
        p->alleles[0] = p->parents[0]->alleles[rand() % 2];
        p->alleles[1] = p->parents[1]->alleles[rand() % 2];
    }

    return p;
}

// ---------- print_family ----------
// Prints generation label, indentation, and blood type for p, then recurses on parents.
void print_family(person *p, int generation)
{
    if (p == NULL)
    {
        return;
    }

    // Print indentation (INDENT_LENGTH spaces per generation level)
    for (int i = 0; i < generation * INDENT_LENGTH; i++)
    {
        printf(" ");
    }

    // Print generation label
    if (generation == 0)
    {
        printf("Child ");
    }
    else if (generation == 1)
    {
        printf("Parent ");
    }
    else
    {
        printf("Grandparent ");
    }

    printf("(Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);

    // Recurse on both parents
    print_family(p->parents[0], generation + 1);
    print_family(p->parents[1], generation + 1);
}

// ---------- free_family ----------
// Recursively frees all ancestors before freeing p itself.
// Base case: p == NULL → nothing to free.
void free_family(person *p)
{
    if (p == NULL)
    {
        return;
    }

    // Free parents first (post-order: children freed after their subtrees)
    free_family(p->parents[0]);
    free_family(p->parents[1]);

    // Now free this person
    free(p);
}

// ---------- random_allele ----------
// Returns 'A', 'B', or 'O' with equal probability.
char random_allele(void)
{
    int r = rand() % 3;
    if (r == 0)
    {
        return 'A';
    }
    else if (r == 1)
    {
        return 'B';
    }
    else
    {
        return 'O';
    }
}
