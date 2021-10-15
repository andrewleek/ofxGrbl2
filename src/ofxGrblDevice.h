//
//  ofxGrblDevice.hpp
//   ofxGrbl
//
//  Created by Roy Macdonald on 7/9/19.
//
//

#pragma once

#include "ofMain.h"
#include "ofxGrblSettings.h"

namespace ofxGrbl
{
    //class device;

    class device
    {
        public:
            
            device();
            
            // serial
            void connect(string _port, int _baudrate);
            bool isConnected();
            
            vector<std::string> getAvailablePorts();
            
            void close();
            
            void loadGCodeFromFile(const std::string& _path);
            
            void sendMessage(const std::string& _msg, bool direct = false);
            
            void clear();
            
            void setOrigin(const glm::vec3& _homePos);
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
            ofEvent<glm::vec3> PositionEvent;
            
            ofRectangle getArea(){return areaRect;}
            
            void penUp();
            void penDown();
            
            ofParameterGroup& getSettingsParams(){return _settings.parameters;}

            ofxGrblSettings& getSettings(){return _settings;}
                        
            bool canSend(){return isReadyToSend;}
            
        protected:
            
            void portChanged(std::string& port);
        //	void baudrateChanged(int& bd);
            ofEventListeners dropdownListeners;
            
            void populatePortsDropdown();
        //	void populateBaudratesDropdown();
            
            string vec3ToGcode( const glm::vec3& _vec);
            
            glm::vec3 currentPos;
            string settingsFileName;
            ofRectangle areaRect;

            void update(ofEventArgs&);
            ofEventListener updateListener;
            ofEventListener exitListener;
            
            void sendUnits();

            
            ofSerial serial;
            bool bConnected;
            bool isDeviceReady;
            ofParameter<string> port = {"port", ""};
        //	ofParameter<int> baudrate = {"baudrate", 115200, 300, 12000000};

            int baudrate = 115200;
            
            void _closeSerial();
            
        private:
            
            vector<string> sendQueList;

            float lastFeedRateSent[2] = {0.0, 0.0};
            
            string getFeedRateString(const float& newFeedrate, bool bRapidMovement);
            
            ofxGrblPositionMode positionMode = OFXGRBL_ABSOLUTE;
            string getPositionModeString(ofxGrblPositionMode newMode);
            
            string status;

            bool isReadyToSend;
            
            string readBuffer;

            bool isDown = false;
            bool bSpindle = false;
            
            vector<ofPolyline> polylines;
            
            ofxGrblSettings _settings;
            
            ofEventListeners settingsListeners;
    };
}
