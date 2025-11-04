#include <stdio.h>
#include <string.h>   // For strcmp and strcspn
#include <stdlib.h>   // For strdup

// Struct to hold player info: name, health, current room pointer,
// inventory array of strings, and count of inventory items
struct Player {
    char name[12];
    int health;
    struct Room *currentRoom;
    char *inventory[10];   // Array of pointers to item strings
    int inventoryCount;    // Number of items in inventory
};

// Struct to hold room info: name, description, pointers to adjacent rooms,
// items in the room, and count of items
struct Room {
    char *name;
    char *description;
    struct Room *north;
    struct Room *east;
    struct Room *south;
    struct Room *west;
    char *items[10];       // Array of pointers to items in the room
    int itemCount;         // Number of items in the room
};

// Function to print the main menu options for the player
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

// Function to save the current game state to a text file
void saveGame(struct Player *player) {
    // Open file "savegame.txt" for writing (overwrite existing)
    FILE *file = fopen("savegame.txt", "w");
    if (!file) {  // Check if file open failed
        printf("Failed to save game.\n");
        return;
    }

    // Save player name, health, and current room name to the file, each on its own line
    fprintf(file, "%s\n", player->name);
    fprintf(file, "%d\n", player->health);
    fprintf(file, "%s\n", player->currentRoom->name);

    // Save how many items player has in inventory
    fprintf(file, "%d\n", player->inventoryCount);

    // Save each inventory item as a string on its own line
    for (int i = 0; i < player->inventoryCount; i++) {
        fprintf(file, "%s\n", player->inventory[i]);
    }

    fclose(file);  // Close the file to flush data
    printf("Game saved.\n");
}

// Function to load a saved game from a file and restore player state
int loadGame(struct Player *player, struct Room *rooms, int roomCount) {
    // Open file "savegame.txt" for reading
    FILE *file = fopen("savegame.txt", "r");
    if (!file) {  // If file doesn't exist or can't be opened
        printf("No saved game found.\n");
        return 0;  // Return failure
    }

    char currentRoomName[50];  // Temporary buffer for room name

    // Read player name from file (line by line)
    if (fgets(player->name, sizeof(player->name), file) == NULL) return 0;
    // Remove newline character from player name
    player->name[strcspn(player->name, "\n")] = 0;

    // Read player health (integer)
    if (fscanf(file, "%d\n", &player->health) != 1) return 0;

    // Read current room name string
    if (fgets(currentRoomName, sizeof(currentRoomName), file) == NULL) return 0;
    // Remove newline character
    currentRoomName[strcspn(currentRoomName, "\n")] = 0;

    // Find room pointer by matching saved room name with existing rooms
    player->currentRoom = NULL;
    for (int i = 0; i < roomCount; i++) {
        if (strcmp(rooms[i].name, currentRoomName) == 0) {
            player->currentRoom = &rooms[i];
            break;
        }
    }

    // If no matching room found, report error and return failure
    if (!player->currentRoom) {
        printf("Saved room not found.\n");
        fclose(file);
        return 0;
    }

    // Read inventory count (how many items the player has)
    if (fscanf(file, "%d\n", &player->inventoryCount) != 1) return 0;

    // Read each inventory item string line-by-line
    for (int i = 0; i < player->inventoryCount; i++) {
        static char line[50];
        if (fgets(line, sizeof(line), file) == NULL) return 0;
        // Remove newline character
        line[strcspn(line, "\n")] = 0;

        // Duplicate the string and store it in player's inventory array
        player->inventory[i] = strdup(line);
    }

    fclose(file);  // Close the file after reading all data
    printf("Game loaded.\n");
    return 1;       // Return success
}

int main() {
    int choice;
    char direction[10];

    // Declare 5 rooms and the player
    struct Room room1, room2, room3, room4, room5;
    struct Player player;

    // Initialize room1 with name, description, connected rooms, and items
    room1.name = "room1";
    room1.description = "You are in a dimly lit entrance hall. A torch flickers on the wall.";
    room1.north = &room2;
    room1.east = NULL;
    room1.south = NULL;
    room1.west = NULL;
    room1.items[0] = "Torch";
    room1.itemCount = 1;

    // Initialize room2
    room2.name = "room2";
    room2.description = "A long hallway stretches ahead, with doors on either side.";
    room2.north = &room4;
    room2.east = &room3;
    room2.south = &room1;
    room2.west = NULL;
    room2.items[0] = "Key";
    room2.itemCount = 1;

    // Initialize room3
    room3.name = "room3";
    room3.description = "Racks of old weapons line the walls.";
    room3.north = &room5;
    room3.east = NULL;
    room3.south = NULL;
    room3.west = &room2;
    room3.items[0] = "Sword";
    room3.items[1] = "Shield";
    room3.itemCount = 2;

    // Initialize room4
    room4.name = "room4";
    room4.description = "Dusty bookshelves reach to the ceiling. Cobwebs hang in the corners.";
    room4.north = NULL;
    room4.east = NULL;
    room4.south = &room2;
    room4.west = NULL;
    room4.items[0] = "Book of Spells";
    room4.itemCount = 1;

    // Initialize room5
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

    // Prompt player to name their character
    printf("Name your character:\n");
    scanf("%11s", player.name);  // Limit input to 11 chars + null terminator

    // Initialize player health and starting room
    player.health = 100;
    player.currentRoom = &room1;
    player.inventoryCount = 0;   // Start with empty inventory

    // Intro story
    printf("\nYou find yourself in a dark mansion...\n");
    printf("You need to find your way out...\n");

    // Game loop - runs until player chooses to exit
    while (1) {
        printf("\n");
        showMenu();  // Show menu options

        // Read player menu choice, handle invalid input
        if (scanf("%d", &choice) != 1) {
            int c;
            // Clear invalid input from buffer
            while ((c = getchar()) != '\n' && c != EOF) {}
            printf("Invalid input.\n");
            continue;  // Prompt menu again
        }

        // Handle each menu choice
        switch (choice) {
            case 1:
                // Look around: print current room description
                printf("%s\n", player.currentRoom->description);
                break;

            case 2: {
                // Move: ask which direction to move
                printf("Which direction (n, e, s, w):\n");
                if (scanf(" %9s", direction) != 1) {
                    printf("Invalid direction.\n");
                    break;
                }
                char d = direction[0];  // Get first char

                // Update current room based on direction, or print error if no room there
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
                // Inventory check - not implemented yet
                printf("Inventory not implemented yet.\n");
                break;

            case 4:
                // Show player stats
                printf("Name: %s\nHealth: %d\n", player.name, player.health);
                break;

            case 5:
                // Exit the game cleanly
                printf("Exiting game.\n");
                return 0;

            default:
                // Handle invalid menu choices
                printf("Invalid option.\n");
        }
    }
    return 0;
}
