#include <iostream>
#include <algorithm>
#include <random>


int Numerosyote(int low, int high){
    bool valid {false};
    while (!valid) {
        int input;
        std::cin >> input;
        if (std::cin.fail()){ // Koska syötettävä muuttuja tallennetaan int muuttujaan, niin jos syöte ei ole numero, cin.fail() palauttaa true
            std::cout << "Syote ei kelpaa, anna luku valilta " << low << " - " << high << "\n";
            std::cin.clear(); // Tyhjennetään cin virheellisestä syötteestä
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
} // Syötteentarkistus aliohjelma numeroille. Parametreina annetaan alaraja ja yläraja

int Generoi (int alaraja, int ylaraja) {
// Käytetään satunnaislukugeneraattorin "Siementämiseen"
    std::random_device rd;

// moottori joka tuottaa satunnaislukuja
    std::default_random_engine moottori(rd());

//Jakauma, joka tuottaa luvut alarajan ja ylärajan väliltä yhtä suurella todennäköisyydellä
    std::uniform_int_distribution<> aivo (alaraja,ylaraja);
    return aivo(moottori);
} // Satunnaislukugeneraattori, jolle annetaan alaraja ja yläraja parametreinä

void tyhjenna(int x = 10){
    for (int i = 0; i<x; i++){
        std::cout<<"\n";
    }
} // Aliohjelma, joka tyhjentää näytön tulostamalla parametrin verran tyhjiä rivejä


int main() {
    const int huoneetMinimi = 30; // Huoneiden alaraja generointia varten
    const int huoneetMaksimi = 70; // Huoneiden yläraja generointia varten
    bool Suorita = true; // Muuttuja, jolla ohjataan "pääsilmukkaa"
    bool varattu = true;
    const int huoneidenLKM {Generoi(huoneetMinimi,huoneetMaksimi)}; // Huoneiden lukumäärä generoidaan ja tallennetaan vakioksi
    int vapaat = huoneidenLKM; // Tällä muuttujalla pidetään kirjaa vapaista huoneista
    int Huoneet [huoneidenLKM]; // Taulukko, johon tallennetaan huoneiden varaus-status, 1 = vapaa, 0 = varattu
    int varattavaHuone; // Muuttuja, johon tallennetaan väliaikaisesti varausta varten huoneen numero
    std::fill_n(Huoneet,huoneidenLKM,1); // Täytetään "Huoneet" taulukko 1:llä, eli kaikki huoneet ovat aluksi vapaana
    int yoLKM {0}; // Muuttuja, johon tallennetaan väliaikaisesti varausta varten öiden lukumäärä
    int hinta {0}; // Muuttuja, johon tallennetaan huoneen hinta tilapäisesti aina varausta tehdessä
while (Suorita) {

    if (vapaat == 0) { // Jos vapaita huoneita ei ole, ohjelma lopetetaan
        std::cout << "Kaikki huoneet on varattu, tervetuloa uudelleen!\n";
        system("pause");
        Suorita = false;
        break;
    }

    std::cout << "Vapaiden huoneiden lukumaara: " << vapaat << "\n";

    std::cout<<"Mita haluat tehda? \n"
    <<"1. Varaa huone valitsemalla itse sen numero\n"
    <<"2. Anna meidan valita vapaa huone puolestasi.\n"
    <<"3. Poistu\n";


    // Käyttäjä valitsee toiminnon ja toimenpiteet suoritetaan switch-case rakenteella
    // Jokaisen syötteen yhteydessä tehdään tarkistus, että syöte on numero ja se on annetulla välillä

    // Case 1: Huoneen varaus siten, että käyttäjä itse valitsee numeron
    // Case 2: Huoneen varaus siten, että ohjelma valitsee numeron
    // Case 3: Ohjelman lopetus asettamalla Suorita = false

    switch(Numerosyote(1,3)) {
        case 1: {
            varattu = true;
            while(varattu) {
                std::cout << "Minka huoneen haluat varata? (Numero)\n";
                 varattavaHuone = Numerosyote(1, vapaat);
                  if (Huoneet[varattavaHuone - 1] == 1) { // Tarkistetaan onko huone varattu, jos ei, varataan huone. (Taulukon indeksi on aina yhtä pienempi kuin huoneen numero)
                    hinta = Generoi(80,100); // Huoneen hinnan genertointi aliohjelmaa käyttäen
                    std::cout << "Huone on vapaa, sen hinta on " << hinta << " euroa per yo.\n";
                    std::cout << "Monekstiko yoksi haluat varta huoneen? \n";
                    yoLKM = Numerosyote(1, 100); // Käyttäjä valitsee öiden määrän
                    std::cout << "Varauksen hinta on " << yoLKM * hinta << " euroa." << "\n";
                      system("pause");
                      tyhjenna();
                    vapaat = vapaat - 1; // Vähennetään vapaat huoneet muuttujasta yksi
                    Huoneet[varattavaHuone - 1] = 0; // Merkitään huone varatuksi "Huoneet" taulukkoon
                    varattu = false;
                } else {
                    std::cout<< "Huone on jo varattu. \n";
                }

            }
            break; // Palataan takaisin pääsilmukkaan
        }
        case 2: {
            while (varattu) { // Tällä silmukalla generoidaan huoneen numero, kunnes löytyy vapaa huone
                varattavaHuone = Generoi(1, vapaat);
                if (Huoneet[varattavaHuone - 1] == 1) {
                    varattu = false;
                }
            }
            hinta = Generoi(80, 100); // Huoneen hinnan genertointi aliohjelmaa käyttäen
            std::cout << "Varattavan huoneen numero on " << varattavaHuone
                      << " Ja sen hinta on " << hinta << " euroa.\n"
                      << "Moneksiko yoksi haluat varata huoneen?\n";
            yoLKM = Numerosyote(1, 100); // Käyttäjä valitsee öiden määrän
            std::cout << "Varauksen hinta on " << yoLKM * hinta << " euroa." << "\n";
            system("pause");
            tyhjenna(10);
            vapaat = vapaat - 1; // Vähennetään vapaat huoneet muuttujasta yksi
            Huoneet[varattavaHuone - 1] = 0; // Merkitään huone varatuksi "Huoneet" taulukkoon
            break; // Palataan takaisin pääsilmukkaan
        }

        case 3: {
            Suorita = false; // Ohjelman lopetus
            break;
        }
    }
}
    return 0;
}
