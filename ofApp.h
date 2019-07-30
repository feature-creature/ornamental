#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

#define PORT 12345
#define MAX_NUM_MSG_STRINGS 40

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

        ofxOscReceiver receiver;
        ofTrueTypeFont font;

        int currentMsgString;
        string msgStrings[MAX_NUM_MSG_STRINGS];
        float timers[MAX_NUM_MSG_STRINGS];

};
