#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(void)
{
        char *ans = NULL;
        ans = malloc(sizeof(char *));
        int score = 0;
        printf("\t\t***************OLUWASEGUN QIUZ***************\n");
        printf("\t\t\tAnswer All Question\n");
        printf("\tYou are provided with four(4) questions and each carries 5 marks\n\n");

        printf("[1] How many planets do we have in the solar system?\n");
        printf("(a) 5\n(b) 7\n(c) 8\n\tEnter a, b, or c: ");
        scanf("%s", ans);
        if (strcmp(ans, "c") == 0)
                score += 5;

        putchar('\n');
        ans = NULL;
        ans = malloc(sizeof(char *));
        printf("[2] What is the name of our Galaxy?\n");
        printf("(a) Milky-way Galaxy\n(b) Earth-way Galaxy\n(c) Elnoid Galaxy\n\tEnter a, b, or c: ");
        scanf("%s", ans);
        if (strcmp(ans, "a") == 0)
                score += 5;

        putchar('\n');
        ans = NULL;
        ans = malloc(sizeof(char *));
        printf("[3] Which language is the most spoken language in the world?\n");
        printf("(a) Chinese\n(b) Korea\n(c) English\n\tEnter a, b, or c: ");
        scanf("%s", ans);
        if (strcmp(ans, "c") == 0)
                score += 5;

        putchar('\n');
        ans = NULL;
        ans = malloc(sizeof(char *));
        printf("[4] What is the name of the metal element that emit ligth rays in bulb?\n");
        printf("(a) Iron\n(b) Thungsten\n(c) Silicon\n\tEnter a, b, or c: ");
        scanf("%s", ans);
        if (strcmp(ans, "b") == 0)
                score += 5;

        printf("\n\t\tYou score %d out of 20 marks\n", score);

        if (score == 0)
                printf("\tYou did very poor\n");
        else if (score == 5)
                printf("\tYou did poor\n");
        else if (score == 10)
                printf("\tYou did good\n");
        else if (score == 15)
                printf("\tYou did very good\n");
        else
                printf("\t***************Excellent*************\n");

        return (0);
}
