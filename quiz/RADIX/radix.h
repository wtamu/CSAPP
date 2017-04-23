#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define NUM_BASES 4
#define NUM_QUEST 5

/* Function Prototypes */
void radixBanner(void);
void randArray(int a[], int size);
void dec2base(int dec, int base, char *converted);
void reverse(char *s);

/* Radix Structure */
typedef struct radix {
    char name[20];
    int val;
} radix;

/* Radix List */
radix base[NUM_BASES] = {
    {"Binary", 2},
    {"Octal", 8},
    {"Decimal", 10},
    {"Hexadecimal", 16},
};

/* Print Artistic Banner */
void radixBanner(void) {
    printf("   ___               _      _               _    \n");
    printf("  | _ \\   __ _    __| |    (_)    __ __    | |   \n");
    printf("  |   /  / _` |  / _` |    | |    \\ \\ /    |_|   \n");
    printf("  |_|_\\  \\__,_|  \\__,_|   _|_|_   /_\\_\\   _(_)_  \n");
    printf("_|\"\"\"\"\"|_|\"\"\"\"\"|_|\"\"\"\"\"|_|\"\"\"\"\"|_|\"\"\"\"\"|_| \"\"\" | \n");
    printf("\"`-0-0-'\"`-0-0-'\"`-0-0-'\"`-0-0-'\"`-0-0-'\"`-0-0-' \n");
}

/* Decimal to Base conversion, (x = q * base + r) */
void dec2base(int x, int b, char *s)
{
    int i = 0;      // String position
    int q = 0;      // Quotient
    int r = x;      // Remainder
    
    // Error Checking: base can be only 9-digits, plus 26-alpha
    if(b > 9 + 26) {
        printf("Error: Base too large for conversion!\n");
        return;
    }
    
    // Get digits into string
    while(r > 0) {
        // decrement r, get quotient
        while(r >= b) {
            r = r - b;
            q++;
        }
        // append base-digit
        if(r < b) {
            s[i++] = r < 10 ? r + '0' : r + ('A' - 10);
            s[i] = '\0';
        }
        // swap values for iteration
        r = q;
        q = 0;
    }
    reverse(s);
    
    return;
}

/* Reverse string */
void reverse(char *s)
{
    int len = strlen(s) - 1;
    for(int first = 0, last = len; first < last; first++, last--) {
        s[last] = s[first] ^ s[last];
        s[first] = s[first] ^ s[last];
        s[last] = s[first] ^ s[last];
    }
    return;
}

/* Load Dec Array - rand() % x */
void randArray(int a[], int size)
{
    time_t t;
    srand((unsigned) time(&t));
    for(int i = 0; i < size; i++)
        a[i] = (rand() % 254) + 1;
    return;
}