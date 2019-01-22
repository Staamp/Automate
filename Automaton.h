#ifndef AUTOMATON_H
#define AUTOMATON_H

#include <cstddef>
#include <cassert>
#include <map>
#include <vector>
#include <set>
#include <iterator>
#include <iostream>
#include <assert.h>

using namespace std;

namespace fa {
    struct state {
        bool Einit;
        bool Efinal;
        bool visited;
    };
    struct transition {
        int from;
        char lettre;
        int to;
    };

    class Automaton {
        public:
        map<int, struct state *> states;
        map<int, struct state *> states_initial;
        map<int, struct state *> states_final;
        std::size_t nombre_etats = 0;
        set<char> alphabet;
        vector<struct transition> transitions;

        std::size_t countStates() const;

        std::size_t countTransitions() const;

        void addState(int state);

        void removeState(int state);

        bool hasState(int state) const;

        void setStateInitial(int state);

        bool isStateInitial(int state) const;

        void setStateFinal(int state);

        void unsetStateFinal(int state);

        void unsetStateInitial(int state);

        bool isStateFinal(int state) const;

        void addTransition(int from, char alpha, int to);

        bool hasAlphabet(char alpha);

        void removeTransition(int from, char alpha, int to);

        bool hasTransition(int from, char alpha, int to) const;

        std::size_t countTransitions();

        std::size_t getAlphabetSize() const;

        void prettyPrint(std::ostream &os) const;

        bool isDeterministic() const;

        bool isComplete() const;

        void makeComplete();

        void makeComplement();

        bool isLanguageEmpty() const;

        void removeNonAccessibleStates();

        void removeNonCoAccessibleStates();

        void DepthFirstSearch(int state, map<int, bool> *isVisited) const;

        void InverseDepthFirstSearch(int state, map<int, bool> *isVisited) const;

        int EtatMaximum() const;

        static Automaton createProduct(const Automaton &lhs, const Automaton &rhs);

        void PrettyDot();

        bool saveImageGV(std::string file_path);

        bool hasEmptyIntersectionWith(const Automaton& other) const;

        static Automaton createDeterministic(const Automaton& automaton);

        std::set<int> readString(const std::string& word)const;

        void Lecture(int state,std::set<int> *isVisited,const std::string &word,size_t position)const;

        bool match(const std::string & word)const;

        void LectureMatch(const Automaton &automaton,int state,bool *res,const std::string &word,size_t position)const;

        static Automaton createWithoutEpsilon(const Automaton &automaton);

        static std::vector<struct transition> SearchTransition(int Etat,const Automaton &automaton,map <int,bool> *isVisited);

        static bool SearchFinal(int Etat,const Automaton &automaton);

        static bool SearchInitial(int Etat,const Automaton &automaton);

        bool isIncludedIn(const Automaton &other)const;

        static Automaton createMinimalMoore (const Automaton &automaton);
    };

} // namespace fa

#endif // AUTOMATON_H
