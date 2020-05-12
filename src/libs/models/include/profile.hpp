#ifndef PROFILE_HPP
#define PROFILE_HPP

#include "models_header.hpp"

class Profile {
public:
    Profile() : profile_id(1), user_id(1), username("user"), avatar("avatar"), birthday("birthday") {}

    Profile(int profile_id, int user_id, std::string _username, std::string _birthday, std::string _avatar):
    profile_id(profile_id),
    user_id(user_id),
    username(std::move(_username)),
    avatar(std::move(_avatar)),
    birthday(std::move(_birthday)) {};

    ~Profile() = default;

    std::string get_username() { return username; }
    std::string get_birthday() { return birthday; }

    void set_profile_id(int id) { profile_id = id; }
    void set_username(std::string _username) { username = std::move(_username); }
    void set_bithday(std::string _birthday) { birthday = std::move(_birthday); }

private:
    int profile_id;
    int user_id;
    std::string username;
    std::string avatar;
    std::string birthday;

};

#endif // PROFILE_HPP
