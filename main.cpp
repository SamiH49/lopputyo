#include <string>
#include <cstdlib>
#include <ctime>
#include <windows.h>

#include "InputValidation.hpp"
#include "HotelManage.hpp"

int main()
{
    SetConsoleOutputCP(65001); // UTF-8 Konsoli käyttöön tällä, printaa ääkköset

    Hotel hotel;

    // Valikkomenu looppi
    int choice;
    while (true)
    {
        std::cout << "Hotelli varausjärjestelmä\n";
        std::cout << "1. Näytä huoneiden tiedot\n";
        std::cout << "2. Varaa huone\n";
        std::cout << "3. Peru huoneen varaus varausnumerolla\n";
        std::cout << "4. Etsi huone varausnumerolla\n";
        std::cout << "5. Lopeta ohjelma\n";
        std::cout << "Kirjoita valintasi: ";
        choice = askNumber();

        // Näytä kaikki huoneet
        if (choice == 1)
        {
            hotel.showRooms();
        }
        // Huoneen varaus
        else if (choice == 2)
        {
            int roomNumber;
            string name;
            int nights;

            while (true)
            {

                std::cout << "Syötä huonenumero: ";
                roomNumber = askNumber();

                // Katsotaan onko huonetta olemassa ja onko sitä varattu.
                HotelRoom *room = hotel.getRoomByNumber(roomNumber);
                if (room == nullptr)
                {
                    std::cout << "Hotellihuonetta tällä numerolla ei ole olemassa.\n";
                }
                else if (room->reserved)
                {
                    std::cout << "Huone " << roomNumber << " on jo varattu, valitse toinen.\n";
                }
                else
                {
                    break;
                }
            }
            std::cout << "Vaaraajan nimi: ";
            name = askString();

            std::cout << "Kuinka monta yötä haluat varata: ";
            nights = askNumber();

            hotel.reserveRoom(roomNumber, name, nights);
        }
        else if (choice == 3)
        {
            std::cout << "Anna varausnumero: ";
            int resNum;
            resNum = askNumber();

            HotelRoom *room = hotel.getRoomByReservationNumber(resNum);
            if (room == nullptr)
            {
                std::cout << "Hotellihuonetta tällä varausnumerolla ei ole olemassa.\n";
            }
            else if (!room->reserved)
            {
                std::cout << "Huonetta varausnumerolla " << resNum << " ei ole varattu, valitse uudestaan.\n";
            }
            else
            {
                room->cancelReservation();
            }
        }
        else if (choice == 4)
        {
            std::cout << "Varausnumero: ";
            int resNum = askNumber();
            HotelRoom *room = hotel.getRoomByReservationNumber(resNum);
            if (room != nullptr)
            {
                room->printInfo();
            }
            else
            {
                std::cout << "Huonetta tällä varausnumerolla ei ole olemassa.\n";
            }
        }
        else if (choice == 5)
        {
            std::cout << "Ohjelma suljettu.\n";
            break;
        }
        else
        {
            std::cout << "Valitsethan jonkun ylläolevista vaihtoehdoista 1-5.\n";
        }
    }

    // Ohjelman päätyttyä tallennetaan hotellin varaustiedot .json tiedostoon.
    hotel.saveRooms("roomData.json");

    // system("pause");
    return 0;
}
