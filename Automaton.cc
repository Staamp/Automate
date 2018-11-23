#include "Automaton.h"

#include <cassert>




namespace fa {

    void fa::Automaton::addState(int state){
        if(!hasState(state)) {
            states.insert(state);
        }
    }

    void fa::Automaton::removeState(int state) {
        if(hasState(state)) {
        	for (std::vector<Transition>::iterator it=transitions.begin(); it!=transitions.end(); ++it) {
        		Transition t = *it;
        		if (t.getTo() == state) {
        			removeTransition(t.getFrom(), t.getAlpha(), t.getTo());
        			it--;
        		}
			}
            states.erase(state);
        }
    }

    bool fa::Automaton::hasState(int state) const {
        for (std::set<int>::iterator it=states.begin(); it!=states.end(); ++it) {
            if (*it == state) {
                return true;
            }
        }
        return false;
    }

    size_t fa::Automaton::countStates() const {
        return states.size();
    }


    void fa::Automaton::setStateInitial(int state) {
        if(hasState(state)) {
            initialStates.insert(state);
        }
    }

    void fa::Automaton::unsetStateInitial(int state) {
        if (isStateInitial(state)) {
            initialStates.erase(state);
        }
    }

    bool fa::Automaton::isStateInitial(int state) const {
        for (std::set<int>::iterator it=initialStates.begin(); it!=initialStates.end(); ++it) {
            if (*it == state) {
                return true;
            }
        }
        return false;
    }

    void fa::Automaton::setStateFinal(int state) {
        if(hasState(state)) {
            finalStates.insert(state);
        }
    }

    void fa::Automaton::unsetStateFinal(int state) {
        if (isStateFinal(state)) {
            finalStates.erase(state);
        }
    }

    bool fa::Automaton::isStateFinal(int state) const {
        for (std::set<int>::iterator it=finalStates.begin(); it!=finalStates.end(); ++it) {
            if (*it == state) {
                return true;
            }
        }
        return false;
    }

    fa::Transition::Transition(int from, char alpha, int to) {
        this->from = from;
        this->alpha = alpha;
        this->to = to;
    }

    char fa::Transition::getAlpha() {
        return alpha;
    }

    int fa::Transition::getFrom() {
        return from;
    }

    int fa::Transition::getTo() {
        return to;
    }

    void fa::Automaton::addTransition(int from, char alpha, int to) {
        if (!hasTransition(from, alpha, to) && hasState(from) && hasState(to)) {
            Transition newTransi(from, alpha, to);
            transitions.push_back(newTransi);
            alphabet.insert(alpha);
        }
    }


    bool fa::Automaton::hasTransition(int from, char alpha, int to) {
        if (hasState(from) && hasState(to)) {
            for (std::vector<Transition>::iterator it=transitions.begin(); it!=transitions.end(); ++it) {
                Transition t = *it;
                if(t.getFrom() == from && t.getTo() == to && t.getAlpha() == alpha) {
                    return true;
                }
            }
            return false;
        }
        return false;
    }

    void fa::Automaton::removeTransition(int from, char alpha, int to) {
        if (hasTransition(from, alpha, to)) {
            for (std::vector<Transition>::iterator it=transitions.begin(); it!=transitions.end(); ++it) {
                Transition t = *it;
                if(t.getFrom() == from && t.getTo() == to && t.getAlpha() == alpha) {
                    transitions.erase(it);
                    break;
                }
            }
        }
        return;
    }

    std::size_t fa::Automaton::countTransitions() const {
        return transitions.size();
    }

    std::size_t fa::Automaton::getAlphabetSize() const {
        return alphabet.size();
    }

    std::size_t fa::Automaton::getInitialStateSize() const {
        return initialStates.size();
    }

    std::size_t fa::Automaton::getFinalStateSize() const {
        return finalStates.size();
    }

    void fa::Automaton::prettyPrint(std::ostream& os) const {
        os << std::endl;
        os << "Initial states:" << std::endl;
        os << "\t";
        for (std::set<int>::iterator it1=initialStates.begin(); it1!=initialStates.end(); ++it1) {
            os << " " << *it1;
        }
        os << std::endl;

        os << "Final states:" << std::endl;
        os << "\t";
        for (std::set<int>::iterator it1=finalStates.begin(); it1!=finalStates.end(); ++it1) {
            os << " " << *it1;
        }
        os << std::endl;

        os << "Transitions:" << std::endl;
        for (std::set<int>::iterator it1=states.begin(); it1!=states.end(); ++it1) {
            os << "\tFor state " << *it1 << ":" << std::endl;
            for (std::set<char>::iterator it2=alphabet.begin(); it2!=alphabet.end(); ++it2) {
                os << "\t\tFor letter " << *it2 << ":";
                for (std::vector<Transition>::const_iterator it3=transitions.begin(); it3!=transitions.end(); ++it3) {
                    Transition t = *it3;
                    if(t.getFrom() == *it1 && t.getAlpha() == *it2) {
                        os << " " << t.getTo();
                    }
                }
                os << std::endl;
            }
        }
    }


/*void dotPrint(std::ostream& os) const {

}*/

/***
__________________________________________________________________________________________________
__________________________________________________________________________________________________
__________________________________________________________________________________________________

*/

    bool fa::Automaton::isDeterministic () const {
        if (initialStates.size() != 1) {
            return false;
        }
        if (states.size() < 1) {
            return false;
        }
        for (std::set<int>::iterator it1=states.begin(); it1!=states.end(); ++it1) {
            for (std::set<char>::iterator it2=alphabet.begin(); it2!=alphabet.end(); ++it2) {
                int compteurTransition = 0;
                for (std::vector<Transition>::const_iterator it3=transitions.begin(); it3!=transitions.end(); ++it3) {
                    Transition t = *it3;
                    if(t.getFrom() == *it1 && t.getAlpha() == *it2) {
                        compteurTransition++;
                    }
                }
                if (compteurTransition != 1) {
                    return false;
                }
            }
        }
        return true;
    }

    bool fa::Automaton::isComplete () const {
        return (countStates() * getAlphabetSize() == countTransitions());
    }

    int fa::Automaton::nameStateMax() const {
        int nameMax = 0;
        for (std::set<int>::iterator it=states.begin(); it!=states.end(); ++it) {
            if (nameMax < *it) {
                nameMax = *it;
            }
        }
        return nameMax;
    }



    void fa::Automaton::makeComplete() {
        bool letter = false;
        int nvEtat = nameStateMax() + 1;
        addState(nvEtat);
        for (std::set<int>::iterator it1=states.begin(); it1!=states.end(); ++it1) {
            int state = *it1;
            for (std::set<char>::iterator it2=alphabet.begin(); it2!=alphabet.end(); ++it2) {
                char alpha = *it2;
                letter = false;
                for (std::vector<Transition>::const_iterator it3=transitions.begin(); it3!=transitions.end(); ++it3) {
                    Transition t = *it3;
                    if(t.getFrom() == *it1 && t.getAlpha() == *it2) {
                        letter = true;
                    }
                }
                if (!letter) {
                    addTransition(state, alpha, nvEtat);
                }
            }
        }
    }

    char fa::Automaton::nameLastChar() {
        char last = 0;
        for (std::set<char>::iterator it=alphabet.begin(); it!=alphabet.end(); ++it) {
            last = *it;
        }
        return last;
    }


    void fa::Automaton::makeComplement() {
        if (!isComplete() || !isDeterministic()) {
            return;
        }
        int lastState = nameStateMax();
        char lastChar = nameLastChar();
        int trappe = lastState + 1;
        addState(trappe);
        addTransition(lastState, lastChar, trappe);
        for (std::set<char>::iterator it=alphabet.begin(); it!=alphabet.end(); ++it) {
            addTransition(trappe, *it, trappe);
        }
        
        std::set<int> etat = finalStates;
        finalStates.clear();
        for (std::set<int>::iterator it=states.begin(); it!=states.end(); ++it) {
        	if (!isStateFinal(*it)) {
        		setStateFinal(*it);
        	}
        }
        
        
    }


/***
__________________________________________________________________________________________________
__________________________________________________________________________________________________
__________________________________________________________________________________________________

*/



    void fa::Automaton::DFSUtil(int v, bool visited[]) {
        // Mark the current node as visited and print it
        visited[v] = true;
        //std::cout << "v " << v << " ";

        // Recur for all the vertices adjacent to this vertex
        for (int i = 0; i < v; i++) {
            /*if (i==0) {
                std::cout << std::endl;
            }
            std::cout << "i : " << i << " ";*/
            chemin.push_back(i);
            if (!visited[i]) {
                DFSUtil(i, visited);
            }
        }
    }


    void fa::Automaton::DepthFirstSearch() {
        int NbTransition = countTransitions();
        // Mark all the vertices as not visited
        bool *visited = new bool[NbTransition];
        for (int i = 0; i < NbTransition; i++) {
            visited[i] = false;
        }
        // Call the recursive helper function to print DFS traversal
        // starting from all vertices one by one
        for (int i = 0; i < NbTransition; i++) {
            if (!visited[i]) {
                DFSUtil(i, visited);
            }
        }
    }

    bool fa::Automaton::isLanguageEmpty() const {
        int compteur = 0;
        
        for (std::vector<int>::const_iterator it=chemin.begin(); it!=chemin.end(); ++it) {
            //std::cout << *it << " " << std::endl;
            if (isStateInitial(*it)) {
                compteur = 0;
            }
            if (!isStateInitial(*it)) {
                compteur++;
            }
            if (isStateFinal(*it) && compteur != 0) {
                //std::cout << "Compteur : " << compteur << std::endl;
                return true;
            }
            //std::cout << "Compteur : " << compteur << std::endl;
        }
        return false;
    }

    void fa::Automaton::removeNonAccessibleStates() {
        std::set<int> etat;
        for (std::set<int>::iterator it1=states.begin(); it1!=states.end(); ++it1) {
            bool accessible = false;
            for (std::set<char>::iterator it2=alphabet.begin(); it2!=alphabet.end(); ++it2) {
                for (std::vector<Transition>::const_iterator it3=transitions.begin(); it3!=transitions.end(); ++it3) {
                    Transition t = *it3;
                    if(t.getTo() == *it1 && t.getAlpha() == *it2) {
                        accessible = true;
                    }
                }
            }
            if (!accessible) {
            	etat.insert(*it1);
            }
        }
        for (std::set<int>::iterator it=etat.begin(); it!=etat.end(); ++it) {
            std::cout << "Non accesible : " << *it << std::endl;
            for (std::vector<Transition>::const_iterator it2=transitions.begin(); it2!=transitions.end(); ++it2) {
                Transition t = *it2;
                if (t.getFrom() == *it) {
                    std::cout << "From : " << t.getFrom() << " | Alpha : " << t.getAlpha() << " | To : " << t.getTo() << std::endl;
                    removeTransition(t.getFrom(), t.getAlpha(), t.getTo());
                    --it2;
                }
            }
            removeState(*it);
        }
        
    }

    void fa::Automaton::removeNonCoAccessibleStates() {
        std::set<int> etat;
        for (std::set<int>::iterator it1=states.begin(); it1!=states.end(); ++it1) {
            bool coaccessible = false;
            for (std::set<char>::iterator it2=alphabet.begin(); it2!=alphabet.end(); ++it2) {
                for (std::vector<Transition>::const_iterator it3=transitions.begin(); it3!=transitions.end(); ++it3) {
                    Transition t = *it3;
                    if(t.getFrom() == *it1 && t.getAlpha() == *it2) {
                        coaccessible = true;
                    }
                }
            }
            if (!coaccessible) {
                etat.insert(*it1);
            }
        }
        for (std::set<int>::iterator it=etat.begin(); it!=etat.end(); ++it) {
            std::cout << "Etat non co-accesible : " << *it << std::endl;
            for (std::vector<Transition>::const_iterator it2=transitions.begin(); it2!=transitions.end(); ++it2) {
                Transition t = *it2;
                if (t.getTo() == *it) {
                    std::cout << "From : " << t.getFrom() << " | Alpha : " << t.getAlpha() << " | To : " << t.getTo() << std::endl;
                    removeTransition(t.getFrom(), t.getAlpha(), t.getTo());
                    --it2;
                }
            }
            removeState(*it);
        }
    }

    Automaton fa::Automaton::createProduct (const Automaton lhs, const Automaton rhs) {
        int stateMax = lhs.nameStateMax();
        int newState = stateMax +1;
        //std::cout << "Etat max " << stateMax << std::endl;

        Automaton newAutomaton = lhs;

        for (std::set<int>::iterator it=rhs.states.begin(); it!=rhs.states.end(); ++it) {
            int i = *it + newState;
            //std::cout << "Nv etat " << i << std::endl;
            newAutomaton.addState(i);
            if (rhs.isStateFinal(*it)) {
                //std::cout << "Nv etat " << *it << std::endl;
                newAutomaton.setStateFinal(i);
            }
        }

        for (std::vector<Transition>::const_iterator it_Transit=rhs.transitions.begin(); it_Transit!=rhs.transitions.end(); ++it_Transit) {
            Transition t = *it_Transit;
            //std::cout << "Etat init : From : " << t.getFrom() << " | Alpha : " << t.getAlpha() << " | TO : " << t.getTo() << std::endl;
            //std::cout << "Nv etat : From : " << t.getFrom() + newState << " | Alpha : " << t.getAlpha() << " | TO : " << t.getTo() + newState << std::endl;
            newAutomaton.addTransition(t.getFrom() + newState, t.getAlpha(), t.getTo() + newState);
        }

        for (std::set<int>::iterator it_FinalState=lhs.finalStates.begin(); it_FinalState!=lhs.finalStates.end(); ++it_FinalState){
            for (std::set<int>::iterator it_InitState=rhs.initialStates.begin(); it_InitState!=rhs.initialStates.end(); ++it_InitState) {
                //std::cout << "Etat " << *it_FinalState << std::endl;
                newAutomaton.addTransition(*it_FinalState, ' ', *it_InitState + newState);
                //std::cout << "From : " << *it_FinalState << " | Alpha : E | TO : " << *it_InitState << std::endl;
            }
            newAutomaton.unsetStateFinal(*it_FinalState);
        }

        return newAutomaton;
    }

    bool fa::Automaton::hasEmptyIntersectionWith(const Automaton& other) const {

        return false;
    }

    std::set<int> fa::Automaton::readString(const std::string& word) {
        std::set<int> r = states;
        
        std::cout << word << std::endl;
        
        return states;
    }



    bool fa::Automaton::match(const std::string& word) const {

        return false;
    }

    Automaton fa::Automaton::createDeterministic(const Automaton& automaton) {

        return automaton;
    }

    bool fa::Automaton::isIncluedIn(const Automaton& other) const {

        return false;
    }

    Automaton fa::Automaton::createMinimalMoore(const Automaton& automaton) {

        return automaton;
    }

    Automaton fa::Automaton::createMinimalBrzozowski(const Automaton& automaton) {

        return automaton;
    }

    Automaton fa::Automaton::createMiniamlHopcroft(const Automaton& automaton) {

        return automaton;
    }

    Automaton fa::Automaton::createWithoutEpsilon(const Automaton& automaton) {

        return automaton;
    }

}
