#ifndef VIDEO_DATABASE_H
#define VIDEO_DATABASE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

class VideoDatabase {
public:
    VideoDatabase();
    ~VideoDatabase();

    bool loadFromFile(const std::string& filename);
    void addVideo(const std::vector<std::string>& videoData);
    void removeVideo(int video_id);
    std::vector<std::vector<std::string>>::const_iterator begin() const;
    std::vector<std::vector<std::string>>::const_iterator end() const;

private:
    std::vector<std::vector<std::string>> videos;
};

#endif // VIDEO_DATABASE_H

