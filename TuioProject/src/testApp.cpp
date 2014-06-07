#include "testApp.h"

int g_DistAlbumToPhoto1 = -150;
int g_DistAlbumToPhoto2 = 150;

//--------------------------------------------------------------
void PhotoAlbum::setup(){
	ofSetFrameRate(60);
	// Connect
	MyClient.connect(3333);

	ofAddListener(ofEvents().touchDown, this, &PhotoAlbum::touchDown);
	ofAddListener(ofEvents().touchMoved, this, &PhotoAlbum::touchMoved);
	ofAddListener(ofEvents().touchUp, this, &PhotoAlbum::touchUp);
	//ofAddListener(ofEvents().touchDoubleTap, this, &PhotoAlbum::touchDouble);
	
	m_OpenGLRenderer = new ofGLRenderer();

	m_PickedAlbumNum = -1;

	m_PhotoAlbums[0].loadImage("1.png");
	m_PhotoAlbums[1].loadImage("2.png");
	m_PhotoAlbums[2].loadImage("3.png");

	float startXPoint = 250.f;
	float startYPoint = 300.f;

	m_Photos[0].loadImage("1_1.png");
	m_Photos[1].loadImage("1_2.png");
	m_Photos[2].loadImage("1_3.png");
	m_Photos[3].loadImage("1_4.png");


	for (int i = 0 ; i<sizeof(m_PhotoAlbums)/ sizeof(m_PhotoAlbums[0]) ; ++i)
	{
		m_PhotoAlbums[i].setImgPosX(startXPoint+250*i);
		m_PhotoAlbums[i].setImgPosY(startYPoint);
		m_PhotoAlbums[i].setImgWidth(m_PhotoAlbums[i].getWidth());
		m_PhotoAlbums[i].setImgHeight(m_PhotoAlbums[i].getHeight());
		m_PhotoAlbums[i].setImgRotateAngle(0);

		//각 노트에 대한 위치 테스트를 위한 것임
// 		if (i == 0)
// 		{
			m_PhotoAlbums[i].setImgVisible(true);
//		}
		
	}
}

//--------------------------------------------------------------
void PhotoAlbum::update(){
	if (m_PickedAlbumNum>=0)
	{
		m_Photos[0].setImgPosX(m_PhotoAlbums[m_PickedAlbumNum].getImgPosX()+g_DistAlbumToPhoto1);
		m_Photos[0].setImgPosY(m_PhotoAlbums[m_PickedAlbumNum].getImgPosY()+g_DistAlbumToPhoto1);

		m_Photos[1].setImgPosX(m_PhotoAlbums[m_PickedAlbumNum].getImgPosX()+ 150);
		m_Photos[1].setImgPosY(m_PhotoAlbums[m_PickedAlbumNum].getImgPosY()- 150);

		m_Photos[2].setImgPosX(m_PhotoAlbums[m_PickedAlbumNum].getImgPosX()- 150);
		m_Photos[2].setImgPosY(m_PhotoAlbums[m_PickedAlbumNum].getImgPosY()+ 150);

		m_Photos[3].setImgPosX(m_PhotoAlbums[m_PickedAlbumNum].getImgPosX()+ 150);
		m_Photos[3].setImgPosY(m_PhotoAlbums[m_PickedAlbumNum].getImgPosY()+ 150);
	}
	
}

//--------------------------------------------------------------
void PhotoAlbum::draw(){

	for (int i = 0 ; i< sizeof(m_PhotoAlbums)/ sizeof(m_PhotoAlbums[0]); ++i)
	{
		if (m_PhotoAlbums[i].getVisible() == true)
		{
			m_OpenGLRenderer.pushMatrix();
			m_OpenGLRenderer.translate(m_PhotoAlbums[i].getImgPosX(), m_PhotoAlbums[i].getImgPosY());
			m_OpenGLRenderer.rotateZ(m_PhotoAlbums[i].getImgRotateAngle());

			m_OpenGLRenderer.draw(m_PhotoAlbums[i], 
				-m_PhotoAlbums[i].getImgWidth() / 2, -m_PhotoAlbums[i].getHeight() / 2, 0.0,
				m_PhotoAlbums[i].getImgWidth(), m_PhotoAlbums[i].getHeight(),
				0.0, 0.0,
				m_PhotoAlbums[i].getWidth(), m_PhotoAlbums[i].getHeight());
			m_OpenGLRenderer.popMatrix();
		}
	}

	for (int j = 0; j< sizeof(m_Photos)/sizeof(m_Photos[0]); ++j)
	{
		if (m_Photos[j].getVisible() == true)
		{
			m_OpenGLRenderer.pushMatrix();
			m_OpenGLRenderer.translate(m_Photos[j].getImgPosX(), m_Photos[j].getImgPosY());
			m_OpenGLRenderer.rotateZ(m_Photos[j].getImgRotateAngle());

			m_OpenGLRenderer.draw(m_Photos[j], 
				-m_Photos[j].getImgWidth() / 2, -m_Photos[j].getHeight() / 2, 0.0,
				m_Photos[j].getImgWidth(), m_Photos[j].getHeight(),
				0.0, 0.0,
				m_Photos[j].getWidth(), m_Photos[j].getHeight());
			m_OpenGLRenderer.popMatrix();
		}
	}
}

//--------------------------------------------------------------
void PhotoAlbum::keyPressed(int key){

}

//--------------------------------------------------------------
void PhotoAlbum::keyReleased(int key){

}

//--------------------------------------------------------------
void PhotoAlbum::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void PhotoAlbum::mouseDragged(int x, int y, int button){
// 	m_ImgPositionX = x;
// 	m_ImgPositionY = y;
// 	m_MyImage.setImgPosX(x);
// 	m_MyImage.setImgPosY(y);
	m_PhotoAlbums[m_PickedAlbumNum].setImgPosX(x);
	m_PhotoAlbums[m_PickedAlbumNum].setImgPosY(y);
}

//--------------------------------------------------------------
void PhotoAlbum::mousePressed(int x, int y, int button){
// 	m_MyImage.setImgPosX(x);
// 	m_MyImage.setImgPosY(y);
}

//--------------------------------------------------------------
void PhotoAlbum::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void PhotoAlbum::windowResized(int w, int h){

}

//--------------------------------------------------------------
int checkAlbums(ofTouchEventArgs& touch, TuioWrappedImg albums[])
{
	printf_s("%f , %f\n", (touch.x)*WINDOW_WIDTH, (touch.y)*WINDOW_HEIGHT);
	for (int i = 0 ; i<3 ; ++i)
	{
		if (albums[i].getImgPosX()<=touch.x*WINDOW_WIDTH && albums[i].getImgPosX()+albums[i].getImgWidth() >= touch.x*WINDOW_WIDTH
			&& albums[i].getImgPosY()<=touch.y*WINDOW_HEIGHT && albums[i].getImgPosY()+albums[i].getImgHeight() >= touch.y*WINDOW_HEIGHT)
		{
			//printf_s("터치 다운! %d \n %f, %f \n", i, touch.x*WINDOW_WIDTH, touch.y*WINDOW_HEIGHT);
			return i;
			break;
		}
	}

	return -1;
}


void PhotoAlbum::touchDown( ofTouchEventArgs & touch )
{
	TUIO::TuioCursor* cursor1 = nullptr;
	TUIO::TuioCursor* cursor2 = nullptr;
	TUIO::TuioCursor* cursor3 = nullptr;
	TUIO::TuioCursor* cursor4 = nullptr;


	if (MyClient.client->getTuioCursors().size() == 1)
	{
		m_PickedAlbumNum = checkAlbums(touch, m_PhotoAlbums);
		
		if (m_PickedAlbumNum == -1)
		{
			return;
		}

		DefaultSpreadPhoto(m_PickedAlbumNum);

		//더블탭 구현 해야지
		touch.time = ofGetElapsedTimeMillis();
		m_touches.push_back(touch);

		if (m_touches.size()>=3)
		{
			if (m_touches[2].time - m_touches[1].time < 1000)
			{
				ShowOffPhoto();
				m_touches.clear();
			}
			else
			{
				m_touches.clear();
				
				//더미 터치를 넣어 항상 2,1이 비교 되도록 함
				m_touches.push_back(touch);
			}
		}


	}

	

	
	if ( MyClient.client->getTuioCursors().size() == 2 )
	{
		for ( auto *iter : MyClient.client->getTuioCursors() )
		{
			switch ( iter->getCursorID() )
			{
			case 0:
				cursor1 = iter;
				break;
			case 1:
				cursor2 = iter;
				break;
			default:
				break;
			}
		}

		// 방어코드
		if (cursor1 == nullptr || cursor2 == nullptr)
		{
			return;
		}

		//시연목적상 1개 사진에 대해서만 실행
		m_Photos[0].setImgWidth(abs( cursor1->getX() - cursor2->getX() ) * WINDOW_WIDTH * 2);
		m_Photos[0].setImgHeight(abs( cursor1->getY() - cursor2->getY() ) * WINDOW_HEIGHT * 2);

	}

	if ( MyClient.client->getTuioCursors().size() == 3 )
	{
		for ( auto *iter : MyClient.client->getTuioCursors() )
		{
			switch ( iter->getCursorID() )
			{
			case 0:
				cursor1 = iter;
				break;
			case 1:
				cursor2 = iter;
				break;
			default:
				break;
			}
		}

		// 방어코드
		if (cursor1 == nullptr || cursor2 == nullptr)
		{
			return;
		}
			
		double tempAngle = ( cursor1->getY() - cursor2->getY() ) / ( cursor1->getX() - cursor2->getX() );

		//시연목적상 1개 사진에 대해서만 실행
		m_Photos[0].setImgRotateAngle(180.0 * PI * atan(tempAngle));
	}

	if ( MyClient.client->getTuioCursors().size() == 4 )
	{
		for ( auto *iter : MyClient.client->getTuioCursors() )
		{
			switch ( iter->getCursorID() )
			{
			case 0:
				cursor1 = iter;
				break;
			case 1:
				cursor2 = iter;
				break;
			case 2:
				cursor3 = iter;
			case 3:
				cursor4 = iter;
			default:
				break;
			}
		}

		// 방어코드
		if (cursor1 == nullptr || cursor4 == nullptr )
		{
			return;
		}

		printf_s("4개다!\n");

		m_XDist = abs( cursor1->getX() - cursor4->getX() ) * WINDOW_WIDTH * 2;
		m_YDist = abs( cursor1->getY() - cursor4->getY() ) * WINDOW_HEIGHT * 2;
		
	}
}

void PhotoAlbum::touchMoved( ofTouchEventArgs & touch )
{
	TUIO::TuioCursor* cursor1 = nullptr;
	TUIO::TuioCursor* cursor2 = nullptr;
	TUIO::TuioCursor* cursor3 = nullptr;
	TUIO::TuioCursor* cursor4 = nullptr;

	if ( MyClient.client->getTuioCursors().size() == 2 )
	{
		for ( auto *iter : MyClient.client->getTuioCursors() )
		{
			switch ( iter->getCursorID() )
			{
			case 0:
				cursor1 = iter;
				break;
			case 1:
				cursor2 = iter;
				break;
			default:
				break;
			}
		}

		// 방어코드
		if (cursor1 == nullptr || cursor2 == nullptr)
		{
			return;
		}

		m_Photos[0].setImgWidth(abs( cursor1->getX() - cursor2->getX() ) * WINDOW_WIDTH * 2);
		m_Photos[0].setImgHeight(abs( cursor1->getY() - cursor2->getY() ) * WINDOW_HEIGHT * 2);
	}

	// rotate
	if ( MyClient.client->getTuioCursors().size() == 3 )
	{
		for ( auto *iter : MyClient.client->getTuioCursors() )
		{
			switch ( iter->getCursorID() )
			{
			case 0:
				cursor1 = iter;
				break;
			case 1:
				cursor2 = iter;
				break;
			default:
				break;
			}
		}

		// 방어코드
		if (cursor1 == nullptr || cursor2 == nullptr)
		{
			return;
		}
		// 포인트 1과 2의 기울기를 기준으로 회전시킨다.
		double tempAngle = ( cursor1->getY() - cursor2->getY() ) / ( cursor1->getX() - cursor2->getX() );
		m_Photos[0].setImgRotateAngle(180.0 * PI * atan(tempAngle));
	}


	if ( MyClient.client->getTuioCursors().size() == 4 )
	{
		for ( auto *iter : MyClient.client->getTuioCursors() )
		{
			switch ( iter->getCursorID() )
			{
			case 0:
				cursor1 = iter;
				break;
			case 1:
				cursor2 = iter;
				break;
			case 2:
				cursor3 = iter;
			case 3:
				cursor4 = iter;
			default:
				break;
			}
		}

		// 방어코드
		if (cursor1 == nullptr || cursor4 == nullptr )
		{
			return;
		}

		float xDist = abs( cursor1->getX() - cursor4->getX() ) * WINDOW_WIDTH * 2;
		float yDist = abs( cursor1->getY() - cursor4->getY() ) * WINDOW_HEIGHT * 2;

		if (m_XDist>xDist || m_YDist>yDist)
		{
			if (g_DistAlbumToPhoto1<0 && g_DistAlbumToPhoto2>0)
			{
				g_DistAlbumToPhoto1 +=3;
				g_DistAlbumToPhoto2 -=3;
			}
			

			AllocatePhoto(1, g_DistAlbumToPhoto1, g_DistAlbumToPhoto2);
		}
		else if (m_XDist<xDist || m_YDist<yDist)
		{
			if (g_DistAlbumToPhoto1<0 && g_DistAlbumToPhoto2>0)
			{
			}
			g_DistAlbumToPhoto1 -= 3;
			g_DistAlbumToPhoto2 += 3;

			AllocatePhoto(1, g_DistAlbumToPhoto1, g_DistAlbumToPhoto2);
		}
	}
}

void PhotoAlbum::touchUp( ofTouchEventArgs & touch )
{
	m_PickedAlbumNum = -1;
}


void PhotoAlbum::DefaultSpreadPhoto(int PickedAlbumNum)
{
	g_DistAlbumToPhoto1 = -150;
	g_DistAlbumToPhoto2 = 150;

	AllocatePhoto(PickedAlbumNum, g_DistAlbumToPhoto1,g_DistAlbumToPhoto2);
	
	for (int i = 0 ; i < 4 ; ++i)
	{
		m_Photos[i].setImgWidth(m_Photos[i].getWidth());
		m_Photos[i].setImgHeight(m_Photos[i].getHeight());
		m_Photos[i].setImgRotateAngle(0);

		m_Photos[i].setImgVisible(true);
	}
}

void PhotoAlbum::AllocatePhoto(int PickedAlbumNum, int dist1, int dist2 )
{
	m_Photos[0].setImgPosX(m_PhotoAlbums[PickedAlbumNum].getImgPosX()+dist1);
	m_Photos[0].setImgPosY(m_PhotoAlbums[PickedAlbumNum].getImgPosY()+dist1);

	m_Photos[1].setImgPosX(m_PhotoAlbums[PickedAlbumNum].getImgPosX()+ dist2);
	m_Photos[1].setImgPosY(m_PhotoAlbums[PickedAlbumNum].getImgPosY()+dist1);

	m_Photos[2].setImgPosX(m_PhotoAlbums[PickedAlbumNum].getImgPosX()+ dist1);
	m_Photos[2].setImgPosY(m_PhotoAlbums[PickedAlbumNum].getImgPosY()+ dist2);

	m_Photos[3].setImgPosX(m_PhotoAlbums[PickedAlbumNum].getImgPosX()+ dist2);
	m_Photos[3].setImgPosY(m_PhotoAlbums[PickedAlbumNum].getImgPosY()+ dist2);
}

void PhotoAlbum::ShowOffPhoto()
{
	for (int i = 0 ; i < 4 ; ++i)
	{
		m_Photos[i].setImgVisible(false);
	}
}


