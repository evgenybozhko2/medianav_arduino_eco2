#include <mcp_can.h>

class CanProcessor {

    MCP_CAN *CAN_AUTO;
    MCP_CAN *CAN_MEDIANAV;

    unsigned char frame_315[8] = {0xFE, 0xFE, 0xFE, 0x00, 0x3E, 0xFE, 0xFF, 0xF0};
    unsigned char frame_558[8] = {0xFE, 0xFE, 0xFE, 0x78, 0xCF, 0x07, 0xF3, 0x00};
    unsigned char frame_568[8] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00};
    unsigned char frame_548[8] = {0xFF, 0xFF, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00};
    unsigned char frame_578[8] = {0xFF, 0xFF, 0xFF, 0xF0, 0xC5, 0x00, 0x00, 0x00};
    unsigned char frame_58C[8] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0x00};
    unsigned char frame_5A8[8] = {0x41, 0x7F, 0xFF, 0x7F, 0xFF, 0x98, 0x00, 0x00};
    unsigned char frame_588[8] = {0x03, 0xFF, 0x7F, 0x03, 0xFF, 0xFF, 0xFF, 0xFC};
    unsigned char frame_559[8] = {0x00, 0x38, 0x38, 0xFE, 0xFE, 0x00, 0x00, 0x00};
    unsigned char frame_32D[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    unsigned char frame_319[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    unsigned char frame_4DE[8] = {0xFF, 0xFF, 0xFF, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB};
    unsigned char frame_590[8] = {0xFF, 0xFF, 0xF0, 0x3D, 0xF0, 0xF0, 0x00, 0x00};
    unsigned char frame_58E[8] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0xFF, 0x00};
    unsigned char frame_038[8] = {0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    unsigned char frame_407[8] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xBB, 0xBB, 0xBB};
    unsigned char frame_58D[8] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    unsigned char frame_342[8] = {0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0xBB, 0xBB};
    unsigned char frame_31A[8] = {0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    unsigned char frame_341[8] = {0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xBB};
    unsigned char frame_409[8] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

  public: CanProcessor(MCP_CAN *CAN_AUTO, MCP_CAN *CAN_MEDIANAV) {
      this->CAN_AUTO = CAN_AUTO;
      this->CAN_MEDIANAV = CAN_MEDIANAV;
    }


    void handle() {
      // listen car side
      if (CAN_MSGAVAIL == CAN_AUTO->checkReceive()) {

        unsigned char can_auto_length = 0;
        unsigned char can_auto_buffer[8] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

        CAN_AUTO->readMsgBuf(&can_auto_length, can_auto_buffer);

        unsigned long messageID = CAN_AUTO->getCanId();

        switch (messageID) {
          // drive eco2 begin
          case 0x66A:
            frame_315[3] = can_auto_buffer[4];

            CAN_MEDIANAV->sendMsgBuf(0x315, 0, 8, frame_315);
            break;
          case 0x350:
            frame_315[4] = can_auto_buffer[5] * 2;

            CAN_MEDIANAV->sendMsgBuf(0x315, 0, 8, frame_315);
            break;
          case 0x648:
            frame_315[0] = can_auto_buffer[3] * 2;
            frame_315[2] = can_auto_buffer[5] * 2;

            int data = can_auto_buffer[4];
            bool isNeedScale = (data % 2) > 0;

            if (isNeedScale) {
              frame_315[1] = data - 0x01;
            } else {
              frame_315[1] = can_auto_buffer[4];
            }

            CAN_MEDIANAV->sendMsgBuf(0x315, 0, 8, frame_315);
            break;
          case 0x646:
            CAN_MEDIANAV->sendMsgBuf(0x314, 0, 8, can_auto_buffer);
            break;
          // drive eco2 end
          case 0x3B7:
            frame_558[0] = can_auto_buffer[2];
            frame_558[1] = can_auto_buffer[1];
            frame_558[2] = can_auto_buffer[0];

            CAN_MEDIANAV->sendMsgBuf(0x558, 0, 8, frame_558);
            break;
          case 0x5D7:
            frame_568[0] = can_auto_buffer[0];
            frame_568[1] = can_auto_buffer[1];

            CAN_MEDIANAV->sendMsgBuf(0x568, 0, 8, frame_568);

            frame_548[0] = can_auto_buffer[0];
            frame_548[1] = can_auto_buffer[1];

            CAN_MEDIANAV->sendMsgBuf(0x548, 0, 8, frame_548);

            frame_578[0] = can_auto_buffer[2];
            frame_578[1] = can_auto_buffer[3];
            frame_578[2] = can_auto_buffer[4];
            frame_578[3] = can_auto_buffer[5];

            CAN_MEDIANAV->sendMsgBuf(0x578, 0, 8, frame_578);
            break;
          case 0x69F:
            frame_568[2] = can_auto_buffer[0];
            frame_568[3] = can_auto_buffer[1];
            frame_568[4] = can_auto_buffer[2];
            frame_568[5] = can_auto_buffer[3];

            CAN_MEDIANAV->sendMsgBuf(0x568, 0, 8, frame_568);
            break;
          case 0x12E:
            frame_58C[0] = can_auto_buffer[0];
            frame_58C[1] = can_auto_buffer[1];
            frame_58C[2] = can_auto_buffer[2];
            frame_58C[5] = can_auto_buffer[3];
            frame_58C[6] = can_auto_buffer[4];

            CAN_MEDIANAV->sendMsgBuf(0x58C, 0, 8, frame_58C);
            break;
          case 0x06C:
            frame_58C[3] = can_auto_buffer[2];
            frame_58C[4] = can_auto_buffer[3];

            CAN_MEDIANAV->sendMsgBuf(0x58C, 0, 8, frame_58C);

            frame_5A8[1] = can_auto_buffer[0];
            frame_5A8[2] = can_auto_buffer[1];
            frame_5A8[3] = can_auto_buffer[4];
            frame_5A8[4] = can_auto_buffer[5];

            CAN_MEDIANAV->sendMsgBuf(0x5A8, 0, 8, frame_5A8);
            break;
          case 0x6FB:
            frame_588[1] = can_auto_buffer[2];
            frame_588[2] = can_auto_buffer[3] / 2;

            CAN_MEDIANAV->sendMsgBuf(0x588, 0, 8, frame_588);

            frame_559[0] = can_auto_buffer[4];

            CAN_MEDIANAV->sendMsgBuf(0x559, 0, 8, frame_559);
            break;
          case 0x673:
            frame_32D[0] = can_auto_buffer[0];
            frame_32D[1] = can_auto_buffer[1];
            frame_32D[2] = can_auto_buffer[2];
            frame_32D[3] = can_auto_buffer[3];
            frame_32D[4] = can_auto_buffer[4];
            frame_32D[5] = can_auto_buffer[5];

            CAN_MEDIANAV->sendMsgBuf(0x32D, 0, 8, frame_32D);

            frame_319[0] = can_auto_buffer[0];
            frame_319[1] = can_auto_buffer[1];
            frame_319[2] = can_auto_buffer[2] * 2;
            frame_319[3] = can_auto_buffer[3] * 2;
            frame_319[4] = can_auto_buffer[4] * 2;
            frame_319[5] = can_auto_buffer[5] * 2;

            CAN_MEDIANAV->sendMsgBuf(0x319, 0, 8, frame_319);
            break;
          case 0x5E9:
            CAN_MEDIANAV->sendMsgBuf(0x5E7, 0, 8, can_auto_buffer);
            break;
          case 0x4DE:
            frame_4DE[0] = can_auto_buffer[0];
            frame_4DE[1] = can_auto_buffer[2];
            frame_4DE[2] = can_auto_buffer[3];

            CAN_MEDIANAV->sendMsgBuf(0x4DE, 0, 8, frame_4DE);
            break;
          case 0x352:
            frame_590[0] = can_auto_buffer[3];
            CAN_MEDIANAV->sendMsgBuf(0x590, 0, 8, frame_590);
            break;
          case 0x5DA:
            frame_590[1] = can_auto_buffer[0];
            CAN_MEDIANAV->sendMsgBuf(0x590, 0, 8, frame_590);
            break;
          case 0x699:
            CAN_MEDIANAV->sendMsgBuf(0x32B, 0, 8, can_auto_buffer);
            break;
          case 0x186:
            frame_58E[0] = can_auto_buffer[0];
            frame_58E[1] = can_auto_buffer[1];
            frame_58E[2] = can_auto_buffer[2];
            frame_58E[4] = can_auto_buffer[5];

            CAN_MEDIANAV->sendMsgBuf(0x58E, 0, 8, frame_58E);
            break;
          case 0x090:
            frame_58E[6] = can_auto_buffer[0];

            CAN_MEDIANAV->sendMsgBuf(0x58E, 0, 8, frame_58E);
            break;
          case 0x023:
            frame_038[0] = can_auto_buffer[0];
            frame_038[1] = can_auto_buffer[1];

            CAN_MEDIANAV->sendMsgBuf(0x038, 0, 8, frame_038);
            break;
          case 0x685:
            frame_407[0] = can_auto_buffer[0];
            frame_407[1] = can_auto_buffer[1];
            frame_407[2] = can_auto_buffer[2];
            frame_407[3] = can_auto_buffer[3];
            frame_407[4] = can_auto_buffer[4];

            CAN_MEDIANAV->sendMsgBuf(0x407, 0, 8, frame_407);
            break;
          case 0x29A:
            frame_58D[0] = can_auto_buffer[0];
            frame_58D[1] = can_auto_buffer[1];
            frame_58D[2] = can_auto_buffer[2];
            frame_58D[3] = can_auto_buffer[3];

            CAN_MEDIANAV->sendMsgBuf(0x58D, 0, 8, frame_58D);
            break;
          case 0x29C:
            frame_58D[4] = can_auto_buffer[2];
            frame_58D[5] = can_auto_buffer[3];
            frame_58D[6] = can_auto_buffer[0];
            frame_58D[7] = can_auto_buffer[1];

            CAN_MEDIANAV->sendMsgBuf(0x58D, 0, 8, frame_58D);
            break;
          case 0x356:
            frame_342[4] = can_auto_buffer[4];
            CAN_MEDIANAV->sendMsgBuf(0x342, 0, 8, frame_342);
            break;
          case 0x405:
            CAN_MEDIANAV->sendMsgBuf(0x344, 0, 8, can_auto_buffer);
            break;
          case 0x401:
            CAN_MEDIANAV->sendMsgBuf(0x343, 0, 8, can_auto_buffer);
            break;
          case 0x668:
            frame_31A[0] = can_auto_buffer[0];
            frame_31A[1] = can_auto_buffer[1];

            CAN_MEDIANAV->sendMsgBuf(0x31A, 0, 8, frame_31A);
            break;
          case 0x4A4:
            frame_341[1] = can_auto_buffer[1];
            frame_341[2] = can_auto_buffer[2];
            frame_341[3] = can_auto_buffer[3];
            frame_341[4] = can_auto_buffer[4];
            frame_341[5] = can_auto_buffer[5];
            frame_341[6] = can_auto_buffer[6];

            CAN_MEDIANAV->sendMsgBuf(0x341, 0, 8, frame_341);
            break;
          case 0x3FA:
            frame_409[0] = can_auto_buffer[1];

            CAN_MEDIANAV->sendMsgBuf(0x409, 0, 8, frame_409);
            break;
        }

      }

      // listen from medianav side
      if (CAN_MSGAVAIL == CAN_MEDIANAV->checkReceive()) {
        unsigned char can_medianav_length = 0;
        unsigned char can_medianav_buffer[8];

        CAN_MEDIANAV->readMsgBuf(&can_medianav_length, can_medianav_buffer);

        unsigned long messageID = CAN_MEDIANAV->getCanId();

        switch (messageID) {
          case 0x31C:
            if (can_medianav_buffer[2] == 0x80) {
              CAN_AUTO->sendMsgBuf(0x433, 0, 8, can_medianav_buffer);
            }
            break;
          case 0x434:
            CAN_AUTO->sendMsgBuf(0x434, 0, 8, can_medianav_buffer);
            break;
          case 0x4DE:
            CAN_AUTO->sendMsgBuf(0x4DE, 0, 8, can_medianav_buffer);
            break;
          case 0x318:
            CAN_AUTO->sendMsgBuf(0x665, 0, 8, can_medianav_buffer);
            break;
        }

      }
    }
};