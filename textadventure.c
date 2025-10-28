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
    struct Room room1, room2, room3, room4, room5;
    room1.name = "room1";
    room1.description = "You are in a dimly lit entrance hall. A torch flickers on the wall.";
    room1.north = &room2;
    room1.east = NULL;
    room1.south = NULL;
    room1.west = "NULL";
    room1.items[0] = "Torch";
    room1.itemCount = 1;

    room2.name = "room2";
    room2.description = "A long hallway stretches ahead, with doors on either side.";
    room2.north = &room4;
    room2.east = &room3;
    room2.south = &room1;
    room2.west = NULL;
    room2.items[0] = "Key";
    room2.itemCount = 1;

    room3.name = "room3";
    room3.description = "Racks of old weapons line the walls.";
    room3.north = &room5;
    room3.east = NULL;
    room3.south = NULL;
    room3.west = &room2;
    room3.items[0] = "Sword";
    room3.items[1] = "Shield";
    room3.itemCount = 2;

    room4.name = "room4";
    room4.description = "Dusty bookshelves reach to the ceiling. Cobwebs hang in the corners.";
    room4.north = NULL;
    room4.east = NULL;
    room4.south = &room2;
    room4.west = NULL;
    room4.items[0] = "Book of Spells";
    room4.itemCount = 1;

    room5.name = "room5";
    room5.description = "Dusty bookshelves reach to the ceiling. Cobwebs hang in the corners.";
    room5.north = NULL;
    room5.east = NULL;
    room5.south = &room3;
    room5.west = NULL;
    room5.items[0] = "Gold coins";
    room5.items[1] = "Gem";
    room5.items[2] = "Mysterious Key";
    room5.itemCount = 3;

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