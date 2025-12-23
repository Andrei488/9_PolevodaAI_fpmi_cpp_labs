#include "library.h"
#include <iostream>
#include <fstream>

void printBookInfo(const Book& book) {
    std::cout << "ID: " << book.GetId()
        << ", Название: \"" << book.GetName()
        << "\", Год: " << book.GetDate()
        << ", Авторы: ";

    auto authors = book.GetAuthors();
    bool first = true;
    for (const auto& author : authors) {
        if (!first) std::cout << ", ";
        std::cout << author.GetSurname() << " "
            << author.GetName();
        if (!author.GetPatronymic().empty()) {
            std::cout << " " << author.GetPatronymic();
        }
        first = false;
    }
    std::cout << std::endl;
}

void printBooksList(const std::list<Book>& books) {
    if (books.empty()) {
        std::cout << "Список книг пуст." << std::endl;
        return;
    }

    std::cout << "Книги в библиотеке:" << std::endl;
    for (const auto& book : books) {
        printBookInfo(book);
    }
    std::cout << std::endl;
}

int main() {
    setlocale(LC_ALL, "Russian");

    Library library;

    std::cout << "1. ЧТЕНИЕ КНИГ ИЗ ФАЙЛА:" << std::endl;

    std::ifstream inFile("Books.txt");
    if (!inFile) {
        std::cerr << "Не удалось открыть файл для чтения" << std::endl;
        return 1;
    }

    bool readSuccess = library.ReadBooksFromFile(inFile);
    inFile.close();

    if (readSuccess) {
        std::cout << "Книги успешно загружены из файла." << std::endl;
    }
    else {
        std::cout << "Ошибка при чтении книг из файла." << std::endl;
    }

    std::cout << std::endl;
    printBooksList(library.GetBooks());

    std::cout << "2. ДОБАВЛЕНИЕ НОВОЙ КНИГИ:" << std::endl;

    std::list<Author> newAuthors = {
        Author("Достоевский", "Федор", "Михайлович")
    };
    library.AddBook(4, newAuthors, "Братья Карамазовы", 1880);
    std::cout << "   Добавлена книга \"Братья Карамазовы\"" << std::endl;

    std::cout << std::endl;
    printBooksList(library.GetBooks());

    std::cout << "3. ПОИСК КНИГИ ПО НАЗВАНИЮ:" << std::endl;

    std::cout << "   Поиск книги \"Анна Каренина\":" << std::endl;
    auto bookIt = library.FindBookByName("Анна Каренина");
    if (bookIt != library.GetBooks().end()) {
        std::cout << "   Найдена: ";
        printBookInfo(*bookIt);
    }
    else {
        std::cout << "   Книга не найдена." << std::endl;
    }

    std::cout << std::endl;
    std::cout << "   Поиск несуществующей книги \"Мастер и Маргарита\":" << std::endl;
    bookIt = library.FindBookByName("Мастер и Маргарита");
    if (bookIt == library.GetBooks().end()) {
        std::cout << "   Книга не найдена." << std::endl;
    }

    std::cout << std::endl;

    std::cout << "4. ПОИСК КНИГ ПО АВТОРУ:" << std::endl;

    std::cout << "   Книги Иванова Ивана Ивановича:" << std::endl;
    auto booksByAuthor = library.FindAllBooksByAuthor("Иванов", "Иван", "Иванович");
    if (!booksByAuthor.empty()) {
        for (const auto* book : booksByAuthor) {
            std::cout << "   - ";
            printBookInfo(*book);
        }
    }
    else {
        std::cout << "   Книги не найдены." << std::endl;
    }

    std::cout << std::endl;
    std::cout << "   Книги Толстого (только по фамилии):" << std::endl;
    booksByAuthor = library.FindAllBooksByAuthor("Толстой");
    if (!booksByAuthor.empty()) {
        for (const auto* book : booksByAuthor) {
            std::cout << "   - ";
            printBookInfo(*book);
        }
    }
    else {
        std::cout << "   Книги не найдены." << std::endl;
    }

    std::cout << std::endl;

    std::cout << "5. ДОБАВЛЕНИЕ АВТОРА К КНИГЕ:" << std::endl;

    std::cout << "   Добавляем Гончарова к книге \"Война и мир\":" << std::endl;
    Author newAuthor("Гончаров", "Иван", "Александрович");
    bool added = library.AddAuthorToBook("Война и мир", newAuthor);
    if (added) {
        std::cout << "   Автор успешно добавлен." << std::endl;
        bookIt = library.FindBookByName("Война и мир");
        if (bookIt != library.GetBooks().end()) {
            std::cout << "   Обновленная книга: ";
            printBookInfo(*bookIt);
        }
    }
    else {
        std::cout << "   Не удалось добавить автора." << std::endl;
    }

    std::cout << std::endl;
    std::cout << "   Пытаемся добавить того же автора еще раз:" << std::endl;
    added = library.AddAuthorToBook("Война и мир", newAuthor);
    if (!added) {
        std::cout << "   Автор не добавлен (уже существует)." << std::endl;
    }

    std::cout << std::endl;

    std::cout << "6. УДАЛЕНИЕ АВТОРА ИЗ КНИГИ:" << std::endl;

    std::cout << "   Удаляем Петрова из книги \"Война и мир\":" << std::endl;
    Author toRemove("Петров", "Петр", "Петрович");
    bool removed = library.RemoveAuthorFromBook("Война и мир", toRemove);
    if (removed) {
        std::cout << "   Автор успешно удален." << std::endl;
        bookIt = library.FindBookByName("Война и мир");
        if (bookIt != library.GetBooks().end()) {
            std::cout << "   Обновленная книга: ";
            printBookInfo(*bookIt);
        }
    }
    else {
        std::cout << "   Не удалось удалить автора." << std::endl;
    }

    std::cout << std::endl;
    std::cout << "   Пытаемся удалить несуществующего автора:" << std::endl;
    Author fakeAuthor("Лермонтов", "Михаил", "Юрьевич");
    removed = library.RemoveAuthorFromBook("Война и мир", fakeAuthor);
    if (!removed) {
        std::cout << "   Автор не удален (не найден)." << std::endl;
    }

    std::cout << std::endl;

    std::cout << "7. УДАЛЕНИЕ КНИГИ:" << std::endl;

    std::cout << "   Удаляем книгу \"Преступление и наказание\":" << std::endl;
    library.DeleteBookByName("Преступление и наказание");

    std::cout << std::endl;
    std::cout << "   Пытаемся удалить несуществующую книгу:" << std::endl;
    library.DeleteBookByName("Отцы и дети");

    std::cout << std::endl;

    std::cout << "8. ФИНАЛЬНОЕ СОСТОЯНИЕ БИБЛИОТЕКИ:" << std::endl;
    printBooksList(library.GetBooks());

    return 0;
}