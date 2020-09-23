#include <string>
#include <fstream>
#include <iostream>
using namespace std;
 
//Programma van Yvo Hu en Wietske ...
//Laatste update 22-9-2020
//Gebruike compiler GNU g++
void split_getal(int i,ofstream& uitvoer)
{
    i > 9 ? split_getal(i / 10,uitvoer) : void();

    int getal = i % 10;
    uitvoer.put('0' + getal);
}

void encode(ifstream& invoer,ofstream& uitvoer)
{
    char letter = invoer.get();
    char vorige_letter = letter;
    while(!invoer.eof()){
        int count = 0;
        while(letter == vorige_letter){
            count++;
            letter = invoer.get();
        }
        if(vorige_letter == '\\'){
            uitvoer.put('\\');
            uitvoer.put('\\');
        }
        else if(vorige_letter >= int('0') && vorige_letter <= int('9')){
            uitvoer.put('\\');
            uitvoer.put(vorige_letter);
        }
        else if(vorige_letter == '\n'){
            for(int i = 0; i < count; i++){
                uitvoer.put(vorige_letter);
            }
        }
        else{
            uitvoer.put(vorige_letter);
        }
        if(count > 1 && vorige_letter != '\n'){
            split_getal(count,uitvoer);
        }
        vorige_letter = letter;
    }
    uitvoer.close();
}
int main()
{
    ifstream invoer;
    ofstream uitvoer;
    string invoernaam;
    string uitvoernaam;
    char keuze;
    int flag_invoer = 1;
    int flag_uitvoer = 1;
    int flag_keuze = 1;
    cout << "Wil je coderen(c) of decoderen?(d)" << endl;
    do{
        cin >> keuze;
        if(keuze == 'C' || keuze == 'c'){
            flag_keuze = 0;
        }
        else if(keuze == 'D' || keuze == 'd'){
            flag_keuze = 0;
        }
        else{
            cout << "Ongeldige invoer, probeer het opnieuw" << endl;
        }
    } while(flag_keuze);

    do{
        cout << "Wat is de naam van het invoerbestand?" << endl;
        cin >> invoernaam;
        invoer.open(invoernaam,ios::in);
        if(invoer.fail()){
            cerr << "Het openen van " << invoernaam << " is mislukt. Probeer het nogmaals" << endl;
        }
        else{
            flag_invoer = 0;
        }
    } while(flag_invoer);

    do{
        cout << "Wat is de naam van het uitvoerbestand?" << endl;
        cin >> uitvoernaam;
        uitvoer.open(uitvoernaam,ios::out);
        if(uitvoer.fail()){
            cerr << "Het openen van " << uitvoernaam << " is mislukt. Probeer het nogmaals" << endl;
        }
        else{
            flag_uitvoer = 0;
        }
    } while(flag_uitvoer);

    encode(invoer,uitvoer);

    system("pause");
    return 0;
}
