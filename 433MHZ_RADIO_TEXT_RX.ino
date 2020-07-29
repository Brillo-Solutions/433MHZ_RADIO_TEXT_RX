byte rxdPkt, addrPkt;
byte chkPkt, pblePkt = 0x55;
byte prevPkt, nextPkt;
boolean rxAddr, rxData;
String dataPkt;

void setup() 
{
  Serial.begin(2400);
}

void loop() 
{
  if (Serial.available() > 0)
  {
    rxdPkt = Serial.read();
    if (rxdPkt == pblePkt)
      rxAddr = true;
    else if (rxAddr)
    {
      addrPkt = rxdPkt;
      rxAddr = false;
      rxData = true;
    }
    else if (rxData)
    {
      nextPkt = rxdPkt;
      rxData = false;
    }
    else
      chkPkt = rxdPkt;
  }

  if (chkPkt == (addrPkt + nextPkt))
    if (nextPkt != prevPkt)
    {
      if (nextPkt != '\n')
        dataPkt.concat((char)nextPkt);
      else
      {
        Serial.println("Message: " + dataPkt);
        dataPkt = "";
      }
      prevPkt = nextPkt;
    }
}