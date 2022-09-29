#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>
#include <unistd.h>

using namespace std;

class Weapon{
    int m_dMIN = 0, m_dMAX = 1;

    string m_type = "";                                             // Sword, Bow, Staff
    float m_level = 0;                                              // Level of weapon
    string m_rarity = "";                                           // Common = 1, Magic = 2, Rare = 3, Legendary = 4
    float m_attack_speed = 0;                                       // Attack speed of weapon
    float m_base_damage = 0;                                        // Base damage    
    float m_damage = 0;                                             // Calculated damage

public: 
    Weapon(string type, float level, string rarity){
        if(rarity.compare("Common") == 0) m_base_damage = 5;
        if(rarity.compare("Magic") == 0) m_base_damage = 10;
        if(rarity.compare("Rare") == 0) m_base_damage = 20;
        if(rarity.compare("Legendary") == 0) m_base_damage = 40;

        if(type.compare("Staff") == 0) m_attack_speed = 1;
        if(type.compare("Sword") == 0) m_attack_speed = 1.3;
        if(type.compare("Bow") == 0) m_attack_speed = 1.5;

        m_type = type;
        m_level = level;
        m_rarity = rarity;
        m_damage = (((m_base_damage + m_level) * ((m_level / 100) + 1 )) / 2) * m_attack_speed;
    }

    void getInfo(){
        cout << m_type << "\n";
        cout << "Level: " << m_level << "\n";
        cout << "Rarity: " << m_rarity << "\n";
        cout << "Damage: " << m_damage << endl;
    }
};

string make_Type(int type){
    if(type == 1) return "Sword";
    if(type == 2) return "Bow";
    if(type == 3) return "Staff";
    return "Bug";
}

string make_Rarity(int* rarity){
    if(*rarity == 20 ||
       *rarity == 40 ||
       *rarity == 60 ||
       *rarity == 80 ||
       *rarity == 100){
        *rarity = 4;
        return "Legendary";       // 05% chance for Legendary - 1 in 20
    }else if(*rarity == 6 || *rarity == 12 || *rarity == 18 ||
             *rarity == 26 || *rarity == 32 || *rarity == 38 ||
             *rarity == 46 || *rarity == 52 || *rarity == 58 ||
             *rarity == 66 || *rarity == 72 || *rarity == 78 ||
             *rarity == 86 || *rarity == 92 || *rarity == 98){
        *rarity = 3;
        return "Rare";             // 15% chance for Rare - 1 in 6.6
    }else if(*rarity == 5 || *rarity == 7 || *rarity == 11 || *rarity == 13 || *rarity == 17 || *rarity == 19 ||
             *rarity == 25 || *rarity == 27 || *rarity == 31 || *rarity == 33 || *rarity == 37 || *rarity == 39 ||
             *rarity == 45 || *rarity == 47 || *rarity == 51 || *rarity == 53 || *rarity == 57 || *rarity == 59 ||
             *rarity == 65 || *rarity == 67 || *rarity == 71 || *rarity == 73 || *rarity == 77 || *rarity == 79 ||
             *rarity == 85 || *rarity == 87 || *rarity == 91 || *rarity == 93 || *rarity == 97 || *rarity == 99){
        *rarity = 2;
        return "Magic";            // 30% chance for Magic - 1 in 3.3
    }else{
        *rarity = 1;
        return "Common";            // 50% chance for Common - 1 in 2
    }    
    return "Bug";
}

int main(){
    srand(time(0));

    int type = 0;
    string str_type = "";
    int rarity = 0;
    string str_rarity = "";

    float level = 0;
    cin >> level;

    if(level >= 1 && level <= 100){
        for(int i = 0; i < 20; i++){
            rarity = rand() % 100 + 1;
            str_rarity = make_Rarity(&rarity);
            type = rand() % 3 + 1;
            str_type = make_Type(type);
            Weapon* weapon = new Weapon(str_type, level, str_rarity);
            weapon->getInfo();
            delete weapon;
            sleep(1);
        }
    }
    return 0;
}