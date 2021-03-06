#include "vonat.hpp"
#include "jegy.hpp"
#include "menu.hpp"

#include "gtest_lite.h"

using namespace std;

int main() {

    Jaratok jaratok;
    beolvas(jaratok, "vonatok.txt");
    Jegyek jegyek;
    beolvas(jaratok, jegyek, "jegyek.txt");

    menu(jaratok ,jegyek);
    // Végleges programhoz tartozó rész, illetve felhasználói menü meghívása




    /*
    Az alábbi tesztek a jelenlegi programban lévő összes függvényt tesztelik a fájlkezeléssel együtt
    */

    ///TESZTEK

    // String osztály tesztje
    TEST(String, Konstruktorok) {
        String s1;  // Paraméter nélküli konstruktor
        EXPECT_EQ("\0", s1.c_str());
        EXPECT_EQ(0, int(s1.size()));

        String s2('c'); // Konstruktor karakter paraméterrel
        EXPECT_STREQ("c", s2.c_str());
        EXPECT_EQ(1, int(s2.size()));

        String s3("string"); // Konstruktor C string-el
        EXPECT_STREQ("string", s3.c_str());
        EXPECT_EQ(6, int(s3.size()));

        String s4(s3); // Másoló konstruktor
        EXPECT_STREQ("string", s4.c_str());
        EXPECT_EQ(6, int(s4.size()));
    } ENDM

    TEST(String, operatorok) {
        String s1("hello");
        String s2("world");
        s2 = s1;
        EXPECT_STREQ(s1.c_str(), s2.c_str());

        s2 = String(" world");
        EXPECT_STREQ(" world", s2.c_str());

        String s3 = s1 + s2;
        EXPECT_STREQ("hello world", s3.c_str());
    } ENDM

    TEST(String, kiir) {
        String s1("Hello World!");
        stringstream ss;
        ss << s1;
        EXPECT_STREQ("Hello World!", ss.str().c_str());
    } ENDM

    TEST(String, beolvas) {
        stringstream ss;
        ss << "Hello World!";
        String s1;
        ss >> s1;
        String s2("Hello World!");
        EXPECT_EQ(s1, s2);
    } ENDM

    TEST(String, egyeb fuggvenyek) {
       // getline
       stringstream ss;
       ss << "adat1#adat2";
       String s1;
       String s2("adat1");
       getline(ss, s1, '#');
       EXPECT_STREQ(s2.c_str(), s1.c_str());
       s2 = "adat2";
       String s3;
       getline(ss, s3, '#');
       EXPECT_STREQ(s2.c_str(), s3.c_str());

       // stoi
       String s4("123");
       int i1 = stoi(s4);
       EXPECT_EQ(123, i1);
    } ENDM

    // Dátum osztály tesztje
    TEST(Datum, kiir) {
        Datum d1(2021, 05, 06, 1140);
        stringstream ss;
        ss << d1;
        EXPECT_STREQ("2021#5#6#19#00", ss.str().c_str());
    } ENDM

    TEST(Datum, beolvas) {
        stringstream ss;
        ss << "2021\n12\n10\n15\n30";
        Datum d1;
        ss >> d1;
        Datum d2(2021, 12, 10, 930);
        EXPECT_EQ(d1, d2);
    } ENDM

    TEST(Datum, nagyobb/kisebb egyenlo) {
        Datum d1(2021, 05, 06, 1140);
        Datum d2(2021, 06, 01, 1100);
        EXPECT_GE(d2, d1);
        EXPECT_LE(d1, d2);

        Datum d3(2021, 05, 10, 1140);
        Datum d4 = d3;
        EXPECT_GE(d3, d4);
        EXPECT_LE(d3, d4);

        Datum d5(2021, 05, 10, 1140);
        Datum d6(2022, 05, 10, 1140);
        EXPECT_FALSE(d5 >= d6);
        EXPECT_FALSE(d6 <= d5);
        EXPECT_GE(d6, d5);

        Datum d7(2021, 05, 9, 1140);
        Datum d8(2021, 05, 10, 1140);
        EXPECT_FALSE(d7 >= d8);
        EXPECT_GE(d8, d7);

        Datum d9(2021, 05, 9, 1140);
        Datum d10(2021, 05, 9, 1141);
        EXPECT_FALSE(d9 >= d10);
        EXPECT_GE(d10, d9);

        // minden egyenlő
        Datum d11(2021, 05, 9, 1141);
        EXPECT_GE(d10, d11);
        EXPECT_LE(d10, d11);
    } ENDM

    TEST(Datum, egyenloseg) {
        Datum d1(2021, 05, 06, 1140);
        Datum d2(2021, 05, 06, 1140);
        EXPECT_EQ(d1, d2);

        Datum d3(2020, 01, 01, 1180);
        EXPECT_FALSE(d1 == d3);
    } ENDM

    TEST(Datum, ertekadas) {
        Datum d1(2021, 05, 06, 1140);
        Datum d2(2021, 06, 01, 1100);
        d1 = d2;
        EXPECT_EQ(d1, d2);
    } ENDM


    // Vonat osztály tesztje
    String azonosito = "AAA111";
    String ind = "Budapest";
    String erk = "Debrecen";
    Datum d1(2021, 05, 06, 1140);
    Datum d2(2021, 06, 01, 1100);
    Vonat v(azonosito, ind, d1, erk, d2);

    TEST(Vonat, kiir) {
        stringstream ss;
        ss << v;
        EXPECT_STREQ("AAA111#2021#5#6#19#00#2021#6#1#18#20#Budapest#Debrecen\n",ss.str().c_str());
    } ENDM

    TEST(Vonat, getterek) {
        EXPECT_STREQ("AAA111",v.get_vsz().c_str());
        EXPECT_EQ(d1, v.get_ind_dt());
        EXPECT_EQ(d2, v.get_erkez_dt());
        EXPECT_STREQ("Budapest", v.get_ind_all().c_str());
        EXPECT_STREQ("Debrecen", v.get_erkez_all().c_str());
    } ENDM

    TEST(Vonat, egyenloseg) {
        String s1("AAA111");
        String s2("BBB111");
        Vonat v1(s1, ind, d1, erk, d2);
        Vonat v2(s1, ind, d1, erk, d2);
        Vonat v3(s2, ind, d1, erk, d2);
        EXPECT_EQ(v1, v2);
        EXPECT_FALSE(v1 == v3);
    } ENDM

    // Jegy osztály tesztje
    Jegy j("Berenyi Henrik Daniel", 10, 5, v);

    TEST(Jegy, kiir) {
        stringstream ss;
        ss << j;
       EXPECT_STREQ("Berenyi Henrik Daniel#10#5#AAA111\n",ss.str().c_str()) ;
    } ENDM

    TEST(Jegy, getterek) {
        EXPECT_STREQ("Berenyi Henrik Daniel", j.get_nev().c_str());
        EXPECT_STREQ("AAA111", j.get_vsz().c_str());
        EXPECT_EQ(10, j.get_ksz());
        EXPECT_EQ(5, j.get_hely());
        EXPECT_STREQ("Budapest", j.get_ind_all().c_str());
        EXPECT_STREQ("Debrecen", j.get_erkez_all().c_str());
        EXPECT_EQ(d1, j.get_ind_dt());
        EXPECT_EQ(d2, j.get_erkez_dt());
        EXPECT_EQ(v,j.get_vonat());
    }ENDM

    TEST(Jegy, ertekadas) {
       Jegy j1(j);
       Jegy j2("Kovacs Endre", 13,2, v);
       j1 = j2;
       EXPECT_EQ(j1, j2);
    } ENDM

    TEST(Jegy, egyenloseg) {
        Jegy j1("Kovacs Endre", 13, 2, v);
        Jegy j2("Kovacs Endre", 13, 2, v);
        Jegy j3("Nagy Lajos", 13, 3, v);
        EXPECT_EQ(j1, j2);
        EXPECT_FALSE(j1 == j3);
    } ENDM
    
    // Járatok es Jegyek tesztjei
    Jaratok ja;
    EXPECT_THROW(beolvas(ja, "ilyen_nincs.txt"), const char*); //ismeretlen fájl esetén kivétel
    EXPECT_NO_THROW(beolvas(ja, "vonatok.txt")); //sikeres beolvasás

    Jegyek je;
    EXPECT_THROW(beolvas(ja, je, "ilyen_nincs.txt"), const char*); //ismeretlen fájl esetén kivétel
    EXPECT_NO_THROW(beolvas(ja, je, "jegyek.txt")); //sikeres beolvasás

    TEST(Jaratok, kiir) {
        stringstream ss;
        ss << ja;
        EXPECT_STREQ("ABB001#2021#4#20#18#50#2021#4#20#19#00#Budapest#Sopron\n"
                     "ZBB002#2021#4#20#18#50#2021#4#20#19#00#Budapest#Debrecen\n"
                     "ZBB003#2021#4#20#18#50#2021#4#20#19#00#Budapest#Berlin\n", ss.str().c_str());
    } ENDM

    TEST(Jaratok, add/remove) {
        ja.add(v);
        EXPECT_EQ(v, ja[3]);
        EXPECT_EQ(size_t(4), ja.size());

        EXPECT_THROW(ja.remove("AAA222"), const char*);
        EXPECT_NO_THROW(ja.remove("AAA111"));
    } ENDM

    TEST(Jaratok, index) {
        stringstream ss;
        ss << ja[0];
        EXPECT_STREQ("ABB001#2021#4#20#18#50#2021#4#20#19#00#Budapest#Sopron\n", ss.str().c_str());
        EXPECT_THROW(ja[ja.size()], const char*);
    } ENDM

    TEST(Jaratok, tovabbi_fuggvenyek) {
        EXPECT_EQ(size_t(3), ja.size());
        EXPECT_TRUE(ja.checkID("ABB001"));
        EXPECT_FALSE(ja.checkID("AAA222"));
    } ENDM

    TEST(Jegyek, kiir) {
       stringstream ss;
       ss << je;
       EXPECT_STREQ("Berenyi Henrik#12#8#ABB001\n"
                    "Kiss Gabor#21#9#ZBB002\n"
                    "Kovács István#10#2#ABB001\n",ss.str().c_str());
    } ENDM

    TEST(Jegyek, add/remove) {
       je.add(j);
       EXPECT_EQ(j, je[3]);
       EXPECT_EQ(size_t(4), je.size());

       EXPECT_THROW(je.remove("nincs ilyen nev"), const char*);
       EXPECT_NO_THROW(je.remove("Berenyi Henrik Daniel"));
    } ENDM

    TEST(Jegyek, index) {
       stringstream ss;
       ss << je[0];
       EXPECT_STREQ("Berenyi Henrik#12#8#ABB001\n", ss.str().c_str());
    } ENDM

    TEST(Jaratok, tovabbi_fuggvenyek) {
       EXPECT_EQ(size_t(3), je.size());
       EXPECT_TRUE(je.checkSeat(je[0].get_vsz(), je[0].get_ksz(), je[0].get_hely()));
       EXPECT_FALSE(je.checkSeat("AAA222", 12, 21));
    } ENDM

    return 0;
}
