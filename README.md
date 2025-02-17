# Cymbergaj

Cymbergaj to gra komputerowa stworzona w języku C++ z wykorzystaniem biblioteki SFML.


![image](https://github.com/user-attachments/assets/7a302ffe-89f5-4890-a18d-32905db05415)
![image](https://github.com/user-attachments/assets/f190b588-99cf-421a-b3a2-3844f9f242bc)
![image](https://github.com/user-attachments/assets/79c5de55-17ed-40a4-9457-95161dc382be)
![image](https://github.com/user-attachments/assets/1c96d375-7d10-40ec-a3f8-1904b063e717)
![image](https://github.com/user-attachments/assets/ba290b0f-6678-432a-a4b4-07251d0c94b1)



## Opis

Gra ma na celu symulację gry w Air Hokej, w której dwóch graczy porusza się na swojej połowie planszy i próbuje odbijać piłkę tak, aby trafić ją do bramki przeciwnika. 
Gra jest wyposażona w menu główne, opcje, takie jak możliwość zmiany tła i liczby bramek oraz pomoc. 
Gra w Cymbergaja umożliwia dwóm użytkownikom zabawę i rywalizację ze sobą w wielu wydaniach. 
Gra wykorzystuje bibliotekę SFML do obsługi grafiki 2D i interakcji z użytkownikiem.

## Funkcje

- **Tryb dla dwóch graczy**: Możliwość rywalizacji dwóch graczy na jednym komputerze.
- **Prosty interfejs**: Intuicyjne sterowanie i przejrzysty interfejs użytkownika.
- **Dynamiczna rozgrywka**: Szybka i ekscytująca akcja na ekranie.

## Wymagania

- **System operacyjny**: Windows, Linux lub macOS
- **Biblioteka SFML**: Należy zainstalować bibliotekę SFML w wersji kompatybilnej z Twoim systemem operacyjnym.

## Instalacja

1. **Pobierz repozytorium**:

   ```bash
   git clone https://github.com/jrozycki2003/Cymbergaj.git
   ```

2. **Zainstaluj bibliotekę SFML**:

   - **Windows**: Pobierz i zainstaluj SFML ze strony [https://www.sfml-dev.org/download.php](https://www.sfml-dev.org/download.php).
   - **Linux**: Użyj menedżera pakietów, np. `sudo apt-get install libsfml-dev` na systemach opartych na Debianie.
   - **macOS**: Zainstaluj SFML za pomocą Homebrew: `brew install sfml`.

3. **Kompilacja projektu**:

   - Przejdź do katalogu z projektem:

     ```bash
     cd Cymbergaj
     ```

   - Użyj kompilatora C, np. GCC, aby skompilować projekt:

     ```bash
     gcc -o cymbergaj main.c -lsfml-graphics -lsfml-window -lsfml-system
     ```

## Użycie

Po skompilowaniu projektu uruchom grę za pomocą polecenia:

```bash
./cymbergaj
```

Sterowanie odbywa się za pomocą klawiszy strzałek dla gracza 1 oraz klawiszy W, A, S, D dla gracza 2.


## Kontakt

W razie pytań lub sugestii zapraszam do kontaktu.
