#ifndef PROFILE_REPOSITORY_HPP
#define PROFILE_REPOSITORY_HPP

#include "repositories_header.hpp"
#include "profile.hpp"

class ProfileRepository {
public:
    ProfileRepository(std::weak_ptr<DBController<DBConnection>> controller) : db_controller(controller) {}
    ~ProfileRepository() = default;

    std::vector<Profile> get_where() {}
	
    Profile get_by_id(int id, err_code &rc);
	
    void create(Profile &item, err_code &rc);
    void update(Profile &item, err_code &rc);
    void erase(int id, err_code &rc);

private:
    std::weak_ptr<DBController<DBConnection>> db_controller;
};

#endif // PROFILE_REPOSITORY_HPP
