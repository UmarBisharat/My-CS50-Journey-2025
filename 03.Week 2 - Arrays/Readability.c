#include <ctype.h>
#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    // Prompt the user for some text
    string text = get_string("Text: ");

    // Count the number of letters, words, and sentences in the text
    int letters   = count_letters(text);
    int words     = count_words(text);
    int sentences = count_sentences(text);

    // Compute the Coleman-Liau index
    // L = average number of letters per 100 words
    // S = average number of sentences per 100 words
    float L = ((float)letters / (float)words) * 100.0;
    float S = ((float)sentences / (float)words) * 100.0;

    float index = 0.0588 * L - 0.296 * S - 15.8;

    // Round to nearest integer
    int grade = (int)round(index);

    // Print the grade level
    if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}

// Counts letters: any lowercase a-z or uppercase A-Z
int count_letters(string text)
{
    int count = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))
        {
            count++;
        }
    }
    return count;
}

// Counts words: any sequence of characters separated by spaces
// Assumes text is not empty and does not start/end with a space
int count_words(string text)
{
    int count = 1; // At least one word if text is non-empty
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == ' ')
        {
            count++;
        }
    }
    return count;
}

// Counts sentences: any occurrence of '.', '!', or '?'
int count_sentences(string text)
{
    int count = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            count++;
        }
    }
    return count;
}
