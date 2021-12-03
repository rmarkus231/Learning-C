#include <iostream>
#include <string.h>
#include <windows.h>
#include <cstdio>
#include <time.h>
#include <stdlib.h>
#include <map>
#include <fstream>
#include <math.h>
#include <algorithm>
#include <ctime>

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
};

//for some reason player stats cant be modified from inside createplayer class
//class just so it'd be in one place
class modifyPlayer{
    public:
        int x = 100;
        string s;
        //by default input is not a valid string number to be converted
        bool notValid = true;
        string arr[101] = {};

        void gen_arr(){
            for(int i = 0;i < 101; i++){
                arr[i] = to_string(i);
                //cout << i << ",";
            }
            //cout << endl;
        }

        bool in_list(string arg){
            for(int i = 0; i < 101;i++){
                if(not arg.compare(arr[i])){
                    cout << "found in list" << endl;
                    return(true);
                }

            }
            cout << "not found in list" << endl;
            return(false);
        }

        int findDef(){
            WAIT;
            cout << "Sul on " << x << " skillpointi jagada" << endl;
            if(x != 0){
                cout << "Ma olen vist " << translate[statNames[0]] << " nii hea: " << endl;
                while(notValid){
                    cin >> s;
                    if(in_list(s)){
                        x = x - stoi(s);
                        return(stoi(s));
                    }
                    else{
                        WAIT;
                        cout << s << " ei ole sobiv sisestus." << endl << "Sisestage arv: " << endl;
                    }
                }
            }
            cout << "Ma ei olnud " << translate[statNames[0]] << "hea: " <<endl << "0" << endl;
            return(0);
        }

        int findStr(){
            WAIT;
            cout << "Sul on " << x << " skillpointi jagada" << endl;
            if(x != 0){
                cout << "Ma olen vist " << translate[statNames[1]] << " nii hea: " << endl;
                while(notValid){
                    cin >> s;
                    //cout << endl;
                    if(in_list(s)){
                        x = x - stoi(s);
                        return(stoi(s));
                    }
                    else{
                        WAIT;
                        cout << s << " ei ole sobiv sisestus." << endl << "Sisestage arv: " << endl;
                    }
                }
            }
            cout << "Ma ei olnud " << translate[statNames[1]] << "hea: " <<endl << "0" << endl;
            return(0);
        }

        int findMag(){
            WAIT;
            cout << "Sul on " << x << " skillpointi jagada" << endl;
            if(x != 0){
                cout << "Ma olen vist " << translate[statNames[2]] << " nii hea: " << endl;
                while(notValid){
                    cin >> s;
                    //cout << endl;
                    if(in_list(s)){
                        x = x - stoi(s);
                        return(stoi(s));
                    }
                    else{
                        WAIT;
                        cout << s << " ei ole sobiv sisestus." << endl << "Sisestage arv: " << endl;
                    }

                }

            }
            cout << "Ma ei olnud " << translate[statNames[2]] << "hea: " <<endl << "0" << endl;
            return(0);
        }

        int findPer(){
            if(x != 0){
                //clr();
                cout << "Ma olin "<< translate[statNames[3]] << " kindlasti nii hea: " << x << endl;
                return(x);
            }
            else if(x = 0){
                //clr();
                cout << "Ma " << translate[statNames[3]] << " ka ei osanud: \n0" << endl;
                return(0);
            }
            cout << "Error in assigning stats" << endl;
            return(0);
        }

        int findHp(int def, int str){
            int hp = 10 + round(sqrt(def + str));
            cout << "Sul on " << hp << " elu." << endl;
            return(hp);
        }
};

string loadSaves(string n){
    //cout << "In loadsave func." << endl;
    fstream data;
    string tempName = n;
    string line;
    string s;
    bool exists = false;
    int delim;

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
    //cout << n << endl;
    data.open(saves, std::ios::in | std::ios::out | std::ios::app);
    

    //cout << "debug 1" << endl;

    //while not end of file
    int sub;
    while(!data.eof() && not exists){
        getline(data,line);
        sub = line.find(",");
        string name = line.substr(0,sub);
        //cout << "name: " << name << endl;
        bool nn = not n.compare(name);
        ++lineCount;
        //cout << "lineCount: " << lineCount-1 <<endl;
        if(nn){
            exists = true;
        }
    }

    if (exists){
        //cout << "debug 2" << endl << "lineCount: " << lineCount << endl;
        WAIT;
        //skip lines to name
        for(int i = 0; i < lineCount; i++){
            getline(data,s);
            //cout << "s: " << s << endl << "lineCount: " << lineCount << endl;
        }
        //need to split by multiple delimiters, perhaps reassigning starter string with removed previous split part
        
        cout << "Salvestatud karakteristest leiti "<< n << endl;
        WAIT;
        return (line);
    }
    //cout << "Returning false" << endl;
    //returns impossible text
    return("!=\")#(¤/%&1784217&/%¤#(&¤&#)&hjnfi&/(¤nhg//%(bhdeokfn&/(654(()/%#");
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
        int PERdam = 0;
        int stats[3] = {STRdam,MAGdam,PERdam};

        int wepNum(){
            bool w1 = not name.compare("pyss");
            bool w2 = not name.compare("oda");
            bool w3 = not name.compare("kepp");

            if(w1){
                return(0);
            }
            else if(w2){
                return(1);
            }
            else if(w3){
                return(2);
            }
            else{
                //this will never happen
                return(3);
            }
        }

        void updateWEPStats(){
            stats[0] = STRdam;
            stats[1] = MAGdam;
            stats[2] = PERdam;
        }

        void createWEP(string n = "weapon name",int s = 0, int m = 0, int r = 0){
            name = n;
            STRdam = s;
            MAGdam = m;
            PERdam = r;
        }

        void printWEPStats(){
            cout << "relv: " << name << endl;
            cout << "Strength damage: " << STRdam << endl;
            cout << "Magic damage: " << MAGdam << endl;
            cout << "Ranged damage: " << PERdam << endl;
        }
};

string chooseWeapon(){
    clr();
    cout << "Sinu ees on kolm relva..." << endl;
    WAIT;
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
            //playerWeapon.createWEP("oda",100,10,0);
            WAIT;
            cout << "Valisid oda." << endl;
            WAIT;
            //playerWeapon.printWEPStats();
            //playerWeapon.updateWEPStats();
            wrong = false;
            return("oda,100,10,0,");
        }
        else if(w2){
            //playerWeapon.createWEP("kepp",0,100,10);
            WAIT;
            cout << "Valisid keppi." << endl;
            WAIT;
            //playerWeapon.printWEPStats();
            //playerWeapon.updateWEPStats();
            wrong = false;
            return("kepp,0,100,10,");
        }
        else if(w3){
            //playerWeapon.createWEP("pyss",10,0,100);
            WAIT;
            cout << "Valisid pyssi." << endl;
            WAIT;
            //playerWeapon.printWEPStats();
            //playerWeapon.updateWEPStats();
            wrong = false;
            return("pyss,10,0,100,");
        }
        else {
            cout << "Vale valik!!!" << endl;
        }
    }
    return("");
}

void stop(){
    t = 100000;
    WAIT;
}

//***************************************************************************//

string createCharacter(){
    cout << "Mu nimi oli vist: " << endl;
    string name;
    getline(cin,name);
    string rtrn = loadSaves(name);
    int idef;
    int istr;
    int imag;
    int iper;
    int ihp;
    bool check = rtrn.compare("!=\")#(¤/%&1784217&/%¤#(&¤&#)&hjnfi&/(¤nhg//%(bhdeokfn&/(654(()/%#");
    if (check){
        //if was found in saves
        WAIT;

        return("%s,%i",0,rtrn);
    }
    else{
        WAIT;
        //cout << "debug 2" << endl;
        modifyPlayer PlayerStats;

        PlayerStats.gen_arr();
        //set skills

        idef = PlayerStats.findDef();
        istr = PlayerStats.findStr();
        imag = PlayerStats.findMag();
        iper = PlayerStats.findPer();
        ihp = PlayerStats.findHp(idef,istr);

        return("%s,%i,%i,%i,%i,%i,%i",1,ihp,iper,imag,istr,idef,name);
    }

}

bool ToF(){
    srand((unsigned) time(0));
    bool tf = (rand() % 2);
    return(tf);
}

int enemyDam(int num){
    srand((unsigned) time(0));
    int dam = (rand() % num);
    return(dam);
}

int playerDamage(int wep, int pStr, int pMag, int pPer, int wStr, int wMag, int wPer){
    //0 = püss
    //1 = oda
    //2 = kepp

    srand((unsigned) time(0));
    if(wep = 0){
        int damage = pPer/10+wPer+(rand() % 4) - 10;
        return(damage);
    }
    else if(wep = 1){
        int damage = pStr/10+wStr+(rand() % 4) - 10;
        return(damage);
    }
    else if(wep = 2){
        int damage = pMag/10+wMag+(rand() % 4) - 10;
        return(damage);
    }
    return(0);

}

int Lammas_fight(int lDef, int lStr, int lMag, int lPer, int lHp, int pDef, int pStr, int pMag, int pPer, int pHp, int wep, int wStr, int wMag, int wPer){
    int score = 0;

    cout << "Sinu ette astub vihane lammas. " << endl;

    //defence is basically % damage reduction
    //while neither are dead
    while (pHp > 0 and lHp > 0){
        WAIT;
        int x = round((3 + enemyDam(3)) - (3 + enemyDam(3)) * (1-(pDef/100)));     //def is 0.sth or 1
        //ToF is 50 / 50 roll
        if(ToF()){
            cout << "Lammas ründab sind ennem ja lööb sind peaga ning teeb sulle " << x << " HP viga" << endl;
            WAIT;
        }
        else{
            cout << "Lammas lööb sind tagajalgadega ning teeb sulle " << x << " HP viga" << endl;
            WAIT;
        }
        pHp = pHp - x;
        score = score - x*10;

        cout << "Sul on " << pHp << " elu";

        int y = round(playerDamage(wep,pStr,pMag,pPer,wStr,wMag,wPer) * (1-(lDef/100)));
        if (wep = 0){
            if(ToF){
                cout << "Sa lased lammast püssiga ning teed talle " << y << " HP viga" << endl;
            }
            else{
                cout << "Lööd lammast püssiga ning teed talle " << y << " HP viga" << endl;
            }
        }
        else if(wep = 1){
            if(ToF()){
                cout << "Sa torkad lammast odaga ning teed talle " << y << " Hp viga" << endl;
            }
            else{
                cout << "Sa vehid odaga lamba suunas tehes talle " << y << " HP viga" << endl;
            }
        }
        else if(wep = 2){
            if(ToF()){
                cout << "Sa viibutad keppi õhus ning teed lambale " << y << " HP viga" << endl;
            }
            else{
                cout << "Lööd lambale keppiga vastu pead ning teed talle " << y << " HP viga" << endl;
            }
        }
        else{
            //something broke
            cout << "Sorry, something went wrong!" << endl;
            return (2147483648);
        }
        lHp = lHp - y;
        cout << "Lambal on " << lHp << " elu" << endl;
    }
    if(pHp = 0){
        cout << "Ma ei tea kuidas sa selle kaotasid..." << endl;
    }
    else{
        cout << "Sa võitsid!" << endl;
    }
    return(score);
}


void prolog(){
    cout << "Sa ärkad alasti keset ristteed ning ei mäleta kes sa oled." << endl;
    WAIT;
    cout << "Põhja poole on mets kus on pimedam ja puud on kiduramad." << endl;
    WAIT;
    cout << "Ida poole on kanakuut, täiesti tavaline kanakuut..." << endl;
    WAIT;
    cout << "Lõuna poole on mahajäetud saeveski." << endl;
    WAIT;
    cout << "Lääne poole on kõrts." << endl;
    WAIT;
    cout << "Aga ennem... kes sa oled?" << endl;
    WAIT;
}

//have to break down the return because class object hasto be constructed in the main loop

int main() {
    createEnemy Lammas;
    Lammas.createEN("Lammas",20,50,10,10,20);

    string y;
    cout << "Soovite m2ngida? (jah/ei)";
    cin >> y;
    bool b_y1 = not y.compare("jah");
    bool b_y2 = not y.compare("Jah");
    bool b_y3 = not y.compare("JAH");
    WAIT;

    string speed;
    cout << "Dialoogi kiirus: (kiire/keskmine/aeglane)" << endl;
    cin >> speed;

    bool s1 = not speed.compare("kiire");
    bool s2 = not speed.compare("keskmine");
    bool s3 = not speed.compare("aeglane");

    //speed is in ms
    if(s1){
        t = 0;
    }
    else if(s2){
        t = 1000;
    }
    else if(s3){
        t = 2000;
    }
    else{
        t = 1000;
        cout << "Vastus oli sobimatu, seatud keskmiseks.";
    }

    if(b_y1 || b_y2 || b_y3){

        prolog();

        int idef;
        int istr;
        int imag;
        int iper;
        int ihp;
        int iloaded;
        bool bloaded;

        string def;
        string str;
        string mag;
        string per;
        string hp;
        string name;
        string saveState;
        string loaded;

        string rtrn = createCharacter();

        int sub = rtrn.find(",");
        name = rtrn.substr(0,sub);
        rtrn.replace(0,sub+1,"");

        sub = rtrn.find(",");
        def = rtrn.substr(0,sub);
        rtrn.replace(0,sub+1,"");

        sub = rtrn.find(",");
        str = rtrn.substr(0,sub);
        rtrn.replace(0,sub+1,"");

        sub = rtrn.find(",");
        mag = rtrn.substr(0,sub);
        rtrn.replace(0,sub+1,"");

        sub = rtrn.find(",");
        per = rtrn.substr(0,sub);
        rtrn.replace(0,sub+1,"");

        sub = rtrn.find(",");
        hp = rtrn.substr(0,sub);
        rtrn.replace(0,sub+1,"");

        //sub = rtrn.find(",");
        loaded = rtrn.substr(0,1);
        //rtrn.replace(0,sub+1,"");
        
        idef = stoi(def);
        istr = stoi(str);
        imag = stoi(mag);
        iper = stoi(per);
        ihp = stoi(hp);

        // 0 = loaded, 1 = not loaded from save
        iloaded = stoi(loaded);
        bloaded = !!iloaded;

        createPlayer Player;
        Player.createPLAYER(name,idef,istr,imag,iper,ihp);
        Player.showPLAYERStatsPrint();
        WAIT;

        if(not bloaded){
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

                //cout << Player.name << Player.defence << Player.strength << Player.magic << Player.perception << Player.health << endl;

                saveChar(Player.name, Player.stats[0], Player.stats[1], Player.stats[2], Player.stats[3], Player.stats[4]);
                WAIT;
            }
            else{
                cout << "Tegelast ei salvestatud." << endl;
            }
        }

        //choose weapon sequence, creating weapon obj inside main loop
        string wep_rtrn = chooseWeapon();

        int istrDam;
        int imagDam;
        int iperDam;


        sub = wep_rtrn.find(",");
        string wepName = wep_rtrn.substr(0,sub);
        wep_rtrn.replace(0,sub+1,"");

        sub = wep_rtrn.find(",");
        string strDam = wep_rtrn.substr(0,sub);
        wep_rtrn.replace(0,sub+1,"");

        sub = wep_rtrn.find(",");
        string magDam = wep_rtrn.substr(0,sub);
        wep_rtrn.replace(0,sub+1,"");

        sub = wep_rtrn.find(",");
        string perDam = wep_rtrn.substr(0,sub);
        //wep_rtrn.replace(0,sub+1,"");
        
        istrDam = stoi(strDam);
        imagDam = stoi(magDam);
        iperDam = stoi(perDam);

        createWeapon playerWeapon;
        playerWeapon.createWEP(name,istrDam,imagDam,iperDam);
        playerWeapon.updateWEPStats();
        //int lDef, int lStr, int lMag, int lPer, int lHp, int pDef, int pStr, int pMag, int pPer, int pHp, int wep, int wStr, int wMag, int wPer

        Lammas_fight(Lammas.defence,Lammas.strength,Lammas.magic,Lammas.perception,Lammas.health,Player.defence,Player.strength,
                        Player.magic,Player.perception,Player.health,playerWeapon.wepNum(),playerWeapon.STRdam,
                        playerWeapon.MAGdam,playerWeapon.PERdam);

        stop();
    }
}