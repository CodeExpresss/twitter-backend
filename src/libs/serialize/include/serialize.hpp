#ifndef SERIALIZE_HPP
#define SERIALIZE_HPP

#include <boost/property_tree/ptree.hpp>
#include <string>
#include "profile.hpp"
#include "tag.hpp"
#include "user.hpp"
#include "tweet.hpp"


template<class Type> struct Serialize;

template<> struct Serialize<Profile> {
    boost::property_tree::ptree operator() (Profile profile) {
        boost::property_tree::ptree profile_tree;

        profile_tree.put("nickname", profile.get_username());
        profile_tree.put("birthday", profile.get_birthday());

        return profile_tree;
    }
};

template<> struct Serialize<std::vector<Tag>> {
    boost::property_tree::ptree  operator() (std::vector<Tag> tags) {
        boost::property_tree::ptree tags_tree;

        for(auto & tag : tags) {
            tags_tree.put_value(tag.get_title());
        }

        return tags_tree;
    }
};

template<> struct Serialize<std::pair<unsigned short int, std::string>> {
    boost::property_tree::ptree operator() (std::pair<unsigned short int, std::string> info) {
        boost::property_tree::ptree info_tree;

        unsigned short int code;
        std::string message;

        std::tie(code, message) = info;

        info_tree.put("status", code);
        info_tree.put("message", message);

    }
};

template<> struct Serialize<User> {
    boost::property_tree::ptree operator() (User user) {
        boost::property_tree::ptree user_tree;

        user_tree.put("email", user.get_email());

        return user_tree;
    }
};


template<> struct Serialize<std::vector<Profile>> {
    boost::property_tree::ptree operator() (std::vector<Profile> profiles) {
        boost::property_tree::ptree profiles_tree,
                                    profile_item;

        for(auto & profile : profiles) {
            profile_item.put("username", profile.get_username());
            profiles_tree.add_child("user", profile_item);
        }

        return profiles_tree;
    }
};

template<> struct Serialize<std::tuple<User, Profile>> {
    boost::property_tree::ptree operator() (std::tuple<User, Profile> user) {
        boost::property_tree::ptree tweet_tree,
                child_item,
                child_profile,
                child_user;

        Profile profile;
        User system_user;

        std::tie(system_user, profile) = user;
        child_user.put("email", system_user.get_email());
        child_profile.put("username", profile.get_username());
//        child_profile.put("avatar", profile.get_avatar());
        child_profile.put("birthday", profile.get_birthday());

        child_item.add_child("system_user", child_user);
        child_item.add_child("profile", child_profile);

        tweet_tree.add_child("user", child_item);

        return tweet_tree;
    }
};

template<> struct Serialize<std::tuple<Tweet, Profile>> {
    boost::property_tree::ptree operator() (std::tuple<Tweet, Profile> new_tweet) {
        boost::property_tree::ptree tweet_tree,
                child_item,
                child_tweet,
                child_user;

        Profile profile;
        Tweet tweet;

        std::tie(tweet, profile) = new_tweet;
        child_tweet.put("text", tweet.get_text());
        child_tweet.put("data", tweet.get_date());
        child_user.put("username", profile.get_username());

        child_item.add_child("tweet", child_tweet);
        child_item.add_child("author", child_user);

        tweet_tree.add_child("wall_item", child_item);

        return tweet_tree;
    }
};


template<> struct Serialize<std::vector<std::tuple<Tweet, Profile>>> {
    boost::property_tree::ptree operator() (std::vector<std::tuple<Tweet, Profile>> wall) {
        boost::property_tree::ptree wall_tree,
                                    child_item,
                                    child_tweet,
                                    child_user;

        Profile profile;
        Tweet tweet;

        for(auto & i : wall) {
            std::tie(tweet, profile) = i;
            child_tweet.put("text", tweet.get_text());
            child_tweet.put("data", tweet.get_date());
            child_user.put("username", profile.get_username());

            child_item.add_child("tweet", child_tweet);
            child_item.add_child("author", child_user);

            wall_tree.add_child("wall_item", child_item);
        }

        return wall_tree;
    }
};

#endif //SERIALIZE_HPP