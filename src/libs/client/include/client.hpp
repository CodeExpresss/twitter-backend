#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>
#include <regex>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>
#include <string>
#include "unit_of_work.hpp"
#include "controllers_types.hpp"
#include "serialize.hpp"
#include "profile.hpp"

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;

class HTTPClient : public std::enable_shared_from_this<HTTPClient> {
public:

    HTTPClient(tcp::socket socket) : socket(std::move(socket)) {}

    void start();

    static std::shared_ptr<UnitOfWork> worker;

private:

    //регулярные выражения для роутинга
    static std::regex register_regex;
    static std::regex get_profile_regex;
    static std::regex current_user_regex;
    static std::regex get_news_feed_regex;
    static std::regex login_regex;
    static std::regex user_update_regex;
    static std::regex profile_update_regex;
    static std::regex create_tweet_regex;
    static std::regex vote_tweet_regex;
    static std::regex follow_regex;
    static std::regex get_subscription_regex;
    static std::regex make_subscription_regex;

    std::string get_query_string(const std::string& url) {
        std::string result;

        static const std::regex parse_query{ R"((/([^ ?]+)?)?/??\?([^/ ]+\=[^/ ]+))"};
        std::smatch match;

        if (std::regex_match(url, match, parse_query)) {
            result = match[match.size() - 1];
        }

        return result;
    }

    std::map<std::string, std::string> get_map_from_query(const std::string& query) {
        std::map<std::string, std::string> data;
        std::regex pattern("([\\w+%]+)=([^&]*)");
        auto words_begin = std::sregex_iterator(query.begin(), query.end(), pattern);
        auto words_end = std::sregex_iterator();

        for (auto i = words_begin; i != words_end; i++)
        {
            std::string key = (*i)[1].str();
            std::string value = (*i)[2].str();
            data[key] = value;
        }

        return data;
    }

    tcp::socket socket; //сокет для подключения конкретного клиента
    beast::flat_buffer buffer{8192}; //буфер для чтения данных

    http::request<http::string_body> request; //объект запроса
    http::response<http::dynamic_body> response; //объект ответа

    //таймер для "протухания" соеденений
    net::steady_timer deadline_{
            socket.get_executor(), std::chrono::seconds(60)};

    HTTPClient(const HTTPClient&) = delete;
    HTTPClient(const HTTPClient&&) = delete;
    HTTPClient&operator= (const HTTPClient&) = delete;
    HTTPClient&operator= (HTTPClient&&) = delete;

    void read_request();

    // Метод для обработки запроса
    void process_request();

    void routing_get_method();

    void routing_post_method();

    // записать ответ в сокет
    void write_response();

    // Проверить время подключения
    void check_deadline();
};

std::shared_ptr<UnitOfWork> HTTPClient::worker = make_shared<UnitOfWork>();
//регулярные выражения для GET
std::regex HTTPClient::get_profile_regex = std::regex("/api/profile/current/.+");
std::regex HTTPClient::current_user_regex = std::regex("/api/user/current/.+");
std::regex HTTPClient::get_news_feed_regex = std::regex("/api/tweet/index/.+");
std::regex HTTPClient::get_subscription_regex = std::regex("/api/user/subscription/.+");
//регулярные выражения для POST
std::regex HTTPClient::register_regex = std::regex("/api/user/register/");
std::regex HTTPClient::login_regex = std::regex("/api/user/login/");
std::regex HTTPClient::user_update_regex = std::regex("/api/user/update/");
std::regex HTTPClient::profile_update_regex = std::regex("/api/profile/update/");
std::regex HTTPClient::create_tweet_regex = std::regex("/api/tweet/create/");
std::regex HTTPClient::vote_tweet_regex = std::regex("/api/tweet/vote/");
std::regex HTTPClient::follow_regex = std::regex("/api/profile/follow/");
std::regex HTTPClient::make_subscription_regex = std::regex("/api/user/make_subscription");

void HTTPClient::start() {
    read_request();
    check_deadline();
}

void HTTPClient::read_request() {
    auto self = shared_from_this();

    http::async_read(
            socket,
            buffer,
            request,
            [self](beast::error_code ec,
                   std::size_t bytes_transferred) {
                boost::ignore_unused(bytes_transferred);
                if(!ec)
                    self->process_request();
            });
}

void HTTPClient::process_request() {
    response.version(request.version());
    response.keep_alive(false);

    switch (request.method()) {
        case http::verb::get:
            response.set(http::field::content_type, "application/json");
            response.set("Access-Control-Allow-Origin", "*");
            response.result(http::status::ok);
            routing_get_method();
            break;
        case http::verb::post:
            response.result(http::status::ok);
            response.set("Access-Control-Allow-Origin", "*");
            routing_post_method();
            break;
        default:
            // неопределённый метод запроса
            response.result(http::status::bad_request);
            response.set("Access-Control-Allow-Origin", "*");
            response.set(http::field::content_type, "application/json");
            beast::ostream(response.body())
                    << "Invalid request-method '"
                    << std::string(request.method_string())
                    << "'";
            break;
    }
    write_response();
}

/*
void my_handle_read(const boost::system::error_code& e, std::size_t bytes_transferred)
{
	if (!e)
	{
		std::stringstream strm1;
		std::string buffer_data = buffer_.data();
		strm1 << buffer_data;
		
		std::string method;
		std::smatch match_method;
		std::regex regex_method ("\\b([^ ]*)( )([^ ]*)( HTTP/1.1)([^ ]*)");
		
		std::string content_type;
		std::smatch match_content_type;
		std::regex regex_content_type ("\\b(Content-type: )([^ ]*)");
		
		std::string line;
		
		while (std::getline(strm1, line)) {
			if (std::regex_search(line, match_method, regex_method)) {
				method = match_method[0];
				method = method.substr(0, method.find(' '));
				boost::trim(method);
				//std::cout << method << std::endl;
			}
			if (std::regex_search(line, match_content_type, regex_content_type))     {
				content_type = match_content_type[0];
				boost::erase_all(content_type, "Content-type:");
				boost::trim(content_type);
				//std::cout << content_type << std::endl;
			}
		}
		
		if (method == "POST") {
			if (content_type == "multipart/form-data") {
				
				std::string content_length;
				std::smatch match_content_length;
				std::regex regex_content_length ("\\b(Content-Length: )([^ ]*)");
				
				std::string filename;
				std::smatch match_filename;
				std::regex regex_filename ("\\b(filename)([^ ]*)");
				
				std::string action;
				std::smatch match_action;
				std::regex regex_action ("\\b(name)([^ ]*)");
				
				std::string boundary;
				std::smatch match_boundary;
				std::regex regex_boundary ("([-]{10,}[0-9]{10,})");
				
				std::string line;
				
				strm1.clear();
				strm1 << buffer_data;
				while (std::getline(strm1, line)) {
					if (std::regex_search(line, match_content_length, regex_content_length)) {
						//Content-Length: 14710
						content_length = match_content_length[0];
						boost::erase_all(content_length, "Content-Length:");
						boost::trim(content_length);
						//std::cout << content_length << std::endl;
					}
					if (std::regex_search(line, match_filename, regex_filename)) {
						filename = match_filename[0];
						boost::erase_all(filename, "\"");
						boost::erase_all(action, ";");
						boost::erase_all(filename, "filename=");
						std::size_t found = filename.find_last_of(".");
						std::size_t len = filename.length();
						std::string mime = filename.substr(found, len);
						boost::trim(filename);
						//std::cout << filename << std::endl;
						//std::cout << mime << std::endl;
					}
					if (std::regex_search(line, match_action, regex_action)) {
						action = match_action[0];
						boost::erase_all(action, "\"");
						boost::erase_all(action, ";");
						boost::erase_all(action, "name=");
						boost::trim(action);
						//std::cout << action << std::endl;
					}
					if (std::regex_search(line, match_boundary, regex_boundary)) {
						boundary = match_boundary[0];
						boost::trim(boundary);
						//std::cout << boundary << std::endl;
					}
				}
				
				//pubseekpos works as expected, but useless here
				//strmbuffer_.pubseekpos(bytes_transferred);
				
				//content length minus bytes_transfered does NOT yield
				//the right result. The number, 392, is the 'magic' number
				//adjustment for this file size, approx 14.2kb, that i found
				//by trial and error.
				//Adjusting the magic number is necessary for every image size
				//in order to avoid a segfault.
				//bytes_transferred, for each read(), is the only 'reliable'
				//number with which to work, as far as i know.
				//If there is a brainier way of calculating this,
				//i don't care, anymore.
				int n_content_length = std::stoi(content_length);
				int transfer = n_content_length - bytes_transferred + 392;
				auto self(shared_from_this());
				boost::asio::async_read(
						socket_,
						strmbuffer_,
						boost::asio::transfer_exactly(transfer),
						strand_.wrap(
								[this, self, boundary](boost::system::error_code ec, std::size_t bytes_transferred)
								{
									std::stringstream strm2;
									strm2 << &strmbuffer_;
									std::string line;
									unsigned bufsize = 512;
									while (std::getline(strm2, line))
									{
										if(line.length() == 1){
											std::string output_file = "../../upload/test.png";
											std::ofstream outfile(output_file);
											char c;
											unsigned bl = boundary.length();
											bool endfile = false;
											if(outfile){
												char buffer[bufsize];
												while(!endfile){
													unsigned j = 0;
													unsigned k;
													while(j < bufsize && strm2.get(c) && !endfile){
														buffer[j] = c;
														k = 0;
														while(boundary[bl - 1 - k] == buffer[j - k]){
															if(k >= bl - 1){
																endfile = true;
																break;
															}
															k++;
														}
														j++;
													}
													outfile.write(buffer, j);
													j = 0;
												};
												outfile.close();
												std::cout << "outfile close" << std::endl;
												break;
											}
										}
									}
								}
						)
				);
			}
			else {
				// POST AJAX
				std::cout << "connection " << method << std::endl;
			}
		}
		else {
			boost::tribool result;
			boost::tie(result, boost::tuples::ignore) = request_parser_.parse(
					request_, buffer_.data(), buffer_.data() + bytes_transferred);
			
			if (result)
			{
				request_handler_.handle_request(
						request_,
						reply_);
				
				boost::asio::async_write(
						socket_,
						reply_.to_buffers(),
						strand_.wrap(
								boost::bind(
										&connection::handle_write,
										shared_from_this(),
										boost::asio::placeholders::error)
						));
			}
			else if (!result)
			{
				reply_ = reply::stock_reply(reply::bad_request);
				boost::asio::async_write(
						socket_,
						reply_.to_buffers(),
						strand_.wrap(
								boost::bind(&connection::handle_write, shared_from_this(),
								            boost::asio::placeholders::error)));
			}
			else
			{
				socket_.async_read_some(
						boost::asio::buffer(buffer_),
						strand_.wrap(
								boost::bind(
										&connection::handle_read,
										shared_from_this(),
										boost::asio::placeholders::error,
										boost::asio::placeholders::bytes_transferred)));
			}
		}
	}
}
*/

void HTTPClient::routing_post_method() {

    boost::property_tree::ptree json_response;
    boost::property_tree::ptree json_request;

    //boost::beast::http::body_type::value_type x;
	{ //получение приходящих бинарных данных (post multipart/form-data)
		std::ofstream f("/home/nick/twitter_backend_data.png");
		//f << request.body().data();
		auto b = request.body();
		std::stringstream ss(b);
		std::string mstr;
		size_t count = 0;
		while (getline(ss, mstr)) {
			std::cout << "string = " << mstr << std::endl;
			if (++count == 4) {
				break;
			}
		}
		while (getline(ss, mstr)) {
			f << mstr << '\n';
			if (++count == 1320) {
				break;
			}
		}
		std::cout << "count = " << count << std::endl;
		//f << b;
		f.flush();
		f.close();
		std::cout << "OK" << std::endl;
		return;
	}
    std::string request_string = request.target().to_string();
    std::stringstream ss;
    ss << request.body().data();
    boost::property_tree::read_json(ss, json_request);
    ss.str(std::string());

    if (std::regex_match(request_string, register_regex)) { // регистрац~ия

//	std::shared_ptr<SignUpController<Serialize<Profile>>> cont =
//                make_shared<SignUpController<Serialize<Profile>>>(worker);
//
//        json_response = cont->get_queryset();


        boost::property_tree::json_parser::write_json(ss, json_response);
        beast::ostream(response.body()) << ss.str();

        return;

    } else if (std::regex_match(request_string, login_regex)) { // логин

        auto email = json_request.get<std::string>("email");
        auto password = json_request.get<std::string>("password");

        std::shared_ptr<LoginController<Serialize<std::pair<unsigned short int, std::string>>>> cont =
                    make_shared<LoginController<Serialize<std::pair<unsigned short int, std::string>>>>(worker,
        email, password);

        json_response = cont->get_queryset();

        boost::property_tree::json_parser::write_json(ss, json_response);
        beast::ostream(response.body()) << ss.str();

        return;

    } else if(std::regex_match(request_string, follow_regex)) {
        auto inviter_id = json_request.get<int>("inviter_id");
        auto invitee_id = json_request.get<int>("invitee_id");

        std::shared_ptr<FollowController<Serialize<std::pair<unsigned short int, std::string>>>> cont =
                make_shared<FollowController<Serialize<std::pair<unsigned short int, std::string>>>>(worker, inviter_id, invitee_id);

        json_response = cont->get_queryset();

        boost::property_tree::json_parser::write_json(ss, json_response);
        beast::ostream(response.body()) << ss.str();

    } else if (std::regex_match(request_string, user_update_regex)) {

        auto id = json_request.get<int>("id");
        auto email = json_request.get<std::string>("email");
        auto password = json_request.get<std::string>("password");

        std::shared_ptr<UpdateUserController<Serialize<User>>> cont =
                    make_shared<UpdateUserController<Serialize<User>>>(worker,
        id, email, password);

        json_response = cont->get_queryset();

        boost::property_tree::json_parser::write_json(ss, json_response);
        beast::ostream(response.body()) << ss.str();

        return;

    } else if (std::regex_match(request_string, profile_update_regex)) {

        auto id = json_request.get<int>("id");
        auto username = json_request.get<std::string>("username");
        auto birthday = json_request.get<std::string>("birthday");
        auto avatar = json_request.get<std::string>("avatar");

        std::shared_ptr<UpdateProfileController<Serialize<Profile>>> cont =
                    make_shared<UpdateProfileController<Serialize<Profile>>>(worker,
        id, username, birthday, avatar);

        json_response = cont->get_queryset();

        boost::property_tree::json_parser::write_json(ss, json_response);
        beast::ostream(response.body()) << ss.str();

        return;

    } else if (std::regex_match(request_string, create_tweet_regex)) {

        auto text = json_request.get<std::string>("text");
        auto id = json_request.get<int>("id");

        std::shared_ptr<AddTweetController<Serialize<std::pair<unsigned short int, std::string>>>> cont =
                    make_shared<AddTweetController<Serialize<std::pair<unsigned short int, std::string>>>>(worker,
        text, id);

        json_response = cont->get_queryset();

        boost::property_tree::json_parser::write_json(ss, json_response);
        beast::ostream(response.body()) << ss.str();

        return;

    } else if (std::regex_match(request_string, vote_tweet_regex)) {

        auto profile_id = json_request.get<int>("profile_id");
        auto tweet_id = json_request.get<int>("tweet_id");

        std::shared_ptr<VoteController<Serialize<std::pair<unsigned short int, std::string>>>> cont =
                    make_shared<VoteController<Serialize<std::pair<unsigned short int, std::string>>>>(worker,
        profile_id, tweet_id);

        json_response = cont->get_queryset();

        boost::property_tree::json_parser::write_json(ss, json_response);
        beast::ostream(response.body()) << ss.str();

        return;

    } else if (std::regex_match(request_string, make_subscription_regex)) {

        auto inviter_id = json_request.get<int>("inviter_id");
        auto invitee_id = json_request.get<int>("invitee_id");

//        std::shared_ptr<VoteController<Serialize<std::pair<unsigned short int, std::string>>>> cont =
//                make_shared<VoteController<Serialize<std::pair<unsigned short int, std::string>>>>(worker,
//                                                                                                   profile_id, tweet_id);

//        json_response = cont->get_queryset();

        boost::property_tree::json_parser::write_json(ss, json_response);
        beast::ostream(response.body()) << ss.str();

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
    auto query_string_map = get_map_from_query( get_query_string(request_string) );
    std::stringstream ss;

    if (request.target() == "/echo") {
        response.set(http::field::content_type, "text/html");
        beast::ostream(response.body())
                << request.method() << "\n"
                << request.target() << "\n";

    } else if (std::regex_match(request_string, current_user_regex)) {

        std::shared_ptr<GetProfileController<Serialize<Profile>>> cont =
                make_shared<GetProfileController<Serialize<Profile>>>(worker);

        json_response = cont->get_queryset(std::stoi(query_string_map["id"]));

        boost::property_tree::json_parser::write_json(ss, json_response);
        beast::ostream(response.body()) << ss.str();

        return;

    } else if (std::regex_match(request_string, get_profile_regex)) {

        std::shared_ptr<GetProfileController<Serialize<Profile>>> cont =
                make_shared<GetProfileController<Serialize<Profile>>>(worker);

        json_response = cont->get_queryset(std::stoi(query_string_map["id"]));

        boost::property_tree::json_parser::write_json(ss, json_response);
        beast::ostream(response.body()) << ss.str();

        return;

    } else if (std::regex_match(request_string, get_subscription_regex)) {

        std::shared_ptr<SubscriptionController<Serialize<std::vector<Profile>>>> cont =
            make_shared<SubscriptionController<Serialize<std::vector<Profile>>>>(worker);

        json_response = cont->get_queryset(std::stoi(query_string_map["id"]));

        boost::property_tree::json_parser::write_json(ss, json_response);
        beast::ostream(response.body()) << ss.str();

        return;

    } else if (std::regex_match(request_string, get_news_feed_regex)) {

        std::shared_ptr<IndexController<Serialize< std::vector<std::pair<Tweet, Profile> > > > > cont =
                make_shared<IndexController<Serialize< std::vector<std::pair<Tweet, Profile>>>>>(worker);

        json_response = cont->get_queryset(std::stoi(query_string_map["id"]));

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

    http::async_write(
            socket,
            response,
            [self](beast::error_code ec, std::size_t) {
                self->socket.shutdown(tcp::socket::shutdown_send, ec);
                self->deadline_.cancel();
            });
}

void HTTPClient::check_deadline() {
    auto self = shared_from_this();

    deadline_.async_wait(
            [self](beast::error_code ec) {
                if(!ec) {
                    self->socket.close(ec);
                }
            });
}

#endif