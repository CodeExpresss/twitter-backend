#include "unit_of_work_header.hpp"
#include "unit_of_work.hpp"
#include "repositories_header.hpp"

std::pair<int, std::string> UnitOfWork::login(User user) {
    err_code rc;
    User _user = user_repository->get_by_email(user.get_email(), rc);
    if(rc == OK) {
        if( user.get_password() == _user.get_password()) {
            return create_session(_user.get_user_id());
        }
    }
}

std::pair<unsigned short, std::string> UnitOfWork::logout(std::string& session) {
    delete_session(session);
    return std::make_pair(200, "ok");
}


std::pair<unsigned short int, std::string> UnitOfWork::sing_up(User user, Profile profile) {
    err_code rc;
    bool status = user_repository->check_user_email(user, rc);
    if (rc == NOT_EXIST) {
        user_repository->create(user, rc);
        if (rc != OK) {
            return std::pair<unsigned short, std::string>(404, "err");
        }
    }
    else if (rc == DELETED) {
        user_repository->erase(user.get_user_id(), rc);
        if (rc != OK) {
            return std::pair<unsigned short, std::string>(404, "err");
        }
    }
    else if (rc == OK && status == true) {
        return std::pair<unsigned short, std::string>(404, "USER ALREADY_EXIST");
    }
    else {
        return std::pair<unsigned short, std::string>(404, "DB err");
    }

    profile.set_user_id(user_repository->check_last_id(rc));
    //profile_repositrory->check_profile_username(profile, rc);
    profile_repositrory->create(profile, rc);
    if (rc != OK) {
        return std::pair<unsigned short, std::string>(404, "err");
    }

    news_feed_repository->create(profile, rc);
    if (rc != OK) {
        return std::pair<unsigned short, std::string>(404, "err");
    }

    return std::pair<unsigned short, std::string>(200, "Ok");
}

std::vector<Profile> UnitOfWork::get_subscriptions(int profile_id, err_code& rc) {
    std::vector<int> profiles_id = subscription_repository->get_by_invitee_id(profile_id, rc);
    std::vector<Profile> profiles;

    for (auto i: profiles_id) {
        profiles.push_back(profile_repositrory->get_by_id(i, rc));
    }

    return profiles;
}

std::pair<unsigned short int, std::string> UnitOfWork::create_tweet(Tweet tweet) {
    err_code rc;

    std::vector<Tag> tags = tweet.get_tags();
    tweet_repository->create(tweet, rc);
    if (rc != OK) {
        return std::pair<unsigned short, std::string>(404, "err");
    }

//    for (auto tag: tags) {
//        tag_repository->create(tag, rc);
//        if (rc != OK) {
//            return std::pair<unsigned short, std::string>(404, "err");
//        }
//    }

    std::pair<Tweet, Profile> updates;
    updates.first = tweet;
    updates.second = profile_repositrory->get_by_id(tweet.get_profile_id(), rc);

    auto update_newsfeed = [&](){
        auto subs = subscription_repository->get_by_inviter_id(tweet.get_profile_id(), rc);
        for (int i : subs) {
            news_feed_repository->update(updates, i, rc);
        }
    };

    std::async(update_newsfeed);

    return std::pair<unsigned short, std::string>(200, "Ok");
}

std::pair<unsigned short int, std::string> UnitOfWork::following(Subscription subscription) {
    err_code rc;

    bool status = subscription_repository->check_subscription(subscription, rc);
    if (rc == NOT_EXIST) {
        subscription.set_is_active(true);
        subscription_repository->create(subscription, rc);
        if (rc != OK) {
            return std::pair<unsigned short, std::string>(404, "err");
        }

        std::vector<Tweet> tweets;
        tweets = tweet_repository->get_by_profile_id(subscription.get_inviter_id(), rc);
        if (rc != OK) {
            return std::pair<unsigned short, std::string>(404, "err");
        }

        if (rc != OK) {
            return std::pair<unsigned short, std::string>(404, "err");
        }

        auto invitee = subscription.get_invitee_id();
        if (rc != OK) {
            return std::pair<unsigned short, std::string>(404, "err");
        }

        std::pair<Tweet, Profile> updates;
        updates.second = profile_repositrory->get_by_id(subscription.get_inviter_id(), rc);
        for (auto tweet: tweets) {
            updates.first = tweet;
            news_feed_repository->update(updates, invitee, rc);
            if (rc != OK) {
                return std::pair<unsigned short, std::string>(404, "err");
            }
        }
    }
    else if (rc == OK || rc == DELETED) {
        subscription.set_is_active(!status);
        subscription_repository->update(subscription, rc);
        if (rc != OK) {
            return std::pair<unsigned short, std::string>(404, "err");
        }
    }
    else {
        return std::pair<unsigned short, std::string>(404, "err");
    }

    return std::pair<unsigned short, std::string>(200, "Ok");
}


std::vector<std::pair<Tweet, Profile>> UnitOfWork::get_index_tweet(int profile_id) {
    err_code rc;
    std::vector<std::pair<Tweet, Profile>> contents = news_feed_repository->get_by_id(profile_id, rc);

    return contents;
}

std::pair<int, std::string> UnitOfWork::create_session(int user_id) {
    err_code rc;
    std::string session_id = session_repository->create(user_id, rc);

    return std::pair<int, std::string>(user_id, session_id);
}

int UnitOfWork::get_user_id_session(std::string &session_id) {
    err_code rc;
    int user_id = session_repository->get_profile_id(session_id, rc);

    return user_id;
}

void UnitOfWork::delete_session(std::string &session_id) {
    err_code rc;
    session_repository->erase(session_id, rc);
}

bool UnitOfWork::check_session(std::string &session_id) {
    err_code rc;
    return session_repository->check_session(session_id, rc);
}

/*Profile UnitOfWork::get_profile(int profile_id) {*/
    //Profile _profile;
    //return _profile;
/*}*/

std::vector<std::pair<Tweet, Profile>> UnitOfWork::find_by_tag(const std::string& tag, err_code& rc)
{
    Tag searching_tag = tag_repository->get_by_title(tag, rc);
    std::vector<int> tweets_id = tag_repository->get_by_id(searching_tag.get_tag_id(), rc);
    std::vector<std::pair<Tweet, Profile>> contents = {};
    std::pair<Tweet, Profile> pair;
    for (auto i: tweets_id) {
        Tweet tweet = tweet_repository->get_by_id(i, rc);
        Profile profile = profile_repositrory->get_by_id(tweet.get_profile_id(), rc);
        pair.first = tweet;
        pair.second = profile;
        contents.push_back(pair);
    }
    return contents;
}