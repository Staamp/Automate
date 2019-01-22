#include <iostream>
#include <iomanip>

#include "gtest/gtest.h"
#include "Automaton.h"


class AutomatonTestFixture : public ::testing::Test {
	protected:
    
    
    fa::Automaton faComplet;
    fa::Automaton faDeterministe;
	fa::Automaton faDeterministeMultiFinal;
	fa::Automaton faNCompletNDeterministe;
	fa::Automaton faCompletEtDeter;
	fa::Automaton faEtatNonSuivi;
	fa::Automaton faEtatNegatif;
	fa::Automaton faNonCoAcces;
	fa::Automaton faNonAcces;
    
    virtual void SetUp() override {
    	initFaComplet();
    	initFaDeterministe();
    	initFaDeterministeMultiFinal();
    	initfFaNCompletNDeterministe();
    	initFaCompletEtDeter();
    	initFaEtatNonSuivi();
    	initFaEtatNegatif();
    	initFaNonCoAcces();
    	initFaNonAcces();
    }

    void initFaComplet() {
    	faComplet.addState(1);
		faComplet.addState(2);
		faComplet.addTransition(1,'e',1);
		faComplet.addTransition(2,'e',1);
		faComplet.addTransition(2,'e',2);
    }
	
	void initFaDeterministe() {
		faDeterministe.addState(1);
		faDeterministe.setStateInitial(1);
		faDeterministe.addState(2);
		faDeterministe.addTransition(1,'e',2);
		faDeterministe.addTransition(1,'f',2);
		faDeterministe.addTransition(2,'f',1);
		faDeterministe.addTransition(2,'e',1);
	}
	
    void initFaDeterministeMultiFinal() {
		faDeterministeMultiFinal.addState(1);
		faDeterministeMultiFinal.setStateInitial(1);
		faDeterministeMultiFinal.addState(2);
		faDeterministeMultiFinal.setStateFinal(1);
		faDeterministeMultiFinal.setStateFinal(2);
		faDeterministeMultiFinal.addTransition(1,'e',2);
		faDeterministeMultiFinal.addTransition(1,'f',2);
		faDeterministeMultiFinal.addTransition(2,'f',1);
		faDeterministeMultiFinal.addTransition(2,'e',1);
    }
    
    void initfFaNCompletNDeterministe() {
    	faNCompletNDeterministe.addState(1);
		faNCompletNDeterministe.setStateInitial(1);
		faNCompletNDeterministe.addState(2);
		faNCompletNDeterministe.setStateFinal(2);
		faNCompletNDeterministe.addTransition(1,'e',1);
		faNCompletNDeterministe.addTransition(1,'e',2);
		faNCompletNDeterministe.addTransition(1,'f',1);
    }
	
	void initFaCompletEtDeter() {
		faCompletEtDeter.addState(1);
		faCompletEtDeter.setStateInitial(1);
		faCompletEtDeter.addState(2);
		faCompletEtDeter.setStateFinal(2);
		faCompletEtDeter.addTransition(1,'a',2);
		faCompletEtDeter.addTransition(1,'b',2);
		faCompletEtDeter.addTransition(2,'a',1);
		faCompletEtDeter.addTransition(2,'b',2);
	}
	
	void initFaEtatNonSuivi() {
		faEtatNonSuivi.addState(1);
		faEtatNonSuivi.setStateInitial(1);
		faEtatNonSuivi.addState(3);
		faEtatNonSuivi.addState(5);
		faEtatNonSuivi.setStateFinal(5);
		faEtatNonSuivi.addTransition(1,'e',3);
		faEtatNonSuivi.addTransition(3,'f',5);
		faEtatNonSuivi.addTransition(5,'f',1);
	}
	
	void initFaEtatNegatif() {
		faEtatNegatif.addState(-1);
		faEtatNegatif.setStateInitial(-1);
		faEtatNegatif.addState(-3);
		faEtatNegatif.addState(5);
		faEtatNegatif.setStateFinal(5);
		faEtatNegatif.addTransition(-1,'e',-3);
		faEtatNegatif.addTransition(-3,'f',5);
		faEtatNegatif.addTransition(5,'f',-1);
	}

	void initFaNonCoAcces() {
		faNonCoAcces.addState(0);
		faNonCoAcces.addState(1);
		faNonCoAcces.addState(2);
		faNonCoAcces.addState(3);
		faNonCoAcces.addState(4);
		faNonCoAcces.setStateFinal(3);
		faNonCoAcces.addTransition(1,'f',0);
		faNonCoAcces.addTransition(4,'e',2);
		faNonCoAcces.addTransition(1,'e',2);
		faNonCoAcces.addTransition(2,'f',3);
	}

	void initFaNonAcces() {
		faNonAcces.addState(0);
		faNonAcces.addState(1);
		faNonAcces.addState(2);
		faNonAcces.addState(3);
		faNonAcces.addState(4);
		faNonAcces.setStateFinal(3);
		faNonAcces.addTransition(1,'f',0);
		faNonAcces.addTransition(2,'e',4);
		faNonAcces.addTransition(1,'e',2);
		faNonAcces.addTransition(2,'f',3);
	}
};


//OK RELU 04/12/2018
TEST(AutomatonTest, Empty) {
    fa::Automaton fa;
    EXPECT_EQ(fa.countStates(), 0u);
    EXPECT_EQ(fa.countTransitions(), 0u);
}


//OK RELU 04/12/2018
TEST(AutomatonTest, addState){
    fa::Automaton fa;
    fa.addState(1);
    fa.addState(3);
    EXPECT_EQ(fa.countStates(), 2u);
    EXPECT_TRUE(fa.hasState(1));
    EXPECT_FALSE(fa.hasState(2));
    EXPECT_TRUE(fa.hasState(3));
    EXPECT_EQ(fa.countStates(), 2u);
    fa.addState(-1);
    EXPECT_TRUE(fa.hasState(-1));
    EXPECT_EQ(fa.countStates(), 3u);
}

TEST(AutomatonTest, addState1) {
	fa::Automaton fa;
    fa.addState(1);
    fa.addState(3);
    EXPECT_TRUE(fa.hasState(1));
    EXPECT_FALSE(fa.hasState(2));
    EXPECT_TRUE(fa.hasState(3));
    EXPECT_DEATH(fa.addState(3), "");
}


//OK RELU 04/12/2018
TEST(AutomatonTest, addTransition) {
    fa::Automaton fa;
    fa.addState(1);
    fa.addState(3);
    EXPECT_DEATH(fa.hasTransition(1,'e',2),"");
    EXPECT_DEATH(fa.addTransition(1,'e',2), "");
    EXPECT_DEATH(fa.hasTransition(1,'e',2),"");
    EXPECT_EQ(fa.countTransitions(),0u);
    EXPECT_FALSE(fa.hasTransition(1,'e',3));
    fa.addTransition(1,'e',3);
    EXPECT_EQ(fa.countTransitions(),1u);
    EXPECT_TRUE(fa.hasTransition(1,'e',3));
    EXPECT_DEATH(fa.hasTransition(2,'e',3),"");
    EXPECT_DEATH(fa.hasTransition(1,'e',2),"");
    EXPECT_FALSE(fa.hasTransition(1,'b',3));
    fa.addTransition(1,'e',3);
    EXPECT_TRUE(fa.hasTransition(1,'e',3));
    EXPECT_EQ(fa.countTransitions(),1u);
    EXPECT_EQ(fa.getAlphabetSize(),1u);
}

//OK RELU 04/12/2018
TEST(AutomatonTest, RemoveTransition) {
    fa::Automaton fa;
    fa.addState(1);
    fa.addState(3);
    fa.addTransition(1,'e',3);
    EXPECT_DEATH(fa.addTransition(2,'e',3), "");
    fa.addTransition(1,'f',3);
    EXPECT_EQ(fa.countTransitions(),2u);
    EXPECT_TRUE(fa.hasTransition(1,'e',3));
    EXPECT_DEATH(fa.hasTransition(1,'e',2),"");
    EXPECT_DEATH(fa.removeTransition(1,'e',2), "");
    EXPECT_DEATH(fa.hasTransition(1,'e',2),"");
    fa.removeTransition(1,'e',3);
    EXPECT_FALSE(fa.hasTransition(1,'e',3));
    EXPECT_EQ(fa.countTransitions(),1u);
    EXPECT_DEATH(fa.hasTransition(2,'e',3),"");
    EXPECT_DEATH(fa.removeTransition(2,'e',3), "");
    EXPECT_DEATH(fa.hasTransition(2,'e',3),"");
    EXPECT_EQ(fa.countTransitions(),1u);
    EXPECT_TRUE(fa.hasTransition(1,'f',3));
    fa.removeTransition(1,'f',3);
    EXPECT_FALSE(fa.hasTransition(1,'f',3));
    EXPECT_EQ(fa.countTransitions(),0u);
}

//OK RELU 04/12/2018
TEST(AutomatonTest, RemoveState0) {
    fa::Automaton fa;
    fa.addState(1);
    fa.addState(2);
    fa.addState(3);
    EXPECT_TRUE(fa.hasState(1));
    EXPECT_TRUE(fa.hasState(2));
    EXPECT_TRUE(fa.hasState(3));
    fa.addTransition(1,'e',3);
    fa.addTransition(1,'e',2);
    fa.addTransition(2,'e',3);
    EXPECT_EQ(fa.countStates(), 3u);
    EXPECT_EQ(fa.countTransitions(), 3u);
    EXPECT_FALSE(fa.hasState(4));
    EXPECT_DEATH(fa.removeState(4), "");
    EXPECT_FALSE(fa.hasState(4));
    EXPECT_TRUE(fa.hasState(1));
    EXPECT_TRUE(fa.hasState(2));
    EXPECT_TRUE(fa.hasState(3));
    EXPECT_EQ(fa.countStates(), 3u);
}

//OK RELU 08/12/2018
TEST(AutomatonTest, removeState1) {
    fa::Automaton fa;
    fa.addState(1);
    fa.addState(2);
    fa.addState(3);
    EXPECT_TRUE(fa.hasState(1));
    EXPECT_TRUE(fa.hasState(2));
    EXPECT_TRUE(fa.hasState(3));
    fa.addTransition(1,'e',3);
    fa.addTransition(1,'e',2);
    fa.addTransition(2,'e',3);
    fa.removeState(3);
    EXPECT_FALSE(fa.hasState(3));
    //VERIF SUP TRANSITION ETAT
    EXPECT_EQ(fa.countTransitions(), 1u);
    EXPECT_TRUE(fa.hasTransition(1,'e',2));
    EXPECT_DEATH(fa.hasTransition(1,'e',3),"");
    EXPECT_DEATH(fa.hasTransition(2,'e',3),"");
    EXPECT_EQ(fa.countStates(), 2u);
    EXPECT_FALSE(fa.hasState(3));
    EXPECT_TRUE(fa.hasState(2));
    EXPECT_TRUE(fa.hasState(1));
}

//OK RELU 08/12/2018
TEST(AutomatonTest, removeState2) {
    fa::Automaton fa;
    fa.addState(1);
    fa.addState(2);
    EXPECT_TRUE(fa.hasState(1));
    EXPECT_TRUE(fa.hasState(2));

    EXPECT_FALSE(fa.isStateInitial(1));
    fa.setStateInitial(1);
    EXPECT_TRUE(fa.isStateInitial(1));
    fa.removeState(1);
    EXPECT_FALSE(fa.hasState(1));
    EXPECT_DEATH(fa.isStateInitial(1), "");

    EXPECT_FALSE(fa.isStateFinal(2));
    fa.setStateFinal(2);
    EXPECT_TRUE(fa.isStateFinal(2));
    fa.removeState(2);
    EXPECT_FALSE(fa.hasState(2));
    EXPECT_DEATH(fa.isStateFinal(2), "");
}

TEST(AutomatonTest, removeState3) {
	fa::Automaton fa;
    fa.addState(1);
    fa.addState(2);
    EXPECT_TRUE(fa.hasState(1));
    EXPECT_TRUE(fa.hasState(2));
    fa.removeState(1);
    EXPECT_FALSE(fa.hasState(1));
    EXPECT_DEATH(fa.removeState(1), "");
}



//OK RELU 04/12/2018
TEST(AutomatonTest, setStateInitial) {
    fa::Automaton fa;
    fa.addState(1);
    EXPECT_EQ(fa.countStates(), 1u);
    EXPECT_FALSE(fa.isStateInitial(1));
    EXPECT_DEATH(fa.isStateInitial(2),"");
    EXPECT_DEATH(fa.setStateInitial(2), "");
    EXPECT_EQ(fa.countStates(), 1u);
    EXPECT_FALSE(fa.isStateInitial(1));
    EXPECT_DEATH(fa.isStateInitial(2),"");
    fa.setStateInitial(1);
    EXPECT_TRUE(fa.isStateInitial(1));
    fa.setStateInitial(1);
    EXPECT_TRUE(fa.isStateInitial(1));
    EXPECT_EQ(fa.countStates(), 1u);
}

//OK RELU 04/12/2018
TEST(AutomatonTest, setStateFinal) {
    fa::Automaton fa;
    fa.addState(1);
    EXPECT_EQ(fa.countStates(), 1u);
    EXPECT_FALSE(fa.isStateFinal(1));
    EXPECT_DEATH(fa.isStateFinal(2), "");
    EXPECT_DEATH(fa.setStateFinal(2), "");
    EXPECT_EQ(fa.countStates(), 1u);
    EXPECT_FALSE(fa.isStateFinal(1));
    EXPECT_DEATH(fa.isStateFinal(2), "");
    fa.setStateFinal(1);
    EXPECT_TRUE(fa.isStateFinal(1));
    fa.setStateFinal(1);
    EXPECT_TRUE(fa.isStateFinal(1));
    EXPECT_EQ(fa.countStates(), 1u);
}

//OK RELU 04/12/2018
TEST(AutomatonTest, Alphabet0) {
    fa::Automaton fa;
    fa.addState(1);
    fa.addState(2);
    EXPECT_EQ(fa.getAlphabetSize(), 0u);
    fa.addTransition(1, 'e', 2);
    EXPECT_EQ(fa.getAlphabetSize(), 1u);
    fa.addTransition(1, 'f', 2);
    EXPECT_TRUE(fa.hasTransition(1,'e', 2));
    EXPECT_TRUE(fa.hasTransition(1, 'f', 2));
    EXPECT_EQ(fa.getAlphabetSize(), 2u);
    fa.removeTransition(1, 'e', 2);
    EXPECT_EQ(fa.getAlphabetSize(), 2u);
}

//OK RELU 08/12/2018
TEST(AutomatonTest, Alphabet1) {
    fa::Automaton fa;
    EXPECT_EQ(fa.getAlphabetSize(), 0u);
    EXPECT_DEATH(fa.addTransition(6, 'z', 7), "");
    EXPECT_DEATH(fa.hasTransition(6, 'z', 7), "");
    EXPECT_EQ(fa.getAlphabetSize(), 0u);
}

//Test automate vide
TEST(AutomatonTest, isDeterministic0) {
    fa::Automaton vide;
    EXPECT_FALSE(vide.isDeterministic());
}

TEST(AutomatonTest, isDeterministic1) {
    fa::Automaton fa;
    fa.addState(1);
    EXPECT_FALSE(fa.isDeterministic());
}

//Test automate complet
TEST_F(AutomatonTestFixture, isDeterministic2) {
    EXPECT_FALSE(faComplet.isDeterministic());
}

//Test automate deterministe
TEST_F(AutomatonTestFixture, isDeterministic3) {
    EXPECT_TRUE(faDeterministe.isDeterministic());
}

//Automate non complet et non deterministe
TEST_F(AutomatonTestFixture, isDeterministic4) {
    EXPECT_FALSE(faNCompletNDeterministe.isDeterministic());
}

//Automate complet et deterministe
TEST_F(AutomatonTestFixture, isDeterministic5) {
    EXPECT_TRUE(faCompletEtDeter.isDeterministic());
}

//Etats qui se suivent pas
TEST_F(AutomatonTestFixture, isDeterministic6) {
    EXPECT_TRUE(faEtatNonSuivi.isDeterministic());
}

//Etats négatifs
TEST_F(AutomatonTestFixture, isDeterministic7) {
    EXPECT_TRUE(faEtatNegatif.isDeterministic());
}

//Automate non accessible
TEST_F(AutomatonTestFixture, isDeterministic8) {
    EXPECT_FALSE(faNonAcces.isDeterministic());
}

//Automate non co accessible
TEST_F(AutomatonTestFixture, isDeterministic9) {
    EXPECT_FALSE(faNonCoAcces.isDeterministic());
}

//Automate avec plusieurs état finaux et déterministe
TEST_F(AutomatonTestFixture, isDeterministic10) {
    EXPECT_TRUE(faDeterministeMultiFinal.isDeterministic());
}

//OK RELU 10/12/2018
TEST(AutomatonTest, isDeterministic11) {
    fa::Automaton fa1;
    EXPECT_FALSE(fa1.isDeterministic());
    fa1.addState(1);
    EXPECT_FALSE(fa1.isDeterministic());
    fa1.setStateInitial(1);
    EXPECT_TRUE(fa1.isDeterministic());
    fa1.addState(2);
    EXPECT_TRUE(fa1.isDeterministic());
    fa1.addTransition(1,'e',2);
    EXPECT_TRUE(fa1.isDeterministic());
    fa1.addTransition(1,'f',2);
    EXPECT_TRUE(fa1.isDeterministic());
    fa1.addTransition(2,'f',1);
    EXPECT_TRUE(fa1.isDeterministic());
    fa1.addTransition(2,'e',1);
    EXPECT_TRUE(fa1.isDeterministic());
    fa1.setStateInitial(2);
    EXPECT_FALSE(fa1.isDeterministic());
}

//OK RELU 04/12/2018
TEST(AutomatonTest, isComplete0) {
    fa::Automaton fa;
    EXPECT_TRUE(fa.isComplete());
    fa.addState(1);
    EXPECT_TRUE(fa.isComplete());
    fa.setStateInitial(1);
    EXPECT_TRUE(fa.isComplete());
    fa.addState(2);
    EXPECT_TRUE(fa.isComplete());
    fa.setStateFinal(2);
    EXPECT_TRUE(fa.isComplete());
    fa.addTransition(1,'e',1);
    EXPECT_FALSE(fa.isComplete());
    fa.addTransition(2,'e',1);
    EXPECT_TRUE(fa.isComplete());
    fa.addTransition(2,'e',2);
    EXPECT_TRUE(fa.isComplete());
}

//Automate vide
TEST(AutomatonTest, isComplete1) {
    fa::Automaton vide;
    EXPECT_TRUE(vide.isComplete());
}

//Automate complet
TEST_F(AutomatonTestFixture, isComplete2) {
    EXPECT_TRUE(faComplet.isComplete());
}

//Automate complet et deterministe
TEST_F(AutomatonTestFixture, isComplete3) {
    EXPECT_TRUE(faCompletEtDeter.isComplete());
}

//Automate deterministe A VERIF
TEST_F(AutomatonTestFixture, isComplete4) {
    EXPECT_TRUE(faDeterministe.isComplete());
}

//Automte non complet et non deterministe
TEST_F(AutomatonTestFixture, isComplete5) {
    EXPECT_FALSE(faNCompletNDeterministe.isComplete());
}

//Etat qui ne se suivent pas
TEST_F(AutomatonTestFixture, isComplete6) {
    EXPECT_FALSE(faEtatNonSuivi.isComplete());
}

//Etat négatifs
TEST_F(AutomatonTestFixture, isComplete7) {
    EXPECT_FALSE(faEtatNegatif.isComplete());
}

//Automate non accessible
TEST_F(AutomatonTestFixture, isComplete8) {
    EXPECT_FALSE(faNonAcces.isComplete());
}

//Automate non co accessible
TEST_F(AutomatonTestFixture, isComplete9) {
    EXPECT_FALSE(faNonCoAcces.isComplete());
}

//OK RELU 04/12/2018
TEST(AutomatonTest, makeComplete0) {
    fa::Automaton fa;
    fa.addState(1);
    fa.addState(2);
    fa.addState(3);
    fa.addTransition(1,'e',1);
    fa.addTransition(1,'f',1);
    fa.addTransition(2,'g',3);
    EXPECT_FALSE(fa.isComplete());
    fa.makeComplete();
    EXPECT_TRUE(fa.isComplete());
}

//OK RELU 04/12/2018
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

//OK RELU 04/12/2018
TEST(AutomatonTest, makeComplete2) {
    fa::Automaton fa;
    fa.addState(0);
    fa.addState(1);
    fa.setStateInitial(0);
    fa.setStateFinal(1);
    fa.addTransition(0, 'a', 0);
    fa.addTransition(0, 'b', 1);
    fa.addTransition(1, 'a', 1);
    fa.addTransition(1, 'b', 0);
    EXPECT_TRUE(fa.isComplete());
    fa.makeComplete();
    EXPECT_TRUE(fa.isComplete());
    EXPECT_EQ(fa.countStates(), 2u);
    EXPECT_EQ(fa.countTransitions(), 4u);
}


TEST_F(AutomatonTestFixture, makeComplete3) {
    faDeterministe.makeComplete();
    EXPECT_TRUE(faDeterministe.isComplete());
}

TEST_F(AutomatonTestFixture, makeComplete4) {
    faNCompletNDeterministe.makeComplete();
    EXPECT_TRUE(faNCompletNDeterministe.isComplete());
}

TEST_F(AutomatonTestFixture,makeComplete5) {
    faEtatNonSuivi.makeComplete();
    EXPECT_TRUE(faEtatNonSuivi.isComplete());
}

TEST_F(AutomatonTestFixture,makeComplete6) {
    faEtatNegatif.makeComplete();
    EXPECT_TRUE(faEtatNegatif.isComplete());
}

TEST_F(AutomatonTestFixture,makeComplete7) {
    faNonAcces.makeComplete();
    EXPECT_TRUE(faNonAcces.isComplete());
}

TEST_F(AutomatonTestFixture,makeComplete8) {
    faNonCoAcces.makeComplete();
    EXPECT_TRUE(faNonCoAcces.isComplete());
}

//Automate deja complet recomplété
TEST_F(AutomatonTestFixture,makeComplete9) {
    EXPECT_TRUE(faComplet.isComplete());
    faComplet.makeComplete();
    EXPECT_TRUE(faComplet.isComplete());
}

//OK RELU 04/12/2018
TEST(AutomatonTest, makeComplement0) {
    fa::Automaton fa;
    EXPECT_DEATH(fa.makeComplement(), "");
    EXPECT_EQ(fa.countStates(), 0u);
    EXPECT_EQ(fa.countTransitions(), 0u);
    EXPECT_EQ(fa.getAlphabetSize(), 0u);
}

TEST_F(AutomatonTestFixture, makeComplement1) {
    EXPECT_TRUE(faDeterministe.isStateInitial(1));
    EXPECT_FALSE(faDeterministe.isStateInitial(2));
    EXPECT_FALSE(faDeterministe.isStateFinal(1));
    EXPECT_FALSE(faDeterministe.isStateFinal(2));
    faDeterministe.makeComplement();
    EXPECT_TRUE(faDeterministe.isStateInitial(1));
    EXPECT_FALSE(faDeterministe.isStateInitial(2));
    EXPECT_TRUE(faDeterministe.isStateFinal(1));
    EXPECT_TRUE(faDeterministe.isStateFinal(2));
}


TEST_F(AutomatonTestFixture, makeComplement2) {
    EXPECT_TRUE(faCompletEtDeter.isDeterministic());
    faCompletEtDeter.makeComplement();
    EXPECT_TRUE(faCompletEtDeter.isStateInitial(1));
    EXPECT_FALSE(faCompletEtDeter.isStateInitial(2));
    EXPECT_TRUE(faCompletEtDeter.isStateFinal(1));
    EXPECT_FALSE(faCompletEtDeter.isStateFinal(2));
}

TEST_F(AutomatonTestFixture, makeComplement3) {
    EXPECT_TRUE(faDeterministeMultiFinal.isDeterministic());
    faDeterministeMultiFinal.makeComplement();
    EXPECT_TRUE(faDeterministeMultiFinal.isStateInitial(1));
    EXPECT_FALSE(faDeterministeMultiFinal.isStateInitial(2));
    EXPECT_FALSE(faDeterministeMultiFinal.isStateFinal(1));
    EXPECT_FALSE(faDeterministeMultiFinal.isStateFinal(2));
}

//OK RELU 04/12/2018
TEST(AutomatonTest, isLangageEmpty0) {
    fa::Automaton fa;
    EXPECT_TRUE(fa.isLanguageEmpty());
    fa.addState(1);
    EXPECT_TRUE(fa.isLanguageEmpty());
    fa.setStateInitial(1);
    EXPECT_TRUE(fa.isLanguageEmpty());
    fa.addState(2);
    fa.setStateFinal(2);
    EXPECT_TRUE(fa.isLanguageEmpty());
    fa.addTransition(1,'e',1);
    EXPECT_TRUE(fa.isLanguageEmpty());
    fa.addTransition(2,'f',2);
    EXPECT_TRUE(fa.isLanguageEmpty());
    fa.addTransition(2,'f',1);
    EXPECT_TRUE(fa.isLanguageEmpty());
    fa.addTransition(1,'e',2);
    EXPECT_FALSE(fa.isLanguageEmpty());
}

TEST(AutomatonTest, isLangageEmpty1) {
    fa::Automaton vide;
    EXPECT_TRUE(vide.isLanguageEmpty());
}

TEST_F(AutomatonTestFixture, isLangageEmpty2) {
    EXPECT_TRUE(faComplet.isLanguageEmpty());
    faComplet.setStateFinal(2);
    EXPECT_TRUE(faComplet.isLanguageEmpty());
    faComplet.setStateInitial(1);
    EXPECT_TRUE(faComplet.isLanguageEmpty());
}

TEST_F(AutomatonTestFixture, isLangageEmpty3) {
    EXPECT_TRUE(faDeterministe.isLanguageEmpty());
    faDeterministe.setStateFinal(2);
    EXPECT_FALSE(faDeterministe.isLanguageEmpty());
}

TEST_F(AutomatonTestFixture, isLangageEmpty4) {
    EXPECT_FALSE(faCompletEtDeter.isLanguageEmpty());
}

TEST_F(AutomatonTestFixture, isLangageEmpty5) {
    EXPECT_FALSE(faNCompletNDeterministe.isLanguageEmpty());
}

TEST_F(AutomatonTestFixture, isLangageEmpty6) {
    EXPECT_FALSE(faEtatNonSuivi.isLanguageEmpty());
}

TEST_F(AutomatonTestFixture, isLangageEmpty7) {
    EXPECT_FALSE(faEtatNegatif.isLanguageEmpty());
}

TEST_F(AutomatonTestFixture, isLangageEmpty8) {
    faNonAcces.setStateInitial(1);
    EXPECT_FALSE(faNonAcces.isLanguageEmpty());
}

TEST_F(AutomatonTestFixture, isLangageEmpty9) {
    EXPECT_TRUE(faNonCoAcces.isLanguageEmpty());
}

TEST_F(AutomatonTestFixture, isLangageEmpty10) {
	faNonCoAcces.setStateFinal(4);
    EXPECT_TRUE(faNonCoAcces.isLanguageEmpty());
}

TEST_F(AutomatonTestFixture, isLangageEmpty11) {
	faNonCoAcces.setStateInitial(0);
	faNonCoAcces.setStateFinal(4);
    EXPECT_TRUE(faNonCoAcces.isLanguageEmpty());
}

//OK RELU 04/12/2018
TEST(AutomatonTest, removeNonCoAccessibleStates0) {
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
    fa.removeNonCoAccessibleStates();
    EXPECT_EQ(fa.countStates(),0u);
    EXPECT_FALSE(fa.hasState(1));
    fa.addState(1);
    fa.addState(2);
    fa.addState(3);
    fa.addState(4);
    fa.addState(5);
    fa.setStateFinal(4);
    fa.addTransition(1,'e',2);
    fa.addTransition(1,'f',3);
    fa.removeNonCoAccessibleStates();
    EXPECT_EQ(fa.countStates(),1u);
    EXPECT_TRUE(fa.hasState(4));
}

//OK RELU 04/12/2018
TEST(AutomatonTest, removeNonCoAccessibleStates1) {
    fa::Automaton fa;
    fa.addState(0);
    fa.addState(1);
    fa.addState(2);
    fa.addState(3);
    fa.setStateInitial(0);
    fa.setStateFinal(2);
    fa.addTransition(0, 'a', 1);
    fa.addTransition(1, 'a', 2);
    fa.addTransition(1, 'a', 3);
    fa.addTransition(3, 'a', 3);
    EXPECT_EQ(fa.countTransitions(), 4u);
    EXPECT_EQ(fa.countStates(), 4u);
    EXPECT_TRUE(fa.hasState(3));
    fa.removeNonCoAccessibleStates();
    EXPECT_FALSE(fa.hasState(3));
    EXPECT_EQ(fa.countTransitions(), 2u);
    EXPECT_EQ(fa.countStates(), 3u);
}

//OK RELU 04/12/2018
TEST(AutomatonTest, removeNonCoAccessibleStates2) {
    fa::Automaton fa;
    fa.addState(0);
    fa.addState(1);
    fa.addState(2);
    fa.addState(3);
    fa.setStateInitial(0);
    fa.setStateFinal(2);
    fa.addTransition(0, 'a', 1);
    fa.addTransition(1, 'a', 2);
    fa.addTransition(1, 'a', 3);
    EXPECT_EQ(fa.countTransitions(), 3u);
    EXPECT_EQ(fa.countStates(), 4u);
    EXPECT_TRUE(fa.hasState(3));
    fa.removeNonCoAccessibleStates();
    EXPECT_FALSE(fa.hasState(3));
    EXPECT_EQ(fa.countTransitions(), 2u);
    EXPECT_EQ(fa.countStates(), 3u);
}

//OK RELU 04/12/2018
TEST(AutomatonTest, removeNonCoAccessibleStates3) {
    fa::Automaton fa;
    fa.addState(0);
    fa.addState(1);
    fa.addState(2);
    fa.addState(3);
    EXPECT_EQ(fa.countTransitions(), 0u);
    EXPECT_EQ(fa.countStates(), 4u);
    fa.removeNonCoAccessibleStates();
    EXPECT_EQ(fa.countTransitions(), 0u);
    EXPECT_EQ(fa.countStates(), 0u);
}

//OK RELU 04/12/2018
TEST(AutomatonTest, removeNonCoAccessibleStates4) {
    fa::Automaton fa;
    fa.addState(0);
    fa.setStateInitial(0);
    fa.addState(1);
    fa.addState(2);
    fa.addState(3);
    fa.setStateFinal(3);
    EXPECT_EQ(fa.countTransitions(), 0u);
    EXPECT_EQ(fa.countStates(), 4u);
    fa.removeNonCoAccessibleStates();
    EXPECT_EQ(fa.countTransitions(), 0u);
    EXPECT_EQ(fa.countStates(), 1u);
    EXPECT_TRUE(fa.hasState(3));
    EXPECT_TRUE(fa.isStateFinal(3));
}

TEST_F(AutomatonTestFixture, removeNonCoAccessibleStates5) {
    faNonAcces.setStateInitial(1);
    faNonAcces.removeNonCoAccessibleStates();
    EXPECT_FALSE(faNonAcces.hasState(0));
    EXPECT_TRUE(faNonAcces.hasState(1));
    EXPECT_TRUE(faNonAcces.hasState(2));
    EXPECT_TRUE(faNonAcces.hasState(3));
    EXPECT_FALSE(faNonAcces.hasState(4));
    EXPECT_DEATH(faNonAcces.hasTransition(2, 'e', 4),"");
    EXPECT_DEATH(faNonAcces.hasTransition(0,'f',1),"");
    EXPECT_TRUE(faNonAcces.hasTransition(2,'f',3));
    EXPECT_TRUE(faNonAcces.hasTransition(1,'e',2));
}


//OK RELU 04/12/2018
TEST(AutomatonTest, removeNonAccessibleStates0) {
    fa::Automaton fa;
    fa.addState(1);
    fa.addState(2);
    fa.removeNonAccessibleStates();
    EXPECT_EQ(fa.countStates(),0u);
    fa.addState(1);
    fa.addState(2);
    fa.addState(3);
    fa.addState(4);
    fa.setStateFinal(4);
    fa.removeNonAccessibleStates();
    EXPECT_EQ(fa.countStates(),0u);
    EXPECT_FALSE(fa.hasState(4));
    fa.addState(0);
    fa.addState(1);
    fa.addState(2);
    fa.addState(3);
    fa.addState(4);
    fa.setStateInitial(0);
    fa.setStateFinal(3);
    fa.addTransition(0,'f',1);
    fa.addTransition(4,'e',2);
    fa.addTransition(1,'e',2);
    fa.addTransition(2,'f',3);
    fa.removeNonAccessibleStates();
    EXPECT_TRUE(fa.hasState(2));
    EXPECT_EQ(fa.countStates(),4u);
    EXPECT_TRUE(fa.hasState(0));
}

//OK RELU 04/12/2018
TEST(AutomatonTest, removeNonAccessibleStates1) {
    fa::Automaton fa;
    fa.addState(0);
    fa.addState(1);
    fa.addState(2);
    fa.addState(3);
    fa.setStateInitial(0);
    fa.setStateFinal(2);
    fa.addTransition(0, 'a', 1);
    fa.addTransition(1, 'a', 2);
    fa.addTransition(3, 'a', 1);
    fa.addTransition(3, 'a', 3);
    EXPECT_EQ(fa.countTransitions(), 4u);
    EXPECT_EQ(fa.countStates(), 4u);
    EXPECT_TRUE(fa.hasState(3));
    fa.removeNonAccessibleStates();
    EXPECT_FALSE(fa.hasState(3));
    EXPECT_EQ(fa.countTransitions(), 2u);
    EXPECT_EQ(fa.countStates(), 3u);
}

//OK RELU 04/12/2018
TEST(AutomatonTest, removeNonAccessibleStates2) {
    fa::Automaton fa;
    fa.addState(0);
    fa.addState(1);
    fa.addState(2);
    fa.addState(3);
    fa.setStateInitial(0);
    fa.setStateFinal(2);
    fa.addTransition(0, 'a', 1);
    fa.addTransition(1, 'a', 2);
    fa.addTransition(3, 'a', 1);
    EXPECT_EQ(fa.countTransitions(), 3u);
    EXPECT_EQ(fa.countStates(), 4u);
    EXPECT_TRUE(fa.hasState(3));
    fa.removeNonAccessibleStates();
    EXPECT_FALSE(fa.hasState(3));
    EXPECT_EQ(fa.countTransitions(), 2u);
    EXPECT_EQ(fa.countStates(), 3u);
}

//OK RELU 04/12/2018
TEST(AutomatonTest, removeNonAccessibleStates3) {
    fa::Automaton fa;
    fa.addState(0);
    fa.addState(1);
    fa.addState(2);
    fa.addState(3);
    EXPECT_EQ(fa.countTransitions(), 0u);
    EXPECT_EQ(fa.countStates(), 4u);
    fa.removeNonAccessibleStates();
    EXPECT_EQ(fa.countTransitions(), 0u);
    EXPECT_EQ(fa.countStates(), 0u);
}

//OK RELU 04/12/2018
TEST(AutomatonTest, removeNonAccessibleStates4) {
    fa::Automaton fa;
    fa.addState(0);
    fa.setStateInitial(0);
    fa.addState(1);
    fa.addState(2);
    fa.addState(3);
    fa.setStateFinal(3);
    EXPECT_EQ(fa.countTransitions(), 0u);
    EXPECT_EQ(fa.countStates(), 4u);
    fa.removeNonAccessibleStates();
    EXPECT_EQ(fa.countTransitions(), 0u);
    EXPECT_TRUE(fa.hasState(0));
    EXPECT_TRUE(fa.isStateInitial(0));
    EXPECT_EQ(fa.countStates(), 1u);
}

//OK RELU 10/12/2018
TEST_F(AutomatonTestFixture,removeNonAccessibleStates5) {
    faNonCoAcces.setStateInitial(1);
    faNonCoAcces.removeNonAccessibleStates();
    EXPECT_TRUE(faNonCoAcces.hasState(0));
    EXPECT_TRUE(faNonCoAcces.hasState(1));
    EXPECT_TRUE(faNonCoAcces.hasState(2));
    EXPECT_TRUE(faNonCoAcces.hasState(3));
    EXPECT_FALSE(faNonCoAcces.hasState(4));
    EXPECT_DEATH(faNonCoAcces.hasTransition(4,'e',2),"");
    EXPECT_FALSE(faNonCoAcces.hasTransition(0,'f',1));
    EXPECT_TRUE(faNonCoAcces.hasTransition(1,'e',2));
    EXPECT_TRUE(faNonCoAcces.hasTransition(2,'f',3));
}

TEST(AutomatonTest, createProduct0) {
    fa::Automaton lhs;
    fa::Automaton rhs;

    lhs.addState(0);
    lhs.addState(1);
    lhs.setStateInitial(0);
    lhs.setStateFinal(1);
    lhs.addTransition(0, 'a', 1);
    lhs.addTransition(1, 'a', 1);
    lhs.addTransition(1, 'b', 1);

    rhs.addState(0);
    rhs.addState(1);
    rhs.setStateInitial(0);
    rhs.setStateFinal(1);
    rhs.addTransition(0, 'a', 0);
    rhs.addTransition(0, 'b', 1);
    rhs.addTransition(1, 'a', 0);
    rhs.addTransition(1, 'b', 1);
    
    
    EXPECT_TRUE(lhs.match("a"));
    EXPECT_TRUE(lhs.match("ab"));
    EXPECT_TRUE(lhs.match("abbbbbb"));
    EXPECT_TRUE(lhs.match("aaaaaaa"));
    EXPECT_TRUE(lhs.match("ababab"));
    
	EXPECT_FALSE(lhs.match(""));
	EXPECT_FALSE(lhs.match("b"));
	EXPECT_FALSE(lhs.match("bbb"));
	EXPECT_FALSE(lhs.match("edf"));
	EXPECT_FALSE(lhs.match("baab"));

	
	EXPECT_TRUE(rhs.match("b"));
	EXPECT_TRUE(rhs.match("ab"));
	EXPECT_TRUE(rhs.match("aab"));
	EXPECT_TRUE(rhs.match("bb"));
	EXPECT_TRUE(rhs.match("bbbbbbbbbb"));
	EXPECT_TRUE(rhs.match("aaabbb"));
	EXPECT_TRUE(rhs.match("aaab"));
	EXPECT_TRUE(rhs.match("bab"));
	EXPECT_TRUE(rhs.match("aaaabbbbab"));
	
	EXPECT_FALSE(rhs.match(""));
	EXPECT_FALSE(rhs.match("a"));
	EXPECT_FALSE(rhs.match("aaaaa"));
	EXPECT_FALSE(rhs.match("aaaaaba"));
	EXPECT_FALSE(rhs.match("aaaaabbbbba"));
	EXPECT_FALSE(rhs.match("edf"));


    fa::Automaton a =  fa::Automaton::createProduct(lhs, rhs);


	EXPECT_TRUE(a.match("ab"));
	EXPECT_TRUE(a.match("aaaaaab"));
	EXPECT_TRUE(a.match("abbbbbbbb"));
	EXPECT_TRUE(a.match("aaaaaaabbbbbbb"));
	EXPECT_TRUE(a.match("abab"));
	EXPECT_TRUE(a.match("aaaabbbbaabb"));
	EXPECT_TRUE(a.match("abbbbab"));
	
	EXPECT_FALSE(a.match(""));
	EXPECT_FALSE(a.match("a"));
	EXPECT_FALSE(a.match("b"));
	EXPECT_FALSE(a.match("aaaaaaaa"));
	EXPECT_FALSE(a.match("bbbbbbbb"));
	EXPECT_FALSE(a.match("bbbaaa"));
	EXPECT_FALSE(a.match("aabbba"));
	EXPECT_FALSE(a.match("ababa"));	
}

TEST(AutomatonTest, createProduct1) {
	fa::Automaton lhs;
	fa::Automaton rhs;
	
	lhs.addState(0);
	lhs.addState(1);
	lhs.addState(2);
	lhs.setStateInitial(0);
	lhs.setStateFinal(2);
	lhs.addTransition(0,'b',0);
	lhs.addTransition(0,'a',1);
	lhs.addTransition(1,'b',1);
	lhs.addTransition(1,'a',2);
	lhs.addTransition(2,'b',2);
	lhs.addTransition(2,'a',1);
	
	rhs.addState(0);
	rhs.addState(1);
	rhs.addState(2);
	rhs.addState(3);
	rhs.setStateInitial(0);
	rhs.setStateFinal(3);
	rhs.addTransition(0,'b',0);
	rhs.addTransition(0,'a',1);
	rhs.addTransition(1,'b',1);
	rhs.addTransition(1,'a',2);
	rhs.addTransition(2,'b',2);
	rhs.addTransition(2,'a',3);
	rhs.addTransition(3,'b',3);
	rhs.addTransition(3,'a',1);
	
	EXPECT_TRUE(lhs.match("bbbbbabbbabbbbb"));
	EXPECT_TRUE(lhs.match("aaaabbbb"));
	EXPECT_TRUE(lhs.match("aaaabaabbb"));
	EXPECT_TRUE(lhs.match("aaaabbbbaabbb"));
	EXPECT_TRUE(lhs.match("aaaaaa"));
	EXPECT_TRUE(lhs.match("babab"));
	EXPECT_TRUE(lhs.match("aa"));
	EXPECT_FALSE(lhs.match("bbb"));
	EXPECT_FALSE(lhs.match("babb"));
	EXPECT_FALSE(lhs.match("bbab"));
	EXPECT_FALSE(lhs.match("bbba"));
	EXPECT_FALSE(lhs.match("bbbbbbbbbbbb"));
	EXPECT_FALSE(lhs.match("b"));
	
	EXPECT_TRUE(rhs.match("bbbbbabbbabbabbb"));
	EXPECT_TRUE(rhs.match("aaabbbb"));
	EXPECT_TRUE(rhs.match("aaaaaabbbb"));
	EXPECT_TRUE(rhs.match("aaaabaabbb"));
	EXPECT_TRUE(rhs.match("aaaabbbbaabbb"));
	EXPECT_TRUE(rhs.match("aaaaaa"));
	EXPECT_TRUE(rhs.match("bababab"));
	EXPECT_TRUE(rhs.match("aaa"));
	EXPECT_FALSE(rhs.match("aa"));
	EXPECT_FALSE(rhs.match("bbb"));
	EXPECT_FALSE(rhs.match("babb"));
	EXPECT_FALSE(rhs.match("bbab"));
	EXPECT_FALSE(rhs.match("bbba"));
	EXPECT_FALSE(rhs.match("bbbbbbbbbbbb"));
	EXPECT_FALSE(rhs.match("b"));
	
	fa::Automaton ret =  fa::Automaton::createProduct(lhs, rhs);
	
	EXPECT_TRUE(ret.match("bbbbbabbbabbabbbabbabbbbab"));
	EXPECT_TRUE(ret.match("aaaabaabbb"));
	EXPECT_TRUE(ret.match("aaaabaabbb"));
	EXPECT_TRUE(ret.match("aaaabbbbaabbb"));
	EXPECT_TRUE(ret.match("aaaaaa"));
	EXPECT_FALSE(ret.match("bbbbbbbbbbbb"));
	EXPECT_FALSE(ret.match("b"));
	EXPECT_FALSE(ret.match("aa"));
	EXPECT_FALSE(ret.match("aaa"));
	EXPECT_FALSE(ret.match("aaaa"));
	EXPECT_FALSE(ret.match("aaaaa"));
	EXPECT_FALSE(ret.match("aaaabbbb"));
	EXPECT_FALSE(ret.match("bbb"));
	EXPECT_FALSE(ret.match("babb"));
	EXPECT_FALSE(ret.match("bbab"));
	EXPECT_FALSE(ret.match("bbba"));
}

TEST(AutomatonTest, createProduct2) {
	fa::Automaton lhs;
	fa::Automaton rhs;
	
	lhs.addState(0);
	lhs.addState(1);
	lhs.addState(2);
	lhs.setStateInitial(0);
	lhs.setStateFinal(2);
	lhs.addTransition(0,'b',0);
	lhs.addTransition(0,'a',1);
	lhs.addTransition(1,'b',1);
	lhs.addTransition(1,'a',2);
	lhs.addTransition(2,'b',2);
	lhs.addTransition(2,'a',1);
	
	fa::Automaton ret =  fa::Automaton::createProduct(lhs, rhs);
	
	EXPECT_EQ(ret.countTransitions(),0u);
	EXPECT_EQ(ret.countStates(),0u);
	EXPECT_EQ(ret.getAlphabetSize(),0u);
	EXPECT_FALSE(ret.match("a"));
	EXPECT_FALSE(ret.match("aaa"));
	EXPECT_FALSE(ret.match("aaabbbba"));
	EXPECT_FALSE(ret.match("b"));
	EXPECT_FALSE(ret.match("bbbbaaaaabbbbb"));
	EXPECT_FALSE(ret.match("bfezuybezkfez"));
}

TEST(AutomatonTest, createProduct3) {
	fa::Automaton lhs;
	fa::Automaton rhs;
	
	rhs.addState(0);
	rhs.addState(1);
	rhs.addState(2);
	rhs.setStateInitial(0);
	rhs.setStateFinal(2);
	rhs.addTransition(0,'b',0);
	rhs.addTransition(0,'a',1);
	rhs.addTransition(1,'b',1);
	rhs.addTransition(1,'a',2);
	rhs.addTransition(2,'b',2);
	rhs.addTransition(2,'a',1);
	
	fa::Automaton ret =  fa::Automaton::createProduct(lhs, rhs);
	
	EXPECT_EQ(ret.countTransitions(),0u);
	EXPECT_EQ(ret.countStates(),0u);
	EXPECT_EQ(ret.getAlphabetSize(),0u);
	EXPECT_FALSE(ret.match("a"));
	EXPECT_FALSE(ret.match("aaa"));
	EXPECT_FALSE(ret.match("aaabbbba"));
	EXPECT_FALSE(ret.match("b"));
	EXPECT_FALSE(ret.match("bbbbaaaaabbbbb"));
	EXPECT_FALSE(ret.match("bfezuybezkfez"));
}

TEST(AutomatonTest, hasEmptyIntersectionWith0) {
    fa::Automaton fa;
    fa::Automaton automata;

    fa.addState(0);
    fa.addState(1);
    fa.setStateInitial(0);
    fa.setStateFinal(1);
    fa.addTransition(0, 'a', 1);
    fa.addTransition(1, 'a', 1);
    fa.addTransition(1, 'b', 1);

    automata.addState(0);
    automata.addState(1);
    automata.setStateInitial(0);
    automata.setStateFinal(1);
    automata.addTransition(0, 'a', 0);
    automata.addTransition(0, 'b', 1);
    automata.addTransition(1, 'a', 0);
    automata.addTransition(1, 'b', 1);

    EXPECT_FALSE(fa.hasEmptyIntersectionWith(automata));
}

TEST(AutomatonTest, hasEmptyIntersectionWith1) {
	fa::Automaton lhs;
	fa::Automaton rhs;
	
	lhs.addState(0);
	lhs.addState(1);
	lhs.addState(2);
	lhs.setStateInitial(0);
	lhs.setStateFinal(2);
	lhs.addTransition(0,'b',0);
	lhs.addTransition(0,'a',1);
	lhs.addTransition(1,'b',1);
	lhs.addTransition(1,'a',2);
	lhs.addTransition(2,'b',2);
	lhs.addTransition(2,'a',1);
	
	EXPECT_TRUE(lhs.hasEmptyIntersectionWith(rhs));
}



TEST(AutomatonTest, readString0){
    fa::Automaton fa;
    fa.addState(0);
    fa.addState(1);
    fa.setStateInitial(0);
    fa.setStateFinal(1);
    fa.addTransition(0, 'a', 1);
    fa.addTransition(1, 'a', 1);
    fa.addTransition(1, 'b', 1);
    std::set<int> resultat = fa.readString("aaabb");
    EXPECT_TRUE(resultat.find(0) != resultat.end());
    EXPECT_TRUE(resultat.find(1) != resultat.end());
    EXPECT_EQ(resultat.size(), 2u);
}

TEST(AutomatonTest, readString1){
    fa::Automaton fa;
    fa.addState(0);
    fa.addState(1);
    fa.setStateInitial(0);
    fa.setStateFinal(1);
    fa.addTransition(0, 'a', 1);
    fa.addTransition(1, 'a', 1);
    fa.addTransition(1, 'b', 1);
	std::set<int> res = fa.readString("");
    EXPECT_TRUE(res.find(0) != res.end());
    EXPECT_FALSE(res.find(1) != res.end());
}



TEST(AutomatonTest, match0) {
    fa::Automaton fa;

    fa.addState(0);
    fa.addState(1);
    fa.setStateInitial(0);
    fa.setStateFinal(1);
    fa.addTransition(0, 'a', 1);
    fa.addTransition(1, 'a', 1);
    fa.addTransition(1, 'b', 1);

    EXPECT_TRUE(fa.match("a"));
    EXPECT_TRUE(fa.match("ab"));
    EXPECT_TRUE(fa.match("abbbbbb"));
    EXPECT_TRUE(fa.match("aaaaaaa"));
    EXPECT_TRUE(fa.match("ababab"));
    
	EXPECT_FALSE(fa.match(""));
	EXPECT_FALSE(fa.match("b"));
	EXPECT_FALSE(fa.match("bbb"));
	EXPECT_FALSE(fa.match("edf"));
	EXPECT_FALSE(fa.match("baab"));
}

TEST(AutomatonTest, match1) {
    fa::Automaton fa;

	EXPECT_FALSE(fa.match("aaabb"));
    EXPECT_FALSE(fa.match(""));
    EXPECT_FALSE(fa.match("e"));
	
    fa.addState(0);
    fa.addState(1);
    fa.setStateInitial(0);
    fa.setStateFinal(1);
    fa.addTransition(0, 'a', 1);
    fa.addTransition(1, 'a', 1);
    fa.addTransition(1, 'b', 1);

    EXPECT_TRUE(fa.match("aaabb"));
    EXPECT_FALSE(fa.match(""));
    EXPECT_FALSE(fa.match("e"));
}

TEST(AutomatonTest, match2) {
	
	fa::Automaton rhs;
	
	rhs.addState(0);
    rhs.addState(1);
    rhs.setStateInitial(0);
    rhs.setStateFinal(1);
    rhs.addTransition(0, 'a', 0);
    rhs.addTransition(0, 'b', 1);
    rhs.addTransition(1, 'a', 0);
    rhs.addTransition(1, 'b', 1);
	
	
	EXPECT_TRUE(rhs.match("b"));
	EXPECT_TRUE(rhs.match("ab"));
	EXPECT_TRUE(rhs.match("aab"));
	EXPECT_TRUE(rhs.match("bb"));
	EXPECT_TRUE(rhs.match("bbbbbbbbbb"));
	EXPECT_TRUE(rhs.match("aaabbb"));
	EXPECT_TRUE(rhs.match("aaab"));
	EXPECT_TRUE(rhs.match("bab"));
	EXPECT_TRUE(rhs.match("aaaabbbbab"));
	
	EXPECT_FALSE(rhs.match(""));
	EXPECT_FALSE(rhs.match("a"));
	EXPECT_FALSE(rhs.match("aaaaa"));
	EXPECT_FALSE(rhs.match("aaaaaba"));
	EXPECT_FALSE(rhs.match("aaaaabbbbba"));
	EXPECT_FALSE(rhs.match("edf"));
}

//DETERMINISTE

TEST(AutomatonTest, createDeterministic0) {
    fa::Automaton fa;

    fa.addState(0);
    fa.addState(1);
    fa.addState(2);
    fa.addState(3);
    fa.setStateInitial(0);
    fa.setStateFinal(3);

    fa.addTransition(0, 'b', 1);
	fa.addTransition(0, 'b', 0);
	fa.addTransition(0, 'a', 0);
	fa.addTransition(0, 'a', 2);
	
	fa.addTransition(1, 'b', 3);
	fa.addTransition(2, 'a', 3);
	
	fa.addTransition(3, 'b', 3);
	fa.addTransition(3, 'a', 3);
	
	EXPECT_TRUE(fa.match("aaaaabbbba"));
	EXPECT_TRUE(fa.match("aaaaabbbbaaa"));
	EXPECT_TRUE(fa.match("bbb"));
	EXPECT_TRUE(fa.match("bbaaaaaaaaaaab"));
	EXPECT_TRUE(fa.match("aaa"));
	EXPECT_TRUE(fa.match("aabbbbbbbbbbbbbba"));
	EXPECT_TRUE(fa.match("aabbbbbbbbbbbbbbab"));
	EXPECT_TRUE(fa.match("aabba"));
	EXPECT_TRUE(fa.match("aa"));
	EXPECT_TRUE(fa.match("bb"));
	
	EXPECT_FALSE(fa.match(""));
	EXPECT_FALSE(fa.match("a"));
	EXPECT_FALSE(fa.match("b"));
	EXPECT_FALSE(fa.match("cd"));
	EXPECT_FALSE(fa.match("aaaaabbbbbbbbbbbcdb"));
	
	
	EXPECT_FALSE(fa.isDeterministic());
    fa::Automaton automata = fa::Automaton::createDeterministic(fa);
	EXPECT_TRUE(automata.isDeterministic());

	EXPECT_TRUE(automata.match("aaaaabbbba"));
	EXPECT_TRUE(automata.match("aaaaabbbbaaa"));
	EXPECT_TRUE(automata.match("bbb"));
	EXPECT_TRUE(automata.match("bbaaaaaaaaaaab"));
	EXPECT_TRUE(automata.match("aaa"));
	EXPECT_TRUE(automata.match("aabbbbbbbbbbbbbba"));
	EXPECT_TRUE(automata.match("aabbbbbbbbbbbbbbab"));
	EXPECT_TRUE(automata.match("aabba"));
	EXPECT_TRUE(automata.match("aa"));
	EXPECT_TRUE(automata.match("bb"));
	
	EXPECT_FALSE(automata.match(""));
	EXPECT_FALSE(automata.match("a"));
	EXPECT_FALSE(automata.match("b"));
	EXPECT_FALSE(automata.match("cd"));
	EXPECT_FALSE(automata.match("aaaaabbbbbbbbbbbcdb"));
}

TEST(AutomatonTest, createDeterministic1) {
    fa::Automaton fa;

    fa.addState(0);
    fa.addState(1);
    fa.addState(2);
    fa.addState(3);
    fa.setStateInitial(0);
    fa.setStateFinal(3);

    fa.addTransition(0, 'b', 1);
	fa.addTransition(0, 'b', 0);
	fa.addTransition(0, 'a', 0);
	fa.addTransition(0, 'a', 2);
	
	fa.addTransition(1, 'b', 3);
	fa.addTransition(2, 'a', 3);
	
	fa.addTransition(3, 'b', 3);
	fa.addTransition(3, 'a', 3);
	
	EXPECT_FALSE(fa.isDeterministic());
	
	fa::Automaton automata = fa::Automaton::createDeterministic(fa);
	EXPECT_TRUE(automata.isDeterministic());
}

TEST_F(AutomatonTestFixture, createDeterministic2) {
	EXPECT_TRUE(faCompletEtDeter.match("aab"));
	EXPECT_TRUE(faCompletEtDeter.match("a"));
	EXPECT_TRUE(faCompletEtDeter.match("b"));
	EXPECT_TRUE(faCompletEtDeter.match("aaaaabbbb"));
	
	EXPECT_FALSE(faCompletEtDeter.match(""));
	EXPECT_FALSE(faCompletEtDeter.match("aa"));
	EXPECT_FALSE(faCompletEtDeter.match("efg"));
	
	EXPECT_TRUE(faCompletEtDeter.isDeterministic());
	fa::Automaton automata = fa::Automaton::createDeterministic(faCompletEtDeter);
	EXPECT_TRUE(automata.isDeterministic());
	
	EXPECT_TRUE(automata.match("aab"));
	EXPECT_TRUE(automata.match("a"));
	EXPECT_TRUE(automata.match("b"));
	EXPECT_TRUE(automata.match("aaaaabbbb"));
	
	EXPECT_FALSE(automata.match(""));
	EXPECT_FALSE(automata.match("aa"));
	EXPECT_FALSE(automata.match("efg"));
}

TEST_F(AutomatonTestFixture, createDeterministic3) {
	EXPECT_TRUE(faNCompletNDeterministe.match("efe"));
	EXPECT_TRUE(faNCompletNDeterministe.match("e"));
	EXPECT_TRUE(faNCompletNDeterministe.match("fe"));
	EXPECT_TRUE(faNCompletNDeterministe.match("eeeeeeeee"));
	EXPECT_TRUE(faNCompletNDeterministe.match("ffffffffffe"));
	
	EXPECT_FALSE(faNCompletNDeterministe.match("ef"));
	EXPECT_FALSE(faNCompletNDeterministe.match("f"));
	EXPECT_FALSE(faNCompletNDeterministe.match(""));
	EXPECT_FALSE(faNCompletNDeterministe.match("fffffffffffffff"));
	
	EXPECT_FALSE(faNCompletNDeterministe.isDeterministic());
	
	fa::Automaton automata = fa::Automaton::createDeterministic(faNCompletNDeterministe);
	
	EXPECT_TRUE(automata.isDeterministic());
	
	EXPECT_TRUE(automata.match("efe"));
	EXPECT_TRUE(automata.match("e"));
	EXPECT_TRUE(automata.match("fe"));
	EXPECT_TRUE(automata.match("eeeeeeeee"));
	EXPECT_TRUE(automata.match("ffffffffffe"));
	
	EXPECT_FALSE(automata.match("ef"));
	EXPECT_FALSE(automata.match("f"));
	EXPECT_FALSE(automata.match(""));
	EXPECT_FALSE(automata.match("fffffffffffffff"));
}

TEST(AutomatonTest, createDeterministic4) {
	fa::Automaton vide;
	
	EXPECT_FALSE(vide.isDeterministic());
	fa::Automaton automata = fa::Automaton::createDeterministic(vide);
	EXPECT_FALSE(automata.isDeterministic());
}

TEST(AutomatonTest, createDeterministic5) {
	fa::Automaton fa;
	fa.addState(0);
    fa.setStateInitial(0);
    fa.addState(1);
    fa.setStateFinal(1);
    fa.addState(3);
    fa.addTransition(0, 'e', 1);
    fa.addTransition(1, 'e', 0);
	
	EXPECT_TRUE(fa.match("e"));
	EXPECT_TRUE(fa.match("eee"));
	
	EXPECT_FALSE(fa.match(""));
	EXPECT_FALSE(fa.match("ee"));
	EXPECT_FALSE(fa.match("fef"));
	EXPECT_FALSE(fa.match("abc"));
	
	EXPECT_TRUE(fa.isDeterministic());
	fa::Automaton automata = fa::Automaton::createDeterministic(fa);
	EXPECT_TRUE(automata.isDeterministic());
	
	EXPECT_TRUE(automata.match("e"));
	EXPECT_TRUE(automata.match("eee"));
	
	EXPECT_FALSE(automata.match(""));
	EXPECT_FALSE(automata.match("ee"));
	EXPECT_FALSE(automata.match("fef"));
	EXPECT_FALSE(automata.match("abc"));
}


TEST(AutomatonTest, createDeterministic6) {
	fa::Automaton fa;
	fa.addState(0);
    fa.setStateInitial(0);
    fa.addState(1);
    fa.setStateInitial(1);
    fa.addState(2);
    fa.setStateFinal(2);
    fa.addState(3);
    fa.addTransition(0, 'e', 1);
    fa.addTransition(0, 'e', 2);
    fa.addTransition(2, 'e', 1);
    fa.addTransition(1, 'f', 2);
    fa.addTransition(2, 'f', 2);
    
	
	EXPECT_TRUE(fa.match("e"));
	EXPECT_TRUE(fa.match("f"));
	EXPECT_TRUE(fa.match("ffffffff"));
	EXPECT_TRUE(fa.match("ef"));
	EXPECT_TRUE(fa.match("efffffff"));
	EXPECT_TRUE(fa.match("eef"));
	EXPECT_TRUE(fa.match("eeffffff"));
	EXPECT_TRUE(fa.match("efeff"));
	EXPECT_TRUE(fa.match("eeffffef"));
	EXPECT_TRUE(fa.match("fef"));
	
	EXPECT_FALSE(fa.match(""));
	EXPECT_FALSE(fa.match("ee"));
	EXPECT_FALSE(fa.match("abc"));
	EXPECT_FALSE(fa.match("fe"));
	EXPECT_FALSE(fa.match("eeeeeee"));
	
	EXPECT_FALSE(fa.isDeterministic());
	fa::Automaton automata = fa::Automaton::createDeterministic(fa);
	EXPECT_TRUE(automata.isDeterministic());
	
	EXPECT_TRUE(automata.match("e"));
	EXPECT_TRUE(automata.match("ef"));
	EXPECT_TRUE(automata.match("f"));
	EXPECT_TRUE(automata.match("ffffff"));
	EXPECT_TRUE(automata.match("effffffff"));
	EXPECT_TRUE(automata.match("fef"));
	EXPECT_TRUE(automata.match("efef"));
	
	EXPECT_FALSE(automata.match("eee"));
	EXPECT_FALSE(automata.match(""));
	EXPECT_FALSE(automata.match("ee"));
	EXPECT_FALSE(automata.match("abc"));
	EXPECT_FALSE(automata.match("fe"));
	EXPECT_FALSE(automata.match("efe"));
	EXPECT_FALSE(automata.match("efefe"));
}



//ISINCLUEDIN

TEST(AutomatonTest, isIncludedIn0) {
	fa::Automaton fa;
	fa::Automaton automata;
	
	fa.addState(0);
	fa.addState(1);
	fa.setStateInitial(0);
	fa.setStateFinal(1);
	fa.addTransition(0, 'a', 1);
	fa.addTransition(0, 'b', 1);
	fa.addTransition(0, 'c', 1);
	fa.addTransition(1, 'a', 1);
	fa.addTransition(1, 'b', 1);
	
	EXPECT_TRUE(fa.match("a"));
	EXPECT_TRUE(fa.match("aa"));
	EXPECT_TRUE(fa.match("b"));
	EXPECT_TRUE(fa.match("bb"));
	EXPECT_TRUE(fa.match("c"));
	EXPECT_TRUE(fa.match("abbbb"));
	EXPECT_TRUE(fa.match("baaaaa"));
	EXPECT_TRUE(fa.match("aaaabbbb"));
	EXPECT_TRUE(fa.match("bbbbbaaaaa"));
	EXPECT_TRUE(fa.match("caaaaaaaabbbbb"));
	EXPECT_TRUE(fa.match("cab"));
	EXPECT_TRUE(fa.match("cba"));
	
	EXPECT_FALSE(fa.match(""));
	EXPECT_FALSE(fa.match("edf"));
	EXPECT_FALSE(fa.match("cc"));
	EXPECT_FALSE(fa.match("acb"));
	
	
	automata.addState(0);
	automata.setStateInitial(0);
	automata.setStateFinal(0);
	automata.addTransition(0, 'a', 0);
	automata.addTransition(0, 'b', 0);
	
	EXPECT_TRUE(automata.match("a"));
	EXPECT_TRUE(automata.match("aa"));
	EXPECT_TRUE(automata.match("b"));
	EXPECT_TRUE(automata.match("bb"));
	EXPECT_TRUE(automata.match("abbbb"));
	EXPECT_TRUE(automata.match("baaaaa"));
	EXPECT_TRUE(automata.match("aaaabbbb"));
	EXPECT_TRUE(automata.match("bbbbbaaaaa"));
	EXPECT_TRUE(automata.match(""));
	
	EXPECT_FALSE(automata.match("edf"));
	EXPECT_FALSE(automata.match("c"));
	EXPECT_FALSE(automata.match("caaaaaaaabbbbb"));
	EXPECT_FALSE(automata.match("cab"));
	EXPECT_FALSE(automata.match("cba"));
	EXPECT_FALSE(automata.match("cc"));
	EXPECT_FALSE(automata.match("acb"));
	
	EXPECT_DEATH(automata.isIncludedIn(fa), "");
	EXPECT_FALSE(fa.isIncludedIn(automata));
}

TEST(AutomatonTest, isIncludedIn1) {
	fa::Automaton fa;
	fa::Automaton automata;
	
	fa.addState(0);
	fa.setStateInitial(0);
	fa.setStateFinal(0);
	
	automata.addState(0);
	automata.setStateInitial(0);
	automata.setStateFinal(0);
	automata.addTransition(0,'a',0);
	automata.addTransition(0,'b',0);
	
	automata.makeComplement();
	
	EXPECT_TRUE(automata.hasEmptyIntersectionWith(fa));
}

//CREATE MINIMAL MOORE

 TEST(AutomatonTest, createMinimalMoore0) {
    fa::Automaton fa;

    fa.addState(0);
    fa.addState(1);
    fa.addState(2);
    fa.addState(3);
    fa.addState(4);
    fa.addState(5);
    fa.setStateInitial(0);
    fa.setStateFinal(3);
    fa.setStateFinal(4);

    fa.addTransition(0, 'a', 1);
    fa.addTransition(0, 'b', 2);
    fa.addTransition(1, 'b', 3);
    fa.addTransition(1, 'a', 2);

    fa.addTransition(2, 'b', 4);
    fa.addTransition(2, 'a', 1);
    fa.addTransition(3, 'a', 4);
    fa.addTransition(3, 'b', 5);

    fa.addTransition(4, 'b', 5);
    fa.addTransition(4, 'a', 3);
    fa.addTransition(5, 'a', 5);
    fa.addTransition(5, 'b', 5);
	
	EXPECT_TRUE(fa.match("ab"));
	EXPECT_TRUE(fa.match("aba"));
	EXPECT_TRUE(fa.match("bb"));
	EXPECT_TRUE(fa.match("bba"));
	EXPECT_TRUE(fa.match("bab"));
	EXPECT_TRUE(fa.match("baaaaaaab"));
	
	EXPECT_FALSE(fa.match(""));
	EXPECT_FALSE(fa.match("a"));
	EXPECT_FALSE(fa.match("b"));
	EXPECT_FALSE(fa.match("aa"));
	EXPECT_FALSE(fa.match("ba"));
	EXPECT_FALSE(fa.match("bbbbbbbbbbbbbb"));
	EXPECT_FALSE(fa.match("bbbbaaaaaaaaaaa"));
	EXPECT_FALSE(fa.match("abbbbbbbbbbbb"));
	
    fa::Automaton automata = fa::Automaton::createMinimalMoore(fa);

    EXPECT_EQ(automata.countStates(), 4u);
    EXPECT_TRUE(automata.isDeterministic());
    
    EXPECT_TRUE(automata.match("ab"));
	EXPECT_TRUE(automata.match("aba"));
	EXPECT_TRUE(automata.match("bb"));
	EXPECT_TRUE(automata.match("bba"));
	EXPECT_TRUE(automata.match("bab"));
	EXPECT_TRUE(automata.match("baaaaaaab"));
	
	EXPECT_FALSE(automata.match(""));
	EXPECT_FALSE(automata.match("a"));
	EXPECT_FALSE(automata.match("b"));
	EXPECT_FALSE(automata.match("aa"));
	EXPECT_FALSE(automata.match("ba"));
	EXPECT_FALSE(automata.match("bbbbbbbbbbbbbb"));
	EXPECT_FALSE(automata.match("bbbbaaaaaaaaaaa"));
	EXPECT_FALSE(automata.match("abbbbbbbbbbbb"));
}

TEST(AutomatonTest, createMinimalMoore1) {
	fa::Automaton fa;
	fa.addState(0);
	fa.addState(1);
	fa.addState(2);
	fa.addState(3);
	fa.addState(4);
	fa.addState(5);
	
	fa.setStateInitial(0);
	fa.setStateFinal(5);
	
	fa.addTransition(0,'a',1);
	fa.addTransition(0,'b',2);
	fa.addTransition(1,'a',4);
	fa.addTransition(1,'b',5);
	fa.addTransition(2,'a',0);
	fa.addTransition(2,'b',0);
	fa.addTransition(3,'b',4);
	fa.addTransition(3,'a',5);
	fa.addTransition(4,'a',3);
	fa.addTransition(4,'b',5);
	fa.addTransition(5,'a',3);
	fa.addTransition(5,'b',4);
	
	EXPECT_TRUE(fa.match("ab"));
	EXPECT_TRUE(fa.match("bbbbbbbbbbab"));
	EXPECT_TRUE(fa.match("aaaa"));
	
	EXPECT_FALSE(fa.match(""));
	EXPECT_FALSE(fa.match("edf"));
	EXPECT_FALSE(fa.match("ba"));
	EXPECT_FALSE(fa.match("bba"));
	EXPECT_FALSE(fa.match("aaba"));
	
	fa::Automaton automata = fa::Automaton::createMinimalMoore(fa);
	
	EXPECT_EQ(fa.countStates(), automata.countStates());
	
	EXPECT_TRUE(automata.match("ab"));
	EXPECT_TRUE(automata.match("bbbbbbbbbbab"));
	EXPECT_TRUE(automata.match("aaaa"));
	
	EXPECT_FALSE(automata.match(""));
	EXPECT_FALSE(automata.match("edf"));
	EXPECT_FALSE(automata.match("ba"));
	EXPECT_FALSE(automata.match("bba"));
	EXPECT_FALSE(automata.match("aaba"));
}

TEST(AutomatonTest, createMinimalMoore2) {
	fa::Automaton fa;
	fa.addState(0);
	fa.addState(1);
	fa.addState(2);
	fa.addState(3);
	fa.addState(4);
	fa.addState(5);
	
	fa.setStateInitial(0);
	fa.setStateFinal(4);
	fa.setStateFinal(5);
	
	fa.addTransition(0,'a',1);
	fa.addTransition(0,'b',3);
	fa.addTransition(1,'a',0);
	fa.addTransition(1,'b',2);
	fa.addTransition(2,'a',1);
	fa.addTransition(2,'b',5);
	fa.addTransition(3,'a',1);
	fa.addTransition(3,'b',4);
	fa.addTransition(4,'a',0);
	fa.addTransition(4,'b',4);
	fa.addTransition(5,'a',1);
	fa.addTransition(5,'b',4);
	
	
	EXPECT_TRUE(fa.match("abb"));
	EXPECT_TRUE(fa.match("aaaaaaabb"));
	EXPECT_TRUE(fa.match("abbabb"));
	EXPECT_TRUE(fa.match("bb"));
	EXPECT_TRUE(fa.match("bbbbbbbbbbb"));
	EXPECT_TRUE(fa.match("bbbbbabbb"));

	EXPECT_FALSE(fa.match("b"));
	EXPECT_FALSE(fa.match("a"));
	EXPECT_FALSE(fa.match("ab"));
	EXPECT_FALSE(fa.match("bba"));
	EXPECT_FALSE(fa.match(""));
	EXPECT_FALSE(fa.match("aa"));
	
	fa::Automaton automata = fa::Automaton::createMinimalMoore(fa);
	
	EXPECT_EQ(automata.countStates(),3u);
	
	EXPECT_TRUE(fa.match("bb"));
	EXPECT_TRUE(fa.match("bbbbbbbbbb"));
	EXPECT_TRUE(fa.match("bbbbbaaaaabb"));
	
	EXPECT_FALSE(fa.match("a"));
	EXPECT_FALSE(fa.match("b"));
	EXPECT_FALSE(fa.match("ba"));
	EXPECT_FALSE(fa.match("baaaaa"));
	EXPECT_FALSE(fa.match("bbbbbbaaaaa"));
}

TEST_F(AutomatonTestFixture, createMinimalMoore3) {
	EXPECT_TRUE(faNCompletNDeterministe.match("e"));
	EXPECT_TRUE(faNCompletNDeterministe.match("efe"));
	EXPECT_TRUE(faNCompletNDeterministe.match("fe"));
	EXPECT_TRUE(faNCompletNDeterministe.match("fffffe"));
	EXPECT_TRUE(faNCompletNDeterministe.match("eeeeefffffe"));
	
	EXPECT_FALSE(faNCompletNDeterministe.match(""));
	EXPECT_FALSE(faNCompletNDeterministe.match("f"));
	EXPECT_FALSE(faNCompletNDeterministe.match("ffff"));
	EXPECT_FALSE(faNCompletNDeterministe.match("ffffef"));
	
	//Automate non complet et non deterministe
	//Donc il est complété et déterminisé par l'algo de Moore
	//En appelant les fcts précédents
	
	fa::Automaton automata = fa::Automaton::createMinimalMoore(faNCompletNDeterministe);
	
	EXPECT_TRUE(automata.match("e"));
	EXPECT_TRUE(automata.match("efe"));
	EXPECT_TRUE(automata.match("fe"));
	EXPECT_TRUE(automata.match("fffffe"));
	EXPECT_TRUE(automata.match("eeeeefffffe"));
	
	EXPECT_FALSE(automata.match(""));
	EXPECT_FALSE(automata.match("f"));
	EXPECT_FALSE(automata.match("ffff"));
	EXPECT_FALSE(automata.match("ffffef"));
}





TEST(AutomatonTest, createMinimalBrzozowski) {

}

TEST(AutomatonTest, createMinimalHopcroft) {

}

//CREATE WHITOUT EPSILON

TEST(AutomatonTest, createWithoutEpsilon0) {
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

	fa::Automaton automata = fa::Automaton::createWithoutEpsilon(fa);

	EXPECT_TRUE(automata.match(""));
	EXPECT_TRUE(automata.match("a"));
	EXPECT_TRUE(automata.match("aa"));
	EXPECT_TRUE(automata.match("ab"));
	EXPECT_TRUE(automata.match("abbbbb"));
	EXPECT_TRUE(automata.match("aaaaaabbbbbbbbc"));
	EXPECT_TRUE(automata.match("bc"));
	EXPECT_TRUE(automata.match("b"));
	EXPECT_TRUE(automata.match("bbbbbbbbbb"));
	EXPECT_TRUE(automata.match("aaaaaaaaa"));
	EXPECT_TRUE(automata.match("bbbccccccccc"));
	EXPECT_TRUE(automata.match("c"));
	EXPECT_TRUE(automata.match("cccccccc"));
	
	EXPECT_FALSE(automata.match("cccab"));
	EXPECT_FALSE(automata.match("edf"));
	EXPECT_FALSE(automata.match("baaac"));
	EXPECT_FALSE(automata.match("aca"));
}

TEST(AutomatonTest, createWithoutEpsilon1) {
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
	
	fa::Automaton automata = fa::Automaton::createWithoutEpsilon(fa);
	
	
	EXPECT_TRUE(automata.match(""));
	EXPECT_TRUE(automata.match("a"));
	EXPECT_TRUE(automata.match("aa"));
	EXPECT_TRUE(automata.match("ab"));
	EXPECT_TRUE(automata.match("abbbbb"));
	EXPECT_TRUE(automata.match("aaaaaabbbbbbbbc"));
	EXPECT_TRUE(automata.match("bc"));
	EXPECT_TRUE(automata.match("b"));
	EXPECT_TRUE(automata.match("bbbbbbbbbb"));
	EXPECT_TRUE(automata.match("aaaaaaaaa"));
	EXPECT_TRUE(automata.match("bbbccccccccc"));
	EXPECT_TRUE(automata.match("c"));
	EXPECT_TRUE(automata.match("cccccccc"));
	EXPECT_TRUE(automata.match("cccab"));
	EXPECT_TRUE(automata.match("baaac"));
	EXPECT_TRUE(automata.match("aca"));
	
	EXPECT_FALSE(automata.match("edf"));
}




int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
