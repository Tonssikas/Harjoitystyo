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
    std::uniform_int_distribution aivo(alaraja, ylaraja); // vaatii c++20

    return aivo(moottori);
}




int main() {
    bool Suorita = true;
    const int huoneidenLKM {Generoi(30,70)};
    int vapaat = huoneidenLKM;
    int Huoneet [huoneidenLKM];
    std::fill_n(Huoneet,huoneidenLKM,1);
    int yoLKM {0};

while (Suorita) {
    std::cout << "Vapaiden huoneiden lukumaara: " << vapaat << "\n";

    std::cout<<"Mita haluat tehda? \n"
    <<"1. Varaa huone\n"
    <<"2. Poistu\n";

    switch(numberInput(1,2)) {
        case 1: {
            bool varattu = true;
            while(varattu) {
                std::cout << "Minka huoneen haluat varata? (Numero) ";
                int varattavaHuone = numberInput(1, 30);
                if (Huoneet[varattavaHuone - 1] == 1) {
                    std::cout << "Huone on vapaa, sen hinta on 100e per yo.\n";
                    std::cout << "Monekstiko yoksi haluat varta huoneen? ";
                    yoLKM = numberInput(1, 100);
                    std::cout << "\nVarauksen hinta on " << yoLKM * 100 << " euroa." << "\n";

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
            Suorita = false;
            break;
        }
    }
}
    return 0;
}
