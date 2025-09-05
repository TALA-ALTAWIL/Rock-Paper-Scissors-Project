#include <iostream>   
#include <cstdlib>    
#include <ctime> 
using namespace std;

enum enGameChoice { Stone = 1, Paper = 2, Scissors = 3 };
enum enWinner { Player1 = 1, Computer = 2, Draw = 3 };
struct stRoundInfo
{
    short RoundNumber = 0;          // Round number.
    enGameChoice Player1Choice;     // Player's choice.
    enGameChoice ComputerChoice;    // Computer's choice.
    enWinner Winner;                // Stores the winner of the round.
    string WinnerName;               // Stores the winner's name.
};
struct stGameResults
{
    short GameRounds = 0;        // Number of rounds played.
    short Player1WinTimes = 0;   // Count of Player1's wins.
    short ComputerWinTimes = 0;  // Count of Computer's wins.
    short DrawTimes = 0;         // Number of rounds that ended in a draw.
    enWinner GameWinner;         // Stores the overall game winner.
    string WinnerName = "";      // Name of the game winner.
};
int RandomNumber(int From, int To)
{
    return rand() % (To - From + 1) + From;
}
short ReadHowManyRounds() {
    short GameRounds = 1;
    do {

        cout << "How Many Rounds You want to play from 1 to 10 ? " << endl;
        cin >> GameRounds;

    } while (GameRounds < 1 || GameRounds > 10);

    return GameRounds;
}
string Tabs(short number) {
    string s = "";
    for (int i = 0; i < number; i++)
    {
        s += "\t";
    }
    return s;
}
enGameChoice ReadPlayer1Choice() {
    short Choice;
    do
    {
        cout << "\nYour Choice: [1]:Stone, [2]:Paper, [3]:Scissors? ";
        cin >> Choice;
    } while (Choice < 1 || Choice > 3);
    return (enGameChoice)Choice;
}
enGameChoice GetComputerChoice() {
    return (enGameChoice)RandomNumber(1, 3);
}
enWinner WhoWonTheRound(stRoundInfo RoundInfo) {
    if (RoundInfo.Player1Choice == RoundInfo.ComputerChoice)
        return enWinner::Draw;

    // Determine the winner based on game rules.
    switch (RoundInfo.Player1Choice)
    {
    case enGameChoice::Stone:
        return (RoundInfo.ComputerChoice == enGameChoice::Paper) ? enWinner::Computer : enWinner::Player1;
    case enGameChoice::Paper:
        return (RoundInfo.ComputerChoice == enGameChoice::Scissors) ? enWinner::Computer : enWinner::Player1;
    case enGameChoice::Scissors:
        return (RoundInfo.ComputerChoice == enGameChoice::Stone) ? enWinner::Computer : enWinner::Player1;
    }
}
string WinnerName(enWinner Winner) {
    string arrWinnerName[3] = { "Player1", "Computer", "No Winner (Draw)" };
    return arrWinnerName[Winner - 1];
}
string ChoiceName(enGameChoice Choice) {
    string arrGameChoices[3] = { "Stone", "Paper", "Scissors" };
    return arrGameChoices[Choice - 1];
}
void PrintRoundResults(stRoundInfo RoundInfo) {
    cout << "\n____________ Round [" << RoundInfo.RoundNumber << "] ____________\n\n";
    cout << "Player1 Choice: " << ChoiceName(RoundInfo.Player1Choice) << endl;
    cout << "Computer Choice: " << ChoiceName(RoundInfo.ComputerChoice) << endl;
    cout << "Round Winner   : [" << RoundInfo.WinnerName << "]\n";
    cout << "_________________________________________\n" << endl;
}
enWinner WhoWonTheGame(short Player1WinTimes, short ComputerWinTimes)
{
    if (Player1WinTimes > ComputerWinTimes)
        return enWinner::Player1;
    else if (ComputerWinTimes > Player1WinTimes)
        return enWinner::Computer;
    else
        return enWinner::Draw;
}
void setWinnerScreenColor(enWinner Winner) {
    switch (Winner)
    {
    case Player1:
        system("color 2F");
        break;
    case Computer:
        system("color 4F");
        cout << "\a";
        break;
    default:
        system("color 6F");
        break;
    }
}
stGameResults PlayGame(short NumberOfRounds) {
    stRoundInfo RoundInfo;
    short Player1WinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;
    for (int GameRound = 1; GameRound <= NumberOfRounds; GameRound++)
    {
        cout << "\nRound [" << GameRound << "] begins:\n";
        RoundInfo.RoundNumber = GameRound;
        RoundInfo.Player1Choice = ReadPlayer1Choice();
        RoundInfo.ComputerChoice = GetComputerChoice();
        RoundInfo.Winner = WhoWonTheRound(RoundInfo);
        RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);
        setWinnerScreenColor(RoundInfo.Winner);

        if (RoundInfo.Winner == enWinner::Player1)
            Player1WinTimes++;
        else if (RoundInfo.Winner == enWinner::Computer)
            ComputerWinTimes++;
        else
            DrawTimes++;

        PrintRoundResults(RoundInfo);
    }
    return { NumberOfRounds, Player1WinTimes, ComputerWinTimes, DrawTimes, WhoWonTheGame(Player1WinTimes, ComputerWinTimes), WinnerName(WhoWonTheGame(Player1WinTimes, ComputerWinTimes)) };
}

void ShowFinalGameResults(stGameResults GameResults) {
    cout << Tabs(2) << "===========================[Game Result ]==============================\n\n";
    cout << Tabs(2) << "Game Rounds           : " << GameResults.GameRounds << endl;
    cout << Tabs(2) << "Player1 Win Times     : " << GameResults.Player1WinTimes << endl;
    cout << Tabs(2) << "Computer Win Times    : " << GameResults.ComputerWinTimes << endl;
    cout << Tabs(2) << "Draw Times            : " << GameResults.DrawTimes << endl;
    cout << Tabs(2) << "Final Winner          : " << GameResults.WinnerName << endl;
    cout << Tabs(2) << "===================================================================\n\n";
    setWinnerScreenColor(GameResults.GameWinner);
}

void ShowGameOverScreen() {
    cout << Tabs(2) << "____________________________________________________________________________\n\n";
    cout << Tabs(2) << "                      +++ G a m e O v e r +++\n";
    cout << Tabs(2) << "____________________________________________________________________________\n\n";
}
void StartGame()
{
    char PlayAgain = 'Y';

    do
    {
        system("cls");  // Clear the screen before starting a new game.
        system("color 0F");
        stGameResults GameResults = PlayGame(ReadHowManyRounds()); // Play 3 rounds.1
        ShowGameOverScreen();
        ShowFinalGameResults(GameResults);

        cout << Tabs(3) << "Do you want to play again ? (Y / N) : ";
        cin >> PlayAgain;

    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}
int main()
{
    srand((unsigned)time(NULL));  // Seed random number generator.
    StartGame();  // Start the game.
    return 0;  // Return 0 to indicate successful execution.
//}