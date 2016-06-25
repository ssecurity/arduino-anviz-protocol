/* Arduino impl of Anviz protocol
 * Date: 2016-06-25
 * Author: Korotkikh Sergei
 * Location: Russia, St.Petersburg
 * Contacts: reg51ru@gmail.com
 */

// DEVICE STATE ANSWERS
#define ACK_SUCCESS 0x00                    // operation successful
#define ACK_FAIL 0x01                       // operation failed
#define ACK_FULL 0x04                       // user full
#define ACK_EMPTY 0x05                      // user empty
#define ACK_NO_USER 0x06                    // user not exist
#define ACK_TIME_OUT 0x08                   //capture timeout
#define ACK_USER_OCCUPIED 0x0A              //user already exists
#define ACK_FINGER_OCCUPIED 0x0B            //fingerprint already exists

// COMMANDS
#define CMD_P761_UPD_FIRMWARE 0x10          //only 761 platform. Update firmware, photo, voice
#define CMD_P761_FILE_OPER 0x12             //only 761 platform. directory file operation
#define CMD_P761_GET_LOG_RECOED 0x13        //only 761 platform. Download log record
#define CMD_ALL_GET_GPRS_PARAMS 0x16        //Get GPRS parameter
#define CMD_ALL_SET_GPRS_PARAMS 0x17        //Set GPRS parameter
#define CMD_ALL_GET_OPT_LANG 0x18           //Read optional language combination
#define CMD_ALL_SET_OPT_LANG 0x19           //Set optional language combination
#define CMD_ALL_GET_DAYLIGHT_PRM 0x1A       //Read daylight saving parameter
#define CMD_ALL_SET_DAYLIGHT_PRM 0x1B       //Set daylight saving time parameter
#define CMD_T5_GET_ADMIN_CARD 0x1C          //only T5. Read admin card number/admin password
#define CMD_T5_SET_ADMIN_CARD 0x1D          //only T5. Read optional language combination
#define CMD_OA3000_GET_ASWITCH 0x20         //only for OA3000 & OA1000. Get T&A state auto switch setting
#define CMD_OA3000_SET_ASWITCH 0x21         //only for OA3000 & OA1000. Set T&A state auto switch setting
#define CMD_P761_GET_STAFF_EXT 0x22         //only 761 platform. Download staff information (extended)
#define CMD_P761_SET_STAFF_EXT 0x23         //only 761 platform. Upload staff information (extend)
#define CMD_ALL_GET_DEV_SN 0x24             //Get device serial number
#define CMD_ALL_SET_DEV_SN 0x25             //Modify device serial number
#define CMD_OA3000_GET_MSG_ID 0x26          //only for OA3000. Get specified index message
#define CMD_OA3000_ADD_MSG 0x27             //only for OA3000. Add new message
#define CMD_OA3000_GET_MSG_LIST 0x28        //only for OA3000. Read message head of assigned section message
#define CMD_OA3000_DEL_MSG 0x29             //only for OA3000. Delete appointed index message
#define CMD_OA3000_GET_PHOTO_CNT 0x2A       //OA1000/OA3000/761platform. Get photo amount
#define CMD_OA3000_GET_PHOTO_HEAD 0x2B      //OA1000/OA3000/761platform. Get photo head information
#define CMD_OA3000_GET_PHOTO 0x2C           //OA1000/OA3000/761platform. Read specified photo file
#define CMD_OA3000_DEL_PHOTO 0x2D           //OA1000/OA3000/761platform. Delete specified photo
#define CMD_V30_GET_SPEC_STATE 0x2F         //VF30/VP30/T60+use only. Get special state
#define CMD_ALL_GET_INFO 0x30               //Get the information of T&A device 1
#define CMD_ALL_SET_INFO 0x31               //Set the configure information of T&A 1
#define CMD_ALL_GET_INFO2 0x32              //Get the information of T&A device 2
#define CMD_ALL_SET_INFO2 0x33              //Set the configure information of T&A 2
#define CMD_ALL_GET_TIME 0x38               //Get the date and time of T&A
#define CMD_ALL_SET_TIME 0x39               //Set the date and time of T&A
#define CMD_ALL_GET_TCPPARAMS 0x3A          //Get TCP/IP parameters
#define CMD_ALL_SET_TCPPARAMS 0x3B          //Set TCP/IP parameters
#define CMD_ALL_GET_RECORD_INFO 0x3C        // Get record information
#define CMD_ALL_CLEAR_ADM_FLAG 0x3D         //Clear administrator flag
#define CMD_ALL_GET_ENROLL_DATE 0x3E        //Read employees enrollment timestamp
#define CMD_ALL_SET_ENROLL_DATE 0x3F        //Set time stamp
#define CMD_ALL_GET_RECORDS 0x40            //Download T&A records
#define CMD_ALL_SET_RECORDS 0x41            //Upload T&A records
#define CMD_ALL_GET_STAFF 0x42              //Download staff info
#define CMD_ALL_SET_STAFF 0x43              //Upload staff info
#define CMD_ALL_GET_FP_TPL 0x44             //Download FP Template
#define CMD_ALL_SET_FP_TPL 0x45             //Upload FP Template
#define CMD_ALL_GET_SN 0x46                 //Get device S/N
#define CMD_ALL_SET_SN 0x47                 //Modify device S/N
#define CMD_ALL_GET_TYPE 0x48               //Get device type code
#define CMD_ALL_SET_TYPE 0x49               //Modify device type code
#define CMD_ALL_GET_FACTORY 0x4A            //Get the factory info code
#define CMD_ALL_SET_FACTORY 0x4B            //Modify the factory info code
#define CMD_ALL_DEL_USERDATA 0x4C           //Delete the designated user data
#define CMD_ALL_INIT_USERAREA 0x4D          //Initialize the user area
#define CMD_ALL_CLR_RECORDS 0x4E            //Clear up Records /Clear new records sign
#define CMD_ALL_INIT_SYSTEM 0x4F            //Initialize System
#define CMD_ALL_GET_TIMEZONE 0x50           //Get the time zone info
#define CMD_ALL_SET_TIMEZONE 0x51           //Set time zone info
#define CMD_ALL_GET_GROUPINFO 0x52          //Get the group info
#define CMD_ALL_SET_GROUPINFO 0x53          //Set the group info
#define CMD_ALL_GET_BELL_TASKS 0x54         //Get the scheduled bell info
#define CMD_ALL_SET_BELL_TASKS 0x55         //Set ring info
#define CMD_ALL_GET_SPEC_MSG 0x56           //Retrieve specified short message
#define CMD_ALL_ADD_SPEC_MSG 0x57           //Add short message
#define CMD_ALL_READ_ALL_SPEC_MSG 0x58      //Read all info head of all short message
#define CMD_ALL_DEL_SPEC_MSG 0x59           //Delete specified index short messageage
#define CMD_ALL_GET_MSG_STATE 0x5A          //Get T&A State message
#define CMD_ALL_SET_PARAM_TBL 0x5B          //Set T&A State parameter table
#define CMD_ALL_ENROLL_USER_FP 0x5C         //Enroll user FP online
#define CMD_ALL_GET_CAPACITY 0x5D           //Get device capacity parameter
#define CMD_ALL_OPEN_DOOR 0x5E              // Output signal to open lock without verifying user
#define CMD_ALL_SENT_RECORD 0x5F            //Sent T&A record in real time
#define CMD_ALL_GET_CUST_TBL 0x70           //Get customized T&A state table
#define CMD_ALL_SET_CUST_TBL 0x71           //Set attendance state table
#define CMD_ALL_GET_STAFF_DATA 0x72         //Download employees data
#define CMD_ALL_SET_STAFF_DATA 0x73         //Upload staff information(extended)
#define CMD_ALL_GET_COM_DEVID 0x74          //Get communication device ID
#define CMD_ALL_SET_COM_DEVID 0x75          //Modify communication device ID
#define CMD_ALL_GET_RANDOM 0x76             //Read random number
#define CMD_ALL_ENC_DEVINFO 0x77            //Encrypt device type and language with random number
#define CMD_ALL_RETR_FEATURE_VAL 0x78       //Receive feature value /card ID to execute following operation
#define CMD_ALL_GET_DEVICE_INFO_EXT 0x7A    //Get device extended information code
#define CMD_ALL_SET_DEVICE_INFO_EXT 0x7B    //Modify device extend message code
#define CMD_T5S_INQUIRE_CARD_INFO 0x7E      //T5S only. inquire information of card number
#define CMD_C5_EMAIL_SETTINGS 0x7F          //C5 only. Sending Email

// Special settings
#define RXTX_PAUSE_TIME_MS 300              //Pause between RX and TX for correct communication
#
//

bool resp_command_started = false;          // Marker for start answer
String resp_command_buffer = String("");    // buffer for answer
unsigned long sending_timeout = 0;          // time then next command will sent 






// crc16 bits
unsigned short _crc_table[] = {
    0x0000,0x1189,0x2312,0x329b,0x4624,0x57ad,0x6536,0x74bf,0x8c48,0x9dc1,
    0xaf5a,0xbed3,0xca6c,0xdbe5,0xe97e,0xf8f7,0x1081,0x0108,0x3393,0x221a,
    0x56a5,0x472c,0x75b7,0x643e,0x9cc9,0x8d40,0xbfdb,0xae52,0xdaed,0xcb64,
    0xf9ff,0xe876,0x2102,0x308b,0x0210,0x1399,0x6726,0x76af,0x4434,0x55bd,
    0xad4a,0xbcc3,0x8e58,0x9fd1,0xeb6e,0xfae7,0xc87c,0xd9f5,0x3183,0x200a,
    0x1291,0x0318,0x77a7,0x662e,0x54b5,0x453c,0xbdcb,0xac42,0x9ed9,0x8f50,
    0xfbef,0xea66,0xd8fd,0xc974,0x4204,0x538d,0x6116,0x709f,0x0420,0x15a9,
    0x2732,0x36bb,0xce4c,0xdfc5,0xed5e,0xfcd7,0x8868,0x99e1,0xab7a,0xbaf3,
    0x5285,0x430c,0x7197,0x601e,0x14a1,0x0528,0x37b3,0x263a,0xdecd,0xcf44,
    0xfddf,0xec56,0x98e9,0x8960,0xbbfb,0xaa72,0x6306,0x728f,0x4014,0x519d,
    0x2522,0x34ab,0x0630,0x17b9,0xef4e,0xfec7,0xcc5c,0xddd5,0xa96a,0xb8e3,
    0x8a78,0x9bf1,0x7387,0x620e,0x5095,0x411c,0x35a3,0x242a,0x16b1,0x0738,
    0xffcf,0xee46,0xdcdd,0xcd54,0xb9eb,0xa862,0x9af9,0x8b70,0x8408,0x9581,
    0xa71a,0xb693,0xc22c,0xd3a5,0xe13e,0xf0b7,0x0840,0x19c9,0x2b52,0x3adb,
    0x4e64,0x5fed,0x6d76,0x7cff,0x9489,0x8500,0xb79b,0xa612,0xd2ad,0xc324,
    0xf1bf,0xe036,0x18c1,0x0948,0x3bd3,0x2a5a,0x5ee5,0x4f6c,0x7df7,0x6c7e,
    0xa50a,0xb483,0x8618,0x9791,0xe32e,0xf2a7,0xc03c,0xd1b5,0x2942,0x38cb,
    0x0a50,0x1bd9,0x6f66,0x7eef,0x4c74,0x5dfd,0xb58b,0xa402,0x9699,0x8710,
    0xf3af,0xe226,0xd0bd,0xc134,0x39c3,0x284a,0x1ad1,0x0b58,0x7fe7,0x6e6e,
    0x5cf5,0x4d7c,0xc60c,0xd785,0xe51e,0xf497,0x8028,0x91a1,0xa33a,0xb2b3,
    0x4a44,0x5bcd,0x6956,0x78df,0x0c60,0x1de9,0x2f72,0x3efb,0xd68d,0xc704,
    0xf59f,0xe416,0x90a9,0x8120,0xb3bb,0xa232,0x5ac5,0x4b4c,0x79d7,0x685e,
    0x1ce1,0x0d68,0x3ff3,0x2e7a,0xe70e,0xf687,0xc41c,0xd595,0xa12a,0xb0a3,
    0x8238,0x93b1,0x6b46,0x7acf,0x4854,0x59dd,0x2d62,0x3ceb,0x0e70,0x1ff9,
    0xf78f,0xe606,0xd49d,0xc514,0xb1ab,0xa022,0x92b9,0x8330,0x7bc7,0x6a4e,
    0x58d5,0x495c,0x3de3,0x2c6a,0x1ef1,0x0f78
    };

unsigned short crc16(byte data[], unsigned short datacount) {
    unsigned short i = 0;
    unsigned short crc = 0xffff;
    for(i = 0; i < datacount; i++) {
        byte b = data[i];
        crc = crc ^ b;
        crc = (crc >> 8) ^ _crc_table[crc & 0xff];
        }
    return crc;
    }

void sendCommand(byte command, unsigned long device_id, byte data[], unsigned short datacount) {
    unsigned short i = 0;
    unsigned short crc = 0x0000;
    byte outdata[9+datacount];
    for(i = 0; i < 10+datacount; i++) {
        outdata[i] = 0x00;
        }
    outdata[0] = 0xA5;
    outdata[1] = (device_id >> 24) % 256;
    outdata[2] = (device_id >> 16) % 256;
    outdata[3] = (device_id >> 8) % 256;
    outdata[4] = device_id % 256;
    outdata[5] = command;
    outdata[6] = (datacount >> 8) % 256;
    outdata[7] = datacount % 256;
    for(i = 0; i < datacount; i++) {
        outdata[8+i] = data[i];
        }
    crc = crc16(outdata,8+datacount);
    outdata[9+datacount] = (crc >> 8) % 256;
    outdata[8+datacount] = crc % 256;
    
    digitalWrite(22,HIGH);
    delay(50);
    for(i = 0; i < 10+datacount; i++) {
        if (outdata[i] < 16) {
            //Serial.print("0");
            }
        //Serial.print(outdata[i],HEX);
        Serial1.write(outdata[i]);
        }
    delay(50);
    digitalWrite(22,LOW);
    // reset start position of command 
    resp_command_started = false;
    
    
    }

/* == (0x30) Get the information of T&A device 1 == 
 * Get the firmware version, communication password, sleep time, volume, language, date
 * and time format, attendance state, language setting flag, command version.
 *
 * params @device_id - when is "0" then all devices connected will response to this command
 */
void getDeviceInfo(unsigned long device_id){
  sendCommand(CMD_ALL_GET_INFO,device_id,{},0);
  }


/* == (0x3C) Get record information 
 * Get record information, including the amount of Used User, Used FP, Used Password,
 * Used Card, All Attendance Record, and New Record
 *
 * params @device_id - when is "0" then all devices connected will response to this command
 */
void getStatistic(unsigned long device_id){
  sendCommand(CMD_ALL_GET_RECORD_INFO,device_id,{},0);
  }

/* == (0x5E) Output signal to open lock without verifying user 
 * Force T&A device output signal to open door
 *
 * params @device_id - when is "0" then all devices connected will response to this command
 */
void openDoor(unsigned long device_id){
  sendCommand(CMD_ALL_OPEN_DOOR,device_id,{},0);
  }

/* Wait answer and stock it in buffer
 */
void stock_device_answer() {
  while (Serial1.available() > 0) {
    byte b = Serial1.read();
    if (!resp_command_started) {
      if (b == 0xA5) { 
        // mark position of new command
        resp_command_started = true;
        }
      } 
    if (resp_command_started) {
      // move time for next command 
      sending_timeout = millis() + RXTX_PAUSE_TIME_MS;
      // display answer
      Serial.print(b < 16 ? "0" : "");
      Serial.print(b, HEX);
      }  
    }
  }

void setup() {
  pinMode(22,OUTPUT);
  digitalWrite(22,LOW);  
  Serial1.begin(9600);
  Serial.begin(9600);
  Serial.println("Start..");
  delay(2000);
  getStatistic(0);
  }

void loop() {
  //
  stock_device_answer();
    
}
