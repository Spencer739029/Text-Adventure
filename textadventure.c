#include <stdio.h>

struct Player {
    char name[12];
    int health;
    struct Room *currentRoom;
};

struct Room {
    char *name;
    char *description;
    struct Room *north;
    struct Room *east;
    struct Room *south;
    struct Room *west;
    char *items[10]; // array of strings, max 10 items for now
    int itemCount;
};

int main() {
    // Make 5 room, with the second leading to number 3 and 4, and room 3 leading to 5
    struct Room room1;
    room1.name = "room1";
    room1.description = "You are in a dimly lit entrance hall. A torch flickers on the wall."
    room1.north = &room2;
    room1.east = "Dead end!";
    room1.south = "Dead end!";
    room1.west = "Table against the wall...";
    room1.items[0] = "Torch";
    room1.itemCount = 1;

    struct Room room2 {
        room2.name = "room2";
        room2.north = &room4;
        room2.east = &room3;
        room2.south = &room1;
        room2.west = "Dead end!";
        room2.items[0] = "Key";
        room2.itemCount = 1;
    };

    // Player has name, health, current room and inventory
    printf("Name your character:\n");
    scanf("%11s", Player.name);
    Player.health = 100;
    Player.currentRoom = &room1;
    printf("\nYou find yourself in a dark mansion...\n");
    printf("You need to find your way out...\n");
    printf("%s", room1.description);
    // Player can check inventory and stats
    // Use items in inventory
    // Save game after every move
    // Add more later

}