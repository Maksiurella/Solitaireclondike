#include <iostream>
#include <iomanip>
#include <ctime>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

const int MAX_C = 52;

struct Card;
{
    int Value, Suit, color; //wartosc karty, kolor, i czerwona czy czarna
    string DescriptionCard;

    
    Card Card(int s; int v){
        Suit = s;
        Value = v;
        switch(Value)
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

             if(Value / 10)
                DesciptionCard = DescriptionCard + T;

                DescriptionCard += N;
        }

        

            

        }
        


    }
    
