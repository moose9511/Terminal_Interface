#include <iostream>
#include <fstream>
#include <map>
#include <functional>
#include <thread>
#include "fileStuff.h"
#include "Menu.h"
using namespace std;

string command = "";

struct menu_dec {
    string header;
    map<int, function<void ()>> funcs;
    vector<string> titles;
};
// menu declarations, branches in the way the menus are structured for organization
menu_dec home_menu;
    menu_dec programs_menu;
        menu_dec openprogram_menu;
        menu_dec setprogram_menu;
    menu_dec games_menu;
        menu_dec opengame_menu;
        menu_dec setgame_menu;
            menu_dec gamefolders_menu;
            menu_dec gamepaths_menu;
    menu_dec settings_menu;

void SetUserName() {

}

//-----------------------------------GAMES MENU------------------------------------
// opens game menu under games menu
// manually wrote this menu because I didn't know how to make each game path into a function to add to the menu class
// so the menu class isn't used here
void OpenGame() {
    Menu menu(opengame_menu.header, opengame_menu.titles, opengame_menu.funcs);
    cout << menu.header << endl;

    // gets game names from buildpaths.txt
    const vector<string> games = GetPaths("buildpaths.txt");

    // gets each game in buildpaths.txt and prints it in a numbered format
    for (int i = 1; i <= games.size(); i++) {
        cout << i << ". " << games[i-1] << endl;
    }
    cout << "-If there are missing games, or duplicates of games, go to Set Games to fix it.-" << endl << endl;

    // gets option, and checks if it's valid, opens game if it is
    int game;
    do {
        Choice("Enter number to open game (0 to go back): ", game);
    } while (game > games.size() && game < 0);

    // if user doesn't quit menu, opens desired game
    if (game != 0) {
        OpenFile(FindPath("buildpaths.txt", games[game-1]));
        menu.Pick("kys", 1);
    } else {
        // games back to ---Home/Games---
        menu.Pick("kys", 0);
    }
}

// sets source folder for games to be found. From set games menu
void GameFolders() {
    cout << "---/Home/Games/Games Folders---" << endl;
    cout << "Game Folders:" << endl;

    // opens file
    fstream file;
    file.open("buildpaths.txt", ios::in);
    string text;
    vector<string> folders;

    // finds all gamesfolder settings to be interacted upon
    while (getline(file, text)) {
        if (text.substr(0, text.find('-')) == "gamesfolder") {
            folders.push_back(text);
            cout << folders.size()+1 << ". " << text << endl;
        }
    }

    cout << "Pick number to remove folder, 0 to go back or, " << folders.size()+2 << " to add a folder." << endl;
}

// sets individual paths to executables, able to remove .exe paths that don't open the game. From set games menu
void GamePaths() {}

// sets game paths menu under games menu
void SetGames() {}

//----------------------------------------PROGRAMS MENU-------------------------------------------------
// Opens programs menu under programs menu
void OpenProgram() {}
// set programs menu under programs menu
void SetPrograms() {}

//----------------------------------------MENUS-----------------------------------------
// all only menu functions, do nothing but navigate to other functions
void SettingsMenu() { Menu menu(settings_menu.header, settings_menu.titles, settings_menu.funcs); menu.Pick(); }
void GamesMenu() { Menu menu(games_menu.header, games_menu.titles, games_menu.funcs); menu.Pick(); }
void ProgramsMenu() { Menu menu(programs_menu.header, programs_menu.titles, programs_menu.funcs); menu.Pick(); }
void HomeMenu() { Menu menu(home_menu.header, home_menu.titles, home_menu.funcs); menu.Pick(); }
// superfluous function, only home menu calls it to satisfy parameter
void Quit() {}

int main() {

    // home menu
    home_menu.header = "---Home---", home_menu.titles = {"Games", "Programs", "Settings", "Quit"};
    home_menu.funcs[1] = &GamesMenu, home_menu.funcs[2] = &ProgramsMenu, home_menu.funcs[3] = &SettingsMenu, home_menu.funcs[4] = &Quit;
        // games menu
        games_menu.header = "---Home/Games---", games_menu.titles = {"Open Games", "Set Games", "Back"};
        games_menu.funcs[1] = &OpenGame, games_menu.funcs[2] = &SetGames, games_menu.funcs[3] = &HomeMenu;
            // sets parameters of the opengames menu
            opengame_menu.header = "---Home/Games/Open Games---", opengame_menu.titles = {"Open Game", "Back"};
            opengame_menu.funcs[0] = &GamesMenu, opengame_menu.funcs[1] = &OpenGame;
            // sets parameters of the setgames menu
            setgame_menu.header = "---Home/Games/Set Games---";
            setgame_menu.titles = {"Source folders", "Game paths", "Back"};
        // programs menu
        programs_menu.header = "---Home/Games/Programs---", programs_menu.titles = {"Open programs", "Set programs", "Back"};
        programs_menu.funcs[1] = &OpenProgram, programs_menu.funcs[2] = &SetPrograms, programs_menu.funcs[3] = &HomeMenu;
        // sets parameters of the settings menu
        settings_menu.header = "---Home/Settings---", settings_menu.titles = {"Username", "Back"};
        settings_menu.funcs[1] = &SetUserName, settings_menu.funcs[2] = &Quit;



    // introduction to program using saved username
    cout << "=====================================================" << endl;
    cout << " Welcome " << ReadFile("settings.txt", "username-")[0] << endl;
    cout << "=====================================================\n\n";

    // starts program, if user ever picks
    HomeMenu();

    cout << "Good Bye!" << endl;
    return 0;
}