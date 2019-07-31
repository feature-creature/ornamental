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

        void updateEEG(ofxOscMessage msg, vector<float>& sensor,int msgNum);
        void updateEEGStatus(ofxOscMessage msg, vector<float>& status, int msgNum);
        void drawEEG(vector<float> sensor,vector<float> status);

        void updateAbsolute(ofxOscMessage msg, vector<float>& sensor);
        void drawAbsolute(vector<float> sensor,vector<float> status);

        ofxOscReceiver receiver;
        ofTrueTypeFont font;

        // EEG
        vector <float> tp9;
        vector <float> af7;
        vector <float> af8;
        vector <float> tp10;

        // EEG status
        vector <float> tp9Status;
        vector <float> af7Status;
        vector <float> af8Status;
        vector <float> tp10Status;
    
        // Absolutes
        vector <float> alpha;
        vector <float> beta;
        vector <float> delta;
        vector <float> theta;
        vector <float> gamma;


        int currentMsgString;
        string msgStrings[MAX_NUM_MSG_STRINGS];
        float timers[MAX_NUM_MSG_STRINGS];
        int bufferSize; 
};
