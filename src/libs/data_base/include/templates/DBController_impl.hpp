#include <stdio.h>
#include "../DBController.hpp"

template <class Connection>
DBController<Connection>::DBController(int connection_count)
{
    create_pool(connection_count);
}

template <class Connection>
DBController<Connection>::~DBController()
{

}

template <class Connection>
void DBController<Connection>::create_pool(int size)
{
    lock_guard<mutex> locker_(mtx);
    // need to read connection params from config
    string host = "localhost", db_name = "twitter";
    string user = "twitter_user", password = "twitter_password";
    int port = 5432;
    for (int i = 0; i < size; ++i )
    {
         connection_pool.emplace(make_shared<Connection>(host, db_name, 
                                                         user, password, 
                                                         port));
    }
}

template <class Connection>
shared_ptr<Connection> DBController<Connection>::get_free_connection(void)
{
    unique_lock<mutex> lock(mtx);
    while (connection_pool.empty())
    {
            cond.wait(lock);
    }

    auto conn = connection_pool.front();
    connection_pool.pop();
    return conn;
}

template <class Connection>
void DBController::reset_connection(shared_ptr<Connection> conn)
{
    unique_lock<mutex> lock(mtx);
    connection_pool.push(conn);
    lock.unlock();
    cond.notify_one();
}

template <class Connection>
bool DBController::run_query(string query, vector<string> &result)
{
    auto conn = get_free_connection();
    PGresult *query_res = PQexec(conn->get_connection().get(), query.c_str());
    if (PQresultStatus(query_res) != PGRES_TUPLES_OK)
    {
        cout << "Error!" << endl;
        return false;
    }

    result.clear();
    int columns = PQnfields(query_res);
    int strings = PQntuples(query_res);
    for (int i = 1; i < PQntuples(query_res); i++)
    {
        for (int j = 0; j < columns; j++)
            result.push_back(PQgetvalue(query_res, i, j));
    }
    reset_connection(conn);
    return true;
}