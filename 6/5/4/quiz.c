#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_QUESTIONS 3
#define MAX_QUESTION_LENGTH 100
#define MAX_ANSWER_LENGTH 100

void askQuestion(const char *question, const char *answer, int *score) {
    char userAnswer[MAX_ANSWER_LENGTH];

    printf("%s\n", question);
    printf("Your answer: ");
    fgets(userAnswer, sizeof(userAnswer), stdin);

    // Remove newline character from user answer
    userAnswer[strcspn(userAnswer, "\n")] = '\0';

    if (strcmp(userAnswer, answer) == 0) {
        printf("Correct!\n");
        (*score)++; // Increment score
    } else {
        printf("Incorrect!\n");
    }
}

int main() {
    const char *questions[MAX_QUESTIONS] = {
        "What is the capital of France?",
        "Who painted the Mona Lisa?",
        "What is the symbol for hydrogen?"
    };

    const char *answers[MAX_QUESTIONS] = {
        "Paris",
        "Leonardo da Vinci",
        "H"
    };

    int score = 0;

    for (int i = 0; i < MAX_QUESTIONS; i++) {
        askQuestion(questions[i], answers[i], &score);
    }

    printf("Quiz completed. Your score is %d/%d\n", score, MAX_QUESTIONS);

    return 0;
}

