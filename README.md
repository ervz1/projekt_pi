# __Konspekt gry__  + readme na samym dole

##
# 1. Ogolne zasady - dla dwóch graczy - przebieg rund:

### Przebieg mojej tury:
| **A) Trafiam** | **B) Nie trafiam** |
| --- | --- |
| 1. Zaczynam pić piwo |
| 2. Kończę pić w momencie, gdy przeciwnik postawi puszkę i wróci do swojej bazy | 2. Koniec mojej tury |
| 3. Koniec mojej tury |
## 
### Przebieg tury przeciwnika:
| **C) Przeciwnik trafia** | **D) Przeciwnik nie trafia** |
| --- | --- |
| 1. Biegnę podnieść puszkę |
| 2. Przeciwnik pije swoje piwo dopóki ja nie podniosę puszki i nie wrócę na miejsce | 2. Koniec tury przeciwnika |
| 3. Koniec tury przeciwnika | 

##
##
# 2. Koncepcje zdarzeń poszczególnych stanów:

### Scanariusz A:
| Zdarzenie | Akcja |
| --- | --- |
| Rzut puszką | Strzałkami ustawiam wektory rzutu |
| Start picia | Klikam w spację |
| Zakończenie tury | Automatyczneie |

##
### Scanariusz B:
| Zdarzenie | Akcja |
| --- | --- |
| Rzut puszką | Strzałkami ustawiam wektory rzutu |
| Nietrafienie puszki | Brak akcji |
| Zakończenie mojej tury | -- |

##
### Scanariusz C:
| Zdarzenie | Akcja |
| --- | --- |
| Rzut puszką przez komputer | Silnik losuje parametry rzutu |
| Trafienie puszki | Biegne klikając w spacje |
| Start picia piwa | Zawartość Piwa komputera spada |
| Dobiegnięcie do puskzi | Klikam B żeby podnieść puszkę |
| Bieg  gracza | Klikam spacje by biec |
| Stop picia piwa | Timer picia się zatrzymuje gdy wróce |
| Zakończenie tury przeciwnika | Przejście do tury gracza; ilosc wypitego piwa co runde sie sumuje |

##
### Scanariusz D:

| Zdarzenie | Akcja |
| --- | --- |
| Rzut puszką przez komputer | Silnik losuje parametry rzutu |
| Nietrafienie puszki | Brak akcji |
| Zakończenie tury przeciwnika | -- |

##
##

### 1. Trudność zwiększa się wraz z rundą do pewnego momentu - bot:  
* czesciej trafia
* szybciej biec po ustawienie swojej puszki

### 2. Menu Logowania:
* Przed rozpoczęciem rozgrywki gracz się loguje lub tworzy "konto"

### 3. Menu customizacji:
* Gracz może wybrać wygląd swojego awatara
  
###
###
##



# 4. README FLANKI PROJECT ©

![SFML](https://img.shields.io/badge/SFML-3.0-green) ![C++](https://img.shields.io/badge/C++-17-blue)

## 🥸 Konfiguracja Projektu (Visual Studio)

Wymagane: SFML 3.0, C++ 14,17, lub 20

Aby poprawnie skonfigurować projekt, otwórz **Właściwości Projektu** (*Project Properties*) i wprowadź poniższe ustawienia.

### 1. Pliki Nagłówkowe (Include)
Nawiguj do:
`C/C++` -> `Ogólne` -> `Dodatkowe katalogi plików nagłówkowych`

> **Wartość:**
> ```text
> Ścieżka do SFML-3.0.0\include
> ```

### 2. Biblioteki (Linker)
Nawiguj do:
`Konsolidator` -> `Ogólne` -> `Dodatkowe katalogi biblioteki`

> **Wartość:**
> ```text
> Ścieżka do SFML-3.0.0\lib
> ```

### 3. Zależności (Dependencies)
Nawiguj do:
`Konsolidator` -> `Dane Wejściowe` -> `Dodatkowe zależności`

Skopiuj i wklej poniższy ciąg:
```text
$(CoreLibraryDependencies);%(AdditionalDependencies);sfml-graphics-d.lib;sfml-window-d.lib;sfml-system-d.lib;sfml-audio-d.lib
```

### Zaleśnośći w release
```text
$(CoreLibraryDependencies);%(AdditionalDependencies);sfml-graphics.lib;sfml-window.lib;sfml-system.lib;sfml-audio.lib
```
