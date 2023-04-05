#include <iostream>
#include <iomanip>
#include <ctime>
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
    int ChoiceNumber1;
    int ChoiceNumber2;
    bool SameColor, CorrectValue, SameSuit;

public:
    Gameplay();

    void createV();
    int maxSizeV();
    void decking();
    void createQ();
    void menu();
    void num1();
    void line();
    void num2();
    void printV();
    void printQ();

    void movement1();
    void movement2();



};
Gameplay::Gameplay() {
    for (int i = 0; i < MAX_C; i++) {
        Card temp(1 / 13, i % 13 + 1);
        deck[i] = temp;
    }
}

void Gameplay::decking()
{
    int k;
    for (int i = 0; i < MAX_C; i++) { //zamiana indeksow, bo dla i=0 k moze byc np 20, co zamieni ze deck bedzie deck[20] zamiast deck[0]
        k = rand() % MAX_C;

        Card temp = deck[i];
        deck[i] = deck[k];
        deck[k] = temp;

    }

}

void Gameplay::createV()
{
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < i + 1; j++)
            h1_7[i].push_back(deck[j]);


        h1_7[i].back().shown = true;

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
void Gameplay::createQ()
{
    for (int i = MAX_VECT; i < MAX_C; i++)
    {
        choice.push(deck[i]);
    }
}

void Gameplay::menu() {

    createV();
    createQ();


    decking();
    num1();
    line();
    cout << endl;
    printQ();
    line();
    cout << endl;
    printV();
    line();
    num2();

    

    cout << endl << "Solitaire" << endl;

}

void Gameplay::num1()
{
    cout << endl << setw(7) << "0" << setw(25) << " ";
    for (int i = 8; i < 12; i++)
        cout<< setw(5) << i;
    cout << endl;
  
}
void Gameplay::num2() {
    cout << endl;
    for (int i = 1; i < 8; i++)
        cout << setw(7) << i <<  " ";
}

void Gameplay::line() {
  
    for (int i = 0; i < 57; i++)
        cout << "-";
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

void Gameplay::printQ() {
    if (!choice.empty())
        cout << setw(7) << choice.front().DescriptionCard << setw(25)<< " ";
    else
        cout << setw(7)<< "0" << setw(25);

    for (int i = 0; i < 4; i++)
    {
        if (!s8_11[i].empty())
            cout << setw(5) << s8_11[i].top().DescriptionCard;
        else
            cout << setw(5) << "0";
     }
    cout << endl;
}

void Gameplay::movement1() {
    if (!choice.empty())
    {
        choice.emplace(choice.front());
        choice.pop();
    }
}
void Gameplay::movement2() {
    if (!choice.empty()) {
        if (choice.front().DescriptionCard == ChosenCard) 
        {
            if (!h1_7[ChoiceNumber1 - 1].empty())
            {
                SameColor = (choice.front().Color == h1_7[ChoiceNumber1 - 1].back().Color);
                CorrectValue = (h1_7[ChoiceNumber1 - 1].back().Value - choice.front().Value == 1);

                if (!SameColor and CorrectValue)
                {
                    h1_7[ChoiceNumber1 - 1].push_back(choice.front());
                    choice.pop();
                    h1_7[ChoiceNumber1 - 1].back().shown = true;
                }
                else
                    cout << "dupa";
            }
            else if (choice.front().Value == 13)
            {
                if (h1_7[ChoiceNumber1 - 1].empty())
                {
                    h1_7[ChoiceNumber1 - 1].push_back(choice.front());
                    choice.front();
                    h1_7[ChoiceNumber1 - 1].back().shown = true;
                }
            }
        }
    }

}
int main()
{
    srand(time(NULL));

    Gameplay b;

    b.menu();

   

    return 0;
}
    
