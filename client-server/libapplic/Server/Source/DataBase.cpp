//
// Created by xink on 20.04.22.
//

#include "../DataBase.h"
    int DataBase :: GetUsersValue(sql::Statement *stmt) {
        sql::ResultSet *res;
        res = stmt->executeQuery("SELECT id,name,surname,login,password FROM users ORDER BY id ASC");
        int i = 1;
        while (res->next()) {
            i++;
        }
        delete res;
        return i;
    }

    int DataBase :: GetBooksValue(sql::Statement *stmt) {
        sql::ResultSet *res;
        res = stmt->executeQuery("SELECT id,book_name,author_id FROM orders ORDER BY id ASC");
        int i = 1;
        while (res->next()) {
            std :: cout << i << std :: endl;
            i++;
        }
        delete res;
        return i;
    }
    int DataBase::GetOrdersValue(sql::Statement *stmt) {
        sql::ResultSet *res;
        res = stmt->executeQuery("SELECT order_id,book_id,user_id FROM orders ORDER BY order_id ASC");
        int i = 1;
        while (res->next()) {
            std :: cout << i << std :: endl;
            i++;
        }
        delete res;
        return i;
    }
    std :: vector<OrderInfo> DataBase::GetOrders(Client client){
        try {
            mutex.lock();
            std :: vector<OrderInfo> orders;
            std::map<int, BookInfo> books;
            sql::Driver *driver;
            sql::Connection *con;
            sql::Statement *stmt;
            sql::ResultSet *res;
            driver = get_driver_instance();
            con = driver->connect(DATABASE_ADDRESS, USERNAME, PASSWORD);
            con->setSchema("ApplicationDB");
            stmt = con->createStatement();
            res = stmt->executeQuery("SELECT orders.order_id,orders.user_id,orders.book_id,books.book_name,authors.name,authors.surname,authors.language,authors.books_value FROM orders JOIN books on books.id = orders.book_id JOIN authors on authors.id = books.author_id");
                    //"SELECT orders.id,books.id,books.book_name,authors.name,authors.surname,authors.language,authors.books_value FROM books JOIN authors on authors.id = books.author_id");
            while (res->next()) {
                int ID = res->getInt("order_id");
                int user_id = res->getInt("user_id");
                int book_id = res->getInt("book_id");
                std::string book_name = res->getString("book_name");
                std::string author_name = res->getString("name");
                std::string author_surname = res->getString("surname");
                std::string author_language = res->getString("language");
                int books_value = res->getInt("books_value");
                if(client.GetId() == user_id){
                    Order ord(client,Book(book_id,book_name,Author(author_name,author_surname,books_value,author_language)));
                    orders.emplace_back(OrderInfo(ord));
                }
            }
            delete con;
            delete stmt;
            delete res;
            mutex.unlock();
            return orders;
        } catch (sql::SQLException &e) {
            mutex.unlock();
            cout << "# ERR: SQLException in " << __FILE__;
            cout << "(" << __FUNCTION__ << ") on line "
                 << __LINE__ << endl;
            cout << "# ERR: " << e.what();
            cout << " (MySQL error code: " << e.getErrorCode();
            cout << ", SQLState: " << e.getSQLState() << " )" << endl;
        }
    };
    int DataBase :: AddNewOrder(Order &order) {
        try {
            mutex.lock();
            sql::Driver *driver;
            sql::Connection *con;
            sql::Statement *stmt;
            sql::ResultSet *res;
            sql::PreparedStatement *prep_stmt;
            driver = get_driver_instance();
            con = driver->connect(DATABASE_ADDRESS, USERNAME, PASSWORD);
            con->setSchema("ApplicationDB");
            std :: cout << "Connected to the DataBase\n";
            prep_stmt = con->prepareStatement("INSERT INTO orders(order_id,book_id,user_id) VALUES (?,?,?)");
            stmt = con->createStatement();
            std :: cout << "Can't see this" << std :: endl;
            prep_stmt->setInt(1, GetOrdersValue(stmt));
            prep_stmt->setInt(2, order.GetBook()->GetId());
            prep_stmt->setInt(3, order.GetClient()->GetId());
            prep_stmt->execute();
            delete con;
            delete prep_stmt;
            mutex.unlock();
            return SQL_SUCCESSFULLY_ADDED;
        }
        catch (sql::SQLException &e) {
            mutex.unlock();
            cout << "# ERR: SQLException in " << __FILE__;
            cout << "(" << __FUNCTION__ << ") on line "
                 << __LINE__ << endl;
            cout << "# ERR: " << e.what();
            cout << " (MySQL error code: " << e.getErrorCode();
            cout << ", SQLState: " << e.getSQLState() << " )" << endl;
            return SQL_ERROR;
        }
    }

    std::map<int, BookInfo> DataBase :: BooksMap() {
        try {
            mutex.lock();
            std::map<int, BookInfo> books;
            sql::Driver *driver;
            sql::Connection *con;
            sql::Statement *stmt;
            sql::ResultSet *res;
            driver = get_driver_instance();
            con = driver->connect(DATABASE_ADDRESS, USERNAME, PASSWORD);
            con->setSchema("ApplicationDB");
            stmt = con->createStatement();
            res = stmt->executeQuery(
                    "SELECT books.id,books.book_name,authors.name,authors.surname,authors.language,authors.books_value FROM books JOIN authors on authors.id = books.author_id");
            while (res->next()) {
                int ID = res->getInt("id");
                std::string book_name = res->getString("book_name");
                std::string author_name = res->getString("name");
                std::string author_surname = res->getString("surname");
                std::string language = res->getString("language");
                int books_value = res->getInt("books_value");
                BookInfo inf(ID, book_name, author_name, author_surname, books_value, language);
                books.insert(std::pair<int, BookInfo>(inf.ID, inf));
            }
            delete con;
            delete stmt;
            delete res;
            mutex.unlock();
            return books;
        } catch (sql::SQLException &e) {
            mutex.unlock();
            cout << "# ERR: SQLException in " << __FILE__;
            cout << "(" << __FUNCTION__ << ") on line "
                 << __LINE__ << endl;
            cout << "# ERR: " << e.what();
            cout << " (MySQL error code: " << e.getErrorCode();
            cout << ", SQLState: " << e.getSQLState() << " )" << endl;
            std::map<int, BookInfo> m;
            m.insert(std::pair<int, BookInfo>(-5, BookInfo(-5, "err", "err", "err", 5, "err")));
            return m;
        }
    }

    int DataBase :: AddNewBook(std::string name, Author author) {
        try {
            mutex.lock();
            sql::Driver *driver;
            sql::Connection *con;
            sql::Statement *stmt;
            sql::ResultSet *res;
            sql::PreparedStatement *prep_stmt;
            driver = get_driver_instance();
            con = driver->connect(DATABASE_ADDRESS, USERNAME, PASSWORD);
            con->setSchema("ApplicationDB");
            prep_stmt = con->prepareStatement("INSERT INTO books(id,book_name,author) VALUES(?,?,?)");
            delete con;
            delete prep_stmt;
            mutex.unlock();
        }
        catch (sql::SQLException &e) {
            mutex.unlock();
            cout << "# ERR: SQLException in " << __FILE__;
            cout << "(" << __FUNCTION__ << ") on line "
                 << __LINE__ << endl;
            cout << "# ERR: " << e.what();
            cout << " (MySQL error code: " << e.getErrorCode();
            cout << ", SQLState: " << e.getSQLState() << " )" << endl;
            return SQL_ERROR;
        }
    }

    int DataBase :: CheckLogin(std::string input_login) {
        try {
            mutex.lock();
            sql::Driver *driver;
            sql::Connection *con;
            sql::Statement *stmt;
            sql::ResultSet *res;
            driver = get_driver_instance();
            con = driver->connect(DATABASE_ADDRESS, USERNAME, PASSWORD);
            con->setSchema("ApplicationDB");
            stmt = con->createStatement();
            res = stmt->executeQuery("SELECT id,name,surname,login,password FROM users ORDER BY id ASC");
            while (res->next()) {
                std::string name = res->getString("name");
                std::string surname = res->getString("surname");
                std::string login = res->getString("login");
                std::string password = res->getString("password");
                if (input_login == login) {
                    delete con;
                    delete stmt;
                    delete res;
                    mutex.unlock();
                    return SQL_LOGIN_EXISTS;
                }
            }
            delete con;
            delete stmt;
            delete res;
            mutex.unlock();
            return SQL_LOGIN_IS_NOT_EXISTS;
        }
        catch (sql::SQLException &e) {
            mutex.unlock();
            cout << "# ERR: SQLException in " << __FILE__;
            cout << "(" << __FUNCTION__ << ") on line "
                 << __LINE__ << endl;
            cout << "# ERR: " << e.what();
            cout << " (MySQL error code: " << e.getErrorCode();
            cout << ", SQLState: " << e.getSQLState() << " )" << endl;
            return SQL_ERROR;
        }
    }

    int DataBase :: AddNewUser(const std::string &name, const std::string &surname, const std::string &login,
                   const std::string &password) {
        try {
            if (CheckLogin(login) == SQL_LOGIN_EXISTS) {
                return SQL_LOGIN_EXISTS;
            } else {
                mutex.lock();
                sql::Driver *driver;
                sql::Connection *con;
                sql::Statement *stmt;
                sql::ResultSet *res;
                sql::PreparedStatement *prep_stmt;
                driver = get_driver_instance();
                con = driver->connect(DATABASE_ADDRESS, USERNAME, PASSWORD);
                con->setSchema("ApplicationDB");
                prep_stmt = con->prepareStatement(
                        "INSERT INTO users(id,name,surname,login,password) VALUES (?,?,?,?,?)");
                stmt = con->createStatement();
                prep_stmt->setInt(1, GetUsersValue(stmt));
                prep_stmt->setString(2, name);
                prep_stmt->setString(3, surname);
                prep_stmt->setString(4, login);
                std :: cout << hash ::sha256(password) << " " << hash ::sha256(password).length() << std :: endl;
                prep_stmt->setString(5, hash ::sha256(password));
                prep_stmt->execute();
                delete con;
                delete prep_stmt;
                mutex.unlock();
                return SQL_SUCCESSFULLY_ADDED;
            }
        }
        catch (sql::SQLException &e) {
            mutex.unlock();
            cout << "# ERR: SQLException in " << __FILE__;
            cout << "(" << __FUNCTION__ << ") on line "
                 << __LINE__ << endl;
            cout << "# ERR: " << e.what();
            cout << " (MySQL error code: " << e.getErrorCode();
            cout << ", SQLState: " << e.getSQLState() << " )" << endl;
            return SQL_ERROR;
        }
    }


    LogFlagReturning DataBase :: CheckLoginPassword(std::string input_login, std::string input_password) {
        try {
            mutex.lock();
            sql::Driver *driver;
            sql::Connection *con;
            sql::Statement *stmt;
            sql::ResultSet *res;
            driver = get_driver_instance();
            con = driver->connect(DATABASE_ADDRESS, USERNAME, PASSWORD);
            con->setSchema("ApplicationDB");
            stmt = con->createStatement();
            res = stmt->executeQuery("SELECT id,name,surname,login,password FROM users ORDER BY id ASC");
            while (res->next()) {
                int ID = res->getInt(1);
                std::string name = res->getString("name");
                std::string surname = res->getString("surname");
                std::string login = res->getString("login");
                std::string password = res->getString("password");
                if (input_login.compare(login) == 0) {
                    if (hash ::sha256(input_password).compare(password) == 0) {
                        delete con;
                        delete stmt;
                        delete res;
                        mutex.unlock();
                        LogFlagReturning log(SQL_SUCCESSFULLY_LOGGED, ID, name, surname, login, password);
                        return log;
                    }
                }
            }
            delete con;
            delete stmt;
            delete res;
            LogFlagReturning log(SQL_CANT_LOGGED);
            mutex.unlock();
            return log;
        }
        catch (sql::SQLException &e) {
            mutex.unlock();
            cout << "# ERR: SQLException in " << __FILE__;
            cout << "(" << __FUNCTION__ << ") on line "
                 << __LINE__ << endl;
            cout << "# ERR: " << e.what();
            cout << " (MySQL error code: " << e.getErrorCode();
            cout << ", SQLState: " << e.getSQLState() << " )" << endl;
            LogFlagReturning log(SQL_ERROR);
            mutex.unlock();
            return log;
        }
    }