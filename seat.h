#ifndef SEAT_H
#define SEAT_H

#include <iostream>
#include <string>
using std::string;
using std::exception;


// ---------------------------------------------
/**
 * We used polymorphism in order to use a class as a definition
  of an exception that is returned when asking for a none existent price .
 * This class has a function called :"what"
  which prints a suitable message to describe the error
 */
class NoPrice : public exception
{
public:
    const char* what() const noexcept override;
};

// ---------------------------------------------
/**
 * This class is THEE "father class" which is the base for all the other classes.
 * It has a line field and a chair field that describes the location of a seat
   and a base_price field that represents the base price of a seat.
 * This class has a constructor function and 3 other virtual functions
   to delete the variable, to print the location and return
   the price according to it's type .
 * Seat class is an abstract class
   which means that no variable can be defined by this type.
 */
class Seat
{
    int line;
    int chair;
protected:
    int base_price;
public:
    Seat(int line, int chair, int base_price);
    virtual ~Seat() = default;
    virtual string location();
    virtual int price() = 0;
};

// ---------------------------------------------
/**
 *  This class represents a type of seats that is not for sale ,
    and only specific people can get it .
 *  This class has a constructor and a destructor .
 *  Location function that returns the location as a string ,
    it links strings with other strings that previous location
    functions return.
 *  Price function returns the price of a seat with all the required additions
 */
class GreenRoomSeat : public Seat
{
public:
    GreenRoomSeat(int line ,int chair);
    ~GreenRoomSeat() override;
    string location() override;
    int price() override;
};

// ---------------------------------------------
/**
 * This class is an abstract class that is the father
   of regular seats
 * It has a constructor and a destructor function.
 *  Location function that returns the location as a string ,
    it links strings with other strings that previous location
    functions return.
 *  Price function returns the price of a seat with all the required additions
 *  (100 shekels in addition to the base).
 */
class MainHallSeat : public Seat
{
public:
    MainHallSeat(int line, int chair, int base_price);
    ~MainHallSeat() override;
    string location() override = 0;
    int price() override;
};

// ---------------------------------------------
/**
 * This class is an abstract class which is "the father" of special seats.
 * It has a constructor and destructor functions.
 *  Location function is pure virtual , thus, it's not implemented.
 * Price function returns the price of a seat with all the required additions
 *  (300 shekels in addition to the base).

 */
class SpecialSeat : public MainHallSeat
{
public:
    SpecialSeat(int line, int chair, int base_price);
    ~SpecialSeat() override;
    string location() override = 0;
    int price() override;
};

// ---------------------------------------------
/**
 * This class is a type of seats .
 * It has a constructor and a destructor function.
 *  Location function that returns the location as a string ,
    it links strings with other strings that previous location
    functions return.
 *  Price function returns the price of a seat with all the required additions
 *  (1000 shekels in addition to the additions).
 */
class GoldenCircleSeat : public SpecialSeat
{
public:
    GoldenCircleSeat(int line, int chair, int base_price);
    ~GoldenCircleSeat() override;
    string location() override;
    int price() override;
};

// ---------------------------------------------
/**
 * This class represents seats of type special that are made
   for special people.
 * It has const price that isn't related to
   the base price of the main seat (200 shekels).
 * It has constructor and destructor.
 * Location function returns the location of the seat by calling
 * previous location functions and linking strings.
 * Price function returns a constant price.
 */
class DisablePodiumSeat : public SpecialSeat
{
public:
    DisablePodiumSeat(int line, int chair, int base_price = 0);
    ~DisablePodiumSeat() override;
    string location() override;
    int price() override;
};

// ---------------------------------------------
/**
 * This class is an abstract class that is the father
   of 3 types of regular seats.
 * It has a constructor and a destructor function.
 *  Location function that returns the location as a string ,
    it links strings with other strings that previous location
    functions return.
 *  Price function is pure virtual , thus , it's not implemented.
 */
class RegularSeat : public MainHallSeat
{
    char area;
public:
    RegularSeat(char area, int line, int chair, int base_price);
    ~RegularSeat() override;
    string location() override;
    int price() override = 0;
};

// ---------------------------------------------
/**
 * This class represents a seat of type regular seats.
 * It has a constructor and a destructor .
 *  Location function that returns the location as a string ,
    it links strings with other strings that previous location
    functions return.
 *  Price function returns the price of a seat with all the required additions
 *  (500 shekels in addition to the additions).
 */
class FrontRegularSeat : public RegularSeat
{
public:
    FrontRegularSeat(char area, int line, int chair, int base_price);
    ~FrontRegularSeat() override;
    string location() override;
    int price() override;
};

// ---------------------------------------------
/**
 * This class represents a seat of type regular seats.
 * It has a constructor and a destructor .
 *  Location function that returns the location as a string ,
    it links strings with other strings that previous location
    functions return.
 *  Price function returns the price of a seat with all the required additions
 *  (250 shekels in addition to the additions).
 */
class MiddleRegularSeat : public RegularSeat
{
public:
    MiddleRegularSeat(char area, int line, int chair, int base_price);
    ~MiddleRegularSeat() override;
    string location() override;
    int price() override;
};

// ---------------------------------------------
/**
 * This class represents a seat of type regular seats.
 * It has a constructor and a destructor .
 *  Location function that returns the location as a string ,
    it links strings with other strings that previous location
    functions return.
 *  Price function returns the price of a seat without any additional price.
 */
class RearRegularSeat : public RegularSeat
{
public:
    RearRegularSeat(char area, int line, int chair, int base_price);
    ~RearRegularSeat() override;
    string location() override;
    int price() override;
};

// ---------------------------------------------
#endif
