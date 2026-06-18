/*
Voca.cpp
project : Voca class 헤더파일의 멤버함수를 구현한 CPP 파일
st_id : 22312039
Author : Cho_ilsu
Date of last update : June 04, 2026
*/

// Voca class를 사용하기 위한 헤더파일
#include "Voca.h"

// 문자 변환 함수를 사용하기 위한 헤더파일
#include <cctype>

// 정규식을 사용하기 위한 헤더파일
#include <regex>

// 기본 생성자
Voca::Voca()
{
    keyWord = "";
    partOfSpeech = "";
}

// 어휘 정보를 초기화하는 생성자
Voca::Voca(const std::string& keyWord, const std::string& partOfSpeech,
    const std::vector<std::string>& thesaurus,
    const std::vector<std::string>& exampleUsages)
{
    this->keyWord = keyWord;
    this->partOfSpeech = partOfSpeech;
    this->thesaurus = thesaurus;
    this->exampleUsages = exampleUsages;
}

// 핵심 어휘 반환하기
std::string Voca::getKeyWord() const
{
    return keyWord;
}

// 품사 반환하기
std::string Voca::getPartOfSpeech() const
{
    return partOfSpeech;
}

// 문자열을 소문자로 변환하기
static std::string toLowerStr(std::string str)
{
    for (char& ch : str)
    {
        ch = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
    }

    return str;
}

// 따옴표 안에 있는 문자열들을 추출하기
static std::vector<std::string> extractQuotedStrings(const std::string& text)
{
    // 추출한 문자열을 저장할 vector 선언하기
    std::vector<std::string> result;

    // 큰따옴표 안의 문자열을 찾기 위한 정규식 선언하기
    std::regex quotedPattern(R"REGEX("([^"]*)")REGEX");

    // 정규식 검색 시작 iterator 생성하기
    std::sregex_iterator it(text.begin(), text.end(), quotedPattern);

    // 정규식 검색 끝 iterator 생성하기
    std::sregex_iterator end;

    // 큰따옴표 안의 문자열들을 모두 추출하기
    while (it != end)
    {
        result.push_back((*it)[1]);
        ++it;
    }

    return result;
}

// 한 줄의 문자열을 Voca 객체로 변환하기
bool Voca::parseLine(const std::string& line)
{
    // 단어, 품사, 유의어 목록, 예문 목록을 분리하기 위한 정규식 선언하기
    std::regex vocaPattern(
        R"REGEX(^\s*([^,]+)\s*,\s*([A-Za-z]+)\s*,\s*\{([^}]*)\}\s*,\s*\{([^}]*)\}\s*;\s*$)REGEX"
    );

    // 정규식 결과를 저장할 객체 선언하기
    std::smatch match;

    // 입력 형식이 정규식과 맞지 않으면 false 반환하기
    if (!std::regex_match(line, match, vocaPattern))
    {
        return false;
    }

    // 핵심 어휘 저장하기
    keyWord = match[1];

    // 품사 저장하기
    partOfSpeech = match[2];

    // 유의어 목록 저장하기
    thesaurus = extractQuotedStrings(match[3]);

    // 예문 목록 저장하기
    exampleUsages = extractQuotedStrings(match[4]);

    return true;
}

// 품사를 출력용 약어로 변환하기
std::string Voca::getPOSAbbrev() const
{
    // 품사를 소문자로 변환하기
    std::string pos = toLowerStr(partOfSpeech);

    if (pos == "noun")
    {
        return "n";
    }
    else if (pos == "verb")
    {
        return "v";
    }
    else if (pos == "adj" || pos == "adjective")
    {
        return "adj";
    }
    else if (pos == "adv" || pos == "adverb")
    {
        return "adv";
    }

    return pos;
}

// 문자열 vector 출력하기
static void printStringVector(std::ostream& fout,
    const std::vector<std::string>& vec)
{
    for (int i = 0; i < static_cast<int>(vec.size()); ++i)
    {
        fout << vec[i];

        if (i != static_cast<int>(vec.size()) - 1)
        {
            fout << ", ";
        }
    }
}

// Voca 객체 출력하기
std::ostream& operator<<(std::ostream& fout, const Voca& voca)
{
    // 단어와 품사 출력하기
    fout << voca.keyWord << "(" << voca.getPOSAbbrev() << "):" << std::endl;

    // 유의어 목록 출력하기
    fout << " - thesaurus(";
    printStringVector(fout, voca.thesaurus);
    fout << ")" << std::endl;

    // 예문 목록 출력하기
    fout << " - example usage(";
    printStringVector(fout, voca.exampleUsages);
    fout << ")";

    return fout;
}