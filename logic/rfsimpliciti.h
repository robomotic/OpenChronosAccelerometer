// *************************************************************************************************
//
//	Copyright (C) 2009 Texas Instruments Incorporated - http://www.ti.com/
//
//
//	  Redistribution and use in source and binary forms, with or without
//	  modification, are permitted provided that the following conditions
//	  are met:
//
//	    Redistributions of source code must retain the above copyright
//	    notice, this list of conditions and the following disclaimer.
//
//	    Redistributions in binary form must reproduce the above copyright
//	    notice, this list of conditions and the following disclaimer in the
//	    documentation and/or other materials provided with the
//	    distribution.
//
//	    Neither the name of Texas Instruments Incorporated nor the names of
//	    its contributors may be used to endorse or promote products derived
//	    from this software without specific prior written permission.
//
//	  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
//	  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
//	  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
//	  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
//	  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
//	  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
//	  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//	  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//	  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//	  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
//	  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// *************************************************************************************************

#ifndef RFSIMPLICITI_H_
#define RFSIMPLICITI_H_

// *************************************************************************************************
// Include section


// *************************************************************************************************
// Prototypes section
extern void reset_rf(void);
extern void sx_rf(uint8_t line);
extern void sx_ppt(uint8_t line);
extern void sx_sync(uint8_t line);
extern void display_rf(uint8_t line, uint8_t update);
extern void display_ppt(uint8_t line, uint8_t update);
extern void display_sync(uint8_t line, uint8_t update);
extern void send_smpl_data(uint16_t data);
extern uint8_t is_rf(void);

// *************************************************************************************************
// Defines section

// SimpliciTI connection states
typedef enum {
	SIMPLICITI_OFF = 0,       // Not connected
#ifdef CONFIG_ACCEL
	SIMPLICITI_ACCELERATION,	// Transmitting acceleration data and button events
#endif
	SIMPLICITI_BUTTONS,		// Transmitting button events
	SIMPLICITI_SYNC,			// Syncing
#ifdef CONFIG_PHASE_CLOCK
	SIMPLICITI_PHASE_CLOCK_START,	// Start new phase
	SIMPLICITI_PHASE_CLOCK,	// Phase Clock is running
#endif
} simpliciti_mode_t;

// Stop SimpliciTI transmission after 60 minutes to save power
#define SIMPLICITI_TIMEOUT									(60*60u)

// Button flags for SimpliciTI data
#define SIMPLICITI_BUTTON_STAR			(0x10)
#define SIMPLICITI_BUTTON_NUM			(0x20)
#define SIMPLICITI_BUTTON_UP			(0x30)

// SimpliciTI mode flag
#define SIMPLICITI_MOUSE_EVENTS             (0x01)
#define SIMPLICITI_KEY_EVENTS               (0x02)
#define SIMPLICITI_PHASE_CLOCK_EVENTS   	(0x03)
#define SIMPLICITI_PHASE_CLOCK_START_EVENTS	(0x04)

// notify the ap that sync mode started
#define SIMPLICITI_SYNC_STARTED_EVENTS      (0x10)


#define WATCH_ID(dst,offset) \
	dst[offset] = simpliciti_ed_address[0] ^ simpliciti_ed_address[1];\
	dst[offset+1] = simpliciti_ed_address[2] ^ simpliciti_ed_address[3];



#define SIMPLICITI_PHASE_CLOCK_START_RESPONSE	(0x54)

// *************************************************************************************************
// Global Variable section
/* TODO: pack this stufff!!!! */
struct RFsmpl
{
	// SIMPLICITI_OFF, SIMPLICITI_ACCELERATION, SIMPLICITI_BUTTONS
	simpliciti_mode_t 	mode;

	// Timeout until SimpliciTI transmission is automatically stopped
	uint16_t					timeout;

};
extern struct RFsmpl sRFsmpl;

extern unsigned char simpliciti_flag;

// *************************************************************************************************
// Extern section
#ifdef SIMPLICITY_TX_ONLY_REQ
extern void start_simpliciti_tx_only(simpliciti_mode_t mode);
#endif

extern int simpliciti_get_rvc_callback(uint8_t len) __attribute__((noinline));


#endif /*RFSIMPLICITI_H_*/
