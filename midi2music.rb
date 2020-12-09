require 'midilib'
require 'midilib/io/seqreader'

# Create a new, empty sequence.
seq = MIDI::Sequence.new()

sharpsconv = {
	"C#" => "Db",
	"D#" => "Eb",
	"F#" => "Gb",
	"G#" => "Ab",
	"A#" => "Bb",
}
# Read the contents of a MIDI file into the sequence.
File.open(ARGV[0], 'rb') { | file |
    seq.read(file) { | track, num_tracks, i |
    	next unless track
    	tonebuf = {};
    	tonelist = [];
    	track.quantize 1
        track.recalc_delta_from_times
        puts "==START_OF_TRACK #{i}=="
        track.each { | event | 
        	next unless event.class < MIDI::NoteEvent
        	if event.class.to_s == "MIDI::NoteOn" then
        		
        		if(event.delta_time > 0) then
        			tonelist << "Pause(#{event.delta_time/192}),"
        		end
        		tonebuf[event.pch_oct] = event.time_from_start
        	elsif event.class.to_s == "MIDI::NoteOff"
        		next if (event.time_from_start-tonebuf[event.pch_oct])/192 == 0
        		notestr = event.pch_oct
        		if notestr =~ /#/ then
        			notestr = sharpsconv[notestr[0..1]] + notestr[2..-1]
        		end
        		tonelist << "Note(#{notestr},#{(event.time_from_start-tonebuf[event.pch_oct])/192}),"
        	end
		}
		tonelist << "Stop()"
        puts tonelist.join("\n")
        puts "==END_OF_TRACK #{i}=="
    }
}