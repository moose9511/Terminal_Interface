//
// Created by kalen on 2025-08-17.
//
#include "fileStuff.h"

namespace fs = std::filesystem;

std::string game_folder_name = "gamesfolder";
std::string buildpath_name = "buildpaths.txt";
// finds the specified setting of a file
std::string setting(const std::string &text) {
    int spacer = text.find('-');
    if (spacer != std::string::npos) {
        return text.substr(0, spacer);
    }

}
// write file function, takes the text, writes to a single line
void WriteFile(const std::string &text, const std::string &filename) {

    std::fstream file;
    file.open(filename, std::ios::out);

    if (file.is_open()) {
        file << text << std::endl;
        file.close();
    } else {
        std::cout << "Failed to open file " << filename << ". Call from WriteFile" << std::endl;
    }
}

// append file function, adds a new line with specified text
void AppendFile(const std::string &filename, const std::string &text) {

    std::fstream file;
    file.open(filename, std::ios::app);

    if (file.is_open()) {

        file << text << std::endl;
        file.close();
    } else {

        std::cout << "Failed to open file " << filename << ". Call from AppendFile" << std::endl;
    }
}
// read file function, gets all entries of a setting if explicit, returns all contents if not
std::vector<std::string> ReadFile(const std::string &filename, const std::string &setting = "") {

    std::fstream file;
    file.open(filename, std::ios::in);

    std::vector<std::string> entries;
    // if file is found and opened
    if (file.is_open()) {

        std::string text;

        // tries to find specific setting of file
        if (setting != "") {

            // goes through each line in file
            while (getline(file, text)) {

                // if setting matches sought after line, finds contents
                bool found_setting = true;
                if (setting.length() > text.length() || LowerCase(text.substr(0, setting.length())) != LowerCase(setting)) {
                    found_setting = false;
                }
                if (found_setting == true) {
                    entries.push_back(text.substr(setting.length()));
                }
            }
            file.close();
            if (entries.size() > 0) {
                return entries;
            } else {
                return {""};
            }
        // returns entire contents
        } else {
            while (getline(file, text)) {}
            file.close();
            entries.push_back(text);
            return entries;
        }
    } else {

        std::cout << "Failed to open file " << filename << ". Call from ReadFile" << std::endl;
        file.close();
        return {"[Failed file read]"};
    }
}
// tries to write the paths of the games based on pre-written folder of game_folder_name which is the steam library
void WriteGamesPaths() {

    // gets folder from steam
    std::fstream src_folder;
    std::vector<std::string> paths = ReadFile(buildpath_name, game_folder_name + '-');
    std::string name;

    // goes through each game folder to try to find the executable
    for (int i = 0; i < paths.size(); i++) {
        for (const auto& entry: fs::directory_iterator(paths[i])) {
            if (entry.is_directory()) {

                // checks if the buildpaths.txt already has the same game path written on it
                name = entry.path().filename().string();
                std::string existing_name = ReadFile(buildpath_name, name+"-")[0];
                if (existing_name == "") {

                    // goes through first layer in the games folder to try and find an executable for the game
                    // doesn't include the game if executable is not one layer inside the folder
                    for (const auto& entry2: fs::directory_iterator(entry.path())) {
                        if (fs::is_regular_file(entry2.path()) && entry2.path().extension() == ".exe") {
                            AppendFile(buildpath_name, name + "-" + entry2.path().string());
                        }
                    }
                }
            }
        }
    }
}
// tries to execute a file via a given buildpath
void OpenFile(const std::string &buildpath) {

    // if it can find the build path, opens executable
    if (fs::exists(buildpath)) {
        ShellExecute(nullptr, "open", buildpath.c_str(), nullptr, nullptr, SW_SHOWDEFAULT);
    } else {
        std::cout << "Failed to open file in path: " << buildpath << std::endl;
    }
}
// gets list of available commands depending on the menu
// prints current list of settings in a given file
std::vector<std::string> GetPaths(const std::string &file_name, bool whole_line) {

    std::fstream file;
    file.open(file_name, std::ios::in);
    std::string text;
    std::vector<std::string> paths;

    std::cout << "Games: " << std::endl;
    // goes through each line in the file
    while (getline(file, text)) {

        // ignores lines that isn't games
        if (text.substr(0, text.find('-')) != game_folder_name) {

            //either gets the whole line or just the name of the setting
            if (whole_line == false) {
                paths.push_back(text.substr(0, text.find('-')));
            } else {
                paths.push_back(text);
            }
        }
    }
    return paths;
}
// find specific path based on the exact name of the setting
std::string FindPath(const std::string &file_name, const std::string &name) {
    std::fstream file;
    file.open(file_name, std::ios::in);
    std::string text;

    // checks each line of the file, if it finds the setting name of the same name, returns the file path
    while (getline(file, text)) {
        if (text.substr(0, text.find('-')) == name) {
            return text.substr(text.find('-') + 1);
        }
    }
}
// gets lowercase version of a std::string
std::string LowerCase(const std::string &str) {

    std::string new_str;
    for (const char c : str) {
        new_str += tolower(c);
    }
    return new_str;
}
// writes whole contents of file except specified setting to a temp file, rewrites original file without the setting from temp
void RemoveSetting(const std::string &filename, const std::string &setting) {
    std::fstream file;
    std::fstream temp_file;
    file.open(filename, std::ios::in | std::ios::app);
    temp_file.clear();
    temp_file.open("temp.txt", std::ios::in | std::ios::app);

    std::string temp;
    // writes all contents except specified setting, to the temp file
    while (std::getline(file, temp)) {
        if (temp != setting) {
            temp_file << temp << std::endl;
        }
    }
    // writes all contents of temp to og file
    file.clear();
    while (std::getline(temp_file, temp)) {
        temp_file << temp << std::endl;
    }

    file.close();
    temp_file.close();
}

void Choice(const std::string &msg, int &i) {
    bool is_valid = false;

    // tries to get user input, checks if it's valid, retries if it isn't
    std::cout << msg << std::endl;
    do {
        try {
            std::string choice;
            std::cin >> choice;
            i = stoi(choice);
            is_valid = true;
        }
        catch (const std::invalid_argument &e) { std::cout << "Invalid choice, try again: "; }
        catch (const std::out_of_range &e) { std::cout << "Invalid choice, try again: "; }

    } while (is_valid == false);
}
