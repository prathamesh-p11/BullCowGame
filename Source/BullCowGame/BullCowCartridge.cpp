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
        if (Input == HiddenWord)
        {
            PrintLine(TEXT("You Won!"));
            EndGame();
        }

        else
        {
            --Lives;
            if(Lives > 0)
            {
                if (HiddenWord.Len() != Input.Len())
                {
                    PrintLine(TEXT("Hidden word length is eual to %i, try again!!"), HiddenWord.Len());
                }
            }
            else
            {
                PrintLine(TEXT("You have no lives left!!"));
            }
        }
    }
}

void UBullCowCartridge::SetupGame()
{
    HiddenWord = TEXT("hour");
    Lives = HiddenWord.Len();
    bGameOver = false;

    PrintLine(TEXT("Welcome to bull cow game!"));
    PrintLine(TEXT("Total lives remaining: %i"), Lives);
    PrintLine(TEXT("Guess the %i letter word:"), HiddenWord.Len());

    PrintLine(TEXT("Press enter to continue..."));
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("Press Enter to play again...."));
}