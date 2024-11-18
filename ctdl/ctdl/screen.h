#pragma once
#ifndef SCREEN_H
#define SCREEN_H

#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>
#include <initializer_list>
#include <vector>
using namespace std;

// Function to move the cursor to the specified coordinates on the console
void gotoxy(int column, int line);

// Function to change text color
void textColor(int color);

// Function to reset text color to default
void resetColor();

// Function to draw a rectangular border around the menu
void veKhung(int x, int y, int chieuDai, int chieuRong);

// Menu class declaration
class Menu {
public:
    Menu() {};

    // Constructor that initializes the menu with items
    Menu(int n, vector<string> arr, string t, int X, int Y, int D, int R);



    // Function to print the menu with the selected line highlighted
    void printMenu(int selectedLine);

    // Function to get the number of items in the menu
    int numberOfItem();


    // Function to handle menu movement input
    int Move();


private:
    vector <string> item; // Array holding menu item names
    int _numberOfItem; // Number of menu items
    string title;
    int x; int y;
    int chieuDai;
    int chieuRong;
};

#endif // MENU_H
