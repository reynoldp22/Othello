/**
 * Praktikum Informatik 1 
 * 
 *
 * @file main.cpp
 *
 * Die Funktionen fuer das Spiel Othello
 */

/**
* @mainpage Othello
*
* Dokumentation des Spiels Othello im Rahmen des Praktikums Informatik 1.
*
*/

#include <iostream>
#include <string>
#include "config.h"
#include "test.h"
#include "othelloKI.h"

#define MENSCH 1
#define COMPUTER 2


/**
 * @brief Funktion zur ersten Initialisierung eines neuen Spielfelds
 *
 * Diese Funktion fuellt ein existierendes Spielfeld mit Nullen und erzeugt die Startaufstellung.
 *
 * @param spielfeld Spielfeld, das initialisiert wird
 */
void initialisiereSpielfeld(int spielfeld[GROESSE_Y][GROESSE_X])
{
    for (int j = 0; j < GROESSE_Y; j++)
        {
            for(int i = 0; i < GROESSE_X; i++)
            {
                spielfeld[j][i] = 0;
            }
        }
        spielfeld[GROESSE_Y / 2 - 1][GROESSE_X / 2 - 1] = 1;
        spielfeld[GROESSE_Y / 2][GROESSE_X / 2 - 1] = 2;
        spielfeld[GROESSE_Y / 2 - 1][GROESSE_X / 2] = 2;
        spielfeld[GROESSE_Y / 2][GROESSE_X / 2] = 1;
}



/**
* @brief Ausgabe des Spielfelds auf der Konsole
*
* Ausgabe des aktuellen Spielfelds, 0 bedeutet leeres Feld, 1 ist Spieler 1 und 2 ist Spieler2
* Kreuze symbolisieren Spieler 1, waehrend Kreise Spieler 2 symbolisieren
*
*  @param spielfeld  Spielfeld, das ausgeben wird
*/
void zeigeSpielfeld(const int spielfeld[GROESSE_Y][GROESSE_X])
{
    std::cout << "   | ";

    //Start bei ASCII 65 = A
    for (int i = 65; i < 65 + GROESSE_X; ++i)
        std::cout << ((char) i) << " | " ;

    std::cout << std::endl;

    for (int j = 0; j < GROESSE_Y; ++j)
    {
        for(int i = 0; i < GROESSE_X; ++i)
        {
            std::cout << "---+";
        }
        std::cout << "---+" << std::endl;

        std::cout << " " << j + 1 << " |";
        for (int i = 0; i < GROESSE_X; ++i)
        {
            switch (spielfeld[j][i])
            {
                case 0:
                    std::cout << "   " ;
                    break;
                case 1:
                    std::cout << " X ";
                    break;
                case 2:
                    std::cout << " O ";
                    break;
                default:
                    std::cout << "Unzulaessige Daten im Spielfeld!" << std::endl;
                    std::cout << "Abbruch .... " << std::endl;
                    exit(0);
                    break;
            }
            std::cout << "|";
        };  //for i
        std::cout <<  std::endl;
    }  //for j
}

/**
 * @brief Prueft, wer Gewinner ist
 *
 * Zaehlt alle Steine auf dem Feld
 *
 * @param spielfeld Aktuelles Spielfeld, fuer das der Gewinner ermittelt wird
 * @return winner
 */
int gewinner(const int spielfeld[GROESSE_Y][GROESSE_X])
{
    int zaehlerSpieler1 = 0;
    int zaehlerSpieler2 = 0;

    for (int j = 0; j < GROESSE_Y; ++j)
    {
        for (int i = 0; i < GROESSE_X; ++i)
        {
            if (spielfeld[j][i] == 1)
            {
                ++zaehlerSpieler1;
            }
            if (spielfeld[j][i] == 2)
            {
                ++zaehlerSpieler2;
            }

        }
    }

    if (zaehlerSpieler1 == zaehlerSpieler2)
    {
        return 0;
    }
    if (zaehlerSpieler1 < zaehlerSpieler2)
    {
        return 2;
    }
    else
    {
        return 1;
    }
}

/**
* @brief Ueberprueft fuer zwei Indizes, ob sie auf dem Spielfeld sind
*
* @param posX Index fuer die Spalte
* @param posY Index fuer die Zeile
* @return true, wenn Spalte und Zeile innerhalb des Spielfelds sind, sonst false
*/
bool aufSpielfeld(const int posX, const int posY)
{
    // Hier erfolgt jetzt Ihre Implementierung ...
	if (posX >= 0 && posX < GROESSE_X && posY >= 0 && posY < GROESSE_Y) {
	        return true;
	    } else {
	        return false;
	    }
    return false;
}


/**
 * @brief Ueberprueft fuer zwei Indizes, ob der Zug gueltig ist
 *
 *  Ueberprueft, ob auf einem benachbarten Feld ein gegnerischer Stein liegt.
 *  Wenn ja, wird diese Richtung solange untersucht, bis ein eigener Stein
 *  gefunden wird. Wird vorher der Spielfeldrand erreicht oder ein leeres Feld
 *  gefunden, wird false zurueckgegeben, sonst true
 *
 * @param spielfeld Das aktuelle Spielfeld
 * @param aktuellerSpieler Der aktuelle Spieler
 * @param posX Zu ueberpruefende Spalte
 * @param posY Zu ueberpruefende Zeile
 * @return
 */
bool zugGueltig(const int spielfeld[GROESSE_Y][GROESSE_X], const int aktuellerSpieler, const int posX, const int posY)
{
    int gegner = 3 - aktuellerSpieler; // dasselbe wie: if aktuellerSpieler == 1 -> gegner = 2
                                       //               if aktuellerSpieler == 2 -> gegner = 1

    if (spielfeld[posY][posX] != 0) // ist das Feld leer?
    {
        return false;
    }

    // Alle Richtungen ueberpruefen bis erster gueltiger Zug gefunden
    for (int j = -1; j <= 1; j++)
    {
        for (int i = -1; i <= 1; i++)
        {
            // Hier erfolgt jetzt Ihre Implementierung ...
        if (i == 0 && j == 0)continue; // 0, 0 is the position of the player.
        int x = posX + i; //posX und posY are the position, that we want to observe. If it is occupied or not.
        int y = posY + j;

        bool gegnerGefunden = false;

			while (x >= 0 && x < GROESSE_X && y >= 0 && y < GROESSE_Y){
				if (spielfeld[y][x] == gegner){
					gegnerGefunden = true;
				}
				else if (spielfeld[y][x] == aktuellerSpieler)
				{
					if (gegnerGefunden)
					{ //if gegnerGefunden == 0, it means that there is not yet occupied. and we can
						return true; // use this block.
					}
					else
						break;
				}
				else
				{
					break;
				}
				x += i;
				y += j;// checking every direction
			}

        }
    }
    return false;
}


/**
 * @brief Funktion, die einen Zug ausfuehrt
 *
 * @param spielfeld Das aktuelle Spielfeld
 * @param aktuellerSpieler Der aktuelle Spieler
 * @param posX Die aktuelle Spalte
 * @param posY Die aktuelle Zeile
 */
void zugAusfuehren(int spielfeld[GROESSE_Y][GROESSE_X], const int aktuellerSpieler, const int posX, const int posY)
{
    int gegner = 3 - aktuellerSpieler;

    //Alle Richtungen bearbeiten
    for (int j = -1; j <= 1; j++)
    {
        for (int i = -1; i <= 1; i++)
        {
            // aehnlich wie die Funktion zugGueltig(), aber stellen Sie sicher, das alle gegnerischen Steine in
            // allen Richtungen in Ihre eigenen Steine umgewandelt werden
            //
            // Hier erfolgt jetzt Ihre Implementierung ...
        	if (i == 0 && j == 0)
        		continue;
        	int x = posX + i;
        	int y = posY + j;
        	bool gegnerGefunden = false;

        	while (x >= 0 && x < GROESSE_X && y >= 0 && y < GROESSE_Y && spielfeld[y][x] == gegner) //pass any gegner
        	{
        		x += i;
        		y += j;
        		gegnerGefunden = true;
        	}

            if (gegnerGefunden && x >= 0 && x < GROESSE_X && y >= 0 && y < GROESSE_Y && spielfeld[y][x] == aktuellerSpieler)
            {
                int xRueck = posX + i;
                int yRueck = posY + j;

                while (xRueck != x || yRueck != y) //turn opponents stone to aktuellerspieler´s stone
                {
                    spielfeld[yRueck][xRueck] = aktuellerSpieler;
                    xRueck += i;
                    yRueck += j;
                }
            }
        }
    }
    spielfeld[posY][posX] = aktuellerSpieler; //setzen den aktuellen Stein.

}
/**
 * \brief
 *
 * @param spielfeld aktuelle Spielfeld
 * @param aktuellerSpieler Spieler, die spielen
 * @return
 */
int moeglicheZuege(const int spielfeld[GROESSE_Y][GROESSE_X], const int aktuellerSpieler)
{
    // Hier erfolgt jetzt Ihre Implementierung ...
    
	int anzahl = 0;
	for (int y = 0; y < GROESSE_Y; y++){
		for (int x = 0; x < GROESSE_X; x++){
			if (zugGueltig(spielfeld, aktuellerSpieler, x, y)){
				anzahl++;
			}
		}
	}
    return anzahl;
}

/**
 * \brief eine von einer Person ausgeführte Funktion
 *
 * @param spielfeld aktuelle Spielfeld
 * @param aktuellerSpieler Spieler, die spielen
 * @return true, falls der Zug erfolgreich ausgeführt wurde, sonst false
 */
bool menschlicherZug(int spielfeld[GROESSE_Y][GROESSE_X], const int aktuellerSpieler)
{
    if (moeglicheZuege(spielfeld, aktuellerSpieler) == 0)
    {
        return false;
    }

    int posX;
    int posY;
    std::string symbolSpieler;
    if (aktuellerSpieler == 1)
    {
        symbolSpieler = "X";
    }
    else
    {
        symbolSpieler = "O";
    }

    while (true)
    {
        std::string eingabe;
        std::cout << std::endl << "Du bist " << symbolSpieler << ". Dein Zug (z.B. A1, a1): " ;
        std::cin >> eingabe;
        posX = (int) eingabe[0] % 32 -1;
        posY = (int) eingabe[1] - 49;

        if (zugGueltig(spielfeld, aktuellerSpieler, posX, posY))
        {
            //accept turn;
            break;
        }
        else
        {
            std::cout << std::endl << "Ungueltige Eingabe !" << std::endl;
        }
    }

    zugAusfuehren(spielfeld, aktuellerSpieler, posX, posY);
    std::cout << std::endl << "Spieler " << aktuellerSpieler << " setzt auf " << (char) (posX + 65) << (posY + 1) << std::endl;

    return true;
}

/**
 * \brief Der Hauptprozess des Spiels wird hier abgewickelt
 *
 * @param spielerTyp Typ der Spieler in 2 Elementen Arrays
 */
void spielen(const int spielerTyp[2])
{
    int spielfeld[GROESSE_Y][GROESSE_X];

    //Erzeuge Startaufstellung
    initialisiereSpielfeld(spielfeld);

    int aktuellerSpieler = 1;
    zeigeSpielfeld(spielfeld);

    // solange noch Zuege bei einem der beiden Spieler moeglich sind
    //
    // Hier erfolgt jetzt Ihre Implementierung ...
    while (moeglicheZuege(spielfeld, 1) > 0 || moeglicheZuege(spielfeld, 2) > 0)
    {
        bool zugErfolgreich = false;

        if(spielerTyp[aktuellerSpieler-1] == COMPUTER)
        {
        	zugErfolgreich = computerZug (spielfeld, aktuellerSpieler);
        }
        else
        {
        	zugErfolgreich = menschlicherZug (spielfeld, aktuellerSpieler);
        }

        if (zugErfolgreich)
        {
        	zeigeSpielfeld(spielfeld);
        }
        else
        {
        	std::cout << "Spieler " << aktuellerSpieler << " kann Zug nicht ausführen" << std::endl;
        }
        aktuellerSpieler = 3 - aktuellerSpieler; //change current player
    }

    switch (gewinner(spielfeld))
    {
        // Hier erfolgt jetzt Ihre Implementierung ...
    case 0:
        std::cout << "Unentschieden!" << std::endl;
        break;
    case 1:
        std::cout << "Spieler 1 (X) gewinnt!" << std::endl;
        break;
    case 2:
        std::cout << "Spieler 2 (O) gewinnt!" << std::endl;
        break;
    }
}

/**
 * \brief Hauptprogramm
 *
 * @return 0, falls das Programm erfolgreich ausgeführt
 */

int main()
{
    if (TEST == 1)
    {
        bool gesamtErgebnis = ganzenTestAusfuehren();
        if (gesamtErgebnis == true)
        {
            std::cout << "ALLE TESTS BESTANDEN!" << std::endl;
        }
        else
        {
            std::cout << "MINDESTENS EIN TEST IST FEHLGESCHLAGEN!" << std::endl;
            exit(1);
        }
        std::cout << std::endl << std::endl;
    }
    
    // Die folgenden drei Zeilen werden auskommentiert oder geloescht, nachdem Sie die Funktion spielen()
    // implementiert haben (waeren sonst doppelt)
    int spielfeld[GROESSE_Y][GROESSE_X];

    initialisiereSpielfeld(spielfeld);

    zeigeSpielfeld(spielfeld);

    // int spielerTyp[2] = { COMPUTER, COMPUTER };  // Feld, das Informationen ueber den Typ des Spielers enthaelt. MENSCH(=1) oder COPMUTER(=2)
    // spielen(spielerTyp);
    //
    // Hier erfolgt jetzt Ihre Implementierung ...
    int spielerTyp[2];
    char spielereingabe = ' ';
    do
    {
    	std::cout << "Start!" << std::endl;
    	std::cout << "Ist Spieler 1 ein Computer ? (j/n) ";
    	//std::cout << "'C' für Computer und 'M' für Mensch." << std::endl;
    	//std::cout << "Bitte Spielertyp für Spieler 1 eingeben: ";
    	std::cin >> spielereingabe;
    	spielerTyp[0] = toupper(spielereingabe) == 'J' ? COMPUTER : MENSCH;
    	//std::cout << "Bitte Spielertyp für Spieler 2 eingeben: ";
    	std::cout << "Ist Spieler 1 ein Computer ? (j/n) ";
    	std::cin >> spielereingabe;
    	spielerTyp[1] = toupper(spielereingabe) == 'J' ? COMPUTER : MENSCH;
    	std::cout << std::endl;

    	initialisiereSpielfeld(spielfeld);

        spielen(spielerTyp);
		std::cout << std::endl;
		std::cout << "Geben Sie [B] ein, um das Spiel zu beenden, ein anderes Zeichen, um fortzufahren.  ";
		std::cin  >> spielereingabe;
	}
	while(toupper(spielereingabe) != 'B');

    return 0;
}
