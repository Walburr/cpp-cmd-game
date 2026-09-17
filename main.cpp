// librairies
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <ctime>
#include <random>
#include <limits>



// ligne de code pour éviter std
using namespace std;

int rng(int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return std::uniform_int_distribution<>(min, max)(gen);
}

// Structure regroupant les stats générées aléatoirement (joueur et ennemi)



// Variables globales représentant l'état du jeu
bool startingGame = true;
bool fightEnd = false;
bool fightWin;
bool EnermieTurn = false;

char repAvencement;
char fightRep;


int Lvl = 1;

int xp = 0;
int xpMax = 40*Lvl;

//int xpgain = rand() % (21 - 10) + 10; 

int avancement =0;
int AvancerRep;

//int randomEnemie  = rand() % 3;
//int enemieLife = rand() % (50+1)*Lvl;
//int enemieAtk = rand() % (8+1*Lvl);

//int atk = rand() % (8)*(Lvl*0.5)+1;
//int esquive  = rand() % (8)+1;
int repEsquive;
int pvMax = 25+Lvl;
int pvCourants = 26;




struct Gamedonnée {

    // xp rand var
    int xpgain = 0;

    //player ability var
    int heal = 0; 
    int atk = 0;
    int esquive  = 0;

    //enemie random var
    int randomEnemie ;
    int enemieLife = 0;
    int enemieAtk = 0;

    void refreshAll() {

        //ability var refresh
        esquive = rng(0, 8);
        heal = rng(1, 8)*(Lvl*0.5)+1;
        atk = rng(0, 8)*(Lvl*0.5);

        //enemie  var refresh
        enemieLife = rng(1,  50)+10*(Lvl-1);
        enemieAtk = rng(0, 7)+1*Lvl;
        randomEnemie = rng(1,2);

        //xp var refresh
        xpgain = rng(20, 40)/max(1, Lvl/2);
    }
};

Gamedonnée donnée;

void allPv() {
    if (pvCourants > pvMax) pvCourants = pvMax;
}
void EnemiPv() {
    if (donnée.enemieLife <= 0) donnée.enemieLife = rand() % (50)*Lvl+1;
}
void EnemieTour() {
    EnemiPv();
    while (EnermieTurn) {
        cout << "\n\n\n\n";
        if (pvCourants <= 0) {
                cout << "Vous avez perdu \n"; 
                startingGame = false;
                fightEnd = true;
                fightWin = false;
                cout << endl;
        }
        cout << "C'est maintenant le tour de l'énemie , il va attaquer , vous avez " << pvCourants <<"pv \n";
        cout << "\n\n\n\n";
        donnée.esquive = rng(1, 8);
        cout << "Tu peux avoir la chance d'ésquiver l'attaque , choisi un nombre entre 1 et 8 \n ";
        
        if (!(cin >> repEsquive)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        if (repEsquive == donnée.esquive) {
        cout << "\n\n\n\n";
            cout << "Bravo vous avez esquivez !\n";
            cout << "\n\n\n\n";
            cout << endl;
            EnermieTurn = false;
        } else if (repEsquive != donnée.esquive) {
            cout << "Vous vous prennez le coup de plein fouet \n";
            sleep(2);
            pvCourants = pvCourants-donnée.enemieAtk;
            cout << "\n\n\n\n";
            cout << "Vous avez maintenant " << pvCourants << " pv \n";
            cout << endl;
            EnermieTurn = false;
            
            if (pvCourants <= 0) {
                cout << "Vous avez perdu \n"; 
                startingGame = false;
                fightEnd = true;
                fightWin = false;
                EnermieTurn = false;
                cout << endl;
            }
        } else if (!isdigit( repEsquive) && repEsquive > 8){
            cout << "Veuillez rentrer une valeur comprise entre 1 et 8 \n";
            cout << "\n\n\n\n";
            EnemieTour();
        } else { cout << "Entrée invalide.\n"; EnemieTour(); }
    }

    cout << endl;

}

void fight()
{

    srand(static_cast<unsigned int>(time(NULL)));
    fightEnd =false;
    system("clear");
    EnemiPv();
    cout << "La vie de l'énemie est de :" << donnée.enemieLife << " \n";

   
    cout << "\n\n\n\n";

    cout << "Vous entrez dans un combat avec un énemie dans quelques secondes \n";
    sleep(2);
    cout << "3\n";
    sleep(1);
    cout << "2\n";
    sleep(1);
    cout << "1\n";
    sleep(1);
    cout << "0";


    while (fightEnd == false) {

        cout << "\n\n\n\n";
        cout << "C'est mtn votre tour";
        cout << "\n\n\n\n";
        
        cout << "\n\n\n\n";
        cout << "Vous avez :" << pvCourants << " pv\n";

        cout << "\n\n\n\n";
        cout << "Voulez vous attaquer ou vous heal (a/h)\n";
        donnée.heal = rng(0, 8)*(Lvl*0.5);
        donnée.atk = rng(0, 8)*(Lvl*0.5);
        if (!(cin >> fightRep)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        if (fightRep == 'a') {
            
            cout << "\n\n\n\n";
            cout << "Vous avez décidé d'attaquer et vous infligez : " << donnée.atk << " dégâts";
            donnée.enemieLife  = donnée.enemieLife - donnée.atk ;
            
            cout << "\n\n\n\n";
            if (donnée.enemieLife <= 0 ) {
                fightEnd = true;
                fightWin =true;
                cout << "Bravo , vous avez vaincu l'énemie\n";
                donnée.enemieLife = rng(1,  50)+10*(Lvl-1);
                donnée.enemieAtk = rng(0, 7)+1*Lvl;
                donnée.randomEnemie = rng(0,3);;
                EnemiPv();
            } else {
                cout << "Il reste " << donnée.enemieLife << " pv à l'énemie";
            }
            if (!fightEnd) {
                EnermieTurn = true;
                EnemieTour();
            }

        } else if (fightRep =='h') {
            
            cout << "\n\n\n\n";
            // heal donc pvCourants plus heal 

            cout << "Vous vous êtes heal de : " << donnée.heal << " pv,\n ";
            pvCourants = pvCourants+donnée.heal;
            allPv();
            cout << "vous avez donc maintenant " << pvCourants<< " pv\n";
            EnermieTurn = true;
            EnemieTour();
        } else {
            system("clear");
            cout << "Veuillez rentrer une réponse entre a et h\n";
            
            cout << "\n\n\n\n";

            cout << "Vous êtes toujours dans un combat ";
        }
    }

    system("clear");
    
}


int main()
{

    donnée.refreshAll();
    cout << "\nBienvenue dans un monde inconnue ou le but est de rejoindre le chateux!\n";
    
    system("clear");
    
    while (startingGame)
    {

        // Le but du jeu est de progresser vers le château en choisissant d'avancer ou non, avec un risque de combat à chaque avancée

        
        cout << "\n\n\n\n";
        cout << "Vous avez " << pvCourants << " pv \n";

        
        cout << "\n\n\n\n";

        cout << "\nVoulez vous avancer ? (y/n) \n";

        if (!(cin >> repAvencement)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (repAvencement == 'y') {
            cout << "\n\n\n\n";
            donnée.randomEnemie = rng(1,2);
            cout << "Vous avez avancé, veuillez choisir un nombre entre 1 et 2 :\n";
            if (!(cin >> AvancerRep)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            if (AvancerRep > 2 || AvancerRep < 1){

                cout << "Veuillez rentrer une valeur compris entre 1 et 2 !\n";

            } else if (AvancerRep == donnée.randomEnemie) {
                fight();

                if (fightWin == false) {
                    cout << "Vous avez perdu !\n";
                    break;
                } else if (fightEnd) {
                    cout << "Vous avez gagné ! Bravo\n";
                    cout << "\n\n\n\n";
                    cout << "Vous avez gagné : " << donnée.xpgain << " Xp.\n";
                    xp = xp+donnée.xpgain;
                    if (xp >= xpMax) {
                        xp = 0;
                        Lvl++;
                        cout << "Vous avez gangé un niveau ,\n vous êtes maintenant niveau  " << Lvl ;
                    }
                    cout << "\n\n\n\n";
                    cout << "Vous avez maintenant " << xp << " xp";

                } else {
                    cout << "Erreur inattendue : état de jeu invalide.\n";
                    donnée.refreshAll();
                }

            } else if (AvancerRep != donnée.randomEnemie) {
                system("clear");
                cout << "Vous avez échapé à l'énemie ! \n";
                avancement++;
                cout << "\n\n\n\n";
                cout << "Vous avez avancé " << avancement << " fois, vous vous raprochez du chateaux\n";
                if (avancement == 15 ) {cout << "Bravo vous avez gagné le jeux , vous avez survécu jusqu'au chateaux\n"  ;
                donnée.refreshAll();
                break;
                }
            }

        } else if(repAvencement == 'n') {
            system("clear");
            cout << "Vous regardez le ciel un instant.\n";
            sleep(3);
            cout << "\n\n\n\n";
        }
    }


    return 0;
}
