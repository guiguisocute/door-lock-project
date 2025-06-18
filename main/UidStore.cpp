// UidStore.cpp
#include <Arduino.h>     // 提供 strlen(), strncpy(), Serial 等
#include "UidStore.h"

// 将 uid.uidByte 数组转换为大写十六进制字符串，*nix printf 风格
void uidToHex(const MFRC522::Uid &uid, char *out) {
  uint8_t idx = 0;
  for (byte i = 0; i < uid.size; i++) {
    // 每个字节输出两位 HEX，不足补零
    sprintf(out + idx, "%02X", uid.uidByte[i]);
    idx += 2;
  }
  out[idx] = '\0'; // 字符串结尾
}

// 内部添加函数，实现边界检查并存储字符串
void UidStore::add(const char *hex) {
  if (count < MAX_UIDS && strlen(hex) < 21) {
    // 使用 strncpy 避免缓冲区溢出
    strncpy(list[count++], hex, 21);
  }
}

// 在此函数中维护所有白名单 UID
void UidStore::begin() {
  // ★ 在这里添加或删除 UID 条目
  add("9EC9687E");  // 曾梓豪校园卡 UID
  add("EE90BB9D");  // 徐雨航校园卡 UID
  add("412FF700");  // 白卡 UID
  add("AE88BB9D");  //郭嘉鹏校园卡
  add("5E9EBB9D");  //王毅校园卡
  // 打印已加载的条目数，方便调试

  Serial.print(F("UidStore initialized, entries = "));
  Serial.println(count);
}

// 遍历列表并进行不区分大小写的比较
bool UidStore::contains(const char *uidHex) const {
  for (uint8_t i = 0; i < count; i++) {
    // strcasecmp 在 <cstring> 提供，但 Arduino.h 中已声明
    if (!strcasecmp(uidHex, list[i])) return true;
  }
  return false;
}