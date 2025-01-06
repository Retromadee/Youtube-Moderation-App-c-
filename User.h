#ifndef _USER_H_
#define _USER_H_

#include <string>
#include <stdexcept>
#include "Person.h"
#include "VideoDatabase.h"


using namespace std;

class User : public Person {
public:
    User(const string& name, int regNo);
    int getRegNo() const;
    void getVideos() const;
    void Trending(const VideoDatabase& videoDB) const;
    void saveNameToFile()const;
    bool usernameExists(const string& username);
    void identifyUserType();
    string determineUserType(const std::string& username);
    //void createUser(const std::string& username, const std::string& userType);
    void GetVideoRecommendations(const VideoDatabase& videoDB) const;





private:
    int regNo;
    string name;
};

#endif // _USER_H_
