#include <iostream>
#include <fstream>
#include <limits>
#include <cctype>

using namespace std;

const int VISINA = 10;
const int SIRINA = 21;

char labirint[VISINA][SIRINA + 1] = {
    "# # # # # # # # # # #",
    "# P   #           C #",
    "#     #   #     # # #",
    "#   # #   # # # #   #",
    "#   #           #   #",
    "#   # # # #     #   #",
    "#         #         #",
    "# # # #   #   # #   #",
    "#             # #   #",
    "# # # # # # # # # # #"
};

struct Igrac {
    int x;
    int y;
    int koraci = 0;
    int bodovi = 0;
};

Igrac igrac;

void prikaziNaslov() {
cout << "   .----------------.  .----------------.  .----------------.  .----------------.  .----------------.  .----------------.  .-----------------. .----------------.   " << endl;
cout << "   | .--------------. || .--------------. || .--------------. || .--------------. || .--------------. || .--------------. || .--------------. || .--------------. | " << endl;
cout << "   |     _____      | || |      __      | || |   ______     | || |     _____    | || |  _______     | || |     _____    | || | ____  _____  | || |  _________   | | " << endl;
cout << "   | |  |_   _|     | || |     /  \\     | || |  |_   _ \\    | || |    |_   _|   | || | |_   __ \\    | || |    |_   _|   | || ||_   \\|_   _| | || | |  _   _  |  | | " << endl;
cout << "   | |    | |       | || |    / /\\ \\    | || |    | |_) |   | || |      | |     | || |   | |__) |   | || |      | |     | || |  |   \\ | |   | || | |_/ | | \\_|  | | " << endl;
cout << "   | |    | |   _   | || |   / ____ \\   | || |    |  __'.   | || |      | |     | || |   |  __ /    | || |      | |     | || |  | |\\ \\| |   | || |     | |      | | " << endl;
cout << "   | |   _| |__/ |  | || | _/ /    \\ \\_ | || |   _| |__) |  | || |     _| |_    | || |  _| |  \\ \\_  | || |     _| |_    | || | _| |_\\   |_  | || |    _| |_     | | " << endl;
cout << "   | |  |________|  | || ||____|  |____|| || |  |_______/   | || |    |_____|   | || | |____| |___| | || |    |_____|   | || ||_____|\\____| | || |   |_____|    | | " << endl;
cout << "   | |              | || |              | || |              | || |              | || |              | || |              | || |              | || |              | | " << endl;
cout << "   | '--------------' || '--------------' || '--------------' || '--------------' || '--------------' || '--------------' || '--------------' || '--------------' | " << endl;
cout << "    '----------------'  '----------------'  '----------------'  '----------------'  '----------------'  '----------------'  '----------------'  '----------------'  " << endl;


}

void prikaziLabirint()
{
    system("clear"); 
    prikaziNaslov();
    for (int i = 0; i < VISINA; i++) {
        cout << labirint[i] << endl;
    }
}

void prikaziStatistiku() {
    cout << "\nKoraci: " << igrac.koraci;
    cout << " | Bodovi: " << igrac.bodovi << endl;
}

void spremiRezultat() {
    // Tekstualna
    ofstream txt("rezultati.txt", ios::app);
    if (txt.is_open()) {
        txt << "Koraci: " << igrac.koraci << ", Bodovi: " << igrac.bodovi << endl;
        txt.close();
    }

    // Binarna
    ofstream bin("rezultati.bin", ios::binary | ios::app);
    if (bin.is_open()) {
        bin.write(reinterpret_cast<char*>(&igrac), sizeof(igrac));
        bin.close();
    }
}

void upute() {
    cout << "\nUPUTE:\n";
    cout << "Kreći se kroz lavirint pomoću tipki W A S D.\n";
    cout << "P je za pauzu.\n";
    cout << "Dođi do cilja (oznaka 'C').\n";
    cout << "Pritisni Enter za početak...\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void pauza() {
    cout << "\nIgra pauzirana. Pritisni Enter za nastavak...\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void pomakniIgraca(char unos) {
    int noviX = igrac.x;
    int noviY = igrac.y;

    if (unos == 'w') noviY--;
    else if (unos == 's') noviY++;
    else if (unos == 'a') noviX--;
    else if (unos == 'd') noviX++;

    if (labirint[noviY][noviX] != '#' && labirint[noviY][noviX] != '\0') {
        // Obriši staru poziciju
        labirint[igrac.y][igrac.x] = ' ';
        igrac.x = noviX;
        igrac.y = noviY;
        // Novi položaj
        labirint[igrac.y][igrac.x] = 'P';
        igrac.koraci++;
        igrac.bodovi += 10;
    }
}

bool provjeriCilj() {
    return labirint[igrac.y][igrac.x] == 'C';
}

int main() {
    // Postavi početnu poziciju igrača
    igrac.y = 1;
    igrac.x = 2;

    upute();

    while (true) {
        prikaziLabirint();
        prikaziStatistiku();

        if (labirint[igrac.y][igrac.x] == 'C') {
            cout << "\nČestitamo! Stigli ste do cilja!\n";
            spremiRezultat();
            break;
        }

        cout << "Unesi potez (W/A/S/D), P za pauzu: ";
        char unos;
        cin >> unos;
        unos = tolower(unos);

        if (unos == 'p') {
            pauza();
        } else {
            pomakniIgraca(unos);
        }
    }

    cout << "\nHvala na igranju!\n";
    return 0;
}
