#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

const int MAX_C = 52;
const int MAX_VECT = 28;

struct Card
{
    int Value, Suit, Color; //wartosc karty, kolor, i czerwona czy czarna
    string DescriptionCard;
    bool shown = false;

    Card() {}

    Card(int s, int v) {
        Suit = s;
        Value = v;
        switch (Value)
        {
        case 1:
            DescriptionCard += "A";
            break;
        case 11:
            DescriptionCard += "J";
            break;
        case 12:
            DescriptionCard += "Q";
            break;
        case 13:
            DescriptionCard += "K";
            break;
        default:
            char T, N;

            T = ('0' + Value / 10);
            N = ('0' + Value % 10);

            if (Value / 10)
                DescriptionCard = DescriptionCard + T;

            DescriptionCard += N;
        }

        switch (Suit)
        {
        case 0:
            DescriptionCard += "h";//serca
            Color = 1;
            break;
        case 1:
            DescriptionCard += "c";//trefl
            Color = 0;
            break;
        case 2:
            DescriptionCard += "s";//pik
            Color = 0;
            break;
        case 3:
            DescriptionCard += "d";//karo    
            Color = 1;
            break;
        }
    }


    Card& operator = (Card c) {
        Value = c.Value;
        Suit = c.Suit;
        Color = c.Color;
        DescriptionCard = c.DescriptionCard;
        shown = c.shown;

        return*this;
    }

};



class Gameplay
{

    Card deck[MAX_C];
    queue<Card> choice;
    vector<Card> heap1, heap2, heap3, heap4, heap5, heap6, heap7;
    vector<vector<Card>> h1_7 = { heap1, heap2, heap3, heap4, heap5, heap6, heap7 };
    stack<Card> s8, s9, s10, s11;
    vector<stack<Card>> s8_11 = { s8, s9, s10, s11 };

    string ChosenCard;
    int ChoiceNumber1; //zmienna 3
    int ChoiceNumber0; // zmienna1
    bool SameColor, CorrectValue, SameSuit;

public:
    Gameplay();

    void menu();

    void decking();
    void createV();
    void createQ();

    int maxSizeV();


    void num1();
    void num2();
    void line();

    void printQS();
    void printV();

    void MoveDirector();
    void movement1();
    void movement2();
    void movement3();
    void movement4();
    void movement5();
    void movement6();

    bool WinCondition();

    void errors(int n);



};
Gameplay::Gameplay() {
    for (int i = 0; i < MAX_C; i++) {
        Card temp(i / 13, i % 13 + 1);
        deck[i] = temp;
    }
}
void Gameplay::menu() {
    for (int i = 0; i < 4; i++)
        decking();

    createV();
    createQ();
    if (heap3.empty())


        cout << endl << setw(30) << "Klondike Solitaire" << endl;


    while (1) {



        num1();
        line();
        cout << endl;
        printQS();
        line();
        cout << endl;
        printV();
        line();
        num2();
        WinCondition();

        cin >> ChoiceNumber0 >> ChosenCard >> ChoiceNumber1;

        if (ChoiceNumber0 == 0)
        {

            if (ChoiceNumber1 == 0) {

                movement1();
            }
            else if (ChoiceNumber1 >= 0 && ChoiceNumber1 <= 7)
                movement2();
            else if (ChoiceNumber1 >= 8 && ChoiceNumber1 <= 11)
                movement3();

            else errors(1);
        }
        else if (ChoiceNumber0 >= 1 && ChoiceNumber0 <= 7)
        {
            if (ChoiceNumber1 >= 1 && ChoiceNumber1 <= 7)
                movement4();
            else if (ChoiceNumber1 >= 8 && ChoiceNumber1 <= 11)
                movement5();
        }
        else if (ChoiceNumber0 >= 8 && ChoiceNumber0 <= 11)
        {
            if (ChoiceNumber1 >= 1 && ChoiceNumber1 <= 7)
                movement6();
        }
    }

            
}





void Gameplay::decking()
{
    int k;
    for (int i = 0; i < MAX_C; i++)
        for (int j = 0; j < 4; j++) { //zamiana indeksow, bo dla i=0 k moze byc np 20, co zamieni ze deck bedzie deck[20] zamiast deck[0]
            k = rand() % MAX_C;

            Card temp = deck[i];
            deck[i] = deck[k];
            deck[k] = temp;

        }
}
void Gameplay::createV()
{
    int count = 0;
    for (int i = 0; i < 7; i++) {
        for (int j = count; j < count + i + 1; j++)
            h1_7[i].push_back(deck[j]);
        count += i + 1;

        h1_7[i].back().shown = true;


    }
}
void Gameplay::createQ()
{
    for (int i = MAX_VECT; i < MAX_C; i++)
    {
        choice.push(deck[i]);
    }
}

int Gameplay::maxSizeV()
{
    int max = 0;
    for (int i = 0; i < 7; i++)
        if (h1_7[i].size() > max)
            max = h1_7[i].size();
    return max;
}

void Gameplay::num1()
{
    cout << endl << setw(7) << "0" << setw(25) << " ";
    for (int i = 8; i < 12; i++)
        cout << setw(5) << i;
    cout << endl;

}
void Gameplay::num2() {
    cout << endl;
    for (int i = 1; i < 8; i++)
        cout << setw(7) << i << " ";
}
void Gameplay::line() {

    for (int i = 0; i < 57; i++)
        cout << "-";
}

void Gameplay::printQS() {
    if (!choice.empty())
        cout << setw(7) << choice.front().DescriptionCard << setw(25) << " ";
    else
        cout << setw(7) << "0" << setw(25);

    for (int i = 0; i < 4; i++)
    {
        if (!s8_11[i].empty())
            cout << setw(5) << s8_11[i].top().DescriptionCard;
        else
            cout << setw(5) << "0";
    }
    cout << endl;

}
void Gameplay::printV() {
    for (int i = 0; i < maxSizeV(); i++) {
        cout << "|";
        for (int j = 0; j < 7; j++) {
            if (i < h1_7[j].size()) {
                if (h1_7[j][i].shown == true)
                    cout << setw(6) << h1_7[j][i].DescriptionCard;
                else
                    cout << setw(6) << "===";


            }
            else
                cout << setw(6) << "  ";
            cout << setw(2) << "|";
        }

        cout << endl << endl;

    }
}

void Gameplay::MoveDirector()
{

    if (ChoiceNumber0 = 0)
    {

        if (ChoiceNumber1 = 0) {

            movement1();
        }
        else if (ChoiceNumber1 >= 0 && ChoiceNumber1 <= 7)
            movement2();
        else if (ChoiceNumber1 >= 8 && ChoiceNumber1 <= 11)
            movement3();

        else errors(3);
    }
    else if (ChoiceNumber0 >= 1 && ChoiceNumber0 <= 7)
    {
        if (ChoiceNumber1 >= 1 && ChoiceNumber1 <= 7)
            movement4();
        else if (ChoiceNumber1 >= 8 && ChoiceNumber1 <= 11)
            movement5();
    }
    else if (ChoiceNumber0 >= 8 && ChoiceNumber0 <= 11)
    {
        if (ChoiceNumber1 >= 1 && ChoiceNumber1 <= 7)
            movement6();
        else errors(3);
    }
    else errors(2);
}

void Gameplay::movement1() { //wybieranie kolejnych kart z kolejki
    if (!choice.empty())
    {
        choice.emplace(choice.front());
        choice.pop();
    }
    else
        errors(4);
}
void Gameplay::movement2() { //ruch z kolejki na wektory
    if (!choice.empty()) {
        if (choice.front().DescriptionCard == ChosenCard)
        {

            if (!h1_7[ChoiceNumber1 - 1].empty())
            {
                SameColor = (choice.front().Color == h1_7[ChoiceNumber1 - 1].back().Color);
                CorrectValue = ((h1_7[ChoiceNumber1 - 1].back().Value - choice.front().Value) == 1);

                if (!SameColor && CorrectValue)
                {
                    h1_7[ChoiceNumber1 - 1].push_back(choice.front());
                    choice.pop();
                    h1_7[ChoiceNumber1 - 1].back().shown = true;
                }
                else
                    errors(5);
            }
            else if (choice.front().Value == 13)
            {
                if (h1_7[ChoiceNumber1 - 1].empty())
                {
                    h1_7[ChoiceNumber1 - 1].push_back(choice.front());
                    choice.pop();
                    h1_7[ChoiceNumber1 - 1].back().shown = true;
                }
            }
          
        else(6);
        }
        else
            errors(7);
    }
    else
        errors(4);

}
void Gameplay::movement3() {
    if (!choice.empty()) {

        if (choice.front().DescriptionCard == ChosenCard) {

            if (!s8_11[ChoiceNumber1 - 8].empty()) {
                SameSuit = (s8_11[ChoiceNumber1 - 8].top().Suit == choice.front().Suit);
                CorrectValue = ((choice.front().Value - s8_11[ChoiceNumber1 - 8].top().Value) == 1);

                if (SameSuit && CorrectValue) {
                    s8_11[ChoiceNumber1 - 8].push(choice.front());
                    choice.pop();
                    s8_11[ChoiceNumber1 - 8].top().shown = true;
                }
                else
                    errors(5);
            }
            else if (choice.front().Value == 1) {
                s8_11[ChoiceNumber1 - 8].push(choice.front());
                choice.pop();
                s8_11[ChoiceNumber1 - 8].top().shown = true;
            }
            else
                errors(8);
        }
        else
            errors(7);
    }
    else errors(4);
}
void Gameplay::movement4() // ruch pomiedzy wektorami
{
    if (!h1_7[ChoiceNumber0 - 1].empty()) {
        int moving = -1;

        for (int i = h1_7[ChoiceNumber0 - 1].size() - 1; i >= 0; i--)
        {
            if (h1_7[ChoiceNumber0 - 1][i].DescriptionCard == ChosenCard && h1_7[ChoiceNumber0 - 1][i].shown == true)
            {
                moving = i;
                break;
            }
        }

        if (moving != -1)
        {
            if (!h1_7[ChoiceNumber1 - 1].empty()) {

                CorrectValue = ((h1_7[ChoiceNumber1 - 1].back().Value - h1_7[ChoiceNumber0 - 1][moving].Value) == 1);
                SameColor = (h1_7[ChoiceNumber0 - 1][moving].Color == h1_7[ChoiceNumber1- 1].back().Color);

                if (!SameColor && CorrectValue)//GDZIES TU JEST BLAD Z WEKTOREM
                {
                    for (int i = moving; i < h1_7[ChoiceNumber0 - 1].size(); i++)
                        h1_7[ChoiceNumber1 - 1].push_back(h1_7[ChoiceNumber0 - 1][i]);

                    h1_7[ChoiceNumber0 - 1].erase(h1_7[ChoiceNumber0 - 1].begin() + moving, h1_7[ChoiceNumber0 - 1].end());

                    if (!h1_7[ChoiceNumber0 - 1].empty())
                        h1_7[ChoiceNumber0 - 1].back().shown = true;
                }
            }
            else if (h1_7[ChoiceNumber0 - 1][moving].Value == 13) {
                for (int i = moving; i < h1_7[ChoiceNumber0 - 1].size(); i++)
                    h1_7[ChoiceNumber1 - 1].push_back(h1_7[ChoiceNumber0 - 1][i]);

                h1_7[ChoiceNumber0 - 1].erase(h1_7[ChoiceNumber0 - 1].begin() + moving, h1_7[ChoiceNumber0 - 1].end());

                if (!h1_7[ChoiceNumber0 - 1].empty())
                    h1_7[ChoiceNumber0 - 1].back().shown = true;
            }
         //dodaj bledy tutaj kuba
        }

    }
}
void Gameplay::movement5() // z wektora na stos
{
    if (!h1_7[ChoiceNumber0 - 1].empty())
    {
        if (h1_7[ChoiceNumber0 - 1].back().DescriptionCard == ChosenCard)
        {
            if (!s8_11[ChoiceNumber1 - 8].empty())
            {
                CorrectValue = ((h1_7[ChoiceNumber0 - 1].back().Value - s8_11[ChoiceNumber1 - 8].top().Value) == 1);
                SameSuit = (h1_7[ChoiceNumber0 - 1].back().Suit == s8_11[ChoiceNumber1 - 8].top().Suit);

                if (SameSuit && CorrectValue)
                {
                    s8_11[ChoiceNumber1 - 8].push(h1_7[ChoiceNumber0 - 1].back());
                    h1_7[ChoiceNumber0 - 1].pop_back();
                    h1_7[ChoiceNumber0 - 1].back().shown = true;
                }
                else
                    errors(5);
            }

            {
                if (h1_7[ChoiceNumber0 - 1].back().Value == 1)
                {

                    s8_11[ChoiceNumber1 - 8].push(h1_7[ChoiceNumber0 - 1].back());
                    h1_7[ChoiceNumber0 - 1].pop_back();
                    if (h1_7[ChoiceNumber0 - 1].size() > 1)
                        h1_7[ChoiceNumber0 - 1].back().shown = true;
                    else
                        h1_7[ChoiceNumber0 - 1].empty();


                }
                else
                    errors(8);
            }
        }
        else
            errors(7);
    }
    else errors(4);
}
void Gameplay::movement6() // ruch ze stosu do wektora
{
        if (!s8_11[ChoiceNumber0 - 8].empty())
        {
            if (s8_11[ChoiceNumber0 - 8].top().DescriptionCard == ChosenCard)
            {
                if (!h1_7[ChoiceNumber1 - 1].empty())
                {
                    CorrectValue = ((h1_7[ChoiceNumber1 - 1].back().Value - s8_11[ChoiceNumber0 - 8].top().Value) == 1);
                    SameColor = (s8_11[ChoiceNumber0 - 8].top().Color == h1_7[ChoiceNumber1 - 1].back().Color);

                    if (CorrectValue && !SameColor)
                    {
                        h1_7[ChoiceNumber1 - 1].push_back(s8_11[ChoiceNumber0 - 8].top());
                        s8_11[ChoiceNumber0 - 8].pop();
                        if (!s8_11[ChoiceNumber0 - 8].empty())
                            s8_11[ChoiceNumber0 - 8].top().shown = true;
                        else
                            s8_11[ChoiceNumber0 - 8].empty();
                    }

                }
                else if (h1_7[ChoiceNumber1 - 1].empty())
                {
                    if (s8_11[ChoiceNumber0 - 8].top().Value == 13)
                    {
                        h1_7[ChoiceNumber1 - 1].push_back(s8_11[ChoiceNumber0 - 8].top());
                        s8_11[ChoiceNumber0 - 8].pop();
                        s8_11[ChoiceNumber0 - 8].top().shown = true;
                    }
                    else errors(4);
                }
                else errors(3);
            }
            else errors(2);
        }
}


bool Gameplay::WinCondition() {

    int stack = 0;

    for (int i = 0; i < 4; i++)
        if (s8_11[i].size() == 13)
            stack++;

    if (stack == 4)
    {
        system("cls");
        cout << "Wygrales" << endl;

        return true;
    }

    return false;
  

}
//bledy
void Gameplay::errors(int n) {
    cout << endl;

    switch (n)
    {
    case 1:
        cout << "!!! Podano bledne dane. Sprobuj ponownie: ";
        break;
    case 2:
        cout << "!!! Do pustej kolumny mozna wstawic tylko krola lub zestaw kart na ktorych czele znajduje sie krol. Sprobuj ponownie: " << endl;
        break;
    case 3:
        cout << "!!! Podano zle dane Sprobuj ponownie." << endl;
        break;
    case 4:
        cout << "!!! Kolejka jest pusta" << endl;
        break;
    case 5:
        cout << "!!! Karty nie roznia sie kolorem lub nie jest o jeden nizsza!" << endl;
        break;
    case 6:
        cout << "!!! Do pustej kolumny mozna wstawic tylko krola lub zestaw kart na ktorych czele znajduje sie krol." << endl;
        break;
    case 7:
        cout << "!!! Zagrano zla karte. Sprobuj pownownie:" << endl;
        break;
    case 8:
        cout << "!!! Na koncu wektora musi znajdowac sie as!" << endl;
        break;
    }
}





int main()
{
    srand(time(NULL));

    Gameplay b;

    b.menu();



    return 0;
}
