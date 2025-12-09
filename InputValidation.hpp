#ifndef INPUT_VALIDATION_HPP
#define INPUT_VALIDATION_HPP

#include <iostream>
using namespace std;

int askNumber()
{
    int inputNumber;

    while (true)
    {
        cin >> inputNumber;

        // Jos numeron syöttö onnistui, tehdään myös pieni lisätarkastus.
        if (!cin.fail())
        {
            if (inputNumber < 1)
            {
                cout << "Anna luku joka on yli 1.\n";
            }
            else
            {
                cin.ignore(80, '\n');
                return inputNumber;
            }
        }

        // Epäonnistuminen, takaisin alkuun.
        cout << "Syötäthän vain numeroita...\n";
        cin.clear();
        cin.ignore(80, '\n');
    }
}

// Sama logiikka kuin ylemmässä mutta vain stringeille.
string askString()
{
    string inputString;

    while (true)
    {
        if (getline(cin, inputString))
        {
            return inputString;
        }

        cout << "Syötössä tapahtui virhe...\n";
        cin.clear();
        cin.ignore(80, '\n');
    }
}

#endif