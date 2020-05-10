#ifndef PROFILE_REPOSITORY_HPP
#define PROFILE_REPOSITORY_HPP

#include "repositories_header.hpp"
#include "profile.hpp"

class ProfileRepository {
public:
    ProfileRepository(std::weak_ptr<DBController<DBConnection>> controller) : db_controller(controller) {}
    ~ProfileRepository() = default;

    std::vector<Profile> get_where() {}
	
    Profile get_by_id(int id, error_code &rc) 
	{
		std::string query = format("select * from profile where id = %d;", id);
		std::vector<std::string> query_result = {};
		int id = 0, user_id = 0;
		std::string username = "", avatar = "", birthday = "";
		if (auto ctrl = db_controller.lock())
		{
			ctrl->run_query(query, query_result);
			if (query_result.size() == 5)
			{
				id = std::stoi(query_result[0]);
				user_id = std::stoi(query_result[1]);
				username = query_result[2];
				avatar = query_result[3];
				birthday = query_result[4];
				rc = OK;
			}
			else
				rc = NOT_EXIST;
		}
		else
			rc = NO_CTRL;
		
		// need to specify the object with params
		Profile p();
		return p;
	}
	
    void create(Profile item) {}
    void update(Profile item) {}
    void erase(int id) {}

private:
    std::weak_ptr<DBController<DBConnection>> db_controller;
};

#endif // PROFILE_REPOSITORY_HPP
