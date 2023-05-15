#include <iostream>
#include <algorithm>
#include <random>
#include <vector>

#include "../header/mapCatan.h"
#include "mapCatan.cpp"

#include "../header/mapTM.h"
#include "mapTM.cpp"

using namespace std;

// Catan

struct IndividualCatan
{
    vector<int> numbers = {2, 3, 3, 4, 4, 5, 5, 7, 6, 6, 8, 8, 9, 9, 10, 10, 11, 11, 12};
    vector<string> types =  { "G", "G", "G", "G", 
                            "L", "L", "L", "L", 
                            "W", "W", "W", "W",
                            "B", "B", "B", 
                            "O", "O", "O", 
                            "D"};   
    int value = 0;
};

void shuffleCatan(IndividualCatan &a)
{
    auto rng = default_random_engine{time(0)};
    shuffle(begin(a.numbers), end(a.numbers), rng);

    rng = default_random_engine{time(0)};
    shuffle(begin(a.types), end(a.types), rng);
    
    int i = 0;
    while(a.numbers[i] != 7) i++;
    
    int j = 0;
    while(a.types[j] != "D") j++;

    swap(a.types[i], a.types[j]);
}

void matchingCatan(IndividualCatan &a, const IndividualCatan &b)
{
    for(int i = 0; i < 7; i++)
    {
        if(b.numbers[i] == 7 || a.numbers[18-i] == 7)
        {
            for(int j = 0; j < 19; j++)
                if(a.numbers[j] == b.numbers[i])
                { 
                    swap(a.numbers[j], a.numbers[18-i]);
                    swap(a.types[j], a.types[18-i]);
                    break;
                }    
        }
        else
        {
            for(int j = 0; j < 19; j++)
                if(a.numbers[j] == b.numbers[i])
                { 
                    swap(a.numbers[j], a.numbers[18-i]);
                    break;
                }

            for(int j = 0; j < 19; j++)
                if(a.types[j] == b.types[i])
                {
                    swap(a.types[j], a.types[18-i]);
                    break;
                }
        }
    }
}

bool compareByValueCatan(const IndividualCatan &a, const IndividualCatan &b)
{
    return a.value < b.value;
}

// TM

struct IndividualTM
{
    vector<int> types = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, // Red
                          2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, // Blue
                          3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, // Green
                          4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, // Yellow
                          5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, // Brown
                          6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, // Gray
                          7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, // Black

                          8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
                          8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
                          8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, // River 
                        };   
    int value = 0;
};

void shuffleTM(IndividualTM &a)
{
    auto rng = default_random_engine{time(0)};
    shuffle(begin(a.types), end(a.types), rng);
}

void matchingTM(IndividualTM &a, const IndividualTM &b)
{
    for(int i = 0; i < 25; i++)
        for(int j = 0; j < a.types.size(); j++)
            if(a.types[j] == b.types[i])
            {
                swap(a.types[j], a.types[112-i]);
                break;
            }
}

bool compareByValueTM(const IndividualTM &a, const IndividualTM &b)
{
    return a.value < b.value;
}

int main()
{
    srand (time(NULL));
    int choice = 0;

    while(true)
    {
        cout << "Deseja um mapa de qual jogo?\n";
        cout << "1) Catan\n";
        cout << "2) Terra Mystica\n";
        cout << "Outro) Sair\n";
        cin >> choice;

        if(choice == 1)
        {
            MapCatan mapCatan;          
            vector<IndividualCatan> population;
            
            for(int i = 0; i < 10000; i++)
            {
                population.push_back(IndividualCatan());
                shuffleCatan(population.back());
                mapCatan.setValues(population.back().numbers, population.back().types);
                population.back().value = mapCatan.getResult();
            }
            
            sort(population.begin(), population.end(), compareByValueCatan);


            int count = 0;
            while(population[0].value > 0 && count < 10000)
            {
                count++;
                for(int i = 2000; i < 10000; i++)
                {
                    if(i<8000)
                    {
                        matchingCatan(population[i], population[rand()%2000]);
                        mapCatan.setValues(population[i].numbers, population[i].types);
                        population[i].value = mapCatan.getResult();
                    }
                    else
                    {
                        shuffleCatan(population[i]);
                        mapCatan.setValues(population[i].numbers, population[i].types);
                        population[i].value = mapCatan.getResult();
                    }
                }
                sort(population.begin(), population.end(), compareByValueCatan);
                cout << population[0].value 
                     << ' ' << population[2000].value 
                     << ' ' << population[8000].value
                     << ' ' << population[9999].value 
                     << " - Generation: " << count <<'\n';
            }

            cout << '\n';
            mapCatan.setValues(population[0].numbers, population[0].types);
            mapCatan.printTypes();
            cout << '\n';
            mapCatan.printNumbers();
            cout << '\n';             
            cout << "\n\n       ";
            
            for (int i = 0; i < 3; i++)
                cout << '[' << population[0].numbers[i] << ';' << population[0].types[i] << "] ";
            cout << "\n\n    ";
            for (int i = 3; i < 7; i++)
                cout << '[' << population[0].numbers[i] << ';' << population[0].types[i] << "] ";
            cout << "\n\n";
            for (int i = 7; i < 12; i++)
                cout << '[' << population[0].numbers[i] << ';' << population[0].types[i] << "] ";
            cout << "\n\n    ";
            for (int i = 12; i < 16; i++)
                cout << '[' << population[0].numbers[i] << ';' << population[0].types[i] << "] ";
            cout << "\n\n       ";
            for (int i = 16; i < 19; i++)
                cout << '[' << population[0].numbers[i] << ';' << population[0].types[i] << "] ";
            cout << "\n\nPoints: " << population[0].value;
        }
        else if(choice == 2)
        {
            MapTM mapTM;          
            vector<IndividualTM> population;
            
            for(int i = 0; i < 10000; i++)
            {
                population.push_back(IndividualTM());
                shuffleTM(population.back());
                mapTM.setValues(population.back().types);
                population.back().value = mapTM.getResult();
            }
            
            sort(population.begin(), population.end(), compareByValueTM);

            int count = 0;
            while(population[0].value > 0 && count < 1000)
            {
                count++;
                for(int i = 2000; i < 10000; i++)
                {
                    if(i<8000)
                    {
                        matchingTM(population[i], population[rand()%2000]);
                        mapTM.setValues(population[i].types);
                        population[i].value = mapTM.getResult();
                    }
                    else
                    {
                        shuffleTM(population[i]);
                        mapTM.setValues(population[i].types);
                        population[i].value = mapTM.getResult();
                    }
                }
                sort(population.begin(), population.end(), compareByValueTM);
                cout << population[0].value 
                     << ' ' << population[2000].value 
                     << ' ' << population[8000].value
                     << ' ' << population[9999].value 
                     << " - Generation: " << count <<'\n';
            }

            cout << "\n";

            for (int i = 0; i < population[0].types.size(); i++)
            {
                if( i == 13 || i == 38 || i == 63 || i == 88) cout << "\n  ";
                if( i == 25 || i == 50 || i == 75 || i == 100) cout << "\n";

                if(population[0].types[i] != 8)
                    cout << '[' << population[0].types[i] << "] ";
                else
                    cout << " *  ";
            }

            cout << "\n\nPoints: " << population[0].value << '\n';
        }
        else break;
    }
    return 0;
};