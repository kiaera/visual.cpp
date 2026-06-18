/*
Event.cpp
project : Event 클래스 헤더파일의 멤버함수를 구현한 CPP 파일
st_id : 22312039
Author : Cho_ilsu
Date of last update : May 19, 2026
*/

#include <cstdlib>

// Event 클래스 헤더파일 포함하기
#include "Event.h"

// 기본 생성자 구현하기
Event::Event()
{
    // Event 번호 초기화하기
    event_no = -1;

    // Event priority 초기화하기
    event_pri = -1;

    // Event 이름 초기화하기
    event_name = "";

    // Event 생성자 주소 초기화하기
    event_gen_addr = -1;

    // Event 처리자 주소 초기화하기
    event_handler_addr = -1;

    // Event 처리 시간 초기화하기
    t_elapsed_time_ms = 0.0;

    // Event 상태 초기화하기
    eventStatus = UNDEFINED;
}

// 매개변수 생성자 구현하기
Event::Event(int event_id,
    int event_pri,
    std::string nm,
    int genAddr)
{
    // Event 번호 저장하기
    this->event_no = event_id;

    // Event priority 저장하기
    this->event_pri = event_pri;

    // Event 이름 저장하기
    this->event_name = nm;

    // Event 생성자 주소 저장하기
    this->event_gen_addr = genAddr;

    // Event 처리자 주소 초기화하기
    this->event_handler_addr = -1;

    // Event 처리 시간 초기화하기
    this->t_elapsed_time_ms = 0.0;

    // Event 상태 초기화하기
    this->eventStatus = GENERATED;
}

// 출력 연산자 함수 구현하기
std::ostream& operator<<(std::ostream& fout, const Event& e)
{
    // Event 번호와 priority 출력하기
    fout << "Ev(no:" << std::setw(2)
        << e.event_no
        << ", pri:"
        << std::setw(2)
        << e.event_pri
        << ")";

    return fout;
}

// 랜덤 Event 생성 함수 구현하기
Event* Gen_Rand_Event(int evt_no)
{
    // 동적 Event 객체 포인터 선언하기
    Event* pEv;

    // Event priority 저장 변수 선언하기
    int evt_prio;

    // Event generator ID 저장 변수 선언하기
    int evt_generator_id;

    // Event 이름 저장 변수 선언하기
    std::string evt_nm;

    // Event 이름 생성하기
    evt_nm = std::string("evt_") + std::to_string(evt_no);

    // Event priority 랜덤 생성하기
    evt_prio = rand() % MAX_EVENT_PRIORITY;

    // Event generator ID 랜덤 생성하기
    evt_generator_id = rand() % NUM_EVENT_GENERATORS;

    // 동적 Event 객체 생성하기
    pEv = new Event(evt_no, evt_prio, evt_nm, evt_generator_id);

    return pEv;
}

// Event 배열 출력 함수 구현하기
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
            fout << std::endl;
        }
    }

    // 마지막 줄 처리하기
    if (size % per_line != 0)
    {
        fout << std::endl;
    }

    return fout;
}