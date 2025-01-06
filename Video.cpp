
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Video {
private:
    int video_id;
    std::string video_name;
    std::string video_duration;
    int no_likes;
    int no_dislikes;
    std::string channel_name;

public:
    // Constructor
    Video(int id, const std::string& name, const std::string& duration,
          int likes, int dislikes, const std::string& channel)
        : video_id(id), video_name(name), video_duration(duration),
          no_likes(likes), no_dislikes(dislikes), channel_name(channel) {}

    // Accessors
    int getVideoId() const { return video_id; }
    const std::string& getVideoName() const { return video_name; }
    const std::string& getVideoDuration() const { return video_duration; }
    int getLikes() const { return no_likes; }
    int getDislikes() const { return no_dislikes; }
    const std::string& getChannelName() const { return channel_name; }

    // Method to display video details
    void displayDetails() const {
        std::cout << "Video ID: " << video_id << std::endl;
        std::cout << "Name: " << video_name << std::endl;
        std::cout << "Duration: " << video_duration << std::endl;
        std::cout << "Likes: " << no_likes << std::endl;
        std::cout << "Dislikes: " << no_dislikes << std::endl;
        std::cout << "Channel: " << channel_name << std::endl;
    }
};
