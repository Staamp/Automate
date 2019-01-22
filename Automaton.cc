//TRAVAIL EN BINOME : PONCOT Cédric - COURVOISIER Nicolas

#include "Automaton.h"

namespace fa {
    void Automaton::addState(int state){
            assert(!hasState(state));
            struct state *current= (struct state*)std::malloc(sizeof(struct state));
            current->Einit=false;
            current->Efinal=false;
            current->visited=false;
            Automaton::states[state]=current;
            nombre_etats++;
    }

    std::size_t Automaton::countTransitions()const{
        return transitions.size();
    }


    void Automaton::removeState(int state){
        assert(hasState(state));
        //On supprime les transitions associÃ©es Ã  l'Ã©tat numÃ©ro state.
        for(std::vector<struct transition>::iterator it=transitions.begin(); it != transitions.end(); ++it){
            if(it->from==state or it->to==state){
                transitions.erase(it);
                it--;
            }
        }
        //On supprime enfin l'Ã©tat.
        for(std::map<int,struct state*>::iterator it=states.begin(); it != states.end(); ++it){
            if(it->first==state){
                states.erase(it);
                nombre_etats--;
                break;
            }
        }
        //Et si il est prÃ©sent dans les Ã©tats initiaux
        for(std::map<int,struct state*>::iterator it=states_initial.begin(); it != states_initial.end(); ++it){
            if(it->first==state){
                states_initial.erase(it);
                break;
            }
        }
        //Et si il est prÃ©sent dans les Ã©tats finaux
        for(std::map<int,struct state*>::iterator it=states_final.begin(); it != states_final.end(); ++it){
            if(it->first==state){
                states_final.erase(it);
                return;
            }
        }
    }
    bool Automaton::hasState(int state) const{
        return states.count(state)==1;
    }
    std::size_t Automaton::countStates() const{
        return nombre_etats;
    }
    void Automaton::setStateInitial (int state){
        assert(hasState(state));
        states[state]->Einit = true;
        states_initial[state] = states[state];
        
    }

    bool Automaton::isStateInitial (int state) const{
        assert(hasState(state));
        return states.at(state)->Einit;
    }

    void Automaton::setStateFinal (int state){
        assert(hasState(state));
        states[state]->Efinal = true;
        states_final[state] = states[state];
    }

    void Automaton::unsetStateFinal (int state){
        states[state]->Efinal=false;
        states_final.erase(state);
    }

    void Automaton::unsetStateInitial (int state){
        states[state]->Einit=false;
        states_initial.erase(state);
    }

    //ComplexitÃ©: O(log n)
    bool Automaton::isStateFinal (int state) const{
        assert(hasState(state));
        return states.at(state)->Efinal;
    }

    //ComplexitÃ©: O(n+m)
    void Automaton::addTransition(int from, char alpha, int to){
        assert(hasState(from) && hasState(to));
        //On prend garde de ne pas pouvoir ajouter 2 fois la même transition et que les états existent.
        if(hasState(from)&&hasState(to)&&!hasTransition(from,alpha,to)){
            //On ajoute la lettre dans  notre alphabet si elle n'est pas dÃ©jÃ  prÃ©sente dedans.
            alphabet.insert(alpha);
            //On ajoute la transition dans notre tableau dynamique transitions
            struct transition *current= (struct transition*)std::malloc(sizeof(struct transition));
            current->from=from;
            current->lettre=alpha;
            current->to=to;
            transitions.push_back(*current);
        }
    }

    bool Automaton::hasAlphabet(char alpha){
        for(std::set<char>::iterator it=alphabet.begin(); it != alphabet.end(); ++it){
            if(*it==alpha)return true;
        }
        return false;
    }

    //ComplexitÃ© O(n+m)
    void Automaton::removeTransition(int from,char alpha,int to){
        assert(hasTransition(from, alpha, to));
        for(std::vector<struct transition>::iterator it=transitions.begin(); it != transitions.end(); ++it){
            if(it->from==from && it->to==to && it->lettre==alpha){
                transitions.erase(it);
                //DÃ¨s que la transition est supprimÃ©e, on peut stopper la fonction.
                return;
            }
        }
    }

    //ComplexitÃ© O(n+m)
    bool Automaton::hasTransition (int from, char alpha, int to) const{
        assert(hasState(from) && hasState(to));
        for(std::vector<struct transition>::const_iterator it=transitions.begin(); it != transitions.end(); ++it){
            if(it->from==from && it->to==to && it->lettre==alpha){
                return true;
            }
        }
        return false;
    }

    //ComplexitÃ© O(n+m)
    std::size_t Automaton::countTransitions(){
        return transitions.size();
    }

    //ComplexitÃ© O(1)
    std::size_t Automaton::getAlphabetSize() const{
        return alphabet.size();
    }


    void Automaton::prettyPrint(std::ostream& os) const{
        cout<<"Initial states:\n\t";
        //On recherche les Ã©tats initiaux
        for(std::map<int,struct state*>::const_iterator it=states.begin(); it != states.end(); ++it){
            if(it->second->Einit){
                os<<it->first<<" ";
            }
        }
        os<<"\nFinal states:\n\t";
        //On recherche les Ã©tats finaux
        for(std::map<int,struct state*>::const_iterator it=states.begin(); it != states.end(); ++it){
            if(it->second->Efinal){
                os<<it->first<<" ";
            }
        }
        os<<"\nTransitions:\n";
        //Pour chaque Ã©tat de dÃ©part, puis pour chaque lettre, on regarde si il y a une transition associÃ©e.
        for(std::map<int,struct state*>::const_iterator it=states.begin(); it != states.end(); ++it){
            os<< "\n\tFor state "<<it->first<<" :";
            for(std::set<char>::const_iterator it3=alphabet.begin(); it3!=alphabet.end();++it3){
                os<< "\n\t\t For letter " << *it3<<" : ";
                for(std::vector<struct transition>::const_iterator it2=transitions.begin(); it2 != transitions.end(); ++it2){
                    if(it2->from==it->first && it2->lettre==*it3){
                        os<< it2->to<<" ";
                    }
                }
            }
        }
        cout<<"\n";
    }


    //ComplexitÃ© : O(n*m*s)
    bool Automaton::isDeterministic() const{
        //On vÃ©rifie qu'il n'y a qu'un unique Ã©tat initial.
        std::size_t compteur=0;
        for(std::map<int,struct state*>::const_iterator it=states.begin(); it != states.end(); ++it){
            if(isStateInitial(it->first)){
                ++compteur;
                if(compteur>=2){
                    return false;
                }
            }
        }
        if(compteur==0){return false;}
        //On vÃ©rifie que toutes les transitions n'ont qu'un Ã©tat retour pour un Ã©tat et une lettre donnÃ©e.
        for(std::map<int,struct state*>::const_iterator it=states.begin(); it != states.end(); ++it){
            for(std::set<char>::const_iterator it3=alphabet.begin(); it3!=alphabet.end();++it3){
                compteur=0;
                for(std::vector<struct transition>::const_iterator it2=transitions.begin(); it2 != transitions.end(); ++it2){
                    if(it2->from==it->first && it2->lettre==*it3){
                        ++compteur;
                        if(compteur>=2){
                            return false;
                        }
                    }
                }
            }
        }
        return true;
    }

    //ComplexitÃ©: O(n*m*s)
    bool Automaton::isComplete() const{
        std::size_t compteur;
        //On vÃ©rifie que toutes les transitions ont au moins un Ã©tat retour.
        for(std::map<int,struct state*>::const_iterator it=states.begin(); it != states.end(); ++it){
            for(std::set<char>::const_iterator it3=alphabet.begin(); it3!=alphabet.end();++it3){
                compteur=0;
                for(std::vector<struct transition>::const_iterator it2=transitions.begin(); it2 != transitions.end(); ++it2){
                    if(it2->from==it->first && it2->lettre==*it3){
                        ++compteur;
                    }
                }
                if(compteur==0){
                    return false;
                }
            }
        }
        return true;
    }

    //O(m*n*s)
    void Automaton::makeComplete(){
        if(!isComplete()) {
            std::size_t compteur;
            //On crÃ©Ã© un Ã©tat poubelle
            int max = EtatMaximum();
            addState(max);
            //On le relie à tous les états par les transitions necessaire
            for (std::map<int, struct state *>::iterator it = states.begin(); it != states.end(); ++it) {
                for (std::set<char>::iterator it3 = alphabet.begin(); it3 != alphabet.end(); ++it3) {
                    compteur = 0;
                    for (std::vector<struct transition>::iterator it2 = transitions.begin();
                         it2 != transitions.end(); ++it2) {
                        if (it2->from == it->first && it2->lettre == *it3) {
                            ++compteur;
                        }
                    }
                    if (compteur == 0) {
                        addTransition(it->first, *it3, max);
                    }
                }
            }
        }
    }

    //O(n*m*s)
    void Automaton::makeComplement(){
        assert(isComplete() && isDeterministic());
		for(std::map<int,struct state*>::iterator it=states.begin(); it != states.end(); ++it){               
			if(!isStateFinal(it->first))setStateFinal(it->first);
			else{unsetStateFinal(it->first);}
		}
    }

    //O(n)
    bool Automaton::isLanguageEmpty() const{
        //tableau associatif qui nous permet de savoir si un Ã©tat est visitÃ© ou non.
        map <int,bool> isVisited;
        //On initialise ce tableau.
        for(std::map<int,struct state*>::const_iterator it=states.begin(); it != states.end(); ++it){
            isVisited[it->first]=false;
        }
        //On rÃ©cupÃ¨re les Ã©tats initiaux et on lance la recherche en profondeur.
        for(std::map<int,struct state*>::const_iterator it=states.begin(); it != states.end(); ++it){
            if(it->second->Einit){
                DepthFirstSearch(it->first,&isVisited);
            }
        }
        for(std::map<int,struct state*>::const_iterator it=states.begin(); it != states.end(); ++it){
            if(it->second->Efinal&&isVisited[it->first]){
                return false;
            }
        }
        return true;
    }

    //O(n)
    void Automaton::removeNonAccessibleStates (){
        //tableau associatif qui nous permet de savoir si un Ã©tat est visitÃ© ou non.
        map <int,bool> isVisited;
        //On initialise ce tableau.
        for(std::map<int,struct state*>::iterator it=states.begin(); it != states.end(); ++it){
            isVisited[it->first]=false;
        }
        //On rÃ©cupÃ¨re les Ã©tats initiaux et on lance la recherche en profondeur.
        for(std::map<int,struct state*>::iterator it=states_initial.begin(); it != states_initial.end(); ++it){
            DepthFirstSearch(it->first,&isVisited);
        }
        //On supprime les Ã©tats non visitÃ©s.
        for(std::map<int,bool>::iterator it=isVisited.begin(); it != isVisited.end(); ++it){
            if(!it->second){
                removeState(it->first);
            }
        }
    }

    //O(n)
    void Automaton::removeNonCoAccessibleStates (){
        //tableau associatif qui nous permet de savoir si un Ã©tat est visitÃ© ou non.
        map <int,bool> isVisited;
        //On initialise ce tableau.
        for(std::map<int,struct state*>::iterator it=states.begin(); it != states.end(); ++it){
            isVisited[it->first]=false;
        }
        //On rÃ©cupÃ¨re les Ã©tats finaux et on lance la recherche en profondeur inversÃ©e.
        for(std::map<int,struct state*>::iterator it=states_final.begin(); it != states_final.end(); ++it){
            InverseDepthFirstSearch(it->first,&isVisited);
        }
        //On supprime les Ã©tats non visitÃ©s
        for(std::map<int,bool>::iterator it=isVisited.begin(); it != isVisited.end(); ++it){
            if(!it->second){
                removeState(it->first);
            }
        }
    }
    void Automaton::DepthFirstSearch(int state,map <int,bool> *isVisited)const{
        (*isVisited)[state]=true;
        for(std::vector<struct transition>::const_iterator it=transitions.begin(); it != transitions.end(); ++it){
            if(it->from==state){
                if(!(*isVisited)[it->to]){
                    DepthFirstSearch(it->to,isVisited);
                }
            }

        }
    }
    void Automaton::InverseDepthFirstSearch(int state,map <int,bool> *isVisited)const{
        (*isVisited)[state]=true;
        for(std::vector<struct transition>::const_iterator it=transitions.begin(); it != transitions.end(); ++it){
            if(it->to==state){
                if(!(*isVisited)[it->from]){
                    InverseDepthFirstSearch(it->from,isVisited);
                }
            }

        }
    }

    //Fonction qui renvoie le numÃ©ro d'Ã©tat max d'un automate (renvoie 0 si automate vide)
    int Automaton::EtatMaximum()const{
        int max=-1000;
        for(std::map<int,struct state*>::const_iterator it=states.begin(); it!=states.end(); ++it){
            if(it->first>max){
                max=it->first;
            }
        }
        return max+1;
    }

    Automaton Automaton::createProduct(const Automaton& lhs ,const Automaton& rhs){
        //On déterminise le membre de droite et de gauche
        fa::Automaton ls,rs;
        if(!lhs.isDeterministic()){
            ls=ls.createDeterministic(lhs);
        }
        else{
            ls=lhs;
        }
        if(!rhs.isDeterministic()){
            rs=rs.createDeterministic(rhs);

        }
        else{
            rs=rhs;
        }
        fa::Automaton fa;
        if(rs.countStates()==0||ls.countStates()==0){
            return fa;
        }
        std::vector<set<int>> aFaire;
        std::vector<set<int>> Connu;
        std::set<char> produit_alphabet;
        int EtatMax=+ls.EtatMaximum();

        //----------------On récupère l'alphabet--------------------------

        for(std::set<char>::const_iterator it=ls.alphabet.begin(); it!=ls.alphabet.end();++it){
            produit_alphabet.insert(*it);
        }
        for(std::set<char>::const_iterator it=rs.alphabet.begin(); it!=rs.alphabet.end();++it){
            produit_alphabet.insert(*it);
        }

        //------------------On a notre ensemble d'états initiaux-------------------

        std::set<int> etat_init;


        //On copie les Ã©tats initiaux du membre de gauche
        for(std::map<int,struct state*>::const_iterator it=ls.states_initial.begin(); it != ls.states_initial.end(); ++it){
            int etat_initial_gauche=it->first;
            etat_init.insert(etat_initial_gauche);
        }
        //On copie les Ã©tats initiaux du membre de droite
        for(std::map<int,struct state*>::const_iterator it=rs.states_initial.begin(); it != rs.states_initial.end(); ++it){
            int etat_initial_droit=it->first+EtatMax;
            etat_init.insert(etat_initial_droit);
        }
        Connu.push_back(etat_init);
        aFaire.push_back(etat_init);
        int num_etat=-1;


        //On teste si l'état initial est final
        bool isFinalgauche=false;
        bool isFinaldroit=false;
        for(std::set<int>::const_iterator it_state=etat_init.begin();it_state!=etat_init.end();++it_state){
            for(std::map<int,struct state*>::const_iterator it=ls.states_final.begin(); it != ls.states_final.end(); ++it){
                int etat_final_gauche=it->first;
                if(*it_state==etat_final_gauche){                        
                    isFinalgauche=true;
                }
            }
            for(std::map<int,struct state*>::const_iterator it=rs.states_final.begin(); it != rs.states_final.end(); ++it){
                int etat_final_droit=it->first+EtatMax;
                if(*it_state==etat_final_droit){
                       isFinaldroit=true;
                }
            }
        }
        if(isFinalgauche&isFinaldroit){
            if(fa.hasState(0)){
                fa.setStateFinal(0);
            }
        }
        //Tant qu'il reste des lignes a faire, on applique l'algo
        while(!aFaire.empty()){
            num_etat++;
            set<int> ensemble=aFaire.back();
            aFaire.pop_back();
            if(!fa.hasState(num_etat)){
                fa.addState(num_etat);
            }
            fa.setStateInitial(0);
            for(std::set<char>::const_iterator it=produit_alphabet.begin(); it!=produit_alphabet.end();++it){
                set<int> ensemble_arrivee;
                bool exist_transit=false;
                for(std::vector<struct transition>::const_iterator it2=ls.transitions.begin(); it2 != ls.transitions.end(); ++it2){
                    for(std::set<int>::const_iterator it3=ensemble.begin(); it3!=ensemble.end();++it3){
                        if(it2->from==*it3 && it2->lettre==*it){
                            ensemble_arrivee.insert(it2->to);
                            exist_transit=true;
                        }
                    }
                }
                for(std::vector<struct transition>::const_iterator it2=rs.transitions.begin(); it2 != rs.transitions.end(); ++it2){
                    for(std::set<int>::const_iterator it3=ensemble.begin(); it3!=ensemble.end();++it3){
                        if(it2->from+EtatMax==*it3 && it2->lettre==*it){  
                            ensemble_arrivee.insert(it2->to+EtatMax);
                            exist_transit=exist_transit&true;
                        }
                    }
                }
                if(!ensemble_arrivee.empty()&&exist_transit){
                    
                
            bool ensemble_existant=false;
            int numero_ensemble_arrive=0;

            bool isFinalgauche=false;
            bool isFinaldroit=false;
            for(std::set<int>::const_iterator it_state=ensemble_arrivee.begin();it_state!=ensemble_arrivee.end();++it_state){
                for(std::map<int,struct state*>::const_iterator it=ls.states_final.begin(); it != ls.states_final.end(); ++it){
                    int etat_final_gauche=it->first;
                    if(*it_state==etat_final_gauche){
                        isFinalgauche=true;
                    }
                }
                for(std::map<int,struct state*>::const_iterator it=rs.states_final.begin(); it != rs.states_final.end(); ++it){
                    int etat_final_droit=it->first+EtatMax;
                    if(*it_state==etat_final_droit){
                        isFinaldroit=true;
                    }
                }
            }
            bool isFinal=isFinalgauche&isFinaldroit;
            //On regarde si l'état doit être initial
            bool isInitialgauche=false;
            bool isInitialdroit=false;
            for(std::set<int>::const_iterator it_state=ensemble_arrivee.begin();it_state!=ensemble_arrivee.end();++it_state){
                for(std::map<int,struct state*>::const_iterator it=ls.states_initial.begin(); it != ls.states_initial.end(); ++it){
                    int etat_final_gauche=it->first;
                    if(*it_state==etat_final_gauche){
                        isInitialgauche=true;
                    }
                }
                for(std::map<int,struct state*>::const_iterator it=rs.states_initial.begin(); it != rs.states_initial.end(); ++it){
                    int etat_final_droit=it->first+EtatMax;
                    if(*it_state==etat_final_droit){
                        isInitialdroit=true;
                    }
                }
            }
            bool isInitial=isInitialdroit&isInitialgauche;
            for(std::vector<set<int>>::const_iterator it=Connu.begin(); it != Connu.end(); ++it){
                if(ensemble_arrivee==*it){
                    ensemble_existant=true;
                    break;
                }
                numero_ensemble_arrive++;
            }
            if(!fa.hasState(numero_ensemble_arrive)){
                fa.addState(numero_ensemble_arrive);
            }
            
            if(isFinal&&fa.hasState(numero_ensemble_arrive)){
                fa.setStateFinal(numero_ensemble_arrive);
            }
            if(isInitial&&fa.hasState(numero_ensemble_arrive)){
                fa.setStateInitial(numero_ensemble_arrive);
            }
            fa.addTransition(num_etat,*it,numero_ensemble_arrive);
            if(!ensemble_existant){
                Connu.push_back(ensemble_arrivee); 
                aFaire.insert(aFaire.begin(),ensemble_arrivee);
            }
            }
            }
            
        }
         return fa;
     }

    Automaton Automaton::createDeterministic(const Automaton& automaton){
        fa::Automaton fa;
        std::vector<set<int>> aFaire;
        std::vector<set<int>> Connu;

        //------------------On a notre ensemble d'états initiaux-------------------

        std::set<int> etat_init;    

        for(std::map<int,struct state*>::const_iterator it=automaton.states_initial.begin(); it != automaton.states_initial.end(); ++it){
            int etat_initial=it->first;
            etat_init.insert(etat_initial);
        }

        Connu.push_back(etat_init);
        if(etat_init.size()!=0){
            aFaire.push_back(etat_init);
        }
        int num_etat=-1;


        //On teste si l'état initial est final
        bool isFinal=false;
        for(std::set<int>::const_iterator it_state=etat_init.begin();it_state!=etat_init.end();++it_state){
            for(std::map<int,struct state*>::const_iterator it=automaton.states_final.begin(); it != automaton.states_final.end(); ++it){
                int etat_final_gauche=it->first;
                if(*it_state==etat_final_gauche){                        
                    isFinal=true;
                }
            }
        }
        if(isFinal){
            fa.setStateFinal(0);
        }
        //tant qu'il reste des lignes de tableaux à faire, on applique l'algorithme
        while(!aFaire.empty()){
            num_etat++;
            set<int> ensemble=aFaire.back();
            aFaire.pop_back();
            if(!fa.hasState(num_etat)){
                fa.addState(num_etat);
            }
            fa.setStateInitial(0);
            for(std::set<char>::const_iterator it=automaton.alphabet.begin(); it!=automaton.alphabet.end();++it){
                set<int> ensemble_arrivee;
                for(std::vector<struct transition>::const_iterator it2=automaton.transitions.begin(); it2 != automaton.transitions.end(); ++it2){
                    for(std::set<int>::const_iterator it3=ensemble.begin(); it3!=ensemble.end();++it3){
                        if(it2->from==*it3 && it2->lettre==*it){
                            ensemble_arrivee.insert(it2->to);
                        }
                    }
                }
                if(!ensemble_arrivee.empty()){
            bool ensemble_existant=false;
            int numero_ensemble_arrive=0;
            bool isFinal=false;
            for(std::set<int>::const_iterator it_state=ensemble_arrivee.begin();it_state!=ensemble_arrivee.end();++it_state){
                for(std::map<int,struct state*>::const_iterator it=automaton.states_final.begin(); it != automaton.states_final.end(); ++it){
                    int etat_final_gauche=it->first;
                    if(*it_state==etat_final_gauche){
                        isFinal=true;
                    }
                }
            }
            for(std::vector<set<int>>::const_iterator it=Connu.begin(); it != Connu.end(); ++it){
                if(ensemble_arrivee==*it){
                    ensemble_existant=true;
                    break;
                }
                numero_ensemble_arrive++;
            }
            //On ajoute l'état si il n'existe pas déjà
            if(!fa.hasState(numero_ensemble_arrive)){
                fa.addState(numero_ensemble_arrive);
            }
            
            if(isFinal){
                fa.setStateFinal(numero_ensemble_arrive);
            }
            //On ajoute la transition correspondante
            fa.addTransition(num_etat,*it,numero_ensemble_arrive);
            if(!ensemble_existant){
                Connu.push_back(ensemble_arrivee);
                aFaire.insert(aFaire.begin(),ensemble_arrivee);
            }
        }
        }    
        }
        return fa;
     }


    std::set<int> Automaton::readString(const std::string &word)const{
        std::set<int> resultat;
        for(std::map<int,struct state*>::const_iterator it=states_initial.begin(); it != states_initial.end(); ++it){
            Lecture(it->first,&resultat,word,0);
        }
        return resultat;
     }

    //fonction avec argument accumulateur qui lit un mot à partir d'une position.
    void Automaton::Lecture(int state,std::set<int> *isVisited,const std::string &word,size_t position)const{
        (*isVisited).insert(state);
        if(position<word.length()){
            char lettreALire=word.at(position);
            for(std::vector<struct transition>::const_iterator it=transitions.begin(); it != transitions.end(); ++it){
                if(it->from==state && it->lettre==lettreALire){
                    
                    Lecture(it->to,isVisited,word,position+1);
                    
                }
            }
        }
    }


    bool Automaton::match(const std::string & word)const{
        fa::Automaton current;
        for(std::map<int,struct state*>::const_iterator it=states.begin(); it !=states.end(); ++it){
            current.addState(it->first);
            if(isStateInitial(it->first)){
                current.setStateInitial(it->first);
            }
            if(isStateFinal(it->first)){
                current.setStateFinal(it->first);
            }
        }
        for(std::vector<struct transition>::const_iterator it=transitions.begin(); it !=transitions.end(); ++it){
            current.addTransition(it->from,it->lettre,it->to);
        }
        if(!isDeterministic()){
            current=current.createDeterministic(current);
        }
        
        bool resultat=false;
        for(std::map<int,struct state*>::const_iterator it=current.states_initial.begin(); it != current.states_initial.end(); ++it){
            LectureMatch(current,it->first,&resultat,word,0);
        }
        return resultat;
    }

    void Automaton::LectureMatch(const Automaton &automaton,int state,bool *res,const std::string &word,size_t position)const{
        if(automaton.isStateFinal(state)&&position==word.length()){
            *res=true;
        }
        if(position<word.length() && !(*res)){
            char lettreALire=word.at(position);
            for(std::vector<struct transition>::const_iterator it=automaton.transitions.begin(); it != automaton.transitions.end(); ++it){
                if(it->from==state && it->lettre==lettreALire){
                    LectureMatch(automaton,it->to,res,word,position+1);
                }

            }
        }
    }


    Automaton Automaton::createWithoutEpsilon(const Automaton &automaton){
        fa::Automaton res;
        for(std::map<int,struct state*>::const_iterator it=automaton.states.begin(); it != automaton.states.end(); ++it){
            res.addState(it->first);
            if(automaton.isStateInitial(it->first)){
                res.setStateInitial(it->first);
            }
            if(automaton.isStateFinal(it->first)||fa::Automaton::SearchFinal(it->first,automaton)){
                res.setStateFinal(it->first);
            }
        }
        for(std::vector<struct transition>::const_iterator it=automaton.transitions.begin(); it != automaton.transitions.end(); ++it){
            if(it->lettre!=0){
                res.addTransition(it->from,it->lettre,it->to);
            }
            else{
                //l'état visité permet de ne pas tourner en rond si l'on a une boucle d'épsilon transition
                map <int,bool> isVisited;
                isVisited[it->from]=true;
                std::vector<struct transition> aAjouter=fa::Automaton::SearchTransition(it->to,automaton,&isVisited);
                for(std::vector<struct transition>::const_iterator it2=aAjouter.begin(); it2 !=aAjouter.end(); ++it2){
                
                    res.addTransition(it->from,it2->lettre,it2->to);
                }
            }
        }
        return res;
    }
    //determine si un etat est final apres la suppression des epsilons transitions
    bool Automaton::SearchFinal(int Etat,const Automaton &automaton){
        bool res=false;
        for(std::vector<struct transition>::const_iterator it=automaton.transitions.begin(); it != automaton.transitions.end(); ++it){
            if(it->from==Etat&&it->lettre==0){
                if(automaton.isStateFinal(it->to)){
                    res=true;
                }
                else{
                    res=SearchFinal(it->to,automaton);
                }
            }
        }
        return res;
    }
    /*
    bool Automaton::SearchInitial(int Etat,const Automaton &automaton){
        bool res=false;
        for(std::vector<struct transition>::const_iterator it=automaton.transitions.begin(); it != automaton.transitions.end(); ++it){
            if(it->from==Etat&&it->lettre==0){
                if(automaton.isStateInitial(it->to)){
                    res=true;
                }
                else{
                    res=SearchInitial(it->to,automaton);
                }
            }
        }
        return res;
    }*/

    std::vector<struct transition> Automaton::SearchTransition(int Etat,const Automaton &automaton,map <int,bool> *isVisited){
        std::vector<struct transition> res;
        if((*isVisited)[Etat]){
            return res;
        }
        (*isVisited)[Etat]=true;
        for(std::vector<struct transition>::const_iterator it=automaton.transitions.begin(); it != automaton.transitions.end(); ++it){
            if(it->from==Etat){
                if(it->lettre!=0){
                    res.push_back(*it);
                }
                else{
                    std::vector<struct transition> Aconcatener=SearchTransition(it->to,automaton,isVisited);
                    res.insert(res.end(),Aconcatener.begin(),Aconcatener.end());
                }
            }
        }
        return res;
    }
    
    bool Automaton::hasEmptyIntersectionWith(const Automaton &other) const{
        fa::Automaton current;
        for(std::map<int,struct state*>::const_iterator it=states.begin(); it !=states.end(); ++it){
            current.addState(it->first);
            if(isStateInitial(it->first)){
                current.setStateInitial(it->first);
            }
            if(isStateFinal(it->first)){
                current.setStateFinal(it->first);
            }
        }
        for(std::vector<struct transition>::const_iterator it=transitions.begin(); it !=transitions.end(); ++it){
            current.addTransition(it->from,it->lettre,it->to);
        }
        fa::Automaton product=createProduct(current,other);
        return product.isLanguageEmpty();
     }
    
    bool Automaton::isIncludedIn (const Automaton &other) const{
        fa::Automaton current;
        for(std::map<int,struct state*>::const_iterator it=other.states.begin(); it !=other.states.end(); ++it){
            current.addState(it->first);
            if(other.isStateInitial(it->first)){
                current.setStateInitial(it->first);
            }
            if(other.isStateFinal(it->first)){
                current.setStateInitial(it->first);
            }
        }
        for(std::vector<struct transition>::const_iterator it=other.transitions.begin(); it !=other.transitions.end(); ++it){
            current.addTransition(it->from,it->lettre,it->to);
        }
        current.makeComplement();
        return hasEmptyIntersectionWith(current);
    }
    
    Automaton Automaton::createMinimalMoore (const Automaton &automaton){
        fa::Automaton res,automatonOK;
        //L'automate automatonOK est l'automate associé a automaton en déterministe et complet.
        if(!automaton.isDeterministic())automatonOK=automatonOK.createDeterministic(automaton);
        else{
            for(std::map<int,struct state*>::const_iterator it=automaton.states.begin(); it !=automaton.states.end(); ++it){
                automatonOK.addState(it->first);
                if(automaton.isStateInitial(it->first)){
                   automatonOK.setStateInitial(it->first);
                }
                if(automaton.isStateFinal(it->first)){
                    automatonOK.setStateFinal(it->first);
                }
            }
            for(std::vector<struct transition>::const_iterator it=automaton.transitions.begin(); it !=automaton.transitions.end(); ++it){
                automatonOK.addTransition(it->from,it->lettre,it->to);
            }
        }
        if(!automatonOK.isComplete()){
            automatonOK.makeComplete();
        }
        //On fait la premiere congruence
        std::vector<std::vector<int>> congruence_prev;
        std::vector<std::vector<int>> congruence;
        std::vector<int> ligne_depart;
        for(std::map<int,struct state*>::const_iterator it=automatonOK.states.begin(); it!=automatonOK.states.end(); ++it){
            if(automatonOK.isStateFinal(it->first)){
                ligne_depart.push_back(2);
            }
            else{
                ligne_depart.push_back(1);
            }
        }
        congruence.push_back(ligne_depart);
        for(std::set<char>::const_iterator it=automatonOK.alphabet.begin(); it!=automatonOK.alphabet.end();++it){
            std::vector<int> ligne_courante;
            int etat_numero=0;
            for(std::map<int,struct state*>::const_iterator it2=automatonOK.states.begin(); it2 !=automatonOK.states.end(); ++it2){
                for(std::vector<struct transition>::const_iterator it3=automatonOK.transitions.begin(); it3 !=automatonOK.transitions.end(); ++it3){
                    if(it3->from==it2->first&&it3->lettre==*it){
                        int nombreArentrer=ligne_depart.at(it3->to);
                        ligne_courante.push_back(nombreArentrer);
                    }
                }
            etat_numero++;
            }
            congruence.push_back(ligne_courante);
        }
        //On applique la n+1 eme congruence tant qu'elle n'est pas égale à la n ème
        
        do{
            congruence_prev.clear();
            for(std::vector<std::vector<int>>::const_iterator it=congruence.begin(); it!=congruence.end(); ++it){
                std::vector<int> ligne=*it;
                congruence_prev.push_back(ligne);
            }
            congruence.clear();
            std::vector<int> premiere_ligne;
            std::vector<std::vector<int>> ensemble_colonnes;
            
            int numero_colonne=0;
            int state=0;
            for(std::map<int,struct state*>::const_iterator it2=automatonOK.states.begin(); it2 !=automatonOK.states.end(); ++it2){
                std::vector<int> colonne;
                for(size_t num_ligne=0;num_ligne<automatonOK.getAlphabetSize()+1;num_ligne++){
                    colonne.push_back(congruence_prev.at(num_ligne).at(numero_colonne));
                }
                int position=0;
                bool contain=false;
                for(std::vector<std::vector<int>>::const_iterator it3=ensemble_colonnes.begin(); it3 !=ensemble_colonnes.end(); ++it3){
                    position++;
                    if(*it3==colonne){
                        contain=true;
                        break;
                    }
                }
                
                if(!contain){
                    ensemble_colonnes.push_back(colonne);
                    state++;
                    premiere_ligne.push_back(state);
                }
                else{
                    premiere_ligne.push_back(position);
                }
                numero_colonne++;
            }
            congruence.push_back(premiere_ligne);
            //On fabrique l'automate à partir de la dernière congruence
            for(std::set<char>::const_iterator it=automatonOK.alphabet.begin(); it!=automatonOK.alphabet.end();++it){
                std::vector<int> ligne_courante;
                int etat_numero=0;
                for(std::map<int,struct state*>::const_iterator it2=automatonOK.states.begin(); it2 !=automatonOK.states.end(); ++it2){
                    for(std::vector<struct transition>::const_iterator it3=automatonOK.transitions.begin(); it3 !=automatonOK.transitions.end(); ++it3){
                        if(it3->from==it2->first&&it3->lettre==*it){
                            int nombreArentrer=premiere_ligne.at(it3->to);
                            ligne_courante.push_back(nombreArentrer);
                        }
                    }
                etat_numero++;
                }
                congruence.push_back(ligne_courante);
            }
        }while(congruence!=congruence_prev);
        std::vector<int> EetatAcreer=congruence.at(0);
        for(std::vector<int>::const_iterator it=EetatAcreer.begin(); it!=EetatAcreer.end();it++){
            int etatAcreer=*it;
            if(!res.hasState(etatAcreer)){
                res.addState(etatAcreer);
            }
        }
      
        int numero_ligne=1;
        for(std::set<char>::const_iterator it=automatonOK.alphabet.begin(); it!=automatonOK.alphabet.end();++it){
                std::vector<int> ligne=congruence.at(numero_ligne);
                int EtatFrom=0;
                for(std::vector<int>::const_iterator it2=ligne.begin(); it2!=ligne.end();it2++){
                    if(!res.hasTransition(congruence.at(0).at(EtatFrom),*it,*it2)){
                         res.addTransition(congruence.at(0).at(EtatFrom),*it,*it2);
                    }
                    EtatFrom++;
                }
                numero_ligne++;
        }
        for(std::map<int,struct state*>::const_iterator it=automatonOK.states_initial.begin(); it != automatonOK.states_initial.end(); ++it){
            int etat_initial=it->first;
            res.setStateInitial(congruence.at(0).at(etat_initial));
        }
        for(std::map<int,struct state*>::const_iterator it=automatonOK.states_final.begin(); it != automatonOK.states_final.end(); ++it){
            int etat_final=it->first;
            res.setStateFinal(congruence.at(0).at(etat_final));
        }
        return res;
    }
}   
