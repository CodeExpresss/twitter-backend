#ifndef PROFILE_HPP
#define PROFILE_HPP

#include "models_header.hpp"

class Profile {
public:
    Profile();

    Profile(int profile_id, int user_id, std::string username,
            std::string avatar, std::string birthday);
    ~Profile() = default;

    int get_profile_id();
    int get_user_id();
    std::string get_username();
    std::string get_avatar();
    std::string get_birthday();

    void set_profile_id(int id);
    void set_user_id(int id);
    void set_username(std::string _username);
    void set_avatar(std::string _avatar);
    void set_bithday(std::string _birthday);

private:
    int profile_id;
    int user_id;
    std::string username;
    std::string avatar;
    std::string birthday;

};

#endif // PROFILE_HPP
