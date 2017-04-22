//Hangman by Yarden Shoham 2017
#define _CRT_SECURE_NO_WARNINGS
#define WORDS_SIZE 16
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
void printAttempts(int attemptsLeft);
char letterGuess(char *usedLetters);
int howManyChars(char *str, char ch);
void printUsedLetters(char *used);
void printWordBeautifully(char *word);
char* chooseWord(char *category);
void bufferFlush(void);
void game();
void main()
{
	char choice;
	printf("Welcome to Yarden's Hangman Game!\n");
	do
	{
		game();
		printf("Would you like to play again? Enter y for yes or n for no.\n");
		do {
			printf("> ");
			scanf("%c", &choice);
			bufferFlush();
			choice = tolower(choice);
			if (choice != 'n' && choice != 'y') printf("Invalid input, Please try again.\n");
			else if (choice == 'n') return;
		} while (choice != 'n' && choice != 'y');
	} while (1);
}
void game()
{
	char *word, *guessedWord, category[20], letter, usedLetters[26] = { 0 };
	int i, wrongGuessesLeft = 8, counter, spacesInWord, guessInWord;
	srand((unsigned)time(NULL));
	word = chooseWord(category);
	spacesInWord = howManyChars(word, ' ');
	guessedWord = (char *)malloc((strlen(word) + 1) * sizeof(char));
	if (!guessedWord)
	{
		printf("ERROR!\n");
		return;
	}
	for (i = 0; word[i]; i++)
		if (word[i] != ' ')
			guessedWord[i] = '_';
		else
			guessedWord[i] = ' ';
	guessedWord[i] = '\0';
	while (wrongGuessesLeft)
	{
		system("cls");
		printf("Category: %s\nAttempts left: %d\t", category, wrongGuessesLeft);
		printUsedLetters(usedLetters);
		printWordBeautifully(guessedWord);
		printAttempts(wrongGuessesLeft);
		letter = letterGuess(usedLetters);
		guessInWord = howManyChars(word, letter);
		if (!guessInWord)
			wrongGuessesLeft--;
		else
		{
			for (i = 0, counter = 0; counter != guessInWord; i++)
				if (tolower(word[i]) == letter)
				{
					guessedWord[i] = word[i];
					counter++;
				}
			if (!strcmp(word, guessedWord))
			{
				system("cls");
				printf("Category: %s\nAttempts left: %d\t", category, wrongGuessesLeft);
				printUsedLetters(usedLetters);
				printWordBeautifully(guessedWord);
				printAttempts(wrongGuessesLeft);
				printf("Success! The word%s indeed \"%s\". You had %d attempt%s left.\n", spacesInWord ? "s were" : " was", guessedWord, wrongGuessesLeft, wrongGuessesLeft > 1 ? "s" : "");
				break;
			}
		}
	}
	free(guessedWord);
	if (!wrongGuessesLeft)
	{
		system("cls");
		printf("You lost. The word%s \"%s\".\n", spacesInWord ? "s were" : " was", word);
	}
}
char letterGuess(char *usedLetters)
{
	char choice;
	printf("Please guess a letter.\n");
	while (1)
	{
		printf("> ");
		scanf("%c", &choice);
		bufferFlush();
		if (choice == '\n') continue;
		choice = tolower(choice);
		if (choice < 'a' || choice > 'z')
			printf("Sorry, you didn't enter a letter. Please try another one.\n");
		else if (usedLetters[choice - 97] != 1)
		{
			usedLetters[choice - 97] = 1;
			break;
		}
			else
				printf("Sorry, you've already tried this letter. Please try another one.\n");
	}
	return choice;
}
int howManyChars(char *str, char ch)
{
	int counter = 0;
	for (; *str; str++)
		if (tolower(*str) == ch) counter++;
	return counter;
}
void printAttempts(int attemptsLeft)
{
	if (attemptsLeft == 8)
	{
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		return;
	}
	if (attemptsLeft == 7)
	{
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n__________________________\n");
		return;
	}
	printf("  ____________\n  |          |\n  |          |\n  |          |\n  |");
	switch (attemptsLeft)
	{
	case 6: printf("\n  |\n  |\n  |\n  |\n  |\n  |\n  |\n  |\n  |\n  |\n");
		break;
	case 5: printf("         ---\n  |        |   |\n  |         ---\n  |\n  |\n  |\n  |\n  |\n  |\n  |\n  |\n");
		break;
	case 4: printf("         ---\n  |        |   |\n  |         ---\n  |          !\n  |          !\n  |          !\n  |          !\n  |          !\n  |\n  |\n  |\n");
		break;
	case 3: printf("         ---\n  |        |   |\n  |         ---\n  |          !\n  |          !\n  |      ----!----\n  |          !\n  |          !\n  |\n  |\n  |\n");
		break;
	case 2: printf("         ---\n  |        |   |\n  |         ---\n  |          !\n  |          !\n  |      ----!----\n  |          !\n  |          !\n  |         /\n  |        /  \n  |\n");
		break;
	case 1: printf("         ---\n  |        |   |\n  |         ---\n  |          !\n  |          !\n  |      ----!----\n  |          !\n  |          !\n  |         / \\\n  |        /   \\\n  |\n");
		break;
	}
	printf("__|_______________________\n");
}
void printUsedLetters(char *used)
{
	int i, counter = 0;
	printf("Letters used: ");
	for (i = 0; i < 26; i++)
		if (used[i])
		{
			if (counter)
				printf(", ");
			printf("%c", i + 97);
			counter = 1;
		}
	printf("\n");
}
void printWordBeautifully(char *word)
{
	for (; *word; word++)
		printf("%c ", *word == ' ' ? '-' : *word);
	printf("\n");
}
char* chooseWord(char *category)
{
	int choice;
	char *movies[WORDS_SIZE] = { 
		"Harry Potter", "Liam Neeson", "Hugh Jackson", "The Lord of the Rings",
		"director", "actor", "actress", "camera",
		"cinema", "film", "projector", "popcorn",
		"The Oscars", "Hollywood", "Brad Pitt", "James Bond"
	}, *shows[WORDS_SIZE] = {
		"The Flash", "news", "Breaking Bad", "The Big Bang Theory",
		"The Walking Dead", "Arrow", "The Blacklist", "Netflix",
		"Yes", "Hot", "Into the Badlands", "Silicon Valley",
		"Family Guy", "The Simpsons", "American Dad", "Game of Thrones"
	}, *computerEngineering[WORDS_SIZE] = {
		"computer", "school","library", "coding",
		"binary tree", "mouse",	"hello world","keyboard",
		"screen", "laptop", "The C Programming Language", "Visual Studio",
		"learning", "compiler", "Python", "The Internet" 
	};
	printf("Choose a category: (1) movies, (2) Computer Engineering, (3) TV shows.\n");
	do {
		printf("> ");
		scanf("%d", &choice);
		bufferFlush();
		if (choice > 3 || choice < 1) printf("Invalid input. Please try again.\n");
	} while (choice > 3 || choice < 1);
	switch (choice) {
	case 1: strcpy(category, "Movies");
		return movies[rand() % WORDS_SIZE];
	case 2: strcpy(category, "Computer Engineering");
		return computerEngineering[rand() % WORDS_SIZE];
	case 3: strcpy(category, "TV Shows");
		return shows[rand() % WORDS_SIZE];
	}
}
//Cleans the buffer.
void bufferFlush(void)
{
	int i, size, ch;
	fseek(stdin, 0, SEEK_END);
	size = ftell(stdin);
	rewind(stdin);
	for (i = 0; i < size; i++)
		ch = getchar();
}