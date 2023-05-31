#include <iostream>
#include <string>
#include "eurovision.h"

Participant::Participant(const string& state, const string& song,
                         const int& length , const string& singer): state_name(state),
        song_name(song), song_length(length), singer_name(singer),
        is_registered(false){
}

string Participant::state() const{
    return state_name;
}

string Participant::song() const{
    return song_name;
}

int Participant::timeLength() const{
    return song_length;
}

string Participant::singer() const{
    return singer_name;
}

bool Participant::isRegistered() const{
    return is_registered;
}

void Participant::update(const string& song, const int& length,
       const string& singer){
    if(is_registered)
        return;
    if(!song.empty())
        song_name = song;
    if(length != 0)
        song_length = length;
    if(!singer.empty())
        singer_name = singer;
}

void Participant::updateRegistered(bool registered){
     is_registered = registered;
}

ostream& operator<<(ostream& os, const Participant& p){
    return os << "[" << p.state() << "/" << p.song() << "/" << p.timeLength()
              << "/" << p.singer() << "]";
}

Voter::Voter(const string& state, VoterType type) :
        voter_state(state), voter_type(type), votes_num(0)
{
}

int Voter::timesOfVotes() const{
    return votes_num;
}

VoterType Voter::voterType() const{
    return voter_type;
}

string Voter::state() const{
    return voter_state;
}

Voter& Voter::operator++(){
    votes_num++;
    return *this;
}

ostream& operator<<(ostream& os, const Voter& voter){
    os << "<" << voter.state() << "/";
    if(voter.voterType() == Regular)
        os << "Regular";
    else if(voter.voterType() == Judge)
        os << "Judge";
    os << ">";
    return os;
}

Vote::Vote(Voter& v, const string& state1, const string& state2,
           const string& state3, const string& state4, const string& state5,
           const string& state6, const string& state7, const string& state8,
           const string& state9, const string& state10) : voter(v) {
    voted_states[0] = state1;
    voted_states[1] = state2;
    voted_states[2] = state3;
    voted_states[3] = state4;
    voted_states[4] = state5;
    voted_states[5] = state6;
    voted_states[6] = state7;
    voted_states[7] = state8;
    voted_states[8] = state9;
    voted_states[9] = state10;
}

MainControl::MainControl(const int time_length,
            const int num_participants, const int votes){
    phase = Registration;
    max_participants_num = num_participants;
    max_time_length = time_length;
    max_votes = votes;
    participants_num = 0;
    participants = new Participant*[max_participants_num + 1];
    judges_votes = new int[max_participants_num];
    regulars_votes = new int[max_participants_num];
    final_score = new int[max_participants_num];
    for(int i=0 ; i < max_participants_num ; i++)
    {
        participants[i] = nullptr;
        judges_votes[i] = 0;
        regulars_votes[i] = 0;
        final_score[i] = 0;
    }
    participants[max_participants_num] = nullptr;
}

MainControl::~MainControl(){
    delete[] participants;
    delete[] judges_votes;
    delete[] regulars_votes;
    delete[] final_score;
}

void MainControl::setPhase(const Phase new_phase){
    if(phase == Registration && new_phase == Contest)
        phase = new_phase;

    if(phase == Contest && new_phase == Voting)
    {
        phase = new_phase;
    }
}

bool MainControl::legalParticipant(const Participant& p){
    if(p.state().empty() || p.singer().empty() || p.song().empty() ||
       p.timeLength() > max_time_length || p.timeLength()<0)
        return false;
    return true;
}

bool MainControl::participate(const string& state_name){
    for(int i=0 ; i < participants_num ; i++)
    {
        if(participants[i]->state() == state_name)
            return true;
    }
    return false;
}

MainControl& MainControl::operator+=(Participant& p){
    if(phase != Registration || participants_num == max_participants_num)
        return *this;
    if(!legalParticipant(p))
        return *this;
    if(participate(p.state()))
        return *this;
    participants[participants_num] = &p;
    p.updateRegistered(true);
    participants_num++;
    for(int i = participants_num-1 ; i >= 0 ; i--)
    {
        int max_index=0;
        for(int j = 0 ; j <= i ; j++)
        {
            if(participants[j]->state() >
               participants[max_index]->state())
                max_index = j;
        }
        Participant* temp = participants[max_index];
        participants[max_index] = participants[i];
        participants[i] = temp;
    }
    return *this;
}

MainControl& MainControl::operator+=(Vote vote){
    if(phase != Voting)
        return *this;
    if(!participate(vote.voter.state()))
        return *this;
    if(vote.voter.voterType() == Regular)
    {
        if(vote.voter.state() == vote.voted_states[0])
            return *this;
        if(!participate(vote.voted_states[0]))
            return *this;
        if(vote.voter.timesOfVotes() == max_votes)
            return *this;
        ++vote.voter;
        for(int i=0 ; i < participants_num ; i++)
        {
            if(participants[i]->state() == vote.voted_states[0])
            {
                regulars_votes[i]++;
            }
        }
    }
    if(vote.voter.voterType() == Judge)
    {
        bool legal_vote = false;
        if(vote.voter.timesOfVotes() == 1)
            return *this;

        int score;
        for(int i=0 ; i < 10 ; i++)
        {
            if(i==0)
                score = 12;
            else if(i==1)
                score = 10;
            else
                score = 10 - i;
            for(int j=0 ; j < participants_num ; j++)
            {
                if(participants[j]->state() == vote.voted_states[i])
                {
                    if(vote.voter.state() != vote.voted_states[i]
                       && participate(vote.voted_states[i]))
                    {
                        judges_votes[j] += score;
                        legal_vote = true;
                    }
                }
            }
        }
        if(legal_vote)
        {
            ++vote.voter;

        }
    }
    return *this;
}

MainControl& MainControl::operator-=(Participant& p){
    if(phase != Registration || !p.isRegistered())
        return *this;
    p.updateRegistered(false);
    for(int i=0 ; i < participants_num ; i++) {
        if (participants[i]->state() == p.state())
        {
            participants[i] = participants[participants_num - 1];
            participants[participants_num - 1] = nullptr;
            participants_num--;
        }
    }
    for(int i = participants_num-1 ; i >= 0 ; i--)
    {
        int max_index=0;
        for(int j = 0 ; j <= i ; j++)
        {
            if(participants[j]->state() >
               participants[max_index]->state())
                max_index = j;
        }
        Participant* temp = participants[max_index];
        participants[max_index] = participants[i];
        participants[i] = temp;
    }
    return *this;
}

bool MainControl::Iterator::operator==(const Iterator iterator) const{
    if(participants == iterator.participants)
        return (i==iterator.i);
    return false;
}

bool MainControl::Iterator::operator<(Iterator iterator){
    if(participants == iterator.participants)
        return (i<iterator.i);
    return false;
}

bool MainControl::Iterator::BiggerThan::operator()(Iterator iterator1,
                                                   Iterator iterator2){
    if(iterator1.final_score[iterator1.i] == iterator2.final_score[iterator2.i])
        return (*iterator1).state() > (*iterator2).state();
    return iterator1.final_score[iterator1.i] >
           iterator2.final_score[iterator2.i];
}

MainControl::Iterator& MainControl::Iterator::operator++(){
    i++;
    return *this;
}
Participant& MainControl::Iterator::operator*(){
    return *participants[i];
}
MainControl::Iterator MainControl::begin(){
    Iterator iterator=Iterator();
    iterator.participants = participants;
    iterator.i = 0;
    iterator.final_score = final_score;
    return iterator;
}

MainControl::Iterator MainControl::end(){
    Iterator iterator=Iterator();
    iterator.participants = participants;
    iterator.i = participants_num;
    iterator.final_score = final_score;
    return iterator;
}

string MainControl::operator()(int i, VoterType v){
    for(int j = 0 ; j < participants_num ; j++)
    {
        final_score[j] = 0;
    }
    if(v == Judge || v == All)
    {
        for(int j = 0 ; j < participants_num ; j++)
        {
            final_score[j] += judges_votes[j];
        }
    }
    if(v == Regular || v == All)
    {
        for(int j = 0 ; j < participants_num ; j++)
        {
            final_score[j] += regulars_votes[j];
        }
    }
    Iterator::BiggerThan biggerThan;
    Iterator iterator = get(this->begin(), this->end(), i, biggerThan);
    if(iterator == this->end())
        return "";
    return (*iterator).state();
}

ostream& operator<<(ostream& os, const MainControl& eurovision){
    if(eurovision.phase == Registration)
    {
        os  << "{" << endl << "Registration" << endl;
        for (int i = 0; i < eurovision.participants_num ; i++) {
           os << *eurovision.participants[i] << endl;
        }
        return os << "}" << endl;
    }
    if(eurovision.phase == Contest)
    {
        return os << "Contest" << endl;
    }
    if(eurovision.phase == Voting) {
        os << "{" << endl << "Voting" << endl;
        for (int i = 0; i < eurovision.participants_num; i++) {
            os << eurovision.participants[i]->state() << " : " << "Regular("
               << eurovision.regulars_votes[i] << ") Judge("
               << eurovision.judges_votes[i] << ")" << endl;
        }
        return os << "}" << endl;
    }
    return os;
}



