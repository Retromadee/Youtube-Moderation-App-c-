#ifndef CREATOR_H
#define CREATOR_H

#include <iostream>
#include <string>
#include <map>
#include <numeric>
#include "VideoDatabase.h"

class Creator
{
public:
    Creator(const std::string& name, int id);
    bool updateLikeDislikeRatio();
    void show_channel_score();
    void create_video();
    void manage_video();
    void createVideo(const std::string& name, float duration);
    void renameVideo(const std::string& old_name, const std::string& new_name);
    void resetLikesDislikes(const std::string& name);
    void deleteVideo(const std::string& name);
    void saveNameToFile() const;
private:
    std::string name;
    int id;
    float like_dislike_ration_total;
    std::map<std::string, float> videos_and_rations;
    VideoDatabase videoDatabase;
};

#endif // CREATOR_H
