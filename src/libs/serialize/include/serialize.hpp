#ifndef SERIALIZE_HPP
#define SERIALIZE_HPP

#include <string>
#include <boost/property_tree/ptree.hpp>
#include "profile.hpp"

template<class Type> struct Serialize;

template<> struct Serialize<Profile> {
    boost::property_tree::ptree operator() (Profile profile) {
        boost::property_tree::ptree profile_tree;

        profile_tree.put("nickname", profile.get_username());
        profile_tree.put("birthday", profile.get_birthday());

        return profile_tree;
    }
};
#endif //SERIALIZE_HPP