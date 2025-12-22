# EMDAER
SFML 3.0
C++ 17
Wpisać we właściwości projektu:
C/C++ -> Ogólne -> Dodatkowe katalogi plików nagłówkowych -> Ścieżka do SFML-3.0.0\include
Konsolidator -> Ogólne -> Dodatkowe katalogi biblioteki -> Ścieżka do SFML-3.0.0\lib
Konsolidator -> Dane Wejśćiowe -> Dodatkowe zależnośći -> $(CoreLibraryDependencies);%(AdditionalDependencies);sfml-graphics-d.lib;sfml-window-d.lib;sfml-system-d.lib;sfml-audio-d.lib
