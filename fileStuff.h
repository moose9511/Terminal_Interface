//
// Created by kalen on 2025-08-17.
//
#pragma once

#include <fstream>
#include <iostream>
#include <filesystem>
#include <windows.h>
#include <vector>

#ifndef TERMINALINTERFACE_FUNCTIONS_H
#define TERMINALINTERFACE_FUNCTIONS_H

#endif //TERMINALINTERFACE_FUNCTIONS_H

void WriteFile(const std::string &text, const std::string &filename);
void AppendFile(const std::string &filename, const std::string &text);
std::vector<std::string> ReadFile(const std::string &filename, const std::string &setting);
std::string LowerCase(const std::string &str);
void WriteGamesPaths();
void OpenFile(const std::string& buildpath);
std::vector<std::string> GetPaths(const std::string &file, bool whole_line = false);
std::string FindPath(const std::string &file_name, const std::string &name);
std::string setting(const std::string &text);
void RemoveSetting(const std::string &filename, const std::string &text);
void Choice(const std::string &msg, int &i);