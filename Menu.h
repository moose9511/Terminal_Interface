//
// Created by kalen on 2025-08-23.
//
#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <functional>

#ifndef MENUTHING_MENU_H
#define MENUTHING_MENU_H

using namespace std;

class Menu {
public:
    string header = "";
    // which func will be executed for this Menu
    int chosen_opt = -1;
    // what will be printed to show the user's options in the menu
    vector<string> titles = {};
    // list of functions for each option of the menu
    map<int, function<void()>> functions;
    // if the menu is temp, doesn't complain about stuff
    bool is_temp = false;

    Menu() : is_temp(true) {};
    Menu(const string &hdr, const vector<string> &tits, const map<int, function<void ()>> &funcs);
    ~Menu();

    void Pick(const string &msg = "Enter choice: ", const int &pre_chosen = -1);

};



#endif //MENUTHING_MENU_H