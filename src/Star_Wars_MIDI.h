#include <PololuBuzzer.h>

#define Tempo 350 //<== BPM HERE

typedef struct note {
    int freq;
    int duration;
} note_t;

#define C0 NOTE_C(0)
#define Db0 NOTE_D_FLAT(0)
#define D0 NOTE_D(0)
#define Eb0 NOTE_E_FLAT(0)
#define E0 NOTE_E(0)
#define F0 NOTE_F(0)
#define Gb0 NOTE_G_FLAT(0)
#define G0 NOTE_G(0)
#define Ab0 NOTE_A_FLAT(0)
#define A0 NOTE_A(0)
#define Bb0 NOTE_B_FLAT(0)
#define B0 NOTE_B(0)
#define C1 NOTE_C(1)
#define Db1 NOTE_D_FLAT(1)
#define D1 NOTE_D(1)
#define Eb1 NOTE_E_FLAT(1)
#define E1 NOTE_E(1)
#define F1 NOTE_F(1)
#define Gb1 NOTE_G_FLAT(1)
#define G1 NOTE_G(1)
#define Ab1 NOTE_A_FLAT(1)
#define A1 NOTE_A(1)
#define Bb1 NOTE_B_FLAT(1)
#define B1 NOTE_B(1)
#define C2 NOTE_C(2)
#define Db2 NOTE_D_FLAT(2)
#define D2 NOTE_D(2)
#define Eb2 NOTE_E_FLAT(2)
#define E2 NOTE_E(2)
#define F2 NOTE_F(2)
#define Gb2 NOTE_G_FLAT(2)
#define G2 NOTE_G(2)
#define Ab2 NOTE_A_FLAT(2)
#define A2 NOTE_A(2)
#define Bb2 NOTE_B_FLAT(2)
#define B2 NOTE_B(2)
#define C3 NOTE_C(3)
#define Db3 NOTE_D_FLAT(3)
#define D3 NOTE_D(3)
#define Eb3 NOTE_E_FLAT(3)
#define E3 NOTE_E(3)
#define F3 NOTE_F(3)
#define Gb3 NOTE_G_FLAT(3)
#define G3 NOTE_G(3)
#define Ab3 NOTE_A_FLAT(3)
#define A3 NOTE_A(3)
#define Bb3 NOTE_B_FLAT(3)
#define B3 NOTE_B(3)
#define C4 NOTE_C(4)
#define Db4 NOTE_D_FLAT(4)
#define D4 NOTE_D(4)
#define Eb4 NOTE_E_FLAT(4)
#define E4 NOTE_E(4)
#define F4 NOTE_F(4)
#define Gb4 NOTE_G_FLAT(4)
#define G4 NOTE_G(4)
#define Ab4 NOTE_A_FLAT(4)
#define A4 NOTE_A(4)
#define Bb4 NOTE_B_FLAT(4)
#define B4 NOTE_B(4)
#define C5 NOTE_C(5)
#define Db5 NOTE_D_FLAT(5)
#define D5 NOTE_D(5)
#define Eb5 NOTE_E_FLAT(5)
#define E5 NOTE_E(5)
#define F5 NOTE_F(5)
#define Gb5 NOTE_G_FLAT(5)
#define G5 NOTE_G(5)
#define Ab5 NOTE_A_FLAT(5)
#define A5 NOTE_A(5)
#define Bb5 NOTE_B_FLAT(5)
#define B5 NOTE_B(5)
#define C6 NOTE_C(6)
#define Db6 NOTE_D_FLAT(6)
#define D6 NOTE_D(6)
#define Eb6 NOTE_E_FLAT(6)
#define E6 NOTE_E(6)
#define F6 NOTE_F(6)
#define Gb6 NOTE_G_FLAT(6)
#define G6 NOTE_G(6)
#define Ab6 NOTE_A_FLAT(6)
#define A6 NOTE_A(6)
#define Bb6 NOTE_B_FLAT(6)
#define B6 NOTE_B(6)
#define C7 NOTE_C(7)
#define Db7 NOTE_D_FLAT(7)
#define D7 NOTE_D(7)
#define Eb7 NOTE_E_FLAT(7)
#define E7 NOTE_E(7)
#define F7 NOTE_F(7)
#define Gb7 NOTE_G_FLAT(7)
#define G7 NOTE_G(7)
#define Ab7 NOTE_A_FLAT(7)
#define A7 NOTE_A(7)
#define Bb7 NOTE_B_FLAT(7)
#define B7 NOTE_B(7)
#define C8 NOTE_C(8)
#define Db8 NOTE_D_FLAT(8)
#define D8 NOTE_D(8)
#define Eb8 NOTE_E_FLAT(8)
#define E8 NOTE_E(8)
#define F8 NOTE_F(8)
#define Gb8 NOTE_G_FLAT(8)
#define G8 NOTE_G(8)
#define Ab8 NOTE_A_FLAT(8)
#define A8 NOTE_A(8)
#define Bb8 NOTE_B_FLAT(8)
#define B8 NOTE_B(8)

#define Note(note,len64) (note_t){ note,len64}
#define Pause(len64) (note_t){ -1, len64}
#define Stop() (note_t){-1,-1}

note_t notes[] = {
Note(B5,5),
Note(G6,5),
Note(E5,5),
Note(E6,5),
Note(B6,5),
Note(E5,10),
Note(A6,5),
Note(E5,5),
Note(Gb6,10),
Note(E5,10),
Note(G6,5),
Note(E5,5),
Note(Eb6,5),
Note(Bb5,5),
Note(F6,5),
Note(B4,5),
Note(E5,5),
Note(B5,5),
Note(B5,5),
Note(B4,5),
Note(G6,5),
Note(E5,5),
Note(E6,5),
Note(B6,5),
Note(E5,10),
Note(D7,5),
Note(D5,10),
Note(G5,10),
Note(Bb5,10),
Note(D6,10),
Note(G6,5),
Note(C7,5),
Note(Ab6,5),
Note(C5,5),
Note(F5,10),
Note(Ab5,10),
Note(C6,5),
Note(F6,10),
Note(B6,5),
Note(C5,10),
Note(A5,10),
Note(C6,10),
Note(E6,5),
Note(Bb5,5),
Note(G6,5),
Note(Db5,10),
Note(E5,10),
Note(Gb5,10),
Note(E5,5),
Note(E6,10),
Note(B5,5),
Note(G6,5),
Note(B4,5),
Note(B6,5),
Note(E5,5),
Note(B6,5),
Note(B5,5),
Note(G6,5),
Note(B4,5),
Note(C7,5),
Note(E5,5),
Note(Bb6,5),
Note(C6,5),
Note(Gb6,5),
Note(B4,5),
Note(B6,5),
Note(E5,5),
Note(Bb5,5),
Note(C5,5),
Note(B5,5),
Note(G5,5),
Note(E5,5),
Note(B6,10),
Note(B5,5),
Note(G6,5),
Note(B4,5),
Note(B6,5),
Note(E5,5),
Note(B6,5),
Note(B5,5),
Note(G6,5),
Note(G5,5),
Note(D7,5),
Note(D5,10),
Note(G5,10),
Note(Bb5,10),
Note(D6,5),
Note(C7,5),
Note(Ab6,5),
Note(C5,10),
Note(F5,10),
Note(Ab5,10),
Note(C6,10),
Note(B6,5),
Note(B4,5),
Note(E5,5),
Note(G5,5),
Note(C6,5),
Note(Bb5,5),
Note(G6,5),
Note(Db5,10),
Note(E5,10),
Note(Gb5,10),
Note(E5,5),
Note(E6,5),
Note(B5,5),
Note(E6,10),
Note(B4,5),
Note(E5,5),
Note(E6,5),
Note(B5,5),
Note(E6,10),
Note(B4,5),
Note(C6,5),
Note(E5,5),
Note(E6,5),
Note(B4,10),
Note(G6,5),
Note(C5,5),
Note(B6,5),
Note(A5,5),
Note(Gb5,10),
Note(Gb5,5),
Note(B4,5),
Note(Gb6,5),
Note(B6,5),
Note(E5,10),
Note(G6,5),
Note(G5,5),
Note(C6,5),
Note(Gb5,5),
Note(Gb5,5),
Note(Gb5,5),
Note(E5,5),
Note(E6,5),
Note(E6,5),
Note(B4,10),
Note(G6,5),
Note(E4,5),
Note(E6,5),
Note(G6,5),
Note(E4,10),
Note(Gb6,5),
Note(E4,5),
Stop()
};