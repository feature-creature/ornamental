#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowTitle("Ornamental Tablet");
    ofSetFrameRate(60);
    ofSetVerticalSync(true);

    receiver.setup(PORT);
    ofLog() << "Listening for OSC messages on port " << PORT;

    bufferSize = 1280;

    // EEG
    tp9.assign(bufferSize,0.0);
    af7.assign(bufferSize,0.0);
    af8.assign(bufferSize,0.0);
    tp10.assign(bufferSize,0.0);

    // Absolutes
    alpha.assign(bufferSize,0.0);
    beta.assign(bufferSize,0.0);
    delta.assign(bufferSize,0.0);
    theta.assign(bufferSize,0.0);
    gamma.assign(bufferSize,0.0);

    // Motion
    gyro.assign(bufferSize,0.0);
    acc.assign(bufferSize,0.0);

    // Battery
    batt = 0;


}

//--------------------------------------------------------------
void ofApp::update(){
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

        // 10Hz
        if(m.getAddress() == "/muse/elements/alpha_absolute")updateAbsolute(m,alpha);
        if(m.getAddress() == "/muse/elements/beta_absolute")updateAbsolute(m,beta);
        if(m.getAddress() == "/muse/elements/delta_absolute")updateAbsolute(m,delta);
        if(m.getAddress() == "/muse/elements/theta_absolute")updateAbsolute(m,theta);
        if(m.getAddress() == "/muse/elements/gamma_absolute")updateAbsolute(m,gamma);

        // 52Hz
        if(m.getAddress() == "/muse/gyro")updateGyro(m,gyro);
        if(m.getAddress() == "/muse/acc")updateGyro(m,acc);

        // 0.1Hz
        if(m.getAddress() == "/muse/batt")updateBatt(m,batt);

    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient(100,0);

    drawEEG(tp9,tp9Status);
    drawEEG(af7,af7Status);
    drawEEG(af8,af8Status);
    drawEEG(tp10,tp10Status);

    drawAbsolute(alpha,tp9Status);
    drawAbsolute(beta,tp9Status);
    drawAbsolute(delta,tp9Status);
    drawAbsolute(theta,tp9Status);
    drawAbsolute(gamma,tp9Status);

    drawGyro(gyro);
    drawAcc(acc);

    drawBatt(batt);

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
void ofApp::updateAbsolute(ofxOscMessage msg, vector<float>& sensor){
    sensor.push_back(msg.getArgAsFloat(0));
    if(sensor.size() >= bufferSize)sensor.erase(sensor.begin(),sensor.begin()+1);
}

//--------------------------------------------------------------
void ofApp::drawAbsolute(vector <float> sensor, vector <float> status){
    ofPushStyle();
    ofPushMatrix();

    ofTranslate(32,600,0);

    ofNoFill();
    status.size() > 0 ? ofSetColor(ofMap(status[status.size() - 1],4,1,100,255)) : ofSetColor(100);

    ofBeginShape();
    for(unsigned int i = 0; i < sensor.size(); i++){
        // max/min?
        ofVertex(i*(ofGetWidth()/bufferSize),ofMap(sensor[i],0,2,0,-300));
    }
    ofEndShape(false);

    ofPopMatrix();
    ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::updateGyro(ofxOscMessage msg, vector <float>& sensor){
    sensor.push_back(msg.getArgAsFloat(0));
    if(sensor.size() >= bufferSize)sensor.erase(sensor.begin(),sensor.begin()+1);
}


//--------------------------------------------------------------
void ofApp::drawGyro(vector <float> sensor){
    ofPushStyle();
    ofPushMatrix();

    ofTranslate(32,350,0);

    ofNoFill();
    ofSetColor(255);

    ofBeginShape();
    for(unsigned int i = 0; i < sensor.size(); i++){
        ofVertex(i*(ofGetWidth()/bufferSize),ofMap(sensor[i],-245,245,0,-300));
    }
    ofEndShape(false);

    ofPopMatrix();
    ofPopStyle();

}

//--------------------------------------------------------------
void ofApp::updateAcc(ofxOscMessage msg, vector <float>& sensor){
    sensor.push_back(msg.getArgAsFloat(0));
    if(sensor.size() >= bufferSize)sensor.erase(sensor.begin(),sensor.begin()+1);
}

//--------------------------------------------------------------
void ofApp::drawAcc(vector <float> sensor){
    ofPushStyle();
    ofPushMatrix();

    ofTranslate(32,350,0);

    ofNoFill();
    ofSetColor(255);

    ofBeginShape();
    for(unsigned int i = 0; i < sensor.size(); i++){
        ofVertex(i*(ofGetWidth()/bufferSize),ofMap(sensor[i],-2,2,0,-300));
    }
    ofEndShape(false);

    ofPopMatrix();
    ofPopStyle();

}

//--------------------------------------------------------------
void ofApp::updateBatt(ofxOscMessage msg, int& sensor){
    sensor = msg.getArgAsInt32(0);
}

//--------------------------------------------------------------
void ofApp::drawBatt(int sensor){
    ofPushStyle();
    ofPushMatrix();


    ofNoFill();
    ofSetColor(255);
    string battPercent = ofToString(sensor)+"%";
    ofDrawBitmapStringHighlight(battPercent,10,50);

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
