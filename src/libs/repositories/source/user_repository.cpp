#include "../include/user_repository.hpp"

User UserRepository::get_by_id(int id, err_code &rc)
{
	std::vector<std::vector<std::string>> query_result = {};
	int user_id = 0;
	std::string password = "", email = "", session = "";
	bool is_active = false;
    std::string query =
        (boost::format("select * from users where id = %1%;") % id).str();
	if (auto ctrl = db_controller.lock())
	{
		if (ctrl->run_query(query, query_result) && query_result.size() > 0)
		{
			if (!query_result[0][4].compare("t"))
			{
				user_id = std::stoi(query_result[0][0]);
				password = query_result[0][1];
				email = query_result[0][2];
				session = query_result[0][3];
				is_active = true;
				rc = OK;
			}
			else
				rc = DELETED;
		}
		else
			rc = NOT_EXIST;
	}
	else
		rc = NO_CTRL;

	User u = User(user_id, password, email, session, is_active);
	return u;
}

User UserRepository::get_by_email(std::string email, err_code &rc) {
    std::vector<std::vector<std::string>> query_result = {};
    int user_id = 0;
    std::string password = "", session = "";
    bool is_active = false;
    std::string query =
            (boost::format("select * from users where email = '%1%';") % email).str();
    if (auto ctrl = db_controller.lock())
    {
        if (ctrl->run_query(query, query_result) && query_result.size() > 0)
        {
            if (!query_result[0][3].compare("t"))
            {
                user_id = std::stoi(query_result[0][0]);
                password = query_result[0][1];
                session = query_result[0][4];
                is_active = true;
                rc = OK;
            }
            else
                rc = DELETED;
        }
        else
            rc = NOT_EXIST;
    }
    else
        rc = NO_CTRL;

    User u = User(user_id, password, email, session, is_active);
    return u;
}

bool UserRepository::check_user_email(User& item, err_code& rc) {
	std::vector<std::vector<std::string>> query_result = {};
    std::string email = item.get_email();
    std::string query =
        (boost::format("select is_active from users where email = %1%;")
         % email).str();
    bool result = false;
	if (auto ctrl = db_controller.lock()) {
		if (ctrl->run_query(query, query_result) && query_result.size() > 0) {
            if (!query_result[0][0].compare("t")) {
                result =  true;
                rc = OK;
            }
            else {
                rc = DELETED;
            }
		}
        else {
            rc = NOT_EXIST;
        }
	}
	else {
		rc = NO_CTRL;
    }

	return result;
}

void UserRepository::create(User &item, err_code &rc)
{
	int user_id = item.get_user_id();
	std::string password = item.get_password();
	std::string email = item.get_email();
	std::string session = item.get_session();
	bool is_active = item.get_is_active();
	std::vector<std::vector<std::string>> query_result = {};
	std::string query = 
		(boost::format("insert into users values(%1%, '%2%', '%3%', %4%, %5%);")
		% user_id % password % email % boost::io::group(std::boolalpha, is_active) % session).str();
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

void UserRepository::update(User &item, err_code &rc)
{
	int id = item.get_user_id();
	std::string password = item.get_password();
	std::string email = item.get_email();
	std::string session = item.get_session();
	bool is_active = item.get_is_active();
	std::vector<std::vector<std::string>> query_result = {};
	std::string query = 
		(boost::format("update users set password = '%1%', email = '%2%', session = %3%, is_active = %4% where id = %5%;") 
		% password % email % session % boost::io::group(std::boolalpha, is_active) % id).str();
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

void UserRepository::erase(int id, err_code &rc)
{
	std::vector<std::vector<std::string>> query_result = {};
	std::string query = 
		(boost::format("update users set is_active = false where id = %1%;") % id).str();
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
