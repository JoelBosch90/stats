#ifndef CREATE_TABLE_H
#define CREATE_TABLE_H

#include <iostream>
#include <sqlite3.h>
#include <string>
#include <vector>
#include "../../join_strings/join_strings.h"
using namespace std;

int create_table(string name, vector<string> *rows, sqlite3 *database);

#endif