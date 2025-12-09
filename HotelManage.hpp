#ifndef HOTELMANAGE_HPP
#define HOTELMANAGE_HPP

#include <string>
#include <fstream>
#include <ctime>
#include "Room.hpp"

#include "json.hpp"
using json = nlohmann::json;

struct Hotel
{
    std::vector<HotelRoom> rooms;

    // Funktio käynnistyy kun main.cpp initialisoi tämän headerin.
    Hotel()
    {
        // Katsotaan, onko hotellin varaus / huonetietoja jo olemassa. Luodaan jos ei ole ja ladataan vanhat jos on.
        loadRooms("roomData.json");
        if (rooms.empty())
        {
            // Luodaan 40-300 huonetta. 50/50 1hh ja 2hh huoneita.
            int numRooms;
            srand(time(nullptr));
            while (true)
            {
                numRooms = rand() % 261 + 40;

                if (numRooms % 2 == 0)
                {

                    break;
                }
            }
            int half = numRooms / 2;

            // Puolet huoneista on 1 henkilön ja toinen puoli 2 henkilön.
            for (int i = 1; i <= numRooms; ++i)
            {
                if (i <= half)
                    rooms.emplace_back(i, "Yhden Henkilön");
                else
                    rooms.emplace_back(i, "Kahden Henkilön");
            }

            std::cout << "Hotelli luotu " << numRooms << ":lla huoneella.\n";
        }
        else
        {
            std::cout << "Ladattu hotellin huoneet aikaisemmista tiedoista " << rooms.size() << ":lla huoneella.\n";
        }
    }

    // Tallentaa huonevectorin .json tiedostoon.
    void saveRooms(const string &filename)
    {
        json j = rooms;
        std::ofstream out(filename);
        out << j.dump(4);
    }

    // Ladataan olemassa olevat tiedot, jos niitä ei ole niin ei huolta kun yläfunktio luo uudet huoneet.
    void loadRooms(const std::string &filename)
    {
        std::ifstream fileRead(filename);

        try
        {
            rooms = json::parse(fileRead).get<std::vector<HotelRoom>>();
        }
        catch (...)
        {
        }
    }

    // Iteroidaan kaikki huoneet ja tulostetaan niiden tiedot.
    void showRooms() const
    {
        std::cout << "Huoneiden tiedot: \n";
        for (const auto &r : rooms)
            r.printInfo();
        std::cout << "\n";
    }

    // "Etsitään" hotellihuone sen huonenumeron perusteella
    HotelRoom *getRoomByNumber(int roomNumber)
    {
        // Palautetaan huoneen referenssi, jotta sitä voidaan muokata funktion ulkopuolella.
        for (auto &room : rooms)
        {
            if (room.roomNumber == roomNumber)
                return &room;
        }
        // Palautetaan nullptr jos huonetta ei löydy
        return nullptr;
    }

    // "Etsitään" hotellihuone sen varausnumeron perusteella
    HotelRoom *getRoomByReservationNumber(int reservationNumber)
    {
        // Palautetaan huoneen referenssi, jotta sitä voidaan muokata funktion ulkopuolella.
        for (auto &room : rooms)
        {
            if (room.reservationNum == reservationNumber)
                return &room;
        }
        // Palautetaan nullptr jos huonetta ei löydy
        return nullptr;
    }

    // Huoneen varausfunktio, kaikki validoitu jo ennen funktiota, joten ei tässä tarvitse.
    void reserveRoom(int roomNumber, const string &guestName, int nights)
    {
        HotelRoom *room = getRoomByNumber(roomNumber);

        room->reserve(guestName, nights);

        std::cout << "Huone " << roomNumber << " | Huonetyyppi: " << room->roomType << " | Varaaja: "
                  << guestName << " | Varattu " << nights << ":ksi yöksi | Kokonaishinta: €"
                  << room->getTotalCost() << " | Varausnumero: " << room->reservationNum << "\n\n";
    }

    // Varauksen peruminen, kaikki validoitu jo ennen funktiota, joten ei tässä tarvitse.
    void cancelReservation(int roomNumber)
    {

        HotelRoom *room = getRoomByNumber(roomNumber);

        room->cancelReservation();
        std::cout << "Varaus huoneelle " << roomNumber << " peruttu.\n";
    }
};

#endif