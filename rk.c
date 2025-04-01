#include <stdio.h>
#include <string.h>

#define PRIME 101  // A prime number for hashing
#define CHAR_SIZE 256  // Number of possible characters (ASCII)

// Rabin-Karp algorithm for substring search
void rabinKarp(char text[], char pattern[], int q) {
    int m = strlen(pattern);
    int n = strlen(text);
    int i, j;
    int patternHash = 0; // Hash value for pattern
    int textHash = 0; // Hash value for text
    int h = 1;

    // The value of h would be "pow(CHAR_SIZE, m-1) % q"
    for (i = 0; i < m - 1; i++)
        h = (h * CHAR_SIZE) % q;

    // Calculate the hash value of pattern and first window of text
    for (i = 0; i < m; i++) {
        patternHash = (CHAR_SIZE * patternHash + pattern[i]) % q;
        textHash = (CHAR_SIZE * textHash + text[i]) % q;
    }

    // Slide the pattern over text one by one
    for (i = 0; i <= n - m; i++) {
        // Check the hash values of the current window of text and pattern
        if (patternHash == textHash) {
            // Check characters one by one
            for (j = 0; j < m; j++) {
                if (text[i + j] != pattern[j])
                    break;
            }
            if (j == m) // If pattern[0...m-1] == text[i...i+m-1]
                printf("Pattern found at index %d\n", i);
        }

        // Calculate hash value for next window of text
        if (i < n - m) {
            textHash = (CHAR_SIZE * (textHash - text[i] * h) + text[i + m]) % q;

            // Make sure textHash is positive
            if (textHash < 0)
                textHash = (textHash + q);
        }
    }
}

// Main function
int main() {
    char text[] = "ABCCDDAEFG";
    char pattern[] = "CDD";
    int q = PRIME; // A prime number
    printf("Searching for pattern \"%s\" in text \"%s\":\n", pattern, text);
    rabinKarp(text, pattern, q);
    return 0;
}

