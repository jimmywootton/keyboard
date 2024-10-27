#include <iostream>
#include <string>
#include <algorithm>
#include <ncurses.h>
#include <vector>
#include <utility>
#include <fstream>

using namespace std;

bool compare(pair<string, double> x,pair<string, double> y)
{
    
    return x.second > y.second;

}

double getRatio(string word, string input)
{
    int count = 0;
    for (int i = 0; i < word.size(); i++) 
    {
        for (int j = 0; j < input.size(); j++) 
        {
            if(word.at(i) == input.at(j))
            {
                count++;
            }
        }
    }
    return (double)count / word.size();
}




int main()
{
    
    initscr(); // Initialize ncurses
    cbreak(); // Line buffering disabled, Pass on everything to me
    noecho(); // Don't echo() while we do getch
    keypad(stdscr, TRUE);
    printw("Type Letters:");
    printw("\n");
    string input;
    int ch;
    while(ch != 10)
    {
        ch = getch();
        if (ch != 10)
        {
            input += ch;
            printw("%c", ch);        
            refresh(); 
        }
    }





    ifstream list("wordlist.txt");
    string word;
    vector<pair<string, double> > words;
    while (getline(list, word)) 
    {
        words.push_back(make_pair(word, getRatio(word, input)));
    }
    list.close();


    sort(words.begin(), words.end(), compare);

    


    

    
    while (!words.empty())
    {
        printw(words.front().first.c_str());
        printw("\n");
        string input;
        while (input != words.front().first) 
        {
            int ch = getch(); // Get a character
            if (ch == 127) 
            { // If Backspace is pressed (ASCII value 8 or 127)
                if (!input.empty()) 
                {
                    input.pop_back(); // Remove last character
                    printw("\b \b"); // Move cursor back, erase character, move cursor back again
                    refresh();
                }
            } 
            if (isalpha(ch))
            {
                input += ch;
                printw("%c", ch); // Print the typed character
                refresh();
            }
        }
        move(getcury(stdscr) - 1, 0); // Move to the line with "Country"
        clrtoeol(); // Clear that line
        move(getcury(stdscr) - 1, 0); // Move to the line with "Type the capital"
        clrtoeol(); // Clear that li
        clear();

        
    }
    
    
    
    endwin();
    
    return 0;
    

    

}