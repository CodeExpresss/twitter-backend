#include "client.hpp"

std::shared_ptr<UnitOfWork> HTTPClient::worker = make_shared<UnitOfWork>();
//регулярные выражения для GET
std::regex HTTPClient::get_profile_regex = std::regex("/api/profile/.+");
std::regex HTTPClient::current_user_regex = std::regex("/api/user/current/");
std::regex HTTPClient::get_news_feed_regex = std::regex("/api/tweet/index/.+");
std::regex HTTPClient::get_subscription_regex =
        std::regex("/api/user/subscription/.+");
std::regex HTTPClient::tag_search_regex = std::regex("/api/tweet/tag/.+");
//регулярные выражения для POST
std::regex HTTPClient::register_regex = std::regex("/api/user/register/");
std::regex HTTPClient::login_regex = std::regex("/api/user/login/");
std::regex HTTPClient::user_update_regex = std::regex("/api/user/update/");
std::regex HTTPClient::profile_update_regex =
        std::regex("/api/profile/update/");
std::regex HTTPClient::create_tweet_regex = std::regex("/api/tweet/create/");
std::regex HTTPClient::vote_tweet_regex = std::regex("/api/tweet/vote/");
std::regex HTTPClient::follow_regex = std::regex("/api/profile/follow/");
std::regex HTTPClient::make_subscription_regex =
        std::regex("/api/user/make_subscription");
const std::regex ln_regex("^Content-Disposition: form-data; name=\"([^\"]*)\".*");
enum ln_file_type {UNDEFINED, IMAGE, AUDIO} ln_current_file_type = UNDEFINED;

void HTTPClient::start() {
    read_request();
    check_deadline();
}

void HTTPClient::session() {
    std::string session_id;
    for (int i = request[http::field::cookie].find("=") + 1;
         i < request[http::field::cookie].size(); i++) {
        session_id += request[http::field::cookie][i];
    }

    std::shared_ptr<SessionController> cont =
            make_shared<SessionController>(worker);
    profile_id = cont->get_profile_id(session_id);
}

void HTTPClient::read_request() {
	std::cout << "here" << std::endl;
    auto self = shared_from_this();
    //http::request_parser<http::string_body> parser(request);
	//parser.body_limit(8192);
    http::async_read(socket, buffer, request, [self](beast::error_code ec, std::size_t bytes_transferred) {
    	std::cout << "bytes_transfered = " << bytes_transferred << std::endl;
    	boost::ignore_unused(bytes_transferred);
    	std::cout << "error_code = " << ec << std::endl;
    	if (!ec) {
    		self->process_request();
    	} else {
    		self->response.result(http::status::bad_request);
    	}
    });
}

std::string digestToString(const md5::digest_type &digest) {
	const auto charDigest = reinterpret_cast<const char*>(&digest);
	std::string result;
	boost::algorithm::hex(charDigest, charDigest + sizeof(md5::digest_type), std::back_inserter(result));
	return result;
}

void HTTPClient::routing_media() {
	response.set("Access-Control-Allow-Origin", "*");
	response.result(http::status::bad_request);
	std::stringstream ln_ss1(request.body()), ln_ss2(request.body());
	std::string ln_boundary, ln_tmp;
	if (!std::getline(ln_ss1, ln_boundary)) {
		return;
	}
	ln_boundary = ln_boundary.substr(0, ln_boundary.length() - 1); //чтобы убрать \r
	std::smatch ln_smatch;
	while (std::getline(ln_ss1, ln_tmp) && ln_tmp.length() > 1) {
		ln_tmp = ln_tmp.substr(0, ln_tmp.length() - 1);
		if (std::regex_match(ln_tmp, ln_smatch, ln_regex)) {
			if (ln_smatch[1].str().find("image") == 0) {
				ln_current_file_type = IMAGE;
			} else if (ln_smatch[1].str().find("audio") == 0) {
				ln_current_file_type = AUDIO;
			} else {
				break;
			}
		}
	}
	if (ln_current_file_type == UNDEFINED) {
		std::cout << "Error: undefined file type" << std::endl;
		return;
	}
	std::cout << "File type: " << ln_current_file_type << std::endl;
	size_t ln_file_start = ln_ss1.tellg(), ln_file_end, ln_current_start = ln_file_start, ln_current_end;
	ln_ss2.ignore(ln_file_start);
	while (true) {
		ln_file_end = ln_current_start;
		ln_ss1.ignore(UINT_MAX, '\n');
		ln_current_end = ln_ss1.tellg();
		if (ln_current_end == ln_current_start) {
			std::cout << "Error: can't parse form..." << std::endl;
			return;
		}
		if (ln_current_end - ln_current_start == ln_boundary.length() + 4) {
			ln_ss2 >> ln_tmp;
			if (ln_tmp.find(ln_boundary) == 0) {
				break;
			}
		}
		ln_current_start = ln_ss1.tellg();
		ln_ss2.ignore(ln_current_start - ln_ss2.tellg());
	}
	if (ln_file_end == ln_file_start) {
		std::cout << "Error: file is empty" << std::endl;
		return;
	}
	md5 ln_hash;
	md5::digest_type ln_digest;
	std::basic_string<char> ln_x = request.body().substr(ln_file_start, ln_file_end - ln_file_start - 2);
	ln_hash.process_bytes(ln_x.data(), ln_x.size());
	ln_hash.get_digest(ln_digest);
	std::string ln_filename = "/home/nick/";
	if (ln_current_file_type == IMAGE) {
		ln_filename += "images/" + digestToString(ln_digest);
	} else { //AUDIO
		ln_filename += "audio/" + digestToString(ln_digest);
	}
	std::ifstream ln_ifstream(ln_filename);
	while (ln_ifstream.good()) {
		std::istreambuf_iterator<char> ln_it1(ln_ifstream);
		const std::istreambuf_iterator<char> ln_it1_end;
		auto ln_it2 = request.body().begin() + ln_file_start;
		const auto ln_it2_end = request.body().begin() + ln_file_end - 2;
		while (ln_it1 != ln_it1_end && ln_it2 < ln_it2_end && *ln_it1 == *ln_it2) {
			ln_it1++;
			ln_it2++;
		}
		if (ln_it1 == ln_it1_end && ln_it2 == ln_it2_end) {
			break;
		}
		ln_filename += "0";
		ln_ifstream = std::ifstream(ln_filename);
	}
	if (!ln_ifstream.good()) {
		std::cout << "writing file..." << std::endl;
		std::ofstream ln_ofstream(ln_filename);
		for (auto it = request.body().begin() + ln_file_start, it_end =
				request.body().begin() + ln_file_end - 2; it < it_end; it++) {
			ln_ofstream << *it;
		}
		ln_ofstream.flush();
		ln_ofstream.close();
	}
	response.result(http::status::ok);
	beast::ostream(response.body()) << ln_filename;
	std::cout << "OK: media content loaded successfully" << std::endl << "----------" << std::endl;
}

void HTTPClient::process_request() {
    response.version(request.version());
    response.keep_alive(false);

    //session();

    response.set("Access-Control-Allow-Origin", "http://127.0.0.1:8080");
    response.set("Access-Control-Allow-Credentials", "true");
    std::cout << "method = " << request.method() << std::endl;

    switch (request.method()) {
        case http::verb::get:
            response.set(http::field::content_type, "application/json");
            response.result(http::status::ok);
            routing_get_method();
            break;
        case http::verb::post:
            response.result(http::status::ok);
            std::cout << "request content_type = " << request[http::field::content_type] << std::endl;
		    if (request[http::field::content_type].find("multipart/form-data") == 0) {
			    routing_media();
		    } else {
		    	routing_post_method();
		    }
            break;
        default:
            // неопределённый метод запроса
            response.result(http::status::bad_request);
            response.set(http::field::content_type, "application/json");
            beast::ostream(response.body()) << "Invalid request-method '"
                                            << std::string(request.method_string())
                                            << "'";
            break;
    }
    write_response();
}

void HTTPClient::routing_post_method() {
    boost::property_tree::ptree json_response;
    boost::property_tree::ptree json_request;

    std::string request_string = request.target().to_string();
    std::stringstream ss;
    ss << request.body().data();
    boost::property_tree::read_json(ss, json_request);
    ss.str(std::string());

    if (profile_id == NO_AUTH) {
        if (std::regex_match(request_string, register_regex)) {  // регистрац~ия

            auto username = json_request.get<std::string>("username");
            auto email = json_request.get<std::string>("email");
            auto password = json_request.get<std::string>("password");
            auto avatar = json_request.get<std::string>("avatar");
            auto birthday = json_request.get<std::string>("birthday");

            auto cont = make_shared<SignUpController<Serialize<Profile>>>(
                    worker, username, email, password, avatar, birthday);

            json_response = cont->get_queryset();

            boost::property_tree::json_parser::write_json(ss, json_response);
            beast::ostream(response.body()) << ss.str();

            return;

        } else if (std::regex_match(request_string, login_regex)) {  // логин

            auto email = json_request.get<std::string>("email");
            auto password = json_request.get<std::string>("password");

            auto cont = make_shared<LoginController<Serialize<res_data>>>(
                    worker, email, password);

            std::string session = cont->get_queryset();
            std::string query =
                    (boost::format("sessionid=%1%; HttpOnly; Path=/") % session).str();
            response.set(http::field::set_cookie, query);

            json_response.put("status", 200);

            boost::property_tree::json_parser::write_json(ss, json_response);
            beast::ostream(response.body()) << ss.str();

            return;

        } else {
            std::cout << "Bad gateway" << std::endl;

            response.result(http::status::not_found);
            response.set(http::field::content_type, "text/plain");
            beast::ostream(response.body()) << "File not found";
        }
    }

    if (std::regex_match(request_string, follow_regex)) {
        auto inviter_id = json_request.get<int>("inviter_id");
        auto invitee_id = json_request.get<int>("invitee_id");

        auto cont = make_shared<FollowController<Serialize<res_data>>>(
                worker, inviter_id, invitee_id);

        json_response = cont->get_queryset();

        boost::property_tree::json_parser::write_json(ss, json_response);
        beast::ostream(response.body()) << ss.str();

    } else if (std::regex_match(request_string, user_update_regex)) {
        auto id = json_request.get<int>("id");
        auto email = json_request.get<std::string>("email");
        auto password = json_request.get<std::string>("password");

        auto cont = make_shared<UpdateUserController<Serialize<User>>>(
                worker, id, email, password);

        json_response = cont->get_queryset();

        boost::property_tree::json_parser::write_json(ss, json_response);
        beast::ostream(response.body()) << ss.str();

        return;

    } else if (std::regex_match(request_string, profile_update_regex)) {
        auto id = json_request.get<int>("id");
        auto username = json_request.get<std::string>("username");
        auto birthday = json_request.get<std::string>("birthday");
        auto avatar = json_request.get<std::string>("avatar");

        auto cont = make_shared<UpdateProfileController<Serialize<Profile>>>(
                worker, id, username, birthday, avatar);

        json_response = cont->get_queryset();

        boost::property_tree::json_parser::write_json(ss, json_response);
        beast::ostream(response.body()) << ss.str();

        return;

    } else if (std::regex_match(request_string, create_tweet_regex)) {
        auto text = json_request.get<std::string>("text");
        auto id = json_request.get<int>("id");

        auto cont =
                make_shared<AddTweetController<Serialize<res_data>>>(worker, text, id);

        json_response = cont->get_queryset();

        boost::property_tree::json_parser::write_json(ss, json_response);
        beast::ostream(response.body()) << ss.str();

        return;

    } else if (std::regex_match(request_string, vote_tweet_regex)) {
        auto _profile_id = json_request.get<int>("profile_id");
        auto tweet_id = json_request.get<int>("tweet_id");

        auto cont = make_shared<VoteController<Serialize<res_data>>>(
                worker, _profile_id, tweet_id);

        json_response = cont->get_queryset();

        boost::property_tree::json_parser::write_json(ss, json_response);
        beast::ostream(response.body()) << ss.str();

        return;

    } else {
        std::cout << "Bad gateway" << std::endl;

        response.result(http::status::not_found);
        response.set(http::field::content_type, "text/plain");
        beast::ostream(response.body()) << "File not found";
    }
}

void HTTPClient::routing_get_method() {
    boost::property_tree::ptree json_response;

    std::string request_string = request.target().to_string();
    auto query_string_map = get_map_from_query(get_query_string(request_string));
    std::stringstream ss;

    if (std::regex_match(request_string, current_user_regex)) {
        auto cont = make_shared<GetProfileController<Serialize<Profile>>>(worker);

        json_response = cont->get_queryset(profile_id);

        boost::property_tree::json_parser::write_json(ss, json_response);
        beast::ostream(response.body()) << ss.str();

        return;

    } else if (std::regex_match(request_string, get_subscription_regex)) {
        auto cont =
                make_shared<SubscriptionController<Serialize<std::vector<Profile>>>>(
                        worker);

        json_response = cont->get_queryset(std::stoi(query_string_map["id"]));

        boost::property_tree::json_parser::write_json(ss, json_response);
        beast::ostream(response.body()) << ss.str();

        return;

    } else if (std::regex_match(request_string, get_news_feed_regex) &&
               profile_id != NO_AUTH) {
        auto cont = make_shared<IndexController<Serialize<content>>>(worker);

        json_response = cont->get_queryset(profile_id);

        boost::property_tree::json_parser::write_json(ss, json_response);
        beast::ostream(response.body()) << ss.str();

        return;

    } else if (std::regex_match(request_string, tag_search_regex)) {
        auto cont = make_shared<TagSearchController<Serialize<content>>>(worker);

        json_response = cont->get_queryset(query_string_map["tag"]);

        boost::property_tree::json_parser::write_json(ss, json_response);
        beast::ostream(response.body()) << ss.str();

        return;

    } else {
        std::cout << "Bad gateway" << std::endl;

        response.result(http::status::not_found);
        response.set(http::field::content_type, "text/plain");
        beast::ostream(response.body()) << "File not found";
    }
}

void HTTPClient::write_response() {
    auto self = shared_from_this();

    response.set(http::field::content_length, response.body().size());

    http::async_write(socket, response,
                      [self](beast::error_code ec, std::size_t) {
                          self->socket.shutdown(tcp::socket::shutdown_send, ec);
                          self->deadline_.cancel();
                      });
}

void HTTPClient::check_deadline() {
    auto self = shared_from_this();

    deadline_.async_wait([self](beast::error_code ec) {
        if (!ec) {
            self->socket.close(ec);
        }
    });
}

std::string HTTPClient::get_query_string(const std::string& url) {
    std::string result;

    static const std::regex parse_query{R"((/([^ ?]+)?)?/??\?([^/ ]+\=[^/ ]+))"};
    std::smatch match;

    if (std::regex_match(url, match, parse_query)) {
        result = match[match.size() - 1];
    }

    return result;
}

std::map<std::string, std::string> HTTPClient::get_map_from_query(
        const std::string& query) {
    std::map<std::string, std::string> data;
    std::regex pattern("([\\w+%]+)=([^&]*)");
    auto words_begin = std::sregex_iterator(query.begin(), query.end(), pattern);
    auto words_end = std::sregex_iterator();

    for (auto i = words_begin; i != words_end; i++) {
        std::string key = (*i)[1].str();
        std::string value = (*i)[2].str();
        data[key] = value;
    }

    return data;
}
