#include <iostream>
#include <iomanip>

#include "gtest/gtest.h"

#include "Automaton.h"

TEST(AutomatonTest, Empty) {
  fa::Automaton fa;

  EXPECT_EQ(fa.countStates(), 0u);
  EXPECT_EQ(fa.countTransitions(), 0u);
}

TEST(AutomatonTest, addState) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(3);
  EXPECT_EQ(fa.countStates(), 2u);
  EXPECT_EQ(fa.hasState(1),true);
  EXPECT_EQ(fa.hasState(2),false);
  EXPECT_EQ(fa.hasState(3),true);
}

TEST(AutomatonTest, addTransition) {
    fa::Automaton fa;
    fa.addState(1);
    fa.addState(3);
    fa.addTransition(1,'e',2);
    EXPECT_EQ(fa.countTransitions(),0u);
    fa.addTransition(1,'e',3);
    EXPECT_EQ(fa.countTransitions(),1u);
    EXPECT_EQ(fa.hasTransition(1,'e',3),true);
    EXPECT_EQ(fa.hasTransition(2,'e',3),false);
    EXPECT_EQ(fa.hasTransition(1,'e',2),false);
    EXPECT_EQ(fa.hasTransition(1,'b',3),false);
    fa.addTransition(1,'e',3);
    EXPECT_EQ(fa.countTransitions(),1u);
    EXPECT_EQ(fa.getAlphabetSize(),1u);
}

TEST(AutomatonTest, RemoveTransition) {
    fa::Automaton fa;
    fa.addState(1);
    fa.addState(3);
    fa.addTransition(1,'e',3);
    fa.removeTransition(1,'e',2);
    EXPECT_EQ(fa.countTransitions(),1u);
    fa.removeTransition(2,'e',3);
    EXPECT_EQ(fa.countTransitions(),1u);
    fa.removeTransition(1,'f',3);
    EXPECT_EQ(fa.countTransitions(),1u);
    fa.removeTransition(1,'e',3);
    EXPECT_EQ(fa.countTransitions(),0u);
}
TEST(AutomatonTest, RemoveState) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.addTransition(1,'e',3);
  fa.addTransition(1,'e',2);
  fa.addTransition(2,'e',3);
  fa.removeState(4);
  EXPECT_EQ(fa.countStates(), 3u);
  fa.removeState(3);
  EXPECT_EQ(fa.countTransitions(), 1u);
  EXPECT_EQ(fa.hasTransition(1,'e',2),true);
  EXPECT_EQ(fa.countStates(), 2u);
  EXPECT_EQ(fa.hasState(3),false);
  EXPECT_EQ(fa.hasState(2),true);
  EXPECT_EQ(fa.hasState(1),true);
}

TEST(AutomatonTest, setStateInitial) {
    fa::Automaton fa;
    fa.addState(1);
    fa.setStateInitial(2);
    EXPECT_EQ(fa.isStateInitial(1),false);
    fa.setStateInitial(1);
    EXPECT_EQ(fa.isStateInitial(1),true);
    fa.setStateInitial(1);
    EXPECT_EQ(fa.isStateInitial(1),true);
}
TEST(AutomatonTest, setStateFinal) {
    fa::Automaton fa;
    fa.addState(1);
    fa.setStateFinal(2);
    EXPECT_EQ(fa.isStateFinal(1),false);
    fa.setStateFinal(1);
    EXPECT_EQ(fa.isStateFinal(1),true);
    fa.setStateFinal(1);
    EXPECT_EQ(fa.isStateFinal(1),true);
}

TEST(AutomatonTest, Alphabet) {
    fa::Automaton fa;
    fa.addState(1);
    fa.addState(2);
    fa.addTransition(1,'e',2);
    EXPECT_EQ(fa.getAlphabetSize(),1u);
    fa.removeTransition(1,'e',2);
    EXPECT_EQ(fa.getAlphabetSize(),1u);
}
TEST(AutomatonTest, isDeterministic0) {
    fa::Automaton fa;
    fa.addState(1);
    fa.addState(2);
    fa.setStateInitial(1);
    fa.addTransition(1,'e',2);
    fa.addTransition(1,'e',1);
    EXPECT_EQ(fa.isDeterministic(),false);
    fa::Automaton fa1;
    EXPECT_EQ(fa1.isDeterministic(),false);
    fa1.addState(1);
    EXPECT_EQ(fa1.isDeterministic(),false);
    fa1.setStateInitial(1);
    EXPECT_EQ(fa1.isDeterministic(),true);
    fa1.addState(2);
    fa1.addTransition(1,'e',2);
    fa1.addTransition(1,'f',2);
    fa1.addTransition(2,'f',1);
    fa1.addTransition(2,'e',1);
    EXPECT_EQ(fa1.isDeterministic(),true);
    fa1.setStateInitial(2);
    EXPECT_EQ(fa1.isDeterministic(),false);
}

TEST(AutomatonTest, isDeterminictic1) {
	fa::Automaton fa;
	fa.addState(0);
	fa.addState(1);
	fa.setStateInitial(0);
	fa.setStateFinal(1);
	fa.addTransition(0, 'a', 1);
	fa.addTransition(1, 'a', 0);
	EXPECT_TRUE(fa.isDeterministic());
}

TEST(AutomatonTest, isComplete) {
    fa::Automaton fa;
    EXPECT_EQ(fa.isComplete(),true);
    fa.addState(1);
    EXPECT_EQ(fa.isComplete(),true);
    fa.addState(2);
    fa.addTransition(1,'e',1);
    EXPECT_EQ(fa.isComplete(),false);
    fa.addTransition(2,'e',1);
    EXPECT_EQ(fa.isComplete(),true);
    fa.addTransition(2,'e',2);
    EXPECT_EQ(fa.isComplete(),false);
}

TEST(AutomatonTest, makeComplete) {
    fa::Automaton fa;
    fa.addState(1);
    fa.addState(2);
    fa.addState(3);
    fa.addTransition(1,'e',1);
    fa.addTransition(1,'f',1);
    fa.addTransition(2,'g',3);
    EXPECT_EQ(fa.isComplete(),false);
    fa.makeComplete();
    EXPECT_EQ(fa.isComplete(),true);
}

TEST(AutomatonTest, makeComplete1) {
	fa::Automaton fa;
	fa.addState(0);
    fa.addState(1);
    fa.addState(2);
    fa.addState(3);
    fa.addState(4);
    fa.addTransition(0,'a',1);
    fa.addTransition(1,'b',0);
    fa.addTransition(1,'a',2);
    fa.addTransition(2,'a',0);
    fa.addTransition(2,'b',3);
    fa.addTransition(3,'a',1);
    fa.addTransition(3,'b',4);
    fa.addTransition(4,'a',3);
    EXPECT_FALSE(fa.isComplete());
    fa.makeComplete();
    EXPECT_TRUE(fa.isComplete());
}

TEST(AutomatonTest, makeComplement) {
    fa::Automaton fa;
    fa.makeComplement();
    EXPECT_EQ(fa.countStates(),0u);
    EXPECT_EQ(fa.countTransitions(),0u);
    EXPECT_EQ(fa.getAlphabetSize(),0u);
    fa.addState(1);
    fa.addState(2);
    fa.addState(3);
    fa.addState(4);
    fa.addTransition(1,'e',1);
    fa.addTransition(1,'f',2);
    fa.setStateFinal(2);
    fa.setStateFinal(3);
    fa.setStateInitial(1);
    EXPECT_EQ(fa.isDeterministic(),true);
    fa.makeComplement();  
    EXPECT_EQ(fa.isStateInitial(1),false);
    EXPECT_EQ(fa.isStateInitial(2),true);
    EXPECT_EQ(fa.isStateInitial(3),true);
    EXPECT_EQ(fa.isStateInitial(4),false);
    EXPECT_EQ(fa.isStateFinal(1),true);
    EXPECT_EQ(fa.isStateFinal(2),false);
    EXPECT_EQ(fa.isStateFinal(3),false);
    EXPECT_EQ(fa.isStateFinal(4),false);
}

 TEST(AutomatonTest, isLangageEmpty) {
  fa::Automaton fa;
  EXPECT_EQ(fa.isLanguageEmpty(),true);
  fa.addState(1);
  EXPECT_EQ(fa.isLanguageEmpty(),true);
  fa.setStateInitial(1);
  EXPECT_EQ(fa.isLanguageEmpty(),true);
  fa.addState(2);
  fa.setStateFinal(2);
  EXPECT_EQ(fa.isLanguageEmpty(),true);
  fa.addTransition(1,'e',1);
  fa.addTransition(2,'f',2);
  EXPECT_EQ(fa.isLanguageEmpty(),true);
  fa.addTransition(1,'e',2);
  EXPECT_EQ(fa.isLanguageEmpty(),false);
 }

  TEST(AutomatonTest, removeNonAccessibleStates) {
    fa::Automaton fa;
    fa.addState(1);
    fa.addState(2);
    fa.removeNonAccessibleStates();
    EXPECT_EQ(fa.countStates(),0u);
    fa.addState(1);
    fa.addState(2);
    fa.addState(3);
    fa.addState(4);
    fa.setStateInitial(1);
    fa.removeNonAccessibleStates();
    EXPECT_EQ(fa.countStates(),1u);
    EXPECT_EQ(fa.hasState(1),true);
    fa.addState(2);
    fa.addState(3);
    fa.addState(4);
    fa.addState(5);
    fa.setStateInitial(4);
    fa.addTransition(1,'e',2);
    fa.addTransition(1,'f',3);
    fa.removeNonAccessibleStates();
    EXPECT_EQ(fa.countStates(),4u);
    EXPECT_EQ(fa.hasState(5),false);
  }

  TEST(AutomatonTest, removeNonCoAccessibleStates) {
    fa::Automaton fa;
    fa.addState(1);
    fa.addState(2);
    fa.removeNonCoAccessibleStates();
    EXPECT_EQ(fa.countStates(),0u);
    fa.addState(1);
    fa.addState(2);
    fa.addState(3);
    fa.addState(4);
    fa.setStateFinal(4);
    fa.removeNonCoAccessibleStates();
    EXPECT_EQ(fa.countStates(),1u);
    EXPECT_EQ(fa.hasState(4),true);
    fa.addState(0);
    fa.addState(1);
    fa.addState(2);
    fa.addState(3);
    fa.setStateFinal(3);
    fa.addTransition(1,'f',0);
    fa.addTransition(4,'e',2);
    fa.addTransition(1,'e',2);
    fa.addTransition(2,'f',3);
    fa.removeNonCoAccessibleStates();
    EXPECT_EQ(fa.hasState(2),true);
    EXPECT_EQ(fa.countStates(),4u);
    EXPECT_EQ(fa.hasState(0),false);
  }

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
