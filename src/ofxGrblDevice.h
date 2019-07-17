//
//  ofxGrblDevice.hpp
//   ofxGrbl
//
//  Created by Roy Macdonald on 7/9/19.
//
//

#pragma once
#pragma once

#include "ofMain.h"
#include "ofxGrblSettings.h"

namespace ofxGrbl{
class device{
	
public:
	
	void setup(string _port = "", int _baudrate = -1, const std::string& settingsFileName = "ofxGrblSettings.xml");
	
	// serial
	void connect(string _port = "", int _baudrate = -1);
	bool isConnected();
	
	
	
	void close();
	
	
	void loadGCodeFromFile(const std::string& _path);
	
	void sendMessage(const std::string& _msg, bool direct = false);
	
	bool checkZisDown(const std::string& _line);
	
	
	void saveStrokesToGCodeFile(const std::string& _path);
	void clear();
	
	void setHome(const glm::vec3& _homePos);
	void goHome();
	
	void enableSpindle(bool _enable, bool _direct = false);
	bool isSpindleEnabled();
	void setSpindleSpeed(int _speed, bool _direct = false);
	
	
	
	void killAlarmLock();
	
	void moveRight(float _mm);
	void moveLeft(float _mm);
	void moveUp(float _mm);
	void moveDown(float _mm);
	
	void setPosition(const glm::vec3& _pos, bool bRapidMovement = false, bool _sendDirect = false, ofxGrblPositionMode positionMode = OFXGRBL_ABSOLUTE);
	
	// Settings
	void saveSettings(const std::string& settingsFileName = "");
	void loadSettings(const std::string& settingsFileName = "");

	
	void send(const ofPath& path);
	void send(const ofPolyline& poly);
	void send(const std::vector<ofPolyline>& polys);
	void send(const std::vector<glm::vec3>& points);
	
	// force the z position of the polys and paths sent
	void send(const ofPath& path, float z);
	void send(const ofPolyline& poly, float z);
	void send(const std::vector<ofPolyline>& polys, float z);
	void send(const std::vector<glm::vec3>& points, float z);
	
	
	/// sets the device to use either millimeters or inches as the units being used for the commands. Default is millimeters
	/// Possible parameters passed are either OFXGRBL_MILLIMETERS or OFXGRBL_INCHES
	void setUnits(ofxGrblUnits newUnits);
	
	
	// events
	ofEvent<bool> UpDownEvent;
	ofEvent<glm::vec3> PositionEvent;
	
	ofRectangle getArea(){return areaRect;}
	
protected:
	
	glm::vec3 currentPos;
	string settingsFileName;
	vector<string> sendQueList;
	ofRectangle areaRect;
//	ofBuffer outputBuffer;
	void update(ofEventArgs&);
	ofEventListener updateListener;
//	bool bSendToFile = true;
	void sendUnits();
	void sendSettings();
	
	ofSerial serial;
	bool bConnected;
	bool isDeviceReady;
	string port;
	int baudrate;
	
private:
	
	
	float lastFeedRateSent = 0;
	string getFeedRateString(const float& newFeedrate);
	
	ofxGrblPositionMode positionMode = OFXGRBL_ABSOLUTE;
	string getPositionModeString(ofxGrblPositionMode newMode);
	
	bool firstTimeLoad;
	string status;
//	bool isPause;
	bool isReadyToSend;
	
	string readBuffer;

	bool isDown = false;
	bool bSpindle = false;
	
	vector<ofPolyline> polylines;
	
	// Grbl Settings
	ofxGrblSettings _settings;
	
	ofEventListeners settingsListeners;
	
};
}
