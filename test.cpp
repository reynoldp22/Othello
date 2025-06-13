/**
 * Praktikum Informatik 1 MMXXV
 *
 * @file test.cpp
 *
 * Stellt Funktionen zum Testen der Spielfunktionen zur Verfuegung
 */


#include <iostream>
#include "config.h"
#include "test.h"


/*
 * Deklaration der in den Tests verwendeten Funktionen.
 * Dadurch weiss der Compiler, das es sich bei den Namen
 * um Funktionsaufrufe handelt, die in einer anderen Datei
 * definiert sind (extern).
 */
extern void zeigeSpielfeld(const int spielfeld[GROESSE_Y][GROESSE_X]);
extern int gewinner(const int spielfeld[GROESSE_Y][GROESSE_X]);
extern bool aufSpielfeld(const int posX, const int posY);
extern bool zugGueltig(const int spielfeld[GROESSE_Y][GROESSE_X],  const int player, const int posX, const int posY);
extern void zugAusfuehren(int spielfeld[GROESSE_Y][GROESSE_X], const int player, const int posX, const int posY);
extern int moeglicheZuege(const int spielfeld[GROESSE_Y][GROESSE_X], const int player);


/**
 * @brief Funktion zum Testen der gewinner() Funktion.
 *
 * @param eingabefeld Das zu testende Spielfeld.
 * @param richtig Der erwartete Gewinner.
 * @param testNummer Nummer des laufenden Tests
 * @return True wenn der berechnete Gewinner und der erwartete Gewinner uebereinstimmen. False ansonsten.
 */
bool gewinnerTest(const int eingabefeld[GROESSE_Y][GROESSE_X], const int richtig, const int testNummer)
{
    std::cout << "Fuehre Test " << testNummer + 1 << " fuer 'gewinner()' aus ..." << std::endl;
    std::cout << "----------------------------------" << std::endl << std::endl;
    int ergebnis = gewinner(eingabefeld);
    if (ergebnis == richtig)
    {
        std::cout << "Test " << testNummer + 1 << " bestanden!" << std::endl << std::endl;
        return true;
    }
    else
    {
        std::cout << "Test " << testNummer + 1 << " fehlgeschlagen" << std::endl << std::endl;
        if (AUSFUEHRLICH == 1)
        {
            zeigeSpielfeld(eingabefeld);
            std::cout << std::endl << "Berechnetes Ergebnis: " << ergebnis << std::endl << "Richtiges Ergebnis: " << richtig
                      << std::endl << std::endl;
        }
        return false;
    }
}


/**
 * @brief Funktion zum Testen der aufSpielfeld() Funktion
 *
 * @param posX Index Spalte
 * @param posY Index Zeile
 * @param richtig Das erwartete Ergebnis
 * @param testNummer Nummer des laufenden Tests
 * @return True wenn Test bestanden, ansonsten false
 */
bool aufSpielfeldTest(const int posX, const int posY, const bool richtig, const int testNummer)
{
    // ueberprueft, ob eine gegebene Position auf dem Spielfeld ist
    //
    // Hier erfolgt jetzt Ihre Implementierung ...
	    bool ergebnis = aufSpielfeld(posX, posY); // calling function that we want to test.

	    if (ergebnis == richtig)
	    {
	        std::cout << "Test " << testNummer << " erfolgreich." << std::endl;
	        return true;
	    }
	    else
	    {
	        std::cout << "Test " << testNummer << " fehlgeschlagen: "
	                  << "aufSpielfeld(" << posX << ", " << posY << ") -> " << ergebnis
	                  << ", erwartet: " << richtig << std::endl;
	        return false;
	    }
    return 0;
}


bool zugGueltigTest(const int eingabeFeld[GROESSE_Y][GROESSE_X], const int spieler, const int posX,
                     const int posY, const bool richtig, const int testNummer)
{
    // ueberprueft, ob der Zug fuer eine gegebene Position gueltig ist
    // wenn AUSFUEHRLICH gleich 1 wird zusaetzlich das Spielfeld und die ungueltige Position ausgegeben
    //
    // Hier erfolgt jetzt Ihre Implementierung ...
		bool ergebnis = zugGueltig(eingabeFeld, spieler, posX, posY);

		if (ergebnis == richtig){
			std::cout << "Test " << testNummer + 1 << " bestanden!" << std::endl << std::endl;
			return true;
		}
		else
		{
			std::cout << "Test " << testNummer + 1 << " fehlgeschlagen" << std::endl << std::endl;
			return false;
		}

    return 0;
}


bool zugAusfuehrenTest(int eingabeFeld[GROESSE_Y][GROESSE_X], const int ergebnisFeld[GROESSE_Y][GROESSE_X],
                       const int spieler, const int posX, const int posY, const int testNummer)
{
    // ueberprueft, ob fuer ein gegebenes Spielfeld der Zug fuer einen gegebenen Spieler korrekt ausgefuehrt wird
    // wenn AUSFUEHRLICH gleich 1 werden zusaetzlich beide Spielfelder ausgegeben   
    //
    // Hier erfolgt jetzt Ihre Implementierung ...

	int feld[GROESSE_Y][GROESSE_X]; //mengkopi eingabeFeld ke Feld untuk testing
	    for (int y = 0; y < GROESSE_Y; y++) { //supaya feld asli tidak rusak
	        for (int x = 0; x < GROESSE_X; x++) {
	            feld[y][x] = eingabeFeld[y][x];
	        }
	    }

	    zugAusfuehren(feld, spieler, posX, posY); //menjalankan zugAusfuehren

	    //Membandingkan dengan hasil yang diinginkan. kalau feld dan ergebnisfeld
	    //tidak sama, maka break.
	    bool korrekt = true;
	    for (int y = 0; y < GROESSE_Y && korrekt; y++) {
	        for (int x = 0; x < GROESSE_X; x++) {
	            if (feld[y][x] != ergebnisFeld[y][x]) {
	                korrekt = false;
	                break;
	            }
	        }
	    }

	    // Ausgabe bei Fehler oder wenn AUSFUEHRLICH aktiv
	    if (!korrekt || AUSFUEHRLICH == 1) {
	        std::cout << "Test " << testNummer << (korrekt ? " OK" : " FEHLER") << std::endl;
	        std::cout << "Eingabe:" << std::endl;
	        zeigeSpielfeld(eingabeFeld);
	        std::cout << "Erwartet:" << std::endl;
	        zeigeSpielfeld(ergebnisFeld);
	        std::cout << "Ergebnis nach zugAusfuehren:" << std::endl;
	        zeigeSpielfeld(feld);
	        std::cout << std::endl;
	    }

	    return korrekt;

}

bool moeglicheZuegeTest(const int eingabeFeld[GROESSE_Y][GROESSE_X], const int spieler,
                         const int richtig, const int testNummer)
{
    // ueberprueft, ob alle moeglichen Zuege fuer einen Spieler gefunden werden
    // wenn AUSFUEHRLICH gleich 1 wird zusaetzlich das Spielfeld, der berechnete falsche und der richtige Wert ausgegeben
    //
    // Hier erfolgt jetzt Ihre Implementierung ...
    int ergebnis = moeglicheZuege(eingabeFeld, spieler);
    bool korrekt = (ergebnis == richtig);

    if (!korrekt || AUSFUEHRLICH == 1) {
        std::cout << "Test " << testNummer << (korrekt ? " OK" : " FEHLER") << std::endl;
        zeigeSpielfeld(eingabeFeld);
        std::cout << "Spieler: " << spieler << std::endl;
        std::cout << "Erwartet: " << richtig << ", Gefunden: " << ergebnis << std::endl;
    }

    return korrekt;
}

/**
 * @brief Funktion, die alle Tests ausfuehrt
 *
 * @return True, wenn alle Tests bestanden wurden, ansonsten false
 */
bool ganzenTestAusfuehren()
{
    bool gesamtErgebnis = true;

    // ---------- TESTE GEWINNER ---------- //
    {
        int eingabeFeld[3][8][8] = {
            {{1, 2, 1, 2, 1, 2, 1, 2},
             {1, 2, 1, 2, 1, 2, 1, 2},
             {1, 2, 1, 2, 1, 2, 1, 2},
             {1, 2, 1, 2, 1, 2, 1, 2},
             {1, 2, 1, 2, 1, 2, 1, 2},
             {1, 2, 1, 2, 1, 2, 1, 2},
             {1, 2, 1, 2, 1, 2, 1, 2},
             {1, 2, 1, 2, 1, 2, 1, 2}},

            {{1, 1, 2, 1, 1, 2, 1, 1},
             {2, 1, 1, 2, 1, 1, 2, 1},
             {1, 2, 1, 1, 2, 1, 1, 2},
             {1, 1, 2, 1, 1, 2, 1, 1},
             {2, 1, 1, 2, 1, 1, 2, 1},
             {1, 2, 1, 1, 2, 1, 1, 2},
             {1, 1, 2, 1, 1, 2, 1, 1},
             {2, 1, 1, 2, 1, 1, 2, 1}},

            {{1, 2, 2, 1, 2, 2, 1, 2},
             {2, 1, 2, 2, 1, 2, 2, 1},
             {2, 2, 1, 2, 2, 1, 2, 2},
             {1, 2, 2, 1, 2, 2, 1, 2},
             {2, 1, 2, 2, 1, 2, 2, 1},
             {2, 2, 1, 2, 2, 1, 2, 2},
             {1, 2, 2, 1, 2, 2, 1, 2},
             {2, 1, 2, 2, 1, 2, 2, 1}}
        };

        int korrektesErgebnis[3] = {0, 1, 2};

        for (int i = 0; i < 3; i++)
        {
            bool tmp_ergebnis = gewinnerTest(eingabeFeld[i], korrektesErgebnis[i], i);
            if (gesamtErgebnis && !tmp_ergebnis)
            {
                gesamtErgebnis = false;
            }
        }
        std::cout << "Ende des Tests fuer 'gewinner()'" << std::endl << std::endl;
    }

    // ---------- TESTE POSITION IM FELD---------- //
    {
        int position[6][2] = {{2, 3}, {0, 8}, {-1, 7}, {2, -1}, {8, 5}, {-1,8}};
        bool korrektesErgebnis[6] = {true, false, false, false, false, false};

        for (int i = 0; i < 6; i++)
        {
            bool tmp_ergebnis = aufSpielfeldTest(position[i][0], position[i][1], korrektesErgebnis[i], i);
            if (gesamtErgebnis && !tmp_ergebnis)
            {
                gesamtErgebnis = false;
            }
        }
        std::cout << "Ende des Tests fuer Positionen" << std::endl << std::endl;
    }
    
    // ---------- TESTE ZUG GUELTIG ---------- //
    {
        int eingabeFeld[7][8][8] = {
            {{1, 0, 2, 0, 0, 1, 1, 1},
             {0, 0, 2, 0, 0, 0, 0, 1},
             {0, 0, 0, 0, 0, 1, 2, 2},
             {2, 2, 0, 2, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 2, 2, 0},
             {0, 0, 0, 2, 1, 1, 0, 2},
             {1, 0, 0, 1, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 1, 0, 1}},

            {{1, 0, 2, 0, 0, 1, 1, 1},
             {0, 0, 2, 0, 0, 1, 0, 0},
             {0, 0, 2, 0, 0, 2, 1, 1},
             {0, 0, 0, 2, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 2, 2, 0},
             {0, 0, 0, 2, 1, 1, 0, 2},
             {1, 0, 0, 1, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 1, 0, 1}},

            {{0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 1, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 2, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0}},

            {{0, 1, 0, 0, 2, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 1, 0},
             {2, 0, 1, 2, 0, 2, 0, 0},
             {0, 2, 0, 2, 2, 2, 2, 2},
             {0, 0, 0, 0, 0, 0, 0, 1},
             {1, 0, 0, 0, 0, 2, 2, 2},
             {0, 2, 0, 0, 0, 0, 0, 0},
             {0, 1, 0, 1, 1, 1, 0, 0}},

            {{2, 1, 0, 0, 2, 1, 1, 1},
             {0, 2, 0, 0, 0, 0, 0, 0},
             {1, 0, 0, 2, 0, 0, 0, 1},
             {0, 1, 1, 1, 0, 1, 0, 0},
             {1, 0, 0, 1, 1, 0, 0, 2},
             {0, 0, 0, 0, 0, 0, 0, 1},
             {1, 1, 0, 0, 0, 0, 2, 0},
             {1, 1, 2, 0, 0, 2, 2, 1}},

            {{0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 1, 0, 0, 0, 0},
             {0, 0, 0, 0, 1, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0}},

            {{1, 2, 2, 2, 2, 2, 2, 2},
             {1, 2, 1, 1, 2, 2, 2, 2},
             {1, 1, 1, 2, 2, 2, 2, 2},
             {1, 1, 1, 2, 2, 2, 2, 2},
             {1, 1, 1, 1, 2, 2, 2, 2},
             {1, 1, 1, 0, 2, 2, 2, 2},
             {1, 0, 0, 0, 2, 0, 0, 2},
             {0, 0, 0, 0, 0, 0, 0, 0}}
        };

        int spieler[7] = {1, 2, 2, 1, 2, 1, 1};
        int position[7][2] = {{2, 3}, {0, 3}, {4, 3}, {3, 4}, {3, 5}, {3, 4}, {5, 7}};
        bool korrektesErgebnis[7] = {false, false, false, true, true, false, false};

        for (int i = 0; i < 7; i++)
        {
            bool tmp_ergebnis = zugGueltigTest(eingabeFeld[i], spieler[i], position[i][0], position[i][1], korrektesErgebnis[i], i);
            if (gesamtErgebnis && !tmp_ergebnis)
            {
                gesamtErgebnis = false;
            }
        }
        std::cout << "Ende des Tests fuer 'zugGueltig()'" << std::endl << std::endl;
    }

    // ---------- TESTE ZUG AUSFUEHREN ---------- //
    {
        int eingabeFeld[10][8][8] = {
            {{0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 1, 2, 2},
             {2, 2, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0}},

            {{0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 2, 1, 1},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0}},

            {{0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 1, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 2, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0}},

            {{0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 1, 0},
             {0, 0, 0, 2, 0, 2, 0, 0},
             {0, 0, 0, 2, 2, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0}},

            {{0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 2, 0, 0, 0, 0},
             {0, 0, 0, 1, 0, 1, 0, 0},
             {0, 0, 0, 1, 1, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0}},

            {{0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 1, 0, 0, 0, 0},
             {0, 0, 0, 0, 1, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0}},

            {{0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 1, 0, 0, 1, 0},
             {0, 0, 0, 2, 0, 2, 0, 0},
             {0, 0, 0, 2, 2, 0, 0, 0},
             {0, 1, 2, 0, 2, 2, 1, 0},
             {0, 0, 0, 2, 2, 0, 0, 0},
             {0, 0, 0, 1, 0, 1, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0}},

            {{0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 2, 0, 0},
             {0, 0, 0, 0, 1, 0, 0, 0},
             {0, 0, 0, 1, 0, 0, 0, 0},
             {0, 0, 0, 1, 1, 1, 1, 0},
             {0, 0, 1, 0, 0, 0, 0, 0},
             {0, 0, 2, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0}},

            {{0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 1, 0, 0, 0, 0, 0, 0},
             {0, 1, 0, 0, 0, 0, 2, 1},
             {1, 0, 1, 1, 2, 0, 0, 0},
             {0, 0, 1, 0, 0, 0, 0, 0},
             {0, 0, 0, 1, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0}},

            {{0, 0, 0, 0, 0, 1, 0, 1},
             {0, 0, 0, 0, 0, 2, 2, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 2, 2, 0, 0},
             {0, 0, 0, 1, 0, 1, 0, 0},
             {0, 0, 2, 0, 0, 2, 0, 0},
             {0, 1, 0, 0, 0, 1, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0}}
        };

        int ergebnisFeld[10][8][8] = {
            {{0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 1, 2, 2},
             {2, 2, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0}},

            {{0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 2, 1, 1},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0}},

            {{0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 1, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 2, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0}},

            {{0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 1, 0},
             {0, 0, 0, 2, 0, 1, 0, 0},
             {0, 0, 0, 2, 1, 0, 0, 0},
             {0, 0, 0, 1, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0}},

            {{0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 2, 0, 0, 0, 0},
             {0, 0, 0, 2, 0, 1, 0, 0},
             {0, 0, 0, 2, 1, 0, 0, 0},
             {0, 0, 0, 2, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0}},

            {{0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 1, 0, 0, 0, 0},
             {0, 0, 0, 0, 1, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0}},

            {{0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 1, 0, 0, 1, 0},
             {0, 0, 0, 1, 0, 1, 0, 0},
             {0, 0, 0, 1, 1, 0, 0, 0},
             {0, 1, 1, 1, 1, 1, 1, 0},
             {0, 0, 0, 1, 1, 0, 0, 0},
             {0, 0, 0, 1, 0, 1, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0}},

            {{0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 2, 0, 0},
             {0, 0, 0, 0, 2, 0, 0, 0},
             {0, 0, 0, 2, 0, 0, 0, 0},
             {0, 0, 2, 1, 1, 1, 1, 0},
             {0, 0, 2, 0, 0, 0, 0, 0},
             {0, 0, 2, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0}},

            {{0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 1, 0, 0, 0, 0, 0, 0},
             {0, 1, 0, 0, 0, 0, 2, 1},
             {1, 2, 2, 2, 2, 0, 0, 0},
             {0, 0, 1, 0, 0, 0, 0, 0},
             {0, 0, 0, 1, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0}},

            {{0, 0, 0, 0, 0, 1, 0, 1},
             {0, 0, 0, 0, 0, 1, 1, 0},
             {0, 0, 0, 0, 0, 1, 0, 0},
             {0, 0, 0, 0, 1, 1, 0, 0},
             {0, 0, 0, 1, 0, 1, 0, 0},
             {0, 0, 2, 0, 0, 2, 0, 0},
             {0, 1, 0, 0, 0, 1, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0}}
        };

        int spieler[10] = {0, 0, 0, 1, 2, 0, 1, 2, 2, 1};
        int position[10][2] = {{0,0}, {0,0}, {0,0}, {3,4}, {3,5}, {0,0}, {3,4}, {2,4}, {1,4}, {5,2}};

        for (int i = 0; i < 10; i++)
        {
            bool tmp_ergebnis = zugAusfuehrenTest(eingabeFeld[i], ergebnisFeld[i], spieler[i], position[i][0], position[i][1], i);
            if (gesamtErgebnis && !tmp_ergebnis)
            {
                gesamtErgebnis = false;
            }
        }
        std::cout << "Ende des Tests fuer 'zugAusfuehren()'" << std::endl << std::endl;
    }

    // ---------- TESTE MOEGLICHE ZUEGE ---------- //
    {
        int eingabeFeld[2][8][8] = {
            {{0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 1, 2, 0, 0, 0},
             {0, 0, 0, 2, 1, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0}},

            {{0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 2, 1, 0, 0, 0},
             {0, 0, 0, 2, 1, 1, 0, 0},
             {0, 0, 0, 2, 1, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0}}
        };

        int spieler[2] = {1, 1};
        int korrektesErgebnis[2] = {4, 5};

        for (int i = 0; i < 2; i++)
        {
            bool tmp_ergebnis = moeglicheZuegeTest(eingabeFeld[i], spieler[i], korrektesErgebnis[i], i);
            if (gesamtErgebnis && !tmp_ergebnis)
            {
                gesamtErgebnis = false;
            }
        }
        std::cout << "Ende des Tests fuer 'moeglicheZuege()'" << std::endl << std::endl;
    }

    std::cout << "Gesamtergebnis aller Tests: " << (gesamtErgebnis ? "ALLE TESTS BESTANDEN" : "FEHLER IN TESTS") << std::endl;
    return gesamtErgebnis;
}
