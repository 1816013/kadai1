#include <DxLib.h>
#include "ImageMng.h"
#include "_DebugConOut.h"

ImageMng *ImageMng::s_Instance = nullptr;

ImageMng::ImageMng()
{
}

ImageMng::~ImageMng() 
{
}

const VecInt& ImageMng::GetID(const std::string& key)
{
	//if (imgMap.find(key) == imgMap.end())
	//{
	//	imgMap[key].resize(1);
	//	imgMap[key]/*map*/[0]/*vector*/ = LoadGraph(key.c_str());
	//}
	//return imgMap[key];

	return GetID(key, key);
}

const VecInt & ImageMng::GetID(const std::string& key, const std::string& fileName)
{
	if (imgMap.find(key) == imgMap.end())
	{
		imgMap[key].resize(1);
		imgMap[key]/*map*/[0]/*vector*/ = LoadGraph(fileName.c_str());
	}
	return imgMap[key];
}

const VecInt & ImageMng::GetID(const std::string& key, const std::string& fileName, const Vector2& divCnt, const Vector2& divSize)
{
	if (imgMap.find(key) == imgMap.end())
	{
		imgMap[key].resize(divCnt.x * divCnt.y);
		LoadDivGraph(fileName.c_str(), divCnt.x * divCnt.y, divCnt.x, divCnt.y, divSize.x, divSize.y, &imgMap[key][0], false);
	}
	return imgMap[key];
}