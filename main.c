#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>


#define DEFAULT_AI 1

/*
 * Light Armored Vehicle (LAV)
 *
 * Armored Vehicle (Tank)
 *
 * Anti-Air Tank (AA)
 *
 *
 */
typedef struct {
    char player_name[25];
    char type[10];
    uint8_t hp;
    uint8_t damage;
    uint8_t armor;
    uint8_t size;
} Vehicle;


Vehicle vehi_types[] = {
    {
        "Vehi 1", "LAV",    100,    12,     10,     30
    }, {
        "Vehi 2", "Tank",   150,    20,     15,     50
    }, {
        "Vehi 3", "AA",     100,    5,      7,      25
    }
};


// Simple function to check whether source vehicle damage is larger than target armor value, if yes then reduces overmatch amount of HP
void deal_damage(Vehicle* shooter, Vehicle* target);

// Basically random generator, bases the likelyhood of hit on size, future possibilities include shooter accuracy.
uint8_t check_hit(Vehicle* shooter, Vehicle* target);

// Func for renaming at the beginning, ask for user input
void rename_vehicle(Vehicle* v);

// Select vehicle type, predetermined types:
void select_vehicle(Vehicle *v, int* choice);

void initialization(Vehicle*p1, Vehicle* p2);

void card(Vehicle* v);

char numerize(int c) {
    return (c - '0');
}

int main(void) {

    Vehicle p1, p2 = {"","", 0, 0, 0,0};

    printf("Hello There!\nWelcome to a text based Vehicle game in which you can select your own vehicle and either shoot at AI target or perhaps your friend in COOP mode.\n\nHowever you choose, good luck and have fun!\n");

    puts("\nPress Any key to Continue\n");
    getchar();

    initialization(&p1, &p2);

    for(;;) {
        card(&p1);
        getchar();
        break;
    }

    return 0;
}

void initialization(Vehicle*p1, Vehicle* p2) {
    printf("Select player count (1, 2):\n");
    int players;
    for(;;) {
        while((players = getchar()) == '\n' && players != EOF);
        players = numerize(players);
        if (players == 2 || players == 1) {
            break;
        }
        puts("Insert only number 1 or 2");
    }
    if (players == 1) {
        // Init the AI players vehicle
        Vehicle n = vehi_types[DEFAULT_AI];
        *p2 = n;
    }
    // P1 init
    int chosen_v = 0;
    select_vehicle(p1, &chosen_v);
    Vehicle n1 = vehi_types[numerize(chosen_v)-1];
    *p1 = n1;
    rename_vehicle(p1);

    // P2 init
    if (players == 2) {
        chosen_v = 0;
        select_vehicle(p2, &chosen_v);
        Vehicle n2 = vehi_types[numerize(chosen_v)-1];
        *p2 = n2;
        rename_vehicle(p2);
    }

}

void select_vehicle(Vehicle* v, int* choice) {
    puts("#### SELECT VEHICLE TYPE ####");
    printf("[1] Light Armored Vehicle\n");
    printf("[2] Armored Vehicle\n");
    printf("[3] Anti-Aircraft Vehicle\n");
    printf("Your choice: ");
    for (;;) {
        while((*choice = getchar()) == '\n' && *choice != EOF);
        if (*choice == '1' || *choice == '2' || *choice == '3') {
            break;
        }
        puts("Select vehicle 1 2 3");
    }

}

void rename_vehicle(Vehicle *v) {
    char t[25];
    puts("Name your vehicle, max 24 chars:");
    fgets(t, sizeof(char) * 25,stdin);
    strcpy(v->player_name, t);
}

// WARNING at this time, this function doesnt care about accuracy of shooter nor armor of target.
/*
 * Function returns 0 for FALSE (no hit) and 1 for TRUE (hit)
 */
uint8_t check_hit(Vehicle* shooter, Vehicle* target) {
    // creates a random int, larger target -> higher hit chance
    uint8_t high = (uint8_t)(1 / target->size) * 250;
    uint8_t result = rand() % high;
    if ((uint8_t)(high / 2) < result) {
        return 1;
    }
    return 0;
}

void card(Vehicle* v) {
    printf("\n### VEHICLE STATS ###\n");
    printf("Player: %s\n", v->player_name);
    printf("Type: %s\n", v->type);
    printf("HP: %d\n", v->hp);
    printf("Damage: %d\n", v->damage);
    printf("Armor: %d\n", v->armor);
    printf("Size: %d\n", v->size);
    printf("\n#####################\n");
}












