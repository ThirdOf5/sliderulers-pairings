#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <stdlib.h>
#include "couple.h"
#include "follow.h"
#include "lead.h"
#include "dance.h"

using namespace std;

const int TIMES_TO_DANCE = 2;
const int NUM_COUPLES_IN_DANCE = 3;
vector<bool> which_leads_tried;
vector<bool> which_follows_tried;
int leads_tried = 0;
int follows_tried = 0;

vector<lead> leads;
vector<follow> follows;

lead* pickLead();
follow* pickFollowForLead(lead* dude);
void resetDancers();
bool hasNotDanced(lead* dude, follow* dudette);
void resetTrieds();
bool allLeadsTried();
bool allFollowsTried();
bool isFollowGood(follow* f, lead dude);
bool isLeadGood(lead* l);
void pickFrontCouple(dance* d);
int evaluate();
void runProgram();
void resetEverything();

int main(){

    //initializing random seed
    srand(time(NULL));
    couple danced_last;

    string name;
    int rating;
    cout << "LEADS--------------" << endl;
    ifstream leadFile("leads.txt");
    if (leadFile.is_open())
    {
        while (leadFile >> name >> rating )
        {
            cout << name << '\n';
            lead l = lead(name, rating);
            leads.push_back(l);
        }
        leadFile.close();
    }

    else cout << "Unable to open file";
    cout << endl;

    cout << "FOLLOWS--------------" << endl;
    ifstream followFile("follows.txt");
    if (followFile.is_open())
    {
        while (followFile >> name >> rating)
        {
            cout << name << '\n';
            follow f = follow(name, rating);
            follows.push_back(f);
        }
        followFile.close();
    }

    else{ cout << "Unable to open file"; }

    ////////////////REAL PROGRAM////////////////////////
    //int num_rounds = leads.size() * TIMES_TO_DANCE / NUM_COUPLES_IN_DANCE;
    //cout << num_rounds << endl;

    //vector<dance> rounds;

    //cout << endl << "<---------------------------------------------------------->" << endl;
    //for (int i = 0; i < num_rounds; i++){
    //  cout << "ROUND " << i+1 << endl;
    //  dance round = dance();
    //  for (int j = 0; j < NUM_COUPLES_IN_DANCE; j++){
    //      lead chosenLead = pickLead();
    //      follow chosenFollow = pickFollowForLead(chosenLead);
    //      couple pair = couple(chosenLead, chosenFollow);
    //      //pair.print();

    //      round.couples.push_back(pair);
    //  }
    //  pickFrontCouple(&round);
    //  for (int i = 0; i < NUM_COUPLES_IN_DANCE; i++){
    //      round.couples[i].print();
    //  }
    //  rounds.push_back(round);
    //  resetDancers();
    //  cout << "---------------------------------------" << endl;
    //}

    //evaluate();

    runProgram();

    system("pause");
    return 0;
}


bool isFollowGood(follow* f, lead* dude){
    return ((f->times_danced < TIMES_TO_DANCE) && (hasNotDanced(dude, f)) && !(f->dancing) && !(f->just_danced));
}

bool isLeadGood(lead* l){
    return ((l->times_danced < TIMES_TO_DANCE) && !(l->dancing) && !(l->just_danced));
}

lead* pickLead(){
    int seed = rand() % leads.size();
    lead* chosenOne = &leads[seed];
    if (isLeadGood(chosenOne)){
        chosenOne->times_danced++;
        chosenOne->dancing = true;
        //cout << chosenOne->name << endl;
        resetTrieds();
        return chosenOne;
    }
    else{
        //try again
        which_leads_tried[seed] = true;
        int seed = rand() % leads.size();
        lead* chosenOne = &leads[seed];
        if (isLeadGood(chosenOne)){
            chosenOne->times_danced++;
            chosenOne->dancing = true;
            //cout << chosenOne->name << endl;
            resetTrieds();
            return chosenOne;
        }
        if (leads_tried != leads.size()){
            for (int i = 0; i < which_leads_tried.size(); i++){
                if (which_leads_tried[i] == false){
                    lead* chosen = &leads[i];
                    if (isLeadGood(chosen)){
                        chosen->times_danced++;
                        chosen->dancing = true;
                        resetTrieds();
                        return chosen;
                    }
                }
            }
        }
        if (allLeadsTried()){
            cout << "no suitable lead found" << endl;
            evaluate();
            cout << "running algorithm again....." << endl << endl << endl << endl;
            resetEverything();
            runProgram();

            // evaluate();
            // system("pause");
            // exit(1);
        }
        //cout << "selecting new lead" << endl;
        leads_tried++;
        return pickLead();
    }
}

follow* pickFollowForLead(lead* dude){
    int seed = rand() % follows.size();
    follow* chosenOne = &follows[seed];
    if (isFollowGood(chosenOne, dude)){
        chosenOne->times_danced++;
        chosenOne->dancing = true;
        resetTrieds();
        return chosenOne;
    }
    else{
        //try again
        which_follows_tried[seed] = true;
        if (follows_tried != follows.size()){
            for (int i = 0; i < which_follows_tried.size(); i++){
                if (which_follows_tried[i] == false){
                    if (follows[i].skill_rating + dude->skill_rating == 4){
                        follow* chosen = &follows[i];
                        if (isFollowGood(chosen, dude)){
                            chosen->times_danced++;
                            chosen->dancing = true;
                            resetTrieds();
                            return chosen;
                        }
                    }
                }
            }
            for (int i = 0; i < which_follows_tried.size(); i++){
                if (which_follows_tried[i] == false){
                    follow* chosen = &follows[i];
                    if (isFollowGood(chosen, dude)){
                        chosen->times_danced++;
                        chosen->dancing = true;
                        resetTrieds();
                        return chosen;
                    }
                }
            }
        }
        else if (allFollowsTried()){
            cout << "no suitable follow found for " << dude->name << endl;
            evaluate();
            cout << "running algorithm again....." << endl << endl << endl << endl;
            resetEverything();
            runProgram();

            //  system("pause");
            //  exit(1);
        }
        //cout << "selecting new follow" << endl;
        follows_tried++;
        return pickFollowForLead(dude);
    }
}

void resetDancers(){
    for (int i = 0; i < leads.size(); i++){
        leads[i].just_danced = false;
        follows[i].just_danced = false;
        if (leads[i].dancing == true){
            leads[i].just_danced = true;
        }
        if (follows[i].dancing == true){
            follows[i].just_danced = true;
        }
        leads[i].dancing = false;
        leads[i].inFront = false;
        follows[i].dancing = false;
    }

}


bool hasNotDanced(lead* dude, follow* dudette){
    //cout << "checking if " << dude.name << " and " << dudette.name << " have danced." << endl;
    if (dude->follows_danced_with.size() == 0){
        //cout << "They haven't" << endl;
        return true;
    }
    for (int i = 0; i < dude->follows_danced_with.size(); i++){
        if (dude->follows_danced_with[i]== dudette->name){
            //cout << "They HAVE!!!!!" << endl;
            return false;
        }
    }
    //cout << "They haven't" << endl;
    return true;
}


void resetTrieds(){
    which_leads_tried.clear();
    which_follows_tried.clear();
    for (int i = 0; i < leads.size(); i++){
        which_leads_tried.push_back(false);
        which_follows_tried.push_back(false);
    }
}

bool allLeadsTried(){
    for (int i = 0; i < which_leads_tried.size(); i++){
        if (which_leads_tried[i] == false){
            return false;
        }
    }
    return true;
}

bool allFollowsTried(){
    for (int i = 0; i < which_follows_tried.size(); i++){
        if (which_follows_tried[i] == false){
            return false;
        }
    }
    return true;
}

void pickFrontCouple(dance* d){
    for (int i = 0; i < NUM_COUPLES_IN_DANCE; i++){
        if (d->couples[i].leader->beenFront == false){
            //  cout << d->couples[i].leader->beenFront << endl;
            d->couples[i].leader->beenFront = true;
            d->couples[i].leader->inFront = true;
            //  cout << "changing " << d->couples[i].leader->name << " to been in Front" << endl;
            //  cout << d->couples[i].leader->beenFront << endl;
            return;
        }
    }
    int seed = rand() % NUM_COUPLES_IN_DANCE;

    //  cout << d->couples[seed].leader->beenFront << endl;
    d->couples[seed].leader->beenFront = true;
    d->couples[seed].leader->inFront = true;
    //  cout << "changing " << d->couples[seed].leader->name << " to been in Front" << endl;
    //  cout << d->couples[seed].leader->beenFront << endl;
    return;


}

int evaluate() {
    vector<lead> lNoGoTwice;
    vector<follow> fNoGoTwice;
    vector<lead> noGoFront;
    for (int i = 0; i < leads.size(); i++){
        if (follows[i].times_danced < 2){
            fNoGoTwice.push_back(follows[i]);
        }
        if (leads[i].times_danced < 2){
            lNoGoTwice.push_back(leads[i]);
        }
        if (leads[i].beenFront == false){
            //debugging
            //cout << leads[i].name << endl << leads[i].beenFront << endl << endl;
            noGoFront.push_back(leads[i]);
        }
    }

    cout << "|||||||||||||| EVALUATION |||||||||||||||" << endl;
    cout << "people not gone twice: " << lNoGoTwice.size() + fNoGoTwice.size() << endl;
    cout << "leads" << endl;
    for (int i = 0; i < lNoGoTwice.size(); i++){
        cout << lNoGoTwice[i].name << ", ";
    }
    cout << endl;
    cout << "follows" << endl;
    for (int i = 0; i < fNoGoTwice.size(); i++){
        cout << fNoGoTwice[i].name << ", ";
    }
    cout << endl;
    cout << "leads not gone in front " << noGoFront.size() << endl;
    for (int i = 0; i < noGoFront.size(); i++){
        cout << noGoFront[i].name << ", ";
    }
    cout << endl;

    return lNoGoTwice.size() + fNoGoTwice.size();
}

void runProgram(){

    int num_rounds = leads.size() * TIMES_TO_DANCE / NUM_COUPLES_IN_DANCE;
    vector<dance> rounds;

    cout << endl << "<---------------------------------------------------------->" << endl;
    for (int i = 0; i < num_rounds; i++){
        cout << "ROUND " << i << endl;
        dance round = dance();
        for (int j = 0; j < NUM_COUPLES_IN_DANCE; j++){
            lead* chosenLead = pickLead();
            follow* chosenFollow = pickFollowForLead(chosenLead);
            chosenLead->follows_danced_with.push_back(chosenFollow->name);
            couple pair = couple(chosenLead, chosenFollow);
            //pair.print();

            round.couples.push_back(pair);
        }
        pickFrontCouple(&round);
        for (int i = 0; i < NUM_COUPLES_IN_DANCE; i++){
            round.couples[i].print();
        }
        rounds.push_back(round);
        resetDancers();
        cout << "---------------------------------------" << endl;
    }

    if (evaluate() != 0){
        runProgram();
    }
}

void resetEverything(){
    resetDancers();
    for (int i = 0; i < leads.size(); i++){
        leads[i].follows_danced_with.clear();
        leads[i].times_danced = 0;
        leads[i].beenFront = false;
        leads[i].just_danced = false;
        leads[i].dancing = false;
        follows[i].times_danced = 0;
        follows[i].just_danced = false;
        follows[i].dancing = false;
    }
}
