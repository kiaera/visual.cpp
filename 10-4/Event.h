/*
Event.h
project : Event 클래스를 선언한 헤더파일
st_id : 22312039
Author : Cho_ilsu
Date of last update : May 19, 2026
*/

// EVENT_H가 선언되어 있지 않은 경우에만 포함하기
#ifndef EVENT_H

// EVENT_H 매크로 정의하기
#define EVENT_H

// 표준 입출력 사용하기 위한 헤더파일
#include <iostream>

// 문자열 자료형을 사용하기 위한 헤더파일
#include <string>

// 파일 입출력 사용하기 위한 헤더파일
#include <fstream>

// LARGE_INTEGER 자료형을 사용하기 위한 헤더파일
#include <Windows.h>

// 출력 형식 제어를 사용하기 위한 헤더파일
#include <iomanip>

// Event 상태 종류 정의하기
enum EventStatus
{
    GENERATED,
    ENQUEUED,
    PROCESSED,
    UNDEFINED
};

// 최대 Event priority 값 정의하기
#define MAX_EVENT_PRIORITY 100

// Event 클래스 선언하기
class Event
{
    // Event 객체 출력 연산자 함수 선언하기
    friend std::ostream& operator<<(std::ostream& fout, const Event& e);

public:
    // 기본 생성자
    Event()
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

    // 매개변수 생성자
    Event(int event_id,
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

    // Event 번호 설정하기
    void setEventNo(int evtNo)
    {
        event_no = evtNo;
    }

    // Event priority 설정하기
    void setEventPri(int pri)
    {
        event_pri = pri;
    }

    // Event 이름 설정하기
    void setEventName(std::string nm)
    {
        event_name = nm;
    }

    // Event handler 주소 설정하기
    void setEventHandlerAddr(int evtHndlerAddr)
    {
        event_handler_addr = evtHndlerAddr;
    }

    // Event generator 주소 설정하기
    void setEventGenAddr(int genAddr)
    {
        event_gen_addr = genAddr;
    }

    // Event 상태 설정하기
    void setEventStatus(EventStatus evtStatus)
    {
        eventStatus = evtStatus;
    }

    // Event 생성 시간 설정하기
    void setEventGenTime(LARGE_INTEGER t_gen)
    {
        t_event_gen = t_gen;
    }

    // Event 처리 시간 설정하기
    void setEventProcTime(LARGE_INTEGER t_proc)
    {
        t_event_proc = t_proc;
    }

    // Event 생성 시간 반환하기
    LARGE_INTEGER getEventGenTime()
    {
        return t_event_gen;
    }

    // Event 처리 시간 반환하기
    LARGE_INTEGER getEventProcTime()
    {
        return t_event_proc;
    }

    // Event 경과 시간 설정하기
    void setEventElaspsedTime(double t_elapsed_ms)
    {
        t_elapsed_time_ms = t_elapsed_ms;
    }

    // Event 경과 시간 반환하기
    double getEventElapsedTime()
    {
        return t_elapsed_time_ms;
    }

    // Event priority 반환하기
    int getEventPri()
    {
        return event_pri;
    }

    // Event 번호 반환하기
    int getEventNo()
    {
        return event_no;
    }

    // Event 이름 반환하기
    std::string getEventName()
    {
        return event_name;
    }

    // priority 비교 연산자 오버로딩하기
    bool operator>(Event& e)
    {
        return (event_pri > e.event_pri);
    }

    // priority 비교 연산자 오버로딩하기
    bool operator<(Event& e)
    {
        return (event_pri < e.event_pri);
    }

private:
    // Event 번호 저장하기
    int event_no;

    // Event priority 저장하기
    int event_pri;

    // Event 이름 저장하기
    std::string event_name;

    // Event 생성자 주소 저장하기
    int event_gen_addr;

    // Event 처리자 주소 저장하기
    int event_handler_addr;

    // Event 생성 시간 저장하기
    LARGE_INTEGER t_event_gen;

    // Event 처리 시간 저장하기
    LARGE_INTEGER t_event_proc;

    // Event 처리 경과 시간 저장하기
    double t_elapsed_time_ms;

    // Event 상태 저장하기
    EventStatus eventStatus;
};

// 출력 연산자 함수 선언하기
std::ostream& operator<<(std::ostream& fout, const Event& e);

// 랜덤 Event 생성 함수 선언하기
Event* genRandEvent(int evt_no);

// Event 배열 출력 함수 선언하기
std::ostream& printEvents(std::ostream& fout,
    Event* events,
    int size,
    int per_line);

#endif