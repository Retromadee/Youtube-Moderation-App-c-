#include "Creator.h"
#include "VideoDatabase.h"
#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <list>
#include <algorithm>
#include <deque>
#include <numeric>
using namespace std;

Creator::Creator(const std::string& name, int id) : name(name), id(id), like_dislike_ration_total(0.0) {}

bool Creator::updateLikeDislikeRatio() {
    like_dislike_ration_total = std::accumulate(videos_and_rations.begin(), videos_and_rations.end(), 0.0,
        [](float sum, const std::pair<std::string, float>& p) {
            return sum + p.second;
        }
    );
    return true;
}
void Creator::saveNameToFile() const {
   ofstream file("creators.txt", ios::app);
    if (file.is_open()) {
        file << this->name << endl; // Write the creator's name followed by a newline
        file.close();
    } else {
        cout << "Unable to open file.";
    }
}

void Creator::show_channel_score() {
    updateLikeDislikeRatio();
    std::cout << "Channel score: " << like_dislike_ration_total << std::endl;
}

void Creator::create_video() {
    std::string videoName;
    float videoDuration;
    std::cout << "Enter the name of the video: ";
    std::cin >> videoName;
    std::cout << "Enter the duration of the video: ";
    std::cin >> videoDuration;
    createVideo(videoName, videoDuration);
}

void Creator::manage_video() {
    std::string action;
    std::cout << "Enter the name of the video you want to manage (rename/reset/delete): ";
    std::cin >> action;
    std::string video_name;
    std::cout << "Enter the name of the video: ";
    std::cin >> video_name;
    if (action == "rename") {
        std::string new_name;
        std::cout << "Enter the new name of the video: ";
        std::cin >> new_name;
        renameVideo(video_name, new_name);
    } else if (action == "reset") {
        resetLikesDislikes(video_name);
    } else if (action == "delete") {
        deleteVideo(video_name);
    } else {
        std::cout << "Invalid action. Please enter a valid action (rename/reset/delete)." << std::endl;
    }
}

void Creator::createVideo(const std::string& name, float duration) {
    videos_and_rations[name] = 0.0;
    videoDatabase.addVideo({name, std::to_string(duration)});
}

void Creator::renameVideo(const std::string& old_name, const std::string& new_name) {
    if (videos_and_rations.find(old_name) != videos_and_rations.end()) {
        float ratio = videos_and_rations[old_name];
        videos_and_rations.erase(old_name);
        videos_and_rations[new_name] = ratio;
    } else {
        std::cout << "Video not found." << std::endl;
    }
}

void Creator::resetLikesDislikes(const std::string& name) {
    if (videos_and_rations.find(name) != videos_and_rations.end()) {
        videos_and_rations[name] = 0.0;
    } else {
        std::cout << "Video not found." << std::endl;
    }
}

void Creator::deleteVideo(const std::string& name) {
    if (videos_and_rations.find(name) != videos_and_rations.end()) {
        videos_and_rations.erase(name);
    } else {
        std::cout << "Video not found." << std::endl;
    }
}
