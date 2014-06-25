// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// + Copyright (c) 2008 Stephan Busker
// + Nur für den privaten Gebrauch
// + FOR NON COMMERCIAL USE ONLY
// + www.Mikro-control.de
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// + Es gilt für das gesamte Projekt (Hardware, Software, Binärfiles, Sourcecode und Dokumentation),
// + dass eine Nutzung (auch auszugsweise) nur für den privaten (nicht-kommerziellen) Gebrauch zulässig ist.
// + Sollten direkte oder indirekte kommerzielle Absichten verfolgt werden, ist mit uns (stephan.busker@mikro-control.de) Kontakt
// + bzgl. der Nutzungsbedingungen aufzunehmen.
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// + Keine Gewähr auf Fehlerfreiheit, Vollständigkeit oder Funktion
// + Benutzung auf eigene Gefahr
// + Wir übernehmen keinerlei Haftung für direkte oder indirekte Personen- oder Sachschäden
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// + Redistributions of source code (with or without modifications) must retain the above copyright notice,
// + this list of conditions and the following disclaimer.
// +   * Neither the name of the copyright holders nor the names of contributors may be used to endorse or promote products derived
// +     from this software without specific prior written permission.
// +   * The use of this project (hardware, software, binary files, sources and documentation) is only permitted
// +     for non-commercial use (directly or indirectly)
// +     Commercial use is only permitted with our written permission
//
// +  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// +  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// +  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// +  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
// +  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// +  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// +  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// +  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// +  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// +  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// +  POSSIBILITY OF SUCH DAMAGE.
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#ifndef _SDC_H
#define _SDC_H

#include "../datatypes.h"


#define SDC_DEBUG
#define CARD_DETECT (!(PINB & 0x08))


//CS_MMC
#define DDR_CS_MMC DDRB
#define DD_CS_MMC DDB3
#define PORT_CS_MMC PORTB
#define CS_MMC PB3

//DET_MMC
#define DDR_DET_MMC DDRB
#define DD_DET_MMC DDB2
#define PIN_DET_MMC PINB
#define PIN_DET_BIT_MMC PINB2

//COMMON_MMC
#define DDR_COMMON_MMC DDRB
#define DD_COMMON_MMC DDB0
#define PORT_COMMON_MMC PORTB
#define COMMON_MMC PB0

//WRITE_MMC
#define DDR_WRITE_MMC DDRB
#define DD_WRITE_MMC DDB1
#define PIN_WRITE_MMC PINB
#define PIN_WRITE_BIT_MMC PINB1

extern uint8_t sd_detected;
extern uint8_t sd_writeable;


//________________________________________________________________________________________________________________________________________
//
// Functions needed for accessing the sdcard.
//
//________________________________________________________________________________________________________________________________________

typedef enum
{
  SD_SUCCESS = 0,
  SD_ERROR_NOCARD,
  SD_ERROR_RESET,
  SD_ERROR_INITIALIZE,
  SD_ERROR_BAD_RESPONSE,
  SD_ERROR_BAD_VOLTAGE_RANGE,
  SD_ERROR_NO_SDCARD,
  SD_ERROR_TIMEOUT,
  SD_ERROR_CRC_DATA,
  SD_ERROR_WRITE_DATA,
  SD_ERROR_READ_DATA,
  SD_ERROR_SET_BLOCKLEN,
  SD_ERROR_UNKNOWN
} SD_Result_t;

void sd_init_status(void);
void sd_cs_select(void);
void sd_cs_unselect(void);
void sd_check_writeable(void);
void sd_check_detected(void);




extern SD_Result_t   SDC_Init(void);
extern SD_Result_t    SDC_GetSector (u32 ,u8 *);
extern SD_Result_t    SDC_PutSector (u32, const u8 *);
extern SD_Result_t   SDC_Deinit(void);

#endif // _SDC_H


