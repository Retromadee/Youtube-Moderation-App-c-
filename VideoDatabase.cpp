#include "VideoDatabase.h"
#include <iostream>
#include <string>
#include <queue>
#include <list>
#include <algorithm>
#include <deque>
#include<string>
#include<fstream>



VideoDatabase::VideoDatabase() {}

VideoDatabase::~VideoDatabase() {}

bool VideoDatabase::loadFromFile(const std::string &filename) {
    std::ifstream file("fake_youtube_data_updated.txt");
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::vector<std::string> videoData;
        std::string token;
        while (std::getline(ss, token, ',')) {
            videoData.push_back(token);
        }
        videos.push_back(videoData);
    }

    file.close();
    return true;
}

void VideoDatabase::addVideo(const std::vector<std::string> &videoData) {
    videos.push_back(videoData);
}

void VideoDatabase::removeVideo(int video_id) {
    auto it = std::remove_if(videos.begin(), videos.end(),
                             [video_id](const std::vector<std::string> &videoData) {
                                 return std::stoi(videoData[0]) == video_id;
                             });
    if (it != videos.end()) {
        videos.erase(it, videos.end());
    } else {
        std::cerr << "Video with ID " << video_id << " not found.\n";
    }
}

std::vector<std::vector<std::string>>::const_iterator VideoDatabase::begin() const {
    return videos.begin();
}

std::vector<std::vector<std::string>>::const_iterator VideoDatabase::end() const {
    return videos.end();
}
