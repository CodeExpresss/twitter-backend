#ifndef PROFILE_HPP
#define PROFILE_HPP

#include "models_header.hpp"

class Profile {
public:
    Profile() : profile_id(1), user_id(1), username("user"), avatar("avatar"), birthday("birthday") {}

    Profile(int profile_id, int user_id, std::string username, std::string avatar, std::string birthday):
    profile_id(profile_id),
    user_id(user_id),
    username(std::move(username)),
    avatar(std::move(avatar)),
    birthday(std::move(birthday)) {};

    ~Profile() = default;

    int get_profile_id() {return profile_id;}
    int get_user_id() {return user_id;}
    std::string get_username() {return username;}
    std::string get_avatar() {return avatar;}
    std::string get_birthday() {return birthday;}

    void set_profile_id(int id) { profile_id = id; }
    void set_user_id(int id) { user_id = id; }
    void set_username(std::string _username) { username = std::move(_username); }
    void set_avatar(std::string _avatar) {avatar = std::move(_avatar);}
    void set_bithday(std::string _birthday) { birthday = std::move(_birthday); }

private:
    int profile_id;
    int user_id;
    std::string username;
    std::string avatar;
    std::string birthday;

};

#endif // PROFILE_HPP
