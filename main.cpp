#include "Person.h"
#include "User.h"
#include "Creator.h"
#include "VideoDatabase.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <list>
#include <deque>
#include <iostream>
#include <sstream>

using namespace std;

template<typename T>
T* login(const string& name) {
    ifstream file("users.txt");
    if (!file.is_open()) {
        cout << "Unable to open user file.\n";
        return nullptr;
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string storedName;
        iss >> storedName; // Extract name
        if (storedName == name) {
            int regNo;
            iss >> regNo; // Extract registration number
            return new T(name, regNo);
        }
    }


}


int main() {
    cout << "\n YouTube Moderation Software";
    cout << "\n----------------------------------------------------------------------------------------------------------------------------------------------------------------\n";

    cout << "\n\n";

    cout << "\t\t    |   ++++++++++  MAIN MENU   +++++++++  |  \n";
    cout << "\t\t    |    [[[  YouTube Moderation system  ]]]  |\n";
    cout << "\t\t    |======================================|   \n";

    cout << "\n--------------------------------------------------------------------------------\n";

    cout << "\         *******************************************\n\n";
    cout << "\           WELCOME TO THE LOGIN PAGE\n\n";
    cout << "\         ******************************************* ";
    cout << "\n================================================================================\n\n";


    // Create VideoDatabase object
    VideoDatabase videoDB;
    // Load video data from file
    videoDB.loadFromFile("fake_youtube_data_updated.txt");

    // Variables to store user and creator names
    string userName, creatorName;

    // Get user's name
    cout << "Enter your name: ";
    getline(cin, userName);


    auto user = login<User>(userName);
    auto creator = login<Creator>(creatorName);

    // Prompt the user for their type
    int userType; // Variable to store user type (1 for user, 2 for creator)
    cout << "Are you a user (1) or a creator (2)? ";
    cin >> userType;

    if (userType == 1 && user) {
        int userChoice;
        do {
            // Display user options
    cout << "\n----------------------------------------------------------------------------------------------------------------------------------------------------------------\n";

    cout << "\n\n";


    cout << "\t\t    |   ++++++++++  USER MENU   +++++++++  |  \n";
    cout << "\t\t    |======================================|   \n";

    cout << "\n--------------------------------------------------------------------------------\n";
    cout << "\n--------------------------------------------------------------------------------\n";

    cout << "\n\n\t1-\t\tPress 1 To Get videos\n\n";
    cout << "\t2-\t\tPress 2 To Get video recommendations\n\n";
    cout << "\t3-\t\tPress 3 To Show Trending channels\n\n";
    cout << "\t4-\t\tPress 4 To Exit\n ";
    cout << "\n================================================================================\n";

     cout << "\t\t\tEnter your choice:\n";

           cin >> userChoice;

            //  user choice
            switch (userChoice) {
                case 1:
                    user->getVideos();
                    break;
                case 2:
                    user->GetVideoRecommendations(videoDB);
                    break;
                case 3:
                    user->Trending(videoDB);
                    break;
                case 4:
                    cout << "Exiting...\n";
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        } while (userChoice != 4);
    } else if (userType == 2 && creator) {
        int creatorChoice;
        do {
            //  creator options
            cout << "\nCreator Options:\n";
            cout << "1. Show channel score\n";
            cout << "2. Create a video\n";
            cout << "3. Manage a video\n";
            cout << "4. Exit\n";
            cout << "Enter your choice: ";
            cin >> creatorChoice;

            // creator choice
            switch (creatorChoice) {
                case 1:
                    creator->show_channel_score();
                    break;
                case 2:
                    creator->create_video();
                    break;
                case 3:
                    creator->manage_video();
                    break;
                case 4:
                    cout << "Exiting...\n";
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        } while (creatorChoice != 4);
    } else {
        cout << "Invalid user type or name not found.\n";
    }

    return 0;
}
