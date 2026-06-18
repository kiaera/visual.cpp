/*
SimParams.h
project : Event Priority Queue 시뮬레이션에 필요한 상수를 정의한 헤더파일
st_id : 22312039
Author : Cho_ilsu
Date of last update : May 19, 2026
*/

// SIMULATION_PARAMETERS_H가 선언되어 있지 않은 경우에만 포함하기
#ifndef SIMULATION_PARAMETERS_H

// SIMULATION_PARAMETERS_H 매크로 정의하기
#define SIMULATION_PARAMETERS_H

// Event Generator 개수 정의하기
#define NUM_EVENT_GENERATORS 1

// Generator당 생성할 Event 개수 정의하기
#define NUM_EVENTS_PER_GEN 30

// Event Handler 개수 정의하기
#define NUM_EVENT_HANDLERS 1

// 전체 Event 개수 정의하기
#define TOTAL_NUM_EVENTS (NUM_EVENTS_PER_GEN * NUM_EVENT_GENERATORS)

// Priority Queue 최대 크기 정의하기
#define PRIOQ_CAPACITY 30

// 기존 코드 호환을 위한 Queue 최대 크기 정의하기
#define CIRQ_CAPACITY PRIOQ_CAPACITY

// 최대 반복 횟수 정의하기
#define MAX_ROUND 1000

// 한 줄당 출력할 Event 개수 정의하기
#define EVENTS_PER_LINE 10

#endif