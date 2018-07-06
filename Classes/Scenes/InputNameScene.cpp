#include "InputNameScene.h"
#include "SimpleAudioEngine.h"
#include "GameSettingScene.h"
#include "ExampleGameScene.h"
#include "../ShareSingleton.h"
using namespace CocosDenshion;
USING_NS_CC;

Scene* InputNameScene::createScene()
{
    return InputNameScene::create();
}

/* ���ļ�������ʱ����ӡ���õĴ�����Ϣ�����Ƿֶδ��� */
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in InputNameSceneScene.cpp\n");
}

/* ��ʼ���������� */
bool InputNameScene::init()
{
#pragma region Cocos2dx�Զ����ɵ����ݣ�һЩ��������

	if (!Scene::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

#pragma endregion


#pragma region UI���� ����ͼƬ
	
	auto bg = Sprite::create("bg/startSceneBackground.png");
	bg->setPosition(visibleSize / 2);
	addChild(bg, 0);

#pragma endregion

#pragma region  Ԥ������Ч�ͱ�������

	auto audio = SimpleAudioEngine::getInstance();
	/*Ԥ���ز�ѭ�����ű�������*/
	audio->playBackgroundMusic("music/WelcomeSceneBgm.mp3", true);
	audio->setBackgroundMusicVolume(0.80);

	/*Ԥ������Ч*/
	audio->preloadEffect("music/ClickCamera.wav");
	audio->setEffectsVolume(0.80);

#pragma endregion

#pragma region �ı�����
	/* VS */
	vs = Label::createWithTTF("VS", "fonts/comicsansms.ttf", 60);
	vs->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	vs->setColor(Color3B(255, 255, 0));
	addChild(vs, 1);

	/* �����༭�� */
	Size boxSize = CCSizeMake(100, 45);	

	editBox1 = EditBox::create(boxSize, "green.png");
	editBox2 = EditBox::create(boxSize, "green.png");
	editBox1->setPosition(Vec2(visibleSize.width / 2 + 200, visibleSize.height / 2));
	editBox2->setPosition(Vec2(visibleSize.width / 2 - 200, visibleSize.height / 2));

	// Ĭ���������
	editBox1->setPlaceHolder("Player1");
	editBox2->setPlaceHolder("Player2");
	editBox1->setPlaceholderFontName("comicsansms");
	editBox2->setPlaceholderFontName("comicsansms");
	editBox1->setPlaceholderFontColor(Color3B::RED);
	editBox2->setPlaceholderFontColor(Color3B::RED);
	editBox1->setPlaceholderFontSize(32);
	editBox2->setPlaceholderFontSize(32);

	// �༭���ı����
	editBox1->setFontName("comicsansms");
	editBox2->setFontName("comicsansms");
	editBox1->setFontColor(Color3B::RED);
	editBox2->setFontColor(Color3B::RED);
	editBox1->setFontSize(36);
	editBox2->setFontSize(36);

	this->addChild(editBox1, 2);
	this->addChild(editBox2, 2);
#pragma endregion

#pragma region ȷ�ϰ�ť
	/* ȷ����ť */
	nameConfirmItem = MenuItemImage::create(
		"button/confirm-normal.png",
		"button/confirm-selected.png",
		CC_CALLBACK_1(InputNameScene::confirmCallback, this));

	nameConfirmItem->setPosition(Vec2(512, 250));
	//addChild(nameConfirmItem);
	auto menu = Menu::create(nameConfirmItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
#pragma endregion

    return true;
}

/* ȷ����ɫ���� */
void InputNameScene::confirmCallback(Ref* pSender)
{
	string name1 = editBox1->getText();
	string name2 = editBox2->getText();
	if (name1[0] == ' ' || name2[0] == ' ' || name1 == name2) {
		return;
	}
	auto particle = ParticleFlower::create();
	SimpleAudioEngine::getInstance()->playEffect("music/ClickCamera.wav", false, 1.0f, 0.0f, 1.0f);

	ShareSingleton::GetInstance()->user1 = editBox1->getText();
	ShareSingleton::GetInstance()->user2 = editBox2->getText();

	float t = 1.2f;
	auto newScene = ExampleGameScene::createScene();
	auto replacesense = CCTransitionFade::create(t, newScene);
	Director::sharedDirector()->replaceScene(replacesense);
	return;
}