#pragma once
#include "ofImage.h"

class TuioWrappedImg:public ofImage
{
public:
	TuioWrappedImg(void);
	~TuioWrappedImg(void);

	float getImgPosX(){return m_ImgPositionX;}
	float getImgPosY(){return m_ImgPositionY;}

	float getImgWidth(){return m_ImgWidth;}
	float getImgHeight(){return m_ImgHeight;}

	float getImgRotateAngle(){return m_ImgRotateAngle;}
	bool getVisible(){return m_Visible;}


	void setImgPosX(float input){m_ImgPositionX = input;}
	void setImgPosY(float input){m_ImgPositionY = input;}

	void setImgWidth(float input){m_ImgWidth = input;}
	void setImgHeight(float input){m_ImgHeight = input;}

	void setImgRotateAngle(float input){m_ImgRotateAngle = input;}

	void setImgVisible(bool input){m_Visible = input;}

private:
	float m_ImgPositionX;
	float m_ImgPositionY;
	float m_ImgWidth;
	float m_ImgHeight;
	float m_ImgRotateAngle;

	bool m_Visible;
};

