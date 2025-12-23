# EMDAER

![SFML](https://img.shields.io/badge/SFML-3.0-green) ![C++](https://img.shields.io/badge/C++-17-blue)

## ⚙️ Konfiguracja Projektu (Visual Studio)

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
