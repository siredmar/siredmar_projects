/** The byte code for setting the baudrate of the GPS receiver */
static char EEMEM baud [] = {0xB5,0x62,0x06,0x00,0x14,0x00,0x01,0x00,
                             0x00,0x00,0xD0,0x08,0x00,0x00,0x00,0x4B,
                             0x00,0x00,0x03,0x00,0x02,0x00,0x00,0x00,
                             0x00,0x00,0x43,0x31};

/** turn on VTG */
static char EEMEM vtg_on[] = {"$PUBX,40,VTG,0,1,0,0*5F\r\n"};
/** turn on RMC */
static char EEMEM rmc_on[] = {"$PUBX,40,RMC,0,1,0,0*46\r\n"};
/** turn on GGA */
static char EEMEM gga_on[] = {"$PUBX,40,GGA,0,1,0,0*5B\r\n"};
/** turn off GSA */
static char EEMEM gsa_off[] = {"$PUBX,40,GSA,0,0,0,0*4E\r\n"};
/** turn off GRS */
static char EEMEM grs_off[] = {"$PUBX,40,GRS,0,0,0,0*5D\r\n"};
/** turn off GSV */
static char EEMEM gsv_off[] = {"$PUBX,40,GSV,0,0,0,0*59\r\n"};
/** turn off ZDA */
static char EEMEM zda_off[] = {"$PUBX,40,ZDA,0,0,0,0*44\r\n"};
/** turn off GST */
static char EEMEM gst_off[] = {"$PUBX,40,GST,0,0,0,0*5B\r\n"};
/** turn off GLL */
static char EEMEM gll_off[] = {"$PUBX,40,GLL,0,0,0,0*5C\r\n"};