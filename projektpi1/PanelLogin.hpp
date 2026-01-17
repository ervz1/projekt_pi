#include <iostream>
#include <fstream>
#include <string>
#include <termios.h>
#include <unistd.h>
std::string getHiddenInput();
std::string szyfr_cezar(std::string tekst, int przesuniecie);
std::string szyfrowanie_hasla(const std::string& haslo);

const int HASLO_PRZESUNIECIE = 7;

enum class LoginState {
    EnterLogin,
    EnterPassword,
    StworzPaslo,
    PrzejdzDalej
};

class PamiecHasel {
public:
    bool userExists(const std::string& login) {
        std::ifstream file(filename);
        if (!file.is_open())
            return false;

        std::string line;
        while (std::getline(file, line)) {
            auto pos = line.find(':');
            if (pos == std::string::npos)
                continue;

            std::string przechLogin = line.substr(0, pos);
            if (przechLogin == login)
                return true;
        }
        return false;
    }

    bool checkPassword(const std::string& login, const std::string& password) {
        std::ifstream file(filename);
        if (!file.is_open())
            return false;

        std::string line;
        while (std::getline(file, line)) {
            auto pos = line.find(':');
            if (pos == std::string::npos)
                continue;

            std::string przechLogin = line.substr(0, pos);
            std::string przechHaslo = line.substr(pos + 1);

            if (przechLogin == login)
                return przechHaslo == szyfrowanie_hasla(password);   
        }
        return false;
    }

    void stworzUzytkownika(const std::string& login, const std::string& password) {
        std::ofstream file(filename, std::ios::app);
        if (!file.is_open()) {
            std::cout << "Nie mozna otworzyc pliku users.txt\n";
            return;
        }

        file << login << ":" << szyfrowanie_hasla(password) << "\n";
    }

private:
    const std::string filename = "users.txt";
};

class LoginPanelTerminal {
public:
    void run() {
        while (state != LoginState::PrzejdzDalej) {
            if (state == LoginState::EnterLogin)
                handleLogin();
            else
                handlePassword();
        }

        std::cout << "\nZalogowano jako: " << currentUser << "\n";
    }

    const std::string& getUser() const {
        return currentUser;
    }

private:
    LoginState state = LoginState::EnterLogin;
    PamiecHasel storage;

    std::string currentUser;
    std::string input;

    void handleLogin() {
        std::cout << "Login: ";
        std::getline(std::cin, input);

        currentUser = input;

        if (storage.userExists(input)) {
            state = LoginState::EnterPassword;
        } else {
            std::cout << "Nowy uzytkownik. Utworz haslo.\n";
            state = LoginState::StworzPaslo;
        }
    }

    void handlePassword() {
        std::cout << "Haslo: ";
        input = getHiddenInput();

        if (state == LoginState::EnterPassword) {
            if (storage.checkPassword(currentUser, input)) {
                state = LoginState::PrzejdzDalej;
            } else {
                std::cout << "Bledne haslo. Sprobuj ponownie.\n";
            }
        } else {
            storage.stworzUzytkownika(currentUser, input);
            state = LoginState::PrzejdzDalej;
        }
    }
};

std::string szyfrowanie_hasla(const std::string& haslo) {
    return szyfr_cezar(haslo, HASLO_PRZESUNIECIE);
}

char zamien_znak(char znak, int przesuniecie){

    if (znak >= ' ' && znak <= '/')
        return ' ' + (znak - ' ' + przesuniecie + 16) % 16;

    if (znak >= '0' && znak <= '9')
        return '0' + (znak - '0' + przesuniecie + 10) % 10;

    if (znak >= ':' && znak <= '@')
        return ':' + (znak - ':' + przesuniecie + 7) % 7;

    if (znak >= 'A' && znak <= 'Z')
        return 'A' + (znak - 'A' + przesuniecie + 26) % 26;

    if (znak >= '[' && znak <= '`')
        return '[' + (znak - '[' + przesuniecie + 6) % 6;

    if (znak >= 'a' && znak <= 'z')
        return 'a' + (znak - 'a' + przesuniecie + 26) % 26;

    if (znak >= '{' && znak <= '~')
        return '{' + (znak - '{' + przesuniecie + 4) % 4;

    return znak;
}

// Szyfr Cezara:
std::string szyfr_cezar(std::string tekst, int przesuniecie){
    std::string wynik = "";
    for (char c : tekst)
        wynik += zamien_znak(c, przesuniecie);
    return wynik;
}

std::string getHiddenInput() {
    termios oldt, newt;
    std::string input;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    newt.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    std::getline(std::cin, input);

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    std::cout << "\n";
    return input;
}
