// UidStore.h
#pragma once
#include <Arduino.h>
#include <MFRC522.h>

// 最大支持的白名单卡片数，可根据需求调整
constexpr uint8_t MAX_UIDS = 32;

/**
 * 将 MFRC522::Uid 转换为大写十六进制字符串，不带冒号与补零，仅 0-9A-F 串联
 * @param uid  MFRC522 库中的 Uid 对象，包含 uidByte[] 和 size
 * @param out  输出缓冲区，至少需要长度 uid.size*2+1
 */
void uidToHex(const MFRC522::Uid &uid, char *out);

/**
 * 简单的基于数组的内置白名单管理
 * 支持在编译期直接修改列表，无需外部存储
 */
class UidStore {
public:
  /**
   * 在 setup() 中调用，向内部列表中添加硬编码的 UID 字符串
   */
  void begin();
  
  /**
   * 检查给定的十六进制 UID 字符串是否在白名单中，比较不区分大小写
   * @param uidHex  输入的 0-9A-F 字符串
   * @return true  在列表中
   * @return false 不在列表中
   */
  bool contains(const char *uidHex) const;

private:
  char list[MAX_UIDS][21]{};  // 存储最多 MAX_UIDS 条 UID，每条最长 20 字符 + '\0'
  uint8_t count = 0;          // 当前已添加 UID 数量
  
  /**
   * 内部方法：向数组中添加一条 UID，长度与边界检查
   * @param hex  传入的十六进制字符串
   */
  void add(const char *hex);
};