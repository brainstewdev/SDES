#include<gtest/gtest.h>

extern "C" {
	#include "../include/SDES.h"
}

// cose da testare:
// -inverti
// -espansione
// -feistel
// -s1
// -s2
// -calcolaChiave

TEST(SDES, inverti){
	ASSERT_EQ(0, inverti(0));
	ASSERT_EQ(2, inverti(1));
	ASSERT_EQ(1, inverti(2));
	ASSERT_EQ(3, inverti(3));
}

// espansione
TEST(SDES, espansione){
	ASSERT_EQ((char)148, (char)espansione(40));
	ASSERT_EQ((char)193, (char)espansione(49));
}
// feistel

// s1
TEST(SDES, S1){
	ASSERT_EQ((char)5, (char)S1(0));	
	ASSERT_EQ((char)2, (char)S1(1));
}

// s2
TEST(SDES, S2){
	ASSERT_EQ((char)5, (char)S2(3));
	ASSERT_EQ((char)0, (char)S2(10));
}

TEST(SDES, CalcolaChiave){
	char * keyComp = (char*) malloc(sizeof(char)*2);
	keyComp[1] = (char)0;
	keyComp[0] = (char)77; 

	char * keys = (char*) malloc(sizeof(char)*4);

	keys[0] = (char)77;
	keys[1] = (char)154;
	keys[2] = (char)52;
	keys[3] =	(char)105;

	for(int i = 0; i < 4; i++){
		ASSERT_EQ(keys[i], calcolaChiave(keyComp,i));
	} 
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
