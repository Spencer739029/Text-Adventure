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

void showMenu() {
    printf("\n\n========== MENU ==========\n");
    printf("1. Look around\n");
    printf("2. Move\n");
    printf("3. Check inventory\n");
    printf("4. Check stats\n");
    printf("5. Exit game\n");
    printf("==========================\n");
    printf("Choose an option: ");
}

int main() {
    int choice;
    char direction[10];

    // Make 5 room, with the second leading to number 3 and 4, and room 3 leading to 5
    struct Room room1, room2, room3, room4, room5;
    struct Player player;
    room1.name = "room1";
    room1.description = "You are in a dimly lit entrance hall. A torch flickers on the wall.";
    room1.north = &room2;
    room1.east = NULL;
    room1.south = NULL;
    room1.west = NULL;
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
    scanf("%11s", player.name);
    player.health = 100;
    player.currentRoom = &room1;
    printf("\nYou find yourself in a dark mansion...\n");
    printf("You need to find your way out...\n");
    // Player can check inventory and stats
    while (1) {
        printf("\n");
        showMenu();
        if (scanf("%d", &choice) != 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}
            printf("Invalid input.\n");
            continue;
        }

        switch (choice) {
            case 1:
                printf("%s\n", player.currentRoom->description);
                break;
            case 2: {
                printf("Which direction (n, e, s, w):\n");
                if (scanf(" %9s", direction) != 1) {
                    printf("Invalid direction.\n");
                    break;
                }
                char d = direction[0];
                if (d == 'n') {
                    if (player.currentRoom->north) player.currentRoom = player.currentRoom->north;
                    else printf("You can't go that way.\n");
                } else if (d == 'e') {
                    if (player.currentRoom->east) player.currentRoom = player.currentRoom->east;
                    else printf("You can't go that way.\n");
                } else if (d == 's') {
                    if (player.currentRoom->south) player.currentRoom = player.currentRoom->south;
                    else printf("You can't go that way.\n");
                } else if (d == 'w') {
                    if (player.currentRoom->west) player.currentRoom = player.currentRoom->west;
                    else printf("You can't go that way.\n");
                } else {
                    printf("Unknown direction.\n");
                }
                break;
            }
            case 3:
                printf("Inventory not implemented yet.\n");
                break;
            case 4:
                printf("Name: %s\nHealth: %d\n", player.name, player.health);
                break;
            case 5:
                printf("Exiting game.\n");
                return 0;
            default:
                printf("Invalid option.\n");
        }
    }
    return 0;
}
    
    // Use items in inventory
    // Save game after every move
    // Add more later