#include "../include/profile_repository.hpp" 

Profile ProfileRepository::get_by_id(int id, err_code &rc) 
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
	//Profile p = Profile(p_id, user_id, username, avatar, birthday);
	Profile p = Profile();
	return p;
}

void ProfileRepository::create(Profile &item, err_code &rc)
{
	/*int id = item.get_id();
	int user_id = item.get_user_id();
	std::string username = item.get_username();
	std::string avatar = item.get_avatar();
	std::string birthday = item.get_birthday();
	std::vector<std::vector<std::string>> query_result = {};
	std::string query = 
		(boost::format("insert into profile values(%1%, %2%, '%3%', '%4%', '2020-05-12');")
		% id % user_id % username % avatar).str();
	if (auto ctrl = db_controller.lock())
	{
		if (ctrl->run_query(query, query_result))
			rc = OK;
		else
			rc = NOT_EXIST;
	}
	else
		rc = NO_CTRL;*/
}

void ProfileRepository::update(Profile &item, err_code &rc)
{
	/*int id = item.get_id();
	std::string username = item.get_username();
	std::string avatar = item.get_avatar();
	std::string birthday = item.get_birthday();
	std::vector<std::vector<std::string>> query_result = {};
	std::string query = 
		(boost::format("update profile set username = '%1%', avatar = '%2%' where id = %3%;") 
		% username % avatar  % id).str();
	if (auto ctrl = db_controller.lock())
	{
		if (ctrl->run_query(query, query_result))
			rc = OK;
		else
			rc = NOT_EXIST;
	}
	else
		rc = NO_CTRL;*/
}

void ProfileRepository::erase(int id, err_code &rc)
{
	std::vector<std::vector<std::string>> query_result = {};
	std::string query = 
		(boost::format("update profile set deleted = true where id = %1%;") % id).str();
	if (auto ctrl = db_controller.lock())
	{
		if (ctrl->run_query(query, query_result))
			rc = OK;
		else
			rc = NOT_EXIST;
	}
	else
		rc = NO_CTRL;
}