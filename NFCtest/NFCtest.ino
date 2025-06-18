/********************************************
 *  识别NFC卡的UID程序，最终结果可返回出校园卡的UIDhex值
 ********************************************/
#include <SPI.h>
#include <MFRC522.h>

/* --- 引脚 --- */
#define SS_PIN   10     // SDA / SS
#define RST_PIN   9     // RST

/* --- 对象 --- */
MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  /* 0. 打开串口 (可按需保留 while(!Serial) 逻辑) */
  Serial.begin(9600);
  delay(500);                     // 给监视器时间

  /* 1. 手动拉高 RST，确保芯片不上软掉电 */
  pinMode(RST_PIN, OUTPUT);       
  digitalWrite(RST_PIN, HIGH);    
  delay(5);                       

  /* 2. 初始化 SPI 与 RC522 */
  SPI.begin();
  mfrc522.PCD_Init();             // 内部还会再次操作 RST
  delay(10);                      //// ← 可选；对部分板子更稳

  Serial.println(F(">> MFRC522 初始化完成"));
  mfrc522.PCD_DumpVersionToSerial();
  Serial.println(F("请将卡片/标签靠近读卡区域...\n"));
}

void loop() {

  if (!mfrc522.PICC_IsNewCardPresent()) return;
  if (!mfrc522.PICC_ReadCardSerial())   return;

  /* 打印 UID */
  Serial.print("UID(hex)=");
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i], HEX);  // HEX = base-16
  }
  Serial.println();

  /* 打印类型 */
  MFRC522::PICC_Type type = mfrc522.PICC_GetType(mfrc522.uid.sak);
  Serial.print(F("PICC Type  = "));
  Serial.println(mfrc522.PICC_GetTypeName(type));
  Serial.println();

  /* 结束会话 */
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}
