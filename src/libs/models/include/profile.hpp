#ifndef PROFILE_HPP
#define PROFILE_HPP

#include "types.hpp"

class Profile {
public:
    Profile() : profile_id(1), user_id(1), username("user"), avatar("avatar"), birthday("birthday") {}
    ~Profile() = default;
private:
    int profile_id;
    int user_id;
    std::string username;
    std::string avatar;
    std::string birthday;

};

#endif // PROFILE_HPP
