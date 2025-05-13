#include "pch.h"
#include "Resource.h"

#include "D2DRenderer.h"
#include "AnimationAsset.h"

#include <istream>
#include <fstream>

Resource::Resource()
{
}

Resource::~Resource()
{
}

void Resource::Initialize()
{
}

void Resource::LoadAnimation(wstring _animPath, D2DRenderer* _pRenderer)
{
    // 폴더가 존재하지 않으면 터진다
    filesystem::path animPath(_animPath);
    assert(filesystem::exists(animPath) && filesystem::is_directory(animPath));
    
    // 폴더 내 파일 순회
    for (const auto& entry : filesystem::directory_iterator(_animPath))
    {
        const filesystem::path& filePath = entry.path();

        // 파일이 정상적이지 않으면 터진다
        assert(filesystem::is_regular_file(filePath) && filePath.has_extension());

        if (filePath.extension() == ".txt")
            LoadAnimInfoFromTextFile(filePath, _pRenderer);
    }
}

void Resource::LoadAnimInfoFromTextFile(filesystem::path _filePath, D2DRenderer* _pRenderer)
{
    std::ifstream file(_filePath);

    // 파일을 열 수 없으면 터진다
    assert(file.is_open());

    // 파일 하나당 하나의 애니메이션 인포가 추가된다
    AnimationInfo* animInfo;

    std::string line;
    bool isFirstLine = true;

    while (std::getline(file, line))
    {
        if (line.empty()) continue;

        // 첫 줄은 따로 처리
        if (isFirstLine)
        {
            isFirstLine = false;
            std::wstring wstr;
            wstr.assign(line.begin(), line.end());

            // 비트맵 키로 어셋 생성 또는 받아오기
            AnimationAsset* animAsset = _pRenderer->CreateAnimationAsset(wstr);

            // 파일명으로 어셋에 인포 추가
            ///animInfo = animAsset->AddAnimationInfo(filePath.stem().string());

            continue;
        }

        std::string  delimiter = ",";
        std::string  token;
        int pos = 0;
        int index = 0;

        while (true)
        {
            pos = (int)line.find(delimiter);
            token = line.substr(0, pos);
            line.erase(0, pos + delimiter.length());

            float top, left, bottom, right;

            switch (index)
            {
                case 0:
                    top = stof(token);
                    break;
                case 1:
                    left = stof(token);
                    break;
                case 2:
                    bottom = stof(token);
                    break;
                case 3:
                    right = stof(token);
                    break;
            }

            // 한 줄 씩 프레임 인포 추가
            ///animInfo->AddFrameInfo(top, left, bottom, left);
            index++;

            // 더 이상 문자가 발견되지 않으면 다음 줄로 넘어간다 
            if (pos == std::string::npos) break;
        }
    }
    file.close();

}


