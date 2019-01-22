#include "Automaton.h"

int main() {
    fa::Automaton depart,deterministe;
    cout<<"on prend un automate vide\n";
    cout<<"\nOn ajoute les etats 0,1 et 2";
    depart.addState(0);
    depart.addState(1);
    depart.addState(2);
    cout<<"\n On ajoute les transitions (0,a,1) et (1,b,2) (1,b,1)";
    depart.addTransition(0,'a',1);
    depart.addTransition(1,'b',2);
    depart.addTransition(1,'b',1);
    cout<<"\n L'automate comporte "<<depart.countStates()<<" états";
    cout<<"\n L'automate comporte "<<depart.countTransitions()<<"transitions";
    cout<<"\n L'état 0 est-il initial? "<<depart.isStateInitial(0);
    cout<<"\n L'état 0 est-il final? "<<depart.isStateFinal(1);
    cout<<"\nOn rend l'état 0 initial et l'état 1 final ";
    depart.setStateInitial(0);
    depart.setStateFinal(1);
    cout<<"\n L'état 0 est-il initial? "<<depart.isStateInitial(0);
    cout<<"\n L'état 0 est-il final? "<<depart.isStateFinal(1);
    cout<<"\n L'état 0 est-il dans l'automate? "<<depart.hasState(0);
    cout<<"\n L'état 3 est-il dans l'automate? "<<depart.hasState(3);
    cout<<"\n On ajoute puis supprime l'état 3 ";
    depart.addState(3);
    depart.removeState(3);
    cout<<"\n L'état 3 est-il dans l'automate? "<<depart.hasState(3);
    cout<<"\n La taille de l'alphabet est : "<<depart.getAlphabetSize();
    cout<<"\n On affiche l'automate: ";
    depart.prettyPrint(std::cout);
    cout<<"\n cet automate est il deterministe? "<<depart.isDeterministic();
    cout<<"\n\n=============================================================================\n";
    cout<<"\n\n Donnons son automate déterministe :";
    fa::Automaton automata = fa::Automaton::createDeterministic(depart);
    cout<<"\n Le nouvel automate est il deterministe? "<<automata.isDeterministic()<<"\nVoici son automate :\n";
    automata.prettyPrint(std::cout);
    
    
    cout<<"\n L'automate d'origine est-il complet ? "<<depart.isComplete();
	cout<<"\n Non, donc completons le et affichons le : \n";
	
	depart.makeComplete();
	depart.prettyPrint(std::cout);
	
	cout<<"\n Est-il toujours déterministe apres le completage ? : "<<depart.isDeterministic();
	cout<<"\n Non, donc on le determinise affichons le : \n";
	automata = fa::Automaton::createDeterministic(depart);
	automata.prettyPrint(std::cout);
	
	cout<<"\n Deterministe et complet :  "<<automata.isComplete() <<" "<< automata.isDeterministic();
	cout<<"\n Il est donc deterministe et complet. \n";
	cout<<"\n ================================================================================\n";
	cout<<"\n Regardons le langage accepté par cet automate : \n";
	cout<<" Le mot est accepte \"aaabaa\" : "<<automata.match("aaabaa")<<" \n";
	cout<<" Le mot est accepte \"aaa\" : "<<automata.match("aaa")<<" \n";
	cout<<" Le mot est accepte \"ba\" : "<<automata.match("ba")<<" \n";
	cout<<" Le mot est accepte \"bbbb\" : "<<automata.match("bbbb")<<" \n";
	cout<<" Le mot est accepte \"\" : "<<automata.match("")<<" \n";
	cout<<" Le mot est accepte \"edf\" : "<<automata.match("edf")<<" \n";
	cout<<" Le mot est accepte \"a\" : "<<automata.match("a")<<" \n";
	cout<<" Le mot est accepte \"ab\" : "<<automata.match("ab")<<" \n";
	cout<<" Le mot est accepte \"abb\" : "<<automata.match("abb")<<" \n";
	cout<<"\n Maintenant, minimisons c'est automate et affichons le : \n";
	fa::Automaton minimal = fa::Automaton::createDeterministic(automata);
	minimal.prettyPrint(std::cout);
	cout<<"\n Il est maintenant minimal.\n";
	cout<<"\n Verifions que le langage est toujours le meme : \n";
	cout<<" Le mot est accepte \"aaabaa\" : "<<minimal.match("aaabaa")<<" \n";
	cout<<" Le mot est accepte \"aaa\" : "<<minimal.match("aaa")<<" \n";
	cout<<" Le mot est accepte \"ba\" : "<<minimal.match("ba")<<" \n";
	cout<<" Le mot est accepte \"bbbb\" : "<<minimal.match("bbbb")<<" \n";
	cout<<" Le mot est accepte \"\" : "<<minimal.match("")<<" \n";
	cout<<" Le mot est accepte \"edf\" : "<<minimal.match("edf")<<" \n";
	cout<<" Le mot est accepte \"a\" : "<<minimal.match("a")<<" \n";
	cout<<" Le mot est accepte \"ab\" : "<<minimal.match("ab")<<" \n";
	cout<<" Le mot est accepte \"abb\" : "<<minimal.match("abb")<<" \n";

	cout<<"\n\n ================================================================================\n";
	cout<<"\n On a vu que le langage n'était pas vide, verifions le : " <<minimal.isLanguageEmpty();
	cout<<"\n\n ================================================================================\n";
	
	cout<<"\n Realisons maintenant le complementaire de cet automate et affichons le :\n";
	minimal.makeComplement();
	minimal.prettyPrint(std::cout);
	cout<<"\n On remarque que les états finaux ne le sont plus que les etats non finaux le sont devenus.\n";

	
	cout<<"\n\n ================================================================================\n";
	
	cout<<"\n\n Nous allons maintenant créer une intersection entre un nouvel automate et le nouveau qui est minimal. Et afficher le résultat\n";
	
	fa::Automaton fa1;
	fa1.addState(0);
	fa1.addState(1);
	fa1.setStateInitial(0);
	fa1.setStateFinal(1);
	fa1.addTransition(0,'a',1);
	fa1.addTransition(1,'a',0);
	
	fa1.prettyPrint(std::cout);
	
	cout<<"\n\n\n";
	
	fa::Automaton produit = fa::Automaton::createProduct(fa1, automata);
	produit.prettyPrint(std::cout);
	
	cout<<"\n\n Nous pouvons constater que l'intersection de ceux-ci n'est pas vide, verifions le avec une fonction : "<<fa1.hasEmptyIntersectionWith(automata);
	
	cout<<"\n\n ================================================================================\n";
	
	cout<<"\n\n Mainteant prenons un automate avec des epsilons transitions et affichons le.\n";
	fa::Automaton fa;

    fa.addState(0);
    fa.addState(1);
    fa.addState(2);
    fa.setStateInitial(0);
    fa.setStateFinal(2);

    fa.addTransition(0, 'a', 0);
    fa.addTransition(0, 0, 1);
    fa.addTransition(1, 'b', 1);
    fa.addTransition(1, 0, 2);
    fa.addTransition(2, 'c', 2);
	fa.addTransition(2, 0, 0);
	
	fa::Automaton faWhitoutEpsilon = fa::Automaton::createWithoutEpsilon(fa);
	
	fa.prettyPrint(std::cout);
	
	cout<<"\n\n Affichons le maintenant sans les epsilons transitions :\n\n";
	
	faWhitoutEpsilon.prettyPrint(std::cout);

	cout<<"\n\n Testons quelques mots du langage :\n";
	cout<<" Le mot est accepte \"aaabaa\" : "<<minimal.match("aaabaa")<<" \n";
	cout<<" Le mot est accepte \"abc\" : "<<minimal.match("abc")<<" \n";
	cout<<" Le mot est accepte \"edf\" : "<<minimal.match("edf")<<" \n";
	cout<<" Le mot est accepte \"aaaaa\" : "<<minimal.match("aaaaa")<<" \n";
	cout<<" Le mot est accepte \"bbbbb\" : "<<minimal.match("bbbbb")<<" \n";
	cout<<" Le mot est accepte \"ccc\" : "<<minimal.match("ccc")<<" \n";
	cout<<"\n";

	return 0;
}
    
