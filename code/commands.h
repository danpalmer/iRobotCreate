enum COMMANDS {				// DATA BYTES		// Description
	START_OI = 128,			// 					starts open interface *required*
	SET_BAUD = 129, 		// 		1			set baud rate
	SET_SAFE = 131,			//					sets safe mode
	SET_FULL = 132, 		//					sets full mode
	/* Demo commands excluded */
	DRIVE = 137,			//		4			2x 16bit signed values, 2's comp, 
							//					byte 1-2: velocity, -500 +500 mm/s
							//					byte 3-4: turn radius -2000 +2000 mm
							//					special: straight: 0x8000 or 0x7FFF
							//					special: turn on point: 0xFFFF clockwise / 0x0001 anti-cw
	DRIVE_DIRECT = 145,		//		4			2x 16bit signed values, 2's comp,
							//					first 2 bytes: velocity of right wheel
							//					second 2 bytes: velocity of left wheel - mm/s
	LED_CONTROL = 139,		//		3			[advance/play][power-colour][power-intensity]
							//					7  6  5  4  3  2  1  0
							//					           ADV   PLAY
							//					Colour: 0-green 255-red, variable in between
	DEFINE_SONG = 140,				//	   2N+2			Specify songs for use later, N=notes
							//					[song-number][song-length][odd-note-number][even-note-duration]
	PLAY_SONG = 141,		//		1			song number to play, doesn't work when a song is already playing
	READ_SENSOR = 142,		//		1			sensor data packet ID, 6=all, 0-5=group, see reference
	STREAM = 148,			//	   N+1			starts continuous stream of sensor data to be received every 15ms
							//					[number][packet-id][packet-id]...
};