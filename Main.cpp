// Tervetuloa hotellihuoneen varausjärjestelmän taakse!


#include <iostream>
#include <stdlib.h>
#include <string>
#include <random>
#include <chrono>
#include <thread>

const float hinta_yksi{ 100 };
const float hinta_kaksi{ 150 };
const int alenolla{ 0 };
const int alekymppi{ 10 };
const int aletokakymppi{ 20 };
const float falenolla{ 1 };
const float falekymppi{ 0.90 };
const float faletokakymppi{ 0.80 };
using namespace std;

//Aliohjelma, joka tulostaa satunnaisen määrän huoneita välillä 40-300 ja tarkastaa onko luku parillinen.
int huoneet()
{
    int randomroom;

    srand(time(0));

    randomroom = rand() % 260 + 40;

    while (randomroom % 2 != 0)
    {
        randomroom = rand() % 260 + 40;
    }

    return randomroom;
}

//Aliohjelma joka tarkastaa onko käyttäjän syöte sopiva (int) ja jos ei ole, vaatii uutta.

int validInput()
{
    int x;
    std::cin >> x;
    while (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Virhe syotteessa. Syota NUMERO: ";
        std::cin >> x;
    }
    return x;
}


int main() {

    //Määritellään hotellihuoneiden varausjärjestelmään tarvittavat muuttujat.

    int one_room_amount{ 0 },
        two_room_amount{ 0 },
        taken_one_amount{ 0 },
        taken_two_amount{ 0 },
        night_amount{ 0 },
        room_number{ 0 };

    //Tämä muuttuja pitää ohjelman "pää" while loopin päällä. (Pakko olla "true" ohjelman alussa.)
        
    bool varausProcess{ true };

    float final { 0 };

    std::vector<int> one_room_viktor{};
    std::vector<int> two_room_viktor{};

    //Lasketaan huoneiden määrä ja asetaan niille const, johon voi vertailla huonneiden uutta määrää.

    int size_room = huoneet();
    int size_one_room = size_room / 2;
    int size_two_room = size_one_room;

    const int size_one_room_ref = size_one_room;
    const int size_two_room_ref = size_two_room;
    const int size_one_room_ref_plus = size_one_room_ref + 1; //Tämä on tärkeää, koska huoneiden kahtia jako jättäisi muuten yhden huoneen likaa.


    //Kysytään käyttäjältä ensimmäiseksi haluuako hän varata huoneen.


        std::cout << "Tervetuloa Taikaranta Hotelliin! \n";
        std::cout << "Haluaisitko varata huoneen? (y=1/n=0)";
        int yesno = validInput();

        if (yesno == 0) {
            std::cout << "Selvä! Ensikerralla sitten.";
            varausProcess = false;
            return 0;
        }

        //Kysytään seuraavaksi haluuako käyttäjä varata lisää jommankumman tyypin huoneita vai mennä suoraan öiden varaamiseen.
        else if (yesno == 1) {
            while (varausProcess == true) {
                start:
                    cout << "Haluatteko varata yhden vai kahden hengen huoneen? (Yhden hengen = 1, Kahden hengen = 2, Siirry öiden määrän valitsemiseen = 3) \n";
                    int ukskaks = validInput();

                    if (ukskaks == 1) {

                        //Tarkistetaan että huoneita on varmasti varattavissa
                        if (size_one_room < 1) {
                            cout << "Yhden hengen huoneita ei ole enää valitettavasti tarjolla.";
                        }
                        //Jos huoneita on saatavilla ohjelma antaa käyttäjän syöttää haluamansa huonenumeron ja se tallennetaan vektoriin, joka tarkistaa onko huonenumeroa jo tallennettu.
                        else {
                            cout << "Minkä huonenumeron haluatte huoneelleenne? \n";
                            cout << "1-" << size_one_room_ref << endl;


                            cout << ": ";
                            room_number = validInput();

                            check1:
                            if ((room_number < 1) || (room_number > size_one_room_ref)) {
                                while ((room_number < 1) || (room_number > size_one_room_ref)) {
                                    cout << "Syöte ei kelpaa: \n";
                                    room_number = validInput();
                                    goto check1;
                                }
                            }

                            else {

                                if (std::find(one_room_viktor.begin(), one_room_viktor.end(), room_number) != one_room_viktor.end()) {
                                    cout << "Huone on jo varattu, valitse toinen huone. \n";
                                }

                                else {
                                    one_room_viktor.push_back(room_number);
                                    size_one_room--;
                                    taken_one_amount++;
                                }
                            }
                        }

                    }

                    else if (ukskaks == 2) {
                        if (size_two_room < 1) {
                            cout << "Kahden hengen huoneita ei ole enää valitettavasti tarjolla.";
                        }
                        else {
                            cout << "Minkä huonenumeron haluatte huoneelleenne? \n";
                            cout << size_one_room_ref + 1 << "-" << size_two_room_ref + size_one_room_ref << endl;
                            cout << ": ";
                            room_number = validInput();

                            check2:
                            if ((room_number < size_one_room_ref) || (room_number > (size_two_room_ref + size_one_room_ref))) {
                                while ((room_number < size_one_room_ref_plus) || (room_number > size_two_room_ref)) {
                                    cout << "Syöte ei kelpaa: \n";
                                    room_number = validInput();
                                    goto check2;
                                }
                            }
                            else {
                                if (std::find(two_room_viktor.begin(), two_room_viktor.end(), room_number) != two_room_viktor.end()) {
                                cout << "Huone on jo varattu, valitse toinen huone. \n";
                                }

                                else {
                                   two_room_viktor.push_back(room_number);
                                    size_two_room--;
                                    taken_two_amount++;
                                }
                            }
                        }
                    }

                    //Ohjelma kysyy kuinka kauan käyttäjä aikoo yöpyä 
                    else if (ukskaks == 3) {
                        cout << "Kuinka monta päivää haluatte majoittautua? :  ";
                        night_amount = validInput();

                        //ohjelma antaa satunnaisen numeron 0-2 välillä jonka avulla arvotaan alennuksen määrän.
                        srand(time(0));
                        int lolexdee = rand() % 3;
                        float salepercent{ 0 };

                        switch (lolexdee) {
                        case 0:
                            lolexdee = alenolla;
                            salepercent = falenolla;
                            break;
                        case 1:
                            lolexdee = alekymppi;
                            salepercent = falekymppi;
                            break;
                        case 2:
                            lolexdee = aletokakymppi;
                            salepercent = faletokakymppi;
                            break;
                        }

                        float final_one_room = hinta_yksi * taken_one_amount;
                        float final_two_room = hinta_kaksi * taken_two_amount;
                        final = final_two_room + final_one_room;
                        final = final * night_amount;
                        final = final * salepercent;

                        cout << "Varauksenne hinta " << final << " euroa." << endl;
                        system("pause");
                        return 0;


                    }

                    else {
                        cout << "Syötteessänne on vikaa. \n";
                        goto start;
                    }



            }


        }

        else {
            cout << "Syötteessänne on vikaa. \n";
        }


    return 0;
}
