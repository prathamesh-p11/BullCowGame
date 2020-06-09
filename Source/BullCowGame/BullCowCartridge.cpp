#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay()
{
    Super::BeginPlay();
    
    PrintLine(TEXT("Number of words = %i"), Words.Num());
    PrintLine(TEXT("\nNumber of Valid words = %i"), GetValidWords(Words).Num());
    SetupGame();
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
        if (Lives <= 0)
        {
            ClearScreen();
            PrintLine(TEXT("You have no lives left!!"));
            PrintLine(TEXT("The hidden word was %s"), *HiddenWord);
            EndGame();
            return;
        }
        else
            PrintLine(TEXT("Lives remaining: %i"), Lives);
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
        ClearScreen();
        PrintLine(TEXT("You Won!"));
        EndGame();
        return;
    }

    if (HiddenWord.Len() != Guess.Len())
    {
        PrintLine(TEXT("Hidden word length is equal to %i\nTry guessing again!!"), HiddenWord.Len());
        --Lives;
        return;
    }

    if (!IsIsogram(Guess))
    {
        PrintLine(TEXT("Word has to be an isogram!\nTry again..."));
        --Lives;
        return;
    }

    --Lives;
    PrintLine(TEXT("Try guessing again!!"));
    PrintLine(TEXT("\nLost a life!"));
}

bool UBullCowCartridge::IsIsogram(const FString &Guess) const
{
    int32 Length = Guess.Len();
    TMap<TCHAR, int32> FrequencyMap;
    
    for (int32 Index = 0; Index < Length; Index++)
    {
        FrequencyMap.Add(Guess[Index], 0);
    }
    
    for (int32 Index = 0; Index < Length; Index++)
    {
        FrequencyMap[Guess[Index]]++;
    }
    
    int32 Repeats = FrequencyMap[Guess[0]];    
    for(auto& Elem: FrequencyMap)
    {
        if(Elem.Value!=Repeats)
        {
            return false;
        }
    }
    return true;
}


TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString> &WordList) const
{
    TArray<FString> ValidWords;
    for(auto Word: WordList)
    {
        if( (Word.Len()>=4 || Word.Len()<=9) && IsIsogram(Word))
        {
            ValidWords.Emplace(Word);
        }       
    }

    return ValidWords;
}
