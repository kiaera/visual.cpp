/*
Event.cpp
project : Event 클래스 헤더파일의 멤버함수를 구현한 CPP 파일
st_id : 22312039
Author : Cho_ilsu
Date of last update : May 19, 2026
*/

// Event 클래스 사용하기 위한 헤더파일
#include "Event.h"

#include "SimParams.h"

/*
Event 출력 연산자 함수 구현하기
*/
std::ostream& operator<<(std::ostream& fout, const Event& e)
{
    // Event 번호, priority, 이름 출력하기
    fout << "Ev(no:"
        << std::setw(2)
        << e.event_no
        << ", pri:"
        << std::setw(2)
        << e.event_pri
        << ", "
        << e.event_name
        << ")";

    return fout;
}

/*
랜덤 Event 생성 함수 구현하기
*/
Event* genRandEvent(int evt_no)
{
    // Event priority를 0부터 29까지 랜덤 생성하기
    int pri = rand() % NUM_EVENTS_PER_GEN;

    // Event 이름 저장하기
    std::string event_name = "evt_";

    // 한 자리 Event 번호인 경우 0 붙이기
    if (evt_no < 10)
    {
        event_name += "0";
    }

    // Event 번호를 문자열로 추가하기
    event_name += std::to_string(evt_no);

    // Event 객체 동적 생성하기
    Event* pEv = new Event(evt_no, pri, event_name, 0);

    return pEv;
}

/*
Event 배열 출력 함수 구현하기
*/
std::ostream& printEvents(std::ostream& fout,
    Event* events,
    int size,
    int per_line)
{
    // Event 배열 출력 반복하기
    for (int i = 0; i < size; i++)
    {
        fout << events[i] << " ";

        // 지정 개수마다 줄바꿈하기
        if ((i + 1) % per_line == 0)
        {
            fout << std::endl << " ";
        }
    }

    // 마지막 줄 처리하기
    if (size % per_line != 0)
    {
        fout << std::endl;
    }

    return fout;
}