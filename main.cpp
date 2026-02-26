#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <limits>
/*
Name: Hector L Catalino
Class: CS-210-10383-M01 Programing Language
Date: 2/17/2026
Synopsis: This program would read from a text file and pull words from it with the amount of each word and will prompt the user what to do with it 
whether they would like to see the words, pull some words out, or even show the words with the amount of each word with *
*/
//Class that tracks grocery item frequencies 
class ItemTracker {
private:
    std::map<std::string, int> itemFrequencies;  
    std::string backupFile;                     
    //Reads data from the input file and initializes the backup file
public:
    ItemTracker(const std::string& filename, const std::string& backupFilename = "./frequency.dat")
        : backupFile(backupFilename)
    {
        std::ifstream inputFile(filename);
        //If the file cannot be opened, display error and exit program
        if (!inputFile) {
            std::cerr << "Error opening input file: " << filename << std::endl;
            exit(1);
        }

        std::string item;
        int count;
        // Read item and count pairs from the file
        while (inputFile >> item >> count) {
            itemFrequencies[item] = count;  //Use the count from the file
        }

        inputFile.close();

        //Save initial backup
        saveBackup();
    }

    //Display menu options
    void displayMenu() {
        std::cout << "\n=== Corner Grocer Item Tracker Menu ===\n";
        std::cout << "1. Search for an item and remove one\n";
        std::cout << "2. Display all item frequencies\n";
        std::cout << "3. Display histogram of items\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
    }

    //Search for an item and remove one
    void searchItemFrequency() {
        std::string item;
        std::cout << "Enter item to search: ";
        std::cin >> item;

        auto it = itemFrequencies.find(item);
        if (it != itemFrequencies.end()) {
            std::cout << item << " was purchased " << it->second << " times.\n";

            //Decrement count
            it->second--;

            //Remove if count reaches 0
            if (it->second <= 0) {
                itemFrequencies.erase(it);
                std::cout << item << " is now removed from the list.\n";
            }
            else {
                std::cout << "After removing one, " << item << " now has " << it->second << " remaining.\n";
            }

            //Update backup file with current frequencies
            saveBackup();
        }
        else {
            std::cout << item << " was not purchased today or has been fully removed.\n";
        }
    }

    //Display all item frequencies
    void displayAllFrequencies() {
        if (itemFrequencies.empty()) {
            std::cout << "No items to display. All items have been removed.\n";
            return;
        }

        std::cout << "\nItem Frequencies:\n";
        for (const auto& pair : itemFrequencies) {
            std::cout << pair.first << " " << pair.second << std::endl;
        }
    }

    //Display histogram of items
    void displayHistogram() {
        if (itemFrequencies.empty()) {
            std::cout << "No items to display. All items have been removed.\n";
            return;
        }

        std::cout << "\nItem Histogram:\n";
        for (const auto& pair : itemFrequencies) {
            std::cout << pair.first << " ";
            for (int i = 0; i < pair.second; i++)
                std::cout << "*";
            std::cout << std::endl;
        }
    }

    //Save backup file 
    void saveBackup() {
        std::ofstream outFile(backupFile);
        if (!outFile) {
            std::cerr << "Error creating backup file: " << backupFile << std::endl;
            return;
        }

        for (const auto& pair : itemFrequencies) {
            outFile << pair.first << " " << pair.second << std::endl;
        }

        outFile.close();
    }
};

int main() {
    //Create tracker object and read input file
    ItemTracker tracker("CS210_Project_Three_Input_File.txt"); 

    int choice;

    do {
        tracker.displayMenu();

        //Input validation for menu choice
        while (!(std::cin >> choice) || choice < 1 || choice > 4) {
            std::cin.clear(); 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard bad input
            std::cout << "Invalid input. Enter a number between 1 and 4: ";
        }

        switch (choice) {
        case 1:
            tracker.searchItemFrequency();
            //Call search and remove function
            break;
        case 2:
            tracker.displayAllFrequencies();
            //Call display all function
            break;
        case 3:
            tracker.displayHistogram();
            //Call histogram function
            break;
        case 4:
            std::cout << "Exiting program. Goodbye!\n";
            //Exits the program
            break;
        }

    } while (choice != 4);
    //Repeat menu until user chooses Exit(4)

    return 0;
}
