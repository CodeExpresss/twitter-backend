#ifndef VOTE_HPP
#define VOTE_HPP

class Vote {
public:
    Vote(int, int);
    ~Vote();

private:
    int profile_id;
    int tweet_id;
    int kind;

    bool set_like(int, int);
    bool remove_like(int, int);
};

#endif // VOTE_HPP
