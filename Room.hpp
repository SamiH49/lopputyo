#ifndef ROOM_HPP
#define ROOM_HPP

#include <random>
#include <ctime>
#include "json.hpp"
using json = nlohmann::json;

struct HotelRoom
{

    int roomNumber;
    string roomType;
    string guestName;
    bool reserved;
    double pricePerNight;
    int nightsBooked;
    int reservationNum;

    // Hotellihuoneen luonti
    HotelRoom(int number = 0, const std::string &type = "Yhden Henkilön")
        : roomNumber(number), roomType(type), guestName(""), reserved(false),
          pricePerNight(type == "Yhden Henkilön" ? 100.0 : 150.0), reservationNum(0), nightsBooked(0)
    {
        std::srand(std::time(nullptr));
    }

    // Varausfunktio
    void reserve(const std::string &name, int nights)
    {
        // Arvotaan alennus 0, 10 tai 20
        static std::mt19937 gen(std::random_device{}());
        int discountPercentage = std::uniform_int_distribution<int>(0, 2)(gen) * 10;
        guestName = name;
        reserved = true;
        nightsBooked = nights;
        pricePerNight = pricePerNight * (1.0 - discountPercentage / 100.0);
        // Randomi varausnumero väliltä 10000-99999
        reservationNum = 10000 + std::rand() % 99999;
    }

    // Peru huoneen varaus, muutetaan kaikki tarvittava oletusarvoiksi.
    void cancelReservation()
    {
        guestName = "";
        reserved = false;
        nightsBooked = 0;
        reservationNum = 0;
        pricePerNight = roomType == "Yhden Henkilön" ? 100.0 : 150.0;
    }

    // Lasketaan huoneen kokonaishinta varaukselle
    double getTotalCost() const
    {
        return reserved ? pricePerNight * nightsBooked : 0.0;
    }

    // Tulosta huoneen tiedot
    void printInfo() const
    {
        std::cout << "Huonenumero " << roomNumber << " | " << roomType << " | " << (reserved ? ("Varaaja: " + guestName) : "Ei varattu")
                  << " | Hinta: " << pricePerNight << "€ per yö"
                  << " | Yöitä varattu: " << (reserved ? std::to_string(nightsBooked) : "0")
                  << " | Kokonaishinta: €" << getTotalCost() << "\n";
    }
};

// Funktiot, joiden avulla tiedot tallennetaan ja luetaan json tiedostoksi.
void to_json(json &j, const HotelRoom &r)
{
    j = json{
        {"roomNumber", r.roomNumber},
        {"reserved", r.reserved},
        {"pricePerNight", r.pricePerNight},
        {"nightsBooked", r.nightsBooked},
        {"reservationNum", r.reservationNum},
        {"roomType", r.roomType},
        {"guestName", r.guestName}};
}

void from_json(const json &j, HotelRoom &r)
{
    j.at("roomNumber").get_to(r.roomNumber);
    j.at("reserved").get_to(r.reserved);
    j.at("pricePerNight").get_to(r.pricePerNight);
    j.at("nightsBooked").get_to(r.nightsBooked);
    j.at("reservationNum").get_to(r.reservationNum);
    j.at("roomType").get_to(r.roomType);
    j.at("guestName").get_to(r.guestName);
}

#endif