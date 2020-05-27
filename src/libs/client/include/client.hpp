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
std::regex HTTPClient::get_profile_regex = std::regex("/api/profile/.+");
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
    std::cout << "Cookie" << request[http::field::cookie] << std::endl;

    response.set("Access-Control-Allow-Origin", "http://127.0.0.1:8080");
    response.set("Access-Control-Allow-Credentials", "true");

    switch (request.method()) {
        case http::verb::get:
            response.set(http::field::content_type, "application/json");
            response.result(http::status::ok);
            routing_get_method();
            break;
        case http::verb::post:
            response.result(http::status::ok);
            routing_post_method();
            break;
        default:
            // неопределённый метод запроса
            response.result(http::status::bad_request);
            response.set(http::field::content_type, "application/json");
            beast::ostream(response.body())
                    << "Invalid request-method '"
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
    response.set(http::field::set_cookie, "sessionid=38afes7a8; HttpOnly; Path=/");

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