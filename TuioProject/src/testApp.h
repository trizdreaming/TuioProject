#pragma once

#include "ofMain.h"
#include "ofxTuioClient.h"
// for openGL
#include "ofGLRenderer.h"
#include "TuioWrappedImg.h"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768

class PhotoAlbum : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);

	// added to Example
		ofxTuioClient MyClient;

		void touchDown(ofTouchEventArgs & touch);
		void touchMoved(ofTouchEventArgs & touch);
		void touchUp(ofTouchEventArgs & touch);
		//뭔가 동작이 잘 안된다
//		void touchDouble(ofTouchEventArgs& touch);

		void DefaultSpreadPhoto(int PickedAlbumNum);
		void AllocatePhoto(int PickedAlbumNum,int dist1, int dist2);
		void ShowOffPhoto();

private:
	ofGLRenderer m_OpenGLRenderer;

	TuioWrappedImg m_PhotoAlbums[3];
	TuioWrappedImg m_Photos[4];

	int m_PickedAlbumNum;

	float m_XDist;
	float m_YDist;
	
	std::vector<ofTouchEventArgs> m_touches;
};
