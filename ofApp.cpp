#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowTitle("Ornamental Tablet");
    ofSetFrameRate(60);
    ofSetVerticalSync(true);

    receiver.setup(PORT);
    ofLog() << "Listening for OSC messages on port " << PORT;

    bufferSize = 1280;
    tp9.assign(bufferSize,0.0);
    af7.assign(bufferSize,0.0);
    af8.assign(bufferSize,0.0);
    tp10.assign(bufferSize,0.0);

}

//--------------------------------------------------------------
void ofApp::update(){
    // clear old data
    /*
    for(int i = 0; i < MAX_NUM_MSG_STRINGS; i++){
        if(timers[i] < ofGetElapsedTimef()){
            msgStrings[i] = "";
        }
    }
    */

    while(receiver.hasWaitingMessages()){
        ofxOscMessage m;
        receiver.getNextMessage(m);

        // 220Hz || 256Hz
        if(m.getAddress() == "/muse/eeg"){

            updateEEG(m,tp9,0);
            updateEEG(m,af7,1);
            updateEEG(m,af8,2);
            updateEEG(m,tp10,3);
        }

        // 10Hz
        if(m.getAddress() == "/muse/elements/horseshoe"){
            updateEEGStatus(m,tp9Status,0);
            updateEEGStatus(m,af7Status,1);
            updateEEGStatus(m,af8Status,2);
            updateEEGStatus(m,tp10Status,3);
        }

    }

        //basic text output 
        /*
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
            else {
                msgString += "unhandled argument type " + m.getArgTypeName(i);
            }
        }

        msgStrings[currentMsgString] = msgString;
        timers[currentMsgString] = ofGetElapsedTimef() + 5.0f;
        currentMsgString = (currentMsgString + 1) % MAX_NUM_MSG_STRINGS;

        msgStrings[currentMsgString] = "";
    }
    */
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient(100,0);

    /*
    for(int i = 0; i < MAX_NUM_MSG_STRINGS; i++){
        ofDrawBitmapStringHighlight(msgStrings[i],10,40 + 15 * i);
    }
    */

    drawEEG(tp9,tp9Status);
    drawEEG(af7,af7Status);
    drawEEG(af8,af8Status);
    drawEEG(tp10,tp10Status);

    string buf = "listening for osc messages on port " + ofToString(PORT);
    ofDrawBitmapStringHighlight(buf,10,20);
}

//--------------------------------------------------------------
void ofApp::updateEEG(ofxOscMessage msg, vector<float>& sensor, int msgNum){
    sensor.push_back(msg.getArgAsFloat(msgNum));
    if(sensor.size() >= bufferSize)sensor.erase(sensor.begin(),sensor.begin()+1);
}

//--------------------------------------------------------------
void ofApp::updateEEGStatus(ofxOscMessage msg, vector<float>& status, int msgNum){
    status.push_back(msg.getArgAsFloat(msgNum));
    if(status.size() >= bufferSize)status.erase(status.begin(),status.begin()+1);
}

//--------------------------------------------------------------
void ofApp::drawEEG(vector <float> sensor,vector <float> status){
    ofPushStyle();
    ofPushMatrix();

    ofTranslate(32,600,0);

    ofNoFill();
    status.size() > 0 ? ofSetColor(ofMap(status[status.size() - 1],4,1,100,255)) : ofSetColor(100);

    ofBeginShape();
    for(unsigned int i = 0; i < sensor.size(); i++){
        ofVertex(i*(ofGetWidth()/bufferSize),ofMap(sensor[i],0,1682.815,0,-500));
    }
    ofEndShape(false);

    ofPopMatrix();
    ofPopStyle();
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
