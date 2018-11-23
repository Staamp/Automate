#include "Automaton.h"
//#include "../../../../Program Files (x86)/Microsoft Visual Studio/2017/Community/VC/Tools/MSVC/14.15.26726/include/iostream"

int main(){
  fa::Automaton fa;
    fa.addState(1);
    fa.addState(2);
    fa.setStateInitial(1);
    fa.addTransition(1,'e',2);
    fa.addTransition(1,'e',1);
    //EXPECT_EQ(fa.isDeterministic(),false);
    fa::Automaton fa1;
    //EXPECT_EQ(fa1.isDeterministic(),false);
    fa1.addState(1);
    //EXPECT_EQ(fa1.isDeterministic(),false);
    fa1.setStateInitial(1);
    //EXPECT_EQ(fa1.isDeterministic(),true);
    fa1.addState(2);
    fa1.addTransition(1,'e',2);
    fa1.addTransition(1,'f',2);
    fa1.addTransition(2,'f',1);
    fa1.addTransition(2,'e',1);
    //EXPECT_EQ(fa1.isDeterministic(),true);
    fa1.setStateInitial(2);
    //EXPECT_EQ(fa1.isDeterministic(),false);
  
  
  	fa::Automaton fa2;
    fa2.addState(0);
    fa2.addState(1);
    fa2.addState(2);
    fa2.setStateInitial(0);
    fa2.setStateFinal(2);

    fa2.addTransition(0, 'a', 0);
    fa2.addTransition(0, 'b', 1);
    fa2.addTransition(1, 'a', 0);
    fa2.addTransition(1, 'b', 2);
    fa2.addTransition(2, 'a', 2);
    fa2.addTransition(2, 'b', 2);

    /*EXPECT_TRUE(fa.isDeterministic());

    EXPECT_EQ(fa.countStates(), 3u);
    EXPECT_EQ(fa.countTransitions(), 6u);
    EXPECT_EQ(fa.getAlphabetSize(), 2u);*/
  

  fa.prettyPrint(std::cout);
  std::cout << std::endl;
  std::cout << "_____________________________________________________________" << std::endl;
  
  
  
  fa1.prettyPrint(std::cout);
  std::cout << std::endl;
  std::cout << "_____________________________________________________________" << std::endl;


  fa2.prettyPrint(std::cout);
  std::cout << std::endl;
  std::cout << "_____________________________________________________________" << std::endl;


  return 0;
}

