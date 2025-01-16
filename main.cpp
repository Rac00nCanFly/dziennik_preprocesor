#include <iostream>
#include <fstream>
#include <string>


// Definicja poziomów logowania przy użyciu enum class
enum class Poziom {
    SEVERE = 1,
    WARNING = 2,
    INFO = 3,
    CONFIG = 4,
    FINE = 5,
    FINER = 6,
    FINEST = 7
};

// Klasa Dziennik do obsługi logowania
class Dziennik {
private:
    Poziom aktualnyPoziom; // Aktualny poziom logowania
    bool doKonsoli; // Czy logować na konsolę
    bool doPliku; // Czy logować do pliku
    std::string plik; // Nazwa pliku logów

    // Metoda pomocnicza do wypisywania komunikatów
    void wypiszKomunikat(Poziom poziom, const std::string &wiadomosc) {
        // Sprawdzenie, czy poziom komunikatu jest wystarczająco wysoki
        if (static_cast<int>(poziom) <= static_cast<int>(aktualnyPoziom)) {
            if (doKonsoli) {
                // Wypisywanie na konsolę
                std::cout << "[" << poziomToString(poziom) << "] " << wiadomosc << std::endl;
            }
            if (doPliku) {
                // Dopisywanie do pliku
                std::ofstream file(plik, std::ios::out);
                if (file.is_open()) {
                    file << "[" << poziomToString(poziom) << "] " << wiadomosc <<"\n"<< __FILE_NAME__<<"\n"<<__TIME__<<"\n"<<__LINE__<<"\n"<<__FUNCTION__<<std::endl;
                    file.close();
                } else {
                    // Komunikat błędu w przypadku problemów z otwarciem pliku
                    std::cerr << "Nie można otworzyć pliku: " << plik << std::endl;
                }
            }
        }
    }

    // Metoda pomocnicza do konwersji poziomu logowania na tekst
    std::string poziomToString(Poziom poziom) const {
        switch (poziom) {
            case Poziom::SEVERE: return "SEVERE";
            case Poziom::WARNING: return "WARNING";
            case Poziom::INFO: return "INFO";
            case Poziom::CONFIG: return "CONFIG";
            case Poziom::FINE: return "FINE";
            case Poziom::FINER: return "FINER";
            case Poziom::FINEST: return "FINEST";
            default: return "UNKNOWN";
        }
    }

public:
    // Konstruktor klasy Dziennik
    Dziennik(Poziom poziom, bool konsola, bool plik, const std::string &nazwaPliku = "")
        : aktualnyPoziom(poziom), doKonsoli(konsola), doPliku(plik), plik(nazwaPliku) {}

    // Metoda do zmiany aktualnego poziomu logowania
    void zmienPoziom(Poziom nowyPoziom) {
        aktualnyPoziom = nowyPoziom;
    }

    // Metody do logowania komunikatów na różnych poziomach
    void severe(const std::string &wiadomosc) {
        wypiszKomunikat(Poziom::SEVERE, wiadomosc);
    }

    void warning(const std::string &wiadomosc) {
        wypiszKomunikat(Poziom::WARNING, wiadomosc);
    }

    void info(const std::string &wiadomosc) {
        wypiszKomunikat(Poziom::INFO, wiadomosc);
    }

    void config(const std::string &wiadomosc) {
        wypiszKomunikat(Poziom::CONFIG, wiadomosc);
    }

    void fine(const std::string &wiadomosc) {
        wypiszKomunikat(Poziom::FINE, wiadomosc);
    }

    void finer(const std::string &wiadomosc) {
        wypiszKomunikat(Poziom::FINER, wiadomosc);
    }

    void finest(const std::string &wiadomosc) {
        wypiszKomunikat(Poziom::FINEST, wiadomosc);
    }
};

// Przykładowe użycie klasy Dziennik
int main() {
    // Tworzenie obiektu Dziennika z poziomem INFO, logowanie na konsolę i do pliku "log.txt"
    Dziennik dziennik(Poziom::INFO, true, true, "log.txt");

    // Logowanie komunikatów na różnych poziomach
    dziennik.severe("To jest komunikat SEVERE.");
    dziennik.warning("To jest komunikat WARNING.");
    dziennik.info("To jest komunikat INFO.");
    dziennik.config("To jest komunikat CONFIG.");
    dziennik.fine("To jest komunikat FINE.");
    dziennik.finer("To jest komunikat FINER.");
    dziennik.finest("To jest komunikat FINEST.");

    // Zmiana poziomu logowania na FINE
    dziennik.zmienPoziom(Poziom::FINE);
    dziennik.info("Teraz poziom został zmieniony na FINE.");
    dziennik.finest("Ten komunikat nie powinien się pojawić.");
}