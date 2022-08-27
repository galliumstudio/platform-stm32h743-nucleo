/*******************************************************************************
 * Copyright (C) 2018 Gallium Studio LLC (Lawrence Lo). All rights reserved.
 *
 * This program is open source software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Alternatively, this program may be distributed and modified under the
 * terms of Gallium Studio LLC commercial licenses, which expressly supersede
 * the GNU General Public License and are specifically designed for licensees
 * interested in retaining the proprietary status of their code.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 * Contact information:
 * Website - https://www.galliumstudio.com
 * Source repository - https://github.com/galliumstudio
 * Email - admin@galliumstudio.com
 ******************************************************************************/

#include "app_hsmn.h"
#include "fw_log.h"
#include "fw_assert.h"
#include "LedFrameInterface.h"
#include "LedPanelInterface.h"
#include "GuiMgrInterface.h"
#include "GuiMgr.h"
#include "WM.h"
#include "LCDConf_Lin_Template.h"


FW_DEFINE_THIS_FILE("GuiMgr.cpp")

namespace APP {

#undef ADD_EVT
#define ADD_EVT(e_) #e_,

static char const * const timerEvtName[] = {
    "GUI_MGR_TIMER_EVT_START",
    GUI_MGR_TIMER_EVT
};

static char const * const internalEvtName[] = {
    "GUI_MGR_INTERNAL_EVT_START",
    GUI_MGR_INTERNAL_EVT
};

static char const * const interfaceEvtName[] = {
    "GUI_MGR_INTERFACE_EVT_START",
    GUI_MGR_INTERFACE_EVT
};

// Bitmap structure created with EmWin utility (located under GuiMgr/Bitmaps)
extern "C" const GUI_BITMAP bmhelloworld;
extern "C" const GUI_BITMAP bmb_0001;
extern "C" const GUI_BITMAP bmb_0002;
extern "C" const GUI_BITMAP bmb_0003;
extern "C" const GUI_BITMAP bmb_0004;
extern "C" const GUI_BITMAP bmb_0005;
extern "C" const GUI_BITMAP bmb_0006;
extern "C" const GUI_BITMAP bmb_0007;
extern "C" const GUI_BITMAP bmb_0008;
extern "C" const GUI_BITMAP bmColordots;
extern "C" const GUI_BITMAP bmLedpanel6;

static const GUI_BITMAP *guiBitmap[] =
{
    &bmhelloworld,
    &bmb_0001,
    &bmb_0002,
    &bmb_0003,
    &bmb_0004,
    &bmb_0005,
    &bmb_0006,
    &bmb_0007,
    &bmb_0008,
    &bmColordots,
    &bmLedpanel6,
};

const GuiMgr::TimeoutMap GuiMgr::m_ticker1Timeout[] = {
    { 4,  40   },
    { 3,  80   },
    { 2,  120  },
    { 1,  160  },
    { 0,  5000 }
};

const GuiMgr::TimeoutMap GuiMgr::m_ticker2Timeout[] = {
    { 4,  10   },
    { 3,  20  },
    { 2,  40  },
    { 1,  80  },
    { 0,  3000 }
};

const GuiMgr::TimeoutMap GuiMgr::m_ticker3Timeout[] = {
    { 4,  20   },
    { 3,  40   },
    { 2,  80  },
    { 1,  120  },
    { 0,  3000 }
};

const GuiMgr::TimeoutMap GuiMgr::m_ticker4Timeout[] = {
    { 4,  60   },
    { 3,  100  },
    { 2,  140  },
    { 1,  180  },
    { 0,  3000 }
};

const GuiMgr::TimeoutMap GuiMgr::m_bmpTimeout[] = {
    { 10, 10   },
    { 6,  20   },
    { 4,  40   },
    { 3,  80   },
    { 2,  120  },
    { 1,  160  },
    { 0,  5000 }
};

// Helper function to map offset to timeout for speed control.
uint32_t GuiMgr::GetTimeout(TimeoutMap const *map, uint32_t mapLen, uint32_t offsetLeft, uint32_t offsetRight) {
    uint32_t timeoutLeft  = GetTimeout(map, mapLen, offsetLeft);
    uint32_t timeoutRight = GetTimeout(map, mapLen, offsetRight);
    return GREATER(timeoutLeft, timeoutRight);
}
uint32_t GuiMgr::GetTimeout(TimeoutMap const *map, uint32_t mapLen, uint32_t offset) {
    uint32_t i;
    FW_ASSERT(map);
    for (i=0; i<mapLen; i++) {
        if (offset >= map[i].offset) {
            return map[i].timeoutMs;
        }
    }
    FW_ASSERT(0);
    return 0;
}

// Window Manager callback function,
void GuiMgr::WmCallback(WM_MESSAGE *msg) {
    FW_ASSERT(msg);
    if ((msg->MsgId != WM_CREATE) && (msg->MsgId != WM_DELETE) && (msg->MsgId != WM_NOTIFY_PARENT)) {
        // WM_CREATE is sent right after the window is created, before user data (obj) is set
        GuiMgr *obj = NULL;
        WM_GetUserData(msg->hWin, &obj, sizeof(obj));
        FW_ASSERT(obj);
        obj->WmHandler(msg);
    }
}

void GuiMgr::WmHandler(WM_MESSAGE *msg) {
    GuiMgr *me = this;  // For Log.
    FW_ASSERT(msg);
    switch (msg->MsgId) {
        case WM_PAINT: {
            HwinSig *result = m_hwinSigMap.GetByKey(msg->hWin);
            if (result) {
                Evt *evt = new WmEvent(result->GetValue(), GetHsmn(), *msg);
                PostSync(evt);
            } else {
                ERROR("WmHandler: WM_PAINT hWin (0x%x) not found", msg->hWin);
            }
            break;
        }
        default: {
            WM_DefaultProc(msg);
            //LOG("WmHandler: Calling WM_DefaultProc msgId=0x%x", msg->MsgId);
            break;
        }
    }
}

void GuiMgr::AddWin(WM_HWIN hwin, QP::QSignal sig) {
    FW_ASSERT(hwin && (sig != Q_USER_SIG));
    m_hwinSigMap.Save(HwinSig(hwin, sig));
}

void GuiMgr::RemoveWin(WM_HWIN hwin) {
    if (hwin) {
        m_hwinSigMap.ClearByKey(hwin);
    }
}

GuiMgr::GuiMgr() :
    Active((QStateHandler)&GuiMgr::InitialPseudoState, GUI_MGR, "GUI_MGR"),
    m_hwinSigMap(m_hwinSigStor, ARRAY_COUNT(m_hwinSigStor), HwinSig(0, Q_USER_SIG)),
    m_dirty(false), m_ticker1CycleCnt(0), m_bmpCycleCnt(0), m_stateTimer(GetHsmn(), STATE_TIMER),
    m_bgWndTimer(GetHsmn(), BG_WND_TIMER, TICK_RATE_GUIMGR, LedPanel::MS_PER_SYNC),
    m_ticker1Timer(GetHsmn(), TICKER1_TIMER, TICK_RATE_GUIMGR, LedPanel::MS_PER_SYNC),
    m_ticker2Timer(GetHsmn(), TICKER2_TIMER, TICK_RATE_GUIMGR, LedPanel::MS_PER_SYNC),
    m_ticker3Timer(GetHsmn(), TICKER3_TIMER, TICK_RATE_GUIMGR, LedPanel::MS_PER_SYNC),
    m_ticker4Timer(GetHsmn(), TICKER4_TIMER, TICK_RATE_GUIMGR, LedPanel::MS_PER_SYNC),
    m_bmpTimer(GetHsmn(), BMP_TIMER, TICK_RATE_GUIMGR, LedPanel::MS_PER_SYNC){
    SET_EVT_NAME(GUI_MGR);
}

QState GuiMgr::InitialPseudoState(GuiMgr * const me, QEvt const * const e) {
    (void)e;
    return Q_TRAN(&GuiMgr::Root);
}

QState GuiMgr::Root(GuiMgr * const me, QEvt const * const e) {
    switch (e->sig) {
        case Q_ENTRY_SIG: {
            EVENT(e);
            me->m_ledFrame.Init(me);
            return Q_HANDLED();
        }
        case Q_EXIT_SIG: {
            EVENT(e);
            return Q_HANDLED();
        }
        case Q_INIT_SIG: {
            return Q_TRAN(&GuiMgr::Stopped);
        }
        case GUI_MGR_START_REQ: {
            EVENT(e);
            Evt const &req = EVT_CAST(*e);
            Evt *evt = new GuiMgrStartCfm(req.GetFrom(), GET_HSMN(), req.GetSeq(), ERROR_STATE, GET_HSMN());
            Fw::Post(evt);
            return Q_HANDLED();
        }
        case GUI_MGR_STOP_REQ: {
            EVENT(e);
            Evt const &req = EVT_CAST(*e);
            me->GetHsm().SaveInSeq(req);
            return Q_TRAN(&GuiMgr::Stopping);
        }
    }
    return Q_SUPER(&QHsm::top);
}

QState GuiMgr::Stopped(GuiMgr * const me, QEvt const * const e) {
    switch (e->sig) {
        case Q_ENTRY_SIG: {
            EVENT(e);
            return Q_HANDLED();
        }
        case Q_EXIT_SIG: {
            EVENT(e);
            return Q_HANDLED();
        }
        case GUI_MGR_STOP_REQ: {
            EVENT(e);
            Evt const &req = EVT_CAST(*e);
            Evt *evt = new GuiMgrStopCfm(req.GetFrom(), GET_HSMN(), req.GetSeq(), ERROR_SUCCESS);
            Fw::Post(evt);
            return Q_HANDLED();
        }
        case GUI_MGR_START_REQ: {
            EVENT(e);
            Evt const &req = EVT_CAST(*e);
            me->GetHsm().SaveInSeq(req);
            return Q_TRAN(&GuiMgr::Starting);
        }
    }
    return Q_SUPER(&GuiMgr::Root);
}

QState GuiMgr::Starting(GuiMgr * const me, QEvt const * const e) {
    switch (e->sig) {
        case Q_ENTRY_SIG: {
            EVENT(e);
            uint32_t timeout = GuiMgrStartReq::TIMEOUT_MS;
            FW_ASSERT(timeout > LedFrameStartReq::TIMEOUT_MS);
            me->m_stateTimer.Start(timeout);
            me->GetHsm().ResetOutSeq();
            Evt *evt = new LedFrameStartReq(LED_FRAME, GET_HSMN(), GEN_SEQ());
            me->GetHsm().SaveOutSeq(*evt);
            Fw::Post(evt);
            return Q_HANDLED();
        }
        case Q_EXIT_SIG: {
            EVENT(e);
            me->m_stateTimer.Stop();
            me->GetHsm().ClearInSeq();
            return Q_HANDLED();
        }
        case LED_FRAME_START_CFM: {
            EVENT(e);
            ErrorEvt const &cfm = ERROR_EVT_CAST(*e);
            bool allReceived;
            if (!me->GetHsm().HandleCfmRsp(cfm, allReceived)) {
                Evt *evt = new Failed(GET_HSMN(), cfm.GetError(), cfm.GetOrigin(), cfm.GetReason());
                me->PostSync(evt);
            } else if (allReceived) {
                Evt *evt = new Evt(DONE, GET_HSMN());
                me->PostSync(evt);
            }
            return Q_HANDLED();
        }
        case FAILED:
        case STATE_TIMER: {
            EVENT(e);
            Evt *evt;
            if (e->sig == FAILED) {
                ErrorEvt const &failed = ERROR_EVT_CAST(*e);
                evt = new GuiMgrStartCfm(me->GetHsm().GetInHsmn(), GET_HSMN(), me->GetHsm().GetInSeq(),
                                            failed.GetError(), failed.GetOrigin(), failed.GetReason());
            } else {
                evt = new GuiMgrStartCfm(me->GetHsm().GetInHsmn(), GET_HSMN(), me->GetHsm().GetInSeq(), ERROR_TIMEOUT, GET_HSMN());
            }
            Fw::Post(evt);
            return Q_TRAN(&GuiMgr::Stopping);
        }
        case DONE: {
            EVENT(e);
            Evt *evt = new GuiMgrStartCfm(me->GetHsm().GetInHsmn(), GET_HSMN(), me->GetHsm().GetInSeq(), ERROR_SUCCESS);
            Fw::Post(evt);
            return Q_TRAN(&GuiMgr::Started);
        }
    }
    return Q_SUPER(&GuiMgr::Root);
}

QState GuiMgr::Stopping(GuiMgr * const me, QEvt const * const e) {
    switch (e->sig) {
        case Q_ENTRY_SIG: {
            EVENT(e);
            uint32_t timeout = GuiMgrStopReq::TIMEOUT_MS;
            FW_ASSERT(timeout > LedFrameStopReq::TIMEOUT_MS);
            me->m_stateTimer.Start(timeout);
            me->GetHsm().ResetOutSeq();
            Evt *evt = new LedFrameStopReq(LED_FRAME, GET_HSMN(), GEN_SEQ());
            me->GetHsm().SaveOutSeq(*evt);
            Fw::Post(evt);
            return Q_HANDLED();
        }
        case Q_EXIT_SIG: {
            EVENT(e);
            me->m_stateTimer.Stop();
            me->GetHsm().ClearInSeq();
            me->GetHsm().Recall();
            return Q_HANDLED();
        }
        case GUI_MGR_STOP_REQ: {
            EVENT(e);
            me->GetHsm().Defer(e);
            return Q_HANDLED();
        }
        case LED_FRAME_STOP_CFM: {
            EVENT(e);
            ErrorEvt const &cfm = ERROR_EVT_CAST(*e);
            bool allReceived;
            if (!me->GetHsm().HandleCfmRsp(cfm, allReceived)) {
                Evt *evt = new Failed(GET_HSMN(), cfm.GetError(), cfm.GetOrigin(), cfm.GetReason());
                me->PostSync(evt);
            } else if (allReceived) {
                Evt *evt = new Evt(DONE, GET_HSMN());
                me->PostSync(evt);
            }
            return Q_HANDLED();
        }
        case FAILED:
        case STATE_TIMER: {
            EVENT(e);
            FW_ASSERT(0);
            // Will not reach here.
            return Q_HANDLED();
        }
        case DONE: {
            EVENT(e);
            Evt *evt = new GuiMgrStopCfm(me->GetHsm().GetInHsmn(), GET_HSMN(), me->GetHsm().GetInSeq(), ERROR_SUCCESS);
            Fw::Post(evt);
            return Q_TRAN(&GuiMgr::Stopped);
        }
    }
    return Q_SUPER(&GuiMgr::Root);
}

QState GuiMgr::Started(GuiMgr * const me, QEvt const * const e) {
    switch (e->sig) {
        case Q_ENTRY_SIG: {
            EVENT(e);
            // Activate the use of memory device feature.
            WM_SetCreateFlags(WM_CF_MEMDEV);
            // Init the STemWin GUI Library.
            GUI_Init();
            // Test only.
            GUI_EnableAlpha(0);

            me->m_dirty = false;
            WM_HWIN handle = me->m_bgWnd.Create(me, 0, 0, 128, 128, &WmCallback);
            LOG("bgWnd win handle = %d", handle);
            me->AddWin(handle, PAINT_BGWND);
            me->m_bgWnd.SetColorIdx(128, 767, GuiBgWnd::GRADIENT_V);
            //me->m_bgWnd.SetColor(0x00ffffff, 0x00ffffff);
            WM_Exec();
            me->m_bgWndTimer.Start(BG_WND_TIMEOUT_MS, Timer::PERIODIC);
            return Q_HANDLED();
        }
        case Q_EXIT_SIG: {
            EVENT(e);
            me->RemoveWin(me->m_bgWnd.Destroy());
            me->m_bgWndTimer.Stop();
            GUI_Exit();
            return Q_HANDLED();
        }
        case Q_INIT_SIG: {
            //return Q_TRAN(&GuiMgr::Ticker);
            return Q_TRAN(&GuiMgr::Bmp);
        }
        case BG_WND_TIMER: {
            EVENT(e);
            me->m_bgWnd.Update(1);
            WM_Exec();
            return Q_HANDLED();
        }
        case PAINT_BGWND:{
            EVENT(e);
            //WmEvent const &wmEvt = static_cast<WmEvent const &>(*e);
            //LOG("PAINT_BGWND msgId=0x%x", wmEvt.GetMsgId());
            me->m_bgWnd.Paint();
            me->m_dirty = true;
            return Q_HANDLED();
        }
        case LED_PANEL_SYNC_IND: {
            EVENT(e);
            if (me->m_dirty) {
                Evt *evt = new LedFrameUpdateReq(LED_FRAME, me->GetHsmn(), me->GenSeq());
                Fw::Post(evt);
                me->m_dirty = false;
            }
            // Drives all timers with tick rate of 1.
            QP::QF::tickX_(TICK_RATE_GUIMGR);
            return Q_HANDLED();
        }
    }
    return Q_SUPER(&GuiMgr::Root);
}

QState GuiMgr::Ticker(GuiMgr * const me, QEvt const * const e) {
    switch (e->sig) {
        case Q_ENTRY_SIG: {
            EVENT(e);
            WM_HWIN handle;
            handle = me->m_ticker1.Create(me, me->m_bgWnd.GetHandle(), 1, 1, 126, 30, 0x040404, &WmCallback);
            me->AddWin(handle, PAINT_TICKER1);
            me->m_ticker1.SetText(0, "Gallium Studio        ",
                                  GUI_FONT_16B_ASCII, 0xa352cc, 0x000000);
            me->m_ticker1.SetText(1, "Promoting STEM with Design     ",
                                  GUI_FONT_16B_ASCII, 0x000000, 0xa352cc);
            me->m_ticker1.SetText(2, "Visit www.galliumstudio.com       ",
                                  GUI_FONT_16B_ASCII, 0xff6600, 0x000000);
            me->m_ticker1Timer.Start(GetTimeout(m_ticker1Timeout, ARRAY_COUNT(m_ticker1Timeout), 0, 0));

            handle = me->m_ticker2.Create(me, me->m_bgWnd.GetHandle(), 1, 33, 126, 30, 0x040404, &WmCallback);
            LOG("ticker2 win handle = %d", handle);
            me->AddWin(handle, PAINT_TICKER2);
            me->m_ticker2.SetText(0, "Using full statechart design. Interrupts at every 8us.    ",
                                  GUI_FONT_16B_ASCII, 0xa352cc, 0x000000);
            me->m_ticker2Timer.Start(GetTimeout(m_ticker2Timeout, ARRAY_COUNT(m_ticker2Timeout), 0, 0));

            handle = me->m_ticker3.Create(me, me->m_bgWnd.GetHandle(), 1, 65, 126, 30, 0x040404, &WmCallback);
            LOG("ticker3 win handle = %d", handle);
            me->AddWin(handle, PAINT_TICKER3);
            me->m_ticker3.SetText(0, "with Quantum Platform and emWin.   ",
                                  GUI_FONT_16B_ASCII, 0xa352cc, 0x000000);
            me->m_ticker3Timer.Start(GetTimeout(m_ticker3Timeout, ARRAY_COUNT(m_ticker3Timeout), 0, 0));

            handle = me->m_ticker4.Create(me, me->m_bgWnd.GetHandle(), 1, 97, 126, 30, 0x040404, &WmCallback);
            LOG("ticker4 win handle = %d", handle);
            me->AddWin(handle, PAINT_TICKER4);
            me->m_ticker4.SetText(0, "Produced by Gallium Studio 2019.  ",
                                  GUI_FONT_16B_ASCII, 0xa352cc, 0x000000);
            me->m_ticker4Timer.Start(GetTimeout(m_ticker4Timeout, ARRAY_COUNT(m_ticker4Timeout), 0, 0));

            WM_Exec();
            return Q_HANDLED();
        }
        case Q_EXIT_SIG: {
            EVENT(e);
            me->RemoveWin(me->m_ticker1.Destroy());
            me->m_ticker1Timer.Stop();
            me->RemoveWin(me->m_ticker2.Destroy());
            me->m_ticker2Timer.Stop();
            me->RemoveWin(me->m_ticker3.Destroy());
            me->m_ticker3Timer.Stop();
            me->RemoveWin(me->m_ticker4.Destroy());
            me->m_ticker4Timer.Stop();
            return Q_HANDLED();
        }
        case Q_INIT_SIG: {
            return Q_TRAN(&GuiMgr::TickerNormal);
        }
        case PAINT_TICKER1: {
            EVENT(e);
            me->m_ticker1.Paint();
            me->m_dirty = true;
            return Q_HANDLED();
        }
        case PAINT_TICKER2: {
            EVENT(e);
            me->m_ticker2.Paint();
            me->m_dirty = true;
            return Q_HANDLED();
        }
        case PAINT_TICKER3: {
            EVENT(e);
            me->m_ticker3.Paint();
            me->m_dirty = true;
            return Q_HANDLED();
        }
        case PAINT_TICKER4: {
            EVENT(e);
            me->m_ticker4.Paint();
            me->m_dirty = true;
            return Q_HANDLED();
        }
        case TICKER1_TIMER: {
            EVENT(e);
            uint32_t bufIdx;
            uint32_t offsetLeft;
            uint32_t offsetRight;
            me->m_ticker1.Update(-1, bufIdx, offsetLeft, offsetRight);
            me->m_ticker1Timer.Restart(GetTimeout(m_ticker1Timeout, ARRAY_COUNT(m_ticker1Timeout), offsetLeft, offsetRight));
            WM_Exec();
            return Q_HANDLED();
        }
        case TICKER2_TIMER: {
            EVENT(e);
            uint32_t bufIdx;
            uint32_t offsetLeft;
            uint32_t offsetRight;
            me->m_ticker2.Update(-1, bufIdx, offsetLeft, offsetRight);
            me->m_ticker2Timer.Restart(GetTimeout(m_ticker2Timeout, ARRAY_COUNT(m_ticker2Timeout), offsetLeft, offsetRight));
            WM_Exec();
            return Q_HANDLED();
        }
        case TICKER3_TIMER: {
            EVENT(e);
            uint32_t bufIdx;
            uint32_t offsetLeft;
            uint32_t offsetRight;
            me->m_ticker3.Update(-1, bufIdx, offsetLeft, offsetRight);
            me->m_ticker3Timer.Restart(GetTimeout(m_ticker3Timeout, ARRAY_COUNT(m_ticker3Timeout), offsetLeft, offsetRight));
            WM_Exec();
            return Q_HANDLED();
        }
        case TICKER4_TIMER: {
            EVENT(e);
            uint32_t bufIdx;
            uint32_t offsetLeft;
            uint32_t offsetRight;
            me->m_ticker4.Update(-1, bufIdx, offsetLeft, offsetRight);
            me->m_ticker4Timer.Restart(GetTimeout(m_ticker4Timeout, ARRAY_COUNT(m_ticker4Timeout), offsetLeft, offsetRight));
            WM_Exec();
            return Q_HANDLED();
        }
    }
    return Q_SUPER(&GuiMgr::Started);
}

QState GuiMgr::TickerNormal(GuiMgr * const me, QEvt const * const e) {
    switch (e->sig) {
        case Q_ENTRY_SIG: {
            EVENT(e);
            return Q_HANDLED();
        }
        case Q_EXIT_SIG: {
            EVENT(e);
            return Q_HANDLED();
        }
    }
    return Q_SUPER(&GuiMgr::Ticker);
}

QState GuiMgr::TickerAlert(GuiMgr * const me, QEvt const * const e) {
    switch (e->sig) {
        case Q_ENTRY_SIG: {
            EVENT(e);
            return Q_HANDLED();
        }
        case Q_EXIT_SIG: {
            EVENT(e);
            return Q_HANDLED();
        }
    }
    return Q_SUPER(&GuiMgr::Ticker);
}


QState GuiMgr::Bmp(GuiMgr * const me, QEvt const * const e) {
    switch (e->sig) {
        case Q_ENTRY_SIG: {
            EVENT(e);
            WM_HWIN handle = me->m_bmp.Create(me, me->m_bgWnd.GetHandle(), 0, 0, 128, 128, &WmCallback);
            LOG("bmp win handle = %d", handle);
            me->AddWin(handle, PAINT_BMP);
            uint32_t bmpCnt = ARRAY_COUNT(guiBitmap);
            for (uint32_t i=0; i<bmpCnt && i<GuiBmp::IMG_CNT; i++) {
                me->m_bmp.SetBitmap(i, guiBitmap[i]);
            }
            me->m_bmpTimer.Start(GetTimeout(m_bmpTimeout, ARRAY_COUNT(m_bmpTimeout), 0, 0));
            WM_Exec();
            return Q_HANDLED();
        }
        case Q_EXIT_SIG: {
            EVENT(e);
            me->RemoveWin(me->m_bmp.Destroy());
            me->m_bmpTimer.Stop();
            return Q_HANDLED();
        }
        case Q_INIT_SIG: {
            return Q_TRAN(&GuiMgr::BmpNormal);
        }
        case PAINT_BMP: {
            EVENT(e);
            me->m_bmp.Paint();
            me->m_dirty = true;
            return Q_HANDLED();
        }
        case BMP_TIMER: {
            EVENT(e);
            uint32_t imgIdx = 0;
            uint32_t offsetLeft = 0;
            uint32_t offsetRight = 0;
            me->m_bmp.Update(-1, imgIdx, offsetLeft, offsetRight);
            me->m_bmpTimer.Start(GetTimeout(m_bmpTimeout, ARRAY_COUNT(m_bmpTimeout), offsetLeft, offsetRight));
            WM_Exec();
            if (offsetLeft == 1) {
                me->m_bmpCycleCnt++;
                if (me->m_bmpCycleCnt >= ARRAY_COUNT(guiBitmap)) {
                    // Commented to stay in bmp state.
                    // @todo Needs to reset m_bmpCycleCnt to 0.
                    //return Q_TRAN(&GuiMgr::Ticker);
                }
            }
            return Q_HANDLED();
        }
    }
    return Q_SUPER(&GuiMgr::Started);
}

QState GuiMgr::BmpNormal(GuiMgr * const me, QEvt const * const e) {
    switch (e->sig) {
        case Q_ENTRY_SIG: {
            EVENT(e);
            return Q_HANDLED();
        }
        case Q_EXIT_SIG: {
            EVENT(e);
            return Q_HANDLED();
        }
    }
    return Q_SUPER(&GuiMgr::Bmp);
}

QState GuiMgr::BmpAlert(GuiMgr * const me, QEvt const * const e) {
    switch (e->sig) {
        case Q_ENTRY_SIG: {
            EVENT(e);
            return Q_HANDLED();
        }
        case Q_EXIT_SIG: {
            EVENT(e);
            return Q_HANDLED();
        }
    }
    return Q_SUPER(&GuiMgr::Bmp);
}

/*
QState GuiMgr::MyState(GuiMgr * const me, QEvt const * const e) {
    switch (e->sig) {
        case Q_ENTRY_SIG: {
            EVENT(e);
            return Q_HANDLED();
        }
        case Q_EXIT_SIG: {
            EVENT(e);
            return Q_HANDLED();
        }
        case Q_INIT_SIG: {
            return Q_TRAN(&GuiMgr::SubState);
        }
    }
    return Q_SUPER(&GuiMgr::SuperState);
}
*/

} // namespace APP
