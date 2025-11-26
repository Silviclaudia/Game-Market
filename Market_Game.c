#include <stdio.h>
#include <stdlib.h>
#include <time.h> // randomness

/*Use enum -> label number with name*/
enum Profession {
    TRADER = 1,
    RISK_MANAGER = 2
};

/*Components for "PLAYER" (TRADER OR RISK_MANAGER) in a game*/
typedef struct {
    int hp;
    int defense_power;
    int profession;
} Player;

/*Components for "BOSS" (economic market situation)*/
typedef struct {
    int hp;
    int attack_power;
} Boss;

// Attack damage, ex: ETF-> 7 to 12 damage; just helper function
int randomRange(int min, int max) {
    return rand() % (max - min + 1) + min; // build own function so ex: range(0,100)
    // ignore rand(), (100-1+1)= 100 so 0 to 99; now +min/+1 so range = 1 to 100 back to normal
}

void printStatus(Player player, Boss boss) {
    printf("Your HP: %d | Boss HP: %d\n", player.hp, boss.hp);
}

// Components to attack boss
int etfAttack() {
    return randomRange(7,12); // stable attack
}

int bondsDefense() {
    /*Bonds were meant to be small heal*/
    return randomRange(3,5); 
}

int crypto() {
    int roll = randomRange(1,100);

    if (roll <= 20) { //Successful crypto 20%, fail 80%
        return randomRange(30,40);
    } else {
        return 0;
    }
}

int cashHold() {
    return randomRange(2,3);
}

int main() { // main() include all scope of declaration
    srand(time(NULL)); //seed random - srand()
    Player player; // struct temporary variable
    Boss boss;

    printf("Choose your profession:\n");
    printf("1. Trader\n");
    printf("2. Risk Manager\n");
    printf("Enter your choice:");

    int userChoice = 0; //integer not pointer; check null only for pointer

    while (1) {
        scanf("%d", &userChoice);
        if (userChoice >=1 && userChoice <=2) {
            break;
        } else {
            printf("Please enter your choose, either 1 or 2\n");
        }
    }

    if (userChoice == 1) {
        player.profession = TRADER;
        player.hp = 95;
        player.defense_power = 0;
    } else {
        player.profession = RISK_MANAGER;
        player.hp = 110;
        player.defense_power = 0;
    }
    /*Boss setup*/
    boss.hp = 120;
    boss.attack_power = 1;

    printf("\nTHE GAME IS ABOUT TO START\n");

    /*Start with player turn before boss*/
    while (player.hp > 0 && boss.hp > 0) { 
        int playerOption = 0;

        while (1) { // / Infinite loop for input validation so repeats until a valid (1–4) choice is entered.
            printf("Choose your move (number 1,2,3, or 4): \n");
            printf("1. ETF Attack\n");
            printf("2. Bonds (Heal)\n");
            printf("3. Crypto Attack\n");
            printf("4. Cash Hold (Heal)\n");

            scanf("%d", &playerOption);

            if (playerOption >= 1 && playerOption <= 4) {
                break;
            } else {
                printf("Invalid choice! Please enter 1,2,3, or 4.\n");
            }
        }

        //"Player action" to choose the move
        if (playerOption == 1) { 
            int damage = etfAttack(); // call the function
            boss.hp = boss.hp - damage; // boss.hp -= damage;
            printf("You used ETF and did %d damage to the boss!\n", damage);
        } else if (playerOption == 2) { 
            int heal = bondsDefense();
            player.hp = player.hp + heal;
            printf("You used Bonds and gained %d heal to yourself!\n", heal);
        } else if (playerOption == 3) { 
            int damage = crypto();
            boss.hp = boss.hp - damage;
            printf("You used Crypto and did %d damage to the boss\n", damage);
        } else {
            int heal = cashHold();
            player.hp = player.hp + heal;
            printf("You used Cash Hold and gained %d heal to yourself\n", heal);
        }
        // After attack check the boss condition 
        if (boss.hp <= 0) {
            printf("YOU WIN! You outperformed the market!\n");
            break;
        }

        //"Boss action" to choose a move
        int attack = randomRange(1,100);

        // Boss can shake the market
        if (attack >= 1 && attack <= 40) {
            int damage = randomRange(5,8); // inflation doesn't really hurt
            player.hp = player.hp - damage;
            printf("Boss uses INFLATION ATTACK! You got hit by %d damage.\n", damage);
        } else if (attack >= 41 && attack <= 70) {
            int damage = randomRange(8,12); 
            player.hp = player.hp - damage;
            printf("Boss uses RECESSION SMASH ATTACK! You got hit by %d damage.\n", damage);
        } else if (attack >= 71 && attack <= 90) {
            int damage = randomRange(0,15); //When gov increase rate, consumer hasn't panic then fine, if panic then market dips
            player.hp = player.hp - damage;
            printf("Boss uses INTEREST RATE HIKE! You got hit by %d damage.\n", damage);
        } else {
            int damage = randomRange(20,30); 
            player.hp = player.hp - damage;
            printf("Boss uses MARKET CRASH 2008! You got hit by %d damage.\n", damage);
        }

        //After attack check the player condition
        if (player.hp <= 0) {
            printf("SORRY, YOU LOSE! The market crushed your portfolio\n");
            break;
        }
        printStatus(player, boss);
        }
        return 0; //As always in C declaring it's done
    }
