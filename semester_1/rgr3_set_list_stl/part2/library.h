#include <string>
#include <list>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

class Author {
private:
    std::string name_;
    std::string surname_;
    std::string patronymic_;

public:
    Author() = default;

    Author(const std::string& surname, const std::string& name, const std::string& patronymic = "")
        : surname_(surname), name_(name), patronymic_(patronymic) {
    }

    std::string GetName() const {
        return name_;
    }

    std::string GetSurname() const {
        return surname_;
    }

    std::string GetPatronymic() const {
        return patronymic_;
    }

    bool operator< (const Author& other) const {
        return surname_ < other.surname_;
    }

    bool operator== (const Author& other) const {
        return surname_ == other.surname_ &&
            name_ == other.name_ &&
            patronymic_ == other.patronymic_;
    }
};

class Book {
private:
    int id_;
    std::list<Author> authors_;
    std::string name_;
    int date_;
public:
    Book() : id_(0), date_(0) {}

    Book(const int& id, const std::list<Author>& authors, const std::string& name, const int& date)
        : id_(id), authors_(authors), name_(name), date_(date) {
    }

    int GetId() const {
        return id_;
    }

    std::list<Author>& GetAuthorsRef() {
        return authors_;
    }

    std::list<Author> GetAuthors() const {
        return authors_;
    }

    std::string GetName() const {
        return name_;
    }

    int GetDate() const {
        return date_;
    }

    bool operator< (const Book& other) const {
        return name_ < other.name_;
    }

    bool operator== (const Book& other) const {
        return id_ == other.id_ &&
            name_ == other.name_ &&
            date_ == other.date_;
    }
};

class Library {
private:
    std::list<Book> books_;

    std::list<Author> ParseAuthors(const std::string& line) {
        std::list<Author> authors;
        std::stringstream ss(line);
        std::string token;

        while (std::getline(ss, token, ',')) {
            size_t start = token.find_first_not_of(" \t");
            size_t end = token.find_last_not_of(" \t");

            if (start == std::string::npos) continue;

            token = token.substr(start, end - start + 1);

            std::stringstream token_stream(token);
            std::string surname, name, patronymic;

            token_stream >> surname >> name;
            if (token_stream >> patronymic) {
                authors.push_back(Author(surname, name, patronymic));
            }
            else {
                authors.push_back(Author(surname, name, ""));
            }
        }

        return authors;
    }

public:
    std::list<Book> GetBooks() const {
        return books_;
    }

    bool ReadBooksFromFile(std::ifstream& in) {
        if (!in.is_open()) {
            return false;
        }

        std::string line;
        while (true) {
            if (!std::getline(in, line)) break;
            if (line.empty()) break;

            int id;
            try {
                id = std::stoi(line);
            }
            catch (...) {
                break;
            }

            if (!std::getline(in, line)) break;
            std::list<Author> authors = ParseAuthors(line);

            if (!std::getline(in, line)) break;
            std::string name = line;

            if (!std::getline(in, line)) break;
            int date;
            try {
                date = std::stoi(line);
            }
            catch (...) {
                date = 0;
            }

            books_.push_back(Book(id, authors, name, date));

            std::streampos pos = in.tellg();
            if (!(std::getline(in, line) && line.empty())) {
                in.seekg(pos);
            }
        }

        return true;
    }

    void AddBook(const int& id, const std::list<Author>& authors, const std::string& name, const int& date) {
        books_.push_back(Book(id, authors, name, date));
    }

    std::list<Book>::iterator FindBookByName(const std::string& name) {
        for (auto it = books_.begin(); it != books_.end(); ++it) {
            if (it->GetName() == name) {
                return it;
            }
        }
        return books_.end();
    }

    void DeleteBookByName(const std::string& name) {
        auto it = FindBookByName(name);
        if (it != books_.end()) {
            books_.erase(it);
            std::cout << " нига удалена." << std::endl;
        }
        else {
            std::cout << " нига не найдена." << std::endl;
        }
    }

    std::list<Book*> FindAllBooksByAuthor(const std::string& surname,
        const std::string& name = "",
        const std::string& patronymic = "") {
        std::list<Book*> found;

        for (Book& book : books_) {
            for (const Author& author : book.GetAuthors()) {
                if (author.GetSurname() != surname) continue;
                if (!name.empty() && author.GetName() != name) continue;
                if (!patronymic.empty() && author.GetPatronymic() != patronymic) continue;

                found.push_back(&book);
                break;
            }
        }

        return found;
    }

    bool AddAuthorToBook(const std::string& book_name, const Author& author) {
        auto book_it = FindBookByName(book_name);
        if (book_it == books_.end()) {
            return false;
        }

        std::list<Author>& authors = book_it->GetAuthorsRef();

        for (const Author& existing : authors) {
            if (existing == author) {
                return false;
            }
        }

        authors.push_back(author);
        return true;
    }

    bool RemoveAuthorFromBook(const std::string& book_name, const Author& author) {
        auto book_it = FindBookByName(book_name);
        if (book_it == books_.end()) {
            return false;
        }

        std::list<Author>& authors = book_it->GetAuthorsRef();

        for (auto auth_it = authors.begin(); auth_it != authors.end(); ++auth_it) {
            if (*auth_it == author) {
                authors.erase(auth_it);
                return true;
            }
        }

        return false;
    }
};