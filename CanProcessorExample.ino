#include "CanProcessor.cpp"

MCP_CAN CAN_AUTO(5);
MCP_CAN CAN_MEDIANAV(10);

CanProcessor canProcessor(&CAN_AUTO, &CAN_MEDIANAV);

void setup() {
  while (CAN_OK != CAN_AUTO.begin(CAN_500KBPS, MCP_8MHz));
  while (CAN_OK != CAN_MEDIANAV.begin(CAN_500KBPS, MCP_8MHz));
}

void loop() {
  canProcessor.handle();
}
