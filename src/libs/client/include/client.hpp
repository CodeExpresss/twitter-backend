#ifndef CLIENT_HPP
#define CLIENT_HPP

#define NO_AUTH -1

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
using res_data = std::pair<unsigned short int, std::string>;
using content = std::vector<std::pair<Tweet, Profile>>;
using profile = std::pair<Profile, bool>;

class HTTPClient : public std::enable_shared_from_this<HTTPClient> {
public:
    HTTPClient(tcp::socket socket)
            : socket(std::move(socket)), profile_id(NO_AUTH) {}

    void start();

    static std::shared_ptr<UnitOfWork> worker;

private:
    //регулярные выражения для роутинга
    static std::regex register_regex;
    static std::regex get_profile_regex;
    static std::regex current_user_regex;
    static std::regex get_news_feed_regex;
    static std::regex login_regex;
    static std::regex logout_regex;
    static std::regex user_update_regex;
    static std::regex profile_update_regex;
    static std::regex create_tweet_regex;
    static std::regex vote_tweet_regex;
    static std::regex follow_regex;
    static std::regex get_subscription_regex;
    static std::regex make_subscription_regex;
    static std::regex tag_search_regex;

    std::string get_query_string(const std::string& url);
    std::map<std::string, std::string> get_map_from_query(
            const std::string& query);

    tcp::socket socket;  //сокет для подключения конкретного клиента
    beast::flat_buffer buffer{8192};  //буфер для чтения данных

    http::request<http::string_body> request;     //объект запроса
    http::response<http::dynamic_body> response;  //объект ответа

    int profile_id;
    std::string session_id;

    //таймер для "протухания" соеденений
    net::steady_timer deadline_{socket.get_executor(), std::chrono::seconds(60)};

    HTTPClient(const HTTPClient&) = delete;
    HTTPClient(const HTTPClient&&) = delete;
    HTTPClient& operator=(const HTTPClient&) = delete;
    HTTPClient& operator=(HTTPClient&&) = delete;

    void read_request();
    // Метод для обработки запроса
    void process_request();

    void routing_get_method();

    void routing_post_method();

    // записать ответ в сокет
    void write_response();

    // Проверить время подключения
    void check_deadline();

    void session();
};

#endif
