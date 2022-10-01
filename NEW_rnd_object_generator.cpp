/*
    Author: Tomáš Kudera
    Description: Testing mechanic ideas for some rpg games
    compiled:
        g++ -pthread NEW_rnd_object_generator.cpp -o gen
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>
#include <unistd.h>
#include <thread>
#include <pthread.h>

using namespace std;

#define COMMON 1
#define MAGIC 2
#define RARE 3
#define LEGENDARY 4

#define SWORD 11
#define BOW 12
#define STAFF 13

#define ZOMBIE 21
#define SKELETON 22
#define ORC 23
#define BOSS_ARACHNID 24

const int rarityWeapWeight[] = {50, 30, 15, 5};

class Weapon{
    int m_type = 0;                                                 // Sword, Bow, Staff
    int m_level = 0;                                                // Level of weapon
    int m_rarity = 0;                                               // Common = 1, Magic = 2, Rare = 3, Legendary = 4
    int m_baseDamage = 0;                                           // Base damage    
    float m_attackSpeed = 0;                                        // Attack speed of weapon
    int m_damage = 0;                                               // Calculated damage

public: 
    Weapon(int type, int level, int rarity){
        m_type = type;
        m_level = level;
        m_rarity = initWeapRarity(rarity);
        m_baseDamage = initWeapBaseDamage();
        m_attackSpeed = initWeapAttackSpeed();
        m_damage = calcWeapDamage();
    }

    void getInfo(){
        cout << convertWeapTypeToString() << "\n";
        cout << "Level: " << m_level << "\n";
        cout << "Rarity: " << convertWeapRarityToString() << "\n";
        cout << "Damage: " << m_damage << endl;
    }

private:
    string convertWeapTypeToString(){
        if(m_type == SWORD) return "Sword";
        if(m_type == BOW) return "Bow";
        if(m_type == STAFF) return "Staff";
        return "Bug in weapon type!";
    }

    string convertWeapRarityToString(){
        if(m_rarity == COMMON) return "Common"; 
        if(m_rarity == MAGIC) return "Magic";
        if(m_rarity == RARE) return "Rare";
        if(m_rarity == LEGENDARY) return "Legendary";
        return "Bug in weapon rarity!";
    }

    int initWeapRarity(int rarity){
        //return 1;             // 50% chance for Common - 1 in 2
        //return 2;             // 30% chance for Magic - 1 in 3.3
        //return 3;             // 15% chance for Rare - 1 in 6.6
        //return 4;             // 05% chance for Legendary - 1 in 20
        for (int i = 1; i <= (sizeof(rarityWeapWeight) / sizeof(int)); i++){
            if(rarity <= rarityWeapWeight[i-1]){
                return i;
            }else{
                rarity -= rarityWeapWeight[i-1];
            }
        }
        return 999;
    }
    int initWeapBaseDamage(){
        if(m_rarity == COMMON) return 5;
        if(m_rarity == MAGIC) return 10;
        if(m_rarity == RARE) return 20;
        if(m_rarity == LEGENDARY) return 40;
        return 999;
    }

    float initWeapAttackSpeed(){
        if(m_type == SWORD) return 1.3;
        if(m_type == BOW) return 1.5;
        if(m_type == STAFF) return 1.1;
        return 999;
    }

    int calcWeapDamage(){
        return (((m_baseDamage + m_level) * ((m_level / 100) + 1 )) / 2) * m_attackSpeed;
    }
};

class Monster{
    int m_type = 0;                                                 // Zombie, Skeleton, Orc, Arachnid boss
    int m_level = 0;                                                // Level of monster
    int m_baseHealth = 0;                                           // Base health
    int m_baseDamage = 0;                                           // Base damage    
    float m_attackSpeed = 0;                                        // Attack speed of monster
    int m_damage = 0;                                               // Calculated overall damage
    int m_health = 0;                                               // Calculated health    --- ((baseHealth+level)) * [1.5 to 1.7] <-- random offset

public:
    Monster(int type, int level){
        m_type = type;
        m_level = level;
        m_baseHealth = initMonBaseHealth();
        m_baseDamage = initMonBaseDamage();
        m_attackSpeed = initMonAttackSpeed();
        m_damage = calcMonDamage();
        m_health = calcMonHealth();
    }

    void getInfo(){
        cout << convertMonTypeToString() << "\n";
        cout << "Level: " << m_level << "\n";
        cout << "Health: " << m_health << "\n";
        cout << "Damage: " << m_damage << endl;
    }
private:
    string convertMonTypeToString(){
        if(m_type == ZOMBIE) return "Zombie";
        if(m_type == SKELETON) return "Skeleton";
        if(m_type == ORC) return "Orc";
        if(m_type == BOSS_ARACHNID) return "Arachnid Boss";
        return "Bug in monster type!";
    }
    int initMonBaseHealth(){
        if(m_type == ZOMBIE) return 4;
        if(m_type == SKELETON) return 5;
        if(m_type == ORC) return 10;
        if(m_type == BOSS_ARACHNID) return 25;
        return 999;
    }
    int initMonBaseDamage(){
        if(m_type == ZOMBIE) return 6;
        if(m_type == SKELETON) return 5;
        if(m_type == ORC) return 20;
        if(m_type == BOSS_ARACHNID) return 30;
        return 999;
    }
    float initMonAttackSpeed(){
        if(m_type == ZOMBIE) return 1.2;
        if(m_type == SKELETON) return 1.2;
        if(m_type == ORC) return 1;
        if(m_type == BOSS_ARACHNID) return 1.3;
        return 999;
    }
    int calcMonDamage(){
        return (((m_baseDamage + m_level) * ((m_level / 100) + 1 )) / 2) * m_attackSpeed;
    }
    int calcMonHealth(){
        float offset = rand () % 31 + 60;
        offset = (offset / 100) + 2;
        return ((m_baseHealth * ((m_level / 100) + 1 )) + (m_level * 2)) * offset;
    }
};

void weaponThread(int level){
    srand(time(0));

    int type = 0;
    int totalRarity = 0;
    int rarityRand = 0;
    for (int ind : rarityWeapWeight)
    {
        totalRarity += ind;
    }
    for(int i = 0; i < 20; i++){
        rarityRand = rand() % totalRarity + 1;                  // Total rarity - sum of weights
        type = rand() % 3 + 11;                                 // 3 - Sword 0+11, Bow 1+11, Staff 2+11
        Weapon* weapon = new Weapon(type, level, rarityRand);
        weapon->getInfo();
        delete weapon;
        sleep(1);
    }
}

void monsterThread(int level){
    srand(time(0));
    
    int type = 0;

    for(int i = 0; i < 10; i++){
        type = rand() % 4 + 21;
        Monster* monster = new Monster(type, level);
        monster->getInfo();
        delete monster;
        sleep(1);
    }
}


int main(){
    int level = 0;
    cin >> level;
    if(level >= 1 && level <= 100){
        thread weapThread(weaponThread, level);
        thread monThread(monsterThread, level);

        weapThread.join();
        monThread.join();
    }

    return 0;
}