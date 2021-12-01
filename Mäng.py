#mäng
#Richard Markus Tins
import time
import random

int time = 0

#scores ja saves faili loomine
save=open("saves.txt","a+")
scores=open("scores.txt","a+")
#faili salvestamise funktsioon
def check_saves(n=""):
    save=open("saves.txt","r")
    saves=save.readlines()
    n=n.replace(" ","-")
    for i in range(len(saves)):
        sn,sd,ss,sm,sp,hpp=saves[i].split(",")
        if sn == n:
            n=n.replace("-"," ")
            pl = createPlayer(sn,sd,ss,sm,sp,hpp)
            return pl
    return 0

#salvestab tegelase/skoor
def save_player(n="",d=0,s=0,m=0,p=0,hp=20):
    save=open("saves.txt","a+")
    nn=n.replace(" ","-")
    save.write(nn+","+str(d)+","+str(s)+","+str(m)+","+str(p)+","+str(hp)+"\n")
    return

def save_score(n,s):
    scores=open("scores.txt","a+")
    nn=n.replace(" ","-")
    scores.write(nn+","+str(s)+"\n")
    return

#kiire tõlke sõnastik
translate = {
    "defence":"Kaitses",
    "strength":"tugevuses",
    "magic":"maagias",
    "perception":"laskmises",
    "pyss":"püssiga",
    "oda":"odaga",
    "kepp":"keppiga",
}

stats=["defence","strength","magic","perception"]

#vaenlane
class createEnemy:
    name='teadmata'
    defence=0
    strength=0
    magic=0
    perception=0
    hp=20
    
    def __init__(self,n,d,s,m,p,hp):
        self.name=n
        self.defence=d
        self.strength=s
        self.magic=m
        self.perception=p
        self.hp

    def showStats(self):
        r=f"{self.name},{self.defence},{self.strength},{self.magic},{self.perception},{self.hp}"
        return r

lammas=createEnemy("lammas",20,50,10,10,20)

#tegelane
class createPlayer:
    #atribuudid
    name='teadmata'
    defence=0
    strength=0
    magic=0
    perception=0
    hp=20
    
    def __init__(self,n,d,s,m,p,hp):
        self.name=n
        self.defence=d
        self.strength=s
        self.magic=m
        self.perception=p
        self.hp=hp
    
    def showStatsPrint(self):
        print(f"\nTegelane: {self.name}")
        time.sleep(t)
        print(f"Kaitse: {self.defence}")
        time.sleep(t)
        print(f"Tugevus: {self.strength}")
        time.sleep(t)
        print(f"Maagia: {self.magic}")
        time.sleep(t)
        print(f"Täpsus: {self.perception}\n")
#        print('Nimi: {} \nKaitse: {} \nTugevus: {} \nMaagia: {} \nTäpsus: {}'.format(self.name, self.defence,self.strength,self.magic,self.perception))
        return
        
    def showStats(self):
        r=f"{self.name},{self.defence},{self.strength},{self.magic},{self.perception},{self.hp}"
        return r

#relva klass
class createWeapon:
    name='teadmata'
    magicDamage=0
    strengthDamage=0
    perceptionDamage=0
    
    def __init__(self,n,m,s,p):
        self.name=n
        self.magicDamage=m
        self.strengthDamage=s
        self.perceptionDamage=p
        
    def showStats(self):
        r=f"{self.name},{self.magicDamage},{self.strengthDamage},{self.perceptionDamage}"
        return r

#relva valimis funktsioon
def chooseWeapon():
    print("Sinu ees maas on kolm relva..")
    time.sleep(t)
    weapon=input("Millise relva valid? (pyss/oda/kepp): \n")
    time.sleep(t)
    if weapon == "pyss":
        print("Valisid pyssi\n")
        n="pyss"
        m=0
        s=10
        p=100
        return createWeapon(n,m,s,p)
    elif weapon == "oda":
        print("Valisid oda\n")
        n="oda"
        m=10
        s=100
        p=0
        return createWeapon(n,m,s,p)
    elif weapon == "kepp":
        print("valisid keppi\n")
        n="kepp"
        m=100
        s=0
        p=20
        return createWeapon(n,m,s,p)

#lollikindel skilli saamise funktsioon
def find_skill():
    skill=""
    x=100
    print(f"Sul on {x} skillpointi jagada")
    for i in range(len(stats)-1):
        if x != 0:
            j=input(f"Ma olin vist {translate[stats[i]]} nii hea: ")
            if x < int(j):
                while x < int(j):
                    j=input("Peab olema väiksem kui olemasolevad punktid: ")
                    if i !=2:
                        s=int(j)
                        s=str(s)+","
                    elif i ==2:
                        s=int(j)
                x=x-int(j)
                
            elif i != 2:
                x=x-int(j)
                s=int(j)
                s=str(s)+","
                
            elif i == 2:
                x=x-int(j)
                s=int(j)
                s=str(s)
            skill=skill+s
        else:
            if x == 0:
                print(f"Ma {translate[stats[i]]}t üldse ei osanud: 0")
                if i != 2:
                    s=0
                    s=str(s)+","
                elif i == 2:
                    s=0
                    s=str(s)
            skill=skill+s
        print(f"Sul on {x} skillpointi jagada")
        time.sleep(1)
    return skill

#tegelase loomise funktsioon      
def createCharacter():
    hp=20
    n=input("Mu nimi oli vist: ")
    if check_saves(n) != 0:
        print(f"Salvestatud karakteritest leiti {n}")
        return check_saves(n)
    else:
        
        d,s,m=find_skill().split(",")
        
        d=int(d)
        s=int(s)
        m=int(m)
        
        print(f"Ma olin {translate[stats[3]]} kindlasti nii hea: {100-d-s-m}")
        
        p=100-d-s-m
        
        sav=input("Kas soovite tegelase salvestada? (jah/ei)\n")
        if sav == "jah":
            save_player(n,d,s,m,p,hp)
        p = createPlayer(n,d,s,m,p,hp)
        return p

def whatWeapon(name):
    if name == "pyss":
        return 0
    if name == "oda":
        return 1
    if name == "kepp":
        return 2

def playerDamage(wep):
    player2=player.showStats()
    weapon2=weapon.showStats()
    playerName,playerDefence,playerStrength,playerMagic,playerPerception,playerHP=player2.split(",")
    weaponName,weaponMagic,weaponStrength,weaponPerception=weapon2.split(",")
    
    if wep==0:
        damage=int(playerPerception)/10+int(weaponPerception)/10+random.randint(0,4)-10
        return damage
    elif wep==1:
        damage=int(playerStrength)/10+int(weaponStrength)/10+random.randint(0,4)-10
        return damage
    elif wep==2:
        damage=int(playerStrength)/10+int(weaponStrength)/10+random.randint(0,4)-10
        return damage

def fightLammas():
    score=0
    
    enemy=lammas.showStats()
    playerr=player.showStats()
    weaponn=weapon.showStats()
    enemyName,enemyDefence,enemyStrength,enemyMagic,enemyPerception,enemyHP=enemy.split(",")
    playerName,playerDefence,playerStrength,playerMagic,playerPerception,playerHP=playerr.split(",")
    weaponName,weaponMagic,weaponStrength,weaponPerception=weaponn.split(",")
    
    enemyDamage1=random.randint(3,6)
    enemyDamage2=[]
    playerDamage2=[]
    print(f"Ette astub vihane lammas ")
    
    while int(playerHP) > 0 and int(enemyHP) > 0:
        time.sleep(t)
        wep=whatWeapon(weaponName)
        enemyDamage2.insert(0,enemyDamage1)
        playerHP=int(playerHP)-int((enemyDamage2[0]-enemyDamage2[0]/100*int(playerDefence)))
        x=int((enemyDamage2[0]-enemyDamage2[0]/100*int(playerDefence)))
        if random.randint(1,2)==1:
            print(f"lammas ründab sind ennem ja lööb sind peaga ning teeb sulle {x}HP viga")
            time.sleep(t)
        else:
            print(f"lammas lööb sind tagajalgadega ning teeb sulle {x}HP viga")
            time.sleep(t)
        score=score-x*10
        
        print(f"Sul on {playerHP} elu")

        playerDamage2.insert(0,playerDamage(wep))
        if wep == 0:
            if random.randint(1,2)==1:
                print(f"Sa lased lammast püssiga ning teed talle {playerDamage2[0]} HP viga")
            elif random.randint(1,2)==2:
                print(f"Lööd lammast püssiga ning teed talle {playerDamage2[0]} HP viga")
        elif wep == 1:
            if random.randint(1,2)==1:
                print(f"Sa torkad lammast odaga ning teed talle {playerDamage2[0]} HP viga")
            elif random.randint(1,2)==2:
                print(f"Sa vehid odaga lamba suunas tehes talle {playerDamage2[0]} HP viga")
        elif wep == 2:
            if random.randint(1,2)==1:
                print(f"Sa viibutad keppi õhus ning teed lambale {playerDamage2[0]} HP viga")
            elif random.randint(1,2)==2:
                print(f"Lööd lambale keppiga vastu pead ning teed talle {playerDamage2[0]} HP viga")
        
        score=score+playerDamage2[0]*10
        enemyHP=int(enemyHP)-int(playerDamage2[0])
        print(f"lambal on {enemyHP} elu")
        
    return score
#
#

#proloogi lugemise funktsioon
def proloog():
    print("Sa ärkad alasti keset ristteed ning ei mäleta kes sa oled.")
    time.sleep(t)
    print("Põhja poole on mets kus on pimedam ja puud on kiduramad.")
    time.sleep(t)
    print("Ida poole on kanakuut, täiesti tavaline kanakuut...")
    time.sleep(t)
    print("Lõuna poole on mahajäetud saeveski.")
    time.sleep(t)
    print("Lääne poole on kõrts.")
    time.sleep(t)
    print("Aga ennem... kes sa oled?")
    time.sleep(t)
    
#mängu algus
y=input("Soovite mängida? (jah/ei) \n")
#mängu dialoogi kiiruse valik
speed=input("dialoogi kiirus: (kiire,keskmine,aeglane) \n")
if speed == "kiire":
    t=0.5
elif speed == "keskmine":
    t=1
elif speed == "aeglane":
    t=1.5

if y == "jah":
    #proloog()
    
    player=createCharacter()
    playerr=player.showStats()
    playerName,playerDefence,playerStrength,playerMagic,playerPerception,playerHP=playerr.split(",")
    
    print(player.showStatsPrint())
    #print(player.showStats())
    weapon=chooseWeapon()
    #print(weapon.showStats())
    score=int(fightLammas())
    print(f"Skoor on: {score}")
    save_score(playerName,score)

    