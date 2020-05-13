#ifndef DBCONTROLLER_HPP
#define DBCONTROLLER_HPP

#include <iostream>
#include <fstream>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <vector>

#include "DBConnection.hpp"

using namespace std;

template <class Connection>
class DBController
{
public:
    explicit DBController(int connection_count);
    ~DBController();

    shared_ptr<Connection> get_free_connection();
    void reset_connection(shared_ptr<Connection>);

    bool run_query(const string& query, vector<vector<string>> &result);

private:
    queue<shared_ptr<Connection>> connection_pool;
    mutex mtx;
    condition_variable cond;

    void create_pool(int size);
};

#include "templates/DBController_impl.hpp"

#endif