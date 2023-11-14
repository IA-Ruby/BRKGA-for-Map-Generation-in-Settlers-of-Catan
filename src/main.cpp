#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <chrono>

#include "../header/mapCatan.h"
#include "mapCatan.cpp"

#include "../header/mapTM.h"
#include "mapTM.cpp"

using namespace std;

// Catan
struct IndividualCatan
{
    vector<int> numbers = {2, 3, 3, 4, 4, 5, 5, 7, 6, 6, 8, 8, 9, 9, 10, 10, 11, 11, 12};
    vector<string> types =  { "G", "G", "G", "G", //Grain
                            "L", "L", "L", "L",   //Lumber
                            "W", "W", "W", "W",   //Wool
                            "B", "B", "B",        //Brick
                            "O", "O", "O",        //Ore
                            "D"};   
    int value = 0;
};

void shuffleCatan(IndividualCatan &a)
{   
    for(int i = 0; i < 19; i++){
        swap(a.numbers[i], a.numbers[rand()%19]);
        swap(a.types[i], a.types[rand()%19]);
        break;
    }    

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

void heapifyCatan(vector<IndividualCatan>& t, int n, int i)
{
    int j = i*2+1;
    if(j <= n && j > 0){
        if(j < n){
            if(t[j+1].value > t[j].value){
                j++;
            }
        }
        if(t[i].value < t[j].value){
            swap(t[j], t[i]);
            heapifyCatan(t, n, j);
        }
    }
}   

void heapSortCatan(vector<IndividualCatan>& t)
{
    int n = t.size();
    for(int i = n/2; i >= 0; i--){
        heapifyCatan(t, n, i);
    }
    for(int i = n-1; i >= 1; i--){
        swap(t[0], t[i]);
        heapifyCatan(t,i-1,0);    
    }
}

// TM
struct IndividualTM
{
    vector<int> types = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, // Yellow
                          2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, // Brown
                          3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, // Black
                          4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, // Blue
                          5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, // Green
                          6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, // Gray
                          7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, // Red

                          8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
                          8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
                          8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, // River 
                        };   
    int value = 0;
};

void shuffleTM(IndividualTM &a)
{
    for(int i = 0; i < a.types.size(); i++){
        swap(a.types[i], a.types[rand()%(a.types.size()-1)]);
    }    
}

void matchingTM(IndividualTM &a, const IndividualTM &b)
{
    for(int i = 0; i < 25; i++)
        for(int j = 0; j < a.types.size(); j++){
            if(a.types[j] == b.types[i])
            {
                swap(a.types[j], a.types[a.types.size()-i]);
                break;
            }
        }
}

void heapifyTM(vector<IndividualTM>& t, int n, int i)
{
    int j = i*2+1;
    if(j <= n && j > 0){
        if(j < n){
            if(t[j+1].value > t[j].value){
                j++;
            }
        }
        if(t[i].value < t[j].value){
            swap(t[j], t[i]);
            heapifyTM(t, n, j);
        }
    }
}   

void heapSortTM(vector<IndividualTM>& t)
{
    int n = t.size();
    for(int i = n/2; i >= 0; i--){
        heapifyTM(t, n, i);
    }
    for(int i = n-1; i >= 1; i--){
        swap(t[0], t[i]);
        heapifyTM(t,i-1,0);    
    }
}

int main()
{
    srand(time(nullptr));
    int popSize = 1000;
    int elite = popSize/10;
    int mutation = popSize/10*8;
    int numberMaps = 1;
    float avrgTime = 0;
    int choice = 1;

    while(choice == 1 || choice == 2)
    {
        cout << "\n\nDeseja um mapa de qual jogo?\n";
        cout << "1) Catan\n";
        cout << "2) Terra Mystica\n";
        cout << "Outro) Sair\n";
        cin >> choice;
        
        if(choice == 1)
        {
            ofstream outputFile("testCatan"+to_string(popSize)+".txt");
            MapCatan mapCatan;          
            IndividualCatan bestScore;

            if(outputFile.is_open()){
                outputFile << "Test for Catan\n";
                outputFile << "\nPopulation: " << popSize;
                outputFile << "\nElite size: " << elite;
                outputFile << "\nMutation size: " << mutation;
                outputFile << "\n\nMaps: \n\n";
                
                int maps = 1;
                while(maps <= numberMaps)
                {
                    chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
                    chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

                    vector<IndividualCatan> population;

                    outputFile << "Map " << maps << ": ";

                    for(int i = 0; i < popSize; i++)
                    {
                        population.push_back(IndividualCatan());
                        shuffleCatan(population.back());
                        mapCatan.setValues(population.back().numbers, population.back().types);
                        population.back().value = mapCatan.getResult();
                    }
                    heapSortCatan(population);
                    outputFile << "\n   (" << population[0].value << ", 0, "
                            << (chrono::duration_cast<chrono::microseconds>(end - begin).count()) /1000000.0 << "s)";

                    int oldScore = population[0].value;
                    int count = 0;
                    while(population[0].value > 0 && (chrono::duration_cast<chrono::microseconds>(end - begin).count())/1000000.0 < 300)
                    {
                        count++;
                        for(int i = elite; i < popSize; i++)
                        {
                            if(i < mutation)
                            {
                                matchingCatan(population[i], population[rand()%elite]);
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
                        heapSortCatan(population);
                        end = std::chrono::steady_clock::now();
                        if(oldScore > population[0].value){
                            oldScore = population[0].value;
                            outputFile << "\n   (" << oldScore << ", " << count << ", "
                                << (chrono::duration_cast<chrono::microseconds>(end - begin).count()) /1000000.0 << "s)";
                        }
                    }
                    
                    if(maps > 1){
                        if(population[0].value < bestScore.value){
                            bestScore = population[0];
                        }
                    }else bestScore = population[0];

                    maps++;
                    end = std::chrono::steady_clock::now();
                    avrgTime += chrono::duration_cast<chrono::microseconds>(end - begin).count() /1000000.0; 
                    outputFile << "\n\n[Points: " << population[0].value << " | Generation: " << count << " | "
                        << "Time: " << (chrono::duration_cast<chrono::microseconds>(end - begin).count()) /1000000.0  <<"s]\n\n";
                }
                outputFile << "\nBest map: \n\n";
                
                for(int i = 0; i < bestScore.numbers.size(); i++){
                    if(i == 3 || i == 7 || i == 12 || i == 16) outputFile << "\n"; 
                    if(i == 0 || i == 16) outputFile << "      ";
                    if(i == 3 || i == 12) outputFile << "   ";
                    outputFile << " [" << bestScore.numbers[i] << ";" << bestScore.types[i] << "] ";
                }
                outputFile << '\n';           
                outputFile << "\nPointuation: " << bestScore.value;
                outputFile << "\nTempo medio: " << avrgTime/numberMaps;

                outputFile.close();
                cout << "Map created";

            }else cout << "Failed to create the file";
        }
        else if(choice == 2)
        {
            ofstream outputFile("testTM"+to_string(popSize)+".txt");
            MapTM mapTM;        
            IndividualTM bestScore;

            if(outputFile.is_open()){
                outputFile << "Test for TM\n";
                outputFile << "\nPopulation: " << popSize;
                outputFile << "\nElite size: " << elite;
                outputFile << "\nMutation size: " << mutation;
                outputFile << "\n\nMaps: \n\n";

                int maps = 1;
                while(maps <= numberMaps)
                {
                    chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
                    chrono::steady_clock::time_point end = std::chrono::steady_clock::now();;  

                    vector<IndividualTM> population;

                    cout << "\nGenerating map " << maps << "...";
                    outputFile << "Map " << maps << ": ";

                    for(int i = 0; i < popSize; i++)
                    {
                        population.push_back(IndividualTM());
                        shuffleTM(population.back());
                        mapTM.setValues(population.back().types);
                        population.back().value = mapTM.getResult();
                    }
                    heapSortTM(population);
                    outputFile << "\n   (" << population[0].value << ", 0, "
                            << (chrono::duration_cast<chrono::microseconds>(end - begin).count()) /1000000.0 << "s)";
                    
                    int oldScore = population[0].value;
                    int count = 0;
                    while(population[0].value > 0 && (chrono::duration_cast<chrono::microseconds>(end - begin).count())/1000000.0 < 300)
                    {
                        count++;
                        for(int i = elite; i < popSize; i++)
                        {
                            if(i < mutation)
                            {
                                matchingTM(population[i], population[rand()%elite]);
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
                        heapSortTM(population);
                        end = std::chrono::steady_clock::now();
                        if(oldScore > population[0].value){
                            oldScore = population[0].value;
                            outputFile << "\n   (" << oldScore << ", " << count << ", "
                                << (chrono::duration_cast<chrono::microseconds>(end - begin).count()) /1000000.0 << "s)";
                        }
                    }
                    if(maps > 1){
                        if(population[0].value < bestScore.value){
                            bestScore = population[0];
                        }
                    }else bestScore = population[0];

                    maps++;
                    end = std::chrono::steady_clock::now();
                    avrgTime += chrono::duration_cast<chrono::microseconds>(end - begin).count() /1000000.0; 
                    outputFile << "\n\n[Points: " << population[0].value << " | Generation: " << count << " | "
                        << "Time: " << (chrono::duration_cast<chrono::microseconds>(end - begin).count()) /1000000.0  <<"s]\n\n";

                }
                
                outputFile << "\nBest map: \n\n";
                for(int i = 0; i < bestScore.types.size(); i++){
                    if(i == 13 || i == 38 || i == 63 || i == 88) outputFile << "\n  ";
                    if(i == 25 || i == 50 || i == 75 || i == 100) outputFile << "\n";
                    if(bestScore.types[i] == 8) outputFile << "  *  ";
                    else outputFile << " [" << bestScore.types[i] << "] ";
                }

                outputFile << '\n';           
                outputFile << "\nPointuation: " << bestScore.value;
                outputFile << "\nTempo medio: " << avrgTime/numberMaps;

                outputFile.close();
                cout << "Map created";

            }else cout << "Failed to create the file";
        }
    }
    return 0;
};