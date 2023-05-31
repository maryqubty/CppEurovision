#ifndef EUROVISION_H_
#define EUROVISION_H_

#include <iostream>
#include <string>

using std::string;
using std::ostream;
using std::endl;

//---------------------------------------------------

enum VoterType { All, Regular, Judge };
enum Phase { Registration, Contest, Voting };

//---------------------------------------------------

class Participant
{
    string state_name;
    string song_name;
    int song_length;
    string singer_name;
    bool is_registered;

public :

    Participant() = delete;
    Participant(const string& state, const string& song, const int& length
                ,const string& singer);
    ~Participant() = default;
    Participant& operator=(const Participant&) = delete;
    Participant(const Participant&) = delete;
    string state() const;
    string song() const;
    int timeLength() const;
    string singer() const;
    bool isRegistered() const;
    void update(const string& song, const int& length,
                const string& singer);
    void updateRegistered(bool is_registered);
};

ostream& operator<<(ostream&, const Participant&);

//---------------------------------------------------


class Voter
{

    string voter_state;
    VoterType voter_type;
    int votes_num;

public :

    explicit Voter(const string& State, VoterType type = Regular);
    ~Voter() = default;
    int timesOfVotes() const;
    VoterType voterType() const;
    string state() const;
    Voter& operator++();
};
ostream& operator<<(ostream& os, const Voter& voter);

// -----------------------------------------------------------

struct Vote
{
    Voter& voter;
    string voted_states[10];

    Vote(Voter& voter, const string& state1, const string& state2 = "",
                 const string& state3 = "", const string& state4 = "",
                 const string& state5 = "", const string& state6 = "",
                 const string& state7 = "", const string& state8 = "",
                 const string& state9 = "", const string& state10 = "");
    ~Vote() = default;
};



// -----------------------------------------------------------


class MainControl
{
    Phase phase;
    Participant **participants;
    int participants_num;
    int max_time_length;
    int max_participants_num;
    int max_votes;
    int* judges_votes;
    int* regulars_votes;
    int* final_score;

public :
    explicit MainControl(int time_length = 180,
                int participants = 26, int votes = 5);
    ~MainControl();
    void setPhase(Phase new_phase);
    bool legalParticipant(const Participant& p);
    bool participate(const string& state_name);
    MainControl& operator+=(Participant& p);
    MainControl& operator+=(Vote vote);
    MainControl& operator-=(Participant& p);
    string operator()(int, VoterType);
    friend ostream& operator<<(ostream&, const MainControl&);

    class Iterator {
    public:
        Participant** participants;
        int i;
        int* final_score;

        Iterator() = default;
        ~Iterator() = default;

        class BiggerThan {
        public:
            bool operator()(Iterator, Iterator);
        };
        bool operator==(const Iterator)const;
        bool operator<(Iterator);
        Iterator& operator++();
        Participant& operator*();
    };
    Iterator begin();
    Iterator end();
};



template<typename Iterator, typename Compare>
Iterator get(const Iterator begin, const Iterator end, const int i, Compare C){
    if(begin == end)
        return end;
    int size = 0;
    for(Iterator j = begin ; j < end ; ++j)
    {
        size++;
    }
    if(i > size || i <= 0)
        return end;
    bool* used = new bool[size];
    for(int j = 0 ; j < size ; ++j)
    {
        used[j] = false;
    }
    Iterator max;
    int max_index;
    for(int num = 0 ; num < i ; num++)
    {
        max = begin;
        max_index = 0;
        while(used[max_index])
        {
            ++max;
            max_index++;
        }
        int index = 0;
        for(Iterator j = begin ; j < end ; ++j)
        {
            if(used[index]) {
                index++;
                continue;
            }
            if(C(j, max)){
                max = j;
                max_index = index;
            }
            index++;
        }
        used[max_index] = true;
    }
    delete[] used;
    return max;
}

// -----------------------------------------------------------

#endif
