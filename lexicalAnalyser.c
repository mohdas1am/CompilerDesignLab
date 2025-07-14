#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int isOperator(char c) {
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '=') {
        return 1;
    }
    return 0;
}

int isDelimiter(char c) {
    if (c == '(' || c == ')' || c == '{' || c == '}' || c == ',' || c == ';') {
        return 1;
    }
    return 0;
}

int isKeyword(char s[]) {
    char *keywords[] = {"int", "float", "void", "const", "long"};
    for (int i = 0; i < 5; i++) {
        if (strcmp(s, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int main() {
    FILE *fp = fopen("input.txt", "r");
    char c;
    
    while ((c = getc(fp)) != EOF) {
        char token[100];
        int i = 0;

        if (isspace(c)) {
            continue;
        } else if (c == '/') {
            c = getc(fp);
            if (c == '*') {
                while ((c = getc(fp)) != '*') {
                    continue;
                }
                c = getc(fp); // To consume '/'
            }
        } else if (isOperator(c)) {
            printf("%c -> operator\n", c);
        } else if (isDelimiter(c)) {
            printf("%c -> separator\n", c);
        } else if (c == '"') {
            token[0] = c;
            i = 1;
            while ((c = fgetc(fp)) != '"') {
                token[i++] = c;
            }
            token[i++] = '"';
            token[i] = '\0';
            printf("%s -> identifier\n", token);
        } else if (isalpha(c)) {
            token[0] = c;
            i = 1;
            while (isalpha(c = fgetc(fp))) {
                token[i++] = c;
            }
            token[i] = '\0';

            if (isKeyword(token)) {
                printf("%s -> keyword\n", token);
            } else {
                printf("%s -> identifier\n", token);
            }
        }
    }

    fclose(fp);
    return 0;
}

