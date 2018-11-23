#ifndef AUTOMATON_H
#define AUTOMATON_H

#include <cstddef>
#include <iostream>
#include <set>
#include <vector>




namespace fa{

    /**
     * Transition est la classe représentant les transitions d'un état à un autre avec un caractère
     * de l'alphabet.
     */
    class Transition{
    public:
        Transition(int source, char alpha, int target);
        bool operator<(const Transition& other) const{
          return false;
        }
        char getAlpha();
        int getFrom();
        int getTo();
    private:
        char alpha;
        int from;
        int to;
    };

    /**
     * Automaton est la classe perméttant la création d'un automate avec des fonctions de
     * manipulation sur ceux-ci.
     */
    class Automaton{
    public:
        void addState(int state);
        void removeState(int state);
        bool hasState(int state) const;
        size_t countStates() const;
        void setStateInitial(int state);
        void unsetStateInitial(int state);
        bool isStateInitial(int state) const;
        void setStateFinal(int state);
        bool isStateFinal(int state) const;
        void unsetStateFinal(int state);
        void addTransition(int from, char alpha, int to);
        void removeTransition(int from, char alpha, int to);
        bool hasTransition(int from, char alpha, int to);
        std::size_t countTransitions() const;
        std::size_t getAlphabetSize() const;
        std::size_t getInitialStateSize() const;
        std::size_t getFinalStateSize() const;
        void prettyPrint(std::ostream& os) const;
        void dotPrint(std::ostream& os) const;
        bool isDeterministic () const;
        bool isComplete () const;
        int nameStateMax() const;
        void makeComplete();
        char nameLastChar();
        void makeComplement();
        void DFSUtil(int v, bool visited[]);
        void DepthFirstSearch();
        bool isLanguageEmpty() const;
        void removeNonAccessibleStates();
        void removeNonCoAccessibleStates();
        static Automaton createProduct(const Automaton lhs, const Automaton rhs);
        bool hasEmptyIntersectionWith(const Automaton& other) const;
        std::set<int> readString(const std::string& word);
        bool match(const std::string& word) const;
        static Automaton createDeterministic(const Automaton& automaton);
        bool isIncluedIn(const Automaton& other) const;
        static Automaton createMinimalMoore(const Automaton& automaton);
        static Automaton createMinimalBrzozowski(const Automaton& automaton);
        static Automaton createMiniamlHopcroft(const Automaton& automaton);
        static Automaton createWithoutEpsilon(const Automaton& automaton);

    private:
        std::set<int> states; // L'ensemble des états de l'automate
        std::set<int> initialStates; // L'ensemble des états initiaux de l'automate
        std::set<int> finalStates; // L'ensemble des états initiaux de l'automate
        std::set<char> alphabet; // Alphabet
        std::vector<Transition> transitions; // L'ensemble des transitions
        std::vector<int> chemin;
    };
}; //namespace fa


#endif // AUTOMATON_H
