// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    SetupGame(); //initializing game
}

void UBullCowCartridge::OnInput(const FString &Input) // When the player hits enter
{

    if (bGameOver)
    {
        ClearScreen();
        SetupGame();
    }
    else
    {
        ProcessGuess(Input);
    }
}

void UBullCowCartridge::SetupGame()
{
    HiddenWord = TEXT("hour");
    Lives = HiddenWord.Len();
    bGameOver = false;

    PrintLine(TEXT("Welcome to bull cow game!"));
    PrintLine(TEXT("Total lives: %i"), Lives);
    PrintLine(TEXT("Guess the %i letter word:"), HiddenWord.Len());
    PrintLine(TEXT("Press enter to continue..."));
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("\nPress Enter to play again...."));
}

void UBullCowCartridge::ProcessGuess(const FString &Guess)
{
    if (Guess == HiddenWord)
    {
        PrintLine(TEXT("You Won!"));
        EndGame();
        return;
    }

    /* 
    if(!IsIsogram)
    {
        
    }
 */
    if (Lives <= 0)
    {
        ClearScreen();
        PrintLine(TEXT("You have no lives left!!"));
        PrintLine(TEXT("The hidden word was %s"), *HiddenWord);
        EndGame();
        return;
    }

    if (HiddenWord.Len() != Guess.Len())
    {
        PrintLine(TEXT("Hidden word length is equal to %i\nTry guessing again!!"), HiddenWord.Len());
        PrintLine(TEXT("Lives remaining: %i"), --Lives);
        return;
    }
    
    --Lives;
    PrintLine(TEXT("\nLost a life!"));

    PrintLine(TEXT("Try guessing again!!"));
    PrintLine(TEXT("Lives remaining: %i"), Lives);
}