#include "User.h"
#include "VideoDatabase.h"
#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <list>
#include <algorithm>
#include <deque>

using namespace std;


//User::User(const string& name, int regNo) : Person(name)
//{
   // this->name = name;
    //this->regNo = regNo;
//}
User::User(const string& name, int regNo) : Person(name), name(name), regNo(regNo) {}
int User::getRegNo() const {
    return regNo;
}
bool User:: usernameExists(const string& username) {
    ifstream file("users.txt");
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string storedUsername;
        iss >> storedUsername; // Extract username
        if (storedUsername == username) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}
double calculateLikeDislikeRatio(const vector<string>& videoData) {
    // Assuming the number of likes is at index 4 and dislikes at index 5
    int likes = stoi(videoData[4]);
    int dislikes = stoi(videoData[5]);
    if (likes + dislikes == 0) {
        return 0; // Avoid division by zero
    }
    return static_cast<double>(likes) / (likes + dislikes);
}

void User::saveNameToFile() const {
    ofstream file("users.txt", ios::app);
    if (file.is_open()) {
        file << this->name << endl; // Write the user's name followed by a newline
        file.close();
    } else {
        cout << "Unable to open file.";
    }
}

/*void User::createUser(const string& username, const string& userType) {
    ofstream file("users.txt", ios::app); // Open the file in append mode
    if (file.is_open()) {
        file << username << " " << userType << endl; // Append username and userType to the file
        file.close();
        cout << "User created successfully.\n";
    } else {
        cout << "Unable to open user database file.\n";
    }
}
*/

// Function to check if a username exists in the user.txt file
void User::identifyUserType() {
    // Function definition for identifyUserType
    string userType;
    if (!usernameExists(name)) {
        cout << "New user created: " << name << endl;
        //createUser(name, "user");
        userType = "user";
    } else {
        cout << "Welcome back, " << name << "!\n";
        userType = determineUserType(name); // Corrected function call
    }

    if (userType == "user") {
        cout << "You are a regular user.\n";
    } else if (userType == "creator") {
        cout << "You are a creator.\n";
    } else {
        cout << "Invalid user type.\n";
    }
}
string User::determineUserType(const string& username) {
    if (usernameExists(username)) {
        ifstream file("users.txt");
        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            string storedUsername, userType;
            iss >> storedUsername >> userType; // Extract username and user type
            if (storedUsername == username) {
                file.close();
                return userType;
            }
        }
    }
    return ""; // Return empty string if user not found
}
void User::getVideos() const {
    cout << "\tGetting videos.............\n";
    string keyword;
    cout << "Enter a keyword: ";
    cin >> keyword;

    VideoDatabase videoDB;
    if (!videoDB.loadFromFile("fake_youtube_data_updated.txt")) {
        cout << "Error loading video database.\n";
        return;
    }

    queue<vector<string>> videoQueue;
    int videosDisplayed = 0;
    for (auto it = videoDB.begin(); it != videoDB.end(); ++it) {
        const vector<string>& videoData = *it;
        if (videoData[1].find(keyword) != string::npos) { // Assuming title is at index 1
            videoQueue.push(videoData);
            ++videosDisplayed;
            if (videosDisplayed >= 20) // Display only 20 videos
                break;
        }
    }

    if (videoQueue.empty()) {
        cout << "No videos found with the given keyword.\n";
        return;
    }

    int choice;
    while (!videoQueue.empty()) {
        vector<string> videoData = videoQueue.front();
        videoQueue.pop();

        // Display video details...
        cout << "Video Title: " << videoData[1] << endl; // Assuming title is at index 1
        cout << "Channel: " << videoData[2] << endl;     // Assuming channel is at index 2

        cout << "1. Watch video\n";
        cout << "2. Return to menu\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                // Display the video

                // Ask if the user likes or dislikes the video
                // Store statistics about the video
                cout << "You watched the video: " << videoData[1] << endl;
                cout << "Did you like the video? (y/n): ";
                char like;
                cin >> like;
                if (like == 'y' || like == 'Y') {
                    // Increment like count for the video
                } else if (like == 'n' || like == 'N') {
                    // Increment dislike count for the video
                } else {
                    cout << "Invalid choice. Assuming dislike.\n";
                    // Increment dislike count for the video
                }
                break;
            case 2:
                return; // Return to the main menu
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}


void User::GetVideoRecommendations(const VideoDatabase& videoDB) const {
    string keyword;
    cout << "Enter a keyword: ";
    cin >> keyword;

    list<vector<string>> videoList; // List to store videos matching the keyword

    // Populate videoList with videos matching the keyword
    for (const auto& video : videoDB) {
        if (video[1].find(keyword) != string::npos) { // Assuming title is at index 1
            videoList.push_back(video);
        }
    }

    if (videoList.empty()) {
        cout << "No videos found with the given keyword.\n";
        return;
    }

    // Sort the videos based on like/dislike ratio
    videoList.sort([](const vector<string>& a, const vector<string>& b) {
        return calculateLikeDislikeRatio(a) > calculateLikeDislikeRatio(b);
    });

    // Display the top 10 videos
    cout << "Top 10 recommended videos:\n";
    int index = 1;
    for (const auto& video : videoList) {
        cout << index++ << ". Title: " << video[1] << " (Likes: " << video[4] << ", Dislikes: " << video[5] << ")\n";
        if (index > 10) break; // Display only the top 10 videos
    }

    // Ask the user for a video to watch or return to the main menu
    int videoChoice;
    do {
        cout << "Enter the number of the video you want to watch or type 'menu' to return: ";
        string input;
        cin >> input;
        if (input == "menu") {
            return;
        }
        stringstream ss(input);
        if (ss >> videoChoice && videoChoice >= 1 && videoChoice <= 10) {
            // Display the chosen video
            auto it = videoList.begin();
            advance(it, videoChoice - 1);
            const vector<string>& chosenVideo = *it;
            cout << "You chose: " << chosenVideo[1] << endl; // Assuming title is at index 1
            cout << "Channel: " << chosenVideo[2] << endl;    // Assuming channel is at index 2

            // Ask if the user likes or dislikes the video
            cout << "Did you like the video? (y/n): ";
            char like;
            cin >> like;
            if (like == 'y' || like == 'Y') {
                // Increment like count for the video
            } else if (like == 'n' || like == 'N') {
                // Increment dislike count for the video
            } else {
                cout << "Invalid choice. Assuming dislike.\n";
                // Increment dislike count for the video
            }
            break;
        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    } while (true); // Continue until a valid choice or 'menu' is entered
}
// Function to calculate the score of a channel
double calculateChannelScore(const std::string& channelName, const VideoDatabase& videoDB) {
    double totalScore = 0.0;
    int videoCount = 0;
    for (const auto& video : videoDB) {
        if (video[2] == channelName) { // Assuming channel name is at index 2
            totalScore += std::stod(video[3]); // Assuming video score is at index 3
            videoCount++;
        }
    }
    return (videoCount > 0) ? (totalScore / videoCount) : 0.0;
}


// Function to get trending channels
void User::Trending(const VideoDatabase& videoDB) const {
    // Calculate channel scores
    std::vector<std::pair<std::string, double>> channelScores; // Pair of channel name and score
    for (const auto& video : videoDB) {
        std::string channelName = video[2]; // Assuming channel name is at index 2
        auto it = std::find_if(channelScores.begin(), channelScores.end(),
                               [&channelName](const auto& pair) { return pair.first == channelName; });
        if (it == channelScores.end()) {
            double score = calculateChannelScore(channelName, videoDB);
            channelScores.emplace_back(channelName, score);
        }
    }

    // Sort channels based on scores
    std::sort(channelScores.begin(), channelScores.end(),
              [](const auto& a, const auto& b) { return a.second > b.second; });

    // Store top 10 channels in a deque
    std::deque<std::pair<std::string, double>> topChannels(channelScores.begin(),
                                                           channelScores.begin() + std::min(10, static_cast<int>(channelScores.size())));

    // Display top 10 channels
    cout << "Top 10 trending channels:\n";
    int index = 1;
    for (const auto& pair : topChannels) {
        cout << index++ << ". " << pair.first << " (Score: " << pair.second << ")\n";
    }

    // Ask the user for a channel to explore
    int channelChoice;
    do {
        cout << "Enter the number of the channel you want to explore (1-10): ";
        cin >> channelChoice;
    } while (channelChoice < 1 || channelChoice > 10);

    // Get the selected channel's name
    string selectedChannel = topChannels[channelChoice - 1].first;

    // Display videos of the selected channel
    std::cout << "Videos of channel " << selectedChannel << ":\n";
    for (const auto& video : videoDB) {
        if (video[2] == selectedChannel) { // Assuming channel name is at index 2
            std::cout << "- " << video[1] << std::endl; // Assuming video title is at index 1
        }
    }

    // Ask the user to choose a video or return to the main menu
    std::string videoChoice;
    do {
        std::cout << "Enter the title of the video you want to watch or type 'menu' to return: ";
        std::cin >> videoChoice;
        if (videoChoice == "menu") {
            return;
        }
        // Find the selected video in the database
        // Update the score based on user feedback (like or dislike)
        // Display the chosen video
        // Ask if the user likes or dislikes the video
        // Implement further logic here
    } while (true); // Continue until a valid choice or 'menu' is entered
}
