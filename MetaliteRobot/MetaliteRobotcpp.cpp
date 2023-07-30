
#include <Windows.h>
#include <gl/GL.h>
#include <Math.h>
#include <gl/GLU.h>
#include <ctime>

#pragma comment (lib, "OpenGL32.lib")
#define WINDOW_TITLE "OpenGL Window"

//KEYS DEFINITION
#define VK_0 0x30
#define VK_1 0x31
#define VK_2 0x32
#define VK_3 0x33
#define VK_4 0x34
#define VK_5 0x35
#define VK_6 0x36
#define VK_7 0x37
#define VK_8 0x38
#define VK_9 0x39

#define VK_A 0x41
#define VK_D 0x44
#define VK_T 0x54
#define VK_W 0x57
#define VK_Q 0x51	
#define VK_E 0x45
#define VK_L 0x4C
#define VK_R 0x52
#define VK_J 0x4A
#define VK_F 0x46
#define VK_Z 0x5A
#define VK_X 0x58
#define VK_S 0x53
#define VK_C 0x43


//Elipse
clock_t currentTicks;
clock_t elapsedTicks;
float elapsedSeconds;

double camRotateSpeed = 200.0f;

//----------------------------------

int key = 0;
float angle = 0;
bool isOrtho = true;
float z = 90, y = 10, zoom = 0;
GLUquadric* obj = NULL;

//Texture Variables
GLuint textureBlackCore = 0, textureMetalGrey = 0, textureMetalBlue = 0, textureRedLamp = 0, textureNuclear = 0, textureMetalBlueShine = 0, textureRubberGrey = 0, textureViolet = 0, textureWhiteMetal = 0;
GLuint textureFace = 0, textureGreenDiamond = 0, textureLaser = 0;
GLuint textureBackground = 0;
BITMAP BMP;
HBITMAP hBMP = NULL;
int textureNo = 0;

//Color
bool colorSwitch = true;
float indigo[] = { 0, 0, 1, 1 };
float silver[] = { (float)128 / 255, (float)128 / 255 , (float)128 / 255, 1 };
float grey[] = { (float)64 / 255, (float)64 / 255 , (float)64 / 255, 1 };
float green[] = { (float)124 / 255, (float)252 / 255, 0, 1 };
float darkBlue[] = { 0, 0.1 , 0.6, 1 };
float red[] = { 1, 0,0,1 };
float lightBlue[] = { 0.85, 0.97, 0.99, 1 };
float darkRed[] = { 0.8, 0.17, 0.12 ,1 };


//Walking Variables
float movement = 0;
float leftUpperLegRotateX = 0, leftLowerLegRotateX = 0, rightUpperLegRotateX = 0, rightLowerLegRotateX = 0;
float leftUpperArmRotateX = 0, leftLowerArmRotateX = 0, rightUpperArmRotateX = 0, rightLowerArmRotateX = 0;
float bodyRotateY = 0, bodyRotateX = 0;
float wholeBodyRotateY = 0;

float headRotateY = 0, headRotateX = 0;
bool left = true;

bool walkDirection = true;
bool bodyChange = false;

//Jump Variables
bool startJump = true;
bool ready = false;
bool jump = false;
bool down = false;
bool press = false;
bool endJump = false;
float wholeBodyTranslateX = 0, wholeBodyTranslateY = 0, wholeBodyTranslateZ = 0;

//Fly variable
float leftUpperLegRotateY = 0, leftLowerLegRotateY = 0, rightUpperLegRotateY = 0, rightLowerLegRotateY = 0;
float leftUpperArmRotateY = 0, leftLowerArmRotateY = 0, rightUpperArmRotateY = 0, rightLowerArmRotateY = 0;
float leftUpperLegRotateZ = 0, leftLowerLegRotateZ = 0, rightUpperLegRotateZ = 0, rightLowerLegRotateZ = 0;
float leftUpperArmRotateZ = 0, leftLowerArmRotateZ = 0, rightUpperArmRotateZ = 0, rightLowerArmRotateZ = 0;
float rocketLeftRotateX = 0, rocketRightRotateX = 0;
bool fly = false;
bool startFly = true;
bool midFly = false;
bool flyArmSet = false;
bool flyFeetSet = false;
bool rocketMove = false, rocketLeft = true;

//Sword Attack variable
float rightHandRotateX = 0, rightHandRotateY = 0, rightHandRotateZ = 0;
float leftHandRotateX = 0, leftHandRotateY = 0, leftHandRotateZ = 0;
bool swordAtkPose = false;
bool swordAtkAni = false;
bool firstSlashPose = false;
bool secondSlashPose = false;
bool firstSlash = false;
bool firstSlashReset = false;
bool secondSlash = false;

//Weapon Variables
bool on = false;
bool gunOn = false;
bool shieldOn = false;
float scale = 0, gunScale = 0, shieldScale = 0;
float shieldAngle = 0;

//Shoot Vairables
bool shoot = false;
float bulletTranslate = 0;
bool onLaser = false;
bool turnShield = false;

//Defense Variables
bool defense = false, handDown = false;
float shieldHeight[] = { 20,20,20 };
bool shieldDown1 = false, shieldDown2 = false, shieldDown3 = false;

//Lighting Variables
bool lightOn = false;
float lightX = -10, lightY = 25, lightZ = -15;
GLfloat defaultAmbient[4] = { 0.2, 0.2, 0.2, 1 };
GLfloat defaultDiffuse[4] = { 0.8, 0.8, 0.8, 1 };
GLfloat ambientLight[4] = { 0, 0, 0, 1 };//RGBA
GLfloat diffuseLight[4] = { 1, 1, 1, 1 };//RGBA

void lighting() {

	glLightfv(GL_LIGHT7, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT7, GL_DIFFUSE, diffuseLight);
	glEnable(GL_LIGHT7);
	glEnable(GL_LIGHTING);
	//glEnable(GL_COLOR_MATERIAL);

}

//RESET VALUES HERE
void reset() {

	//Head
	headRotateY = 0;
	headRotateX = 0;

	//Legs
	leftLowerLegRotateX = 0;
	leftUpperLegRotateX = 0;
	rightLowerLegRotateX = 0;
	rightUpperLegRotateX = 0;
	leftLowerLegRotateY = 0;
	leftUpperLegRotateY = 0;
	rightLowerLegRotateY = 0;
	rightUpperLegRotateY = 0;
	leftLowerLegRotateZ = 0;
	leftUpperLegRotateZ = 0;
	rightLowerLegRotateZ = 0;
	rightUpperLegRotateZ = 0;
	left = true;
	walkDirection = true;

	//Arms
	leftUpperArmRotateX = 0;
	leftLowerArmRotateX = 0;
	rightUpperArmRotateX = 0;
	rightLowerArmRotateX = 0;
	leftUpperArmRotateY = 0;
	leftLowerArmRotateY = 0;
	rightUpperArmRotateY = 0;
	rightLowerArmRotateY = 0;
	leftUpperArmRotateZ = 0;
	leftLowerArmRotateZ = 0;
	rightUpperArmRotateZ = 0;
	rightLowerArmRotateZ = 0;

	//Hands
	rightHandRotateX = 0;
	rightHandRotateY = 0;
	rightHandRotateZ = 0;
	leftHandRotateX = 0;
	leftHandRotateY = 0;
	leftHandRotateZ = 0;

	//Body
	bodyRotateY = 0;
	bodyRotateX = 0;
	wholeBodyTranslateX = 0;
	wholeBodyTranslateY = 0;
	wholeBodyTranslateZ = 0;
	wholeBodyRotateY = 0;
	bodyChange = false;

	//Rocket
	rocketLeftRotateX = 0;
	rocketRightRotateX = 0;


	startJump = true;
	ready = false;
	jump = false;
	down = false;
	press = false;
	endJump = false;

	//Fly
	fly = false;
	startFly = true;
	midFly = false;
	flyArmSet = false;
	flyFeetSet = false;
	rocketMove = false;
	rocketLeft = true;

	//Attack (Sword)
	swordAtkAni = false;
	swordAtkPose = false;
	firstSlashPose = false;
	secondSlashPose = false;
	firstSlash = false;
	secondSlash = false;
	firstSlashReset = false;

	//Light
	lightX = -10;
	lightY = 25;
	lightZ = -15;
	lightOn = false;

	shoot = false;
	bulletTranslate = 0;
	onLaser = false;
	turnShield = false;

	//Defense
	defense = false;
	handDown = false;
	shieldHeight[0] = 20;
	shieldHeight[1] = 20;
	shieldHeight[2] = 20;
	shieldDown1 = false;
	shieldDown2 = false;
	shieldDown3 = false;

	//Weapons
	/*on = false;
	shieldOn = false;
	gunOn = false;*/

	zoom = 0;

	glLoadIdentity();
}

//Reset Camera 
void cameraReset() {
	z = 90;
	y = 10;
}

void camera() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (isOrtho) {
		glOrtho(-35, 35, -35, 35, 0.1, 1000);
	}
	else {
		gluPerspective(120, 8 / 6, 0.1, 1000);
	}
}

void texture1Initialization() {
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"coreBlack.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);
	glGenTextures(1, &textureBlackCore);
	glBindTexture(GL_TEXTURE_2D, textureBlackCore);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);
	DeleteObject(hBMP);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"greyMetal.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);//ice fire
	GetObject(hBMP, sizeof(BMP), &BMP);
	glGenTextures(1, &textureMetalGrey);
	glBindTexture(GL_TEXTURE_2D, textureMetalGrey);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);
	DeleteObject(hBMP);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"blueMetalic.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);
	glGenTextures(1, &textureMetalBlue);
	glBindTexture(GL_TEXTURE_2D, textureMetalBlue);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);
	DeleteObject(hBMP);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"blueMetal.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);
	glGenTextures(1, &textureMetalBlueShine);
	glBindTexture(GL_TEXTURE_2D, textureMetalBlueShine);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);
	DeleteObject(hBMP);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"greyRubber.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);
	glGenTextures(1, &textureRubberGrey);
	glBindTexture(GL_TEXTURE_2D, textureRubberGrey);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);
	DeleteObject(hBMP);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"redLamp.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);
	glGenTextures(1, &textureRedLamp);
	glBindTexture(GL_TEXTURE_2D, textureRedLamp);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);
	DeleteObject(hBMP);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"nuclear.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);
	glGenTextures(1, &textureNuclear);
	glBindTexture(GL_TEXTURE_2D, textureNuclear);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);
	DeleteObject(hBMP);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"face.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);
	glGenTextures(1, &textureFace);
	glBindTexture(GL_TEXTURE_2D, textureFace);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);
	DeleteObject(hBMP);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"greenDiamond.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);
	glGenTextures(1, &textureGreenDiamond);
	glBindTexture(GL_TEXTURE_2D, textureGreenDiamond);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);
	DeleteObject(hBMP);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"violetTexture.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);
	glGenTextures(1, &textureViolet);
	glBindTexture(GL_TEXTURE_2D, textureViolet);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);
	DeleteObject(hBMP);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"whitemetal.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);
	glGenTextures(1, &textureWhiteMetal);
	glBindTexture(GL_TEXTURE_2D, textureWhiteMetal);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);
	DeleteObject(hBMP);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"background.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);
	glGenTextures(1, &textureBackground);
	glBindTexture(GL_TEXTURE_2D, textureBackground);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);
	DeleteObject(hBMP);

}

void texture2Initialization() {
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"icefire.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);//ice fire
	GetObject(hBMP, sizeof(BMP), &BMP);
	glGenTextures(1, &textureMetalGrey);
	glBindTexture(GL_TEXTURE_2D, textureMetalGrey);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);
	DeleteObject(hBMP);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"icefire.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);
	glGenTextures(1, &textureMetalBlue);
	glBindTexture(GL_TEXTURE_2D, textureMetalBlue);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);
	DeleteObject(hBMP);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"redfire.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);
	glGenTextures(1, &textureMetalBlueShine);
	glBindTexture(GL_TEXTURE_2D, textureMetalBlueShine);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);
	DeleteObject(hBMP);
}

void texture3Initialization() {
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"galaxy.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);//ice fire
	GetObject(hBMP, sizeof(BMP), &BMP);
	glGenTextures(1, &textureMetalGrey);
	glBindTexture(GL_TEXTURE_2D, textureMetalGrey);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);
	DeleteObject(hBMP);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"galaxy1.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);
	glGenTextures(1, &textureMetalBlue);
	glBindTexture(GL_TEXTURE_2D, textureMetalBlue);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);
	DeleteObject(hBMP);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"galaxy1.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);
	glGenTextures(1, &textureMetalBlueShine);
	glBindTexture(GL_TEXTURE_2D, textureMetalBlueShine);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);
	DeleteObject(hBMP);
}

void texture4Initialization() {
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"electric.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);//ice fire
	GetObject(hBMP, sizeof(BMP), &BMP);
	glGenTextures(1, &textureMetalGrey);
	glBindTexture(GL_TEXTURE_2D, textureMetalGrey);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);
	DeleteObject(hBMP);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"electric2.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);
	glGenTextures(1, &textureMetalBlue);
	glBindTexture(GL_TEXTURE_2D, textureMetalBlue);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);
	DeleteObject(hBMP);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"electric2.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);
	glGenTextures(1, &textureMetalBlueShine);
	glBindTexture(GL_TEXTURE_2D, textureMetalBlueShine);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);
	DeleteObject(hBMP);
}

void switchColorText() {
	if (colorSwitch) {
		//Enable color
		glDisable(GL_TEXTURE_2D);
	}
	else {
		//Disable color
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
		glEnable(GL_TEXTURE_2D);
	}
}

void walkingAnimation() {
	if (leftUpperLegRotateX >= -28 && left) {
		movement += 0.1;
		if (bodyRotateY < 1.96) {
			bodyRotateY += 0.07;
		}
		if (walkDirection) {
			leftUpperLegRotateX -= 1;
			if (leftLowerLegRotateX < 0) {
				leftLowerLegRotateX += 2;
			}
			if (rightLowerLegRotateX < 0) {
				rightLowerLegRotateX += 2;
			}
			rightUpperLegRotateX += 1;

			if (leftUpperLegRotateX <= -28) {
				walkDirection = !walkDirection;
			}

			//Arm Animation
			if (leftUpperArmRotateX < 14) {
				leftUpperArmRotateX += 0.5;
			}
			rightLowerArmRotateX -= 1;
			rightUpperArmRotateX -= 0.5;

		}
		else {
			if (bodyRotateY > 0) {
				bodyRotateY -= 0.14;
			}
			leftUpperLegRotateX += 1;
			rightUpperLegRotateX -= 1;
			rightLowerLegRotateX -= 2;

			if (leftUpperArmRotateX > 0) {
				leftUpperArmRotateX -= 0.5;
			}
			rightLowerArmRotateX += 1;
			rightUpperArmRotateX += 0.5;

			if (leftUpperLegRotateX >= 0) {
				left = !left;
				walkDirection = !walkDirection;
			}

		}
	}
	else if (rightUpperLegRotateX >= -28 && !left) {
		movement += 0.1;
		if (bodyRotateY > -1.96) {
			bodyRotateY -= 0.07;
		}
		if (walkDirection) {
			rightUpperLegRotateX -= 1;
			if (leftLowerLegRotateX < 0) {
				leftLowerLegRotateX += 2;
			}
			if (rightLowerLegRotateX < 0) {
				rightLowerLegRotateX += 2;
			}
			leftUpperLegRotateX += 1;

			if (rightUpperLegRotateX <= -28) {
				walkDirection = !walkDirection;
			}

			//Arm Animation
			if (rightUpperArmRotateX < 14) {
				rightUpperArmRotateX += 0.5;
			}
			leftUpperArmRotateX -= 0.5;
			leftLowerArmRotateX -= 1;

		}
		else {
			if (bodyRotateY < 0) {
				bodyRotateY += 0.14;
			}
			rightUpperLegRotateX += 1;
			leftUpperLegRotateX -= 1;
			leftLowerLegRotateX -= 2;

			if (rightUpperArmRotateX > 0) {
				rightUpperArmRotateX -= 0.5;
			}
			leftUpperArmRotateX += 0.5;
			leftLowerArmRotateX += 1;

			if (rightUpperLegRotateX >= 0) {
				left = !left;
				walkDirection = !walkDirection;
			}
		}
	}


}

void runningAnimation() {
	//Left leg
	if (leftUpperLegRotateX > -90 && walkDirection && left) {
		leftUpperLegRotateX -= 5;
		leftLowerLegRotateX -= 5;
		if (leftUpperLegRotateX == -90) {
			walkDirection = !walkDirection;
		}

		if (rightUpperLegRotateX < 0) {
			rightUpperLegRotateX += 5;
			rightLowerLegRotateX += 5;
		}

		//Right Arm
		if (rightUpperArmRotateX > -45) {
			rightUpperArmRotateX -= 3;
			rightLowerArmRotateX -= 5;
		}

		//Left Arm
		if (leftUpperArmRotateX < 9) {
			leftUpperArmRotateX += 3;
			leftLowerArmRotateX += 5;
		}


	}

	if (leftUpperLegRotateX < 0 && !walkDirection && left) {
		leftUpperLegRotateX += 5;
		leftLowerLegRotateX += 5;
		if (rightUpperLegRotateX > -90) {
			rightUpperLegRotateX -= 5;
			rightLowerLegRotateX -= 5;
			if (rightUpperLegRotateX == -90) {
				left = !left;
			}
		}

		//Right Arm
		if (rightUpperArmRotateX < 9) {
			rightUpperArmRotateX += 3;
			rightLowerArmRotateX += 5;
		}

		//Left Arm
		if (leftUpperArmRotateX > -45) {
			leftUpperArmRotateX -= 3;
			leftLowerArmRotateX -= 5;
		}

		if (leftUpperLegRotateX == 0) {
			walkDirection = !walkDirection;
		}



	}

	//Right leg
	if (rightUpperLegRotateX < 0 && walkDirection && !left) {
		rightUpperLegRotateX += 5;
		rightLowerLegRotateX += 5;
		if (leftUpperLegRotateX > -90) {
			leftUpperLegRotateX -= 5;
			leftLowerLegRotateX -= 5;
			if (leftUpperLegRotateX == -90) {
				walkDirection = !walkDirection;
			}
		}
		if (rightUpperLegRotateX == -90) {
			walkDirection = !walkDirection;
		}

		//Right Arm
		if (rightUpperArmRotateX > -45) {
			rightUpperArmRotateX -= 3;
			rightLowerArmRotateX -= 5;
		}

		//Left Arm
		if (leftUpperArmRotateX < 9) {
			leftUpperArmRotateX += 3;
			leftLowerArmRotateX += 5;
		}


	}

	if (rightUpperLegRotateX > -90 && !walkDirection && !left) {
		rightUpperLegRotateX -= 5;
		rightLowerLegRotateX -= 5;
		if (leftUpperLegRotateX < 0) {
			leftUpperLegRotateX += 5;
			leftLowerLegRotateX += 5;
		}
		if (rightUpperLegRotateX == -90) {
			left = !left;
		}
		if (rightUpperLegRotateX == -90) {
			walkDirection = !walkDirection;
		}

		//Right Arm
		if (rightUpperArmRotateX < 9) {
			rightUpperArmRotateX += 3;
			rightLowerArmRotateX += 5;
		}

		//Left Arm
		if (leftUpperArmRotateX > -45) {
			leftUpperArmRotateX -= 3;
			leftLowerArmRotateX -= 5;
		}

	}

	//Body
	if (bodyChange) {
		bodyRotateY -= 2;
		if (bodyRotateY <= -18) {
			bodyChange = !bodyChange;
		}
	}
	else if (!bodyChange) {
		bodyRotateY += 2;
		if (bodyRotateY >= 18) {
			bodyChange = !bodyChange;
		}
	}

	if (bodyRotateX < 25) {
		bodyRotateX += 0.5;
	}

	//Head
	if (headRotateX > -15) {
		headRotateX -= 1;
	}
}

void jumpAnimation() {

	if (leftUpperLegRotateX > -45 && !ready && !endJump && startJump) {
		leftUpperLegRotateX -= 0.05;
		rightUpperLegRotateX -= 0.05;
		leftLowerLegRotateX -= 0.05;
		rightLowerLegRotateX -= 0.05;

		leftUpperArmRotateX -= 0.025;
		rightUpperArmRotateX -= 0.025;
		leftLowerArmRotateX -= 0.025;
		rightLowerArmRotateX -= 0.025;

		wholeBodyTranslateY -= 0.005;
		bodyRotateX += 0.025;

		if (leftUpperLegRotateX <= -45) {
			ready = true;
			startJump = !startJump;
		}
	}

	if (ready && leftUpperLegRotateX < -15) {
		leftUpperLegRotateX += 0.05;
		rightUpperLegRotateX += 0.05;
		leftLowerLegRotateX += 0.05;
		rightLowerLegRotateX += 0.05;
		wholeBodyTranslateY += 0.025;
		wholeBodyTranslateZ += 0.005;

		leftUpperArmRotateX += 0.025;
		rightUpperArmRotateX += 0.025;
		leftLowerArmRotateX += 0.025;
		rightLowerArmRotateX += 0.025;

		bodyRotateX -= 0.015;

		if (leftUpperLegRotateX >= -15) {
			down = true;
			ready = !ready;
		}

	}

	if (down && wholeBodyTranslateY > 0) {
		leftUpperLegRotateX -= 0.05;
		rightUpperLegRotateX -= 0.05;
		leftLowerLegRotateX -= 0.05;
		rightLowerLegRotateX -= 0.05;
		wholeBodyTranslateY -= 0.025;
		wholeBodyTranslateZ += 0.005;

		leftUpperArmRotateX -= 0.025;
		rightUpperArmRotateX -= 0.025;
		leftLowerArmRotateX -= 0.025;
		rightLowerArmRotateX -= 0.025;

		bodyRotateX += 0.03;

		if (wholeBodyTranslateY <= 0) {
			down = !down;
			press = true;
		}
	}

	if (press && leftUpperLegRotateX > -60) {
		leftUpperLegRotateX -= 0.05;
		rightUpperLegRotateX -= 0.05;
		leftLowerLegRotateX -= 0.05;
		rightLowerLegRotateX -= 0.05;
		wholeBodyTranslateY -= 0.0075;

		leftUpperArmRotateX -= 0.025;
		rightUpperArmRotateX -= 0.025;
		leftLowerArmRotateX -= 0.025;
		rightLowerArmRotateX -= 0.025;

		if (bodyRotateX > 0) {
			bodyRotateX -= 0.015;
		}
		if (leftUpperLegRotateX <= -60) {
			endJump = true;
			press = !press;
		}
	}

	if (endJump && leftUpperLegRotateX < -15) {
		leftUpperLegRotateX += 0.025;
		rightUpperLegRotateX += 0.025;
		leftLowerLegRotateX += 0.025;
		rightLowerLegRotateX += 0.025;
		wholeBodyTranslateY += 0.002;

		if (leftUpperArmRotateX < 0) {
			leftUpperArmRotateX += 0.025;
			rightUpperArmRotateX += 0.025;
			leftLowerArmRotateX += 0.025;
			rightLowerArmRotateX += 0.025;
		}


		if (leftUpperLegRotateX >= -15) {
			endJump = !endJump;
		}
	}
	bool complete = true;
	if (endJump) {
		if (leftUpperArmRotateX < 0) {
			leftUpperArmRotateX += 0.025;
			rightUpperArmRotateX += 0.025;
			leftLowerArmRotateX += 0.025;
			rightLowerArmRotateX += 0.025;
			complete = false;
		}

		if (leftUpperLegRotateX < 0) {
			leftUpperLegRotateX += 0.025;
			rightUpperLegRotateX += 0.025;
			leftLowerLegRotateX += 0.025;
			rightLowerLegRotateX += 0.025;
			complete = false;
		}

		if (bodyRotateX > 0) {
			bodyRotateX -= 0.0125;
			complete = false;
		}

		if (complete) {
			jump = !jump;
		}
	}
}

void flyAnimation() {
	//Take off
	if (rightUpperArmRotateZ > -25 && startFly) {
		rightUpperArmRotateZ -= 0.06;
		leftUpperArmRotateZ += 0.06;

		if (rightUpperLegRotateZ < 7) {
			rightUpperLegRotateZ += 0.045;
			leftUpperLegRotateZ -= 0.045;
		}

		if (rightUpperArmRotateZ <= -25) {
			startFly = !startFly;
		}
	}

	if (wholeBodyTranslateY < 13 && !startFly) {
		wholeBodyTranslateY += 0.025;

		if (wholeBodyTranslateY >= 7) {
			midFly = true;
		}
	}

	//Mid-flying after takeoff
	if (midFly) {
		if (bodyRotateX < 70) {
			bodyRotateX += 0.035;
			headRotateX -= 0.035;
			rightUpperLegRotateX -= 0.04;
			leftUpperLegRotateX -= 0.04;

			//Delay leg rotation ; flying
			if (bodyRotateX > 15) {
				if (rightUpperLegRotateZ > 0) {
					rightUpperLegRotateZ -= 0.015;
					leftUpperLegRotateZ += 0.015;
				}
			}

			//Arm rotation ; flying pose
			rightUpperArmRotateZ += 0.015;
			rightUpperArmRotateX -= 0.045;
			rightUpperArmRotateY -= 0.045;
			rightLowerArmRotateZ += 0.055;
			rightLowerArmRotateX -= 0.045;

			leftLowerArmRotateX -= 0.07;
			leftLowerArmRotateZ += 0.025;
			leftUpperArmRotateZ -= 0.015;
			leftUpperArmRotateY -= 0.045;
			leftUpperArmRotateX -= 0.02;

			//Position leg after delay
			if (bodyRotateX >= 40) {
				rightUpperLegRotateX += 0.1;
				leftUpperLegRotateX += 0.1;
				flyArmSet = true;
			}

			//finalize flying pose
			if (flyArmSet) {
				rightLowerArmRotateY += 0.08;
				rightUpperArmRotateX -= 0.08;

				rightUpperLegRotateX -= 0.05;
				rightLowerLegRotateX -= 0.1;

				leftUpperLegRotateX -= 0.02;
				leftLowerLegRotateX -= 0.04;

				rocketMove = true;
			}
		}
	}
}

void rocketAnimation() {
	if (rocketLeftRotateX < 30 && rocketLeft) {
		rocketLeftRotateX += 0.1;
		if (rocketRightRotateX >= 0 && rocketLeft) {
			rocketRightRotateX -= 0.1;
		}
		if (rocketLeftRotateX >= 30) {
			rocketLeft = !rocketLeft;
		}
	}



	if (rocketRightRotateX < 30 && !rocketLeft) {
		rocketRightRotateX += 0.1;
		if (rocketLeftRotateX >= 0 && !rocketLeft) {
			rocketLeftRotateX -= 0.1;
		}
		if (rocketRightRotateX >= 30) {
			rocketLeft = !rocketLeft;
		}
	}



}

void swordAttackAnimation() {
	//Attack pose
	if (bodyRotateX < 20 && !swordAtkPose) {
		bodyRotateX += 0.05;
		headRotateX -= 0.06;

		rightUpperLegRotateX -= 0.2;
		rightLowerLegRotateX -= 0.15;
		leftUpperLegRotateX -= 0.05;
		leftLowerLegRotateX -= 0.2;

		leftUpperArmRotateX -= 0.23;
		rightUpperArmRotateX -= 0.21;

		if (bodyRotateX > 10) {
			leftUpperArmRotateZ -= 0.05;
			leftLowerArmRotateZ -= 0.15;
			rightUpperArmRotateZ += 0.1;
			rightLowerArmRotateZ += 0.15;
		}

		if (bodyRotateX >= 20) {
			swordAtkPose = true;
		}
	}
	if (swordAtkPose) {
		if (!on) {
			on = !on;
		}
	}

	//First Slash stance
	if (bodyRotateX > 10 && swordAtkPose && !firstSlashPose) {
		headRotateX += 0.025;
		bodyRotateX -= 0.015;
		headRotateY += 0.045;
		bodyRotateY -= 0.045;
		rightUpperLegRotateX += 0.05;
		rightLowerLegRotateX += 0.01;
		leftUpperLegRotateX += 0.02;
		leftLowerLegRotateX += 0.05;

		rightUpperArmRotateX -= 0.1;
		leftUpperArmRotateX -= 0.1;
		leftLowerArmRotateX -= 0.05;
		rightLowerArmRotateX -= 0.05;
		leftLowerArmRotateZ -= 0.05;
		rightUpperArmRotateZ -= 0.005;
		leftUpperArmRotateZ += 0.025;

		leftHandRotateX -= 0.025;
		rightHandRotateX -= 0.025;

		if (bodyRotateX < 10) {
			firstSlashPose = true;
		}
	}

	//Execute first slash
	if (firstSlashPose && !firstSlash) {
		if (bodyRotateX < 20) {
			headRotateX -= 0.025;
			bodyRotateX += 0.015;
			rightUpperLegRotateX -= 0.05;
			rightLowerLegRotateX -= 0.01;
			leftUpperLegRotateX -= 0.02;
			leftLowerLegRotateX -= 0.05;

			bodyRotateY += 0.1;
			headRotateY -= 0.08;
			rightUpperArmRotateX += 0.2;
			leftUpperArmRotateX += 0.2;
			rightLowerArmRotateX += 0.03;
			leftLowerArmRotateX += 0.03;
			rightLowerArmRotateZ += 0.02;
			leftLowerArmRotateZ += 0.02;
			leftUpperArmRotateZ -= 0.03;

			leftHandRotateX += 0.045;
			rightHandRotateX += 0.045;

			if (bodyRotateX >= 20) {
				firstSlash = true;
			}
		}
	}

	//Reset position
	if (firstSlash && !firstSlashReset) {
		if (bodyRotateX > 10) {
			headRotateX += 0.025;
			bodyRotateX -= 0.015;
			rightUpperLegRotateX += 0.05;
			rightLowerLegRotateX += 0.01;
			leftUpperLegRotateX += 0.02;
			leftLowerLegRotateX += 0.05;

			bodyRotateY -= 0.1;
			headRotateY += 0.08;
			rightUpperArmRotateX -= 0.2;
			leftUpperArmRotateX -= 0.2;
			rightLowerArmRotateX -= 0.03;
			leftLowerArmRotateX -= 0.03;
			rightLowerArmRotateZ -= 0.02;
			leftLowerArmRotateZ -= 0.02;
			leftUpperArmRotateZ += 0.03;

			leftHandRotateX -= 0.045;
			rightHandRotateX -= 0.045;

			if (bodyRotateX < 10) {
				firstSlashReset = true;
			}
		}
	}

	//Second slash stance
	if (bodyRotateX < 40 && firstSlashReset && !secondSlashPose) {
		headRotateX -= 0.035;
		bodyRotateX += 0.03;
		headRotateY -= 0.05;
		bodyRotateY += 0.07;
		rightUpperLegRotateX -= 0.05;
		rightLowerLegRotateX -= 0.005;
		leftUpperLegRotateX -= 0.02;
		leftLowerLegRotateX -= 0.005;

		rightUpperArmRotateX += 0.12;
		leftUpperArmRotateX += 0.12;
		leftUpperArmRotateZ -= 0.025;
		rightLowerArmRotateZ += 0.025;

		leftHandRotateX += 0.045;
		rightHandRotateX += 0.045;

		if (bodyRotateX > 40) {
			secondSlashPose = true;
		}
	}

	//Execute second slash
	if (secondSlashPose && !secondSlash) {
		if (bodyRotateX > 30) {
			wholeBodyTranslateY -= 0.005;
			wholeBodyTranslateZ += 0.015;

			headRotateY += 0.025;
			bodyRotateX -= 0.015;
			bodyRotateY -= 0.045;
			rightUpperLegRotateX += 0.12;
			rightLowerLegRotateX -= 0.03;
			leftUpperLegRotateX -= 0.12;
			leftLowerLegRotateX -= 0.07;

			rightUpperArmRotateX -= 0.1;
			leftUpperArmRotateX -= 0.1;
			rightUpperArmRotateZ -= 0.005;
			leftUpperArmRotateZ += 0.005;
			rightLowerArmRotateZ -= 0.05;
			leftLowerArmRotateZ += 0.05;

			leftHandRotateX += 0.1;
			rightHandRotateX += 0.1;
			leftHandRotateY += 0.05;
			rightHandRotateY += 0.05;
			if (bodyRotateX < 30) {
				secondSlash = true;
			}
		}
	}

}

void shootingAnimation() {

	gunOn = true;
	shieldOn = true;
	turnShield = true;
	shieldAngle = 180;
	on = false;

	if (rightUpperArmRotateX > -90) {
		z += 0.5;
		rightUpperArmRotateX -= 0.25;
		rightUpperArmRotateY += 0.25;

		rightUpperLegRotateX -= 0.25;
		rightLowerLegRotateX -= 0.25;

		leftUpperArmRotateX -= 0.15;
		leftUpperArmRotateY -= 0.1;

		leftLowerArmRotateX -= 0.3;
		leftLowerArmRotateY += 0.25;

		leftUpperLegRotateX -= 0.1;
		leftLowerLegRotateX -= 0.35;
		wholeBodyTranslateY -= 0.025;
		bodyRotateX += 0.01;

		if (rightUpperArmRotateX == -90) {
			onLaser = true;
		}

	}

	if (onLaser && bulletTranslate < 70) {
		bulletTranslate += 0.1;
		if (bulletTranslate >= 70) {
			bulletTranslate = 0;
		}
	}
}

void defenseAnimation() {

	if (leftUpperArmRotateX > -90 && handDown == false) {

		rightUpperLegRotateX -= 0.25;
		rightLowerLegRotateX -= 0.25;

		leftUpperArmRotateX -= 0.25;
		leftUpperArmRotateY -= 0.1;

		leftLowerArmRotateX -= 0.3;
		leftLowerArmRotateY += 0.25;

		leftUpperLegRotateX -= 0.1;
		leftLowerLegRotateX -= 0.35;
		wholeBodyTranslateY -= 0.025;
		bodyRotateX += 0.01;

		if (leftUpperArmRotateX <= -90) {
			shieldOn = false;
			shieldDown1 = true;
		}
	}

	if (shieldDown1) {
		if (shieldHeight[0] > -25) {
			shieldHeight[0] -= 0.5;
			if (shieldHeight[0] == -25) {
				shieldDown1 = false;
				shieldDown2 = true;
			}
		}
	}

	if (shieldDown2) {
		if (shieldHeight[1] > -25) {
			shieldHeight[1] -= 0.5;
			if (shieldHeight[1] == -25) {
				shieldDown2 = false;
				shieldDown3 = true;
			}
		}
	}

	if (shieldDown3) {
		if (shieldHeight[2] > -25) {
			shieldHeight[2] -= 0.5;
			if (shieldHeight[2] == -25) {
				shieldDown3 = false;
				handDown = true;
			}
		}
	}

	if (leftUpperArmRotateX < 0 && handDown == true) {
		leftUpperArmRotateX += 0.25;
		leftUpperArmRotateY += 0.1;
		if (rightUpperArmRotateX > -90) {
			z += 0.5;
			rightUpperArmRotateX -= 0.25;
			rightUpperArmRotateY += 0.25;

			if (rightUpperArmRotateX == -90) {
				gunOn = true;
				onLaser = true;
			}

		}
	}


}

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) //Capture input from users & Instruction
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN: //Press escape to quit in Window
		//msdn virtual key
		switch (wParam) {
		case VK_ESCAPE:
			PostQuitMessage(0); break;
		case VK_SPACE:
			reset();
			cameraReset();
			break;
		case VK_UP:
			if (y <= 30) {
				y += 1;
			}break;
		case VK_DOWN:
			if (y >= 0) {
				y -= 1;
			}
			break;
		case VK_LEFT:
			z -= 2; break;
		case VK_RIGHT:
			z += 2; break;
		case VK_0:
			isOrtho = !isOrtho;
			break;
		case VK_1:
			colorSwitch = !colorSwitch;
			break;
		case VK_2:
			if (headRotateX >= -10)
				headRotateX -= 1;
			break;
		case VK_3:
			if (headRotateX <= 10)
				headRotateX += 1;
			break;
		case VK_4:
			if (zoom > -16 && !isOrtho)
				zoom -= 2;;
			break;
		case VK_5:
			if (zoom < 0 && !isOrtho)
				zoom += 2;
			break;
		case VK_7:
			//shield
			shieldOn = !shieldOn;
			break;
		case VK_8:
			//gun
			gunOn = !gunOn;
			break;

		case VK_9:
			//sword beam
			on = !on;
			break;
		case VK_W:
			if (key != VK_W) {
				reset();
				key = VK_W;
			}
			walkingAnimation();
			break;
		case VK_R:
			if (key != VK_1) {
				reset();
				key = VK_1;
			}
			runningAnimation();
			break;
		case VK_J:
			reset();
			jump = true;
			break;
		case VK_F:
			reset();
			fly = true;
			break;
		case VK_Q:
			if (headRotateY >= -30)
				headRotateY -= 1;
			break;
		case VK_E:
			if (headRotateY <= 30)
				headRotateY += 1;
			break;
		case VK_T:
			if (textureNo < 3) {
				textureNo++;
			}
			else {
				textureNo = 0;
			}

			if (textureNo == 0) {
				texture1Initialization();
			}
			else if (textureNo == 1) {
				texture2Initialization();
			}
			else if (textureNo == 2) {
				texture3Initialization();
			}
			else if (textureNo == 3) {
				texture4Initialization();
			}
			break;
		case VK_OEM_4:
			lightY += 1;
			break;
		case VK_OEM_6:
			lightY -= 1;
			break;
		case VK_OEM_MINUS:
			lightX -= 1;
			break;
		case VK_OEM_PLUS:
			lightX += 1;
			break;
		case VK_OEM_7:
			lightZ += 1;
			break;
		case VK_OEM_1:
			lightZ -= 1;
			break;
		case VK_A:
			wholeBodyRotateY -= 2;
			break;
		case VK_D:
			wholeBodyRotateY += 2;
			break;
		case VK_L:
			lightOn = !lightOn;
			break;
		case VK_Z:
			if (key != VK_Z) {
				reset();
				key = VK_Z;
			}
			cameraReset();
			shoot = true;
			break;
		case VK_X:
			if (key != VK_X) {
				reset();
				shieldOn = true;
				key = VK_X;
			}
			cameraReset();
			defense = true;
			break;		
		case VK_C:
			reset();
			swordAtkAni = true;
			break;
		}

	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
//--------------------------------------------------------------------

bool initPixelFormat(HDC hdc) //rendering pixel
{
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.cAlphaBits = 8;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 0;

	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;

	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;

	// choose pixel format returns the number most similar pixel format available
	int n = ChoosePixelFormat(hdc, &pfd);

	// set pixel format returns whether it sucessfully set the pixel format
	if (SetPixelFormat(hdc, n, &pfd))
	{
		return true;
	}
	else
	{
		return false;
	}
}
//--------------------------------------------------------------------
void background() {
	glPushMatrix();
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureBackground);

	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
	//Right (alter y, z)
	glTexCoord2f(0, 0);
	glVertex3f(80, -80, 80);
	glTexCoord2f(1, 0);
	glVertex3f(80, -80, -80);
	glTexCoord2f(1, 1);
	glVertex3f(80, 80, -80);
	glTexCoord2f(0, 1);
	glVertex3f(80, 80, 80);

	//Left (alter y, z)
	glTexCoord2f(0, 0);
	glVertex3f(-80, -80, 80);
	glTexCoord2f(1, 0);
	glVertex3f(-80, -80, -80);
	glTexCoord2f(1, 1);
	glVertex3f(-80, 80, -80);
	glTexCoord2f(0, 1);
	glVertex3f(-80, 80, 80);

	//Bottom (alter y)
	glTexCoord2f(0.5, 0);
	glVertex3f(-80, -30, 80);
	glTexCoord2f(0.5, 0.5);
	glVertex3f(-80, -30, -80);
	glTexCoord2f(1, 0.5);
	glVertex3f(80, -30, -80);
	glTexCoord2f(1, 0);
	glVertex3f(80, -30, 80);

	//Top (alter y)
	glTexCoord2f(0.5, 0.75);
	glVertex3f(-80, 80, 80);
	glTexCoord2f(0.5, 1);
	glVertex3f(-80, 80, -80);
	glTexCoord2f(1, 1);
	glVertex3f(80, 80, -80);
	glTexCoord2f(1, 0.75);
	glVertex3f(80, 80, 80);

	//Back (alter x,y)
	glTexCoord2f(0, 0);
	glVertex3f(-80, -80, -80);
	glTexCoord2f(0, 1);
	glVertex3f(-80, 80, -80);
	glTexCoord2f(1, 1);
	glVertex3f(80, 80, -80);
	glTexCoord2f(1, 0);
	glVertex3f(80, -80, -80);

	//Front (alter x,y)
	glTexCoord2f(0, 0);
	glVertex3f(-80, -80, 80);
	glTexCoord2f(0, 1);
	glVertex3f(-80, 80, 80);
	glTexCoord2f(1, 1);
	glVertex3f(80, 80, 80);
	glTexCoord2f(1, 0);
	glVertex3f(80, -80, 80);

	glEnd();
	glDisable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glPopMatrix();
}

void sword() {
	glPushMatrix();
	glColor3f(0.15, 0.18, 0.29);
#pragma region core
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glPushMatrix();
	gluCylinder(obj, 0.5, 0.5, 5, 10, 10);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++) {
		glVertex2f(0.5 * cos(i), 0.5 * sin(i));
	}
	glEnd();
	glTranslatef(0, 0, 5);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++) {
		glVertex2f(0.5 * cos(i), 0.5 * sin(i));
	}
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, -1);
	gluCylinder(obj, 1, 1, 1, 10, 10);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++) {
		glVertex2f(1 * cos(i), 1 * sin(i));
	}
	glEnd();
	glTranslatef(0, 0, 1);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++) {
		glVertex2f(0.5 * cos(i), 0.5 * sin(i));
	}
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, -2);
	gluCylinder(obj, 0.75, 0.75, 1, 10, 10);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++) {
		glVertex2f(0.75 * cos(i), 0.75 * sin(i));
	}
	glEnd();
	glTranslatef(0, 0, 1);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++) {
		glVertex2f(0.75 * cos(i), 0.75 * sin(i));
	}
	glEnd();
	glPopMatrix();
	glPopMatrix();
#pragma endregion core
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, green);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, green);
	glColor3f(green[0], green[1], green[2]);
#pragma region blade
	glPushMatrix();
	if (on) {
		if (scale < 1) {
			scale += 0.005;
		}
	}
	else {
		if (scale > 0) {
			scale -= 0.005;
		}
	}
	glBindTexture(GL_TEXTURE_2D, textureGreenDiamond);
	glScalef(scale, scale, scale);
	glRotatef(-90, 1, 0, 0);
	gluQuadricTexture(obj, true);
	gluCylinder(obj, 0.75, 0.5, 21, 10, 10);
	glTranslatef(0, 0, 21);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++) {
		glVertex2f(0.5 * cos(i), 0.5 * sin(i));
	}
	glEnd();
	glPopMatrix();
#pragma endregion blade
	glPopMatrix();
}

void shield() {
	glPushMatrix();
	glScalef(0.8, 0.8, 0.8);
	glBindTexture(GL_TEXTURE_2D, textureMetalBlueShine);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, indigo);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, indigo);
	glColor3f(indigo[0], indigo[1], indigo[2]);
#pragma region core
	//front
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);
	glVertex3f(-4, 10, 0);
	glTexCoord2f(1, 0);
	glVertex3f(-6, 28, 0);
	glTexCoord2f(1, 1);
	glVertex3f(-5, 30, 0);
	glTexCoord2f(0, 1);
	glVertex3f(5, 30, 0);
	glTexCoord2f(0, 0);
	glVertex3f(6, 28, 0);
	glTexCoord2f(1, 0);
	glVertex3f(4, 10, 0);
	glEnd();

	//-------------------------------side
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, darkBlue);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, darkBlue);
	glColor3f(darkBlue[0], darkBlue[1], darkBlue[2]);
	glBegin(GL_QUADS);
	//right
	glTexCoord2f(0, 0);
	glVertex3f(6, 28, 0);
	glTexCoord2f(1, 0);
	glVertex3f(6.5, 28.5, -1);
	glTexCoord2f(1, 1);
	glVertex3f(4.5, 9.5, -1);
	glTexCoord2f(0, 1);
	glVertex3f(4, 10, 0);

	glTexCoord2f(0, 0);
	glVertex3f(5, 30, 0);
	glTexCoord2f(1, 0);
	glVertex3f(5.5, 30.5, -1);
	glTexCoord2f(1, 1);
	glVertex3f(6.5, 28.5, -1);
	glTexCoord2f(0, 1);
	glVertex3f(6, 28, 0);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-6, 28, 0);
	glTexCoord2f(1, 0);
	glVertex3f(-6.5, 28.5, -1);
	glTexCoord2f(1, 1);
	glVertex3f(-4.5, 9.5, -1);
	glTexCoord2f(0, 1);
	glVertex3f(-4, 10, 0);

	glTexCoord2f(0, 0);
	glVertex3f(-5, 30, 0);
	glTexCoord2f(1, 0);
	glVertex3f(-5.5, 30.5, -1);
	glTexCoord2f(1, 1);
	glVertex3f(-6.5, 28.5, -1);
	glTexCoord2f(0, 1);
	glVertex3f(-6, 28, 0);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-5, 30, 0);
	glTexCoord2f(1, 0);
	glVertex3f(5, 30, 0);
	glTexCoord2f(1, 1);
	glVertex3f(5.5, 30.5, -1);
	glTexCoord2f(0, 1);
	glVertex3f(-5.5, 30.5, -1);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-4, 10, 0);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 10, 0);
	glTexCoord2f(1, 1);
	glVertex3f(-2.5, 9.5, -1);
	glTexCoord2f(0, 1);
	glVertex3f(-4.5, 9.5, -1);

	glTexCoord2f(0, 0);
	glVertex3f(4, 10, 0);
	glTexCoord2f(1, 0);
	glVertex3f(2, 10, 0);
	glTexCoord2f(1, 1);
	glVertex3f(2.5, 9.5, -1);
	glTexCoord2f(0, 1);
	glVertex3f(4.5, 9.5, -1);
	glEnd();
#pragma endregion core
	glBindTexture(GL_TEXTURE_2D, textureRedLamp);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, red);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, red);
	glColor3f(1, 0, 0);
#pragma region lowerCore
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(2, 0, 0.05);
	glTexCoord2f(1, 0);
	glVertex3f(3, 20, 0.05);
	glTexCoord2f(1, 1);
	glVertex3f(-3, 20, 0.05);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 0, 0.05);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, darkRed);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, darkRed);
	glColor3f(darkRed[0], darkRed[1], darkRed[2]);
	//-------------------------------side
	//right
	glTexCoord2f(0, 0);
	glVertex3f(2.5, 10, 0.05);
	glTexCoord2f(1, 0);
	glVertex3f(3, 9.5, -1);
	glTexCoord2f(1, 1);
	glVertex3f(2.5, -0.5, -1);
	glTexCoord2f(0, 1);
	glVertex3f(2, 0, 0.05);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-2.5, 10, 0.05);
	glTexCoord2f(1, 0);
	glVertex3f(-3, 9.5, -1);
	glTexCoord2f(1, 1);
	glVertex3f(-2.5, -0.5, -1);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 0, 0.05);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-2, 0, 0.05);
	glTexCoord2f(1, 0);
	glVertex3f(2, 0, 0.05);
	glTexCoord2f(1, 1);
	glVertex3f(2.5, -0.5, -1);
	glTexCoord2f(0, 1);
	glVertex3f(-2.5, -0.5, -1);
	glEnd();
#pragma endregion lowerCore
	glPopMatrix();
}

void head() {
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, lightBlue);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, lightBlue);
	glColor3f(lightBlue[0], lightBlue[1], lightBlue[2]);
#pragma region core
	glBindTexture(GL_TEXTURE_2D, textureFace);
	glPushMatrix();
	gluQuadricTexture(obj, true);
	gluSphere(obj, 2, 20, 20);
	glPopMatrix();
#pragma endregion core

#pragma region mask
	//----------------------------------------middle part
	glBindTexture(GL_TEXTURE_2D, textureMetalBlue);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, indigo);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, indigo);
	glColor3f(indigo[0], indigo[1], indigo[2]);
	//front
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);
	glVertex3f(-0.25, 0, 2.5);
	glTexCoord2f(0, 1);
	glVertex3f(-1.25, -0.5, 2.25);
	glTexCoord2f(1, 1);
	glVertex3f(-1, -1.5, 2.25);
	glTexCoord2f(1, 0);
	glVertex3f(-0.25, -2, 2.25);
	glTexCoord2f(0, 0);
	glVertex3f(-0.2, -1.25, 2.25);
	glTexCoord2f(0, 1);
	glVertex3f(0.2, -1.25, 2.25);
	glTexCoord2f(1, 1);
	glVertex3f(0.25, -2, 2.25);
	glTexCoord2f(1, 0);
	glVertex3f(1, -1.5, 2.25);
	glTexCoord2f(0, 0);
	glVertex3f(1.25, -0.5, 2.25);
	glTexCoord2f(0, 1);
	glVertex3f(0.25, 0, 2.5);
	glEnd();

	//mastach
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, red);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, red);
	glColor3f(1, 0, 0);
	glBindTexture(GL_TEXTURE_2D, textureRedLamp);
	glBegin(GL_QUADS);
	//back
	glTexCoord2f(0, 0);
	glVertex3f(-0.25, -2, 2.25);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2, -1.25, 2.25);
	glTexCoord2f(1, 1);
	glVertex3f(0.2, -1.25, 2.25);
	glTexCoord2f(0, 1);
	glVertex3f(0.25, -2, 2.25);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-0.2, -1.25, 2.25);
	glTexCoord2f(1, 0);
	glVertex3f(0.2, -1.25, 2.25);
	glTexCoord2f(1, 1);
	glVertex3f(0.25, -1.75, 2.5);
	glTexCoord2f(0, 1);
	glVertex3f(-0.25, -1.75, 2.5);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(-0.25, -1.75, 2.5);
	glTexCoord2f(1, 0);
	glVertex3f(0.25, -1.75, 2.5);
	glTexCoord2f(1, 1);
	glVertex3f(0.25, -2.5, 2.5);
	glTexCoord2f(0, 1);
	glVertex3f(-0.25, -2.5, 2.5);
	glEnd();

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-0.25, -2, 2.25);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2, -1.25, 2.25);
	glTexCoord2f(1, 1);
	glVertex3f(-0.25, -1.75, 2.5);
	glTexCoord2f(0, 1);
	glVertex3f(-0.25, -2.5, 2.5);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(0.25, -2, 2.25);
	glTexCoord2f(1, 0);
	glVertex3f(0.2, -1.25, 2.25);
	glTexCoord2f(1, 1);
	glVertex3f(0.25, -1.75, 2.5);
	glTexCoord2f(0, 1);
	glVertex3f(0.25, -2.5, 2.5);

	glBindTexture(GL_TEXTURE_2D, textureMetalGrey);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, indigo);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, indigo);
	glColor3f(indigo[0], indigo[1], indigo[2]);
	glBegin(GL_QUADS);
	//background
	//left
	glTexCoord2f(0, 0);
	glVertex3f(-0.25, -0.5, 2.25);
	glTexCoord2f(1, 0);
	glVertex3f(-1.75, 0, 2);
	glTexCoord2f(1, 1);
	glVertex3f(-1.5, -1.5, 2);
	glTexCoord2f(0, 1);
	glVertex3f(-0.25, -2, 2);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(0.25, -0.5, 2.25);
	glTexCoord2f(1, 0);
	glVertex3f(1.75, 0, 2);
	glTexCoord2f(1, 1);
	glVertex3f(1.5, -1.5, 2);
	glTexCoord2f(0, 1);
	glVertex3f(0.25, -2, 2);
	glEnd();

#pragma endregion mask

#pragma region helmet
	glBindTexture(GL_TEXTURE_2D, textureMetalBlue);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, indigo);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, indigo);
	glColor3f(indigo[0], indigo[1], indigo[2]);
	//right
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);
	glVertex3f(1.75, 0, 2.25);
	glTexCoord2f(1, 0);
	glVertex3f(1.5, -1.5, 2.25);
	glTexCoord2f(1, 1);
	glVertex3f(2, -1.75, 2.25);
	glTexCoord2f(0, 1);
	glVertex3f(2.25, -0.5, 2.25);
	glTexCoord2f(0, 0);
	glVertex3f(2.25, 0, 1.75);
	glTexCoord2f(1, 0);
	glVertex3f(2.25, 0.5, 1.75);
	glTexCoord2f(1, 1);
	glVertex3f(1.75, 0.5, 1.75);
	glTexCoord2f(0, 1);
	glVertex3f(1.75, 0, 1.75);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);
	glVertex3f(2, -1.75, 2.25);
	glTexCoord2f(1, 0);
	glVertex3f(2.25, -0.5, 2.25);
	glTexCoord2f(1, 1);
	glVertex3f(2.25, 0, 1.75);
	glTexCoord2f(0, 1);
	glVertex3f(2.25, 0.5, 1.75);
	glTexCoord2f(0, 0);
	glVertex3f(2.25, 0.5, 1.5);
	glTexCoord2f(1, 0);
	glVertex3f(2.25, 0.5, -1.25);
	glTexCoord2f(1, 1);
	glVertex3f(2.25, -2, -1.25);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(2.25, 0.5, -1.25);
	glTexCoord2f(1, 0);
	glVertex3f(1.75, 0.5, -2.25);
	glTexCoord2f(1, 1);
	glVertex3f(1.75, -2, -2.25);
	glTexCoord2f(0, 1);
	glVertex3f(2.25, -2, -1.25);
	glEnd();

	//back
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(1.75, 0.5, -2.25);
	glTexCoord2f(1, 0);
	glVertex3f(-1.75, 0.5, -2.25);
	glTexCoord2f(1, 1);
	glVertex3f(-1.75, -2, -2.25);
	glTexCoord2f(0, 1);
	glVertex3f(1.75, -2, -2.25);
	glEnd();

	//left
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);
	glVertex3f(-1.75, 0, 2.25);
	glTexCoord2f(1, 0);
	glVertex3f(-1.5, -1.5, 2.25);
	glTexCoord2f(1, 1);
	glVertex3f(-2, -1.75, 2.25);
	glTexCoord2f(0, 1);
	glVertex3f(-2.25, -0.5, 2.25);
	glTexCoord2f(0, 0);
	glVertex3f(-2.25, 0, 1.75);
	glTexCoord2f(1, 0);
	glVertex3f(-2.25, 0.5, 1.75);
	glTexCoord2f(1, 1);
	glVertex3f(-1.75, 0.5, 1.75);
	glTexCoord2f(0, 1);
	glVertex3f(-1.75, 0, 1.75);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);
	glVertex3f(-2, -1.75, 2.25);
	glTexCoord2f(1, 0);
	glVertex3f(-2.25, -0.5, 2.25);
	glTexCoord2f(1, 1);
	glVertex3f(-2.25, 0, 1.75);
	glTexCoord2f(0, 1);
	glVertex3f(-2.25, 0.5, 1.75);
	glTexCoord2f(0, 0);
	glVertex3f(-2.25, 0.5, 1.5);
	glTexCoord2f(1, 0);
	glVertex3f(-2.25, 0.5, -1.25);
	glTexCoord2f(1, 1);
	glVertex3f(-2.25, -2, -1.25);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-2.25, 0.5, -1.25);
	glTexCoord2f(1, 0);
	glVertex3f(-1.75, 0.5, -2.25);
	glTexCoord2f(1, 1);
	glVertex3f(-1.75, -2, -2.25);
	glTexCoord2f(0, 1);
	glVertex3f(-2.25, -2, -1.25);
	glEnd();

	//------------------------------------------top back
	//bottom
	glBindTexture(GL_TEXTURE_2D, textureMetalBlue);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);
	glVertex3f(-2.25, 0.5, 1.75);
	glTexCoord2f(1, 0);
	glVertex3f(-1.75, 0.5, 1.75);
	glTexCoord2f(1, 1);
	glVertex3f(-0.25, 0.5, 2);
	glTexCoord2f(0, 1);
	glVertex3f(0.25, 0.5, 2);
	glTexCoord2f(0, 0);
	glVertex3f(1.75, 0.5, 1.75);
	glTexCoord2f(1, 0);
	glVertex3f(2.25, 0.5, 1.75);

	glTexCoord2f(1, 1);
	glVertex3f(1.75, 0.5, 2.25);
	glTexCoord2f(0, 1);
	glVertex3f(0.25, 0.5, 2.5);
	glTexCoord2f(0, 0);
	glVertex3f(-0.25, 0.5, 2.5);
	glTexCoord2f(1, 0);
	glVertex3f(-1.75, 0.5, 2.25);
	glEnd();

	//front
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);
	glVertex3f(-1.75, 0.5, -2.25);
	glTexCoord2f(1, 0);
	glVertex3f(-1.25, 1.5, -2.25);
	glTexCoord2f(1, 1);
	glVertex3f(0, 1.75, -2);
	glTexCoord2f(0, 1);
	glVertex3f(1.25, 1.5, -2.25);
	glTexCoord2f(0, 0);
	glVertex3f(1.75, 0.5, -2.25);
	glEnd();

	//left
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);
	glVertex3f(1.75, 0.5, -2.25);
	glTexCoord2f(1, 0);
	glVertex3f(1.25, 1.5, -2.25);
	glTexCoord2f(1, 1);
	glVertex3f(1.5, 2, 0);
	glTexCoord2f(0, 1);
	glVertex3f(2.25, 0.5, 0);
	glTexCoord2f(0, 0);
	glVertex3f(2.25, 0.5, -1.75);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);
	glVertex3f(1.25, 1.5, -2.25);
	glTexCoord2f(1, 0);
	glVertex3f(1.5, 2, 0);
	glTexCoord2f(1, 1);
	glVertex3f(0, 2.5, 0);
	glTexCoord2f(0, 1);
	glVertex3f(0, 1.75, -2);
	glEnd();

	//right
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);
	glVertex3f(-1.75, 0.5, -2.25);
	glTexCoord2f(1, 0);
	glVertex3f(-1.25, 1.5, -2.25);
	glTexCoord2f(1, 1);
	glVertex3f(-1.5, 2, 0);
	glTexCoord2f(0, 1);
	glVertex3f(-2.25, 0.5, 0);
	glTexCoord2f(0, 0);
	glVertex3f(-2.25, 0.5, -1.75);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);
	glVertex3f(-1.25, 1.5, -2.25);
	glTexCoord2f(1, 0);
	glVertex3f(-1.5, 2, 0);
	glTexCoord2f(1, 1);
	glVertex3f(-0, 2.25, 0);
	glTexCoord2f(0, 1);
	glVertex3f(-0, 1.75, -2);
	glEnd();

	//--------------------------------------top front
	//front
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);
	glVertex3f(-1.75, 0.5, 2.25);
	glTexCoord2f(1, 0);
	glVertex3f(-1.25, 1.5, 2.25);
	glTexCoord2f(1, 1);
	glVertex3f(0, 1.75, 2.25);
	glTexCoord2f(0, 1);
	glVertex3f(1.25, 1.5, 2.25);
	glTexCoord2f(0, 0);
	glVertex3f(1.75, 0.5, 2.25);
	glEnd();

	//left
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);
	glVertex3f(1.75, 0.5, 2.25);
	glTexCoord2f(1, 0);
	glVertex3f(1.25, 1.5, 2.25);
	glTexCoord2f(1, 1);
	glVertex3f(1.5, 2, 0);
	glTexCoord2f(0, 1);
	glVertex3f(2.25, 0.5, 0);
	glTexCoord2f(0, 0);
	glVertex3f(2.25, 0.5, 1.75);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);
	glVertex3f(1.25, 1.5, 2.25);
	glTexCoord2f(1, 0);
	glVertex3f(1.5, 2, 0);
	glTexCoord2f(1, 1);
	glVertex3f(0, 2.25, 0);
	glTexCoord2f(0, 1);
	glVertex3f(0, 1.75, 2.25);
	glEnd();

	//right
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);
	glVertex3f(-1.75, 0.5, 2.25);
	glTexCoord2f(1, 0);
	glVertex3f(-1.25, 1.5, 2.25);
	glTexCoord2f(1, 1);
	glVertex3f(-1.5, 2, 0);
	glTexCoord2f(0, 1);
	glVertex3f(-2.25, 0.5, 0);
	glTexCoord2f(0, 0);
	glVertex3f(-2.25, 0.5, 1.75);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);
	glVertex3f(-1.25, 1.5, 2.25);
	glTexCoord2f(1, 0);
	glVertex3f(-1.5, 2, 0);
	glTexCoord2f(1, 1);
	glVertex3f(-0, 2.5, 0);
	glTexCoord2f(0, 1);
	glVertex3f(-0, 1.75, 2.25);
	glEnd();

	//----------------------------------------top part
	glBindTexture(GL_TEXTURE_2D, textureGreenDiamond);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, green);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, green);
	glColor3f(green[0], green[1], green[2]);
	glBegin(GL_QUADS);
	//front
	glTexCoord2f(0, 0);
	glVertex3f(-0.75, 1.75, 1.25);
	glTexCoord2f(1, 0);
	glVertex3f(0.75, 1.75, 1.25);
	glTexCoord2f(1, 1);
	glVertex3f(0.75, 3.25, 1.25);
	glTexCoord2f(0, 1);
	glVertex3f(-0.75, 3.25, 1.25);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textureMetalBlue);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, indigo);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, indigo);
	glColor3f(indigo[0], indigo[1], indigo[2]);
	glBegin(GL_QUADS);
	//back
	glTexCoord2f(0, 0);
	glVertex3f(-0.75, 1.75, -2);
	glTexCoord2f(1, 0);
	glVertex3f(0.75, 1.75, -2);
	glTexCoord2f(1, 1);
	glVertex3f(0.75, 2.75, -1.75);
	glTexCoord2f(0, 1);
	glVertex3f(-0.75, 2.75, -1.75);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-0.75, 3.25, 1.25);
	glTexCoord2f(1, 0);
	glVertex3f(0.75, 3.25, 1.25);
	glTexCoord2f(1, 1);
	glVertex3f(0.75, 2.75, -1.75);
	glTexCoord2f(0, 1);
	glVertex3f(-0.75, 2.75, -1.75);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-0.75, 1.75, -2);
	glTexCoord2f(1, 0);
	glVertex3f(-0.75, 2.75, -1.75);
	glTexCoord2f(1, 1);
	glVertex3f(-0.75, 3.25, 1.25);
	glTexCoord2f(0, 1);
	glVertex3f(-0.75, 1.75, 1.25);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(0.75, 1.75, -2);
	glTexCoord2f(1, 0);
	glVertex3f(0.75, 2.75, -1.75);
	glTexCoord2f(1, 1);
	glVertex3f(0.75, 3.25, 1.25);
	glTexCoord2f(0, 1);
	glVertex3f(0.75, 1.75, 1.25);
	glEnd();


	//----------------------------------------left side part
	//left
	glBindTexture(GL_TEXTURE_2D, textureMetalGrey);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, silver);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, silver);
	glColor3f(silver[0], silver[1], silver[2]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-2.75, 1, -1.5);
	glTexCoord2f(1, 0);
	glVertex3f(-2.75, -1, -1.5);
	glTexCoord2f(1, 1);
	glVertex3f(-2.25, -1, -1.5);
	glTexCoord2f(0, 1);
	glVertex3f(-2.25, 1, -1.5);

	glTexCoord2f(0, 0);
	glVertex3f(-2.25, -1, -1.5);
	glTexCoord2f(1, 0);
	glVertex3f(-2.25, -1.5, -0.25);
	glTexCoord2f(1, 1);
	glVertex3f(-2.75, -1.5, -0.25);
	glTexCoord2f(0, 1);
	glVertex3f(-2.75, -1, -1.5);

	glTexCoord2f(0, 0);
	glVertex3f(-2.25, -1, 1);
	glTexCoord2f(1, 0);
	glVertex3f(-2.25, -1.5, -0.25);
	glTexCoord2f(1, 1);
	glVertex3f(-2.75, -1.5, -0.25);
	glTexCoord2f(0, 1);
	glVertex3f(-2.75, -1, 1);

	glTexCoord2f(0, 0);
	glVertex3f(-2.75, 1, 1);
	glTexCoord2f(1, 0);
	glVertex3f(-2.75, -1, 1);
	glTexCoord2f(1, 1);
	glVertex3f(-2.25, -1, 1);
	glTexCoord2f(0, 1);
	glVertex3f(-2.25, 1, 1);

	glTexCoord2f(0, 0);
	glVertex3f(-2.75, 1, 1);
	glTexCoord2f(1, 0);
	glVertex3f(-2.25, 1, 1);
	glTexCoord2f(1, 1);
	glVertex3f(-2.25, 1, -1.5);
	glTexCoord2f(0, 1);
	glVertex3f(-2.75, 1, -1.5);

	//-----------------------------------------
	//left
	glTexCoord2f(0, 0);
	glVertex3f(-2.75, 1, 1);
	glTexCoord2f(1, 0);
	glVertex3f(-2.75, -0.5, 1);
	glTexCoord2f(1, 1);
	glVertex3f(-2.75, 0, 1.75);
	glTexCoord2f(0, 1);
	glVertex3f(-2.75, 0.5, 1.75);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-2.75, 0.5, 1.75);
	glTexCoord2f(1, 0);
	glVertex3f(-2.75, 1, 1);
	glTexCoord2f(1, 1);
	glVertex3f(-2.25, 1, 1);
	glTexCoord2f(0, 1);
	glVertex3f(-2.25, 0.5, 1.75);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-2.75, -0.5, 1);
	glTexCoord2f(1, 0);
	glVertex3f(-2.75, 0, 1.75);
	glTexCoord2f(1, 1);
	glVertex3f(-2.25, 0, 1.75);
	glTexCoord2f(0, 1);
	glVertex3f(-2.25, -0.5, 1);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(-2.75, 0, 1.75);
	glTexCoord2f(1, 0);
	glVertex3f(-2.75, 0.5, 1.75);
	glTexCoord2f(1, 1);
	glVertex3f(-2.25, 0.5, 1.75);
	glTexCoord2f(0, 1);
	glVertex3f(-2.25, 0, 1.75);
	glEnd();

	//left side
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);
	glVertex3f(-2.75, 1, 1);
	glTexCoord2f(1, 0);
	glVertex3f(-2.75, -1, 1);
	glTexCoord2f(1, 1);
	glVertex3f(-2.75, -1.5, -0.25);
	glTexCoord2f(0, 1);
	glVertex3f(-2.75, -1, -1.5);
	glTexCoord2f(1, 0);
	glVertex3f(-2.75, 1, -1.5);
	glEnd();

	//----------------------------------------side part
	//left
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(2.75, 1, -1.5);
	glTexCoord2f(1, 0);
	glVertex3f(2.75, -1, -1.5);
	glTexCoord2f(1, 1);
	glVertex3f(2.25, -1, -1.5);
	glTexCoord2f(0, 1);
	glVertex3f(2.25, 1, -1.5);

	glTexCoord2f(0, 0);
	glVertex3f(2.25, -1, -1.5);
	glTexCoord2f(1, 0);
	glVertex3f(2.25, -1.5, -0.25);
	glTexCoord2f(1, 1);
	glVertex3f(2.75, -1.5, -0.25);
	glTexCoord2f(0, 1);
	glVertex3f(2.75, -1, -1.5);

	glTexCoord2f(0, 0);
	glVertex3f(2.25, -1, 1);
	glTexCoord2f(1, 0);
	glVertex3f(2.25, -1.5, -0.25);
	glTexCoord2f(1, 1);
	glVertex3f(2.75, -1.5, -0.25);
	glTexCoord2f(0, 1);
	glVertex3f(2.75, -1, 1);

	glTexCoord2f(0, 0);
	glVertex3f(2.75, 1, 1);
	glTexCoord2f(1, 0);
	glVertex3f(2.75, -1, 1);
	glTexCoord2f(1, 1);
	glVertex3f(2.25, -1, 1);
	glTexCoord2f(0, 1);
	glVertex3f(2.25, 1, 1);

	glTexCoord2f(0, 0);
	glVertex3f(2.75, 1, 1);
	glTexCoord2f(1, 0);
	glVertex3f(2.25, 1, 1);
	glTexCoord2f(1, 1);
	glVertex3f(2.25, 1, -1.5);
	glTexCoord2f(0, 1);
	glVertex3f(2.75, 1, -1.5);

	//-----------------------------------------
	//left
	glTexCoord2f(0, 0);
	glVertex3f(2.75, 1, 1);
	glTexCoord2f(1, 0);
	glVertex3f(2.75, -0.5, 1);
	glTexCoord2f(1, 1);
	glVertex3f(2.75, 0, 1.75);
	glTexCoord2f(0, 1);
	glVertex3f(2.75, 0.5, 1.75);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(2.75, 0.5, 1.75);
	glTexCoord2f(1, 0);
	glVertex3f(2.75, 1, 1);
	glTexCoord2f(1, 1);
	glVertex3f(2.25, 1, 1);
	glTexCoord2f(0, 1);
	glVertex3f(2.25, 0.5, 1.75);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(2.75, -0.5, 1);
	glTexCoord2f(1, 0);
	glVertex3f(2.75, 0, 1.75);
	glTexCoord2f(1, 1);
	glVertex3f(2.25, 0, 1.75);
	glTexCoord2f(0, 1);
	glVertex3f(2.25, -0.5, 1);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(2.75, 0, 1.75);
	glTexCoord2f(1, 0);
	glVertex3f(2.75, 0.5, 1.75);
	glTexCoord2f(1, 1);
	glVertex3f(2.25, 0.5, 1.75);
	glTexCoord2f(0, 1);
	glVertex3f(2.25, 0, 1.75);
	glEnd();

	//right side
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);
	glVertex3f(2.75, 1, 1);
	glTexCoord2f(1, 0);
	glVertex3f(2.75, -1, 1);
	glTexCoord2f(1, 1);
	glVertex3f(2.75, -1.5, -0.25);
	glTexCoord2f(0, 1);
	glVertex3f(2.75, -1, -1.5);
	glTexCoord2f(1, 0);
	glVertex3f(2.75, 1, -1.5);
	glEnd();

	//-------------------------------------middle top part
	glBindTexture(GL_TEXTURE_2D, textureRedLamp);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, red);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, red);
	glColor3f(red[0], red[1], red[2]);
	//back
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);
	glVertex3f(-0.75, 2, 2.25);
	glTexCoord2f(1, 0);
	glVertex3f(-0.75, 1.25, 2.25);
	glTexCoord2f(1, 1);
	glVertex3f(0, 0.75, 2.25);
	glTexCoord2f(0, 1);
	glVertex3f(0.75, 1.25, 2.25);
	glTexCoord2f(0, 0);
	glVertex3f(0.75, 2, 2.25);
	glEnd();

	//front
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);
	glVertex3f(-0.75, 2, 2.5);
	glTexCoord2f(1, 0);
	glVertex3f(-0.75, 1.25, 2.5);
	glTexCoord2f(1, 1);
	glVertex3f(0, 0.75, 2.5);
	glTexCoord2f(0, 1);
	glVertex3f(0.75, 1.25, 2.5);
	glTexCoord2f(0, 0);
	glVertex3f(0.75, 2, 2.5);
	glEnd();

	glBegin(GL_QUADS);
	//top
	glTexCoord2f(0, 0);
	glVertex3f(-0.75, 2, 2.5);
	glTexCoord2f(1, 0);
	glVertex3f(-0.75, 2, 2.25);
	glTexCoord2f(1, 1);
	glVertex3f(0.75, 2, 2.25);
	glTexCoord2f(0, 1);
	glVertex3f(0.75, 2, 2.5);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-0.75, 2, 2.5);
	glTexCoord2f(1, 0);
	glVertex3f(-0.75, 2, 2.25);
	glTexCoord2f(1, 1);
	glVertex3f(-0.75, 1.25, 2.25);
	glTexCoord2f(0, 1);
	glVertex3f(-0.75, 1.25, 2.5);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(0.75, 2, 2.5);
	glTexCoord2f(1, 0);
	glVertex3f(0.75, 2, 2.25);
	glTexCoord2f(1, 1);
	glVertex3f(0.75, 1.25, 2.25);
	glTexCoord2f(0, 1);
	glVertex3f(0.75, 1.25, 2.5);

	//bottom left
	glTexCoord2f(0, 0);
	glVertex3f(-0.75, 1.25, 2.25);
	glTexCoord2f(1, 0);
	glVertex3f(-0.75, 1.25, 2.5);
	glTexCoord2f(1, 1);
	glVertex3f(0, 0.75, 2.5);
	glTexCoord2f(0, 1);
	glVertex3f(0, 0.75, 2.25);

	//bottom right
	glTexCoord2f(0, 0);
	glVertex3f(0.75, 1.25, 2.25);
	glTexCoord2f(1, 0);
	glVertex3f(0.75, 1.25, 2.5);
	glTexCoord2f(1, 1);
	glVertex3f(0, 0.75, 2.5);
	glTexCoord2f(0, 1);
	glVertex3f(0, 0.75, 2.25);
	glEnd();

#pragma endregion helmet

#pragma region leftantena
	//---------------------------------left antena
	glBindTexture(GL_TEXTURE_2D, textureMetalGrey);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, silver);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, silver);
	glColor3f(silver[0], silver[1], silver[2]);
	glBegin(GL_QUADS);
	//front
	glTexCoord2f(0, 0);
	glVertex3f(-0.75, 1.5, 2.5);
	glTexCoord2f(1, 0);
	glVertex3f(-1, 1.5, 2.5);
	glTexCoord2f(1, 1);
	glVertex3f(-1, 3, 2.5);
	glTexCoord2f(0, 1);
	glVertex3f(-0.75, 3, 2.5);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(-0.75, 1.5, 1.75);
	glTexCoord2f(1, 0);
	glVertex3f(-1, 1.5, 1.75);
	glTexCoord2f(1, 1);
	glVertex3f(-1, 3, 2);
	glTexCoord2f(0, 1);
	glVertex3f(-0.75, 3, 2);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-1, 1.5, 1.75);
	glTexCoord2f(1, 0);
	glVertex3f(-1, 1.5, 2.5);
	glTexCoord2f(1, 1);
	glVertex3f(-1, 3, 2.5);
	glTexCoord2f(0, 1);
	glVertex3f(-1, 3, 2);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(-0.75, 1.5, 1.75);
	glTexCoord2f(1, 0);
	glVertex3f(-0.75, 1.5, 2.5);
	glTexCoord2f(1, 1);
	glVertex3f(-0.75, 3, 2.5);
	glTexCoord2f(0, 1);
	glVertex3f(-0.75, 3, 2);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-0.75, 1.5, 2.5);
	glTexCoord2f(1, 0);
	glVertex3f(-1, 1.5, 2.5);
	glTexCoord2f(1, 1);
	glVertex3f(-1, 1.5, 1.75);
	glTexCoord2f(0, 1);
	glVertex3f(-0.75, 1.5, 1.75);

	glColor3f(1, 1, 1);
	//front
	glTexCoord2f(0, 0);
	glVertex3f(-0.75, 3, 2.5);
	glTexCoord2f(1, 0);
	glVertex3f(-1, 3, 2.5);
	glTexCoord2f(1, 1);
	glVertex3f(-1, 4.5, 2.5);
	glTexCoord2f(0, 1);
	glVertex3f(-0.75, 4.5, 2.5);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(-0.75, 3, 2);
	glTexCoord2f(1, 0);
	glVertex3f(-1, 3, 2);
	glTexCoord2f(1, 1);
	glVertex3f(-1, 4.5, 2);
	glTexCoord2f(0, 1);
	glVertex3f(-0.75, 4.5, 2);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-1, 3, 2);
	glTexCoord2f(1, 0);
	glVertex3f(-1, 3, 2.5);
	glTexCoord2f(1, 1);
	glVertex3f(-1, 4.5, 2.5);
	glTexCoord2f(0, 1);
	glVertex3f(-1, 4.5, 2);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(-0.75, 3, 2);
	glTexCoord2f(1, 0);
	glVertex3f(-0.75, 3, 2.5);
	glTexCoord2f(1, 1);
	glVertex3f(-0.75, 4.5, 2.5);
	glTexCoord2f(0, 1);
	glVertex3f(-0.75, 4.5, 2);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-0.75, 4.5, 2.5);
	glTexCoord2f(1, 0);
	glVertex3f(-1, 4.5, 2.5);
	glTexCoord2f(1, 1);
	glVertex3f(-1, 4.5, 2);
	glTexCoord2f(0, 1);
	glVertex3f(-0.75, 4.5, 2);
	glEnd();

#pragma endregion leftantena

#pragma region rightantena
	//---------------------------------right antena
	glBindTexture(GL_TEXTURE_2D, textureMetalGrey);
	glColor3f(silver[0], silver[1], silver[2]);
	glBegin(GL_QUADS);
	//front
	glTexCoord2f(0, 0);
	glVertex3f(0.75, 1.5, 2.5);
	glTexCoord2f(1, 0);
	glVertex3f(1, 1.5, 2.5);
	glTexCoord2f(1, 1);
	glVertex3f(1, 3, 2.5);
	glTexCoord2f(0, 1);
	glVertex3f(0.75, 3, 2.5);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(0.75, 1.5, 1.75);
	glTexCoord2f(1, 0);
	glVertex3f(1, 1.5, 1.75);
	glTexCoord2f(1, 1);
	glVertex3f(1, 3, 2);
	glTexCoord2f(0, 1);
	glVertex3f(0.75, 3, 2);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(1, 1.5, 1.75);
	glTexCoord2f(1, 0);
	glVertex3f(1, 1.5, 2.5);
	glTexCoord2f(1, 1);
	glVertex3f(1, 3, 2.5);
	glTexCoord2f(0, 1);
	glVertex3f(1, 3, 2);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(0.75, 1.5, 1.75);
	glTexCoord2f(1, 0);
	glVertex3f(0.75, 1.5, 2.5);
	glTexCoord2f(1, 1);
	glVertex3f(0.75, 3, 2.5);
	glTexCoord2f(0, 1);
	glVertex3f(0.75, 3, 2);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(0.75, 1.5, 2.5);
	glTexCoord2f(1, 0);
	glVertex3f(1, 1.5, 2.5);
	glTexCoord2f(1, 1);
	glVertex3f(1, 1.5, 1.75);
	glTexCoord2f(0, 1);
	glVertex3f(0.75, 1.5, 1.75);

	glColor3f(1, 1, 1);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(0.75, 3, 2.5);
	glTexCoord2f(1, 0);
	glVertex3f(1, 3, 2.5);
	glTexCoord2f(1, 1);
	glVertex3f(1, 4.5, 2.5);
	glTexCoord2f(0, 1);
	glVertex3f(0.75, 4.5, 2.5);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(0.75, 3, 2);
	glTexCoord2f(1, 0);
	glVertex3f(1, 3, 2);
	glTexCoord2f(1, 1);
	glVertex3f(1, 4.5, 2);
	glTexCoord2f(0, 1);
	glVertex3f(0.75, 4.5, 2);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(1, 3, 2);
	glTexCoord2f(1, 0);
	glVertex3f(1, 3, 2.5);
	glTexCoord2f(1, 1);
	glVertex3f(1, 4.5, 2.5);
	glTexCoord2f(0, 1);
	glVertex3f(1, 4.5, 2);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(0.75, 3, 2);
	glTexCoord2f(1, 0);
	glVertex3f(0.75, 3, 2.5);
	glTexCoord2f(1, 1);
	glVertex3f(0.75, 4.5, 2.5);
	glTexCoord2f(0, 1);
	glVertex3f(0.75, 4.5, 2);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(0.75, 4.5, 2.5);
	glTexCoord2f(1, 0);
	glVertex3f(1, 4.5, 2.5);
	glTexCoord2f(1, 1);
	glVertex3f(1, 4.5, 2);
	glTexCoord2f(0, 1);
	glVertex3f(0.75, 4.5, 2);
	glEnd();

#pragma endregion rightantena
	glPopMatrix();
}

void body() {
	glPushMatrix();
#pragma region core
	glBindTexture(GL_TEXTURE_2D, textureMetalGrey);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, grey);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, grey);
	glColor3f(grey[0], grey[1], grey[2]);
	glBegin(GL_QUADS);
	//--------------------------------------Layer 1	
	//top
	glTexCoord2f(0, 0);
	glVertex3f(-7.5, 10, 0);
	glTexCoord2f(1, 0);
	glVertex3f(7.5, 10, 0);
	glTexCoord2f(1, 1);
	glVertex3f(7.5, 12, -8);
	glTexCoord2f(0, 1);
	glVertex3f(-7.5, 12, -8);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-7.5, 4, 0);
	glTexCoord2f(1, 0);
	glVertex3f(7.5, 4, 0);
	glTexCoord2f(1, 1);
	glVertex3f(7.5, 4, -8);
	glTexCoord2f(0, 1);
	glVertex3f(-7.5, 4, -8);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(-7.5, 4, 0);
	glTexCoord2f(1, 0);
	glVertex3f(7.5, 4, 0);
	glTexCoord2f(1, 1);
	glVertex3f(7.5, 10, 0);
	glTexCoord2f(0, 1);
	glVertex3f(-7.5, 10, 0);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(-7.5, 4, -8);
	glTexCoord2f(1, 0);
	glVertex3f(7.5, 4, -8);
	glTexCoord2f(1, 1);
	glVertex3f(7.5, 12, -8);
	glTexCoord2f(0, 1);
	glVertex3f(-7.5, 12, -8);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-7.5, 4, 0);
	glTexCoord2f(1, 0);
	glVertex3f(-7.5, 4, -8);
	glTexCoord2f(1, 1);
	glVertex3f(-7.5, 12, -8);
	glTexCoord2f(0, 1);
	glVertex3f(-7.5, 10, 0);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(7.5, 4, 0);
	glTexCoord2f(1, 0);
	glVertex3f(7.5, 4, -8);
	glTexCoord2f(1, 1);
	glVertex3f(7.5, 12, -8);
	glTexCoord2f(0, 1);
	glVertex3f(7.5, 10, 0);

	//--------------------------------------Layer 2
	//top
	glTexCoord2f(0, 0);
	glVertex3f(-6, 4, -1);
	glTexCoord2f(1, 0);
	glVertex3f(6, 4, -1);
	glTexCoord2f(1, 1);
	glVertex3f(6, 4, -7);
	glTexCoord2f(0, 1);
	glVertex3f(-6, 4, -7);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-5, 1, -1);
	glTexCoord2f(1, 0);
	glVertex3f(5, 1, -1);
	glTexCoord2f(1, 1);
	glVertex3f(5, 1, -7);
	glTexCoord2f(0, 1);
	glVertex3f(-5, 1, -7);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(-5, 1, -1);
	glTexCoord2f(0, 1);
	glVertex3f(5, 1, -1);
	glTexCoord2f(1, 1);
	glVertex3f(6, 4, -1);
	glTexCoord2f(1, 0);
	glVertex3f(-6, 4, -1);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(-5, 1, -7);
	glTexCoord2f(0, 1);
	glVertex3f(5, 1, -7);
	glTexCoord2f(1, 1);
	glVertex3f(6, 4, -7);
	glTexCoord2f(1, 0);
	glVertex3f(-6, 4, -7);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-5, 1, -1);
	glTexCoord2f(0, 1);
	glVertex3f(-5, 1, -7);
	glTexCoord2f(1, 1);
	glVertex3f(-6, 4, -7);
	glTexCoord2f(1, 0);
	glVertex3f(-6, 4, -1);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(5, 1, -1);
	glTexCoord2f(0, 1);
	glVertex3f(5, 1, -7);
	glTexCoord2f(1, 1);
	glVertex3f(6, 4, -7);
	glTexCoord2f(1, 0);
	glVertex3f(6, 4, -1);

	//--------------------------------------Middle Part
	//front
	glTexCoord2f(0, 0);
	glVertex3f(-2.5, 10, 2);
	glTexCoord2f(1, 0);
	glVertex3f(2.5, 10, 2);
	glTexCoord2f(1, 1);
	glVertex3f(2.5, 6, 2);
	glTexCoord2f(0, 1);
	glVertex3f(-2.5, 6, 2);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-2.5, 10, 2);
	glTexCoord2f(1, 0);
	glVertex3f(2.5, 10, 2);
	glTexCoord2f(1, 1);
	glVertex3f(2.5, 11, -3);
	glTexCoord2f(0, 1);
	glVertex3f(-2.5, 11, -3);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-2.5, 6, 2);
	glTexCoord2f(1, 0);
	glVertex3f(2.5, 6, 2);
	glTexCoord2f(1, 1);
	glVertex3f(2.5, 1, -1);
	glTexCoord2f(0, 1);
	glVertex3f(-2.5, 1, -1);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-2.5, 11, -3);
	glTexCoord2f(1, 0);
	glVertex3f(-2.5, 10, 2);
	glTexCoord2f(1, 1);
	glVertex3f(-2.5, 6, 2);
	glTexCoord2f(0, 1);
	glVertex3f(-2.5, 1, -1);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(2.5, 11, -3);
	glTexCoord2f(1, 0);
	glVertex3f(2.5, 10, 2);
	glTexCoord2f(1, 1);
	glVertex3f(2.5, 6, 2);
	glTexCoord2f(0, 1);
	glVertex3f(2.5, 1, -1);
	glEnd();

	//--------------------------------------Middle top Part
	glBindTexture(GL_TEXTURE_2D, textureBlackCore);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, silver);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, silver);
	glColor3f(silver[0], silver[1], silver[2]);
	glBegin(GL_QUADS);
	//front
	glTexCoord2f(0, 0);
	glVertex3f(-2.5, 11, 1.75);
	glTexCoord2f(1, 0);
	glVertex3f(2.5, 11, 1.75);
	glTexCoord2f(1, 1);
	glVertex3f(2.25, 10, 2);
	glTexCoord2f(0, 1);
	glVertex3f(-2.25, 10, 2);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(-2.5, 11, -3);
	glTexCoord2f(1, 0);
	glVertex3f(2.5, 11, -3);
	glTexCoord2f(1, 1);
	glVertex3f(2.25, 10, -3);
	glTexCoord2f(0, 1);
	glVertex3f(-2.25, 10, -3);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-2.25, 11, 1.75);
	glTexCoord2f(1, 0);
	glVertex3f(2.25, 11, 1.75);
	glTexCoord2f(1, 1);
	glVertex3f(2.25, 11, -2.75);
	glTexCoord2f(0, 1);
	glVertex3f(-2.25, 11, -2.75);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-2.25, 11, -2.75);
	glTexCoord2f(1, 0);
	glVertex3f(-2.25, 11, 1.75);
	glTexCoord2f(1, 1);
	glVertex3f(-2.5, 10, 2);
	glTexCoord2f(0, 1);
	glVertex3f(-2.5, 10, -2);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(2.25, 11, -2.75);
	glTexCoord2f(1, 0);
	glVertex3f(2.25, 11, 1.75);
	glTexCoord2f(1, 1);
	glVertex3f(2.5, 10, 2);
	glTexCoord2f(0, 1);
	glVertex3f(2.5, 10, -2);
	glEnd();

	//--------------------------------------Middle bottom Part
	glColor3f(1, 0, 0);
	glBegin(GL_QUADS);
	//front
	glTexCoord2f(0, 0);
	glVertex3f(-1.25, 4, 1.5);
	glTexCoord2f(1, 0);
	glVertex3f(1.25, 4, 1.5);
	glTexCoord2f(1, 1);
	glVertex3f(1.25, 1.5, 0);
	glTexCoord2f(0, 1);
	glVertex3f(-1.25, 1.5, 0);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-1.25, 4, 1.5);
	glTexCoord2f(1, 0);
	glVertex3f(1.25, 4, 1.5);
	glTexCoord2f(1, 1);
	glVertex3f(1.25, 6, 0);
	glTexCoord2f(0, 1);
	glVertex3f(-1.25, 6, 0);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-1.25, 1.5, 1.5);
	glTexCoord2f(1, 0);
	glVertex3f(1.25, 1.5, 1.5);
	glTexCoord2f(1, 1);
	glVertex3f(1.25, 1.5, 0);
	glTexCoord2f(0, 1);
	glVertex3f(-1.25, 1.5, 0);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-1.25, 6, 0);
	glTexCoord2f(1, 0);
	glVertex3f(-1.25, 4, 1.5);
	glTexCoord2f(1, 1);
	glVertex3f(-1.25, 1.5, 0);
	glTexCoord2f(0, 1);
	glVertex3f(-1.25, 1.5, -1);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(1.25, 6, 0);
	glTexCoord2f(1, 0);
	glVertex3f(1.25, 4, 1.5);
	glTexCoord2f(1, 1);
	glVertex3f(1.25, 1.5, 0);
	glTexCoord2f(0, 1);
	glVertex3f(1.25, 1.5, -1);
	glEnd();

	//-----------------------------------Beside core
	//right front
	glBindTexture(GL_TEXTURE_2D, textureBlackCore);
	glColor3f(silver[0], silver[1], silver[2]);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);
	glVertex3f(7.5, 10, 1);
	glTexCoord2f(1, 0);
	glVertex3f(7.5, 7, 1);
	glTexCoord2f(1, 1);
	glVertex3f(4.5, 6, 1);
	glTexCoord2f(0, 1);
	glVertex3f(4, 4, 0.5);
	glTexCoord2f(0, 0);
	glVertex3f(2.5, 4, 0.5);
	glTexCoord2f(1, 0);
	glVertex3f(2.5, 10, 1);
	glEnd();

	//right side
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);
	glVertex3f(7.5, 10, 1);
	glTexCoord2f(1, 0);
	glVertex3f(7.5, 10, 0);
	glTexCoord2f(1, 1);
	glVertex3f(7.5, 7, 0);
	glTexCoord2f(0, 1);
	glVertex3f(4.5, 6, 0);
	glTexCoord2f(0, 0);
	glVertex3f(4, 4, 0);
	glTexCoord2f(1, 0);
	glVertex3f(2.5, 4, 0);
	glTexCoord2f(1, 1);
	glVertex3f(2.5, 4, 0.5);
	glTexCoord2f(0, 1);
	glVertex3f(4, 4, 0.5);
	glTexCoord2f(0, 0);
	glVertex3f(4.5, 6, 1);
	glTexCoord2f(1, 0);
	glVertex3f(7.5, 7, 1);
	glEnd();

	//left front
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);
	glVertex3f(-7.5, 10, 1);
	glTexCoord2f(1, 0);
	glVertex3f(-7.5, 7, 1);
	glTexCoord2f(1, 1);
	glVertex3f(-4.5, 6, 1);
	glTexCoord2f(0, 1);
	glVertex3f(-4, 4, 0.5);
	glTexCoord2f(0, 0);
	glVertex3f(-2.5, 4, 0.5);
	glTexCoord2f(1, 0);
	glVertex3f(-2.5, 10, 1);
	glEnd();

	//left side
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);
	glVertex3f(-7.5, 10, 1);
	glTexCoord2f(1, 0);
	glVertex3f(-7.5, 10, 0);
	glTexCoord2f(1, 1);
	glVertex3f(-7.5, 7, 0);
	glTexCoord2f(0, 1);
	glVertex3f(-4.5, 6, 0);
	glTexCoord2f(0, 0);
	glVertex3f(-4, 4, 0);
	glTexCoord2f(1, 0);
	glVertex3f(-2.5, 4, 0);
	glTexCoord2f(1, 1);
	glVertex3f(-2.5, 4, 0.5);
	glTexCoord2f(0, 1);
	glVertex3f(-4, 4, 0.5);
	glTexCoord2f(0, 0);
	glVertex3f(-4.5, 6, 1);
	glTexCoord2f(1, 0);
	glVertex3f(-7.5, 7, 1);
	glEnd();

	//left top
	glBegin(GL_QUADS);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, grey);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, grey);
	glColor3f(grey[0], grey[1], grey[2]);
	//front
	glTexCoord2f(0, 0);
	glVertex3f(-7.5, 10, 1);
	glTexCoord2f(1, 0);
	glVertex3f(-2.5, 10, 1);
	glTexCoord2f(1, 1);
	glVertex3f(-2.5, 12, -1);
	glTexCoord2f(0, 1);
	glVertex3f(-7.5, 12, -1);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-7.5, 12, -1);
	glTexCoord2f(1, 0);
	glVertex3f(-2.5, 12, -1);
	glTexCoord2f(1, 1);
	glVertex3f(-2.5, 12, -8);
	glTexCoord2f(0, 1);
	glVertex3f(-7.5, 12, -8);
	glEnd();

	glBegin(GL_TRIANGLES);
	//left
	glTexCoord2f(0, 0);
	glVertex3f(-7.5, 10, 1);
	glTexCoord2f(0.25, 1);
	glVertex3f(-7.5, 12, -1);
	glTexCoord2f(1, 1);
	glVertex3f(-7.5, 12, -8);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(-2.5, 10, 1);
	glTexCoord2f(0.25, 1);
	glVertex3f(-2.5, 12, -1);
	glTexCoord2f(1, 1);
	glVertex3f(-2.5, 12, -8);
	glEnd();

	//right top
	glBegin(GL_QUADS);
	//front
	glTexCoord2f(0, 0);
	glVertex3f(7.5, 10, 1);
	glTexCoord2f(1, 0);
	glVertex3f(2.5, 10, 1);
	glTexCoord2f(1, 1);
	glVertex3f(2.5, 12, -1);
	glTexCoord2f(0, 1);
	glVertex3f(7.5, 12, -1);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(7.5, 12, -1);
	glTexCoord2f(1, 0);
	glVertex3f(2.5, 12, -1);
	glTexCoord2f(1, 1);
	glVertex3f(2.5, 12, -8);
	glTexCoord2f(0, 1);
	glVertex3f(7.5, 12, -8);
	glEnd();

	glBegin(GL_TRIANGLES);
	//left
	glTexCoord2f(0, 0);
	glVertex3f(7.5, 10, 1);
	glTexCoord2f(0.25, 1);
	glVertex3f(7.5, 12, -1);
	glTexCoord2f(1, 1);
	glVertex3f(7.5, 12, -8);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(2.5, 10, 1);
	glTexCoord2f(0.25, 1);
	glVertex3f(2.5, 12, -1);
	glTexCoord2f(1, 1);
	glVertex3f(2.5, 12, -8);
	glEnd();

	//----------------------------------Lamp Part
	glBindTexture(GL_TEXTURE_2D, textureRedLamp);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, red);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, red);
	glColor3f(red[0], red[1], red[2]);
	//left lamp
	glBegin(GL_QUADS);
	//front
	glTexCoord2f(0, 0);
	glVertex3f(-6.5, 11, -1);
	glTexCoord2f(1, 0);
	glVertex3f(-3.5, 11, -1);
	glTexCoord2f(1, 1);
	glVertex3f(-3.5, 14, -1);
	glTexCoord2f(0, 1);
	glVertex3f(-6.5, 14, -1);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textureMetalGrey);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, grey);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, grey);
	glColor3f(grey[0], grey[1], grey[2]);
	glBegin(GL_QUADS);
	//top
	glTexCoord2f(0, 0);
	glVertex3f(-6.5, 14, -1);
	glTexCoord2f(1, 0);
	glVertex3f(-3.5, 14, -1);
	glTexCoord2f(1, 1);
	glVertex3f(-3.5, 14, -3);
	glTexCoord2f(0, 1);
	glVertex3f(-6.5, 14, -3);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-6.5, 11, -1);
	glTexCoord2f(1, 0);
	glVertex3f(-3.5, 11, -1);
	glTexCoord2f(1, 1);
	glVertex3f(-3.5, 11, -5);
	glTexCoord2f(0, 1);
	glVertex3f(-6.5, 11, -5);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(-6.5, 11, -5);
	glTexCoord2f(1, 0);
	glVertex3f(-3.5, 11, -5);
	glTexCoord2f(1, 1);
	glVertex3f(-3.5, 14, -3);
	glTexCoord2f(0, 1);
	glVertex3f(-6.5, 14, -3);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-6.5, 11, -1);
	glTexCoord2f(1, 0);
	glVertex3f(-6.5, 11, -5);
	glTexCoord2f(1, 1);
	glVertex3f(-6.5, 14, -3);
	glTexCoord2f(0, 1);
	glVertex3f(-6.5, 14, -1);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(-3.5, 11, -1);
	glTexCoord2f(1, 0);
	glVertex3f(-3.5, 11, -5);
	glTexCoord2f(1, 1);
	glVertex3f(-3.5, 14, -3);
	glTexCoord2f(0, 1);
	glVertex3f(-3.5, 14, -1);
	glEnd();

	//right lamp
	glBindTexture(GL_TEXTURE_2D, textureRedLamp);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, red);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, red);
	glColor3f(red[0], red[1], red[2]);
	glBegin(GL_QUADS);
	//front
	glTexCoord2f(0, 0);
	glVertex3f(6.5, 11, -1);
	glTexCoord2f(1, 0);
	glVertex3f(3.5, 11, -1);
	glTexCoord2f(1, 1);
	glVertex3f(3.5, 14, -1);
	glTexCoord2f(0, 1);
	glVertex3f(6.5, 14, -1);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textureMetalGrey);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, grey);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, grey);
	glColor3f(grey[0], grey[1], grey[2]);
	glBegin(GL_QUADS);
	//top
	glTexCoord2f(0, 0);
	glVertex3f(6.5, 14, -1);
	glTexCoord2f(1, 0);
	glVertex3f(3.5, 14, -1);
	glTexCoord2f(1, 1);
	glVertex3f(3.5, 14, -3);
	glTexCoord2f(0, 1);
	glVertex3f(6.5, 14, -3);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(6.5, 11, -1);
	glTexCoord2f(1, 0);
	glVertex3f(3.5, 11, -1);
	glTexCoord2f(1, 1);
	glVertex3f(3.5, 11, -5);
	glTexCoord2f(0, 1);
	glVertex3f(6.5, 11, -5);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(6.5, 11, -5);
	glTexCoord2f(1, 0);
	glVertex3f(3.5, 11, -5);
	glTexCoord2f(1, 1);
	glVertex3f(3.5, 14, -3);
	glTexCoord2f(0, 1);
	glVertex3f(6.5, 14, -3);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(6.5, 11, -1);
	glTexCoord2f(1, 0);
	glVertex3f(6.5, 11, -5);
	glTexCoord2f(1, 1);
	glVertex3f(6.5, 14, -3);
	glTexCoord2f(0, 1);
	glVertex3f(6.5, 14, -1);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(3.5, 11, -1);
	glTexCoord2f(1, 0);
	glVertex3f(3.5, 11, -5);
	glTexCoord2f(1, 1);
	glVertex3f(3.5, 14, -3);
	glTexCoord2f(0, 1);
	glVertex3f(3.5, 14, -1);
	glEnd();

	//-------------------------------Neck part
	glColor3f(grey[0], grey[1], grey[2]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-2.5, 11, -7);
	glTexCoord2f(1, 0);
	glVertex3f(-2.25, 12, -5);
	glTexCoord2f(1, 1);
	glVertex3f(-2.25, 10, -5);
	glTexCoord2f(0, 1);
	glVertex3f(-2.5, 10, -7);

	glTexCoord2f(0, 0);
	glVertex3f(-2.25, 12, -5);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 13, -3);
	glTexCoord2f(1, 1);
	glVertex3f(-2, 10, -3);
	glTexCoord2f(0, 1);
	glVertex3f(-2.25, 10, -5);

	glTexCoord2f(0, 0);
	glVertex3f(-2, 13, -3);
	glTexCoord2f(1, 0);
	glVertex3f(2, 13, -3);
	glTexCoord2f(1, 1);
	glVertex3f(2, 10, -3);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 10, -3);

	glTexCoord2f(0, 0);
	glVertex3f(2.25, 12, -5);
	glTexCoord2f(1, 0);
	glVertex3f(2, 13, -3);
	glTexCoord2f(1, 1);
	glVertex3f(2, 10, -3);
	glTexCoord2f(0, 1);
	glVertex3f(2.25, 10, -5);

	glTexCoord2f(0, 0);
	glVertex3f(2.5, 11, -7);
	glTexCoord2f(1, 0);
	glVertex3f(2.25, 12, -5);
	glTexCoord2f(1, 1);
	glVertex3f(2.25, 10, -5);
	glTexCoord2f(0, 1);
	glVertex3f(2.5, 10, -7);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, silver);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, silver);
	glColor3f(silver[0], silver[1], silver[2]);
	//front
	glTexCoord2f(0, 0);
	glVertex3f(-1, 13, -4);
	glTexCoord2f(1, 0);
	glVertex3f(1, 13, -4);
	glTexCoord2f(1, 1);
	glVertex3f(1, 10, -2);
	glTexCoord2f(0, 1);
	glVertex3f(-1, 10, -2);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(-1, 13, -7);
	glTexCoord2f(1, 0);
	glVertex3f(1, 13, -7);
	glTexCoord2f(1, 1);
	glVertex3f(1, 10, -8);
	glTexCoord2f(0, 1);
	glVertex3f(-1, 10, -8);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-1, 13, -4);
	glTexCoord2f(1, 0);
	glVertex3f(1, 13, -4);
	glTexCoord2f(1, 1);
	glVertex3f(1, 13, -7);
	glTexCoord2f(0, 1);
	glVertex3f(-1, 13, -7);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-1, 10, -8);
	glTexCoord2f(1, 0);
	glVertex3f(-1, 10, -4);
	glTexCoord2f(1, 1);
	glVertex3f(-0.5, 13, -4);
	glTexCoord2f(0, 1);
	glVertex3f(-0.5, 13, -8);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(1, 10, -8);
	glTexCoord2f(1, 0);
	glVertex3f(1, 10, -4);
	glTexCoord2f(1, 1);
	glVertex3f(0.5, 13, -4);
	glTexCoord2f(0, 1);
	glVertex3f(0.5, 13, -8);
	glEnd();

	//-------------------------------Fan part
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, textureNuclear);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, red);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, red);
	glColor3f(red[0], red[1], red[2]);
	gluQuadricTexture(obj, true);
	glTranslatef(-6, 5, 1);
	glRotatef(180, 1, 0, 0);
	gluCylinder(obj, 1, 1, 1, 20, 20);
	glPushMatrix();
	glTranslatef(0, 0, 1);
	gluSphere(obj, 1, 10, 10);
	glPopMatrix();

	gluQuadricTexture(obj, true);
	glTranslatef(12, 0, 1);
	glRotatef(180, 1, 0, 0);
	gluCylinder(obj, 1, 1, 1, 20, 20);
	glPushMatrix();
	gluSphere(obj, 1, 10, 10);
	glPopMatrix();
	glPopMatrix();

#pragma endregion core
	glPopMatrix();
}

void lowerBody() {
	glPushMatrix();
#pragma region core
	glBindTexture(GL_TEXTURE_2D, textureMetalGrey);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, grey);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, grey);
	glColor3f(grey[0], grey[1], grey[2]);
	glBegin(GL_QUADS);
	//front
	glTexCoord2f(0, 0);
	glVertex3f(-5, 0, 2);
	glTexCoord2f(1, 0);
	glVertex3f(5, 0, 2);
	glTexCoord2f(1, 1);
	glVertex3f(5, 3, 2);
	glTexCoord2f(0, 1);
	glVertex3f(-5, 3, 2);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(-5, 0, -2);
	glTexCoord2f(1, 0);
	glVertex3f(5, 0, -2);
	glTexCoord2f(1, 1);
	glVertex3f(5, 3, -2);
	glTexCoord2f(0, 1);
	glVertex3f(-5, 3, -2);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-5, 3, -2);
	glTexCoord2f(1, 0);
	glVertex3f(5, 3, -2);
	glTexCoord2f(1, 1);
	glVertex3f(5, 3, 2);
	glTexCoord2f(0, 1);
	glVertex3f(-5, 3, 2);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-5, 0, -2);
	glTexCoord2f(1, 0);
	glVertex3f(5, 0, -2);
	glTexCoord2f(1, 1);
	glVertex3f(5, 0, 2);
	glTexCoord2f(0, 1);
	glVertex3f(-5, 0, 2);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-5, 0, -2);
	glTexCoord2f(1, 0);
	glVertex3f(-5, 3, -2);
	glTexCoord2f(1, 1);
	glVertex3f(-5, 3, 2);
	glTexCoord2f(0, 1);
	glVertex3f(-5, 0, 2);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(5, 0, -2);
	glTexCoord2f(1, 0);
	glVertex3f(5, 3, -2);
	glTexCoord2f(1, 1);
	glVertex3f(5, 3, 2);
	glTexCoord2f(0, 1);
	glVertex3f(5, 0, 2);

	//----------------------------------join
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, silver);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, silver);
	glColor3f(silver[0], silver[1], silver[2]);
	//front
	glTexCoord2f(0, 0);
	glVertex3f(-3, 3, 1);
	glTexCoord2f(1, 0);
	glVertex3f(3, 3, 1);
	glTexCoord2f(1, 1);
	glVertex3f(2.5, 4, 1);
	glTexCoord2f(0, 1);
	glVertex3f(-2.5, 4, 1);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(-3, 3, -1);
	glTexCoord2f(1, 0);
	glVertex3f(3, 3, -1);
	glTexCoord2f(1, 1);
	glVertex3f(2.5, 4, -1);
	glTexCoord2f(0, 1);
	glVertex3f(-2.5, 4, -1);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-3, 3, -1);
	glTexCoord2f(1, 0);
	glVertex3f(-3, 3, 1);
	glTexCoord2f(1, 1);
	glVertex3f(-2.5, 4, 1);
	glTexCoord2f(0, 1);
	glVertex3f(-2.5, 4, -1);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(3, 3, -1);
	glTexCoord2f(1, 0);
	glVertex3f(3, 3, 1);
	glTexCoord2f(1, 1);
	glVertex3f(2.5, 4, 1);
	glTexCoord2f(0, 1);
	glVertex3f(2.5, 4, -1);
	glEnd();
#pragma endregion core

#pragma region butt
	glBindTexture(GL_TEXTURE_2D, textureMetalBlueShine);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, indigo);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, indigo);
	glColor3f(indigo[0], indigo[1], indigo[2]);
	glBegin(GL_POLYGON);
	//front
	glTexCoord2f(0, 0);
	glVertex3f(-5, 3, -2);
	glTexCoord2f(1, 0);
	glVertex3f(5, 3, -2);
	glTexCoord2f(1, 1);
	glVertex3f(6, -4, -2);
	glTexCoord2f(0, 1);
	glVertex3f(5, -5, -2);
	glTexCoord2f(0, 0);
	glVertex3f(-5, -5, -2);
	glTexCoord2f(1, 0);
	glVertex3f(-6, -4, -2);
	glEnd();

	glBegin(GL_POLYGON);
	//back
	glTexCoord2f(0, 0);
	glVertex3f(-5, 3, -3);
	glTexCoord2f(1, 0);
	glVertex3f(5, 3, -3);
	glTexCoord2f(1, 1);
	glVertex3f(6, -4, -3);
	glTexCoord2f(0, 1);
	glVertex3f(5, -5, -3);
	glTexCoord2f(0, 0);
	glVertex3f(-5, -5, -3);
	glTexCoord2f(1, 0);
	glVertex3f(-6, -4, -3);
	glEnd();

	glBegin(GL_QUADS);
	//top
	glTexCoord2f(0, 0);
	glVertex3f(-5, 3, -2);
	glTexCoord2f(1, 0);
	glVertex3f(5, 3, -2);
	glTexCoord2f(1, 1);
	glVertex3f(5, 3, -3);
	glTexCoord2f(0, 1);
	glVertex3f(-5, 3, -3);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-5, -5, -2);
	glTexCoord2f(1, 0);
	glVertex3f(5, -5, -2);
	glTexCoord2f(1, 1);
	glVertex3f(5, -5, -3);
	glTexCoord2f(0, 1);
	glVertex3f(-5, -5, -3);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-5, 3, -2);
	glTexCoord2f(1, 0);
	glVertex3f(-6, -4, -2);
	glTexCoord2f(1, 1);
	glVertex3f(-6, -4, -3);
	glTexCoord2f(0, 1);
	glVertex3f(-5, 3, -3);

	glTexCoord2f(0, 0);
	glVertex3f(-6, -4, -2);
	glTexCoord2f(1, 0);
	glVertex3f(-6, -4, -3);
	glTexCoord2f(1, 1);
	glVertex3f(-5, -5, -3);
	glTexCoord2f(0, 1);
	glVertex3f(-5, -5, -2);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(5, 3, -2);
	glTexCoord2f(1, 0);
	glVertex3f(6, -4, -2);
	glTexCoord2f(1, 1);
	glVertex3f(6, -4, -3);
	glTexCoord2f(0, 1);
	glVertex3f(5, 3, -3);

	glTexCoord2f(0, 0);
	glVertex3f(6, -4, -2);
	glTexCoord2f(1, 0);
	glVertex3f(6, -4, -3);
	glTexCoord2f(1, 1);
	glVertex3f(5, -5, -3);
	glTexCoord2f(0, 1);
	glVertex3f(5, -5, -2);
	glEnd();

	//-----------------------------butt pattern
	glBindTexture(GL_TEXTURE_2D, textureMetalGrey);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, darkBlue);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, darkBlue);
	glColor3f(darkBlue[0], darkBlue[1], darkBlue[2]);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);
	glVertex3f(0, 2, -3.25);
	glTexCoord2f(1, 0);
	glVertex3f(-4, 1, -3.25);
	glTexCoord2f(1, 1);
	glVertex3f(-3.5, -3.5, -3.25);
	glTexCoord2f(0, 1);
	glVertex3f(-3, -4, -3.25);
	glTexCoord2f(0, 0);
	glVertex3f(3, -4, -3.25);
	glTexCoord2f(1, 0);
	glVertex3f(3.5, -3.5, -3.25);
	glTexCoord2f(1, 1);
	glVertex3f(4, 1, -3.25);
	glEnd();
#pragma endregion butt

#pragma region buttTop
	//-----------------------------butt pattern
	//front
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);
	glVertex3f(-2, 3.5, -4);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 0, -4);
	glTexCoord2f(1, 1);
	glVertex3f(-1, -1, -4);
	glTexCoord2f(0, 1);
	glVertex3f(1, -1, -4);
	glTexCoord2f(0, 1);
	glVertex3f(2, 0, -4);
	glTexCoord2f(0, 0);
	glVertex3f(2, 3.5, -4);
	glEnd();

	//back
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);
	glVertex3f(-2, 3.5, -2.5);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 0, -2.5);
	glTexCoord2f(1, 1);
	glVertex3f(-1, -1, -2.5);
	glTexCoord2f(0, 1);
	glVertex3f(1, -1, -2.5);
	glTexCoord2f(0, 0);
	glVertex3f(2, 0, -2.5);
	glTexCoord2f(1, 0);
	glVertex3f(2, 3.5, -2.5);
	glEnd();

	glBegin(GL_QUADS);
	//top
	glTexCoord2f(0, 0);
	glVertex3f(-2, 3.5, -2.5);
	glTexCoord2f(1, 0);
	glVertex3f(2, 3.5, -2.5);
	glTexCoord2f(1, 1);
	glVertex3f(2, 3.5, -4);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 3.5, -4);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-1, -1, -2.5);
	glTexCoord2f(1, 0);
	glVertex3f(1, -1, -2.5);
	glTexCoord2f(1, 1);
	glVertex3f(1, -1, -4);
	glTexCoord2f(0, 1);
	glVertex3f(-1, -1, -4);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-2, 3.5, -2.5);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 3.5, -4);
	glTexCoord2f(1, 1);
	glVertex3f(-2, 0, -4);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 0, -2.5);

	glTexCoord2f(0, 0);
	glVertex3f(-2, 0, -2.5);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 0, -4);
	glTexCoord2f(1, 1);
	glVertex3f(-1, -1, -4);
	glTexCoord2f(0, 1);
	glVertex3f(-1, -1, -2.5);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(2, 3.5, -2.5);
	glTexCoord2f(1, 0);
	glVertex3f(2, 3.5, -4);
	glTexCoord2f(1, 1);
	glVertex3f(2, 0, -4);
	glTexCoord2f(0, 1);
	glVertex3f(2, 0, -2.5);

	glTexCoord2f(0, 0);
	glVertex3f(2, 0, -2.5);
	glTexCoord2f(1, 0);
	glVertex3f(2, 0, -4);
	glTexCoord2f(1, 1);
	glVertex3f(1, -1, -4);
	glTexCoord2f(0, 1);
	glVertex3f(1, -1, -2.5);
	glEnd();
#pragma endregion buttTop

#pragma region frontPart
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, darkBlue);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, darkBlue);
	glColor3f(darkBlue[0], darkBlue[1], darkBlue[2]);
	glBegin(GL_QUADS);
	//back
	glTexCoord2f(0, 0);
	glVertex3f(-1.5, 4, 2);
	glTexCoord2f(1, 0);
	glVertex3f(1.5, 4, 2);
	glTexCoord2f(1, 1);
	glVertex3f(1.5, -5, 2);
	glTexCoord2f(0, 1);
	glVertex3f(-1.5, -5, 2);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-1.5, 4, 2);
	glTexCoord2f(1, 0);
	glVertex3f(1.5, 4, 2);
	glTexCoord2f(1, 1);
	glVertex3f(1.5, 4, 4);
	glTexCoord2f(0, 1);
	glVertex3f(-1.5, 4, 4);

	//front top
	glTexCoord2f(0, 0);
	glVertex3f(-1.5, 4, 4);
	glTexCoord2f(1, 0);
	glVertex3f(1.5, 4, 4);
	glTexCoord2f(1, 1);
	glVertex3f(1.5, 3, 5);
	glTexCoord2f(0, 1);
	glVertex3f(-1.5, 3, 5);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(-1.5, 3, 5);
	glTexCoord2f(1, 0);
	glVertex3f(1.5, 3, 5);
	glTexCoord2f(1, 1);
	glVertex3f(1.5, -3, 5);
	glTexCoord2f(0, 1);
	glVertex3f(-1.5, -3, 5);

	//front bottom
	glTexCoord2f(0, 0);
	glVertex3f(-1.5, -3, 5);
	glTexCoord2f(1, 0);
	glVertex3f(1.5, -3, 5);
	glTexCoord2f(1, 1);
	glVertex3f(1.5, -6, 3);
	glTexCoord2f(0, 1);
	glVertex3f(-1.5, -6, 3);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-1.5, -6, 3);
	glTexCoord2f(1, 0);
	glVertex3f(1.5, -6, 3);
	glTexCoord2f(1, 1);
	glVertex3f(1.5, -5, 2);
	glTexCoord2f(0, 1);
	glVertex3f(-1.5, -5, 2);
	glEnd();

	//left
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);
	glVertex3f(-1.5, -5, 2);
	glTexCoord2f(1, 0);
	glVertex3f(-1.5, -6, 3);
	glTexCoord2f(1, 1);
	glVertex3f(-1.5, -3, 5);
	glTexCoord2f(0, 1);
	glVertex3f(-1.5, 3, 5);
	glTexCoord2f(0, 0);
	glVertex3f(-1.5, 4, 4);
	glTexCoord2f(1, 0);
	glVertex3f(-1.5, 4, 2);
	glEnd();

	//right
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);
	glVertex3f(1.5, -5, 2);
	glTexCoord2f(1, 0);
	glVertex3f(1.5, -6, 3);
	glTexCoord2f(1, 1);
	glVertex3f(1.5, -3, 5);
	glTexCoord2f(0, 1);
	glVertex3f(1.5, 3, 5);
	glTexCoord2f(0, 0);
	glVertex3f(1.5, 4, 4);
	glTexCoord2f(1, 0);
	glVertex3f(1.5, 4, 2);
	glEnd();
#pragma endregion frontPart
	glPopMatrix();
}

void leftHand() {
	glPushMatrix();
#pragma region hand
	glBindTexture(GL_TEXTURE_2D, textureMetalGrey);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, silver);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, silver);
	glColor3f(silver[0], silver[1], silver[2]);
	//----------------------------------right plam
	glBegin(GL_QUADS);
	//front
	glTexCoord2f(0, 0);
	glVertex3f(-0.5, 0, 2);
	glTexCoord2f(1, 0);
	glVertex3f(0.5, 0, 2);
	glTexCoord2f(1, 1);
	glVertex3f(1, 3, 2);
	glTexCoord2f(0, 1);
	glVertex3f(-0.5, 4, 2);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(-0.5, 0, -2);
	glTexCoord2f(1, 0);
	glVertex3f(0.5, 0, -2);
	glTexCoord2f(1, 1);
	glVertex3f(1, 3, -2);
	glTexCoord2f(0, 1);
	glVertex3f(-0.5, 4, -2);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(0.5, 0, 2);
	glTexCoord2f(1, 0);
	glVertex3f(0.5, 0, -2);
	glTexCoord2f(1, 1);
	glVertex3f(1, 3, -2);
	glTexCoord2f(0, 1);
	glVertex3f(1, 3, 2);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-0.5, 0, 2);
	glTexCoord2f(1, 0);
	glVertex3f(-0.5, 0, -2);
	glTexCoord2f(1, 1);
	glVertex3f(-0.5, 4, -2);
	glTexCoord2f(0, 1);
	glVertex3f(-0.5, 4, 2);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-0.5, 4, -2);
	glTexCoord2f(1, 0);
	glVertex3f(-0.5, 4, 2);
	glTexCoord2f(1, 1);
	glVertex3f(1, 3, 2);
	glTexCoord2f(0, 1);
	glVertex3f(1, 3, -2);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-0.5, 0, -2);
	glTexCoord2f(1, 0);
	glVertex3f(-0.5, 0, 2);
	glTexCoord2f(1, 1);
	glVertex3f(0.5, 0, 2);
	glTexCoord2f(0, 1);
	glVertex3f(0.5, 0, -2);

	//-------------------------------------finger
	//front 1
	glTexCoord2f(0, 0);
	glVertex3f(-0.5, 0, 2);
	glTexCoord2f(1, 0);
	glVertex3f(-1.75, 0, 2);
	glTexCoord2f(1, 1);
	glVertex3f(-1.5, 1, 2);
	glTexCoord2f(0, 1);
	glVertex3f(-0.5, 1, 2);

	glTexCoord2f(0, 0);
	glVertex3f(-1.75, 0, 2);
	glTexCoord2f(1, 0);
	glVertex3f(-1.25, 1, 2);
	glTexCoord2f(1, 1);
	glVertex3f(-1.5, 2, 2);
	glTexCoord2f(0, 1);
	glVertex3f(-2.25, 2.25, 2);

	glTexCoord2f(0, 0);
	glVertex3f(-1.5, 1.5, 2);
	glTexCoord2f(1, 0);
	glVertex3f(-2.25, 2.25, 2);
	glTexCoord2f(1, 1);
	glVertex3f(-0.5, 2.25, 2);
	glTexCoord2f(0, 1);
	glVertex3f(-0.5, 1.5, 2);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-1.75, 0, 2);
	glTexCoord2f(1, 0);
	glVertex3f(-2.25, 2.25, 2);
	glTexCoord2f(1, 1);
	glVertex3f(-2.25, 2.25, 1);
	glTexCoord2f(0, 1);
	glVertex3f(-1.75, 0, 1);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-2.25, 2.25, 2);
	glTexCoord2f(1, 0);
	glVertex3f(-0.5, 2.25, 2);
	glTexCoord2f(1, 1);
	glVertex3f(-0.5, 2.25, 1);
	glTexCoord2f(0, 1);
	glVertex3f(-2.25, 2.25, 1);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-0.5, 0, 2);
	glTexCoord2f(1, 0);
	glVertex3f(-1.75, 0, 2);
	glTexCoord2f(1, 1);
	glVertex3f(-1.75, 0, 1);
	glTexCoord2f(0, 1);
	glVertex3f(-0.5, 0, 1);

	//front 2
	glTexCoord2f(0, 0);
	glVertex3f(-0.5, 0, 1);
	glTexCoord2f(1, 0);
	glVertex3f(-1.75, 0, 1);
	glTexCoord2f(1, 1);
	glVertex3f(-1.5, 1, 1);
	glTexCoord2f(0, 1);
	glVertex3f(-0.5, 1, 1);

	glTexCoord2f(0, 0);
	glVertex3f(-1.75, 0, 1);
	glTexCoord2f(1, 0);
	glVertex3f(-1.25, 1, 1);
	glTexCoord2f(1, 1);
	glVertex3f(-1.5, 2, 1);
	glTexCoord2f(0, 1);
	glVertex3f(-2.25, 2.25, 1);

	glTexCoord2f(0, 0);
	glVertex3f(-1.5, 1.5, 1);
	glTexCoord2f(1, 0);
	glVertex3f(-2.25, 2.25, 1);
	glTexCoord2f(1, 1);
	glVertex3f(-0.5, 2.25, 1);
	glTexCoord2f(0, 1);
	glVertex3f(-0.5, 1.5, 1);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-1.75, 0, 1);
	glTexCoord2f(1, 0);
	glVertex3f(-2.25, 2.25, 1);
	glTexCoord2f(1, 1);
	glVertex3f(-2.25, 2.25, 0);
	glTexCoord2f(0, 1);
	glVertex3f(-1.75, 0, 0);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-2.25, 2.25, 1);
	glTexCoord2f(1, 0);
	glVertex3f(-0.5, 2.25, 1);
	glTexCoord2f(1, 1);
	glVertex3f(-0.5, 2.25, 0);
	glTexCoord2f(0, 1);
	glVertex3f(-2.25, 2.25, 0);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-0.5, 0, 1);
	glTexCoord2f(1, 0);
	glVertex3f(-1.75, 0, 1);
	glTexCoord2f(1, 1);
	glVertex3f(-1.75, 0, 0);
	glTexCoord2f(0, 1);
	glVertex3f(-0.5, 0, 0);

	//front 3
	glTexCoord2f(0, 0);
	glVertex3f(-0.5, 0, 0);
	glTexCoord2f(1, 0);
	glVertex3f(-1.75, 0, 0);
	glTexCoord2f(1, 1);
	glVertex3f(-1.5, 1, 0);
	glTexCoord2f(0, 1);
	glVertex3f(-0.5, 1, 0);

	glTexCoord2f(0, 0);
	glVertex3f(-1.75, 0, 0);
	glTexCoord2f(1, 0);
	glVertex3f(-1.25, 1, 0);
	glTexCoord2f(1, 1);
	glVertex3f(-1.5, 2, 0);
	glTexCoord2f(0, 1);
	glVertex3f(-2.25, 2.25, 0);

	glTexCoord2f(0, 0);
	glVertex3f(-1.5, 1.5, 0);
	glTexCoord2f(1, 0);
	glVertex3f(-2.25, 2.25, 0);
	glTexCoord2f(1, 1);
	glVertex3f(-0.5, 2.25, 0);
	glTexCoord2f(0, 1);
	glVertex3f(-0.5, 1.5, 0);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-1.75, 0, 0);
	glTexCoord2f(1, 0);
	glVertex3f(-2.25, 2.25, 0);
	glTexCoord2f(1, 1);
	glVertex3f(-2.25, 2.25, -1);
	glTexCoord2f(0, 1);
	glVertex3f(-1.75, 0, -1);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-2.25, 2.25, 0);
	glTexCoord2f(1, 0);
	glVertex3f(-0.5, 2.25, 0);
	glTexCoord2f(1, 1);
	glVertex3f(-0.5, 2.25, -1);
	glTexCoord2f(0, 1);
	glVertex3f(-2.25, 2.25, -1);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-0.5, 0, 0);
	glTexCoord2f(1, 0);
	glVertex3f(-1.75, 0, 0);
	glTexCoord2f(1, 1);
	glVertex3f(-1.75, 0, -1);
	glTexCoord2f(0, 1);
	glVertex3f(-0.5, 0, -1);

	//front 4
	glTexCoord2f(0, 0);
	glVertex3f(-0.5, 0, -1);
	glTexCoord2f(1, 0);
	glVertex3f(-1.75, 0, -1);
	glTexCoord2f(1, 1);
	glVertex3f(-1.5, 1, -1);
	glTexCoord2f(0, 1);
	glVertex3f(-0.5, 1, -1);

	glTexCoord2f(0, 0);
	glVertex3f(-1.75, 0, -1);
	glTexCoord2f(1, 0);
	glVertex3f(-1.25, 1, -1);
	glTexCoord2f(1, 1);
	glVertex3f(-1.5, 2, -1);
	glTexCoord2f(0, 1);
	glVertex3f(-2.25, 2.25, -1);

	glTexCoord2f(0, 0);
	glVertex3f(-1.5, 1.5, -1);
	glTexCoord2f(1, 0);
	glVertex3f(-2.25, 2.25, -1);
	glTexCoord2f(1, 1);
	glVertex3f(-0.5, 2.25, -1);
	glTexCoord2f(0, 1);
	glVertex3f(-0.5, 1.5, -1);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-1.75, 0, -1);
	glTexCoord2f(1, 0);
	glVertex3f(-2.25, 2.25, -1);
	glTexCoord2f(1, 1);
	glVertex3f(-2.25, 2.25, -2);
	glTexCoord2f(0, 1);
	glVertex3f(-1.75, 0, -2);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-2.25, 2.25, -1);
	glTexCoord2f(1, 0);
	glVertex3f(-0.5, 2.25, -1);
	glTexCoord2f(1, 1);
	glVertex3f(-0.5, 2.25, -2);
	glTexCoord2f(0, 1);
	glVertex3f(-2.25, 2.25, -2);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-0.5, 0, -1);
	glTexCoord2f(1, 0);
	glVertex3f(-1.75, 0, -1);
	glTexCoord2f(1, 1);
	glVertex3f(-1.75, 0, -2);
	glTexCoord2f(0, 1);
	glVertex3f(-0.5, 0, -2);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(-0.5, 0, -2);
	glTexCoord2f(1, 0);
	glVertex3f(-1.75, 0, -2);
	glTexCoord2f(1, 1);
	glVertex3f(-1.5, 1, -2);
	glTexCoord2f(0, 1);
	glVertex3f(-0.5, 1, -2);

	glTexCoord2f(0, 0);
	glVertex3f(-1.75, 0, -2);
	glTexCoord2f(1, 0);
	glVertex3f(-1.25, 1, -2);
	glTexCoord2f(1, 1);
	glVertex3f(-1.5, 2, -2);
	glTexCoord2f(0, 1);
	glVertex3f(-2.25, 2.25, -2);

	glTexCoord2f(0, 0);
	glVertex3f(-1.5, 1.5, -2);
	glTexCoord2f(1, 0);
	glVertex3f(-2.25, 2.25, -2);
	glTexCoord2f(1, 1);
	glVertex3f(-0.5, 2.25, -2);
	glTexCoord2f(0, 1);
	glVertex3f(-0.5, 1.5, -2);

	//------------------------------------thumb
	//back
	glTexCoord2f(0, 0);
	glVertex3f(-0.5, 4, 2);
	glTexCoord2f(1, 0);
	glVertex3f(-0.5, 2, 2);
	glTexCoord2f(1, 1);
	glVertex3f(-1.5, 1.5, 2);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 2, 2);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(-0.5, 4, 3);
	glTexCoord2f(1, 0);
	glVertex3f(-0.5, 2, 3);
	glTexCoord2f(1, 1);
	glVertex3f(-1.5, 1.5, 3);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 2, 3);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(-0.5, 4, 3);
	glTexCoord2f(1, 0);
	glVertex3f(-0.5, 2, 3);
	glTexCoord2f(1, 1);
	glVertex3f(-0.5, 2, 2);
	glTexCoord2f(0, 1);
	glVertex3f(-0.5, 4, 2);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-0.5, 2, 3);
	glTexCoord2f(1, 0);
	glVertex3f(-1.5, 1.5, 3);
	glTexCoord2f(1, 1);
	glVertex3f(-1.5, 1.5, 2);
	glTexCoord2f(0, 1);
	glVertex3f(-0.5, 2, 2);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-0.5, 4, 3);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 2, 3);
	glTexCoord2f(1, 1);
	glVertex3f(-2, 2, 2);
	glTexCoord2f(0, 1);
	glVertex3f(-0.5, 4, 2);

	//layer2
	//front
	glTexCoord2f(0, 0);
	glVertex3f(-1.5, 1.5, 3);
	glTexCoord2f(1, 0);
	glVertex3f(-2.5, 2, 1.5);
	glTexCoord2f(1, 1);
	glVertex3f(-2.5, 3, 1.5);
	glTexCoord2f(0, 1);
	glVertex3f(-1, 2.5, 3);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-2.5, 3, 1.5);
	glTexCoord2f(1, 0);
	glVertex3f(-1, 2.5, 3);
	glTexCoord2f(1, 1);
	glVertex3f(-0.5, 2.5, 3);
	glTexCoord2f(0, 1);
	glVertex3f(-1.5, 3, 1.75);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-1.5, 1.5, 3);
	glTexCoord2f(1, 0);
	glVertex3f(-2.5, 2, 1.5);
	glTexCoord2f(1, 1);
	glVertex3f(-0.5, 2, 3);
	glTexCoord2f(0, 1);
	glVertex3f(-1.5, 2, 1.75);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(-2.5, 3, 1.5);
	glTexCoord2f(1, 0);
	glVertex3f(-1.5, 3, 1.75);
	glTexCoord2f(1, 1);
	glVertex3f(-1.5, 2, 1.75);
	glTexCoord2f(0, 1);
	glVertex3f(-1.5, 1.5, 3);

	//layer3
	//front
	glTexCoord2f(0, 0);
	glVertex3f(-2, 3, -1);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 2, -1);
	glTexCoord2f(1, 1);
	glVertex3f(-2.5, 2, 1.5);
	glTexCoord2f(0, 1);
	glVertex3f(-2.5, 3, 1.5);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-2, 3, -1);
	glTexCoord2f(1, 0);
	glVertex3f(-1, 3, -1);
	glTexCoord2f(1, 1);
	glVertex3f(-1, 2.5, 3);
	glTexCoord2f(0, 1);
	glVertex3f(-2.5, 3, 1.5);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-1, 2, -1);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 2, -1);
	glTexCoord2f(1, 1);
	glVertex3f(-2.5, 2, 1.5);
	glTexCoord2f(0, 1);
	glVertex3f(-1.5, 1.5, 3);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(-2, 3, -1);
	glTexCoord2f(1, 0);
	glVertex3f(-1, 3, -1);
	glTexCoord2f(1, 1);
	glVertex3f(-1, 2, -1);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 2, -1);
	glEnd();

	//-----------------------------------------sword
	glPushMatrix();
	glTranslatef(-1, 1, 2);
	glRotatef(90, 1, 0, 0);
	sword();
	glPopMatrix();
#pragma endregion hand
	glPopMatrix();
}

void leftLowerArm() {
	glPushMatrix();
#pragma region core
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, textureMetalGrey);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, grey);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, grey);
	glColor3f(grey[0], grey[1], grey[2]);
	glTranslatef(0, 4, 0);
	gluQuadricTexture(obj, true);
	gluSphere(obj, 1, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 4, 0);
	glRotatef(-90, 1, 0, 0);
	glBindTexture(GL_TEXTURE_2D, textureMetalGrey);
	gluQuadricTexture(obj, true);
	gluCylinder(obj, 1.5, 1.5, 6, 10, 10);
	glPopMatrix();
#pragma endregion core
#pragma region shield
	//front
	glBindTexture(GL_TEXTURE_2D, textureMetalBlueShine);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, indigo);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, indigo);
	glColor3f(indigo[0], indigo[1], indigo[2]);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);
	glVertex3f(-2, 4, 2);
	glTexCoord2f(1, 0);
	glVertex3f(2, 4, 2);
	glTexCoord2f(1, 1);
	glVertex3f(2, 8, 2);
	glTexCoord2f(0, 1);
	glVertex3f(2, 11, 1.5);
	glTexCoord2f(0, 0);
	glVertex3f(1.5, 11, 1.5);
	glTexCoord2f(1, 0);
	glVertex3f(0.75, 8, 2);
	glTexCoord2f(1, 1);
	glVertex3f(-0.75, 8, 2);
	glTexCoord2f(0, 1);
	glVertex3f(-1.5, 11, 1.5);
	glTexCoord2f(0, 0);
	glVertex3f(-2, 11, 1.5);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 8, 2);
	glEnd();

	//back
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);
	glVertex3f(-2, 4, -2);
	glTexCoord2f(1, 0);
	glVertex3f(2, 4, -2);
	glTexCoord2f(1, 1);
	glVertex3f(2, 8, -2);
	glTexCoord2f(0, 1);
	glVertex3f(2, 11, -1.5);
	glTexCoord2f(0, 0);
	glVertex3f(1.5, 11, -1.5);
	glTexCoord2f(1, 0);
	glVertex3f(0.75, 8, -2);
	glTexCoord2f(1, 1);
	glVertex3f(-0.75, 8, -2);
	glTexCoord2f(0, 1);
	glVertex3f(-1.5, 11, -1.5);
	glTexCoord2f(0, 0);
	glVertex3f(-2, 11, -1.5);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 8, -2);
	glEnd();

	//left
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);
	glVertex3f(-2, 4, 2);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 8, 2);
	glTexCoord2f(1, 1);
	glVertex3f(-2, 11, 1.5);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 11, -1.5);
	glTexCoord2f(0, 0);
	glVertex3f(-2, 8, -2);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 4, -2);
	glEnd();

	//right
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);
	glVertex3f(2, 4, 2);
	glTexCoord2f(1, 0);
	glVertex3f(2, 8, 2);
	glTexCoord2f(1, 1);
	glVertex3f(2, 11, 1.5);
	glTexCoord2f(0, 1);
	glVertex3f(2, 11, -1.5);
	glTexCoord2f(0, 0);
	glVertex3f(2, 8, -2);
	glTexCoord2f(1, 0);
	glVertex3f(2, 4, -2);
	glEnd();

#pragma endregion shield

#pragma region side
	glBindTexture(GL_TEXTURE_2D, textureMetalGrey);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, darkBlue);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, darkBlue);
	glColor3f(darkBlue[0], darkBlue[1], darkBlue[2]);
	glBegin(GL_QUADS);
	//left
	glTexCoord2f(0, 0);
	glVertex3f(2, 3.5, 1.5);
	glTexCoord2f(1, 0);
	glVertex3f(2, 9, 1.5);
	glTexCoord2f(1, 1);
	glVertex3f(2, 9, -1.5);
	glTexCoord2f(0, 1);
	glVertex3f(2, 3.5, -1.5);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(3.5, 4, 1.5);
	glTexCoord2f(1, 0);
	glVertex3f(3.5, 7.5, 1.5);
	glTexCoord2f(1, 1);
	glVertex3f(3.5, 7.5, -1.5);
	glTexCoord2f(0, 1);
	glVertex3f(3.5, 4, -1.5);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(2, 3.5, 1.5);
	glTexCoord2f(1, 0);
	glVertex3f(2, 9, 1.5);
	glTexCoord2f(1, 1);
	glVertex3f(3.5, 7.5, 1.5);
	glTexCoord2f(0, 1);
	glVertex3f(3.5, 4, 1.5);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(2, 3.5, -1.5);
	glTexCoord2f(1, 0);
	glVertex3f(2, 9, -1.5);
	glTexCoord2f(1, 1);
	glVertex3f(3.5, 7.5, -1.5);
	glTexCoord2f(0, 1);
	glVertex3f(3.5, 4, -1.5);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(2, 3.5, 1.5);
	glTexCoord2f(1, 0);
	glVertex3f(2, 3.5, -1.5);
	glTexCoord2f(1, 1);
	glVertex3f(3.5, 4, -1.5);
	glTexCoord2f(0, 1);
	glVertex3f(3.5, 4, 1.5);
	glEnd();

	//top
	glBegin(GL_QUADS);
	//front
	glTexCoord2f(0, 0);
	glVertex3f(2, 7, 1.75);
	glTexCoord2f(1, 0);
	glVertex3f(2, 10, 1.5);
	glTexCoord2f(1, 1);
	glVertex3f(4, 8, 1.75);
	glTexCoord2f(0, 1);
	glVertex3f(4, 7, 1.75);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(2, 7, -1.75);
	glTexCoord2f(1, 0);
	glVertex3f(2, 10, -1.5);
	glTexCoord2f(1, 1);
	glVertex3f(4, 8, -1.75);
	glTexCoord2f(0, 1);
	glVertex3f(4, 7, -1.75);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(2, 10, -1.5);
	glTexCoord2f(1, 0);
	glVertex3f(2, 10, 1.5);
	glTexCoord2f(1, 1);
	glVertex3f(4, 8, 1.75);
	glTexCoord2f(0, 1);
	glVertex3f(4, 8, -1.75);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(4, 7, -1.75);
	glTexCoord2f(1, 0);
	glVertex3f(4, 7, 1.75);
	glTexCoord2f(1, 1);
	glVertex3f(4, 8, 1.75);
	glTexCoord2f(0, 1);
	glVertex3f(4, 8, -1.75);
	glEnd();

	//-------------------------------------
	glBindTexture(GL_TEXTURE_2D, textureRedLamp);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, red);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, red);
	glColor3f(red[0], red[1], red[2]);
	glBegin(GL_POLYGON);
	//front
	glTexCoord2f(0, 0);
	glVertex3f(2, 4.5, 2.25);
	glTexCoord2f(1, 0);
	glVertex3f(2, 4, 2.25);
	glTexCoord2f(1, 1);
	glVertex3f(4, 4.5, 2.25);
	glTexCoord2f(0, 1);
	glVertex3f(4, 5.5, 2.25);
	glTexCoord2f(0, 0);
	glVertex3f(0, 5.5, 2.25);
	glTexCoord2f(1, 0);
	glVertex3f(0, 4.5, 2.25);
	glEnd();

	glBegin(GL_QUADS);
	//back
	glTexCoord2f(0, 0);
	glVertex3f(4, 4.5, 2.25);
	glTexCoord2f(1, 0);
	glVertex3f(4, 5.5, 2.25);
	glTexCoord2f(1, 1);
	glVertex3f(4, 5.5, -2.25);
	glTexCoord2f(0, 1);
	glVertex3f(4, 4.5, -2.25);
	glEnd();

	glBegin(GL_POLYGON);
	//right
	glTexCoord2f(0, 0);
	glVertex3f(2, 4.5, -2.25);
	glTexCoord2f(1, 0);
	glVertex3f(2, 4, -2.25);
	glTexCoord2f(1, 1);
	glVertex3f(4, 4.5, -2.25);
	glTexCoord2f(0, 1);
	glVertex3f(4, 5.5, -2.25);
	glTexCoord2f(0, 0);
	glVertex3f(0, 5.5, -2.25);
	glTexCoord2f(1, 0);
	glVertex3f(0, 4.5, -2.25);
	glEnd();

#pragma endregion side
	glPushMatrix();
	if (shieldOn) {
		if (shieldScale < 1) {
			shieldScale += 0.005;
		}
	}
	else {
		if (shieldScale > 0) {
			shieldScale -= 0.005;
		}
	}
	glScalef(shieldScale, shieldScale, shieldScale);
	glPushMatrix();
	glTranslatef(4, -10, 0);
	glRotatef(90, 0, 1, 0);

	if (turnShield) {
		glTranslatef(0, 15, 0);
		glRotatef(shieldAngle, 0, 0, 1);
		glTranslatef(0, -15, 0);
	}


	shield();

	glPopMatrix();
	glPopMatrix();
#pragma region join
	glBindTexture(GL_TEXTURE_2D, textureBlackCore);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, grey);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, grey);
	glColor3f(grey[0], grey[1], grey[2]);
	glBegin(GL_QUADS);
	//front
	glTexCoord2f(0, 0);
	glVertex3f(-1.25, 7.5, 1.5);
	glTexCoord2f(1, 0);
	glVertex3f(1.25, 7.5, 1.5);
	glTexCoord2f(1, 1);
	glVertex3f(1.25, 13, 1.5);
	glTexCoord2f(0, 1);
	glVertex3f(-1.25, 13, 1.5);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(-1.25, 7.5, -1.5);
	glTexCoord2f(1, 0);
	glVertex3f(1.25, 7.5, -1.5);
	glTexCoord2f(1, 1);
	glVertex3f(1.25, 13, -1.5);
	glTexCoord2f(0, 1);
	glVertex3f(-1.25, 13, -1.5);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-1.25, 7.5, -1.5);
	glTexCoord2f(1, 0);
	glVertex3f(-1.25, 7.5, 1.5);
	glTexCoord2f(1, 1);
	glVertex3f(-1.25, 13, 1.5);
	glTexCoord2f(0, 1);
	glVertex3f(-1.25, 13, -1.5);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(1.25, 7.5, -1.5);
	glTexCoord2f(1, 0);
	glVertex3f(1.25, 7.5, 1.5);
	glTexCoord2f(1, 1);
	glVertex3f(1.25, 13, 1.5);
	glTexCoord2f(0, 1);
	glVertex3f(1.25, 13, -1.5);
	glEnd();

#pragma endregion join
	glPopMatrix();
}

void leftUpperArm() {
	glPushMatrix();
#pragma region core
	glBindTexture(GL_TEXTURE_2D, textureMetalGrey);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, silver);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, silver);
	glColor3f(silver[0], silver[1], silver[2]);
	glBegin(GL_QUADS);
	//left front
	glTexCoord2f(0, 0);
	glVertex3f(1.25, 11.5, 1.75);
	glTexCoord2f(1, 0);
	glVertex3f(1.5, 11.5, 1.75);
	glTexCoord2f(1, 1);
	glVertex3f(1.5, 18, 1.75);
	glTexCoord2f(0, 1);
	glVertex3f(1.25, 18, 1.75);

	//middle front
	glTexCoord2f(0, 0);
	glVertex3f(-1.25, 12.5, 1.75);
	glTexCoord2f(1, 0);
	glVertex3f(1.25, 12.5, 1.75);
	glTexCoord2f(1, 1);
	glVertex3f(1.25, 18, 1.75);
	glTexCoord2f(0, 1);
	glVertex3f(-1.25, 18, 1.75);

	//right front
	glTexCoord2f(0, 0);
	glVertex3f(-1.25, 11.5, 1.75);
	glTexCoord2f(1, 0);
	glVertex3f(-1.5, 11.5, 1.75);
	glTexCoord2f(1, 1);
	glVertex3f(-1.5, 18, 1.75);
	glTexCoord2f(0, 1);
	glVertex3f(-1.25, 18, 1.75);

	//left back
	glTexCoord2f(0, 0);
	glVertex3f(1.25, 11.5, -1.75);
	glTexCoord2f(1, 0);
	glVertex3f(1.5, 11.5, -1.75);
	glTexCoord2f(1, 1);
	glVertex3f(1.5, 18, -1.75);
	glTexCoord2f(0, 1);
	glVertex3f(1.25, 18, -1.75);

	//middle back
	glTexCoord2f(0, 0);
	glVertex3f(-1.25, 12.5, -1.75);
	glTexCoord2f(1, 0);
	glVertex3f(1.25, 12.5, -1.75);
	glTexCoord2f(1, 1);
	glVertex3f(1.25, 18, -1.75);
	glTexCoord2f(0, 1);
	glVertex3f(-1.25, 18, -1.75);

	//right back
	glTexCoord2f(0, 0);
	glVertex3f(-1.25, 11.5, -1.75);
	glTexCoord2f(1, 0);
	glVertex3f(-1.5, 11.5, -1.75);
	glTexCoord2f(1, 1);
	glVertex3f(-1.5, 18, -1.75);
	glTexCoord2f(0, 1);
	glVertex3f(-1.25, 18, -1.75);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(1.5, 18, -1.75);
	glTexCoord2f(1, 0);
	glVertex3f(1.5, 18, 1.75);
	glTexCoord2f(1, 1);
	glVertex3f(1.5, 11.5, 1.75);
	glTexCoord2f(0, 1);
	glVertex3f(1.5, 11.5, -1.75);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(-1.5, 18, -1.75);
	glTexCoord2f(1, 0);
	glVertex3f(-1.5, 18, 1.75);
	glTexCoord2f(1, 1);
	glVertex3f(-1.5, 11.5, 1.75);
	glTexCoord2f(0, 1);
	glVertex3f(-1.5, 11.5, -1.75);
	glEnd();
#pragma endregion core
#pragma region join
	glBindTexture(GL_TEXTURE_2D, textureMetalBlueShine);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, darkBlue);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, darkBlue);
	glColor3f(darkBlue[0], darkBlue[1], darkBlue[2]);
	glBegin(GL_QUADS);
	//left
	glTexCoord2f(0, 0);
	glVertex3f(1.5, 21, -1.75);
	glTexCoord2f(1, 0);
	glVertex3f(1.5, 21, 1.75);
	glTexCoord2f(1, 1);
	glVertex3f(1.5, 18, 1.75);
	glTexCoord2f(0, 1);
	glVertex3f(1.5, 18, -1.75);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(-1.5, 21, -1.75);
	glTexCoord2f(1, 0);
	glVertex3f(-1.5, 21, 1.75);
	glTexCoord2f(1, 1);
	glVertex3f(-1.5, 18, 1.75);
	glTexCoord2f(0, 1);
	glVertex3f(-1.5, 18, -1.75);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(1.5, 21, 1.75);
	glTexCoord2f(1, 0);
	glVertex3f(-1.5, 21, 1.75);
	glTexCoord2f(1, 1);
	glVertex3f(-1.5, 18, 1.75);
	glTexCoord2f(0, 1);
	glVertex3f(1.5, 18, 1.75);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(1.5, 21, -1.75);
	glTexCoord2f(1, 0);
	glVertex3f(-1.5, 21, -1.75);
	glTexCoord2f(1, 1);
	glVertex3f(-1.5, 18, -1.75);
	glTexCoord2f(0, 1);
	glVertex3f(1.5, 18, -1.75);

	//-------------------------------------side part
	//right
	glTexCoord2f(0, 0);
	glVertex3f(2, 20, -1.25);
	glTexCoord2f(1, 0);
	glVertex3f(2, 20, 1.25);
	glTexCoord2f(1, 1);
	glVertex3f(2, 17, 1.25);
	glTexCoord2f(0, 1);
	glVertex3f(2, 17, -1.25);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(1.5, 20, -1.25);
	glTexCoord2f(1, 0);
	glVertex3f(1.5, 20, 1.25);
	glTexCoord2f(1, 1);
	glVertex3f(1.5, 18, 1.25);
	glTexCoord2f(0, 1);
	glVertex3f(1.5, 18, -1.25);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(1.5, 20, 1.25);
	glTexCoord2f(1, 0);
	glVertex3f(1.5, 18, 1.25);
	glTexCoord2f(1, 1);
	glVertex3f(2, 17, 1.25);
	glTexCoord2f(0, 1);
	glVertex3f(2, 20, 1.25);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(1.5, 20, -1.25);
	glTexCoord2f(1, 0);
	glVertex3f(1.5, 18, -1.25);
	glTexCoord2f(1, 1);
	glVertex3f(2, 17, -1.25);
	glTexCoord2f(0, 1);
	glVertex3f(2, 20, -1.25);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(1.5, 20, -1.25);
	glTexCoord2f(1, 0);
	glVertex3f(1.5, 20, 1.25);
	glTexCoord2f(1, 1);
	glVertex3f(2, 20, 1.25);
	glTexCoord2f(0, 1);
	glVertex3f(2, 20, -1.25);
	glEnd();
#pragma endregion join
#pragma region shield
	glBindTexture(GL_TEXTURE_2D, textureMetalBlueShine);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, indigo);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, indigo);
	glColor3f(indigo[0], indigo[1], indigo[2]);
	glBegin(GL_QUADS);
	//front
	glTexCoord2f(0, 0);
	glVertex3f(-3, 22, 2.25);
	glTexCoord2f(1, 0);
	glVertex3f(2, 22, 2.25);
	glTexCoord2f(1, 1);
	glVertex3f(2, 17, 2.25);
	glTexCoord2f(0, 1);
	glVertex3f(-3, 16, 2.25);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(-3, 22, -2.25);
	glTexCoord2f(1, 0);
	glVertex3f(2, 22, -2.25);
	glTexCoord2f(1, 1);
	glVertex3f(2, 17, -2.25);
	glTexCoord2f(0, 1);
	glVertex3f(-3, 16, -2.25);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-3, 22, -2.25);
	glTexCoord2f(1, 0);
	glVertex3f(2, 22, -2.25);
	glTexCoord2f(1, 1);
	glVertex3f(2, 22, 2.25);
	glTexCoord2f(0, 1);
	glVertex3f(-3, 22, 2.25);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(2, 22, 2.25);
	glTexCoord2f(1, 0);
	glVertex3f(2, 22, 1.75);
	glTexCoord2f(1, 1);
	glVertex3f(2, 17, 1.75);
	glTexCoord2f(0, 1);
	glVertex3f(2, 17, 2.25);

	glTexCoord2f(0, 0);
	glVertex3f(2, 22, -2.25);
	glTexCoord2f(1, 0);
	glVertex3f(2, 22, -1.75);
	glTexCoord2f(1, 1);
	glVertex3f(2, 17, -1.75);
	glTexCoord2f(0, 1);
	glVertex3f(2, 17, -2.25);

	glTexCoord2f(0, 0);
	glVertex3f(2, 22, 2.25);
	glTexCoord2f(1, 0);
	glVertex3f(2, 22, -2.25);
	glTexCoord2f(1, 1);
	glVertex3f(2, 21, -1.75);
	glTexCoord2f(0, 1);
	glVertex3f(2, 21, 1.75);
	glEnd();

	//--------------------------side part
	glBindTexture(GL_TEXTURE_2D, textureRedLamp);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, red);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, red);
	glColor3f(red[0], red[1], red[2]);
	glBegin(GL_QUADS);
	//front
	glTexCoord2f(0, 0);
	glVertex3f(2, 21, 1.75);
	glTexCoord2f(1, 0);
	glVertex3f(4, 21, 1.75);
	glTexCoord2f(1, 1);
	glVertex3f(4, 19, 1.75);
	glTexCoord2f(0, 1);
	glVertex3f(2, 18, 1.75);

	glTexCoord2f(0, 0);
	glVertex3f(2, 21, 1.25);
	glTexCoord2f(1, 0);
	glVertex3f(4, 21, 1.25);
	glTexCoord2f(1, 1);
	glVertex3f(4, 19, 1.25);
	glTexCoord2f(0, 1);
	glVertex3f(2, 18, 1.25);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(2, 21, -1.75);
	glTexCoord2f(1, 0);
	glVertex3f(4, 21, -1.75);
	glTexCoord2f(1, 1);
	glVertex3f(4, 19, -1.75);
	glTexCoord2f(0, 1);
	glVertex3f(2, 18, -1.75);

	glTexCoord2f(0, 0);
	glVertex3f(2, 21, -1.25);
	glTexCoord2f(1, 0);
	glVertex3f(4, 21, -1.25);
	glTexCoord2f(1, 1);
	glVertex3f(4, 19, -1.25);
	glTexCoord2f(0, 1);
	glVertex3f(2, 18, -1.25);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(2, 21, 1.75);
	glTexCoord2f(1, 0);
	glVertex3f(4, 21, 1.75);
	glTexCoord2f(1, 1);
	glVertex3f(4, 21, -1.75);
	glTexCoord2f(0, 1);
	glVertex3f(2, 21, -1.75);

	glTexCoord2f(0, 0);
	glVertex3f(2, 20.5, 1.75);
	glTexCoord2f(1, 0);
	glVertex3f(4, 20.5, 1.75);
	glTexCoord2f(1, 1);
	glVertex3f(4, 20.5, -1.75);
	glTexCoord2f(0, 1);
	glVertex3f(2, 20.5, -1.75);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(4, 21, 1.75);
	glTexCoord2f(1, 0);
	glVertex3f(4, 21, 1.25);
	glTexCoord2f(1, 1);
	glVertex3f(4, 19, 1.25);
	glTexCoord2f(0, 1);
	glVertex3f(4, 19, 1.75);

	glTexCoord2f(0, 0);
	glVertex3f(4, 19, 1.25);
	glTexCoord2f(1, 0);
	glVertex3f(4, 19, 1.75);
	glTexCoord2f(1, 1);
	glVertex3f(2, 18, 1.75);
	glTexCoord2f(0, 1);
	glVertex3f(2, 18, 1.25);

	glTexCoord2f(0, 0);
	glVertex3f(4, 21, -1.75);
	glTexCoord2f(1, 0);
	glVertex3f(4, 21, -1.25);
	glTexCoord2f(1, 1);
	glVertex3f(4, 19, -1.25);
	glTexCoord2f(0, 1);
	glVertex3f(4, 19, -1.75);

	glTexCoord2f(0, 0);
	glVertex3f(4, 19, -1.25);
	glTexCoord2f(1, 0);
	glVertex3f(4, 19, -1.75);
	glTexCoord2f(1, 1);
	glVertex3f(2, 18, -1.75);
	glTexCoord2f(0, 1);
	glVertex3f(2, 18, -1.25);

	glTexCoord2f(0, 0);
	glVertex3f(4, 21, 1.25);
	glTexCoord2f(1, 0);
	glVertex3f(4, 21, -1.75);
	glTexCoord2f(1, 1);
	glVertex3f(4, 20.5, -1.75);
	glTexCoord2f(0, 1);
	glVertex3f(4, 20.5, 1.25);
	glEnd();

	//-----------------------------front left part
	glBindTexture(GL_TEXTURE_2D, textureMetalGrey);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, darkBlue);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, darkBlue);
	glColor3f(darkBlue[0], darkBlue[1], darkBlue[2]);
	glBegin(GL_QUADS);
	//front
	glTexCoord2f(0, 0);
	glVertex3f(-3, 23, 2.75);
	glTexCoord2f(1, 0);
	glVertex3f(-1.25, 23, 2.75);
	glTexCoord2f(1, 1);
	glVertex3f(-1.25, 19.5, 2.75);
	glTexCoord2f(0, 1);
	glVertex3f(-3, 19, 2.75);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(-3, 23, -2.75);
	glTexCoord2f(1, 0);
	glVertex3f(-1.25, 23, -2.75);
	glTexCoord2f(1, 1);
	glVertex3f(-1.25, 19.5, -2.75);
	glTexCoord2f(0, 1);
	glVertex3f(-3, 19, -2.75);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-3, 23, 2.75);
	glTexCoord2f(1, 0);
	glVertex3f(-1.25, 23, 2.75);
	glTexCoord2f(1, 1);
	glVertex3f(-1.25, 23, -2.75);
	glTexCoord2f(0, 1);
	glVertex3f(-3, 23, -2.75);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-3, 23, 2.75);
	glTexCoord2f(1, 0);
	glVertex3f(-3, 23, -2.75);
	glTexCoord2f(1, 1);
	glVertex3f(-3, 19, -2.75);
	glTexCoord2f(0, 1);
	glVertex3f(-3, 19, 2.75);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(-1.25, 23, 2.75);
	glTexCoord2f(1, 0);
	glVertex3f(-1.25, 23, -2.75);
	glTexCoord2f(1, 1);
	glVertex3f(-1.25, 19.5, -2.75);
	glTexCoord2f(0, 1);
	glVertex3f(-1.25, 19.5, 2.75);

	//-----------------------------front right part
	//front
	glTexCoord2f(0, 0);
	glVertex3f(0.25, 23, 2.75);
	glTexCoord2f(1, 0);
	glVertex3f(2, 23, 2.75);
	glTexCoord2f(1, 1);
	glVertex3f(2, 19.5, 2.75);
	glTexCoord2f(0, 1);
	glVertex3f(0.25, 19.5, 2.75);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(0.25, 23, -2.75);
	glTexCoord2f(1, 0);
	glVertex3f(2, 23, -2.75);
	glTexCoord2f(1, 1);
	glVertex3f(2, 19.5, -2.75);
	glTexCoord2f(0, 1);
	glVertex3f(0.25, 19.5, -2.75);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(2, 23, 2.75);
	glTexCoord2f(1, 0);
	glVertex3f(0.25, 23, 2.75);
	glTexCoord2f(1, 1);
	glVertex3f(0.25, 23, -2.75);
	glTexCoord2f(0, 1);
	glVertex3f(2, 23, -2.75);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(0.25, 23, 2.75);
	glTexCoord2f(1, 0);
	glVertex3f(0.25, 23, -2.75);
	glTexCoord2f(1, 1);
	glVertex3f(0.25, 19.5, -2.75);
	glTexCoord2f(0, 1);
	glVertex3f(0.25, 19.5, 2.75);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(2, 23, 2.75);
	glTexCoord2f(1, 0);
	glVertex3f(2, 23, 2.25);
	glTexCoord2f(1, 1);
	glVertex3f(2, 19.5, 2.25);
	glTexCoord2f(0, 1);
	glVertex3f(2, 19.5, 2.75);

	glTexCoord2f(0, 0);
	glVertex3f(2, 23, -2.75);
	glTexCoord2f(1, 0);
	glVertex3f(2, 23, -2.25);
	glTexCoord2f(1, 1);
	glVertex3f(2, 19.5, -2.25);
	glTexCoord2f(0, 1);
	glVertex3f(2, 19.5, -2.75);

	glTexCoord2f(0, 0);
	glVertex3f(2, 23, 2.75);
	glTexCoord2f(1, 0);
	glVertex3f(2, 22.5, 2.25);
	glTexCoord2f(1, 1);
	glVertex3f(2, 22.5, -2.25);
	glTexCoord2f(0, 1);
	glVertex3f(2, 23, -2.75);
	glEnd();
#pragma endregion shield
	glPopMatrix();
}

void rightHand() {
	glPushMatrix();
#pragma region hand
	glBindTexture(GL_TEXTURE_2D, textureMetalGrey);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, silver);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, silver);
	glColor3f(silver[0], silver[1], silver[2]);
	//----------------------------------right plam
	glBegin(GL_QUADS);
	//front
	glTexCoord2f(0, 0);
	glVertex3f(0.5, 0, 2);
	glTexCoord2f(1, 0);
	glVertex3f(-0.5, 0, 2);
	glTexCoord2f(1, 1);
	glVertex3f(-1, 3, 2);
	glTexCoord2f(0, 1);
	glVertex3f(0.5, 4, 2);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(0.5, 0, -2);
	glTexCoord2f(1, 0);
	glVertex3f(-0.5, 0, -2);
	glTexCoord2f(1, 1);
	glVertex3f(-1, 3, -2);
	glTexCoord2f(0, 1);
	glVertex3f(0.5, 4, -2);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(-0.5, 0, 2);
	glTexCoord2f(1, 0);
	glVertex3f(-0.5, 0, -2);
	glTexCoord2f(1, 1);
	glVertex3f(-1, 3, -2);
	glTexCoord2f(0, 1);
	glVertex3f(-1, 3, 2);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(0.5, 0, 2);
	glTexCoord2f(1, 0);
	glVertex3f(0.5, 0, -2);
	glTexCoord2f(1, 1);
	glVertex3f(0.5, 4, -2);
	glTexCoord2f(0, 1);
	glVertex3f(0.5, 4, 2);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(0.5, 4, -2);
	glTexCoord2f(1, 0);
	glVertex3f(0.5, 4, 2);
	glTexCoord2f(1, 1);
	glVertex3f(-1, 3, 2);
	glTexCoord2f(0, 1);
	glVertex3f(-1, 3, -2);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(0.5, 0, -2);
	glTexCoord2f(1, 0);
	glVertex3f(0.5, 0, 2);
	glTexCoord2f(1, 1);
	glVertex3f(-0.5, 0, 2);
	glTexCoord2f(0, 1);
	glVertex3f(-0.5, 0, -2);

	//-------------------------------------finger
	//front 1
	glTexCoord2f(0, 0);
	glVertex3f(0.5, 0, 2);
	glTexCoord2f(1, 0);
	glVertex3f(1.75, 0, 2);
	glTexCoord2f(1, 1);
	glVertex3f(1.5, 1, 2);
	glTexCoord2f(0, 1);
	glVertex3f(0.5, 1, 2);

	glTexCoord2f(0, 0);
	glVertex3f(1.75, 0, 2);
	glTexCoord2f(1, 0);
	glVertex3f(1.25, 1, 2);
	glTexCoord2f(1, 1);
	glVertex3f(1.5, 2, 2);
	glTexCoord2f(0, 1);
	glVertex3f(2.25, 2.25, 2);

	glTexCoord2f(0, 0);
	glVertex3f(1.5, 1.5, 2);
	glTexCoord2f(1, 0);
	glVertex3f(2.25, 2.25, 2);
	glTexCoord2f(1, 1);
	glVertex3f(0.5, 2.25, 2);
	glTexCoord2f(0, 1);
	glVertex3f(0.5, 1.5, 2);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(1.75, 0, 2);
	glTexCoord2f(1, 0);
	glVertex3f(2.25, 2.25, 2);
	glTexCoord2f(1, 1);
	glVertex3f(2.25, 2.25, 1);
	glTexCoord2f(0, 1);
	glVertex3f(1.75, 0, 1);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(2.25, 2.25, 2);
	glTexCoord2f(1, 0);
	glVertex3f(0.5, 2.25, 2);
	glTexCoord2f(1, 1);
	glVertex3f(0.5, 2.25, 1);
	glTexCoord2f(0, 1);
	glVertex3f(2.25, 2.25, 1);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(0.5, 0, 2);
	glTexCoord2f(1, 0);
	glVertex3f(1.75, 0, 2);
	glTexCoord2f(1, 1);
	glVertex3f(1.75, 0, 1);
	glTexCoord2f(0, 1);
	glVertex3f(0.5, 0, 1);

	//front 2
	glTexCoord2f(0, 0);
	glVertex3f(0.5, 0, 1);
	glTexCoord2f(1, 0);
	glVertex3f(1.75, 0, 1);
	glTexCoord2f(1, 1);
	glVertex3f(1.5, 1, 1);
	glTexCoord2f(0, 1);
	glVertex3f(0.5, 1, 1);

	glTexCoord2f(0, 0);
	glVertex3f(1.75, 0, 1);
	glTexCoord2f(1, 0);
	glVertex3f(1.25, 1, 1);
	glTexCoord2f(1, 1);
	glVertex3f(1.5, 2, 1);
	glTexCoord2f(0, 1);
	glVertex3f(2.25, 2.25, 1);

	glTexCoord2f(0, 0);
	glVertex3f(1.5, 1.5, 1);
	glTexCoord2f(1, 0);
	glVertex3f(2.25, 2.25, 1);
	glTexCoord2f(1, 1);
	glVertex3f(0.5, 2.25, 1);
	glTexCoord2f(0, 1);
	glVertex3f(0.5, 1.5, 1);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(1.75, 0, 1);
	glTexCoord2f(1, 0);
	glVertex3f(2.25, 2.25, 1);
	glTexCoord2f(1, 1);
	glVertex3f(2.25, 2.25, 0);
	glTexCoord2f(0, 1);
	glVertex3f(1.75, 0, 0);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(2.25, 2.25, 1);
	glTexCoord2f(1, 0);
	glVertex3f(0.5, 2.25, 1);
	glTexCoord2f(1, 1);
	glVertex3f(0.5, 2.25, 0);
	glTexCoord2f(0, 1);
	glVertex3f(2.25, 2.25, 0);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(0.5, 0, 1);
	glTexCoord2f(1, 0);
	glVertex3f(1.75, 0, 1);
	glTexCoord2f(1, 1);
	glVertex3f(1.75, 0, 0);
	glTexCoord2f(0, 1);
	glVertex3f(0.5, 0, 0);

	//front 3
	glTexCoord2f(0, 0);
	glVertex3f(0.5, 0, 0);
	glTexCoord2f(1, 0);
	glVertex3f(1.75, 0, 0);
	glTexCoord2f(1, 1);
	glVertex3f(1.5, 1, 0);
	glTexCoord2f(0, 1);
	glVertex3f(0.5, 1, 0);

	glTexCoord2f(0, 0);
	glVertex3f(1.75, 0, 0);
	glTexCoord2f(1, 0);
	glVertex3f(1.25, 1, 0);
	glTexCoord2f(1, 1);
	glVertex3f(1.5, 2, 0);
	glTexCoord2f(0, 1);
	glVertex3f(2.25, 2.25, 0);

	glTexCoord2f(0, 0);
	glVertex3f(1.5, 1.5, 0);
	glTexCoord2f(1, 0);
	glVertex3f(2.25, 2.25, 0);
	glTexCoord2f(1, 1);
	glVertex3f(0.5, 2.25, 0);
	glTexCoord2f(0, 1);
	glVertex3f(0.5, 1.5, 0);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(1.75, 0, 0);
	glTexCoord2f(1, 0);
	glVertex3f(2.25, 2.25, 0);
	glTexCoord2f(1, 1);
	glVertex3f(2.25, 2.25, -1);
	glTexCoord2f(0, 1);
	glVertex3f(1.75, 0, -1);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(2.25, 2.25, 0);
	glTexCoord2f(1, 0);
	glVertex3f(0.5, 2.25, 0);
	glTexCoord2f(1, 1);
	glVertex3f(0.5, 2.25, -1);
	glTexCoord2f(0, 1);
	glVertex3f(2.25, 2.25, -1);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(0.5, 0, 0);
	glTexCoord2f(1, 0);
	glVertex3f(1.75, 0, 0);
	glTexCoord2f(1, 1);
	glVertex3f(1.75, 0, -1);
	glTexCoord2f(0, 1);
	glVertex3f(0.5, 0, -1);

	//front 4
	glTexCoord2f(0, 0);
	glVertex3f(0.5, 0, -1);
	glTexCoord2f(1, 0);
	glVertex3f(1.75, 0, -1);
	glTexCoord2f(1, 1);
	glVertex3f(1.5, 1, -1);
	glTexCoord2f(0, 1);
	glVertex3f(0.5, 1, -1);

	glTexCoord2f(0, 0);
	glVertex3f(1.75, 0, -1);
	glTexCoord2f(1, 0);
	glVertex3f(1.25, 1, -1);
	glTexCoord2f(1, 1);
	glVertex3f(1.5, 2, -1);
	glTexCoord2f(0, 1);
	glVertex3f(2.25, 2.25, -1);

	glTexCoord2f(0, 0);
	glVertex3f(1.5, 1.5, -1);
	glTexCoord2f(1, 0);
	glVertex3f(2.25, 2.25, -1);
	glTexCoord2f(1, 1);
	glVertex3f(0.5, 2.25, -1);
	glTexCoord2f(0, 1);
	glVertex3f(0.5, 1.5, -1);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(1.75, 0, -1);
	glTexCoord2f(1, 0);
	glVertex3f(2.25, 2.25, -1);
	glTexCoord2f(1, 1);
	glVertex3f(2.25, 2.25, -2);
	glTexCoord2f(0, 1);
	glVertex3f(1.75, 0, -2);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(2.25, 2.25, -1);
	glTexCoord2f(1, 0);
	glVertex3f(0.5, 2.25, -1);
	glTexCoord2f(1, 1);
	glVertex3f(0.5, 2.25, -2);
	glTexCoord2f(0, 1);
	glVertex3f(2.25, 2.25, -2);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(0.5, 0, -1);
	glTexCoord2f(1, 0);
	glVertex3f(1.75, 0, -1);
	glTexCoord2f(1, 1);
	glVertex3f(1.75, 0, -2);
	glTexCoord2f(0, 1);
	glVertex3f(0.5, 0, -2);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(0.5, 0, -2);
	glTexCoord2f(1, 0);
	glVertex3f(1.75, 0, -2);
	glTexCoord2f(1, 1);
	glVertex3f(1.5, 1, -2);
	glTexCoord2f(0, 1);
	glVertex3f(0.5, 1, -2);

	glTexCoord2f(0, 0);
	glVertex3f(1.75, 0, -2);
	glTexCoord2f(1, 0);
	glVertex3f(1.25, 1, -2);
	glTexCoord2f(1, 1);
	glVertex3f(1.5, 2, -2);
	glTexCoord2f(0, 1);
	glVertex3f(2.25, 2.25, -2);

	glTexCoord2f(0, 0);
	glVertex3f(1.5, 1.5, -2);
	glTexCoord2f(1, 0);
	glVertex3f(2.25, 2.25, -2);
	glTexCoord2f(1, 1);
	glVertex3f(0.5, 2.25, -2);
	glTexCoord2f(0, 1);
	glVertex3f(0.5, 1.5, -2);

	//------------------------------------thumb
	//back
	glTexCoord2f(0, 0);
	glVertex3f(0.5, 4, 2);
	glTexCoord2f(1, 0);
	glVertex3f(0.5, 2, 2);
	glTexCoord2f(1, 1);
	glVertex3f(1.5, 1.5, 2);
	glTexCoord2f(0, 1);
	glVertex3f(2, 2, 2);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(0.5, 4, 3);
	glTexCoord2f(1, 0);
	glVertex3f(0.5, 2, 3);
	glTexCoord2f(1, 1);
	glVertex3f(1.5, 1.5, 3);
	glTexCoord2f(0, 1);
	glVertex3f(2, 2, 3);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(0.5, 4, 3);
	glTexCoord2f(1, 0);
	glVertex3f(0.5, 2, 3);
	glTexCoord2f(1, 1);
	glVertex3f(0.5, 2, 2);
	glTexCoord2f(0, 1);
	glVertex3f(0.5, 4, 2);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(0.5, 2, 3);
	glTexCoord2f(1, 0);
	glVertex3f(1.5, 1.5, 3);
	glTexCoord2f(1, 1);
	glVertex3f(1.5, 1.5, 2);
	glTexCoord2f(0, 1);
	glVertex3f(0.5, 2, 2);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(0.5, 4, 3);
	glTexCoord2f(1, 0);
	glVertex3f(2, 2, 3);
	glTexCoord2f(1, 1);
	glVertex3f(2, 2, 2);
	glTexCoord2f(0, 1);
	glVertex3f(0.5, 4, 2);

	//layer2
	//front
	glTexCoord2f(0, 0);
	glVertex3f(1.5, 1.5, 3);
	glTexCoord2f(1, 0);
	glVertex3f(2.5, 2, 1.5);
	glTexCoord2f(1, 1);
	glVertex3f(2.5, 3, 1.5);
	glTexCoord2f(0, 1);
	glVertex3f(1, 2.5, 3);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(2.5, 3, 1.5);
	glTexCoord2f(1, 0);
	glVertex3f(1, 2.5, 3);
	glTexCoord2f(1, 1);
	glVertex3f(0.5, 2.5, 3);
	glTexCoord2f(0, 1);
	glVertex3f(1.5, 3, 1.75);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(1.5, 1.5, 3);
	glTexCoord2f(1, 0);
	glVertex3f(2.5, 2, 1.5);
	glTexCoord2f(1, 1);
	glVertex3f(0.5, 2, 3);
	glTexCoord2f(0, 1);
	glVertex3f(1.5, 2, 1.75);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(2.5, 3, 1.5);
	glTexCoord2f(1, 0);
	glVertex3f(1.5, 3, 1.75);
	glTexCoord2f(1, 1);
	glVertex3f(1.5, 2, 1.75);
	glTexCoord2f(0, 1);
	glVertex3f(1.5, 1.5, 3);

	//layer3
	//front
	glTexCoord2f(0, 0);
	glVertex3f(2, 3, -1);
	glTexCoord2f(1, 0);
	glVertex3f(2, 2, -1);
	glTexCoord2f(1, 1);
	glVertex3f(2.5, 2, 1.5);
	glTexCoord2f(0, 1);
	glVertex3f(2.5, 3, 1.5);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(2, 3, -1);
	glTexCoord2f(1, 0);
	glVertex3f(1, 3, -1);
	glTexCoord2f(1, 1);
	glVertex3f(1, 2.5, 3);
	glTexCoord2f(0, 1);
	glVertex3f(2.5, 3, 1.5);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(1, 2, -1);
	glTexCoord2f(1, 0);
	glVertex3f(2, 2, -1);
	glTexCoord2f(1, 1);
	glVertex3f(2.5, 2, 1.5);
	glTexCoord2f(0, 1);
	glVertex3f(1.5, 1.5, 3);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(2, 3, -1);
	glTexCoord2f(1, 0);
	glVertex3f(1, 3, -1);
	glTexCoord2f(1, 1);
	glVertex3f(1, 2, -1);
	glTexCoord2f(0, 1);
	glVertex3f(2, 2, -1);
	glEnd();

#pragma endregion hand
	glPopMatrix();
}

void rightLowerArm() {
	glColor3f(1, 1, 1);
	glPushMatrix();
#pragma region core
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, textureMetalGrey);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, grey);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, grey);
	glColor3f(grey[0], grey[1], grey[2]);
	glTranslatef(0, 4, 0);
	gluQuadricTexture(obj, true);
	gluSphere(obj, 1, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 4, 0);
	glRotatef(-90, 1, 0, 0);
	gluQuadricTexture(obj, true);
	gluCylinder(obj, 1.5, 1.5, 6, 10, 10);
	glPopMatrix();
#pragma endregion core
#pragma region shield
	//front
	glBindTexture(GL_TEXTURE_2D, textureMetalBlueShine);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, indigo);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, indigo);
	glColor3f(indigo[0], indigo[1], indigo[2]);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);
	glVertex3f(2, 4, 2);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 4, 2);
	glTexCoord2f(1, 1);
	glVertex3f(-2, 8, 2);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 11, 1.5);
	glTexCoord2f(0, 0);
	glVertex3f(-1.5, 11, 1.5);
	glTexCoord2f(1, 0);
	glVertex3f(-0.75, 8, 2);
	glTexCoord2f(1, 1);
	glVertex3f(0.75, 8, 2);
	glTexCoord2f(0, 1);
	glVertex3f(1.5, 11, 1.5);
	glTexCoord2f(0, 0);
	glVertex3f(2, 11, 1.5);
	glTexCoord2f(1, 0);
	glVertex3f(2, 8, 2);
	glEnd();

	//back
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);
	glVertex3f(2, 4, -2);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 4, -2);
	glTexCoord2f(1, 1);
	glVertex3f(-2, 8, -2);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 11, -1.5);
	glTexCoord2f(0, 0);
	glVertex3f(-1.5, 11, -1.5);
	glTexCoord2f(1, 0);
	glVertex3f(-0.75, 8, -2);
	glTexCoord2f(1, 1);
	glVertex3f(0.75, 8, -2);
	glTexCoord2f(0, 1);
	glVertex3f(1.5, 11, -1.5);
	glTexCoord2f(0, 0);
	glVertex3f(2, 11, -1.5);
	glTexCoord2f(1, 0);
	glVertex3f(2, 8, -2);
	glEnd();

	//left
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);
	glVertex3f(2, 4, 2);
	glTexCoord2f(1, 0);
	glVertex3f(2, 8, 2);
	glTexCoord2f(1, 1);
	glVertex3f(2, 11, 1.5);
	glTexCoord2f(0, 1);
	glVertex3f(2, 11, -1.5);
	glTexCoord2f(0, 0);
	glVertex3f(2, 8, -2);
	glTexCoord2f(1, 0);
	glVertex3f(2, 4, -2);
	glEnd();

	//right
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);
	glVertex3f(-2, 4, 2);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 8, 2);
	glTexCoord2f(1, 1);
	glVertex3f(-2, 11, 1.5);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 11, -1.5);
	glTexCoord2f(0, 0);
	glVertex3f(-2, 8, -2);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 4, -2);
	glEnd();

#pragma endregion shield
#pragma region side
	glPushMatrix();
	if (gunOn) {
		glTranslatef(-1, 0, 0);
		if (gunScale < 1) {
			gunScale += 0.005;
		}
	}
	else {
		glTranslatef(0, 0, 0);
		if (gunScale > 0) {
			gunScale -= 0.005;
		}
	}
	glBindTexture(GL_TEXTURE_2D, textureMetalGrey);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, darkBlue);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, darkBlue);
	glColor3f(darkBlue[0], darkBlue[1], darkBlue[2]);
	glBegin(GL_QUADS);
	//left
	glTexCoord2f(0, 0);
	glVertex3f(-2, 3.5, 1.5);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 9, 1.5);
	glTexCoord2f(1, 1);
	glVertex3f(-2, 9, -1.5);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 3.5, -1.5);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(-3.5, 4, 1.5);
	glTexCoord2f(1, 0);
	glVertex3f(-3.5, 7.5, 1.5);
	glTexCoord2f(1, 1);
	glVertex3f(-3.5, 7.5, -1.5);
	glTexCoord2f(0, 1);
	glVertex3f(-3.5, 4, -1.5);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(-2, 3.5, 1.5);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 9, 1.5);
	glTexCoord2f(1, 1);
	glVertex3f(-3.5, 7.5, 1.5);
	glTexCoord2f(0, 1);
	glVertex3f(-3.5, 4, 1.5);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(-2, 3.5, -1.5);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 9, -1.5);
	glTexCoord2f(1, 1);
	glVertex3f(-3.5, 7.5, -1.5);
	glTexCoord2f(0, 1);
	glVertex3f(-3.5, 4, -1.5);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-2, 3.5, 1.5);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 3.5, -1.5);
	glTexCoord2f(1, 1);
	glVertex3f(-3.5, 4, -1.5);
	glTexCoord2f(0, 1);
	glVertex3f(-3.5, 4, 1.5);
	glEnd();

	//top
	glBegin(GL_QUADS);
	//front
	glTexCoord2f(0, 0);
	glVertex3f(-2, 7, 1.75);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 10, 1.5);
	glTexCoord2f(1, 1);
	glVertex3f(-4, 8, 1.75);
	glTexCoord2f(0, 1);
	glVertex3f(-4, 7, 1.75);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(-2, 7, -1.75);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 10, -1.5);
	glTexCoord2f(1, 1);
	glVertex3f(-4, 8, -1.75);
	glTexCoord2f(0, 1);
	glVertex3f(-4, 7, -1.75);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-2, 10, -1.5);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 10, 1.5);
	glTexCoord2f(1, 1);
	glVertex3f(-4, 8, 1.75);
	glTexCoord2f(0, 1);
	glVertex3f(-4, 8, -1.75);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(-4, 7, -1.75);
	glTexCoord2f(1, 0);
	glVertex3f(-4, 7, 1.75);
	glTexCoord2f(1, 1);
	glVertex3f(-4, 8, 1.75);
	glTexCoord2f(0, 1);
	glVertex3f(-4, 8, -1.75);

	//---------------------------------------------gun
	//---------------------------------------------up scale
	//top
	glTexCoord2f(0, 0);
	glVertex3f(0, 10, -1.25);
	glTexCoord2f(1, 0);
	glVertex3f(0, 10, 1.25);
	glTexCoord2f(1, 1);
	glVertex3f(-2, 10, 1.5);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 10, -1.5);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(0, 7, 1.25);
	glTexCoord2f(1, 0);
	glVertex3f(0, 10, 1.25);
	glTexCoord2f(1, 1);
	glVertex3f(-2, 10, 1.25);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 7, 1.25);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(0, 7, -1.25);
	glTexCoord2f(1, 0);
	glVertex3f(0, 10, -1.25);
	glTexCoord2f(1, 1);
	glVertex3f(-2, 10, -1.25);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 7, -1.25);
	glEnd();

	//---------------------------------------------gun core
	glPushMatrix();
	glScalef(gunScale, gunScale, gunScale);
	glBindTexture(GL_TEXTURE_2D, textureWhiteMetal);
	glPushMatrix();
	glTranslatef(-1.5, 9, -0.5);
	glRotatef(90, 1, 0, 0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, silver);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, silver);
	glColor3f(silver[0], silver[1], silver[2]);
	gluCylinder(obj, 0.5, 0.5, 15, 10, 10);

	if (onLaser) {
		glLineWidth(0.1);
		glBegin(GL_LINES);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, red);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, red);
		glColor3f(1, 0, 0);
		glVertex3f(0, 0.5, 2);
		glVertex3f(0, 0.5, 30);
		glEnd();
	}

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, silver);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, silver);
	glColor3f(silver[0], silver[1], silver[2]);
	glTranslatef(0, 0, bulletTranslate);
	gluSphere(obj, 0.25, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.5, 9, 0.5);
	glRotatef(90, 1, 0, 0);
	gluCylinder(obj, 0.5, 0.5, 15, 10, 10);
	glTranslatef(0, 0, bulletTranslate);
	gluSphere(obj, 0.25, 10, 10);
	glPopMatrix();
	glPopMatrix();

	//---------------------------------------------down scale
	glBindTexture(GL_TEXTURE_2D, textureRedLamp);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, red);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, red);
	glColor3f(red[0], red[1], red[2]);
	glBegin(GL_POLYGON);
	//front
	glTexCoord2f(0, 0);
	glVertex3f(-2, 4.5, 2.25);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 4, 2.25);
	glTexCoord2f(1, 1);
	glVertex3f(-4, 4.5, 2.25);
	glTexCoord2f(0, 1);
	glVertex3f(-4, 5.5, 2.25);
	glTexCoord2f(0, 0);
	glVertex3f(-0, 5.5, 2.25);
	glTexCoord2f(1, 0);
	glVertex3f(-0, 4.5, 2.25);
	glEnd();

	glBegin(GL_QUADS);
	//back
	glTexCoord2f(0, 0);
	glVertex3f(-4, 4.5, 2.25);
	glTexCoord2f(1, 0);
	glVertex3f(-4, 5.5, 2.25);
	glTexCoord2f(1, 1);
	glVertex3f(-4, 5.5, -2.25);
	glTexCoord2f(0, 1);
	glVertex3f(-4, 4.5, -2.25);
	glEnd();

	glBegin(GL_POLYGON);
	//right
	glTexCoord2f(0, 0);
	glVertex3f(-2, 4.5, -2.25);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 4, -2.25);
	glTexCoord2f(1, 1);
	glVertex3f(-4, 4.5, -2.25);
	glTexCoord2f(0, 1);
	glVertex3f(-4, 5.5, -2.25);
	glTexCoord2f(0, 0);
	glVertex3f(-0, 5.5, -2.25);
	glTexCoord2f(1, 0);
	glVertex3f(-0, 4.5, -2.25);
	glEnd();

	glPopMatrix();
#pragma endregion side
#pragma region join
	glBindTexture(GL_TEXTURE_2D, textureBlackCore);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, grey);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, grey);
	glColor3f(grey[0], grey[1], grey[2]);
	glBegin(GL_QUADS);
	//front
	glTexCoord2f(0, 0);
	glVertex3f(1.25, 7.5, 1.5);
	glTexCoord2f(1, 0);
	glVertex3f(-1.25, 7.5, 1.5);
	glTexCoord2f(1, 1);
	glVertex3f(-1.25, 13, 1.5);
	glTexCoord2f(0, 1);
	glVertex3f(1.25, 13, 1.5);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(1.25, 7.5, -1.5);
	glTexCoord2f(1, 0);
	glVertex3f(-1.25, 7.5, -1.5);
	glTexCoord2f(1, 1);
	glVertex3f(-1.25, 13, -1.5);
	glTexCoord2f(0, 1);
	glVertex3f(1.25, 13, -1.5);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(1.25, 7.5, -1.5);
	glTexCoord2f(1, 0);
	glVertex3f(1.25, 7.5, 1.5);
	glTexCoord2f(1, 1);
	glVertex3f(1.25, 13, 1.5);
	glTexCoord2f(0, 1);
	glVertex3f(1.25, 13, -1.5);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(-1.25, 7.5, -1.5);
	glTexCoord2f(1, 0);
	glVertex3f(-1.25, 7.5, 1.5);
	glTexCoord2f(1, 1);
	glVertex3f(-1.25, 13, 1.5);
	glTexCoord2f(0, 1);
	glVertex3f(-1.25, 13, -1.5);
	glEnd();

#pragma endregion join
	glPopMatrix();
}

void rightUpperArm() {
	glPushMatrix();
#pragma region core
	glBindTexture(GL_TEXTURE_2D, textureMetalGrey);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, silver);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, silver);
	glColor3f(silver[0], silver[1], silver[2]);
	glBegin(GL_QUADS);
	//left front
	glTexCoord2f(0, 0);
	glVertex3f(-1.25, 11.5, 1.75);
	glTexCoord2f(1, 0);
	glVertex3f(-1.5, 11.5, 1.75);
	glTexCoord2f(1, 1);
	glVertex3f(-1.5, 18, 1.75);
	glTexCoord2f(0, 1);
	glVertex3f(-1.25, 18, 1.75);

	//middle front
	glTexCoord2f(0, 0);
	glVertex3f(1.25, 12.5, 1.75);
	glTexCoord2f(1, 0);
	glVertex3f(-1.25, 12.5, 1.75);
	glTexCoord2f(1, 1);
	glVertex3f(-1.25, 18, 1.75);
	glTexCoord2f(0, 1);
	glVertex3f(1.25, 18, 1.75);

	//right front
	glTexCoord2f(0, 0);
	glVertex3f(1.25, 11.5, 1.75);
	glTexCoord2f(1, 0);
	glVertex3f(1.5, 11.5, 1.75);
	glTexCoord2f(1, 1);
	glVertex3f(1.5, 18, 1.75);
	glTexCoord2f(0, 1);
	glVertex3f(1.25, 18, 1.75);

	//left back
	glTexCoord2f(0, 0);
	glVertex3f(-1.25, 11.5, -1.75);
	glTexCoord2f(1, 0);
	glVertex3f(-1.5, 11.5, -1.75);
	glTexCoord2f(1, 1);
	glVertex3f(-1.5, 18, -1.75);
	glTexCoord2f(0, 1);
	glVertex3f(-1.25, 18, -1.75);

	//middle back
	glTexCoord2f(0, 0);
	glVertex3f(1.25, 12.5, -1.75);
	glTexCoord2f(1, 0);
	glVertex3f(-1.25, 12.5, -1.75);
	glTexCoord2f(1, 1);
	glVertex3f(-1.25, 18, -1.75);
	glTexCoord2f(0, 1);
	glVertex3f(1.25, 18, -1.75);

	//right back
	glTexCoord2f(0, 0);
	glVertex3f(1.25, 11.5, -1.75);
	glTexCoord2f(1, 0);
	glVertex3f(1.5, 11.5, -1.75);
	glTexCoord2f(1, 1);
	glVertex3f(1.5, 18, -1.75);
	glTexCoord2f(0, 1);
	glVertex3f(1.25, 18, -1.75);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-1.5, 18, -1.75);
	glTexCoord2f(1, 0);
	glVertex3f(-1.5, 18, 1.75);
	glTexCoord2f(1, 1);
	glVertex3f(-1.5, 11.5, 1.75);
	glTexCoord2f(0, 1);
	glVertex3f(-1.5, 11.5, -1.75);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(1.5, 18, -1.75);
	glTexCoord2f(1, 0);
	glVertex3f(1.5, 18, 1.75);
	glTexCoord2f(1, 1);
	glVertex3f(1.5, 11.5, 1.75);
	glTexCoord2f(0, 1);
	glVertex3f(1.5, 11.5, -1.75);
	glEnd();
#pragma endregion core
#pragma region join
	glBindTexture(GL_TEXTURE_2D, textureMetalBlueShine);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, darkBlue);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, darkBlue);
	glColor3f(darkBlue[0], darkBlue[1], darkBlue[2]);
	glBegin(GL_QUADS);
	//left
	glTexCoord2f(0, 0);
	glVertex3f(-1.5, 21, -1.75);
	glTexCoord2f(1, 0);
	glVertex3f(-1.5, 21, 1.75);
	glTexCoord2f(1, 1);
	glVertex3f(-1.5, 18, 1.75);
	glTexCoord2f(0, 1);
	glVertex3f(-1.5, 18, -1.75);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(1.5, 21, -1.75);
	glTexCoord2f(1, 0);
	glVertex3f(1.5, 21, 1.75);
	glTexCoord2f(1, 1);
	glVertex3f(1.5, 18, 1.75);
	glTexCoord2f(0, 1);
	glVertex3f(1.5, 18, -1.75);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(-1.5, 21, 1.75);
	glTexCoord2f(1, 0);
	glVertex3f(1.5, 21, 1.75);
	glTexCoord2f(1, 1);
	glVertex3f(1.5, 18, 1.75);
	glTexCoord2f(0, 1);
	glVertex3f(-1.5, 18, 1.75);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(-1.5, 21, -1.75);
	glTexCoord2f(1, 0);
	glVertex3f(1.5, 21, -1.75);
	glTexCoord2f(1, 1);
	glVertex3f(1.5, 18, -1.75);
	glTexCoord2f(0, 1);
	glVertex3f(-1.5, 18, -1.75);

	//-------------------------------------side part
	//right
	glTexCoord2f(0, 0);
	glVertex3f(-2, 20, -1.25);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 20, 1.25);
	glTexCoord2f(1, 1);
	glVertex3f(-2, 17, 1.25);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 17, -1.25);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-1.5, 20, -1.25);
	glTexCoord2f(1, 0);
	glVertex3f(-1.5, 20, 1.25);
	glTexCoord2f(1, 1);
	glVertex3f(-1.5, 18, 1.25);
	glTexCoord2f(0, 1);
	glVertex3f(-1.5, 18, -1.25);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(-1.5, 20, 1.25);
	glTexCoord2f(1, 0);
	glVertex3f(-1.5, 18, 1.25);
	glTexCoord2f(1, 1);
	glVertex3f(-2, 17, 1.25);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 20, 1.25);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(-1.5, 20, -1.25);
	glTexCoord2f(1, 0);
	glVertex3f(-1.5, 18, -1.25);
	glTexCoord2f(1, 1);
	glVertex3f(-2, 17, -1.25);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 20, -1.25);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-1.5, 20, -1.25);
	glTexCoord2f(1, 0);
	glVertex3f(-1.5, 20, 1.25);
	glTexCoord2f(1, 1);
	glVertex3f(-2, 20, 1.25);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 20, -1.25);
	glEnd();
#pragma endregion join
#pragma region shield
	glBindTexture(GL_TEXTURE_2D, textureMetalBlueShine);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, indigo);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, indigo);
	glColor3f(indigo[0], indigo[1], indigo[2]);
	glBegin(GL_QUADS);
	//front
	glTexCoord2f(0, 0);
	glVertex3f(3, 22, 2.25);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 22, 2.25);
	glTexCoord2f(1, 1);
	glVertex3f(-2, 17, 2.25);
	glTexCoord2f(0, 1);
	glVertex3f(3, 16, 2.25);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(3, 22, -2.25);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 22, -2.25);
	glTexCoord2f(1, 1);
	glVertex3f(-2, 17, -2.25);
	glTexCoord2f(0, 1);
	glVertex3f(3, 16, -2.25);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(3, 22, -2.25);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 22, -2.25);
	glTexCoord2f(1, 1);
	glVertex3f(-2, 22, 2.25);
	glTexCoord2f(0, 1);
	glVertex3f(3, 22, 2.25);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(-2, 22, 2.25);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 22, 1.75);
	glTexCoord2f(1, 1);
	glVertex3f(-2, 17, 1.75);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 17, 2.25);

	glTexCoord2f(0, 0);
	glVertex3f(-2, 22, -2.25);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 22, -1.75);
	glTexCoord2f(1, 1);
	glVertex3f(-2, 17, -1.75);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 17, -2.25);

	glTexCoord2f(0, 0);
	glVertex3f(-2, 22, 2.25);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 22, -2.25);
	glTexCoord2f(1, 1);
	glVertex3f(-2, 21, -1.75);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 21, 1.75);
	glEnd();

	//--------------------------side part
	glBindTexture(GL_TEXTURE_2D, textureRedLamp);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, red);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, red);
	glColor3f(red[0], red[1], red[2]);
	glBegin(GL_QUADS);
	//front
	glTexCoord2f(0, 0);
	glVertex3f(-2, 21, 1.75);
	glTexCoord2f(1, 0);
	glVertex3f(-4, 21, 1.75);
	glTexCoord2f(1, 1);
	glVertex3f(-4, 19, 1.75);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 18, 1.75);

	glTexCoord2f(0, 0);
	glVertex3f(-2, 21, 1.25);
	glTexCoord2f(1, 0);
	glVertex3f(-4, 21, 1.25);
	glTexCoord2f(1, 1);
	glVertex3f(-4, 19, 1.25);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 18, 1.25);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(-2, 21, -1.75);
	glTexCoord2f(1, 0);
	glVertex3f(-4, 21, -1.75);
	glTexCoord2f(1, 1);
	glVertex3f(-4, 19, -1.75);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 18, -1.75);

	glTexCoord2f(0, 0);
	glVertex3f(-2, 21, -1.25);
	glTexCoord2f(1, 0);
	glVertex3f(-4, 21, -1.25);
	glTexCoord2f(1, 1);
	glVertex3f(-4, 19, -1.25);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 18, -1.25);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-2, 21, 1.75);
	glTexCoord2f(1, 0);
	glVertex3f(-4, 21, 1.75);
	glTexCoord2f(1, 1);
	glVertex3f(-4, 21, -1.75);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 21, -1.75);

	glTexCoord2f(0, 0);
	glVertex3f(-2, 20.5, 1.75);
	glTexCoord2f(1, 0);
	glVertex3f(-4, 20.5, 1.75);
	glTexCoord2f(1, 1);
	glVertex3f(-4, 20.5, -1.75);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 20.5, -1.75);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(-4, 21, 1.75);
	glTexCoord2f(1, 0);
	glVertex3f(-4, 21, 1.25);
	glTexCoord2f(1, 1);
	glVertex3f(-4, 19, 1.25);
	glTexCoord2f(0, 1);
	glVertex3f(-4, 19, 1.75);

	glTexCoord2f(0, 0);
	glVertex3f(-4, 19, 1.25);
	glTexCoord2f(1, 0);
	glVertex3f(-4, 19, 1.75);
	glTexCoord2f(1, 1);
	glVertex3f(-2, 18, 1.75);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 18, 1.25);

	glTexCoord2f(0, 0);
	glVertex3f(-4, 21, -1.75);
	glTexCoord2f(1, 0);
	glVertex3f(-4, 21, -1.25);
	glTexCoord2f(1, 1);
	glVertex3f(-4, 19, -1.25);
	glTexCoord2f(0, 1);
	glVertex3f(-4, 19, -1.75);

	glTexCoord2f(0, 0);
	glVertex3f(-4, 19, -1.25);
	glTexCoord2f(1, 0);
	glVertex3f(-4, 19, -1.75);
	glTexCoord2f(1, 1);
	glVertex3f(-2, 18, -1.75);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 18, -1.25);

	glTexCoord2f(0, 0);
	glVertex3f(-4, 21, 1.25);
	glTexCoord2f(1, 0);
	glVertex3f(-4, 21, -1.75);
	glTexCoord2f(1, 1);
	glVertex3f(-4, 20.5, -1.75);
	glTexCoord2f(0, 1);
	glVertex3f(-4, 20.5, 1.25);
	glEnd();

	//-----------------------------front left part
	glBindTexture(GL_TEXTURE_2D, textureMetalGrey);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, darkBlue);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, darkBlue);
	glColor3f(darkBlue[0], darkBlue[1], darkBlue[2]);
	glBegin(GL_QUADS);
	//front
	glTexCoord2f(0, 0);
	glVertex3f(3, 23, 2.75);
	glTexCoord2f(1, 0);
	glVertex3f(1.25, 23, 2.75);
	glTexCoord2f(1, 1);
	glVertex3f(1.25, 19.5, 2.75);
	glTexCoord2f(0, 1);
	glVertex3f(3, 19, 2.75);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(3, 23, -2.75);
	glTexCoord2f(1, 0);
	glVertex3f(1.25, 23, -2.75);
	glTexCoord2f(1, 1);
	glVertex3f(1.25, 19.5, -2.75);
	glTexCoord2f(0, 1);
	glVertex3f(3, 19, -2.75);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(3, 23, 2.75);
	glTexCoord2f(1, 0);
	glVertex3f(1.25, 23, 2.75);
	glTexCoord2f(1, 1);
	glVertex3f(1.25, 23, -2.75);
	glTexCoord2f(0, 1);
	glVertex3f(3, 23, -2.75);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(3, 23, 2.75);
	glTexCoord2f(1, 0);
	glVertex3f(3, 23, -2.75);
	glTexCoord2f(1, 1);
	glVertex3f(3, 19, -2.75);
	glTexCoord2f(0, 1);
	glVertex3f(3, 19, 2.75);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(1.25, 23, 2.75);
	glTexCoord2f(1, 0);
	glVertex3f(1.25, 23, -2.75);
	glTexCoord2f(1, 1);
	glVertex3f(1.25, 19.5, -2.75);
	glTexCoord2f(0, 1);
	glVertex3f(1.25, 19.5, 2.75);

	//-----------------------------front right part
	//front
	glTexCoord2f(0, 0);
	glVertex3f(-0.25, 23, 2.75);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 23, 2.75);
	glTexCoord2f(1, 1);
	glVertex3f(-2, 19.5, 2.75);
	glTexCoord2f(0, 1);
	glVertex3f(-0.25, 19.5, 2.75);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(-0.25, 23, -2.75);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 23, -2.75);
	glTexCoord2f(1, 1);
	glVertex3f(-2, 19.5, -2.75);
	glTexCoord2f(0, 1);
	glVertex3f(-0.25, 19.5, -2.75);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-2, 23, 2.75);
	glTexCoord2f(1, 0);
	glVertex3f(-0.25, 23, 2.75);
	glTexCoord2f(1, 1);
	glVertex3f(-0.25, 23, -2.75);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 23, -2.75);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-0.25, 23, 2.75);
	glTexCoord2f(1, 0);
	glVertex3f(-0.25, 23, -2.75);
	glTexCoord2f(1, 1);
	glVertex3f(-0.25, 19.5, -2.75);
	glTexCoord2f(0, 1);
	glVertex3f(-0.25, 19.5, 2.75);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(-2, 23, 2.75);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 23, 2.25);
	glTexCoord2f(1, 1);
	glVertex3f(-2, 19.5, 2.25);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 19.5, 2.75);

	glTexCoord2f(0, 0);
	glVertex3f(-2, 23, -2.75);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 23, -2.25);
	glTexCoord2f(1, 1);
	glVertex3f(-2, 19.5, -2.25);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 19.5, -2.75);

	glTexCoord2f(0, 0);
	glVertex3f(-2, 23, 2.75);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 22.5, 2.25);
	glTexCoord2f(1, 1);
	glVertex3f(-2, 22.5, -2.25);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 23, -2.75);
	glEnd();
#pragma endregion shield
	glPopMatrix();
}

void leftFoot() {
	glPushMatrix();
#pragma region core
	glBindTexture(GL_TEXTURE_2D, textureMetalGrey);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, silver);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, silver);
	glColor3f(silver[0], silver[1], silver[2]);
	glBegin(GL_QUADS);
	//--------------------------------front part
	//front
	glTexCoord2f(0, 0);
	glVertex3f(-1.5, 0, 4);
	glTexCoord2f(1, 0);
	glVertex3f(1.5, 0, 4);
	glTexCoord2f(1, 1);
	glVertex3f(1.5, 2, 2.5);
	glTexCoord2f(0, 1);
	glVertex3f(-1.5, 2, 2.5);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(-1.5, 0, -1);
	glTexCoord2f(1, 0);
	glVertex3f(1.5, 0, -1);
	glTexCoord2f(1, 1);
	glVertex3f(1.5, 2, -1);
	glTexCoord2f(0, 1);
	glVertex3f(-1.5, 2, -1);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-1.5, 2, 2.5);
	glTexCoord2f(1, 0);
	glVertex3f(1.5, 2, 2.5);
	glTexCoord2f(1, 1);
	glVertex3f(1.5, 2, -1);
	glTexCoord2f(0, 1);
	glVertex3f(-1.5, 2, -1);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-1.5, 0, 4);
	glTexCoord2f(1, 0);
	glVertex3f(-1.5, 2, 2.5);
	glTexCoord2f(1, 1);
	glVertex3f(-1.5, 2, -1);
	glTexCoord2f(0, 1);
	glVertex3f(-1.5, 0, -1);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(1.5, 0, 4);
	glTexCoord2f(1, 0);
	glVertex3f(1.5, 2, 2.5);
	glTexCoord2f(1, 1);
	glVertex3f(1.5, 2, -1);
	glTexCoord2f(0, 1);
	glVertex3f(1.5, 0, -1);

	//------------------------------------front part shield
	//front
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, indigo);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, indigo);
	glColor3f(indigo[0], indigo[1], indigo[2]);
	glTexCoord2f(0, 0);
	glVertex3f(-2, 0, 5);
	glTexCoord2f(1, 0);
	glVertex3f(2, 0, 5);
	glTexCoord2f(1, 1);
	glVertex3f(2, 1, 4);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 1, 4);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(-2.5, 0, -1);
	glTexCoord2f(1, 0);
	glVertex3f(2.5, 0, -1);
	glTexCoord2f(1, 1);
	glVertex3f(2.5, 2, -2);
	glTexCoord2f(0, 1);
	glVertex3f(-2.5, 2, -2);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-2, 1, 4);
	glTexCoord2f(1, 0);
	glVertex3f(2, 1, 4);
	glTexCoord2f(1, 1);
	glVertex3f(2.5, 2, -2);
	glTexCoord2f(0, 1);
	glVertex3f(-2.5, 2, -2);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-2, 0, 5);
	glTexCoord2f(1, 0);
	glVertex3f(2, 0, 5);
	glTexCoord2f(1, 1);
	glVertex3f(2.5, 0, -1);
	glTexCoord2f(0, 1);
	glVertex3f(-2.5, 0, -1);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-2, 0, 5);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 1, 4);
	glTexCoord2f(1, 1);
	glVertex3f(-2.5, 2, -2);
	glTexCoord2f(0, 1);
	glVertex3f(-2.5, 0, -1);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(2, 0, 5);
	glTexCoord2f(1, 0);
	glVertex3f(2, 1, 4);
	glTexCoord2f(1, 1);
	glVertex3f(2.5, 2, -2);
	glTexCoord2f(0, 1);
	glVertex3f(2.5, 0, -1);

	//------------------------------------middle part
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, grey);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, grey);
	glColor3f(grey[0], grey[1], grey[2]);
	//back
	glTexCoord2f(0, 0);
	glVertex3f(-2, 5, -4.5);
	glTexCoord2f(1, 0);
	glVertex3f(2, 5, -4.5);
	glTexCoord2f(1, 1);
	glVertex3f(2, 2, -5);
	glTexCoord2f(1, 1);
	glVertex3f(-2, 2, -5);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-2, 5, -4.5);
	glTexCoord2f(1, 0);
	glVertex3f(2, 5, -4.5);
	glTexCoord2f(1, 1);
	glVertex3f(2, 5, 0);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 5, 0);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-2, 5, 0);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 5, -4.5);
	glTexCoord2f(1, 1);
	glVertex3f(-2, 2, -5);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 2, 0);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(2, 5, 0);
	glTexCoord2f(1, 0);
	glVertex3f(2, 5, -4.5);
	glTexCoord2f(1, 1);
	glVertex3f(2, 2, -5);
	glTexCoord2f(0, 1);
	glVertex3f(2, 2, 0);
	glEnd();

	//--------------------------------back shield part
	glBindTexture(GL_TEXTURE_2D, textureMetalBlueShine);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, indigo);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, indigo);
	glColor3f(indigo[0], indigo[1], indigo[2]);
	glBegin(GL_POLYGON);
	//back
	glTexCoord2f(0, 0);
	glVertex3f(-2.5, 0, -5.25);
	glTexCoord2f(1, 0);
	glVertex3f(-2.5, 1, -5.5);
	glTexCoord2f(1, 1);
	glVertex3f(-2.5, 3, -5);
	glTexCoord2f(0, 1);
	glVertex3f(2.5, 3, -5);
	glTexCoord2f(0, 0);
	glVertex3f(2.5, 1, -5.5);
	glTexCoord2f(1, 0);
	glVertex3f(2.5, 0, -5.25);
	glEnd();

	glBegin(GL_POLYGON);
	//left
	glTexCoord2f(0, 0);
	glVertex3f(-2.5, 3, -2);
	glTexCoord2f(1, 0);
	glVertex3f(-2.5, 3, -5);
	glTexCoord2f(1, 1);
	glVertex3f(-2.5, 1, -5.5);
	glTexCoord2f(0, 1);
	glVertex3f(-2.5, 0, -5.25);
	glTexCoord2f(0, 0);
	glVertex3f(-2.5, 0, -2.5);
	glTexCoord2f(1, 0);
	glVertex3f(-2.5, 1, -2);
	glEnd();

	glBegin(GL_POLYGON);
	//right
	glTexCoord2f(0, 0);
	glVertex3f(2.5, 3, -2);
	glTexCoord2f(1, 0);
	glVertex3f(2.5, 3, -5);
	glTexCoord2f(1, 1);
	glVertex3f(2.5, 1, -5.5);
	glTexCoord2f(0, 1);
	glVertex3f(2.5, 0, -5.25);
	glTexCoord2f(0, 0);
	glVertex3f(2.5, 0, -2.5);
	glTexCoord2f(1, 0);
	glVertex3f(2.5, 1, -2);
	glEnd();
#pragma endregion core

#pragma region shield
	//------------------------------------front part
	glBegin(GL_POLYGON);
	//left darkBlue
	glTexCoord2f(0, 0);
	glVertex3f(-2, 3, 2);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 1.25, 1.5);
	glTexCoord2f(1, 1);
	glVertex3f(-2.5, 2, -1.75);
	glTexCoord2f(0, 1);
	glVertex3f(-2.5, 3, -2);
	glTexCoord2f(0, 0);
	glVertex3f(-2, 6, 1);
	glEnd();

	glBegin(GL_POLYGON);
	//right darkBlue
	glTexCoord2f(0, 0);
	glVertex3f(2, 3, 2);
	glTexCoord2f(1, 0);
	glVertex3f(2, 1.25, 1.5);
	glTexCoord2f(1, 1);
	glVertex3f(2.5, 2, -1.75);
	glTexCoord2f(0, 1);
	glVertex3f(2.5, 3, -2);
	glTexCoord2f(1, 0);
	glVertex3f(2, 6, 1);
	glEnd();

	glBegin(GL_QUADS);
	//front darkBlue
	glTexCoord2f(0, 0);
	glVertex3f(-2, 3, 2);
	glTexCoord2f(1, 0);
	glVertex3f(2, 3, 2);
	glTexCoord2f(1, 1);
	glVertex3f(2, 6, 1);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 6, 1);
	glEnd();


	glBindTexture(GL_TEXTURE_2D, textureMetalGrey);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, grey);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, grey);
	glColor3f(grey[0], grey[1], grey[2]);
	glBegin(GL_QUADS);
	//front black
	glTexCoord2f(0, 0);
	glVertex3f(-2, 6, 1);
	glTexCoord2f(1, 0);
	glVertex3f(2, 6, 1);
	glTexCoord2f(1, 1);
	glVertex3f(2, 7, 1);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 7, 1);

	//left black
	glTexCoord2f(0, 0);
	glVertex3f(-2, 6, 1);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 7, 1);
	glTexCoord2f(1, 1);
	glVertex3f(-2.5, 4.5, -2.25);
	glTexCoord2f(0, 1);
	glVertex3f(-2.5, 3, -2);

	//right black
	glTexCoord2f(0, 0);
	glVertex3f(2, 6, 1);
	glTexCoord2f(1, 0);
	glVertex3f(2, 7, 1);
	glTexCoord2f(1, 1);
	glVertex3f(2.5, 4.5, -2.25);
	glTexCoord2f(0, 1);
	glVertex3f(2.5, 3, -2);
	glEnd();

	//-------------------------------------join part
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, textureBlackCore);
	glTranslatef(-3, 3, -2.5);
	glRotatef(90, 0, 1, 0);
	gluQuadricTexture(obj, true);
	gluCylinder(obj, 1.5, 1.5, 6, 20, 10);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++) {
		glTexCoord2d((float)i / 360, (float)i / 360);
		glVertex2f(1.5 * cos(i), 1.5 * sin(i));
	}
	glEnd();
	glPushMatrix();
	glTranslatef(0, 0, 6);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++) {
		glTexCoord2d((float)i / 360, (float)i / 360);
		glVertex2f(1.5 * cos(i), 1.5 * sin(i));
	}
	glEnd();
	glPopMatrix();
	glPopMatrix();
#pragma endregion shield
	glPopMatrix();
}

void leftLowerLeg() {
	glPushMatrix();
#pragma region core
	//----------------------------------join
	glPushMatrix();
	glTranslatef(0, 5.5, -2.5);
	glBindTexture(GL_TEXTURE_2D, textureMetalGrey);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, silver);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, silver);
	glColor3f(silver[0], silver[1], silver[2]);
	gluQuadricTexture(obj, true);
	gluSphere(obj, 1.3, 10, 10);
	glPopMatrix();

	//--------------------------------core

	glBegin(GL_QUADS);
	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-1.5, 6, -4);
	glTexCoord2f(1, 0);
	glVertex3f(1.5, 6, -4);
	glTexCoord2f(1, 1);
	glVertex3f(1.5, 6, -1);
	glTexCoord2f(0, 1);
	glVertex3f(-1.5, 6, -1);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-1.5, 10, -4);
	glTexCoord2f(1, 0);
	glVertex3f(1.5, 10, -4);
	glTexCoord2f(1, 1);
	glVertex3f(1.5, 10, -1);
	glTexCoord2f(0, 1);
	glVertex3f(-1.5, 10, -1);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-1.5, 6, -4);
	glTexCoord2f(1, 0);
	glVertex3f(-1.5, 10, -4);
	glTexCoord2f(1, 1);
	glVertex3f(-1.5, 10, -1);
	glTexCoord2f(0, 1);
	glVertex3f(-1.5, 6, -1);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(1.5, 6, -4);
	glTexCoord2f(1, 0);
	glVertex3f(1.5, 10, -4);
	glTexCoord2f(1, 1);
	glVertex3f(1.5, 10, -1);
	glTexCoord2f(0, 1);
	glVertex3f(1.5, 6, -1);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(-1.5, 6, -1);
	glTexCoord2f(1, 0);
	glVertex3f(1.5, 6, -1);
	glTexCoord2f(1, 1);
	glVertex3f(1.5, 10, -1);
	glTexCoord2f(0, 1);
	glVertex3f(-1.5, 10, -1);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(-1.5, 6, -4);
	glTexCoord2f(1, 0);
	glVertex3f(1.5, 6, -4);
	glTexCoord2f(1, 1);
	glVertex3f(1.5, 10, -4);
	glTexCoord2f(0, 1);
	glVertex3f(-1.5, 10, -4);
	glEnd();
#pragma endregion core

#pragma region shield
	glBindTexture(GL_TEXTURE_2D, textureMetalBlueShine);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, indigo);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, indigo);
	glColor3f(indigo[0], indigo[1], indigo[2]);
	glBegin(GL_QUADS);
	//front
	glTexCoord2f(0, 0);
	glVertex3f(-1.5, 6, 0);
	glTexCoord2f(1, 0);
	glVertex3f(1.5, 6, 0);
	glTexCoord2f(1, 1);
	glVertex3f(1.5, 10, -1);
	glTexCoord2f(0, 1);
	glVertex3f(-1.5, 10, -1);
	glEnd();

	glBegin(GL_POLYGON);
	//left
	glTexCoord2f(0, 0);
	glVertex3f(-1.5, 6, 0);
	glTexCoord2f(1, 0);
	glVertex3f(-1.5, 10, -1);
	glTexCoord2f(1, 1);
	glVertex3f(-2, 8, -4.25);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 6, -4.25);
	glTexCoord2f(0, 0);
	glVertex3f(-2.5, 3, -1.5);
	glEnd();

	glBegin(GL_POLYGON);
	//right
	glTexCoord2f(0, 0);
	glVertex3f(1.5, 6, 0);
	glTexCoord2f(1, 0);
	glVertex3f(1.5, 10, -1);
	glTexCoord2f(1, 1);
	glVertex3f(2, 8, -4.25);
	glTexCoord2f(0, 1);
	glVertex3f(2, 6, -4.25);
	glTexCoord2f(0, 0);
	glVertex3f(2.5, 3, -1.5);
	glEnd();

	glBegin(GL_QUADS);
	//back
	glTexCoord2f(0, 0);
	glVertex3f(-2, 6, -4.25);
	glTexCoord2f(1, 0);
	glVertex3f(2, 6, -4.25);
	glTexCoord2f(1, 1);
	glVertex3f(2, 8, -4.25);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 8, -4.25);
	glEnd();

	//-----------------------------top front part
	glBindTexture(GL_TEXTURE_2D, textureMetalGrey);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, darkBlue);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, darkBlue);
	glColor3f(darkBlue[0], darkBlue[1], darkBlue[2]);
	glBegin(GL_QUADS);
	//horizontal part
	//front
	glTexCoord2f(0, 0);
	glVertex3f(-1.5, 12.5, 0);
	glTexCoord2f(1, 0);
	glVertex3f(1.5, 12.5, 0);
	glTexCoord2f(1, 1);
	glVertex3f(1.5, 10.5, 0);
	glTexCoord2f(0, 1);
	glVertex3f(-1.5, 10.5, 0);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(-2, 13, -1);
	glTexCoord2f(1, 0);
	glVertex3f(2, 13, -1);
	glTexCoord2f(1, 1);
	glVertex3f(2, 10, -1);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 10, -1);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-2, 13, -1);
	glTexCoord2f(1, 0);
	glVertex3f(2, 13, -1);
	glTexCoord2f(1, 1);
	glVertex3f(2, 12.5, 0);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 12.5, 0);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-2, 10, -1);
	glTexCoord2f(1, 0);
	glVertex3f(2, 10, -1);
	glTexCoord2f(1, 1);
	glVertex3f(2, 10.5, 0);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 10.5, 0);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-2, 13, -1);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 12.5, 0);
	glTexCoord2f(1, 1);
	glVertex3f(-2, 10.5, 0);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 10, -1);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(2, 13, -1);
	glTexCoord2f(1, 0);
	glVertex3f(2, 12.5, 0);
	glTexCoord2f(1, 1);
	glVertex3f(2, 10.5, 0);
	glTexCoord2f(0, 1);
	glVertex3f(2, 10, -1);

	//vertical part
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, indigo);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, indigo);
	glColor3f(indigo[0], indigo[1], indigo[2]);
	//front
	glTexCoord2f(0, 0);
	glVertex3f(-1, 9, 0.25);
	glTexCoord2f(1, 0);
	glVertex3f(1, 9, 0.25);
	glTexCoord2f(1, 1);
	glVertex3f(1, 14, 0.25);
	glTexCoord2f(0, 1);
	glVertex3f(-1, 14, 0.25);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-1, 14, -0.75);
	glTexCoord2f(1, 0);
	glVertex3f(1, 14, -0.75);
	glTexCoord2f(1, 1);
	glVertex3f(1, 14, 0.25);
	glTexCoord2f(0, 1);
	glVertex3f(-1, 14, 0.25);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-1, 9, -1);
	glTexCoord2f(1, 0);
	glVertex3f(1, 9, -1);
	glTexCoord2f(1, 1);
	glVertex3f(1, 9, 0.25);
	glTexCoord2f(0, 1);
	glVertex3f(-1, 9, 0.25);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-1, 9, 0.25);
	glTexCoord2f(1, 0);
	glVertex3f(-1, 14, 0.25);
	glTexCoord2f(1, 1);
	glVertex3f(-1, 14, -0.75);
	glTexCoord2f(0, 1);
	glVertex3f(-1, 9, -0.75);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(1, 9, 0.25);
	glTexCoord2f(1, 0);
	glVertex3f(1, 14, 0.25);
	glTexCoord2f(1, 1);
	glVertex3f(1, 14, -0.75);
	glTexCoord2f(0, 1);
	glVertex3f(1, 9, -0.75);
	glEnd();

	//-----------------------------right part
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, darkBlue);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, darkBlue);
	glColor3f(darkBlue[0], darkBlue[1], darkBlue[2]);
	glBegin(GL_POLYGON);
	//right
	glTexCoord2f(0, 0);
	glVertex3f(2, 13, -1);
	glTexCoord2f(1, 0);
	glVertex3f(2, 13, -3);
	glTexCoord2f(1, 1);
	glVertex3f(2, 10, -3.5);
	glTexCoord2f(0, 1);
	glVertex3f(2, 8, -3);
	glTexCoord2f(0, 0);
	glVertex3f(2, 8, -1);
	glTexCoord2f(1, 0);
	glVertex3f(2, 10, -0.5);
	glEnd();

	glBegin(GL_POLYGON);
	//front
	glTexCoord2f(0, 0);
	glVertex3f(2, 13, -1);
	glTexCoord2f(1, 0);
	glVertex3f(2, 10, -0.5);
	glTexCoord2f(1, 1);
	glVertex3f(2, 8, -1);
	glTexCoord2f(0, 1);
	glVertex3f(1, 8, -1);
	glTexCoord2f(0, 0);
	glVertex3f(1, 10, -0.5);
	glTexCoord2f(1, 0);
	glVertex3f(1, 13, -1);
	glEnd();

	glBegin(GL_POLYGON);
	//back
	glTexCoord2f(0, 0);
	glVertex3f(2, 13, -3);
	glTexCoord2f(1, 0);
	glVertex3f(2, 10, -3.5);
	glTexCoord2f(1, 1);
	glVertex3f(2, 8, -3);
	glTexCoord2f(0, 1);
	glVertex3f(1, 8, -3);
	glTexCoord2f(0, 0);
	glVertex3f(1, 10, -3.5);
	glTexCoord2f(1, 0);
	glVertex3f(1, 13, -3);
	glEnd();

	glBegin(GL_QUADS);
	//top
	glTexCoord2f(0, 0);
	glVertex3f(2, 13, -1);
	glTexCoord2f(1, 0);
	glVertex3f(2, 13, -3);
	glTexCoord2f(1, 1);
	glVertex3f(1, 13, -3);
	glTexCoord2f(0, 1);
	glVertex3f(1, 13, -1);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(2, 8, -1);
	glTexCoord2f(1, 0);
	glVertex3f(2, 8, -3);
	glTexCoord2f(1, 1);
	glVertex3f(1, 8, -3);
	glTexCoord2f(0, 1);
	glVertex3f(1, 8, -1);
	glEnd();

	//-----------------------------left part
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, darkBlue);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, darkBlue);
	glColor3f(darkBlue[0], darkBlue[1], darkBlue[2]);
	glBegin(GL_POLYGON);
	//right
	glTexCoord2f(0, 0);
	glVertex3f(-2, 13, -1.5);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 13, -3.5);
	glTexCoord2f(1, 1);
	glVertex3f(-2, 10, -4);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 8, -3.5);
	glTexCoord2f(0, 0);
	glVertex3f(-2, 8, -1.5);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 10, -0.5);
	glEnd();

	glBegin(GL_POLYGON);
	//front
	glTexCoord2f(0, 0);
	glVertex3f(-2, 13, -1.5);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 10, -0.5);
	glTexCoord2f(1, 1);
	glVertex3f(-2, 8, -1.5);
	glTexCoord2f(0, 1);
	glVertex3f(-1, 8, -1.5);
	glTexCoord2f(0, 0);
	glVertex3f(-1, 10, -0.5);
	glTexCoord2f(1, 0);
	glVertex3f(-1, 13, -1.5);
	glEnd();

	glBegin(GL_POLYGON);
	//back
	glTexCoord2f(0, 0);
	glVertex3f(-2, 13, -3.5);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 10, -4);
	glTexCoord2f(1, 1);
	glVertex3f(-2, 8, -3.5);
	glTexCoord2f(0, 1);
	glVertex3f(-1, 8, -3.5);
	glTexCoord2f(0, 0);
	glVertex3f(-1, 10, -4);
	glTexCoord2f(1, 0);
	glVertex3f(-1, 13, -3.5);
	glEnd();

	glColor3f(darkBlue[0], darkBlue[1], darkBlue[2]);
	glBegin(GL_QUADS);
	//top
	glTexCoord2f(0, 0);
	glVertex3f(-2, 13, -1.5);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 13, -3.5);
	glTexCoord2f(1, 1);
	glVertex3f(-1, 13, -3.5);
	glTexCoord2f(0, 1);
	glVertex3f(-1, 13, -1.5);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-2, 8, -1.5);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 8, -3.5);
	glTexCoord2f(1, 1);
	glVertex3f(-1, 8, -3.5);
	glTexCoord2f(0, 1);
	glVertex3f(-1, 8, -1.5);

	//-----------front part
	//left
	glTexCoord2f(0, 0);
	glVertex3f(-3, 14, -2);
	glTexCoord2f(1, 0);
	glVertex3f(-3, 14, -3);
	glTexCoord2f(1, 1);
	glVertex3f(-3, 5, -3);
	glTexCoord2f(0, 1);
	glVertex3f(-3, 5, -2);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(-3, 14, -3);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 14, -3);
	glTexCoord2f(1, 1);
	glVertex3f(-2, 5, -3);
	glTexCoord2f(0, 1);
	glVertex3f(-3, 5, -3);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(-3, 14, -2);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 14, -2);
	glTexCoord2f(1, 1);
	glVertex3f(-2, 5, -2);
	glTexCoord2f(0, 1);
	glVertex3f(-3, 5, -2);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-3, 14, -2);
	glTexCoord2f(1, 0);
	glVertex3f(-3, 14, -3);
	glTexCoord2f(1, 1);
	glVertex3f(-2, 14, -3);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 14, -2);
	glEnd();

	//-----------------------------back part
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, indigo);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, indigo);
	glColor3f(indigo[0], indigo[1], indigo[2]);
	glBegin(GL_QUADS);
	//front
	glTexCoord2f(0, 0);
	glVertex3f(-1.5, 7.5, -6);
	glTexCoord2f(1, 0);
	glVertex3f(1.5, 7.5, -6);
	glTexCoord2f(1, 1);
	glVertex3f(1.5, 11.5, -6);
	glTexCoord2f(0, 1);
	glVertex3f(-1.5, 11.5, -6);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(-1.75, 7, -4);
	glTexCoord2f(1, 0);
	glVertex3f(1.75, 7, -4);
	glTexCoord2f(1, 1);
	glVertex3f(1.75, 12, -4.25);
	glTexCoord2f(0, 1);
	glVertex3f(-1.75, 12, -4.25);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-1.5, 11.5, -6);
	glTexCoord2f(1, 0);
	glVertex3f(1.5, 11.5, -6);
	glTexCoord2f(1, 1);
	glVertex3f(1.75, 12, -4.25);
	glTexCoord2f(0, 1);
	glVertex3f(-1.75, 12, -4.25);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-1.5, 7.5, -6);
	glTexCoord2f(1, 0);
	glVertex3f(1.5, 7.5, -6);
	glTexCoord2f(1, 1);
	glVertex3f(1.75, 7, -4);
	glTexCoord2f(0, 1);
	glVertex3f(-1.75, 7, -4);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-1.75, 12, -4.25);
	glTexCoord2f(1, 0);
	glVertex3f(-1.75, 7, -4);
	glTexCoord2f(1, 1);
	glVertex3f(-1.5, 7.5, -6);
	glTexCoord2f(0, 1);
	glVertex3f(-1.5, 11.5, -6);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(1.75, 12, -4.25);
	glTexCoord2f(1, 0);
	glVertex3f(1.75, 7, -4);
	glTexCoord2f(1, 1);
	glVertex3f(1.5, 7.5, -6);
	glTexCoord2f(0, 1);
	glVertex3f(1.5, 11.5, -6);
	glEnd();

#pragma endregion shield

#pragma region join
	glBindTexture(GL_TEXTURE_2D, textureBlackCore);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, grey);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, grey);
	glColor3f(grey[0], grey[1], grey[2]);
	glBegin(GL_QUADS);
	//top
	glTexCoord2f(0, 0);
	glVertex3f(-1, 15, -3);
	glTexCoord2f(1, 0);
	glVertex3f(1, 15, -3);
	glTexCoord2f(1, 1);
	glVertex3f(1, 13, -1);
	glTexCoord2f(0, 1);
	glVertex3f(-1, 13, -1);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(-1, 15, -3);
	glTexCoord2f(1, 0);
	glVertex3f(1, 15, -3);
	glTexCoord2f(1, 1);
	glVertex3f(1, 10, -4);
	glTexCoord2f(0, 1);
	glVertex3f(-1, 10, -4);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-1, 15, -3);
	glTexCoord2f(1, 0);
	glVertex3f(-1, 13, -1);
	glTexCoord2f(1, 1);
	glVertex3f(-1, 10, -1);
	glTexCoord2f(0, 1);
	glVertex3f(-1, 10, -4);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(1, 15, -3);
	glTexCoord2f(1, 0);
	glVertex3f(1, 13, -1);
	glTexCoord2f(1, 1);
	glVertex3f(1, 10, -1);
	glTexCoord2f(0, 1);
	glVertex3f(1, 10, -4);
	glEnd();
#pragma endregion join
	glPopMatrix();
}

void leftUpperLeg() {
	glPushMatrix();
#pragma region core
	glBindTexture(GL_TEXTURE_2D, textureRubberGrey);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, silver);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, silver);
	glColor3f(silver[0], silver[1], silver[2]);
	glBegin(GL_QUADS);
	//back
	glTexCoord2f(0, 0);
	glVertex3f(-1, 15, -3.5);
	glTexCoord2f(1, 0);
	glVertex3f(1, 15, -3.5);
	glTexCoord2f(1, 1);
	glVertex3f(2, 22, -4);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 22, -4);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(-1.5, 12.75, -1);
	glTexCoord2f(1, 0);
	glVertex3f(1.5, 12.75, -1);
	glTexCoord2f(1, 1);
	glVertex3f(2, 22, -0);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 22, -0);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-1.5, 12.75, -1);
	glTexCoord2f(1, 0);
	glVertex3f(-1, 15, -3.5);
	glTexCoord2f(1, 1);
	glVertex3f(-2, 22, -4);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 22, -0);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(1.5, 12.75, -1);
	glTexCoord2f(1, 0);
	glVertex3f(1, 15, -3.5);
	glTexCoord2f(1, 1);
	glVertex3f(2, 22, -4);
	glTexCoord2f(0, 1);
	glVertex3f(2, 22, -0);
	glEnd();
#pragma endregion core
#pragma region frontShield
	glBindTexture(GL_TEXTURE_2D, textureBlackCore);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, indigo);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, indigo);
	glColor3f(indigo[0], indigo[1], indigo[2]);
	glBegin(GL_POLYGON);
	//back
	glTexCoord2f(0, 0);
	glVertex3f(-2, 20, 0);
	glTexCoord2f(1, 0);
	glVertex3f(1.75, 20, 0);
	glTexCoord2f(1, 1);
	glVertex3f(2, 21, 0);
	glTexCoord2f(0, 1);
	glVertex3f(2, 28, 0);
	glTexCoord2f(0, 0);
	glVertex3f(-2, 28, 0);
	glEnd();

	glBegin(GL_POLYGON);
	//front
	glTexCoord2f(0, 0);
	glVertex3f(-2, 20, 1);
	glTexCoord2f(1, 0);
	glVertex3f(1.75, 20, 1);
	glTexCoord2f(1, 1);
	glVertex3f(2, 21, 1);
	glTexCoord2f(0, 1);
	glVertex3f(2, 28, 1);
	glTexCoord2f(0, 0);
	glVertex3f(-2, 28, 1);
	glEnd();

	glBegin(GL_QUADS);
	//top
	glTexCoord2f(0, 0);
	glVertex3f(-2, 28, 0);
	glTexCoord2f(1, 0);
	glVertex3f(2, 28, 0);
	glTexCoord2f(1, 1);
	glVertex3f(2, 28, 1);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 28, 1);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-2, 20, 0);
	glTexCoord2f(1, 0);
	glVertex3f(1.5, 20, 0);
	glTexCoord2f(1, 1);
	glVertex3f(1.5, 20, 1);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 20, 1);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-2, 20, 0);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 20, 1);
	glTexCoord2f(1, 1);
	glVertex3f(-2, 28, 1);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 28, 0);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(2, 21, 0);
	glTexCoord2f(1, 0);
	glVertex3f(2, 21, 1);
	glTexCoord2f(1, 1);
	glVertex3f(2, 28, 1);
	glTexCoord2f(0, 1);
	glVertex3f(2, 28, 0);

	glTexCoord2f(0, 0);
	glVertex3f(1.5, 20, 0);
	glTexCoord2f(1, 0);
	glVertex3f(1.5, 20, 1);
	glTexCoord2f(1, 1);
	glVertex3f(2, 21, 1);
	glTexCoord2f(0, 1);
	glVertex3f(2, 21, 0);
	glEnd();

	//------------------------------front part

	glBindTexture(GL_TEXTURE_2D, textureMetalBlueShine);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, darkBlue);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, darkBlue);
	glColor3f(darkBlue[0], darkBlue[1], darkBlue[2]);
	glBegin(GL_POLYGON);
	//front
	glTexCoord2f(0, 0);
	glVertex3f(-1.75, 27.5, 2);
	glTexCoord2f(1, 0);
	glVertex3f(1.75, 27.5, 2);
	glTexCoord2f(1, 1);
	glVertex3f(1.75, 23, 2);
	glTexCoord2f(0, 1);
	glVertex3f(1.25, 22, 2);
	glTexCoord2f(1, 1);
	glVertex3f(-1.75, 22, 2);
	glEnd();

	glBegin(GL_QUADS);
	//top
	glTexCoord2f(0, 0);
	glVertex3f(-1.75, 27.5, 1);
	glTexCoord2f(1, 0);
	glVertex3f(1.75, 27.5, 1);
	glTexCoord2f(1, 1);
	glVertex3f(1.75, 27.5, 2);
	glTexCoord2f(0, 1);
	glVertex3f(-1.75, 27.5, 2);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-1.75, 22, 1);
	glTexCoord2f(1, 0);
	glVertex3f(1.25, 22, 1);
	glTexCoord2f(1, 1);
	glVertex3f(1.25, 22, 2);
	glTexCoord2f(0, 1);
	glVertex3f(-1.75, 22, 2);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-1.75, 22, 1);
	glTexCoord2f(1, 0);
	glVertex3f(-1.75, 22, 2);
	glTexCoord2f(1, 1);
	glVertex3f(-1.75, 27.5, 2);
	glTexCoord2f(0, 1);
	glVertex3f(-1.75, 27.5, 1);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(1.75, 23, 1);
	glTexCoord2f(1, 0);
	glVertex3f(1.75, 23, 2);
	glTexCoord2f(1, 1);
	glVertex3f(1.75, 27.5, 2);
	glTexCoord2f(0, 1);
	glVertex3f(1.75, 27.5, 1);

	glTexCoord2f(0, 0);
	glVertex3f(1.25, 22, 1);
	glTexCoord2f(1, 0);
	glVertex3f(1.25, 22, 2);
	glTexCoord2f(1, 1);
	glVertex3f(1.75, 23, 2);
	glTexCoord2f(0, 1);
	glVertex3f(1.75, 23, 1);
	glEnd();

#pragma endregion frontShield
#pragma region sideShield
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, indigo);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, indigo);
	glColor3f(indigo[0], indigo[1], indigo[2]);
	glBegin(GL_POLYGON);
	//left
	glTexCoord2f(0, 0);
	glVertex3f(2, 28, 0);
	glTexCoord2f(1, 0);
	glVertex3f(2, 21, 0);
	glTexCoord2f(1, 1);
	glVertex3f(2, 20, -1);
	glTexCoord2f(0, 1);
	glVertex3f(2, 20, -3);
	glTexCoord2f(0, 0);
	glVertex3f(2, 21, -4);
	glTexCoord2f(1, 0);
	glVertex3f(2, 28, -4);
	glEnd();

	glBegin(GL_POLYGON);
	//right
	glTexCoord2f(0, 0);
	glVertex3f(3, 28, 0);
	glTexCoord2f(1, 0);
	glVertex3f(3, 21, 0);
	glTexCoord2f(1, 1);
	glVertex3f(3, 20, -1);
	glTexCoord2f(0, 1);
	glVertex3f(3, 20, -3);
	glTexCoord2f(0, 0);
	glVertex3f(3, 21, -4);
	glTexCoord2f(1, 0);
	glVertex3f(3, 28, -4);
	glEnd();

	glBegin(GL_QUADS);
	//front
	glTexCoord2f(0, 0);
	glVertex3f(2, 28, 0);
	glTexCoord2f(1, 0);
	glVertex3f(3, 28, 0);
	glTexCoord2f(1, 1);
	glVertex3f(3, 21, 0);
	glTexCoord2f(0, 1);
	glVertex3f(2, 21, 0);

	//front bottom
	glTexCoord2f(0, 0);
	glVertex3f(3, 21, 0);
	glTexCoord2f(1, 0);
	glVertex3f(2, 21, 0);
	glTexCoord2f(1, 1);
	glVertex3f(2, 20, -1);
	glTexCoord2f(0, 1);
	glVertex3f(3, 20, -1);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(3, 20, -1);
	glTexCoord2f(1, 0);
	glVertex3f(2, 20, -1);
	glTexCoord2f(1, 1);
	glVertex3f(2, 20, -3);
	glTexCoord2f(0, 1);
	glVertex3f(3, 20, -3);

	//back bottom
	glTexCoord2f(0, 0);
	glVertex3f(3, 21, -4);
	glTexCoord2f(1, 0);
	glVertex3f(2, 21, -4);
	glTexCoord2f(1, 1);
	glVertex3f(2, 20, -3);
	glTexCoord2f(0, 1);
	glVertex3f(3, 20, -3);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(2, 28, -4);
	glTexCoord2f(1, 0);
	glVertex3f(3, 28, -4);
	glTexCoord2f(1, 1);
	glVertex3f(3, 21, -4);
	glTexCoord2f(0, 1);
	glVertex3f(2, 21, -4);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(2, 28, 0);
	glTexCoord2f(1, 0);
	glVertex3f(3, 28, 0);
	glTexCoord2f(1, 1);
	glVertex3f(3, 28, -4);
	glTexCoord2f(0, 1);
	glVertex3f(2, 28, -4);
	glEnd();

	//------------------------------side part
	glBindTexture(GL_TEXTURE_2D, textureMetalGrey);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, grey);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, grey);
	glColor3f(grey[0], grey[1], grey[2]);
	glBegin(GL_QUADS);
	//top
	glTexCoord2f(0, 0);
	glVertex3f(3, 28, -1);
	glTexCoord2f(1, 0);
	glVertex3f(3, 28, -3);
	glTexCoord2f(1, 1);
	glVertex3f(3.5, 28, -3);
	glTexCoord2f(0, 1);
	glVertex3f(3.5, 28, -1);

	//top right
	glTexCoord2f(0, 0);
	glVertex3f(3.5, 28, -1);
	glTexCoord2f(1, 0);
	glVertex3f(3.5, 28, -3);
	glTexCoord2f(1, 1);
	glVertex3f(4, 27, -3);
	glTexCoord2f(0, 1);
	glVertex3f(4, 27, -1);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(4, 27, -3);
	glTexCoord2f(1, 0);
	glVertex3f(4, 27, -1);
	glTexCoord2f(1, 1);
	glVertex3f(4, 24, -1);
	glTexCoord2f(0, 1);
	glVertex3f(4, 24, -3);

	//bottom left
	glTexCoord2f(0, 0);
	glVertex3f(3.5, 23, -1);
	glTexCoord2f(1, 0);
	glVertex3f(3.5, 23, -3);
	glTexCoord2f(1, 1);
	glVertex3f(4, 24, -3);
	glTexCoord2f(0, 1);
	glVertex3f(4, 24, -1);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(3, 23, -1);
	glTexCoord2f(1, 0);
	glVertex3f(3, 23, -3);
	glTexCoord2f(1, 1);
	glVertex3f(3.5, 23, -3);
	glTexCoord2f(0, 1);
	glVertex3f(3.5, 23, -1);
	glEnd();

	glBegin(GL_POLYGON);
	//front
	glTexCoord2f(0, 0);
	glVertex3f(3, 28, -1);
	glTexCoord2f(1, 0);
	glVertex3f(3.5, 28, -1);
	glTexCoord2f(1, 1);
	glVertex3f(4, 27, -1);
	glTexCoord2f(0, 1);
	glVertex3f(4, 24, -1);
	glTexCoord2f(0, 0);
	glVertex3f(3.5, 23, -1);
	glTexCoord2f(1, 0);
	glVertex3f(3, 23, -1);
	glEnd();

	glBegin(GL_POLYGON);
	//back
	glTexCoord2f(0, 0);
	glVertex3f(3, 28, -3);
	glTexCoord2f(1, 0);
	glVertex3f(3.5, 28, -3);
	glTexCoord2f(1, 1);
	glVertex3f(4, 27, -3);
	glTexCoord2f(0, 1);
	glVertex3f(4, 24, -3);
	glTexCoord2f(0, 0);
	glVertex3f(3.5, 23, -3);
	glTexCoord2f(1, 0);
	glVertex3f(3, 23, -3);
	glEnd();
#pragma endregion sideShield
	glPopMatrix();
}

void rightFoot() {
	glPushMatrix();
#pragma region core
	glBindTexture(GL_TEXTURE_2D, textureMetalGrey);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, silver);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, silver);
	glColor3f(silver[0], silver[1], silver[2]);
	glBegin(GL_QUADS);
	//--------------------------------front part
	//front
	glTexCoord2f(0, 0);
	glVertex3f(1.5, 0, 4);
	glTexCoord2f(1, 0);
	glVertex3f(-1.5, 0, 4);
	glTexCoord2f(1, 1);
	glVertex3f(-1.5, 2, 2.5);
	glTexCoord2f(0, 1);
	glVertex3f(1.5, 2, 2.5);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(1.5, 0, -1);
	glTexCoord2f(1, 0);
	glVertex3f(-1.5, 0, -1);
	glTexCoord2f(1, 1);
	glVertex3f(-1.5, 2, -1);
	glTexCoord2f(0, 1);
	glVertex3f(1.5, 2, -1);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(1.5, 2, 2.5);
	glTexCoord2f(1, 0);
	glVertex3f(-1.5, 2, 2.5);
	glTexCoord2f(1, 1);
	glVertex3f(-1.5, 2, -1);
	glTexCoord2f(0, 1);
	glVertex3f(1.5, 2, -1);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(1.5, 0, 4);
	glTexCoord2f(1, 0);
	glVertex3f(1.5, 2, 2.5);
	glTexCoord2f(1, 1);
	glVertex3f(1.5, 2, -1);
	glTexCoord2f(0, 1);
	glVertex3f(1.5, 0, -1);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(-1.5, 0, 4);
	glTexCoord2f(1, 0);
	glVertex3f(-1.5, 2, 2.5);
	glTexCoord2f(1, 1);
	glVertex3f(-1.5, 2, -1);
	glTexCoord2f(0, 1);
	glVertex3f(-1.5, 0, -1);

	//------------------------------------front part shield
	//front
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, indigo);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, indigo);
	glColor3f(indigo[0], indigo[1], indigo[2]);
	glTexCoord2f(0, 0);
	glVertex3f(2, 0, 5);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 0, 5);
	glTexCoord2f(1, 1);
	glVertex3f(-2, 1, 4);
	glTexCoord2f(0, 1);
	glVertex3f(2, 1, 4);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(2.5, 0, -1);
	glTexCoord2f(1, 0);
	glVertex3f(-2.5, 0, -1);
	glTexCoord2f(1, 1);
	glVertex3f(-2.5, 2, -2);
	glTexCoord2f(0, 1);
	glVertex3f(2.5, 2, -2);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(2, 1, 4);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 1, 4);
	glTexCoord2f(1, 1);
	glVertex3f(-2.5, 2, -2);
	glTexCoord2f(0, 1);
	glVertex3f(2.5, 2, -2);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(2, 0, 5);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 0, 5);
	glTexCoord2f(1, 1);
	glVertex3f(-2.5, 0, -1);
	glTexCoord2f(0, 1);
	glVertex3f(2.5, 0, -1);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(2, 0, 5);
	glTexCoord2f(1, 0);
	glVertex3f(2, 1, 4);
	glTexCoord2f(1, 1);
	glVertex3f(2.5, 2, -2);
	glTexCoord2f(0, 1);
	glVertex3f(2.5, 0, -1);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(-2, 0, 5);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 1, 4);
	glTexCoord2f(1, 1);
	glVertex3f(-2.5, 2, -2);
	glTexCoord2f(0, 1);
	glVertex3f(-2.5, 0, -1);

	//------------------------------------middle part
	//back
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, grey);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, grey);
	glColor3f(grey[0], grey[1], grey[2]);
	glTexCoord2f(0, 0);
	glVertex3f(2, 5, -4.5);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 5, -4.5);
	glTexCoord2f(1, 1);
	glVertex3f(-2, 2, -5);
	glTexCoord2f(0, 1);
	glVertex3f(2, 2, -5);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(2, 5, -4.5);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 5, -4.5);
	glTexCoord2f(1, 1);
	glVertex3f(-2, 5, 0);
	glTexCoord2f(0, 1);
	glVertex3f(2, 5, 0);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(2, 5, 0);
	glTexCoord2f(1, 0);
	glVertex3f(2, 5, -4.5);
	glTexCoord2f(1, 1);
	glVertex3f(2, 2, -5);
	glTexCoord2f(0, 1);
	glVertex3f(2, 2, 0);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(-2, 5, 0);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 5, -4.5);
	glTexCoord2f(1, 1);
	glVertex3f(-2, 2, -5);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 2, 0);

	//--------------------------------back shield part
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textureMetalBlueShine);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, indigo);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, indigo);
	glColor3f(indigo[0], indigo[1], indigo[2]);
	glBegin(GL_POLYGON);
	//back
	glTexCoord2f(0, 0);
	glVertex3f(2.5, 0, -5.25);
	glTexCoord2f(1, 0);
	glVertex3f(2.5, 1, -5.5);
	glTexCoord2f(1, 1);
	glVertex3f(2.5, 3, -5);
	glTexCoord2f(0, 1);
	glVertex3f(-2.5, 3, -5);
	glTexCoord2f(0, 0);
	glVertex3f(-2.5, 1, -5.5);
	glTexCoord2f(1, 0);
	glVertex3f(-2.5, 0, -5.25);
	glEnd();

	glBegin(GL_POLYGON);
	//left
	glTexCoord2f(0, 0);
	glVertex3f(2.5, 3, -2);
	glTexCoord2f(1, 0);
	glVertex3f(2.5, 3, -5);
	glTexCoord2f(1, 1);
	glVertex3f(2.5, 1, -5.5);
	glTexCoord2f(0, 1);
	glVertex3f(2.5, 0, -5.25);
	glTexCoord2f(0, 0);
	glVertex3f(2.5, 0, -2.5);
	glTexCoord2f(1, 0);
	glVertex3f(2.5, 1, -2);
	glEnd();

	glBegin(GL_POLYGON);
	//right
	glTexCoord2f(0, 0);
	glVertex3f(-2.5, 3, -2);
	glTexCoord2f(1, 0);
	glVertex3f(-2.5, 3, -5);
	glTexCoord2f(1, 1);
	glVertex3f(-2.5, 1, -5.5);
	glTexCoord2f(0, 1);
	glVertex3f(-2.5, 0, -5.25);
	glTexCoord2f(0, 0);
	glVertex3f(-2.5, 0, -2.5);
	glTexCoord2f(1, 0);
	glVertex3f(-2.5, 1, -2);
	glEnd();
#pragma endregion core

#pragma region shield
	//------------------------------------front part
	glBegin(GL_POLYGON);
	//left darkBlue
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, indigo);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, indigo);
	glColor3f(indigo[0], indigo[1], indigo[2]);
	glTexCoord2f(0, 0);
	glVertex3f(2, 3, 2);
	glTexCoord2f(1, 0);
	glVertex3f(2, 1.25, 1.5);
	glTexCoord2f(1, 1);
	glVertex3f(2.5, 2, -1.75);
	glTexCoord2f(0, 1);
	glVertex3f(2.5, 3, -2);
	glTexCoord2f(1, 1);
	glVertex3f(2, 6, 1);
	glEnd();

	glBegin(GL_POLYGON);
	//right darkBlue
	glTexCoord2f(0, 0);
	glVertex3f(-2, 3, 2);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 1.25, 1.5);
	glTexCoord2f(1, 1);
	glVertex3f(-2.5, 2, -1.75);
	glTexCoord2f(0, 1);
	glVertex3f(-2.5, 3, -2);
	glTexCoord2f(1, 1);
	glVertex3f(-2, 6, 1);
	glEnd();

	glBegin(GL_QUADS);
	//front darkBlue
	glTexCoord2f(0, 0);
	glVertex3f(2, 3, 2);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 3, 2);
	glTexCoord2f(1, 1);
	glVertex3f(-2, 6, 1);
	glTexCoord2f(0, 1);
	glVertex3f(2, 6, 1);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textureMetalGrey);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, grey);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, grey);
	glColor3f(grey[0], grey[1], grey[2]);
	glBegin(GL_QUADS);
	//front black
	glTexCoord2f(0, 0);
	glVertex3f(2, 6, 1);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 6, 1);
	glTexCoord2f(1, 1);
	glVertex3f(-2, 7, 1);
	glTexCoord2f(0, 1);
	glVertex3f(2, 7, 1);

	//left black
	glTexCoord2f(0, 0);
	glVertex3f(2, 6, 1);
	glTexCoord2f(1, 0);
	glVertex3f(2, 7, 1);
	glTexCoord2f(1, 1);
	glVertex3f(2.5, 4.5, -2.25);
	glTexCoord2f(0, 1);
	glVertex3f(2.5, 3, -2);

	//right black
	glTexCoord2f(0, 0);
	glVertex3f(-2, 6, 1);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 7, 1);
	glTexCoord2f(1, 1);
	glVertex3f(-2.5, 4.5, -2.25);
	glTexCoord2f(0, 1);
	glVertex3f(-2.5, 3, -2);
	glEnd();

	//-------------------------------------join part
	glColor3f(grey[0], grey[1], grey[2]);
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, textureBlackCore);
	glTranslatef(-3, 3, -2.5);
	glRotatef(90, 0, 1, 0);
	gluQuadricTexture(obj, true);
	gluCylinder(obj, 1.5, 1.5, 6, 20, 10);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++) {
		glTexCoord2d((float)i / 360, (float)i / 360);
		glVertex2f(1.5 * cos(i), 1.5 * sin(i));
	}
	glEnd();
	glPushMatrix();
	glTranslatef(0, 0, 6);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++) {
		glTexCoord2d((float)i / 360, (float)i / 360);
		glVertex2f(1.5 * cos(i), 1.5 * sin(i));
	}
	glEnd();
	glPopMatrix();
	glPopMatrix();
#pragma endregion shield
	glPopMatrix();
}

void rightLowerLeg() {
	glPushMatrix();
#pragma region core
	//----------------------------------join
	glPushMatrix();
	glTranslatef(0, 5.5, -2.5);
	glBindTexture(GL_TEXTURE_2D, textureMetalGrey);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, silver);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, silver);
	glColor3f(silver[0], silver[1], silver[2]);
	gluQuadricTexture(obj, true);
	gluSphere(obj, 1.3, 10, 10);
	glPopMatrix();

	//--------------------------------core
	glBegin(GL_QUADS);
	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(1.5, 6, -4);
	glTexCoord2f(1, 0);
	glVertex3f(-1.5, 6, -4);
	glTexCoord2f(1, 1);
	glVertex3f(-1.5, 6, -1);
	glTexCoord2f(0, 1);
	glVertex3f(1.5, 6, -1);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(1.5, 10, -4);
	glTexCoord2f(1, 0);
	glVertex3f(-1.5, 10, -4);
	glTexCoord2f(1, 1);
	glVertex3f(-1.5, 10, -1);
	glTexCoord2f(0, 1);
	glVertex3f(1.5, 10, -1);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(1.5, 6, -4);
	glTexCoord2f(1, 0);
	glVertex3f(1.5, 10, -4);
	glTexCoord2f(1, 1);
	glVertex3f(1.5, 10, -1);
	glTexCoord2f(0, 1);
	glVertex3f(1.5, 6, -1);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(-1.5, 6, -4);
	glTexCoord2f(1, 0);
	glVertex3f(-1.5, 10, -4);
	glTexCoord2f(1, 1);
	glVertex3f(-1.5, 10, -1);
	glTexCoord2f(0, 1);
	glVertex3f(-1.5, 6, -1);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(1.5, 6, -1);
	glTexCoord2f(1, 0);
	glVertex3f(-1.5, 6, -1);
	glTexCoord2f(1, 1);
	glVertex3f(-1.5, 10, -1);
	glTexCoord2f(0, 1);
	glVertex3f(1.5, 10, -1);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(1.5, 6, -4);
	glTexCoord2f(1, 0);
	glVertex3f(-1.5, 6, -4);
	glTexCoord2f(1, 1);
	glVertex3f(-1.5, 10, -4);
	glTexCoord2f(0, 1);
	glVertex3f(1.5, 10, -4);
	glEnd();
#pragma endregion core

#pragma region shield
	glBindTexture(GL_TEXTURE_2D, textureMetalBlueShine);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, indigo);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, indigo);
	glColor3f(indigo[0], indigo[1], indigo[2]);
	glBegin(GL_QUADS);
	//front
	glTexCoord2f(0, 0);
	glVertex3f(1.5, 6, 0);
	glTexCoord2f(1, 0);
	glVertex3f(-1.5, 6, 0);
	glTexCoord2f(1, 1);
	glVertex3f(-1.5, 10, -1);
	glTexCoord2f(0, 1);
	glVertex3f(1.5, 10, -1);
	glEnd();

	glBegin(GL_POLYGON);
	//left
	glTexCoord2f(0, 0);
	glVertex3f(1.5, 6, 0);
	glTexCoord2f(1, 0);
	glVertex3f(1.5, 10, -1);
	glTexCoord2f(1, 1);
	glVertex3f(2, 8, -4.25);
	glTexCoord2f(0, 1);
	glVertex3f(2, 6, -4.25);
	glTexCoord2f(1, 1);
	glVertex3f(2.5, 3, -1.5);
	glEnd();

	glBegin(GL_POLYGON);
	//right
	glTexCoord2f(0, 0);
	glVertex3f(-1.5, 6, 0);
	glTexCoord2f(1, 0);
	glVertex3f(-1.5, 10, -1);
	glTexCoord2f(1, 1);
	glVertex3f(-2, 8, -4.25);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 6, -4.25);
	glTexCoord2f(1, 1);
	glVertex3f(-2.5, 3, -1.5);
	glEnd();

	glBegin(GL_QUADS);
	//back
	glTexCoord2f(0, 0);
	glVertex3f(2, 6, -4.25);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 6, -4.25);
	glTexCoord2f(1, 1);
	glVertex3f(-2, 8, -4.25);
	glTexCoord2f(0, 1);
	glVertex3f(2, 8, -4.25);
	glEnd();

	//-----------------------------top front part
	glBindTexture(GL_TEXTURE_2D, textureMetalGrey);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, darkBlue);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, darkBlue);
	glColor3f(darkBlue[0], darkBlue[1], darkBlue[2]);
	glBegin(GL_QUADS);
	//horizontal part
	//front
	glTexCoord2f(0, 0);
	glVertex3f(1.5, 12.5, 0);
	glTexCoord2f(1, 0);
	glVertex3f(-1.5, 12.5, 0);
	glTexCoord2f(1, 1);
	glVertex3f(-1.5, 10.5, 0);
	glTexCoord2f(0, 1);
	glVertex3f(1.5, 10.5, 0);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(2, 13, -1);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 13, -1);
	glTexCoord2f(1, 1);
	glVertex3f(-2, 10, -1);
	glTexCoord2f(0, 1);
	glVertex3f(2, 10, -1);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(2, 13, -1);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 13, -1);
	glTexCoord2f(1, 1);
	glVertex3f(-2, 12.5, 0);
	glTexCoord2f(0, 1);
	glVertex3f(2, 12.5, 0);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(2, 10, -1);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 10, -1);
	glTexCoord2f(1, 1);
	glVertex3f(-2, 10.5, 0);
	glTexCoord2f(0, 1);
	glVertex3f(2, 10.5, 0);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(2, 13, -1);
	glTexCoord2f(1, 0);
	glVertex3f(2, 12.5, 0);
	glTexCoord2f(1, 1);
	glVertex3f(2, 10.5, 0);
	glTexCoord2f(0, 1);
	glVertex3f(2, 10, -1);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(-2, 13, -1);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 12.5, 0);
	glTexCoord2f(1, 1);
	glVertex3f(-2, 10.5, 0);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 10, -1);

	//vertical part
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, indigo);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, indigo);
	glColor3f(indigo[0], indigo[1], indigo[2]);
	//front
	glTexCoord2f(0, 0);
	glVertex3f(1, 9, 0.25);
	glTexCoord2f(1, 0);
	glVertex3f(-1, 9, 0.25);
	glTexCoord2f(1, 1);
	glVertex3f(-1, 14, 0.25);
	glTexCoord2f(0, 1);
	glVertex3f(1, 14, 0.25);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(1, 14, -0.75);
	glTexCoord2f(1, 0);
	glVertex3f(-1, 14, -0.75);
	glTexCoord2f(1, 1);
	glVertex3f(-1, 14, 0.25);
	glTexCoord2f(0, 1);
	glVertex3f(1, 14, 0.25);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(1, 9, -1);
	glTexCoord2f(1, 0);
	glVertex3f(-1, 9, -1);
	glTexCoord2f(1, 1);
	glVertex3f(-1, 9, 0.25);
	glTexCoord2f(0, 1);
	glVertex3f(1, 9, 0.25);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(1, 9, 0.25);
	glTexCoord2f(1, 0);
	glVertex3f(1, 14, 0.25);
	glTexCoord2f(1, 1);
	glVertex3f(1, 14, -0.75);
	glTexCoord2f(0, 1);
	glVertex3f(1, 9, -0.75);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(-1, 9, 0.25);
	glTexCoord2f(1, 0);
	glVertex3f(-1, 14, 0.25);
	glTexCoord2f(1, 1);
	glVertex3f(-1, 14, -0.75);
	glTexCoord2f(0, 1);
	glVertex3f(-1, 9, -0.75);
	glEnd();

	//-----------------------------right part
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, darkBlue);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, darkBlue);
	glColor3f(darkBlue[0], darkBlue[1], darkBlue[2]);
	glBegin(GL_POLYGON);
	//right
	glTexCoord2f(0, 0);
	glVertex3f(-2, 13, -1);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 13, -3);
	glTexCoord2f(1, 1);
	glVertex3f(-2, 10, -3.5);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 8, -3);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 8, -1);
	glTexCoord2f(1, 1);
	glVertex3f(-2, 10, -0.5);
	glEnd();

	glBegin(GL_POLYGON);
	//front
	glTexCoord2f(0, 0);
	glVertex3f(-2, 13, -1);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 10, -0.5);
	glTexCoord2f(1, 1);
	glVertex3f(-2, 8, -1);
	glTexCoord2f(0, 1);
	glVertex3f(-1, 8, -1);
	glTexCoord2f(0, 0);
	glVertex3f(-1, 10, -0.5);
	glTexCoord2f(1, 0);
	glVertex3f(-1, 13, -1);
	glEnd();

	glBegin(GL_POLYGON);
	//back
	glTexCoord2f(0, 0);
	glVertex3f(-2, 13, -3);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 10, -3.5);
	glTexCoord2f(1, 1);
	glVertex3f(-2, 8, -3);
	glTexCoord2f(0, 1);
	glVertex3f(-1, 8, -3);
	glTexCoord2f(1, 1);
	glVertex3f(-1, 10, -3.5);
	glTexCoord2f(0, 1);
	glVertex3f(-1, 13, -3);
	glEnd();

	glBegin(GL_QUADS);
	//top
	glTexCoord2f(0, 0);
	glVertex3f(-2, 13, -1);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 13, -3);
	glTexCoord2f(1, 1);
	glVertex3f(-1, 13, -3);
	glTexCoord2f(0, 1);
	glVertex3f(-1, 13, -1);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-2, 8, -1);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 8, -3);
	glTexCoord2f(1, 1);
	glVertex3f(-1, 8, -3);
	glTexCoord2f(0, 1);
	glVertex3f(-1, 8, -1);
	glEnd();

	//-----------------------------left part
	glColor3f(darkBlue[0], darkBlue[1], darkBlue[2]);
	glBegin(GL_POLYGON);
	//right
	glTexCoord2f(0, 0);
	glVertex3f(2, 13, -1.5);
	glTexCoord2f(1, 0);
	glVertex3f(2, 13, -3.5);
	glTexCoord2f(1, 1);
	glVertex3f(2, 10, -4);
	glTexCoord2f(0, 1);
	glVertex3f(2, 8, -3.5);
	glTexCoord2f(0, 0);
	glVertex3f(2, 8, -1.5);
	glTexCoord2f(1, 0);
	glVertex3f(2, 10, -0.5);
	glEnd();

	glBegin(GL_POLYGON);
	//front
	glTexCoord2f(0, 0);
	glVertex3f(2, 13, -1.5);
	glTexCoord2f(1, 0);
	glVertex3f(2, 10, -0.5);
	glTexCoord2f(1, 1);
	glVertex3f(2, 8, -1.5);
	glTexCoord2f(0, 1);
	glVertex3f(1, 8, -1.5);
	glTexCoord2f(0, 0);
	glVertex3f(1, 10, -0.5);
	glTexCoord2f(1, 0);
	glVertex3f(1, 13, -1.5);
	glEnd();

	glBegin(GL_POLYGON);
	//back
	glTexCoord2f(0, 0);
	glVertex3f(2, 13, -3.5);
	glTexCoord2f(1, 0);
	glVertex3f(2, 10, -4);
	glTexCoord2f(1, 1);
	glVertex3f(2, 8, -3.5);
	glTexCoord2f(0, 1);
	glVertex3f(1, 8, -3.5);
	glTexCoord2f(0, 0);
	glVertex3f(1, 10, -4);
	glTexCoord2f(1, 0);
	glVertex3f(1, 13, -3.5);
	glEnd();

	glBegin(GL_QUADS);
	//top
	glTexCoord2f(0, 0);
	glVertex3f(2, 13, -1.5);
	glTexCoord2f(1, 0);
	glVertex3f(2, 13, -3.5);
	glTexCoord2f(1, 1);
	glVertex3f(1, 13, -3.5);
	glTexCoord2f(0, 1);
	glVertex3f(1, 13, -1.5);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(2, 8, -1.5);
	glTexCoord2f(1, 0);
	glVertex3f(2, 8, -3.5);
	glTexCoord2f(1, 1);
	glVertex3f(1, 8, -3.5);
	glTexCoord2f(0, 1);
	glVertex3f(1, 8, -1.5);

	//-----------front part
	//left
	glTexCoord2f(0, 0);
	glVertex3f(3, 14, -2);
	glTexCoord2f(1, 0);
	glVertex3f(3, 14, -3);
	glTexCoord2f(1, 1);
	glVertex3f(3, 5, -3);
	glTexCoord2f(0, 1);
	glVertex3f(3, 5, -2);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(3, 14, -3);
	glTexCoord2f(1, 0);
	glVertex3f(2, 14, -3);
	glTexCoord2f(1, 1);
	glVertex3f(2, 5, -3);
	glTexCoord2f(0, 1);
	glVertex3f(3, 5, -3);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(3, 14, -2);
	glTexCoord2f(1, 0);
	glVertex3f(2, 14, -2);
	glTexCoord2f(1, 1);
	glVertex3f(2, 5, -2);
	glTexCoord2f(0, 1);
	glVertex3f(3, 5, -2);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(3, 14, -2);
	glTexCoord2f(1, 0);
	glVertex3f(3, 14, -3);
	glTexCoord2f(1, 1);
	glVertex3f(2, 14, -3);
	glTexCoord2f(0, 1);
	glVertex3f(2, 14, -2);
	glEnd();

	//-----------------------------back part
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, indigo);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, indigo);
	glColor3f(indigo[0], indigo[1], indigo[2]);
	glBegin(GL_QUADS);
	//front
	glTexCoord2f(0, 0);
	glVertex3f(1.5, 7.5, -6);
	glTexCoord2f(1, 0);
	glVertex3f(-1.5, 7.5, -6);
	glTexCoord2f(1, 1);
	glVertex3f(-1.5, 11.5, -6);
	glTexCoord2f(0, 1);
	glVertex3f(1.5, 11.5, -6);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(1.75, 7, -4);
	glTexCoord2f(1, 0);
	glVertex3f(-1.75, 7, -4);
	glTexCoord2f(1, 1);
	glVertex3f(-1.75, 12, -4.25);
	glTexCoord2f(0, 1);
	glVertex3f(1.75, 12, -4.25);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(1.5, 11.5, -6);
	glTexCoord2f(1, 0);
	glVertex3f(-1.5, 11.5, -6);
	glTexCoord2f(1, 1);
	glVertex3f(-1.75, 12, -4.25);
	glTexCoord2f(0, 1);
	glVertex3f(1.75, 12, -4.25);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(1.5, 7.5, -6);
	glTexCoord2f(1, 0);
	glVertex3f(-1.5, 7.5, -6);
	glTexCoord2f(1, 1);
	glVertex3f(-1.75, 7, -4);
	glTexCoord2f(0, 1);
	glVertex3f(1.75, 7, -4);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(1.75, 12, -4.25);
	glTexCoord2f(1, 0);
	glVertex3f(1.75, 7, -4);
	glTexCoord2f(1, 1);
	glVertex3f(1.5, 7.5, -6);
	glTexCoord2f(0, 1);
	glVertex3f(1.5, 11.5, -6);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(-1.75, 12, -4.25);
	glTexCoord2f(1, 0);
	glVertex3f(-1.75, 7, -4);
	glTexCoord2f(1, 1);
	glVertex3f(-1.5, 7.5, -6);
	glTexCoord2f(0, 1);
	glVertex3f(-1.5, 11.5, -6);
	glEnd();

#pragma endregion shield

#pragma region join
	glBindTexture(GL_TEXTURE_2D, textureBlackCore);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, grey);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, grey);
	glColor3f(grey[0], grey[1], grey[2]);
	glBegin(GL_QUADS);
	//top
	glTexCoord2f(0, 0);
	glVertex3f(1, 15, -3);
	glTexCoord2f(0, 0);
	glVertex3f(-1, 15, -3);
	glTexCoord2f(0, 0);
	glVertex3f(-1, 13, -1);
	glTexCoord2f(0, 0);
	glVertex3f(1, 13, -1);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(1, 15, -3);
	glTexCoord2f(1, 0);
	glVertex3f(-1, 15, -3);
	glTexCoord2f(1, 1);
	glVertex3f(-1, 10, -4);
	glTexCoord2f(0, 1);
	glVertex3f(1, 10, -4);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(1, 15, -3);
	glTexCoord2f(1, 0);
	glVertex3f(1, 13, -1);
	glTexCoord2f(1, 1);
	glVertex3f(1, 10, -1);
	glTexCoord2f(0, 1);
	glVertex3f(1, 10, -4);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(-1, 15, -3);
	glTexCoord2f(1, 0);
	glVertex3f(-1, 13, -1);
	glTexCoord2f(1, 1);
	glVertex3f(-1, 10, -1);
	glTexCoord2f(0, 1);
	glVertex3f(-1, 10, -4);
	glEnd();
#pragma endregion join
	glPopMatrix();
}

void rightUpperLeg() {
	glPushMatrix();
#pragma region core
	glBindTexture(GL_TEXTURE_2D, textureRubberGrey);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, silver);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, silver);
	glColor3f(silver[0], silver[1], silver[2]);
	glBegin(GL_QUADS);
	//back
	glTexCoord2f(0, 0);
	glVertex3f(1, 15, -3.5);
	glTexCoord2f(1, 0);
	glVertex3f(-1, 15, -3.5);
	glTexCoord2f(1, 1);
	glVertex3f(-2, 22, -4);
	glTexCoord2f(0, 1);
	glVertex3f(2, 22, -4);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(1.5, 12.75, -1);
	glTexCoord2f(1, 0);
	glVertex3f(-1.5, 12.75, -1);
	glTexCoord2f(1, 1);
	glVertex3f(-2, 22, -0);
	glTexCoord2f(0, 1);
	glVertex3f(2, 22, -0);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(1.5, 12.75, -1);
	glTexCoord2f(1, 0);
	glVertex3f(1, 15, -3.5);
	glTexCoord2f(1, 1);
	glVertex3f(2, 22, -4);
	glTexCoord2f(0, 1);
	glVertex3f(2, 22, -0);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(-1.5, 12.75, -1);
	glTexCoord2f(1, 0);
	glVertex3f(-1, 15, -3.5);
	glTexCoord2f(1, 1);
	glVertex3f(-2, 22, -4);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 22, -0);
	glEnd();
#pragma endregion core
#pragma region frontShield
	glBindTexture(GL_TEXTURE_2D, textureBlackCore);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, indigo);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, indigo);
	glColor3f(indigo[0], indigo[1], indigo[2]);
	glBegin(GL_POLYGON);
	//back
	glTexCoord2f(0, 0);
	glVertex3f(2, 20, 0);
	glTexCoord2f(1, 0);
	glVertex3f(-1.75, 20, 0);
	glTexCoord2f(1, 1);
	glVertex3f(-2, 21, 0);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 28, 0);
	glTexCoord2f(1, 1);
	glVertex3f(2, 28, 0);
	glEnd();

	glBegin(GL_POLYGON);
	//front
	glTexCoord2f(0, 0);
	glVertex3f(2, 20, 1);
	glTexCoord2f(1, 0);
	glVertex3f(-1.75, 20, 1);
	glTexCoord2f(1, 1);
	glVertex3f(-2, 21, 1);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 28, 1);
	glTexCoord2f(1, 1);
	glVertex3f(2, 28, 1);
	glEnd();

	glBegin(GL_QUADS);
	//top
	glTexCoord2f(0, 0);
	glVertex3f(2, 28, 0);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 28, 0);
	glTexCoord2f(1, 1);
	glVertex3f(-2, 28, 1);
	glTexCoord2f(0, 1);
	glVertex3f(2, 28, 1);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(2, 20, 0);
	glTexCoord2f(1, 0);
	glVertex3f(-1.5, 20, 0);
	glTexCoord2f(1, 1);
	glVertex3f(-1.5, 20, 1);
	glTexCoord2f(0, 1);
	glVertex3f(2, 20, 1);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(2, 20, 0);
	glTexCoord2f(1, 0);
	glVertex3f(2, 20, 1);
	glTexCoord2f(1, 1);
	glVertex3f(2, 28, 1);
	glTexCoord2f(0, 1);
	glVertex3f(2, 28, 0);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(-2, 21, 0);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 21, 1);
	glTexCoord2f(1, 1);
	glVertex3f(-2, 28, 1);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 28, 0);

	glTexCoord2f(0, 0);
	glVertex3f(-1.5, 20, 0);
	glTexCoord2f(1, 0);
	glVertex3f(-1.5, 20, 1);
	glTexCoord2f(1, 1);
	glVertex3f(-2, 21, 1);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 21, 0);
	glEnd();

	//------------------------------front part
	glBindTexture(GL_TEXTURE_2D, textureMetalBlueShine);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, darkBlue);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, darkBlue);
	glColor3f(darkBlue[0], darkBlue[1], darkBlue[2]);
	glBegin(GL_POLYGON);
	//front
	glTexCoord2f(0, 0);
	glVertex3f(1.75, 27.5, 2);
	glTexCoord2f(1, 0);
	glVertex3f(-1.75, 27.5, 2);
	glTexCoord2f(1, 1);
	glVertex3f(-1.75, 23, 2);
	glTexCoord2f(0, 1);
	glVertex3f(-1.25, 22, 2);
	glTexCoord2f(1, 1);
	glVertex3f(1.75, 22, 2);
	glEnd();

	glBegin(GL_QUADS);
	//top
	glTexCoord2f(0, 0);
	glVertex3f(1.75, 27.5, 1);
	glTexCoord2f(1, 0);
	glVertex3f(-1.75, 27.5, 1);
	glTexCoord2f(1, 1);
	glVertex3f(-1.75, 27.5, 2);
	glTexCoord2f(0, 1);
	glVertex3f(1.75, 27.5, 2);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(1.75, 22, 1);
	glTexCoord2f(1, 0);
	glVertex3f(-1.25, 22, 1);
	glTexCoord2f(1, 1);
	glVertex3f(-1.25, 22, 2);
	glTexCoord2f(0, 1);
	glVertex3f(1.75, 22, 2);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(1.75, 22, 1);
	glTexCoord2f(1, 0);
	glVertex3f(1.75, 22, 2);
	glTexCoord2f(1, 1);
	glVertex3f(1.75, 27.5, 2);
	glTexCoord2f(0, 1);
	glVertex3f(1.75, 27.5, 1);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(-1.75, 23, 1);
	glTexCoord2f(1, 0);
	glVertex3f(-1.75, 23, 2);
	glTexCoord2f(1, 1);
	glVertex3f(-1.75, 27.5, 2);
	glTexCoord2f(0, 1);
	glVertex3f(-1.75, 27.5, 1);

	glTexCoord2f(0, 0);
	glVertex3f(-1.25, 22, 1);
	glTexCoord2f(1, 0);
	glVertex3f(-1.25, 22, 2);
	glTexCoord2f(1, 1);
	glVertex3f(-1.75, 23, 2);
	glTexCoord2f(0, 1);
	glVertex3f(-1.75, 23, 1);
	glEnd();

#pragma endregion frontShield
#pragma region sideShield
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, indigo);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, indigo);
	glColor3f(indigo[0], indigo[1], indigo[2]);
	glBegin(GL_POLYGON);
	//left
	glTexCoord2f(0, 0);
	glVertex3f(-2, 28, 0);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 21, 0);
	glTexCoord2f(1, 1);
	glVertex3f(-2, 20, -1);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 20, -3);
	glTexCoord2f(0, 0);
	glVertex3f(-2, 21, -4);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 28, -4);
	glEnd();

	glBegin(GL_POLYGON);
	//right
	glTexCoord2f(0, 0);
	glVertex3f(-3, 28, 0);
	glTexCoord2f(1, 0);
	glVertex3f(-3, 21, 0);
	glTexCoord2f(1, 1);
	glVertex3f(-3, 20, -1);
	glTexCoord2f(0, 1);
	glVertex3f(-3, 20, -3);
	glTexCoord2f(0, 0);
	glVertex3f(-3, 21, -4);
	glTexCoord2f(1, 0);
	glVertex3f(-3, 28, -4);
	glEnd();

	glBegin(GL_QUADS);
	//front
	glTexCoord2f(0, 0);
	glVertex3f(-2, 28, 0);
	glTexCoord2f(1, 0);
	glVertex3f(-3, 28, 0);
	glTexCoord2f(1, 1);
	glVertex3f(-3, 21, 0);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 21, 0);

	//front bottom
	glTexCoord2f(0, 0);
	glVertex3f(-3, 21, 0);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 21, 0);
	glTexCoord2f(1, 1);
	glVertex3f(-2, 20, -1);
	glTexCoord2f(0, 1);
	glVertex3f(-3, 20, -1);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-3, 20, -1);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 20, -1);
	glTexCoord2f(1, 1);
	glVertex3f(-2, 20, -3);
	glTexCoord2f(0, 1);
	glVertex3f(-3, 20, -3);

	//back bottom
	glTexCoord2f(0, 0);
	glVertex3f(-3, 21, -4);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 21, -4);
	glTexCoord2f(1, 1);
	glVertex3f(-2, 20, -3);
	glTexCoord2f(0, 1);
	glVertex3f(-3, 20, -3);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(-2, 28, -4);
	glTexCoord2f(1, 0);
	glVertex3f(-3, 28, -4);
	glTexCoord2f(1, 1);
	glVertex3f(-3, 21, -4);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 21, -4);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-2, 28, 0);
	glTexCoord2f(1, 0);
	glVertex3f(-3, 28, 0);
	glTexCoord2f(1, 1);
	glVertex3f(-3, 28, -4);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 28, -4);
	glEnd();

	//------------------------------side part
	glBindTexture(GL_TEXTURE_2D, textureMetalGrey);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, grey);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, grey);
	glColor3f(grey[0], grey[1], grey[2]);
	glBegin(GL_QUADS);
	//top
	glTexCoord2f(0, 0);
	glVertex3f(-3, 28, -1);
	glTexCoord2f(1, 0);
	glVertex3f(-3, 28, -3);
	glTexCoord2f(1, 1);
	glVertex3f(-3.5, 28, -3);
	glTexCoord2f(0, 1);
	glVertex3f(-3.5, 28, -1);

	//top right
	glTexCoord2f(0, 0);
	glVertex3f(-3.5, 28, -1);
	glTexCoord2f(1, 0);
	glVertex3f(-3.5, 28, -3);
	glTexCoord2f(1, 1);
	glVertex3f(-4, 27, -3);
	glTexCoord2f(0, 1);
	glVertex3f(-4, 27, -1);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(-4, 27, -3);
	glTexCoord2f(1, 0);
	glVertex3f(-4, 27, -1);
	glTexCoord2f(1, 1);
	glVertex3f(-4, 24, -1);
	glTexCoord2f(0, 1);
	glVertex3f(-4, 24, -3);

	//bottom left
	glTexCoord2f(0, 0);
	glVertex3f(-3.5, 23, -1);
	glTexCoord2f(1, 0);
	glVertex3f(-3.5, 23, -3);
	glTexCoord2f(1, 1);
	glVertex3f(-4, 24, -3);
	glTexCoord2f(0, 1);
	glVertex3f(-4, 24, -1);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-3, 23, -1);
	glTexCoord2f(1, 0);
	glVertex3f(-3, 23, -3);
	glTexCoord2f(1, 1);
	glVertex3f(-3.5, 23, -3);
	glTexCoord2f(0, 1);
	glVertex3f(-3.5, 23, -1);
	glEnd();

	glBegin(GL_POLYGON);
	//front
	glTexCoord2f(0, 0);
	glVertex3f(-3, 28, -1);
	glTexCoord2f(1, 0);
	glVertex3f(-3.5, 28, -1);
	glTexCoord2f(1, 1);
	glVertex3f(-4, 27, -1);
	glTexCoord2f(0, 1);
	glVertex3f(-4, 24, -1);
	glTexCoord2f(0, 0);
	glVertex3f(-3.5, 23, -1);
	glTexCoord2f(1, 0);
	glVertex3f(-3, 23, -1);
	glEnd();

	glBegin(GL_POLYGON);
	//back
	glTexCoord2f(0, 0);
	glVertex3f(-3, 28, -3);
	glTexCoord2f(1, 0);
	glVertex3f(-3.5, 28, -3);
	glTexCoord2f(1, 1);
	glVertex3f(-4, 27, -3);
	glTexCoord2f(0, 1);
	glVertex3f(-4, 24, -3);
	glTexCoord2f(0, 0);
	glVertex3f(-3.5, 23, -3);
	glTexCoord2f(1, 0);
	glVertex3f(-3, 23, -3);
	glEnd();
#pragma endregion sideShield
	glPopMatrix();
}

void rocketLeftPart() {
	//front
	glBindTexture(GL_TEXTURE_2D, textureMetalBlueShine);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, indigo);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, indigo);
	glColor3f(indigo[0], indigo[1], indigo[2]);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);
	glVertex3f(1, 12, -1);
	glTexCoord2f(1, 0);
	glVertex3f(1, 16, -1);
	glTexCoord2f(1, 1);
	glVertex3f(2, 16, -1);
	glTexCoord2f(1, 1);
	glVertex3f(2, 0, -1);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 0, -1);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 8, -1);
	glEnd();

	//back
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);
	glVertex3f(1, 12, 0);
	glTexCoord2f(1, 0);
	glVertex3f(1, 16, 0);
	glTexCoord2f(1, 1);
	glVertex3f(2, 16, 0);
	glTexCoord2f(0, 1);
	glVertex3f(2, 0, 0);
	glTexCoord2f(0, 0);
	glVertex3f(-2, 0, 0);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 8, 0);
	glEnd();

	glBegin(GL_QUADS);
	//left
	glTexCoord2f(0, 0);
	glVertex3f(2, 16, -1);
	glTexCoord2f(1, 0);
	glVertex3f(2, 16, 0);
	glTexCoord2f(1, 1);
	glVertex3f(2, 0, 0);
	glTexCoord2f(0, 1);
	glVertex3f(2, 0, -1);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(1, 12, -1);
	glTexCoord2f(1, 0);
	glVertex3f(1, 12, 0);
	glTexCoord2f(1, 1);
	glVertex3f(1, 16, 0);
	glTexCoord2f(0, 1);
	glVertex3f(1, 16, -1);

	glTexCoord2f(0, 0);
	glVertex3f(1, 12, -1);
	glTexCoord2f(1, 0);
	glVertex3f(1, 12, 0);
	glTexCoord2f(1, 1);
	glVertex3f(-2, 8, 0);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 8, -1);

	glTexCoord2f(0, 0);
	glVertex3f(-2, 8, -1);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 8, 0);
	glTexCoord2f(1, 1);
	glVertex3f(-2, 0, 0);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 0, -1);

	//top 
	glTexCoord2f(0, 0);
	glVertex3f(2, 16, -1);
	glTexCoord2f(1, 0);
	glVertex3f(2, 16, 0);
	glTexCoord2f(1, 1);
	glVertex3f(1, 16, 0);
	glTexCoord2f(0, 1);
	glVertex3f(1, 16, -1);

	glTexCoord2f(0, 0);
	glVertex3f(-2, 8, -1);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 8, 0);
	glTexCoord2f(1, 1);
	glVertex3f(1, 12, 0);
	glTexCoord2f(0, 1);
	glVertex3f(1, 12, -1);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(2, 0, -1);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 0, 0);
	glTexCoord2f(1, 1);
	glVertex3f(-2, 0, 0);
	glTexCoord2f(0, 1);
	glVertex3f(2, 0, -1);
	glEnd();

	//line
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, red);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, red);
	glColor3f(1, 0, 0);
	glLineWidth(6);
	glBindTexture(GL_TEXTURE_2D, textureRedLamp);
	glBegin(GL_LINES);
	glTexCoord2f(0, 0);
	glVertex3f(-2, 0, -0.5);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 6, -0.5);
	glEnd();
}

void rocketRightPart() {
	glBindTexture(GL_TEXTURE_2D, textureMetalBlueShine);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, indigo);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, indigo);
	glColor3f(indigo[0], indigo[1], indigo[2]);
	//front
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);
	glVertex3f(-1, 12, -1);
	glTexCoord2f(1, 0);
	glVertex3f(-1, 16, -1);
	glTexCoord2f(1, 1);
	glVertex3f(-2, 16, -1);
	glTexCoord2f(1, 1);
	glVertex3f(-2, 0, -1);
	glTexCoord2f(0, 1);
	glVertex3f(2, 0, -1);
	glTexCoord2f(1, 0);
	glVertex3f(2, 8, -1);
	glEnd();

	//back
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);
	glVertex3f(-1, 12, 0);
	glTexCoord2f(1, 0);
	glVertex3f(-1, 16, 0);
	glTexCoord2f(1, 1);
	glVertex3f(-2, 16, 0);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 0, 0);
	glTexCoord2f(0, 0);
	glVertex3f(2, 0, 0);
	glTexCoord2f(1, 0);
	glVertex3f(2, 8, 0);
	glEnd();

	glBegin(GL_QUADS);
	//left
	glTexCoord2f(0, 0);
	glVertex3f(-2, 16, -1);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 16, 0);
	glTexCoord2f(1, 1);
	glVertex3f(-2, 0, 0);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 0, -1);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(-1, 12, -1);
	glTexCoord2f(1, 0);
	glVertex3f(-1, 12, 0);
	glTexCoord2f(1, 1);
	glVertex3f(-1, 16, 0);
	glTexCoord2f(0, 1);
	glVertex3f(-1, 16, -1);

	glTexCoord2f(0, 0);
	glVertex3f(-1, 12, -1);
	glTexCoord2f(1, 0);
	glVertex3f(-1, 12, 0);
	glTexCoord2f(1, 1);
	glVertex3f(2, 8, 0);
	glTexCoord2f(0, 1);
	glVertex3f(2, 8, -1);

	glTexCoord2f(0, 0);
	glVertex3f(2, 8, -1);
	glTexCoord2f(1, 0);
	glVertex3f(2, 8, 0);
	glTexCoord2f(1, 1);
	glVertex3f(2, 0, 0);
	glTexCoord2f(0, 1);
	glVertex3f(2, 0, -1);

	//top 
	glTexCoord2f(0, 0);
	glVertex3f(-2, 16, -1);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 16, 0);
	glTexCoord2f(1, 1);
	glVertex3f(-1, 16, 0);
	glTexCoord2f(0, 1);
	glVertex3f(-1, 16, -1);

	glTexCoord2f(0, 0);
	glVertex3f(2, 8, -1);
	glTexCoord2f(1, 0);
	glVertex3f(2, 8, 0);
	glTexCoord2f(1, 1);
	glVertex3f(-1, 12, 0);
	glTexCoord2f(0, 1);
	glVertex3f(-1, 12, -1);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-2, 0, -1);
	glTexCoord2f(1, 0);
	glVertex3f(2, 0, 0);
	glTexCoord2f(1, 1);
	glVertex3f(2, 0, 0);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 0, -1);
	glEnd();

	//line
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, red);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, red);
	glColor3f(1, 0, 0);
	glLineWidth(6);
	glBindTexture(GL_TEXTURE_2D, textureRedLamp);
	glBegin(GL_LINES);
	glTexCoord2f(0, 0);
	glVertex3f(2, 0, -0.5);
	glTexCoord2f(1, 0);
	glVertex3f(2, 6, -0.5);
	glEnd();
}

void jetpack() {
	glPushMatrix();
	//glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureMetalGrey);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, darkBlue);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, darkBlue);
	glColor3f(darkBlue[0], darkBlue[1], darkBlue[2]);
#pragma region core
	glBegin(GL_QUADS);
	//front
	glTexCoord2f(0, 0);
	glVertex3f(-3, 0, 0);
	glTexCoord2f(1, 0);
	glVertex3f(3, 0, 0);
	glTexCoord2f(1, 1);
	glVertex3f(3, 7, 0);
	glTexCoord2f(0, 1);
	glVertex3f(-3, 7, 0);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(-3, 2, -5);
	glTexCoord2f(1, 0);
	glVertex3f(3, 2, -5);
	glTexCoord2f(1, 1);
	glVertex3f(3, 7, -4);
	glTexCoord2f(0, 1);
	glVertex3f(-3, 7, -4);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-3, 7, 0);
	glTexCoord2f(1, 0);
	glVertex3f(3, 7, 0);
	glTexCoord2f(1, 1);
	glVertex3f(3, 7, -4);
	glTexCoord2f(0, 1);
	glVertex3f(-3, 7, -4);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-3, 0, 0);
	glTexCoord2f(1, 0);
	glVertex3f(3, 0, 0);
	glTexCoord2f(1, 1);
	glVertex3f(3, 2, -5);
	glTexCoord2f(0, 1);
	glVertex3f(-3, 2, -5);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-3, 0, 0);
	glTexCoord2f(1, 0);
	glVertex3f(-3, 2, -5);
	glTexCoord2f(1, 1);
	glVertex3f(-3, 7, -4);
	glTexCoord2f(0, 1);
	glVertex3f(-3, 7, 0);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(3, 0, 0);
	glTexCoord2f(1, 0);
	glVertex3f(3, 2, -5);
	glTexCoord2f(1, 1);
	glVertex3f(3, 7, -4);
	glTexCoord2f(0, 1);
	glVertex3f(3, 7, 0);

	//----------------------------bottom part
	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-2, -1, -1);
	glTexCoord2f(1, 0);
	glVertex3f(2, -1, -1);
	glTexCoord2f(1, 1);
	glVertex3f(2, -1, -3);
	glTexCoord2f(0, 1);
	glVertex3f(-2, -1, -3);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(-3, 0.25, -0.25);
	glTexCoord2f(1, 0);
	glVertex3f(3, 0.25, -0.25);
	glTexCoord2f(1, 1);
	glVertex3f(2, -1, -1);
	glTexCoord2f(0, 1);
	glVertex3f(-2, -1, -1);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(-3, 2, -4.55);
	glTexCoord2f(1, 0);
	glVertex3f(3, 2, -5);
	glTexCoord2f(1, 1);
	glVertex3f(2, -1, -3);
	glTexCoord2f(0, 1);
	glVertex3f(-2, -1, -3);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-3, 2, -4.5);
	glTexCoord2f(1, 0);
	glVertex3f(-2, -1, -3);
	glTexCoord2f(1, 1);
	glVertex3f(-2, -1, -1);
	glTexCoord2f(0, 1);
	glVertex3f(-3, 0.25, -0.25);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(3, 2, -4.5);
	glTexCoord2f(1, 0);
	glVertex3f(2, -1, -3);
	glTexCoord2f(1, 1);
	glVertex3f(2, -1, -1);
	glTexCoord2f(0, 1);
	glVertex3f(3, 0.25, -0.25);
	glEnd();
#pragma endregion core
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, red);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, red);
	glColor3f(1, 0, 0);
#pragma region midRocket
	glBegin(GL_QUADS);
	//top
	glTexCoord2f(0, 0);
	glVertex3f(-2, 4, -3);
	glTexCoord2f(1, 0);
	glVertex3f(2, 4, -3);
	glTexCoord2f(1, 1);
	glVertex3f(2, 4, -6);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 4, -6);

	//front top
	glTexCoord2f(0, 0);
	glVertex3f(-2, 2, -6.5);
	glTexCoord2f(1, 0);
	glVertex3f(2, 2, -6.5);
	glTexCoord2f(1, 1);
	glVertex3f(2, 4, -6);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 4, -6);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(-2, 2, -6.5);
	glTexCoord2f(1, 0);
	glVertex3f(2, 2, -6.5);
	glTexCoord2f(1, 1);
	glVertex3f(2, 0, -5);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 0, -5);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-2, 2, -3);
	glTexCoord2f(1, 0);
	glVertex3f(2, 2, -3);
	glTexCoord2f(1, 1);
	glVertex3f(2, 0, -5);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 0, -5);
	glEnd();

	//left
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);
	glVertex3f(-2, 4, -3);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 4, -6);
	glTexCoord2f(1, 1);
	glVertex3f(-2, 2, -6.5);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 0, -5);
	glTexCoord2f(0, 0);
	glVertex3f(-2, 0, -5);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 2, -3);
	glEnd();

	//right
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);
	glVertex3f(2, 4, -3);
	glTexCoord2f(1, 0);
	glVertex3f(2, 4, -6);
	glTexCoord2f(1, 1);
	glVertex3f(2, 2, -6.5);
	glTexCoord2f(0, 1);
	glVertex3f(2, 0, -5);
	glTexCoord2f(0, 0);
	glVertex3f(2, 0, -5);
	glTexCoord2f(1, 0);
	glVertex3f(2, 2, -3);
	glEnd();
#pragma endregion midRocket

#pragma region leftRocket
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, indigo);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, indigo);
	glColor3f(indigo[0], indigo[1], indigo[2]);
	glBegin(GL_POLYGON);
	//left
	glTexCoord2f(0, 0);
	glVertex3f(-3, 2, -6);
	glTexCoord2f(1, 0);
	glVertex3f(-3, 9, -3);
	glTexCoord2f(1, 1);
	glVertex3f(-3, 9, -1);
	glTexCoord2f(0, 1);
	glVertex3f(-3, 2, -1);
	glTexCoord2f(1, 1);
	glVertex3f(-3, 1, -3);
	glEnd();

	glBegin(GL_POLYGON);
	//right
	glTexCoord2f(0, 0);
	glVertex3f(-4, 2, -6);
	glTexCoord2f(1, 0);
	glVertex3f(-4, 9, -3);
	glTexCoord2f(1, 1);
	glVertex3f(-4, 9, -1);
	glTexCoord2f(0, 1);
	glVertex3f(-4, 2, -1);
	glTexCoord2f(1, 1);
	glVertex3f(-4, 1, -3);
	glEnd();

	glBegin(GL_QUADS);
	//front
	glTexCoord2f(0, 0);
	glVertex3f(-3, 2, -6);
	glTexCoord2f(1, 0);
	glVertex3f(-3, 9, -3);
	glTexCoord2f(1, 1);
	glVertex3f(-4, 9, -3);
	glTexCoord2f(0, 1);
	glVertex3f(-4, 2, -6);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(-3, 2, -1);
	glTexCoord2f(1, 0);
	glVertex3f(-3, 9, -1);
	glTexCoord2f(1, 1);
	glVertex3f(-4, 9, -1);
	glTexCoord2f(0, 1);
	glVertex3f(-4, 2, -1);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-3, 1, -3);
	glTexCoord2f(1, 0);
	glVertex3f(-3, 2, -6);
	glTexCoord2f(1, 1);
	glVertex3f(-4, 2, -6);
	glTexCoord2f(0, 1);
	glVertex3f(-4, 1, -3);

	glTexCoord2f(0, 0);
	glVertex3f(-3, 1, -3);
	glTexCoord2f(1, 0);
	glVertex3f(-3, 2, -1);
	glTexCoord2f(1, 1);
	glVertex3f(-4, 2, -1);
	glTexCoord2f(0, 1);
	glVertex3f(-4, 1, -3);

	//----------------------------layer2
	//right
	glTexCoord2f(0, 0);
	glVertex3f(-4, 12, -3);
	glTexCoord2f(1, 0);
	glVertex3f(-4, 9, -3);
	glTexCoord2f(1, 1);
	glVertex3f(-4, 9, -1);
	glTexCoord2f(0, 1);
	glVertex3f(-4, 12, -1);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-3, 12, -3);
	glTexCoord2f(1, 0);
	glVertex3f(-3, 9, -3);
	glTexCoord2f(1, 1);
	glVertex3f(-3, 9, -1);
	glTexCoord2f(0, 1);
	glVertex3f(-3, 12, -1);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(-3, 9, -3);
	glTexCoord2f(1, 0);
	glVertex3f(-4, 9, -3);
	glTexCoord2f(1, 1);
	glVertex3f(-4, 12, -3);
	glTexCoord2f(0, 1);
	glVertex3f(-3, 12, -3);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(-3, 9, -1);
	glTexCoord2f(1, 0);
	glVertex3f(-4, 9, -1);
	glTexCoord2f(1, 1);
	glVertex3f(-4, 12, -1);
	glTexCoord2f(0, 1);
	glVertex3f(-3, 12, -1);

	//-------------------------------layer3
	//top
	glTexCoord2f(0, 0);
	glVertex3f(-3, 17, -2);
	glTexCoord2f(1, 0);
	glVertex3f(-4, 17, -2);
	glTexCoord2f(1, 1);
	glVertex3f(-4, 17, -4);
	glTexCoord2f(0, 1);
	glVertex3f(-3, 17, -4);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(-3, 17, -4);
	glTexCoord2f(1, 0);
	glVertex3f(-4, 17, -4);
	glTexCoord2f(1, 1);
	glVertex3f(-4, 13, -4);
	glTexCoord2f(0, 1);
	glVertex3f(-3, 13, -4);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-3, 13, -2);
	glTexCoord2f(1, 0);
	glVertex3f(-4, 13, -2);
	glTexCoord2f(1, 1);
	glVertex3f(-4, 12, -1);
	glTexCoord2f(0, 1);
	glVertex3f(-3, 12, -1);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(-3, 17, -2);
	glTexCoord2f(1, 0);
	glVertex3f(-4, 17, -2);
	glTexCoord2f(1, 1);
	glVertex3f(-4, 12, -1);
	glTexCoord2f(0, 1);
	glVertex3f(-3, 12, -1);
	glEnd();

	glBegin(GL_POLYGON);
	//right
	glTexCoord2f(0, 0);
	glVertex3f(-4, 12, -3);
	glTexCoord2f(1, 0);
	glVertex3f(-4, 12, -1);
	glTexCoord2f(1, 1);
	glVertex3f(-4, 17, -2);
	glTexCoord2f(0, 1);
	glVertex3f(-4, 17, -4);
	glTexCoord2f(1, 1);
	glVertex3f(-4, 13, -4);
	glEnd();

	glBegin(GL_POLYGON);
	//left
	glTexCoord2f(0, 0);
	glVertex3f(-3, 12, -3);
	glTexCoord2f(1, 0);
	glVertex3f(-3, 12, -1);
	glTexCoord2f(1, 1);
	glVertex3f(-3, 17, -2);
	glTexCoord2f(0, 1);
	glVertex3f(-3, 17, -4);
	glTexCoord2f(1, 1);
	glVertex3f(-3, 13, -4);
	glEnd();

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, silver);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, silver);
	glColor3f(silver[0], silver[1], silver[2]);
	glPushMatrix();
	glTranslatef(-5, 4, -3);
	glRotatef(90, 0, 1, 0);
	gluQuadricTexture(obj, true);
	gluCylinder(obj, 1.5, 1.5, 2, 10, 2);
	glBegin(GL_POLYGON);
	glTranslatef(0, 0, 13);
	for (int i = 0; i < 360; i++) {
		glTexCoord2f((float)i / 360, (float)i / 360);
		glVertex2f(1.5 * cos(i), 1.5 * sin(i));
	}
	glEnd();
	glPopMatrix();

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, darkBlue);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, darkBlue);
	glColor3f(darkBlue[0], darkBlue[1], darkBlue[2]);
	glBegin(GL_QUADS);
	//left
	glTexCoord2f(0, 0);
	glVertex3f(-6, 4, -4);
	glTexCoord2f(1, 0);
	glVertex3f(-5, 2.5, -4);
	glTexCoord2f(1, 1);
	glVertex3f(-5, 5.5, -4);
	glTexCoord2f(0, 1);
	glVertex3f(-6, 5, -4);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(-6, 4, -2);
	glTexCoord2f(1, 0);
	glVertex3f(-5, 2.5, -2);
	glTexCoord2f(1, 1);
	glVertex3f(-5, 5.5, -2);
	glTexCoord2f(0, 1);
	glVertex3f(-6, 5, -2);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-6, 4, -2);
	glTexCoord2f(1, 0);
	glVertex3f(-5, 5.5, -2);
	glTexCoord2f(1, 1);
	glVertex3f(-5, 5.5, -4);
	glTexCoord2f(0, 1);
	glVertex3f(-6, 4, -4);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(-6, 4, -2);
	glTexCoord2f(1, 0);
	glVertex3f(-6, 4, -4);
	glTexCoord2f(1, 1);
	glVertex3f(-6, 5, -4);
	glTexCoord2f(0, 1);
	glVertex3f(-6, 5, -2);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-6, 4, -2);
	glTexCoord2f(1, 0);
	glVertex3f(-5, 2.5, -2);
	glTexCoord2f(1, 1);
	glVertex3f(-5, 2.5, -4);
	glTexCoord2f(0, 1);
	glVertex3f(-6, 4, -4);
	glEnd();

	glPushMatrix();

	glTranslatef(-6, 3.5, -2.5);
	glRotatef(rocketLeftRotateX, 1, 0, 0);
	glRotatef(20, 1, 0, 0);
	glRotatef(-20, 0, 0, 1);
	glTranslatef(-1, -16, 0);
	rocketLeftPart();
	glPopMatrix();

#pragma endregion leftRocket
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, red);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, red);
	glColor3f(1, 0, 0);
#pragma region rightRocket
	glBindTexture(GL_TEXTURE_2D, textureMetalGrey);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, indigo);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, indigo);
	glColor3f(indigo[0], indigo[1], indigo[2]);
	glBegin(GL_POLYGON);
	//left
	glTexCoord2f(0, 0);
	glVertex3f(3, 2, -6);
	glTexCoord2f(1, 0);
	glVertex3f(3, 9, -3);
	glTexCoord2f(1, 1);
	glVertex3f(3, 9, -1);
	glTexCoord2f(0, 1);
	glVertex3f(3, 2, -1);
	glTexCoord2f(1, 1);
	glVertex3f(3, 1, -3);
	glEnd();

	glBegin(GL_POLYGON);
	//right
	glTexCoord2f(0, 0);
	glVertex3f(4, 2, -6);
	glTexCoord2f(1, 0);
	glVertex3f(4, 9, -3);
	glTexCoord2f(1, 1);
	glVertex3f(4, 9, -1);
	glTexCoord2f(0, 1);
	glVertex3f(4, 2, -1);
	glTexCoord2f(1, 1);
	glVertex3f(4, 1, -3);
	glEnd();

	glBegin(GL_QUADS);
	//front
	glTexCoord2f(0, 0);
	glVertex3f(3, 2, -6);
	glTexCoord2f(1, 0);
	glVertex3f(3, 9, -3);
	glTexCoord2f(1, 1);
	glVertex3f(4, 9, -3);
	glTexCoord2f(0, 1);
	glVertex3f(4, 2, -6);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(3, 2, -1);
	glTexCoord2f(1, 0);
	glVertex3f(3, 9, -1);
	glTexCoord2f(1, 1);
	glVertex3f(4, 9, -1);
	glTexCoord2f(0, 1);
	glVertex3f(4, 2, -1);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(3, 1, -3);
	glTexCoord2f(1, 0);
	glVertex3f(3, 2, -6);
	glTexCoord2f(1, 1);
	glVertex3f(4, 2, -6);
	glTexCoord2f(0, 1);
	glVertex3f(4, 1, -3);

	glTexCoord2f(0, 0);
	glVertex3f(3, 1, -3);
	glTexCoord2f(1, 0);
	glVertex3f(3, 2, -1);
	glTexCoord2f(1, 1);
	glVertex3f(4, 2, -1);
	glTexCoord2f(0, 1);
	glVertex3f(4, 1, -3);

	//----------------------------layer2
	//right
	glTexCoord2f(0, 0);
	glVertex3f(4, 12, -3);
	glTexCoord2f(1, 0);
	glVertex3f(4, 9, -3);
	glTexCoord2f(1, 1);
	glVertex3f(4, 9, -1);
	glTexCoord2f(0, 1);
	glVertex3f(4, 12, -1);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(3, 12, -3);
	glTexCoord2f(1, 0);
	glVertex3f(3, 9, -3);
	glTexCoord2f(1, 1);
	glVertex3f(3, 9, -1);
	glTexCoord2f(0, 1);
	glVertex3f(3, 12, -1);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(3, 9, -3);
	glTexCoord2f(1, 0);
	glVertex3f(4, 9, -3);
	glTexCoord2f(1, 1);
	glVertex3f(4, 12, -3);
	glTexCoord2f(0, 1);
	glVertex3f(3, 12, -3);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(3, 9, -1);
	glTexCoord2f(1, 0);
	glVertex3f(4, 9, -1);
	glTexCoord2f(1, 1);
	glVertex3f(4, 12, -1);
	glTexCoord2f(0, 1);
	glVertex3f(3, 12, -1);

	//-------------------------------layer3
	//top
	glTexCoord2f(0, 0);
	glVertex3f(3, 17, -2);
	glTexCoord2f(1, 0);
	glVertex3f(4, 17, -2);
	glTexCoord2f(1, 1);
	glVertex3f(4, 17, -4);
	glTexCoord2f(0, 1);
	glVertex3f(3, 17, -4);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(3, 17, -4);
	glTexCoord2f(1, 0);
	glVertex3f(4, 17, -4);
	glTexCoord2f(1, 1);
	glVertex3f(4, 13, -4);
	glTexCoord2f(0, 1);
	glVertex3f(3, 13, -4);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(3, 13, -2);
	glTexCoord2f(1, 0);
	glVertex3f(4, 13, -2);
	glTexCoord2f(1, 1);
	glVertex3f(4, 12, -1);
	glTexCoord2f(0, 1);
	glVertex3f(3, 12, -1);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(3, 17, -2);
	glTexCoord2f(1, 0);
	glVertex3f(4, 17, -2);
	glTexCoord2f(1, 1);
	glVertex3f(4, 12, -1);
	glTexCoord2f(0, 1);
	glVertex3f(3, 12, -1);
	glEnd();

	glBegin(GL_POLYGON);
	//right
	glTexCoord2f(0, 0);
	glVertex3f(4, 12, -3);
	glTexCoord2f(1, 0);
	glVertex3f(4, 12, -1);
	glTexCoord2f(1, 1);
	glVertex3f(4, 17, -2);
	glTexCoord2f(0, 1);
	glVertex3f(4, 17, -4);
	glTexCoord2f(1, 1);
	glVertex3f(4, 13, -4);
	glEnd();

	glBegin(GL_POLYGON);
	//left
	glTexCoord2f(0, 0);
	glVertex3f(3, 12, -3);
	glTexCoord2f(1, 0);
	glVertex3f(3, 12, -1);
	glTexCoord2f(1, 1);
	glVertex3f(3, 17, -2);
	glTexCoord2f(0, 1);
	glVertex3f(3, 17, -4);
	glTexCoord2f(1, 1);
	glVertex3f(3, 13, -4);
	glEnd();

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, silver);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, silver);
	glColor3f(silver[0], silver[1], silver[2]);
	glPushMatrix();
	glTranslatef(5, 4, -3);
	glRotatef(-90, 0, 1, 0);
	gluQuadricTexture(obj, true);
	gluCylinder(obj, 1.5, 1.5, 2, 10, 2);
	glBegin(GL_POLYGON);
	glTranslatef(0, 0, 13);
	for (int i = 0; i < 360; i++) {
		glTexCoord2f((float)i / 360, (float)i / 360);
		glVertex2f(1.5 * cos(i), 1.5 * sin(i));
	}
	glEnd();
	glPopMatrix();

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, darkBlue);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, darkBlue);
	glColor3f(darkBlue[0], darkBlue[1], darkBlue[2]);
	glBegin(GL_QUADS);
	//left
	glTexCoord2f(0, 0);
	glVertex3f(6, 4, -4);
	glTexCoord2f(1, 0);
	glVertex3f(5, 2.5, -4);
	glTexCoord2f(1, 1);
	glVertex3f(5, 5.5, -4);
	glTexCoord2f(0, 1);
	glVertex3f(6, 5, -4);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(6, 4, -2);
	glTexCoord2f(1, 0);
	glVertex3f(5, 2.5, -2);
	glTexCoord2f(1, 1);
	glVertex3f(5, 5.5, -2);
	glTexCoord2f(0, 1);
	glVertex3f(6, 5, -2);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(6, 4, -2);
	glTexCoord2f(1, 0);
	glVertex3f(5, 5.5, -2);
	glTexCoord2f(1, 1);
	glVertex3f(5, 5.5, -4);
	glTexCoord2f(0, 1);
	glVertex3f(6, 4, -4);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(6, 4, -2);
	glTexCoord2f(1, 0);
	glVertex3f(6, 4, -4);
	glTexCoord2f(1, 1);
	glVertex3f(6, 5, -4);
	glTexCoord2f(0, 1);
	glVertex3f(6, 5, -2);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(6, 4, -2);
	glTexCoord2f(1, 0);
	glVertex3f(5, 2.5, -2);
	glTexCoord2f(1, 1);
	glVertex3f(5, 2.5, -4);
	glTexCoord2f(0, 1);
	glVertex3f(6, 4, -4);
	glEnd();

	glPushMatrix();
	glTranslatef(6, 3.5, -2.5);
	glRotatef(rocketRightRotateX, 1, 0, 0);
	glRotatef(20, 1, 0, 0);
	glRotatef(20, 0, 0, 1);
	glTranslatef(1, -16, 0);
	rocketRightPart();
	glPopMatrix();

#pragma endregion rightRocket
	glPopMatrix();
}

void display()
{
	//--------------------------------
	//	OpenGL drawing
	//--------------------------------
	glClearColor(1, 1, 1, 0); // divide the ratio to obtain RGBA code
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (obj == NULL) { obj = gluNewQuadric(); }
	lightOn ? glEnable(GL_LIGHTING) : glDisable(GL_LIGHTING);
	camera();

	glMatrixMode(GL_MODELVIEW);

	if (jump) {
		jumpAnimation();
	}
	if (fly) {
		flyAnimation();
	}
	if (rocketMove) {
		rocketAnimation();
	}
	if (shoot) {
		shootingAnimation();
	}
	if (defense) {
		defenseAnimation();
	}
	if (swordAtkAni) {
		swordAttackAnimation();
	}

	//Outer Push & Pop
	glPushMatrix();
	gluLookAt((35+zoom) * cos(z * 3.142 / 180), y, -6 + (35+zoom) * sin(z * 3.142 / 180),
		0, 0, 0,
		0, 1, 0);

#pragma region program
	switchColorText();
	glPushMatrix();
	
	//Whole body rotation
	glTranslatef(wholeBodyTranslateX, wholeBodyTranslateY, wholeBodyTranslateZ);
	glTranslatef(0, 0, -4);
	glRotatef(wholeBodyRotateY, 0, 1, 0);
	glTranslatef(0, 0, 4);
	glRotatef(bodyRotateX, 1, 0, 0);

	//-------------------------------------------------Upper body container
	glPushMatrix();
	glRotatef(bodyRotateY, 0, 1, 0);

	glPushMatrix();
	glTranslatef(0, 15, -4.75);
	glRotatef(headRotateX, 1, 0, 0);
	glRotatef(headRotateY, 0, 1, 0);
	head();
	glPopMatrix();

	body();

	glPushMatrix();
	glTranslatef(0, 4, -8);
	jetpack();
	glPopMatrix();

	//left hand
	glPushMatrix();
	glTranslatef(12, -8, -4);
	glRotatef(5, 0, 0, 1);

	glTranslatef(0, 20, 0);
	glRotatef(leftUpperArmRotateX, 1, 0, 0);
	glRotatef(leftUpperArmRotateY, 0, 1, 0);
	glRotatef(leftUpperArmRotateZ, 0, 0, 1);
	glTranslatef(0, -20, 0);
	leftUpperArm();

	glTranslatef(0, 11, 0);
	glRotatef(leftLowerArmRotateX, 1, 0, 0);
	glRotatef(leftLowerArmRotateY, 0, 1, 0);
	glRotatef(leftLowerArmRotateZ, 0, 0, 1);
	glTranslatef(0, -11, 0);
	leftLowerArm();
	
	glTranslatef(0, 2, 0);
	glRotatef(leftHandRotateX, 1, 0, 0);
	glRotatef(leftHandRotateY, 0, 1, 0);
	glRotatef(leftHandRotateZ, 0, 0, 1);
	glTranslatef(0, -2, 0);
	leftHand();
	glPopMatrix();

	//right hand
	glPushMatrix();
	glTranslatef(-12, -8, -4);
	glRotatef(-5, 0, 0, 1);

	glTranslatef(0, 20, 0);
	glRotatef(rightUpperArmRotateX, 1, 0, 0);
	glRotatef(rightUpperArmRotateY, 0, 1, 0);
	glRotatef(rightUpperArmRotateZ, 0, 0, 1);
	glTranslatef(0, -20, 0);
	rightUpperArm();

	glTranslatef(0, 11, 0);
	glRotatef(rightLowerArmRotateX, 1, 0, 0);
	glRotatef(rightLowerArmRotateY, 0, 1, 0);
	glRotatef(rightLowerArmRotateZ, 0, 0, 1);
	glTranslatef(0, -11, 0);
	rightLowerArm();	
	
	glTranslatef(0, 2, 0);
	glRotatef(rightHandRotateX, 1, 0, 0);
	glRotatef(rightHandRotateY, 0, 1, 0);
	glRotatef(rightHandRotateZ, 0, 0, 1);
	glTranslatef(0, -2, 0);
	rightHand();
	glPopMatrix();
	glPopMatrix(); //End upper body container

	//-------------------------------------------------lower body part
	glPushMatrix();
	glTranslatef(0, -3, -4);
	glPushMatrix();
	glRotatef(bodyRotateY / 10, 0, 1, 0);
	lowerBody();
	glPopMatrix();

	glPushMatrix(); //Whole legs
	//left leg
	glPushMatrix();
	glRotatef(5, 0, 0, 1);
	glTranslatef(4, -25, 2);

	glTranslatef(0, 28, 0);
	glRotatef(leftUpperLegRotateX, 1, 0, 0);
	glRotatef(leftUpperLegRotateY, 0, 1, 0);
	glRotatef(leftUpperLegRotateZ, 0, 0, 1);
	glTranslatef(0, -28, 0);
	leftUpperLeg();

	glTranslatef(0, 15, 0);
	glRotatef(-leftLowerLegRotateX, 1, 0, 0);
	glRotatef(-leftLowerLegRotateY, 0, 1, 0);
	glRotatef(-leftLowerLegRotateZ, 0, 0, 1);
	glTranslatef(0, -15, 0);
	leftLowerLeg();

	leftFoot();
	glPopMatrix();

	//right leg
	glPushMatrix();
	glRotatef(-5, 0, 0, 1);
	glTranslatef(-4, -25, 2);

	glTranslatef(0, 28, 0);
	glRotatef(rightUpperLegRotateX, 1, 0, 0);
	glRotatef(rightUpperLegRotateY, 0, 1, 0);
	glRotatef(rightUpperLegRotateZ, 0, 0, 1);
	glTranslatef(0, -28, 0);
	rightUpperLeg();

	glTranslatef(0, 15, 0);
	glRotatef(-rightLowerLegRotateX, 1, 0, 0);
	glRotatef(-rightLowerLegRotateY, 0, 1, 0);
	glRotatef(-rightLowerLegRotateZ, 0, 0, 1);
	glTranslatef(0, -15, 0);
	rightLowerLeg();

	rightFoot();
	glPopMatrix();
	glPopMatrix();


	glPopMatrix();
	glPopMatrix();

	//Extra Shields
	if (defense) {
		glPushMatrix();
		glTranslatef(10, shieldHeight[1], 20); // default -22
		glRotatef(45, 0, 1, 0);
		shield();
		glPopMatrix();


		glPushMatrix();
		glTranslatef(-10, shieldHeight[2], 20);
		glRotatef(-45, 0, 1, 0);
		shield();
		glPopMatrix();


		glPushMatrix();
		glTranslatef(0, shieldHeight[0], 24);
		shield();
		glPopMatrix();
	}

	background();
	glDisable(GL_TEXTURE_2D);
#pragma endregion program

	//lighting
	glPushMatrix();
	GLfloat positionLight[4] = { lightX, lightY, lightZ, 1 };
	glLightfv(GL_LIGHT7, GL_POSITION, positionLight);
	glPopMatrix();

	glPopMatrix();

	//--------------------------------
	//	End of OpenGL drawing
	//--------------------------------
}
//--------------------------------------------------------------------

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = WindowProcedure;
	wc.lpszClassName = WINDOW_TITLE;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wc)) return false;

	HWND hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 800,
		NULL, NULL, wc.hInstance, NULL); //Window size

	//--------------------------------
	//	Initialize window for OpenGL
	//--------------------------------

	HDC hdc = GetDC(hWnd);

	//	initialize pixel format for the window
	initPixelFormat(hdc);

	//	get an openGL context
	HGLRC hglrc = wglCreateContext(hdc);

	//	make context current
	if (!wglMakeCurrent(hdc, hglrc)) return false;

	//--------------------------------
	//	End initialization
	//--------------------------------

	texture1Initialization();

	// Set variables properties
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-35, 35, -35, 35, 0.1, 100);
	//gluPerspective(100, 6/6, 0, 100);

	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));



	lighting();


	while (true)
	{
		// Get start time of this loop
		currentTicks = clock();
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		display();

		SwapBuffers(hdc);

		// Get end time of this loop
		elapsedTicks = clock() - currentTicks;
		elapsedSeconds = (float)elapsedTicks / 1000.0f;
	}

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}
//--------------------------------------------------------------------