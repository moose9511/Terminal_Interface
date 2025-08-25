//
// Created by kalen on 2025-08-23.
//

#include "Menu.h"

Menu::Menu(const string &hdr, const vector<string> &tits, const map<int, function<void()>> &funcs) : header(hdr), titles(tits), functions(funcs) {
    if (tits.size() != funcs.size()) {
        cout << "Invalid creation of Menu object. Functions and titles don't match" << endl;
    }
}

// executes the option chosen when object destructs, does this to avoid deep function nesting, and it's related errors.
Menu::~Menu() {
    functions[chosen_opt]();
}

// gets a valid choice from the user
void Menu::Pick(const string &msg, const int &pre_chosen) {

    // checks if user chose option beforehand, skips to setting the chosen function
    if (pre_chosen == -1) {

        // header of menu the user's in
        cout << header << endl;

        // list of options
        for (int i = 1; i <= titles.size(); i++) {
            cout << i << ". " << titles[i-1] << endl;
        }

        // prints message, asking for input, sets which option to interact with upon destruction
        cout << msg << endl;
        string choice;
        int index;
        cin >> choice;

        // tries to get user input, checks if it's valid, retries if it isn't
        do {
            try {
                index = stoi(choice);
            }
            catch (const invalid_argument &e) {}
            catch (const out_of_range &e) {}

            if (index < 0 || index > functions.size()) {
                cout << "Invalid option. Try again: ";
                cin >> choice;
            }
        } while (index < 0 && index > functions.size());

        chosen_opt = index;

    } else {
        chosen_opt = pre_chosen;
    }
}

