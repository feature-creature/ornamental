#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowTitle("Ornamental Tablet");
    ofSetFrameRate(60);
    ofSetVerticalSync(true);

    receiver.setup(PORT);
    ofLog() << "Listening for OSC messages on port " << PORT;

}

//--------------------------------------------------------------
void ofApp::update(){
    // clear old data
    for(int i = 0; i < MAX_NUM_MSG_STRINGS; i++){
        if(timers[i] < ofGetElapsedTimef()){
            msgStrings[i] = "";
        }
    }

    while(receiver.hasWaitingMessages()){
        ofxOscMessage m;
        receiver.getNextMessage(m);

        // if(m.getAddress() == ""){}
        
        string msgString;
        msgString = m.getAddress();
        msgString += ":";

        for(size_t i = 0; i < m.getNumArgs(); i++){
            msgString += " ";   
            msgString += m.getArgTypeName(i);
            msgString += ":";
            
            if(m.getArgType(i) == OFXOSC_TYPE_INT32){
                msgString += ofToString(m.getArgAsInt32(i));
            }
            else if(m.getArgType(i) == OFXOSC_TYPE_FLOAT){
                msgString += ofToString(m.getArgAsFloat(i));
            }
            else if(m.getArgType(i) == OFXOSC_TYPE_STRING){
                msgString += ofToString(m.getArgAsString(i));
            }
            else {
                msgString += "unhandled argument type " + m.getArgTypeName(i);
            }
        }

        msgStrings[currentMsgString] = msgString;
        timers[currentMsgString] = ofGetElapsedTimef() + 5.0f;
        currentMsgString = (currentMsgString + 1) % MAX_NUM_MSG_STRINGS;

        msgStrings[currentMsgString] = "";
    }
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofBackgroundGradient(100,0);

    for(int i = 0; i < MAX_NUM_MSG_STRINGS; i++){
        ofDrawBitmapStringHighlight(msgStrings[i],10,40 + 15 * i);
    }

    string buf = "listening for osc messages on port " + ofToString(PORT);
    ofDrawBitmapStringHighlight(buf,10,20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
