#include <iostream>
#include <string>
#include "seat.h"




const int MAIN_HALL_ADDITION= 100;




[]
Seat::Seat(int line, int chair, int base_price) :
    line(line), chair(chair), base_price(base_price) {
}
string Seat::location() {
    string s;
    s +="line: ";
    s += std::to_string(line);
    s +=", chair: ";
    s += std::to_string(chair);;
    return s;
}

const char* NoPrice::what() const noexcept {
    return "Not For Sale !";
}

GreenRoomSeat::GreenRoomSeat(int line, int chair): Seat(line,chair,0) {
}

GreenRoomSeat::~GreenRoomSeat(){
}

string GreenRoomSeat::location(){
    Seat* seat = this;
    return "Green Room-> " + (seat)->Seat::location();
}

int GreenRoomSeat::price() {
    throw NoPrice();
}

MainHallSeat::MainHallSeat(int line, int chair, int base_price)
                : Seat(line, chair, base_price) {
}

MainHallSeat::~MainHallSeat(){
}

int MainHallSeat::price() {
    return base_price + 100;
}

SpecialSeat::SpecialSeat(int line, int chair, int base_price)
             : MainHallSeat(line, chair, base_price){
}

SpecialSeat::~SpecialSeat(){
}

int SpecialSeat::price() {
    MainHallSeat* s = this;
    return s->MainHallSeat::price() + 300;
}

RegularSeat::RegularSeat(char area, int line, int chair, int base_price)
        :  MainHallSeat(line, chair, base_price), area(area) {
}

RegularSeat::~RegularSeat() {
}

string RegularSeat::location(){
    Seat* seat = this;
    string s;
    s = "area: ";
    s += area;
    s += ", ";
    return s + seat->Seat::location();
}

GoldenCircleSeat::GoldenCircleSeat(int line, int chair, int base_price)
        : SpecialSeat(line, chair, base_price){
}
GoldenCircleSeat::~GoldenCircleSeat(){
}
string GoldenCircleSeat::location(){
    Seat* seat = this;
    return "Golden Circle-> " + seat->Seat::location();
}
int GoldenCircleSeat::price(){
    SpecialSeat* seat = this;
    return seat->SpecialSeat::price() + 1000;
}

DisablePodiumSeat::DisablePodiumSeat(int line, int chair, int base_price)
        : SpecialSeat(line, chair, base_price){
}
DisablePodiumSeat::~DisablePodiumSeat(){
}
string DisablePodiumSeat::location(){
    Seat* seat = this;
    return "Disable Podium-> " + seat->Seat::location();
}
int DisablePodiumSeat::price(){
    return 200;
}

FrontRegularSeat::FrontRegularSeat(char area, int line, int chair, int base_price)
: RegularSeat(area, line, chair, base_price){
}

FrontRegularSeat::~FrontRegularSeat() {
}

string FrontRegularSeat::location() {
    RegularSeat* seat = this;
    return "Front-> " + seat->RegularSeat::location();
}

int FrontRegularSeat::price() {
    MainHallSeat* seat = this;
    return seat->MainHallSeat::price() + 500;
}

MiddleRegularSeat::MiddleRegularSeat(char area, int line, int chair, int base_price)
        : RegularSeat(area, line, chair, base_price){
}

MiddleRegularSeat::~MiddleRegularSeat() {
}

string MiddleRegularSeat::location() {
    RegularSeat* seat = this;
    return "Middle-> " + seat->RegularSeat::location();
}

int MiddleRegularSeat::price() {
    MainHallSeat* seat = this;
    return seat->MainHallSeat::price() + 250;
}

RearRegularSeat::RearRegularSeat(char area, int line, int chair, int base_price)
        : RegularSeat(area, line, chair, base_price){
}

RearRegularSeat::~RearRegularSeat() {
}

string RearRegularSeat::location() {
    RegularSeat* seat = this;
    return "Rear-> " + seat->RegularSeat::location();
}

int RearRegularSeat::price() {
    MainHallSeat* seat = this;
    return seat->MainHallSeat::price();
}
