// This example shows how to make sounds with the buzzer on the
// Romi 32U4.
//
// This example demonstrates the use of the playFrequency(),
// playNote(), and playFromProgramSpace() functions, which play
// entirely in the background, requiring no further action from
// the user once the function is called.  The CPU is then free to
// execute other code while the buzzer plays.
//
// This example also shows how to use the stopPlaying() function
// to stop the buzzer, and it shows how to use the isPlaying()
// function to tell whether the buzzer is still playing or not.

#include <PololuBuzzer.h>
#include "Star_Wars_MIDI.h"
#include "Music_player.h"

PololuBuzzer buzzer;
// Store this song in program space using the PROGMEM macro.
// Later we will play it directly from program space, bypassing
// the need to load it all into RAM first.
void MusicPlayer::Init(void)
{
    buzzer = PololuBuzzer();
}

void MusicPlayer::Play(void) 
{
    int current_note = 0;
    while(notes[current_note].duration != -1) {
        current_note += 1;
        if(notes[current_note].freq == -1) {
            buzzer.playNote(SILENT_NOTE,(15000/Tempo)*notes[current_note].duration,15);
        }
        else {
            buzzer.playNote(notes[current_note].freq,(15000/Tempo)*notes[current_note].duration,15);
        }
        while (buzzer.isPlaying());
    }
}

//https://www.pololu.com/docs/0J69/6