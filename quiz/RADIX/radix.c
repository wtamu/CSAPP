#include "radix.h" 

#define TRUE 1
#define FALSE 0
#define MAXLINE 100

/* Function Prototypes */
int getLine(char line[], int maxline);
int isNumber(char line[]);
int inArray(char line[], int size);

int main()
{
    radixBanner();
    printf(">>Welcome to radix! Let's practice number system conversions!\n");
    
    // User Input Line
    char line[MAXLINE];
    
    int replay = TRUE;
    while(replay) { 
        
        int from, to;
        
        /***** 1. Get Base To Convert From *****/
        printf("\n>>Which base would you like to convert from?\n");
        
        // Print List
        for(int i = 0; i < NUM_BASES; i++)
            printf("%d: %s\n", i+1, base[i].name);
        
        // Ask Option From
        do {
            printf(">>Enter Number: ");
            getLine(line, MAXLINE);
        } while(!(isNumber(line) && inArray(line, NUM_BASES)));
        
        // Assign Option From
        from = atoi(line);
        printf(">>You chose %d: %s\n\n", from, base[from-1].name);
        
        /***** 2. Get Base To Convert To *****/ 
        printf(">>Which base would you like to convert to?\n");
        
        // Print List, Less Option From
        for(int i = 0; i < NUM_BASES; i++)
            (i + 1 != from) ? printf("%d: %s\n", i+1, base[i].name): FALSE;

        // Ask Option To
        do {
            do {
                printf(">>Enter Number: ");
                getLine(line, MAXLINE);
            } while(!(isNumber(line) && inArray(line, NUM_BASES)));
            // Assign Option To
            to = atoi(line);
        } while(from == to);
        
        printf(">>You chose %d: %s\n\n", to, base[to-1].name);

        /***** 3. Create Questions and Answers *****/
        int dec[NUM_QUEST];
        char *question[NUM_QUEST];
        char *answer[NUM_QUEST];
        
        // Malloc Questions and Answers
        for(int i = 0; i < NUM_QUEST; i++) {
            question[i] = (char *) malloc(MAXLINE);
            answer[i] = (char *) malloc(MAXLINE);
        }
        
        // Create RND
        randArray(dec, NUM_QUEST);
    
        // Convert RND to Questions and Answers
        for(int i = 0; i < NUM_QUEST; i++){
            dec2base(dec[i], base[from-1].val, question[i]);
            dec2base(dec[i], base[to-1].val, answer[i]);
        }
        
        /***** 4. Ask Questions *****/
        int score = 0;
        time_t start_t, end_t;
        double diff_t;
        
        // Start Timer!!!
        time(&start_t);
    
        for(int i = 0; i < NUM_QUEST; i++){
            // Ask Question
            printf("%s: %s\n", base[from-1].name, question[i]);
            printf("%s: ", base[to-1].name);
            getLine(line, MAXLINE);
            
            // Case Insensitive
            for(int j = 0, len = strlen(line); j < len; j++)
                line[j] = toupper(line[j]);
        
            // Check Answer    
            if(strcmp(answer[i], line) == 0){
                printf(">>Correct!\n\n");
                score++;
            }
            else
                printf(">>Incorrect. %s\n\n", answer[i]);
        }
        
        // End Timer!!!
        time(&end_t);
        diff_t = difftime(end_t, start_t);
        
        // Post Results
        printf(">>Thanks for playing!\n>>SCORE: %d/%d\n>>TIME: %.0f seconds\n", score, NUM_QUEST, diff_t);
        
        // Only If Perfect Score, Compare Results
        if (score == NUM_QUEST) {
            
            /***** 5. Open File *****/
            FILE *fp;
            char path[MAXLINE];     // File Path
            char fname[MAXLINE];    // File Name
            
            // Name File
            strcpy(path, "./SCORES/");
            sprintf(fname, "%dto%d_Q%d.txt", base[from-1].val, base[to-1].val, NUM_QUEST);
            strcat(path, fname);
            
            // Open File Append+
            fp = fopen(path, "a+");
            if (fp == NULL) {
                printf("Error: File could not be opened!");
                fclose(fp);
                exit(1);
            }
            
            /***** 6. Read File *****/
            char scoreline[MAXLINE];
            int highscore[5];
    
            // Initialize to Zero
            for(int i = 0; i < 5; i++)
                highscore[i] = 0;
            
            // Read File Into Scoreline
            fread(scoreline, sizeof(char), MAXLINE, fp);
            
            // Parse File For High Scores
            char token[20];     // Token
            int rank = 0;       // High Score Rank
    
            // Traverse Entire String (Skips Zero)
            for(int i = 0, ti = 0, len = strlen(scoreline); i < len; i++){
                // EOF
                if(scoreline[i] == '\0') {
                    break;
                }
                // Pipe-Delimiter
                else if(scoreline[i] == '|') {
                    highscore[rank] = atoi(token);
                    rank++;     // Advance To Next Rank
                    ti = 0;     // Reset Token Position
                }
                // Tokenize
                else {
                    token[ti++] = scoreline[i];
                    token[ti] = '\0';       // Advance Token Position
                }
            }
            
            // Close File for Reading
            fclose(fp);
            
            /***** 7. Compare High Score Results *****/
            for(int i = 0; i < 5; i++) {
                // High Score!
                if(diff_t <= highscore[i]) {
                    // Shift Scores Down
                    for(int j = 4; j > i; j--)
                        highscore[j] = highscore[j-1];
                    highscore[i] = diff_t;
                    
                    // Print High Scores
                    printf(">>HIGH SCORE!!!\n");
                    for(int k = 0; k < 5; k++)
                        (highscore[k] != 0) ? printf("[%d]: %d seconds\n", k + 1, highscore[k]) : FALSE;
                    break;
                }
                // High Score!
                else if (highscore[i] == 0) {
                    // Because No Competition...
                    highscore[i] = diff_t;
                    
                    // Print High Scores
                    printf(">>HIGH SCORE!!\n");
                    for(int k = 0; k < 5; k++)
                        (highscore[k] != 0) ? printf("[%d]: %d seconds\n", k + 1, highscore[k]) : FALSE;
                    break;
                }
            }
            
            /***** 8. Write File *****/
            fp = fopen(path, "w");
            if (fp == NULL) {
                printf("Error: File could not be opened!");
                fclose(fp);
                exit(2);
            }
            
            // Write Scores To File
            for(int i = 0; i < 5; i++)
                fprintf(fp, "%d|", highscore[i]);
            
            // Close File for Writing
            fclose(fp);
        }
        
        /***** 9. Free Mallocs *****/ 
        for(int i = 0; i < NUM_QUEST; i++){
            free(question[i]);
            free(answer[i]);
        }
    
        /***** 10. Replay *****/       
        printf(">>Play Again? (Y/N)\n");
        getLine(line, MAXLINE);
        if(line[0] == 'Y' || line[0] == 'y')
            replay++;
        else
            replay = FALSE;
    }
return 0;
}

/* Get User Input, returns length of string */
int getLine(char s[], int lim)
{
    int c, i;
    for(i = 0; i < lim-1 && (c=getchar()) != EOF && c != '\n'; i++)
        s[i] = c;
    s[i] = '\0';
    return i;
}

/* String input is Number */
int isNumber(char s[])
{
    int len = strlen(s);
    if(len <= 0) {
        printf("Invalid Input: No text entered!\n");
        return FALSE;
    }                                                          
    
    for(int i = 0; i < len; i++)                  
        if(!isdigit(s[i]) && s[i] != '\0') {
            printf("Invalid Input: %s is not a number!\n", s);
            return FALSE;
        }
    return TRUE;
}

/* String input is in Array */
int inArray(char s[], int size)
{
    int n = atoi(s);
    if(n > 0 && n <= size)
        return TRUE;
    else
        printf("Invalid Input: %s is not an option!\n", s);
    return FALSE;
}