#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>
#include <unistd.h>

using namespace std;

#define COMMON 1
#define MAGIC 2
#define RARE 3
#define LEGENDARY 4

#define SWORD 11
#define BOW 12
#define STAFF 13

const int rarityWeight[] = {50, 30, 15, 5};

class Weapon{
    int m_type = 0;                                                 // Sword, Bow, Staff
    int m_level = 0;                                                // Level of weapon
    int m_rarity = 0;                                               // Common = 1, Magic = 2, Rare = 3, Legendary = 4
    int m_baseDamage = 0;                                           // Base damage    
    float m_attackSpeed = 0;                                        // Attack speed of weapon
    float m_damage = 0;                                             // Calculated damage

public: 
    Weapon(int type, int level, int rarity){
        m_type = type;
        convertTypeToString();
        m_level = level;
        m_rarity = initRarity(rarity);
        convertRarityToString();
        m_baseDamage = initBaseDamage();
        m_attackSpeed = initAttackSpeed();
        m_damage = calcDamage();
    }

    void getInfo(){
        cout << convertTypeToString() << "\n";
        cout << "Level: " << m_level << "\n";
        cout << "Rarity: " << convertRarityToString() << "\n";
        cout << "Damage: " << m_damage << endl;
    }

private:
    string convertTypeToString(){
        if(m_type == SWORD) return "Sword";
        if(m_type == BOW) return "Bow";
        if(m_type == STAFF) return "Staff";
        return "Bug in type";
    }

    string convertRarityToString(){
        if(m_rarity == COMMON) return "Common"; 
        if(m_rarity == MAGIC) return "Magic";
        if(m_rarity == RARE) return "Rare";
        if(m_rarity == LEGENDARY) return "Legendary";
        return "Bug in rarity";
    }

    int initRarity(int rarity){
        //return 1;             // 50% chance for Common - 1 in 2
        //return 2;             // 30% chance for Magic - 1 in 3.3
        //return 3;             // 15% chance for Rare - 1 in 6.6
        //return 4;             // 05% chance for Legendary - 1 in 20
        for (int i = 1; i <= (sizeof(rarityWeight) / sizeof(int)); i++){
            if(rarity <= rarityWeight[i-1]){
                return i;
            }else{
                rarity -= rarityWeight[i-1];
            }
        }
        return 999;
    }
    int initBaseDamage(){
        if(m_rarity == COMMON) return 5;
        if(m_rarity == MAGIC) return 10;
        if(m_rarity == RARE) return 20;
        if(m_rarity == LEGENDARY) return 40;
        return 999;
    }

    float initAttackSpeed(){
        if(m_type == SWORD) return 1.3;
        if(m_type == BOW) return 1.5;
        if(m_type == STAFF) return 1.1;
        return 999;
    }

    int calcDamage(){
        return (((m_baseDamage + m_level) * ((m_level / 100) + 1 )) / 2) * m_attackSpeed;
    }
};

int main(){
    srand(time(0));

    int type = 0;

    int level = 0;
    cin >> level;

    int totalRarity = 0;
    int rarityRand = 0;
    for (int ind : rarityWeight)
    {
        totalRarity += ind;
    }

    if(level >= 1 && level <= 100){
        for(int i = 0; i < 20; i++){
            rarityRand = rand() % totalRarity + 1;                  //Total rarity - sum of weights
            type = rand() % 3 + 11;                                 //3 - Sword 0+11, Bow 1+11, Staff 2+11
            Weapon* weapon = new Weapon(type, level, rarityRand);
            weapon->getInfo();
            delete weapon;
            sleep(1);
        }
    }
    return 0;
}