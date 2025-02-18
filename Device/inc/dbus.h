#pragma once
#include <stdint.h>
#include <webots/Keyboard.hpp>

namespace RCS
{
    enum SWPos
    {
        Lost = 0,
        Up = 1,
        Mid = 3,
        Down = 2
    };

    enum SWTick
    {
        UnDefined = 0,
        Up_Mid = 2,
        Mid_Up = -2,
        Mid_Down = -1,
        Down_Mid = 1
    };
}

typedef struct
{
    uint32_t keyValue;
    struct{
    uint16_t A : 1;     ///< 0x0001
    uint16_t B : 1;     ///< 0x0002
    uint16_t C : 1;     ///< 0x0004
    uint16_t D : 1;     ///< 0x0008
    uint16_t E : 1;     ///< 0x0010
    uint16_t F : 1;     ///< 0x0020
    uint16_t G : 1;     ///< 0x0040
    uint16_t H : 1;     ///< 0x0080
    uint16_t I : 1;     ///< 0x0100
    uint16_t J : 1;     ///< 0x0200
    uint16_t K : 1;     ///< 0x0400
    uint16_t L : 1;     ///< 0x0800
    uint16_t M : 1;     ///< 0x1000
    uint16_t N : 1;     ///< 0x2000
    uint16_t O : 1;     ///< 0x4000
    uint16_t P : 1;     ///< 0x8000

    uint16_t Q : 1;     ///< 0x0001
    uint16_t R : 1;     ///< 0x0002
    uint16_t S : 1;     ///< 0x0004
    uint16_t T : 1;     ///< 0x0008
    uint16_t U : 1;     ///< 0x0010
    uint16_t V : 1;     ///< 0x0020
    uint16_t W : 1;     ///< 0x0040
    uint16_t X : 1;     ///< 0x0080
    uint16_t Y : 1;     ///< 0x0100
    uint16_t Z : 1;     
    uint16_t Up: 1;
    uint16_t Down:1;
    uint16_t unused : 4; ///< 保留位，未使用
};


} RemoteKey;


class RemoteCtrl
{
public:

    RemoteCtrl();
    ~RemoteCtrl();
    webots::Keyboard *keyboard;
    void RC_init(void);
    void handleData();
    int rc;
    RemoteKey key;
    RemoteKey lastKey;
    RemoteKey keyTick;
    RemoteKey keyPress;

private:
public:
    uint8_t updated;
    uint64_t updateTime;

};
void RCtaskSchedule();

extern RemoteCtrl RC;
extern uint8_t deforceFlag;




