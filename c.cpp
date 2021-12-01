#include <iostream>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <cstdio>
#include <time.h>
#include <stdlib.h>
#include <map>
#include <fstream>
#include <math.h>
#include <algorithm>
//#include <typeinfo>

using namespace std;

#define WAIT        \
do {                \
    Sleep(t);       \
} while (0)

const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
const COORD pos = {0, 0};
int t = 1000;
int skill[5] = {0,0,0,0,0};
//          def,str,mag,per,hp

const string saves = "saves.csv";
const string scores = "scores.csv";

const string statNames[4] = {"defence","strength","magic","perception"};

map <string, string> translate = {
    {"defence","kaitses"},
    {"strength","tugevuses"},
    {"magic","maagias"},
    {"perception","laskmises"},
    {"pyss","pyssiga"},
    {"oda","odaga"},
    {"kepp","keppiga"}
};


void saveChar(string n, int d, int s, int m, int p, int h){
    ofstream saveFile;
    saveFile.open(saves,fstream::app);
    replace(n.begin(),n.end(),' ','-');
    saveFile << n << "," << d << "," << s << "," << m << "," << p << "," << h << endl;;
    saveFile.close();
}

void clr(){
    string buffer;
    SetConsoleCursorPosition(hConsole, pos);
    for(int j = 0; j<30;j++){
        for(int i = 0;i<50;i++){
            buffer.append("        ");
        }
        buffer.append("\n");
    }
    cout << buffer;
    SetConsoleCursorPosition(hConsole, pos);
}

class createPlayer{
    public: 
        int defence = 0;
        int strength = 0;
        int magic = 0;
        int perception = 0;
        int health = 0;
        string name="Default name";
        int stats[5] = {defence,strength,magic,perception,health}; 
        
        
        void showPLAYERStatsPrint() {
            cout << "Name: " << name << "\n";
            cout << "defence: " << defence << "\n";
            cout << "strength: " << strength << "\n";
            cout << "magic: " << magic << "\n";
            cout << "perception: " << perception << "\n";
            cout << "hp: " << health << "\n";
        }

        void createPLAYER(string n = "nameError", int d = 0, int s = 0, int m = 0, int p = 0, int h = 0){
            //cout << "Creating player: debug" << endl;
            name = n;
            defence = d;
            strength = s;
            magic = m;
            perception = p;
            health = h;
            //cout << "Finished creating player: debug" << endl;
            updatePLAYERStats();
        }

        void updatePLAYERStats(){
            stats[0] = defence;
            stats[1] = strength;
            stats[2] = magic;
            stats[3] = perception;
            stats[4] = health;
        }

        void updateStatSheet(){
            defence = stats[0];
            strength = stats[1];
            magic = stats[2];
            perception = stats[3];
            health = stats[4];
        }

        void reskill(int num, int inew){
            if(num = 0){
                defence = inew;
            }
            else if(num = 1){
                strength = inew;
            }
            else if(num = 2){
                magic = inew;
            }
            else if(num = 3){
                perception = inew;
            }
            else if(num = 4){
                health = inew;
            }
        }

        void set_skill(){
            //cout << "in set skill func." << endl;
            int x = 100;
            string s;
        
            for(int i = 0; i < 3;i++){
                //s = "";
                WAIT;
                cout << "Sul on " << x << " skillpointi jagada" << endl;
                if(x != 0){
                    //WAIT;
                    cout << "Ma olen vist " << translate[statNames[i]] << " nii hea: " << endl;
                    cin >> s;
                    cout << endl;
                    //clr();
                    while (x < stoi(s)){
                        cout << "Peab olema väiksem kui olemasolevad punktid: "<< endl;
                        cin >> s;
                    }
                    x = x - stoi(s);
                    reskill(i,stoi(s));
                }
                else if (x = 0){
                    //WAIT;
                    //clr();
                    cout << "Ma " << translate[statNames[i]] << " yldse ei osanud: \n0" << endl;
                    reskill(i,0);
                WAIT;
                }
            }
            WAIT;
            if(x != 0){
                //clr();
                int skill4 = 100-defence-strength-magic;
                cout << "Ma olin "<< translate[statNames[3]] << " kindlasti nii hea: " << skill4 << endl;
                reskill(3,skill4);
            }
            else if(x = 0){
                //clr();
                cout << "Ma " << translate[statNames[4]] << " ka ei osanud: 0" << endl;
            }
            reskill(10, round(sqrt(skill[0] + skill[1])));
            updatePLAYERStats();
            cout << "stats: " << stats[0] << stats[1] << stats[2] << stats[3] << stats[4] << endl;
            WAIT;
            clr();
        }
};

//Something is broken in this loadsave func

bool loadSaves(string n){
    cout << "In loadsave func." << endl;
    fstream data;
    string tempName = n;
    string line;
    string s;
    bool exists = false;

    //skill variables to be used
    int idef;
    int istr;
    int imag;
    int iper;
    int ihp;

    string def;
    string str;
    string mag;
    string per;
    string hp;

    int lineCount = 0;
    replace(n.begin(),n.end(),' ','-');
    cout << n << endl;
    data.open(saves, std::ios::in | std::ios::out | std::ios::app);
    

    cout << "debug 1" << endl;

    //while not end of file
    while(!data.eof() && not exists){
        getline(data,line);
        ++lineCount;
        bool nn = not line.compare(n);
        if(nn){
            cout << "nn: " << nn <<endl;
            exists = true;
        }
    }

    if (exists){
        cout << "debug 2" << endl << "lineCount: " << lineCount << endl;
        //skip lines to name
        for(int i = 0; i < lineCount; i++){
            getline(data,s);
            cout << "s: " << s << endl << "lineCount: " << lineCount << endl;
        }
        getline(data,def);
        getline(data,str);
        getline(data,mag);
        getline(data,per);
        getline(data,hp);

        cout << "debug 3" << endl;

        cout << "def: " << stoi(def) << endl << "str: " << stoi(str) << endl << "mag: " << stoi(mag) << endl << "per: " << stoi(per) << endl << "hp: " << stoi(hp) << endl;

        idef = stoi(def);
        istr = stoi(str);
        imag = stoi(mag);
        iper = stoi(per);
        ihp = stoi(hp);

        cout << "Salvestatud karakteristest leiti "<< n << endl;
        createPlayer Player;
        Player.createPLAYER(tempName,idef,istr,imag,iper,ihp);
        return (true);
    }
    cout << "Returning false" << endl;
    return(false);
}

class createEnemy{
    public:
        int defence;
        int strength;
        int magic;
        int perception;
        int health;
        string name="Default enemy name";
        int stats[5] = {defence,strength,magic,perception,health}; 

        void updateENStats(){
            stats[0] = defence;
            stats[1] = strength;
            stats[2] = magic;
            stats[3] = perception;
            stats[4] = health;
        }

        void createEN(string n = "nameError", int d = 0, int s = 0, int m = 0, int p = 0, int h = 0){
             name = n;
             defence = d;
             strength = s;
             magic = m;
             perception = p;
             health = h;
             updateENStats();
        }

        void showENStatsPrint() {
            cout << "Name: " << name << "\n";
            cout << "defence: " << defence << "\n";
            cout << "strength: " << strength << "\n";
            cout << "magic: " << magic << "\n";
            cout << "perception: " << perception << "\n";
            cout << "hp: " << health << "\n";
        }
};

class createWeapon{
    public:
        string name = "weapon name";
        int STRdam = 0;
        int MAGdam = 0;
        int RANdam = 0;
        int stats[3] = {STRdam,MAGdam,RANdam};

        void updateWEPStats(){
            stats[0] = STRdam;
            stats[1] = MAGdam;
            stats[2] = RANdam;
        }

        void createWEP(string n = "weapon name",int s = 0, int m = 0, int r = 0){
            name = n;
            STRdam = s;
            MAGdam = m;
            RANdam = r;
        }

        void printWEPStats(){
            cout << "relv: " << name << endl;
            cout << "Strength damage: " << STRdam << endl;
            cout << "Magic damage: " << MAGdam << endl;
            cout << "Ranged damage: " << RANdam << endl;
        }
};

void chooseWeapon(){
    clr();
    cout << "Sinu ees on kolm relva..." << endl;
    WAIT;
    createWeapon playerWeapon;
    string weapon;
    cout << "Kas valid oda, keppi v6i pyssi" << endl;
    WAIT;
    cin >> weapon;
    //not is there because it returns the value difference of ascii char, if identical difference is 0, gets reversed to 1
    bool w1 = not weapon.compare("oda");
    bool w2 = not weapon.compare("keppi");
    bool w3 = not weapon.compare("pyssi");
    //cout << "w1: " << w1 << "\n" << "w2: " << w2 << "\n" << "w3: " << w3 << endl; 

    bool wrong = true;

    while(wrong){
        if(w1){
            playerWeapon.createWEP("oda",100,10,0);
            WAIT;
            cout << "Valisid oda." << endl;
            WAIT;
            clr();
            playerWeapon.printWEPStats();
            playerWeapon.updateWEPStats();
            wrong = false;
        }
        else if(w2){
            playerWeapon.createWEP("kepp",0,100,10);
            WAIT;
            cout << "Valisid keppi." << endl;
            WAIT;
            clr();
            playerWeapon.printWEPStats();
            playerWeapon.updateWEPStats();
            wrong = false;
        }
        else if(w3){
            playerWeapon.createWEP("pyss",10,0,100);
            WAIT;
            cout << "Valisid pyssi." << endl;
            WAIT;
            clr();
            playerWeapon.printWEPStats();
            playerWeapon.updateWEPStats();
            wrong = false;
        }
        else {
            cout << "Vale valik!!!" << endl;
        }
    }
}

void stop(){
    t = 100000;
    WAIT;
}

//***************************************************************************//

void createCharacter(){
    cout << "Mu nimi oli vist: " << endl;
    string name;
    getline(cin,name);
    bool rtrn = loadSaves(name);
    if (rtrn){
        //if was found in saves
        WAIT;
        cout << "found in saves, WIP" << endl;
    }
    else{
        WAIT;
        //cout << "debug 2" << endl;
        createPlayer Player;
        Player.createPLAYER(name);
        Player.set_skill();
        //cout << "set skills: debug" << endl;
        string saveState;

        WAIT;
        cout << "Kas soovite tegelase salvestada? (jah/ei): " << endl;
        cin >> saveState;

        //workaround for not being able to use or operator on string || char
        bool j1 = not saveState.compare("jah");
        bool j2 = not saveState.compare("JAH");
        bool j3 = not saveState.compare("Jah");

        //cout << "debug 3" << endl;

        if(j1 || j2 || j3){
            //char gets saved
            cout << "Tegelane salvestati." << endl;

            //Both of these giva name00000
            cout << Player.name << Player.stats[0] << Player.stats[1] << Player.stats[2] << Player.stats[3] << Player.stats[4] << endl;
            cout << Player.name << Player.defence << Player.strength << Player.magic << Player.perception << Player.health << endl;

            saveChar(Player.name, Player.stats[0], Player.stats[1], Player.stats[2], Player.stats[3], Player.stats[4]);
            WAIT;
        }
        else{
            cout << "Tegelast ei salvestatud." << endl;
        }
    }

}

//array decleration must be a constant
    //well no, under some circumstances
//its not printing the updated version of the array

int main() {
    bool playing = true;
    createCharacter();
    //Player.createPLAYER("Peeter",10,20,30,40,50);

    //while(playing){
        
        /*
        for (int i = 0; i < 5; i++){
            cout <<i <<":"<<Player.stats[i] << " ";
        }
        */

    chooseWeapon();

        //clr();

        
        //Player.showPLAYERStatsPrint();
    
    stop();
}