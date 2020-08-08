/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: ishan
 *
 * Created on July 20, 2020, 9:30 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
 * @description This function will read the file and select the random word from the list of words.
 * @param rNum
 */@return void
void readFile(int rNum)
{
    FILE *fptr;
    //Creating file pointer, 'r+' mode is to avoid overwriting the file
    fptr = fopen("C:/Users/ishan/NetBeansProjects/Hangman/Words.txt","r+");
    //Condition if file do not open
    if(fptr == NULL)
    {
        printf("File opening error!!\n");
        exit(1);
    }
    
    //logic to select a random word by reading the word from list using random  number.
    char ch;
    int count = 0;
    int arrCount = 0;
    ch = getc(fptr);
    char wordArr[5];
    //Read the file till EOF
    while(ch != EOF)
    {
        //Logic to find the correct word as per random number
        if(count == rNum-1)
        {
            //Store the whole word
            while(ch != '\n')
            {
                wordArr[arrCount] = ch;
                arrCount++;
                ch = getc(fptr);
            }
            break;
        }
        //If one word is complete, move to next word
        if(ch == '\n')
        {
            count++;
        }
        ch = getc(fptr);
    }
    askUser(wordArr,arrCount);
    fclose(fptr);
}

/**
 * @description This function will ask user to enter a letter for the given word till either user looses 
 * or wins the game. User will have 8 turns to guess the word.
 * @param inputWord
 * @param size
 * @return void
 */
void askUser(char *inputWord, int size)
{
    char displayArr[size];
    int matchCount = 0;
    int winFlag = 0;
    //First create a new array to store the updated word and initialize with '-' character.
    for(int i = 0; i<size; i++)
    {
        displayArr[i] = '-';
    }
    printf("\n");
    //Initially display '-'
    for(int i = 0; i<size; i++)
    {
        printf("-");
    }
    
    printf("\nTotal 8 turns allowed.\n");
    int turns = 1;
    char inputLetter;
    //Logic to enter guess letter by the user and also to check if character matches with the original word.
    //If the letter matches with the letter in the original word, it will be updated in final array.
    while(turns < 9)
    {
        printf("\nTurn: %d    Guess letter: ",turns);
        scanf(" %c",&inputLetter);
        checkChar(inputLetter,inputWord,size,displayArr,matchCount);
        //Logic to check if the user guesses the whole word correctly.
        if(checkCompleteArray(displayArr,size) == 0)
        {
            printf("\nYou won!!\n");
            winFlag = 1;
            break;
        }
        turns++;
    }
    //Logic to check if user won or lost
    if(winFlag == 0)
    {
        printf("\nYou loose.\n");
        printf("Word was ");
        for(int i = 0; i<size; i++)
        {
            printf("%c",inputWord[i]);
        }
        printf("\n");
    }
    
    
}

/**
 * @description This function will check if the user has guessed the whole word.
 * @param inputArr
 * @param size
 * @return integer
 */
int checkCompleteArray(char *inputArr, int size)
{
    int verifyCommplete = 0;
    for(int i = 0; i<size; i++)
    {
        if(inputArr[i] == '-')
        {
            verifyCommplete = 1;
            break;
        }
    }
    return verifyCommplete;
    
}

/**
 * @description This function will check if the user's input matches the original word. If it matches it will updated the final array.
 * @param input
 * @param wordArray
 * @param size
 * @param dispArray
 * @param matchCount
 */
void checkChar(char input, char *wordArray, int size, char *dispArray, int matchCount)
{
    
    for(int i = 0; i<size; i++)
    {
        if(input == wordArray[i])
        {
            matchCount++;
            dispArray[i] = input;
        }
    }
    
    for(int j = 0; j < size; j++)
    {
        printf("%c",dispArray[j]);
    }
   
}

/**
 * @description This function will generate random number.
 * @return integer
 */
int generateRandomNum()
{
    int min = 1;
    int max = 9;
    int randomNum = 0;
    srand((unsigned)time(NULL));
    randomNum = rand()%((max+1)-min) + min;
    return randomNum;
}


/*
 * 
 */
int main(int argc, char** argv) {

    printf("*****Hangman*****\n");
    printf("*****************\n");
    int randomNum = 0;
    randomNum = generateRandomNum();
    readFile(randomNum);
    return 0;
}

