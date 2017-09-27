#include <iostream>
#include <ctime>

using namespace std;

// deklarasjoner
int getrandomCard(int &mi, int &ma, int deckArray[][13], int &number, int &suit);
int drawCards(int &mi, int &ma, int &pHand, int deckArray[][13], int &number, int &suit, bool &a, bool &dCard);
int playerTurn(int &pHand, int &hHand, int &mi, int &ma, int deckArray[][13], int &number, int &suit, bool &natB, bool &a, bool &dCard);
int houseTurn(int &hHand, int &playerHand, int &mi, int &ma, int deckArray[][13], int &number, int &suit, bool &housea);

// main funksjonen
int main()
{        
    int cardSuit;
    int cardNumber;
    int win = 0;
    int playerHand = 0;
    int houseHand = 0;
    int pMoney = 100;
    int pBet = 10;
    int min;
    int max;
    int betAnswer;
    bool playGame = true;
    bool bettingTime = false;
    bool dealersCard = false;
    string playagainAnswer;

    srand(time(0));

    cout << "Welcome to blackjack.\n";
    cout << "The game will simulate a true deck of cards.\n";
    cout << "Aces are valued at both 1 and 11. Soft/hard hands are implemented.\n";
    cout << "Knight, queen and king are all valued at 10.\n";
    cout << "The goal is to get to 21, or as close as possible. The dealer will then play and try to beat you.\n";
    cout << "You can see the dealers first card during your turn by typing dealer.\n";
    cout << "The dealer will not draw any more cards after reaching the sum 17 or higher.\n";
    cout << "If you get 21 from the first two cards you initially recieve, you will get a natural blackjack. This gives 50% higher payout.\n\n";
    cout << "To play you have to bet a minimum of $10.\n";

    // selve spillets loop
    while (playGame == true)
    {
        int deckArray[4][13] =
        {{1,2,3,4,5,6,7,8,9,10,11,12,13},
         {1,2,3,4,5,6,7,8,9,10,11,12,13},
         {1,2,3,4,5,6,7,8,9,10,11,12,13},
         {1,2,3,4,5,6,7,8,9,10,11,12,13}};
        int &number = cardNumber;
        int &suit = cardSuit;
        int &pHand = playerHand;
        int &hHand = houseHand;
        int &mi = min;
        int &ma = max;
        bool naturalB = false;
        bool &natB = naturalB;
        bool ace = false;
        bool &a = ace;
        bool houseAce = false;
        bool &housea = houseAce;
        bool &dCard = dealersCard;

        // spillerens tur
        cout << "You have $" << pMoney << ".\n";
        cout << "Current bet $" << pBet << ".\n";
        cout << "Type bet to change it. Any key to start your turn.\n";
        cin >> playagainAnswer;
        if (playagainAnswer == "bet" || playagainAnswer == "BET")
        {
            bettingTime = true;
            cout << "---------------------------------------\n\n";
            cout << "Enter 3 to confirm bet. The game will then begin.\n";
            // en loop så man kan bestemme seg over hvor mye man vil vedde
            while (bettingTime == true)
            {
                cout << "Current bet: $" << pBet << ".\n"
                        "1. Enter amount\n"
                        "2. All in\n"
                        "3. Confirm bet\n";
                cout << "You have $" << pMoney << ".\n\n";
                cout << "---------------------------------------\n";
                cin >> betAnswer;
                switch (betAnswer)
                {
                case 1 :
                {
                    cout << "Enter the amount you wish to bet.\n";
                    cout << "You have $" << pMoney << ".\n";
                    cin >> betAnswer;
                    pBet = betAnswer;
                    break;
                }
                case 2 :
                {
                    pBet = pMoney;
                    cout << "You're going all in.\n";
                    break;
                }
                case 3 :
                {
                    if (pBet > pMoney) {
                        cout << "Cannot bet more than you currently have.\n";
                    }
                    else if (pBet < 10)
                    {
                        cout << "You have to bet at least $10 to play.";
                    }
                    else
                    {
                        bettingTime = false;
                        break;
                    }
                }
                default :
                    cout << "Invalid input.\n";
                }
            }
        }
        // kjører spillerfunksjonen
        win = playerTurn(pHand, hHand, mi, ma, deckArray, number, suit, natB, a, dCard);
        // hvis spilleren har stoppet selv er det huset sin tur
        if (win == 0)
        {
            win = houseTurn(hHand, pHand, mi, ma, deckArray, number, suit, housea);
        }
        // hvis spilleren får over 21 hopper den over huset sin tur

        /***** win checks *****/

        // splleren vinner hvis spilleren har høyest hånd
        if (win == 1)
        {
            if (naturalB == true)
            {
                cout << "-----------------------------------\n\n";
                cout << "You won a natural Blackjack. 50% higher payout!\n";
                pBet = pBet * 1.5;
                cout << "You won $" << pBet << ".\n";
                pMoney += pBet;
            }
            else
            {
                cout << "-----------------------------------\n\n";
                cout << "PLAYER: " << pHand << " / " << "DEALER: " << hHand << endl;
                cout << "You won: $" << pBet << ".\n";
                pMoney += pBet;
            }
            playGame = false;
        }
        // spilleren taper hvis huset har høyest hånd
        else if (win == 2)
        {
            cout << "-----------------------------------\n\n";
            cout << "PLAYER: " << pHand << " / " << "DEALER: " << hHand << endl;
            cout << "You lost: $" << pBet << ".\n";
            pMoney -= pBet;
            playGame = false;
        }
        // hvis huset får lik hånd som spilleren blir det uavgjort
        else if (win == 3)
        {
            cout << "-----------------------------------\n\n";
            cout << "PLAYER: " << pHand << " / " << "DEALER: " << hHand << endl;
            cout << "It's a draw.\n";
            playGame = false;
        }
        // hvis spilleren er tom for penger, er spillet over
        if (pMoney <= 0)
        {
            cout << "You are out of cash.\n";
            // muligheten til å starte på nytt
            cout << "Do you want to start over? (Y/N)\n";
            cin >> playagainAnswer;
            if (playagainAnswer == "Y" || playagainAnswer == "y")
            {
                playGame = true;
                pHand = 0;
                hHand = 0;
                pMoney = 100;
                pBet = 10;
                cout << "-----------------------------------\n\n";
            }
            else
            {
                return 0;
            }
        }
        else
        {

            playGame = true;
            pHand = 0;
            hHand = 0;
        }
    }
}

// lager selve kortet
int getrandomCard(int &mi, int &ma, int deckArray[][13], int &number, int &suit)
{
    int randomCard;
    int x = 99;
    bool drawCard = true;

    while (drawCard == true)
    {
        mi = 1;
        ma = 4;
        suit = mi + rand() % ((ma - mi ));
        ma = 13;
        number = mi + rand() % ((ma - mi ));
        if(deckArray[suit][number] == x)
        {
            drawCard = true;
        }
        else
        {
           randomCard = deckArray[suit][number];
           deckArray[suit][number] = x;
           drawCard = false;
        }
    }
    return randomCard;
}

// trekker kortet
int drawCards (int &mi, int &ma, bool &a, int deckArray[][13], int &number, int &suit, bool &dCard)
{
    int card = 0;
    int currentHand = 0;
    string suitName;
    string cardName;

    card = getrandomCard(mi, ma, deckArray, number, suit);

    // sjekker hva slags type og evnt om det er et bildekort
    switch(suit){
    case 1:
        suitName = "spades";
        break;
    case 2:
        suitName = "clubs";
        break;
    case 3:
        suitName = "diamonds";
        break;
    case 4:
        suitName = "hearts";
    }
    switch(number){
    case 10:
        cardName = "knight";
        break;
    case 11:
        cardName = "queen";
        break;
    case 12:
        cardName = "king";
        break;
    }
    if (dCard == true)
    {
        // ess
        if (card == 1)
        {
            currentHand += card;
            a = true;
        }
        // bildekort
        else if (card > 10)
        {
            card = 10;
            currentHand += card;
        }
        // kort 2-10
        else
        {
            currentHand += card;
        }
    }
    else
    {
        // ess
        if (card == 1)
        {
            cout << "The dealer draws you an ace of " << suitName << ".\n";
            currentHand += card;
            a = true;
        }
        // bildekort
        else if (card > 10)
        {
            cout << "The dealer draws you a " << cardName <<  " of " << suitName << ".\n";
            card = 10;
            currentHand += card;
        }
        // kort 2-10
        else
        {
            cout << "The dealer draws you a " << card << " of " << suitName << ".\n";
            currentHand += card;
        }
    }
    return currentHand;
}

// spillerens funksjon
int playerTurn(int &pHand, int &hHand, int &mi, int &ma, int deckArray[][13], int &number, int &suit, bool &natB, bool &a, bool &dCard)
{
    // deklarerer variabler
    int card;
    int answer;
    string continueAnswer;
    string suitName;
    string cardName;
    bool stopPlay = false;

    cout << "-----------------------------------\n";
    cout << "PLAYER\n\n";
    // gir spilleren to kort
    pHand = drawCards(mi, ma, a, deckArray, number, suit, dCard);
    pHand += drawCards(mi, ma, a, deckArray, number, suit, dCard);
    // gir huset et kort uten å vise det, derav boolen
    dCard = true;
    hHand = drawCards(mi, ma, a, deckArray, number, suit, dCard);
    dCard = false;
    if (a == true)
    {
        cout << "Soft hand: " << pHand << " / " << pHand+10 << ".\n";
    }
    else
    {
        cout << "Current hand: " << pHand << ".\n";
    }
    if (pHand+10 == 21 && a == true)
    {
        natB = true;
        return 1;
    }
    // spiller loop
    while (pHand < 22 && !stopPlay)
    {
        dCard = false;
        // spør om man vil plukke et kort
        cout << "\nNew card (Y/N) / To make the dealer draw his first card, type dealer (lower case).\n";
        cin >> continueAnswer;
        if (continueAnswer == "dealer")
        {
            switch(suit){
            case 1:
                suitName = "spades";
                break;
            case 2:
                suitName = "clubs";
                break;
            case 3:
                suitName = "diamonds";
                break;
            case 4:
                suitName = "hearts";
            }
            switch(number){
            case 11:
                cardName = "knight";
                break;
            case 12:
                cardName = "queen";
                break;
            case 13:
                cardName = "king";
                break;
            }

            // ess
            if (card == 1)
            {
               cout << "Dealers first card is ace of " << suitName << ".\n";
            }
            // bildekort
            else if (hHand > 10)
            {
                cout << "Dealers first card is " << cardName << " of " << suitName << ".\n";
            }
            // kort 2-10
            else
            {
                cout << "Dealers first card is " << hHand << " of " << suitName << ".\n";
            }
        }
        else if (continueAnswer == "Y" || continueAnswer == "y")
        {
            // trekker et kort
            card = drawCards(mi, ma, a, deckArray, number, suit, dCard);
            if (a == true)
            {
                // hvis kortet blir mer enn 10 så er det et bildekort
                if (card > 10)
                {
                    pHand+=card;
                    if (pHand < 11)
                    {
                        cout << "Soft hand: " << pHand << " / " << pHand+10 << ".\n";
                    }
                    else
                    {
                        cout << "Current hand: " << pHand << ".\n";
                    }
                }
                else if (card == 1)
                {
                    pHand+=1;
                    if (pHand < 11)
                    {
                        cout << "Current hand: " << pHand << " / " << pHand+10 << ".\n";
                    }
                    else
                    {
                        cout << "Current hand: " << pHand << ".\n";
                    }
                }
            }
            // 1 er det samme som ess
            else if (card == 1)
            {
                pHand+=1;
                if (pHand < 11)
                {
                    cout << "Current hand: " << pHand << " / " << pHand+10 << ".\n";
                }
                else
                {
                    cout << "Current hand: " << pHand << ".\n";
                }
                a = true;
            }
            else if (card > 10)
            {
                card = 10;
                pHand+= card;
                cout << "Current hand: " << pHand << ".\n";
            }
            else
            {
                pHand += card;
                cout << "Current hand: " << pHand << ".\n";
            }
        }
        // hvis man svarer noe annet enn ja, stopp loopen
        else
        {
            stopPlay = true;
        }

        if (a== true)
        {
            if (pHand < 11)
            {
                cout << "Current hand: " << pHand << " / " << pHand+10 << ".\n";
            }
        }
    }
    // returnerer 2 hvis man har høyere enn 21
    if (pHand > 21)
    {
        cout << "Player busted.\n";
        return 2;
    }
    // returnerer 0 hvis man har stoppet spillet selv
    else if (stopPlay == true)
    {
        if (a == true)
        {
            if (pHand < 11)
            {
                cout << "What hand do you choose? " << pHand << " or " << pHand+10 << "?\n";
                cin >> answer;
                if (answer == pHand)
                {
                    return 0;
                }
                else if (answer == pHand+10)
                {
                    pHand += 10;
                    return 0;
                }
                else
                {
                    cout << "Invalid input entered. Choosing most logical answer.\n";
                    if (pHand < 11)
                    {
                        pHand+=10;
                    }
                }
            }
            else
            {
                cout << "You have a hard " << pHand + 1 << ".\n";
                pHand++;
            }
        }
        cout << "Stopped with a hand of " << pHand << ".\n\n";
        return 0;
    }
    cout << "Lost with the hand " << pHand << ".\n";
    return 2;
}

// husets funksjon
int houseTurn(int &hHand, int &pHand, int &mi, int &ma, int deckArray[][13], int &number, int &suit, bool &housea)
{
    // deklarerer variabler
    int card;
    bool continuePlay = true;
    string suitName;
    string cardName;
    mi = 1;
    mi = 13;

    cout << "-----------------------------------\n";
    cout << "DEALER\n\n";
    cout << "Dealers current hand: " << hHand << ".\n";
    // summen ai må nå er mer enn playerHand og 21 eller mindre. Huset kan ikke trekke et kort til hvis summen er over 17
    while (hHand < 22 && continuePlay == true)
    {
        // trekk kort
        if (hHand <= pHand && hHand < 17)
        {
            card = getrandomCard(mi, ma, deckArray, number, suit);
            switch(suit){
            case 1:
                suitName = "spades";
                break;
            case 2:
                suitName = "clubs";
                break;
            case 3:
                suitName = "diamonds";
                break;
            case 4:
                suitName = "hearts";
            }
            switch(number){
            case 11:
                cardName = "knight";
                break;
            case 12:
                cardName = "queen";
                break;
            case 13:
                cardName = "king";
                break;
            }
            if (card == 1)
            {
                cout << "The dealer picked an ace of " << suitName << ".\n";
                housea = true;
                if (hHand > 11)
                {
                    cout << "Hard hand.\n";
                    card = 1;
                }
                else
                {
                    cout << "Soft hand.\n";
                    card = 11;
                }
            }
            else if (card > 10)
            {
                cout << "The dealer picked a " << cardName << " of " << suitName << ".\n";
                card = 10;
            }
            else
            {
                cout << "The dealer picked " << card << " of " << suitName << ".\n";
            }
            hHand += card;
            cout << "Dealers current hand: " << hHand << ".\n\n";
            continuePlay = true;
        }
        // hvis husets hånd er større enn spilleren
        // vinner huset
        else if (hHand > pHand)
        {
            continuePlay = false;
            return 2;
        }
        else if (hHand > pHand && hHand < 11)
        {
            continuePlay = true;
        }
        // Hvis husets hånd mer enn 16, men fortsatt lavere enn spilleren
        // vinner spilleren
        else if (hHand < pHand && hHand > 16)
        {
            continuePlay = false;
            return 1;
        }
        // hvis husets hånd er over 16 og lik som spilleren
        // blir det uavgjort
        else if (hHand == pHand && hHand > 16)
        {
            continuePlay = false;
            return 3;
        }
    }
    cout << "House busted.\n";
    return 1;
}
