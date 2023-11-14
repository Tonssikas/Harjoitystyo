#include <iostream>
#include <algorithm>
#include <random>



int numberInput(int low, int high){
    bool valid {false};
    while (!valid) {
        int input;
        std::cin >> input;
        if (std::cin.fail()){
            std::cout << "Syote ei kelpaa, anna luku valilta " << low << " - " << high << "\n";
            std::cin.clear();
            std::cin.ignore(100, '\n');
            continue;
        }

        if (input >= low && input <= high){
            return input;
        }
        else {
            std::cout << "Luku ei kelpaa, syota luku valilta " << low << " - " << high << "\n";
            continue;
        }
    }
}

int Generoi (int alaraja, int ylaraja) {
// Käytetään satunnaislukugeneraattorin "Siementämiseen"
    std::random_device rd;

// moottori joka tuottaa satunnaislukuja
    std::default_random_engine moottori(rd());

//Jakauma, joka tuottaa luvut alarajan ja ylärajan väliltä yhtä suurella todennäköisyydellä
    std::uniform_int_distribution<> aivo (alaraja,ylaraja);
    return aivo(moottori);
}

void tyhjenna(int x = 10){
    for (int i = 0; i<x; i++){
        std::cout<<"\n";
    }
}


int main() {
    const int huoneetMinimi = 40;
    const int huoneetMaksimi = 70;
    bool Suorita = true;
    bool varattu = true;
    const int huoneidenLKM {Generoi(huoneetMinimi,huoneetMaksimi)};
    int vapaat = huoneidenLKM;
    int Huoneet [huoneidenLKM];
    int varattavaHuone;
    std::fill_n(Huoneet,huoneidenLKM,1);
    int yoLKM {0};
    int hinta {0};
while (Suorita) {
    std::cout << "Vapaiden huoneiden lukumaara: " << vapaat << "\n";

    std::cout<<"Mita haluat tehda? \n"
    <<"1. Varaa huone valitsemalla itse sen numero\n"
    <<"2. Anna meidan valita vapaa huone puolestasi.\n"
    <<"3. Poistu\n";

    switch(numberInput(1,2)) {
        case 1: {
            varattu = true;
            while(varattu) {
                std::cout << "Minka huoneen haluat varata? (Numero)\n";
                 varattavaHuone = numberInput(1, vapaat);
                  if (Huoneet[varattavaHuone - 1] == 1) {
                    hinta = Generoi(80,100);
                    std::cout << "Huone on vapaa, sen hinta on " << hinta << " euroa per yo.\n";
                    std::cout << "Monekstiko yoksi haluat varta huoneen? \n";
                    yoLKM = numberInput(1, 100);
                    std::cout << "Varauksen hinta on " << yoLKM * hinta << " euroa." << "\n";
                      tyhjenna();
                    vapaat = vapaat - 1;
                    Huoneet[varattavaHuone - 1] = 0;
                    varattu = false;
                } else {
                    std::cout<< "Huone on jo varattu. \n";
                }

            }
            break;
        }
        case 2: {
            while (varattu) {
                varattavaHuone = Generoi(1, vapaat);
                if (Huoneet[varattavaHuone - 1] == 1) {
                    varattu = false;
                }
            }
            hinta = Generoi(80, 100);
            std::cout << "Varattavan huoneen numero on " << varattavaHuone
                      << " Ja sen hinta on " << hinta << " euroa.\n"
                      << "Moneksiko yoksi haluat varata huoneen?\n";
            yoLKM = numberInput(1, 100);
            std::cout << "Varauksen hinta on " << yoLKM * hinta << " euroa." << "\n";
            tyhjenna(10);
            vapaat = vapaat - 1;
            Huoneet[varattavaHuone - 1] = 0;
            break;
        }

        case 3: {
            Suorita = false;
            break;
        }
    }
}
    return 0;
}
