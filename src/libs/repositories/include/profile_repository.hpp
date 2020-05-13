#ifndef PROFILE_REPOSITORY_HPP
#define PROFILE_REPOSITORY_HPP

#include "repositories_header.hpp"
#include "profile.hpp"

class ProfileRepository {
public:
    ProfileRepository(std::weak_ptr<DBController<DBConnection>> controller) : db_controller(controller) {}
    ~ProfileRepository() = default;

    std::vector<Profile> get_where() {}
	
    Profile get_by_id(int id, err_code &rc)
    {
        std::vector<std::vector<std::string>> query_result = {};
	    int p_id = 0, user_id = 0;
	    std::string username = "", avatar = "", birthday = "";
        std::string query = 
            (boost::format("select * from profile where id = %1%;") % id).str();
	    if (auto ctrl = db_controller.lock())
	    {
		    if (ctrl->run_query(query, query_result))
		    {
			    p_id = std::stoi(query_result[0][0]);
			    user_id = std::stoi(query_result[0][1]);
			    username = query_result[0][2];
			    avatar = query_result[0][3];
			    birthday = query_result[0][4];
			    rc = OK;
		    }
		    else
			    rc = NOT_EXIST;
	    }
	    else
		    rc = NO_CTRL;
	
	// need to specify the object with params
	    Profile p = Profile(p_id, user_id, username, avatar, birthday);
	//Profile p = Profile();
	    return p;
    }
	
    void create(Profile &item, err_code &rc);
    void update(Profile &item, err_code &rc);
    void erase(int id, err_code &rc);

private:
    std::weak_ptr<DBController<DBConnection>> db_controller;
};

#endif // PROFILE_REPOSITORY_HPP
